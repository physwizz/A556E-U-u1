/*
 * s2mpb06-core.c - mfd core driver for the Samsung s2mpb06
 *
 * Copyright (C) 2022 Samsung Electronics
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * This driver is based on max77804.c
 */

#include <linux/module.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <linux/mutex.h>
#include <linux/mfd/core.h>
#include <linux/samsung/pmic/s2mpb06.h>
#include <linux/samsung/pmic/s2mpb06-regulator.h>
#include <linux/regulator/machine.h>

#if IS_ENABLED(CONFIG_OF)
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#endif /* CONFIG_OF */

static struct mfd_cell s2mpb06_devs[] = {
	{ .name = "s2mpb06-regulator", },
};

int s2mpb06_read_reg(struct i2c_client *i2c, uint8_t reg, uint8_t *dest)
{
	struct s2mpb06_dev *s2mpb06 = i2c_get_clientdata(i2c);
	int ret;

	mutex_lock(&s2mpb06->i2c_lock);
	ret = i2c_smbus_read_byte_data(i2c, reg);
	mutex_unlock(&s2mpb06->i2c_lock);
	if (ret < 0) {
		pr_info("%s: reg(0x%02hhx), ret(%d)\n", __func__, reg, ret);
		return ret;
	}

	ret &= 0xff;
	*dest = ret;
	return 0;
}
EXPORT_SYMBOL_GPL(s2mpb06_read_reg);

int s2mpb06_bulk_read(struct i2c_client *i2c, uint8_t reg, int count, uint8_t *buf)
{
	struct s2mpb06_dev *s2mpb06 = i2c_get_clientdata(i2c);
	int ret;

	mutex_lock(&s2mpb06->i2c_lock);
	ret = i2c_smbus_read_i2c_block_data(i2c, reg, count, buf);
	mutex_unlock(&s2mpb06->i2c_lock);
	if (ret < 0)
		return ret;

	return 0;
}
EXPORT_SYMBOL_GPL(s2mpb06_bulk_read);

int s2mpb06_write_reg(struct i2c_client *i2c, uint8_t reg, uint8_t value)
{
	struct s2mpb06_dev *s2mpb06 = i2c_get_clientdata(i2c);
	int ret;

	mutex_lock(&s2mpb06->i2c_lock);
	ret = i2c_smbus_write_byte_data(i2c, reg, value);
	mutex_unlock(&s2mpb06->i2c_lock);
	if (ret < 0)
		pr_info("%s: reg(0x%02hhx), ret(%d)\n", __func__, reg, ret);

	return ret;
}
EXPORT_SYMBOL_GPL(s2mpb06_write_reg);

int s2mpb06_bulk_write(struct i2c_client *i2c, uint8_t reg, int count, uint8_t *buf)
{
	struct s2mpb06_dev *s2mpb06 = i2c_get_clientdata(i2c);
	int ret;

	mutex_lock(&s2mpb06->i2c_lock);
	ret = i2c_smbus_write_i2c_block_data(i2c, reg, count, buf);
	mutex_unlock(&s2mpb06->i2c_lock);
	if (ret < 0)
		return ret;

	return 0;
}
EXPORT_SYMBOL_GPL(s2mpb06_bulk_write);

int s2mpb06_update_reg(struct i2c_client *i2c, uint8_t reg, uint8_t val, uint8_t mask)
{
	struct s2mpb06_dev *s2mpb06 = i2c_get_clientdata(i2c);
	int ret;

	mutex_lock(&s2mpb06->i2c_lock);
	ret = i2c_smbus_read_byte_data(i2c, reg);
	if (ret >= 0) {
		uint8_t old_val = ret & 0xff;
		uint8_t new_val = (val & mask) | (old_val & (~mask));
		ret = i2c_smbus_write_byte_data(i2c, reg, new_val);
	}
	mutex_unlock(&s2mpb06->i2c_lock);
	return ret;
}
EXPORT_SYMBOL_GPL(s2mpb06_update_reg);

#if IS_ENABLED(CONFIG_OF)
static int of_s2mpb06_dt(struct device *dev, struct s2mpb06_platform_data *pdata)
{
	struct device_node *np_s2mpb06 = dev->of_node;

	if (!np_s2mpb06)
		return -EINVAL;

	pdata->irq_gpio = of_get_named_gpio(np_s2mpb06, "s2mpb06,irq-gpio", 0);
	pdata->wakeup = of_property_read_bool(np_s2mpb06, "s2mpb06,wakeup");

	return 0;
}
#else
static int of_s2mpb06_dt(struct device *dev, struct s2mpb06_platform_data *pdata)
{
	return 0;
}
#endif /* CONFIG_OF */

static int s2mpb06_i2c_probe(struct i2c_client *i2c,
				const struct i2c_device_id *dev_id)
{
	struct s2mpb06_dev *s2mpb06;
	struct s2mpb06_platform_data *pdata = i2c->dev.platform_data;
	size_t size = 0;
	int ret = 0;
	uint8_t rev_id;

	dev_info(&i2c->dev, "%s start...\n", __func__);

	size = sizeof(struct s2mpb06_dev);
	s2mpb06 = devm_kzalloc(&i2c->dev, size, GFP_KERNEL);
	if (!s2mpb06)
		return -ENOMEM;

	size = sizeof(struct s2mpb06_platform_data);
	pdata = devm_kzalloc(&i2c->dev, size, GFP_KERNEL);
	if (!pdata)
		return -ENOMEM;

	ret = of_s2mpb06_dt(&i2c->dev, pdata);
	if (ret < 0) {
		dev_err(&i2c->dev, "Failed to get device of_node\n");
		return ret;
	}

	i2c->dev.platform_data = pdata;

	s2mpb06->dev = &i2c->dev;
	s2mpb06->i2c = i2c;
	s2mpb06->irq = i2c->irq;
	s2mpb06->pdata = pdata;
	pdata->irq_base = devm_irq_alloc_descs(s2mpb06->dev, -1, 600,
						S2MPB06_IRQ_NR, 0);
	if (pdata->irq_base < 0) {
		pr_err("%s: devm_irq_alloc_descs Fail! ret(%d)\n",
			__func__, pdata->irq_base);
		return -EINVAL;
	} else {
		s2mpb06->irq_base = pdata->irq_base;
	}
	s2mpb06->wakeup = pdata->wakeup;

	mutex_init(&s2mpb06->i2c_lock);

	i2c_set_clientdata(i2c, s2mpb06);

	ret = s2mpb06_read_reg(s2mpb06->i2c, S2MPB06_REG_PMIC_ID, &rev_id);
	if (ret < 0)
		goto err_irq_init;
	dev_info(&i2c->dev, "%s: device found: rev.0x%02hhx\n", __func__, rev_id);

	ret = s2mpb06_irq_init(s2mpb06);
	if (ret < 0)
		goto err_irq_init;

	ret = devm_mfd_add_devices(s2mpb06->dev, PLATFORM_DEVID_AUTO, s2mpb06_devs,
			      ARRAY_SIZE(s2mpb06_devs), NULL, 0, NULL);
	if (ret < 0)
		goto err_irq_init;

	ret = device_init_wakeup(s2mpb06->dev, pdata->wakeup);
	if (ret < 0) {
		dev_err(&i2c->dev, "%s: device_init_wakeup fail(%d)\n",
				__func__, ret);
		goto err_irq_init;
	}

	return 0;

err_irq_init:
	mutex_destroy(&s2mpb06->i2c_lock);
	return ret;
}

static void s2mpb06_i2c_remove(struct i2c_client *i2c)
{
	struct s2mpb06_dev *s2mpb06 = i2c_get_clientdata(i2c);

	if (s2mpb06->pdata->wakeup)
		device_init_wakeup(s2mpb06->dev, false);

	mutex_destroy(&s2mpb06->i2c_lock);
}

static const struct i2c_device_id s2mpb06_i2c_id[] = {
	{ MFD_DEV_NAME, 0 },
	{},
};
MODULE_DEVICE_TABLE(i2c, s2mpb06_i2c_id);

#if IS_ENABLED(CONFIG_OF)
static struct of_device_id s2mpb06_i2c_dt_ids[] = {
	{ .compatible = "s2mpb06,s2mpb06mfd" },
	{},
};
MODULE_DEVICE_TABLE(of, s2mpb06_i2c_dt_ids);
#endif /* CONFIG_OF */

#if IS_ENABLED(CONFIG_PM)
static int s2mpb06_suspend(struct device *dev)
{
	struct i2c_client *i2c = to_i2c_client(dev);
	struct s2mpb06_dev *s2mpb06 = i2c_get_clientdata(i2c);

	if (device_may_wakeup(dev))
		enable_irq_wake(s2mpb06->irq);

	disable_irq(s2mpb06->irq);

	return 0;
}

static int s2mpb06_resume(struct device *dev)
{
	struct i2c_client *i2c = to_i2c_client(dev);
	struct s2mpb06_dev *s2mpb06 = i2c_get_clientdata(i2c);

	if (device_may_wakeup(dev))
		disable_irq_wake(s2mpb06->irq);

	enable_irq(s2mpb06->irq);

	return 0;
}
#else
#define s2mpb06_suspend	NULL
#define s2mpb06_resume	NULL
#endif /* CONFIG_PM */

static const struct dev_pm_ops s2mpb06_pm = {
	.suspend = s2mpb06_suspend,
	.resume = s2mpb06_resume,
};


static struct i2c_driver s2mpb06_i2c_driver = {
	.driver		= {
		.name	= MFD_DEV_NAME,
		.owner	= THIS_MODULE,
#if IS_ENABLED(CONFIG_PM)
		.pm	= &s2mpb06_pm,
#endif /* CONFIG_PM */
#if IS_ENABLED(CONFIG_OF)
		.of_match_table	= s2mpb06_i2c_dt_ids,
#endif /* CONFIG_OF */
		.suppress_bind_attrs = true,
	},
	.probe		= s2mpb06_i2c_probe,
	.remove		= s2mpb06_i2c_remove,
	.id_table	= s2mpb06_i2c_id,
};

static int __init s2mpb06_i2c_init(void)
{
	pr_info("%s:%s\n", MFD_DEV_NAME, __func__);
	return i2c_add_driver(&s2mpb06_i2c_driver);
}
/* init early so consumer devices can complete system boot */
subsys_initcall(s2mpb06_i2c_init);

static void __exit s2mpb06_i2c_exit(void)
{
	i2c_del_driver(&s2mpb06_i2c_driver);
}
module_exit(s2mpb06_i2c_exit);

MODULE_DESCRIPTION("SAMSUNG S2MPB06 Multi-Function Core driver");
MODULE_LICENSE("GPL");
