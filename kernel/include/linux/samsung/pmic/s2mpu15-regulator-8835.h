/*
 * s2mpu15-regulator.h - Voltage regulator driver for the S2MPU15
 *
 *  Copyright (C) 2022 Samsung Electrnoics
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
 */

#ifndef __LINUX_MFD_S2MPU15_REGULATOR_H
#define __LINUX_MFD_S2MPU15_REGULATOR_H
#include <linux/i2c.h>

#if IS_ENABLED(CONFIG_S2MPU15_ADC_8835)
#include <linux/iio/iio.h>
#include <linux/iio/machine.h>
#include <linux/iio/driver.h>
#include <linux/iio/consumer.h>
#endif

/* Slave sid */
#define MAIN_CHANNEL	0 // TODO: check channel

/* PMIC base addr */
#define VGPIO_ADDR		0x00
#define COMMON_ADDR		0x03
#define RTC_ADDR		0x04
#define PMIC1_ADDR		0x05
#define PMIC2_ADDR		0x06
#define CLOSE1_ADDR		0x0E
#define CLOSE2_ADDR		0x0F
#define ADC_ADDR		0x0A
#define TEMP_ADDR		0x0C

#define S2MPU15_REG_INVALID             (0xFF)

/* PMIC ADDRESS: VGPIO(0x0) */
#define S2MPU15_VGPIO_REG0			0x00
#define S2MPU15_VGPIO_PSI			0x01
#define S2MPU15_VGPIO_VGI0			0x02
#define S2MPU15_VGPIO_VGI1			0x03
#define S2MPU15_VGPIO_VGI20			0x04
#define S2MPU15_VGPIO_VGI3			0x05
#define S2MPU15_VGPIO_VGI4			0x06
#define S2MPU15_VGPIO_VGI5			0x07
#define S2MPU15_VGPIO_VGI6			0x08
#define S2MPU15_VGPIO_VGI7			0x09
#define S2MPU15_VGPIO_VGI8			0x0A
#define S2MPU15_VGPIO_VGI9			0x0B
#define S2MPU15_VGPIO_VGI10			0x0C
#define S2MPU15_VGPIO_VGI11			0x0D
#define S2MPU15_VGPIO_VGI12			0x0E
#define S2MPU15_VGPIO_VGI13			0x0F
#define S2MPU15_VGPIO_VGI14			0x10
#define S2MPU15_VGPIO_VGI15			0x11
#define S2MPU15_VGPIO_VGI16			0x12
#define S2MPU15_VGPIO_VGI17			0x13
#define S2MPU15_VGPIO_VGI18			0x14

/* VGPIO TX (PMIC -> AP) table */
#define S2MPU15_VGI0_WRSTBO		(1 << 0)
#define S2MPU15_VGI0_ONOB		(1 << 1)
#define S2MPU15_VGI0_IRQ_M		(1 << 2)	// main
#define S2MPU15_VGI0_IRQ_S1		(1 << 3)	// sub
#define S2MPU15_VGI4_VOL_DN		(1 << 3)

/* PMIC ADDRESS: Common(0x3) */
#define S2MPU15_COMMON_VGPIO_REG0_1		0x00
#define S2MPU15_COMMON_VGPIO_REG0_2		0x01
#define S2MPU15_COMMON_CHIP_ID			0x0E
#define S2MPU15_COMMON_SPMI_CFG1		0x0F
#define S2MPU15_COMMON_SPMI_CFG2		0x10
#define S2MPU15_COMMON_SPMI_CFG3		0x11
#define S2MPU15_COMMON_COM_CTRL1		0x12
#define S2MPU15_COMMON_COM_CTRL2		0x13
#define S2MPU15_COMMON_COM_CTRL3		0x14
#define S2MPU15_COMMON_DUMP_CTRL		0x15
#define S2MPU15_COMMON_TX_MASK			0x16
#define S2MPU15_COMMON_IRQ			0x17
#define S2MPU15_COMMON_COM_CTRL4		0x18
#define S2MPU15_COMMON_COM_CLK_ON		0x19
#define S2MPU15_COMMON_COM_CLK_OFF		0x1A
#define S2MPU15_COMMON_COM_OM			0x1B
#define S2MPU15_COMMON_COM_OTP_TEST		0x1C
#define S2MPU15_COMMON_COM_OTP_ADRL		0x1D
#define S2MPU15_COMMON_COM_OTP_ADRH		0x1E
#define S2MPU15_COMMON_COM_OTP_DATA		0x1F
#define S2MPU15_COMMON_COM_MONSEL1		0x20
#define S2MPU15_COMMON_COM_MONSEL2		0x21
#define S2MPU15_COMMON_COM_MONRD1		0x22
#define S2MPU15_COMMON_COM_MONRD2		0x23
#define S2MPU15_COMMON_COM_CCD			0x24
#define S2MPU15_COMMON_CHECKSUM_DATA		0x25
#define S2MPU15_COMMON_CHECKSUM_REF		0x26
#define S2MPU15_COMMON_CHECKSUM_RESULT		0x27
#define S2MPU15_COMMON_BUCK_OM			0x28
#define S2MPU15_COMMON_BUCK_MON_SEL		0x29
#define S2MPU15_COMMON_BUCK_MON_EN1		0x2A
#define S2MPU15_COMMON_BUCK_MON_EN2		0x2B

/* CHIP ID MASK */
#define S2MPU15_CHIP_ID_MASK			(0xFF)
#define S2MPU15_CHIP_ID_HW_MASK			(0x0F)
#define S2MPU15_CHIP_ID_SW_MASK			(0xF0)

/* TX_MASK MASK */
#define S2MPU15_IRQ_TX_EN			(1 << 7)
#define S2MPU15_VOLDN_TX_ENB_MASK		(1 << 5)
#define S2MPU15_ONOB_TX_ENB_MASK		(1 << 4)
#define S2MPU15_WRSTBO_TX_ENB_MASK		(1 << 3)
#define S2MPU15_GPIO_IRQM_MASK			(1 << 2)
#define S2MPU15_ADC_IRQM_MASK			(1 << 1)
#define S2MPU15_PM_IRQM_MASK			(1 << 0)

/* IRQ MASK */
#define S2MPU15_GPIO_IRQ		(1 << 2)
#define S2MPU15_ADC_IRQ			(1 << 1)
#define S2MPU15_PM_IRQ			(1 << 0)

/* PMIC ADDRESS: OOTP1(0x05) */
#define S2MPU15_PM1_INT1			0x00
#define S2MPU15_PM1_INT2			0x01
#define S2MPU15_PM1_INT3			0x02
#define S2MPU15_PM1_INT4			0x03
#define S2MPU15_PM1_INT5			0x04
#define S2MPU15_PM1_INT6			0x05
#define S2MPU15_PM1_INT7			0x06
#define S2MPU15_PM1_INT8			0x07
#define S2MPU15_PM1_INT1M			0x08
#define S2MPU15_PM1_INT2M			0x09
#define S2MPU15_PM1_INT3M			0x0A
#define S2MPU15_PM1_INT4M			0x0B
#define S2MPU15_PM1_INT5M			0x0C
#define S2MPU15_PM1_INT6M			0x0D
#define S2MPU15_PM1_INT7M			0x0E
#define S2MPU15_PM1_INT8M			0x0F
#define S2MPU15_PM1_STATUS1			0x10
#define S2MPU15_PM1_STATUS2			0x11
#define S2MPU15_PM1_STATUS3			0x12
#define S2MPU15_PM1_STATUS4			0x13
#define S2MPU15_PM1_PWRONSRC1			0x14
#define S2MPU15_PM1_PWRONSRC2			0x15
#define S2MPU15_PM1_OFFSRC1_CUR			0x16
#define S2MPU15_PM1_OFFSRC2_CUR			0x17
#define S2MPU15_PM1_OFFSRC1_OLD1		0x18
#define S2MPU15_PM1_OFFSRC2_OLD1		0x19
#define S2MPU15_PM1_OFFSRC1_OLD2		0x1A
#define S2MPU15_PM1_OFFSRC2_OLD2		0x1B
#define S2MPU15_PM1_BU_CHG			0x1C
#define S2MPU15_PM1_RTC_BUF			0x1D
#define S2MPU15_PM1_CTRL1			0x1E
#define S2MPU15_PM1_CTRL2			0x1F
#define S2MPU15_PM1_CTRL3			0x20
#define S2MPU15_PM1_ETC_OTP1			0x21
#define S2MPU15_PM1_ETC_OTP2			0x22
#define S2MPU15_PM1_UVLO_OTP			0x23
#define S2MPU15_PM1_CFG_PM			0x24
#define S2MPU15_PM1_TIME_CTRL			0x25
#define S2MPU15_PM1_BUCK1M_CTRL			0x26
#define S2MPU15_PM1_BUCK1M_OUT1			0x27
#define S2MPU15_PM1_BUCK1M_OUT2			0x28
#define S2MPU15_PM1_BUCK1M_OUT3			0x29
#define S2MPU15_PM1_BUCK1M_OUT4			0x2A
#define S2MPU15_PM1_BUCK1M_DVS			0x2B
#define S2MPU15_PM1_BUCK1M_AFM			0x2C
#define S2MPU15_PM1_BUCK1M_AFMX			0x2D
#define S2MPU15_PM1_BUCK1M_AFMY			0x2E
#define S2MPU15_PM1_BUCK1M_AFMZ			0x2F
#define S2MPU15_PM1_BUCK1M_OCP			0x30
#define S2MPU15_PM1_BUCK1M_AVP			0x31
#define S2MPU15_PM1_BUCK2M_CTRL			0x32
#define S2MPU15_PM1_BUCK2M_OUT1			0x33
#define S2MPU15_PM1_BUCK2M_OUT2			0x34
#define S2MPU15_PM1_BUCK2M_OUT3			0x35
#define S2MPU15_PM1_BUCK2M_OUT4			0x36
#define S2MPU15_PM1_BUCK2M_DVS			0x37
#define S2MPU15_PM1_BUCK2M_AFM			0x38
#define S2MPU15_PM1_BUCK2M_AFMX			0x39
#define S2MPU15_PM1_BUCK2M_AFMY			0x3A
#define S2MPU15_PM1_BUCK2M_AFMZ			0x3B
#define S2MPU15_PM1_BUCK2M_OCP			0x3C
#define S2MPU15_PM1_BUCK2M_AVP			0x3D
#define S2MPU15_PM1_BUCK3M_CTRL			0x3E
#define S2MPU15_PM1_BUCK3M_OUT1			0x3F
#define S2MPU15_PM1_BUCK3M_OUT2			0x40
#define S2MPU15_PM1_BUCK3M_OUT3			0x41
#define S2MPU15_PM1_BUCK3M_OUT4			0x42
#define S2MPU15_PM1_BUCK3M_DVS			0x43
#define S2MPU15_PM1_BUCK3M_AFM			0x44
#define S2MPU15_PM1_BUCK3M_AFMX			0x45
#define S2MPU15_PM1_BUCK3M_AFMY			0x46
#define S2MPU15_PM1_BUCK3M_AFMZ			0x47
#define S2MPU15_PM1_BUCK3M_OCP			0x48
#define S2MPU15_PM1_BUCK3M_AVP			0x49
#define S2MPU15_PM1_BUCK4M_CTRL			0x4A
#define S2MPU15_PM1_BUCK4M_OUT1			0x4B
#define S2MPU15_PM1_BUCK4M_OUT2			0x4C
#define S2MPU15_PM1_BUCK4M_OUT3			0x4D
#define S2MPU15_PM1_BUCK4M_OUT4			0x4E
#define S2MPU15_PM1_BUCK4M_DVS			0x4F
#define S2MPU15_PM1_BUCK4M_AFM			0x50
#define S2MPU15_PM1_BUCK4M_AFMX			0x51
#define S2MPU15_PM1_BUCK4M_AFMY			0x52
#define S2MPU15_PM1_BUCK4M_AFMZ			0x53
#define S2MPU15_PM1_BUCK4M_OCP			0x54
#define S2MPU15_PM1_BUCK4M_AVP			0x55
#define S2MPU15_PM1_BUCK5M_CTRL			0x56
#define S2MPU15_PM1_BUCK5M_OUT1			0x57
#define S2MPU15_PM1_BUCK5M_OUT2			0x58
#define S2MPU15_PM1_BUCK5M_OUT3			0x59
#define S2MPU15_PM1_BUCK5M_OUT4			0x5A
#define S2MPU15_PM1_BUCK5M_DVS			0x5B
#define S2MPU15_PM1_BUCK5M_AFM			0x5C
#define S2MPU15_PM1_BUCK5M_AFMX			0x5D
#define S2MPU15_PM1_BUCK5M_AFMY			0x5E
#define S2MPU15_PM1_BUCK5M_AFMZ			0x5F
#define S2MPU15_PM1_BUCK5M_OCP			0x60
#define S2MPU15_PM1_BUCK5M_AVP			0x61
#define S2MPU15_PM1_BUCK6M_CTRL			0x62
#define S2MPU15_PM1_BUCK6M_OUT1			0x63
#define S2MPU15_PM1_BUCK6M_OUT2			0x64
#define S2MPU15_PM1_BUCK6M_OUT3			0x65
#define S2MPU15_PM1_BUCK6M_OUT4			0x66
#define S2MPU15_PM1_BUCK6M_DVS			0x67
#define S2MPU15_PM1_BUCK6M_AFM			0x68
#define S2MPU15_PM1_BUCK6M_AFMX			0x69
#define S2MPU15_PM1_BUCK6M_AFMY			0x6A
#define S2MPU15_PM1_BUCK6M_AFMZ			0x6B
#define S2MPU15_PM1_BUCK6M_OCP			0x6C
#define S2MPU15_PM1_BUCK6M_AVP			0x6D
#define S2MPU15_PM1_BUCK7M_CTRL			0x6E
#define S2MPU15_PM1_BUCK7M_OUT1			0x6F
#define S2MPU15_PM1_BUCK7M_OUT2			0x70
#define S2MPU15_PM1_BUCK7M_OUT3			0x71
#define S2MPU15_PM1_BUCK7M_OUT4			0x72
#define S2MPU15_PM1_BUCK7M_DVS			0x73
#define S2MPU15_PM1_BUCK7M_AFM			0x74
#define S2MPU15_PM1_BUCK7M_AFMX			0x75
#define S2MPU15_PM1_BUCK7M_AFMY			0x76
#define S2MPU15_PM1_BUCK7M_AFMZ			0x77
#define S2MPU15_PM1_BUCK7M_OCP			0x78
#define S2MPU15_PM1_BUCK7M_AVP			0x79
#define S2MPU15_PM1_BUCK8M_CTRL			0x7A
#define S2MPU15_PM1_BUCK8M_OUT1			0x7B
#define S2MPU15_PM1_BUCK8M_OUT2			0x7C
#define S2MPU15_PM1_BUCK8M_OUT3			0x7D
#define S2MPU15_PM1_BUCK8M_OUT4			0x7E
#define S2MPU15_PM1_BUCK8M_DVS			0x7F
#define S2MPU15_PM1_BUCK8M_AFM			0x80
#define S2MPU15_PM1_BUCK8M_AFMX			0x81
#define S2MPU15_PM1_BUCK8M_AFMY			0x82
#define S2MPU15_PM1_BUCK8M_AFMZ			0x83
#define S2MPU15_PM1_BUCK8M_OCP			0x84
#define S2MPU15_PM1_BUCK8M_AVP			0x85
#define S2MPU15_PM1_BUCK_SR1M_CTRL		0x86
#define S2MPU15_PM1_BUCK_SR1M_OUT1		0x87
#define S2MPU15_PM1_BUCK_SR1M_OUT2		0x88
#define S2MPU15_PM1_BUCK_SR1M_DVS		0x89
#define S2MPU15_PM1_BUCK_SR1M_OCP		0x8A
#define S2MPU15_PM1_BUCK_SR2M_CTRL		0x8B
#define S2MPU15_PM1_BUCK_SR2M_OUT1		0x8C
#define S2MPU15_PM1_BUCK_SR2M_OUT2		0x8D
#define S2MPU15_PM1_BUCK_SR2M_DVS		0x8E
#define S2MPU15_PM1_BUCK_SR2M_OCP		0x8F
#define S2MPU15_PM1_BUCK_SR3M_CTRL		0x90
#define S2MPU15_PM1_BUCK_SR3M_OUT1		0x91
#define S2MPU15_PM1_BUCK_SR3M_OUT2		0x92
#define S2MPU15_PM1_BUCK_SR3M_DVS		0x93
#define S2MPU15_PM1_BUCK_SR3M_OCP		0x94
#define S2MPU15_PM1_BUCK_SR4M_CTRL		0x95
#define S2MPU15_PM1_BUCK_SR4M_OUT1		0x96
#define S2MPU15_PM1_BUCK_SR4M_OUT2		0x97
#define S2MPU15_PM1_BUCK_SR4M_DVS		0x98
#define S2MPU15_PM1_BUCK_SR4M_OCP		0x99
#define S2MPU15_PM1_LDO1M_CTRL			0x9A
#define S2MPU15_PM1_LDO1M_OUT			0x9B
#define S2MPU15_PM1_LDO2M_CTRL			0x9C
#define S2MPU15_PM1_LDO3M_CTRL			0x9D
#define S2MPU15_PM1_LDO3M_OUT			0x9E
#define S2MPU15_PM1_LDO4M_CTRL			0x9F
#define S2MPU15_PM1_LDO5M_CTRL			0xA0
#define S2MPU15_PM1_LDO5M_OUT			0xA1
#define S2MPU15_PM1_LDO6M_CTRL			0xA2
#define S2MPU15_PM1_LDO7M_CTRL			0xA3
#define S2MPU15_PM1_LDO8M_CTRL			0xA4
#define S2MPU15_PM1_LDO8M_OUT1			0xA5
#define S2MPU15_PM1_LDO8M_OUT2			0xA6
#define S2MPU15_PM1_LDO8M_OUT3			0xA7
#define S2MPU15_PM1_LDO8M_OUT4			0xA8
#define S2MPU15_PM1_LDO9M_CTRL			0xA9
#define S2MPU15_PM1_LDO9M_OUT			0xAA
#define S2MPU15_PM1_LDO10M_CTRL			0xAB
#define S2MPU15_PM1_LDO11M_CTRL			0xAC
#define S2MPU15_PM1_LDO12M_CTRL			0xAD
#define S2MPU15_PM1_LDO12M_OUT1			0xAE
#define S2MPU15_PM1_LDO12M_OUT2			0xAF
#define S2MPU15_PM1_LDO12M_OUT3			0xB0
#define S2MPU15_PM1_LDO12M_OUT4			0xB1
#define S2MPU15_PM1_LDO13M_CTRL			0xB2
#define S2MPU15_PM1_LDO13M_OUT			0xB3
#define S2MPU15_PM1_LDO14M_CTRL			0xB4
#define S2MPU15_PM1_LDO14M_OUT			0xB5
#define S2MPU15_PM1_LDO15M_CTRL			0xB6
#define S2MPU15_PM1_LDO15M_OUT			0xB7
#define S2MPU15_PM1_LDO16M_CTRL			0xB8
#define S2MPU15_PM1_LDO17M_CTRL			0xB9
#define S2MPU15_PM1_LDO17M_OUT			0xBA
#define S2MPU15_PM1_LDO18M_CTRL			0xBB
#define S2MPU15_PM1_LDO19M_CTRL			0xBC
#define S2MPU15_PM1_LDO19M_OUT1			0xBD
#define S2MPU15_PM1_LDO19M_OUT2			0xBE
#define S2MPU15_PM1_LDO19M_OUT3			0xBF
#define S2MPU15_PM1_LDO19M_OUT4			0xC0
#define S2MPU15_PM1_LDO20M_CTRL			0xC1
#define S2MPU15_PM1_LDO20M_OUT1			0xC2
#define S2MPU15_PM1_LDO20M_OUT2			0xC3
#define S2MPU15_PM1_LDO20M_OUT3			0xC4
#define S2MPU15_PM1_LDO20M_OUT4			0xC5
#define S2MPU15_PM1_LDO21M_CTRL			0xC6
#define S2MPU15_PM1_LDO21M_OUT			0xC7
#define S2MPU15_PM1_LDO22M_CTRL			0xC8
#define S2MPU15_PM1_LDO23M_CTRL			0xC9
#define S2MPU15_PM1_LDO23M_OUT			0xCA
#define S2MPU15_PM1_LDO24M_CTRL			0xCB
#define S2MPU15_PM1_LDO25M_CTRL			0xCC
#define S2MPU15_PM1_LDO25M_OUT			0xCD
#define S2MPU15_PM1_LDO26M_CTRL			0xCE
#define S2MPU15_PM1_LDO27M_CTRL			0xCF
#define S2MPU15_PM1_LDO27M_OUT			0xD0
#define S2MPU15_PM1_LDO28M_CTRL			0xD1
#define S2MPU15_PM1_LDO29M_CTRL			0xD2
#define S2MPU15_PM1_LDO29_OUT2			0xD3
#define S2MPU15_PM1_LDO29_OUT3			0xD4
#define S2MPU15_PM1_LDO29_OUT4			0xD5
#define S2MPU15_PM1_LDO30M_CTRL			0xD6
#define S2MPU15_PM1_LDO31M_CTRL			0xD7
#define S2MPU15_PM1_LDO31M_OUT			0xD8
#define S2MPU15_PM1_LDO32M_CTRL			0xD9
#define S2MPU15_PM1_LDO33M_CTRL			0xDA
#define S2MPU15_PM1_LDO34M_CTRL			0xDB
#define S2MPU15_PM1_LDO34M_OUT			0xDC
#define S2MPU15_PM1_LDO35M_CTRL			0xDD
#define S2MPU15_PM1_LDO35M_OUT			0xDE
#define S2MPU15_PM1_LDO_DSCH1			0xDF
#define S2MPU15_PM1_LDO_DSCH2			0xE0
#define S2MPU15_PM1_LDO_DSCH3			0xE1
#define S2MPU15_PM1_DVS_LDO_CTRL1		0xE2
#define S2MPU15_PM1_DVS_LDO_CTRL2		0xE3
#define S2MPU15_PM1_DVS_LDO_CTRL3		0xE4
#define S2MPU15_PM1_DVS_LDO_CTRL4		0xE5
#define S2MPU15_PM1_DVS_LDO_CTRL5		0xE6
#define S2MPU15_PM1_DVS_LDO_CTRL6		0xE7
#define S2MPU15_PM1_DVS_LDO34_CTRL		0xE8
#define S2MPU15_PM1_DVS_LDO35_CTRL		0xE9
#define S2MPU15_PM1_GPIO_SEQ_CTRL		0xEA
#define S2MPU15_PM1_GPIO2_SET			0xEB
#define S2MPU15_PM1_GPIO3_SET			0xEC
#define S2MPU15_PM1_GPIO_MODE			0xED
#define S2MPU15_PM1_GPIO_STATUS			0xEE
#define S2MPU15_PM1_GPIO_INTM			0xEF
#define S2MPU15_PM1_GPIO_INT			0xF0
#define S2MPU15_PM1_MEM_SEL			0xFA
#define S2MPU15_PM1_EXT_CTRL5			0xFB
#define S2MPU15_PM1_EXT_CTRL4			0xFC
#define S2MPU15_PM1_EXT_CTRL3			0xFD
#define S2MPU15_PM1_EXT_CTRL2			0xFE
#define S2MPU15_PM1_EXT_CTRL1			0xFF

/* PMIC ADDRESS: OOTP2(0x6) */
#define S2MPU15_PM2_M_SEL_VGPIO1		0x4C
#define S2MPU15_PM2_M_SEL_VGPIO2		0x4D
#define S2MPU15_PM2_M_SEL_VGPIO3		0x4E
#define S2MPU15_PM2_M_SEL_VGPIO4		0x4F
#define S2MPU15_PM2_M_SEL_VGPIO5		0x50
#define S2MPU15_PM2_M_SEL_VGPIO6		0x51
#define S2MPU15_PM2_M_SEL_VGPIO7		0x52
#define S2MPU15_PM2_M_SEL_VGPIO8		0x53
#define S2MPU15_PM2_M_SEL_VGPIO9		0x54
#define S2MPU15_PM2_M_SEL_VGPIO10		0x55
#define S2MPU15_PM2_M_SEL_VGPIO11		0x56
#define S2MPU15_PM2_M_SEL_VGPIO12		0x57
#define S2MPU15_PM2_M_SEL_VGPIO13		0x58
#define S2MPU15_PM2_M_SEL_VGPIO14		0x59
#define S2MPU15_PM2_M_SEL_VGPIO15		0x5A
#define S2MPU15_PM2_M_SEL_VGPIO16		0x5B
#define S2MPU15_PM2_M_SEL_VGPIO17		0x5C
#define S2MPU15_PM2_M_SEL_VGPIO18		0x5D
#define S2MPU15_PM2_M_SEL_VGPIO19		0x5E
#define S2MPU15_PM2_M_SEL_VGPIO20		0x5F
#define S2MPU15_PM2_M_SEL_VGPIO21		0x60
#define S2MPU15_PM2_M_SEL_VGPIO22		0x61
#define S2MPU15_PM2_M_SEL_VGPIO23		0x62
#define S2MPU15_PM2_M_SEL_VGPIO24		0x63
#define S2MPU15_PM2_M_SEL_VGPIO25		0x64
#define S2MPU15_PM2_M_SEL_VGPIO26		0x65
#define S2MPU15_PM2_M_SEL_VGPIO27		0x66
#define S2MPU15_PM2_M_SEL_VGPIO28		0x67
#define S2MPU15_PM2_M_SEL_VGPIO29		0x68
#define S2MPU15_PM2_M_SEL_VGPIO30		0x69
#define S2MPU15_PM2_M_SEL_VGPIO31		0x6A
#define S2MPU15_PM2_M_SEL_VGPIO32		0x6B
#define S2MPU15_PM2_M_SEL_VGPIO33		0x6C
#define S2MPU15_PM2_M_SEL_VGPIO34		0x6D
#define S2MPU15_PM2_M_SEL_VGPIO35		0x6E
#define S2MPU15_PM2_M_SEL_VGPIO36		0x6F
#define S2MPU15_PM2_M_SEL_VGPIO37		0x70
#define S2MPU15_PM2_M_SEL_VGPIO38		0x71
#define S2MPU15_PM2_M_SEL_VGPIO39		0x72
#define S2MPU15_PM2_M_SEL_VGPIO40		0x73
#define S2MPU15_PM2_M_SEL_VGPIO41		0x74
#define S2MPU15_PM2_M_SEL_VGPIO42		0x75
#define S2MPU15_PM2_M_SEL_VGPIO43		0x76
#define S2MPU15_PM2_M_SEL_VGPIO44		0x77
#define S2MPU15_PM2_M_SEL_VGPIO45		0x78
#define S2MPU15_PM2_M_SEL_VGPIO46		0x79
#define S2MPU15_PM2_M_SEL_VGPIO47		0x7A
#define S2MPU15_PM2_M_SEL_VGPIO48		0x7B
#define S2MPU15_PM2_M_SEL_VGPIO49		0x7C
#define S2MPU15_PM2_M_SEL_VGPIO50		0x7D
#define S2MPU15_PM2_M_SEL_DVS_EN1		0x7E
#define S2MPU15_PM2_M_SEL_DVS_EN2		0x7F
#define S2MPU15_PM2_M_SEL_DVS_EN3		0x80
#define S2MPU15_PM2_M_SEL_DVS_EN4		0x81
#define S2MPU15_PM2_M_SEL_DVS_EN5		0x82
#define S2MPU15_PM2_M_SEL_DVS_EN6		0x83
#define S2MPU15_PM2_M_SEL_DVS_EN7		0x84
#define S2MPU15_PM2_M_SEL_DVS_EN8		0x85
#define S2MPU15_PM2_M_SEL_DVS_EN9		0x86
#define S2MPU15_PM2_OFF_CTRL1			0x87
#define S2MPU15_PM2_OFF_CTRL2			0x88
#define S2MPU15_PM2_OFF_CTRL3			0x89
#define S2MPU15_PM2_OFF_CTRL4			0x8A
#define S2MPU15_PM2_OFF_CTRL5			0x8B
#define S2MPU15_PM2_OFF_CTRL6			0x8C
#define S2MPU15_PM2_OFF_CTRL7			0x8D
#define S2MPU15_PM2_EXT_EN			0x8E
#define S2MPU15_PM2_SUB_CTRL			0x8F
#define S2MPU15_PM2_SEQ_CTRL			0x90
#define S2MPU15_PM2_CFG_PM2			0x91
#define S2MPU15_PM2_CFG_PM3			0x92
#define S2MPU15_PM2_PSI_CTRL1			0x93
#define S2MPU15_PM2_PSI_CTRL2			0x94
#define S2MPU15_PM2_PSI_CTRL3			0x95
#define S2MPU15_PM2_CFG_PM4			0x96
#define S2MPU15_PM2_LDO_OI_CTRL1		0x97
#define S2MPU15_PM2_LDO_OI_CTRL2		0x98
#define S2MPU15_PM2_LDO_OI_CTRL3		0x99
#define S2MPU15_PM2_LDO_OI_CTRL4		0x9A
#define S2MPU15_PM2_OI_OVP_CTRL			0x9B
#define S2MPU15_PM2_OVP_CTRL2			0x9C
#define S2MPU15_PM2_IPTAT			0x9D
#define S2MPU15_PM2_AFM_CH_SEL1			0x9E
#define S2MPU15_PM2_AFM_CH_SEL2			0x9F

/* PMIC 1 mask */
#define BUCK_RAMP_MASK			(0x03)
#define BUCK_RAMP_UP_SHIFT		6

/* S2MPU15 regulator ids */
enum s2mpu15_regulators {
	S2MPU15_BUCK1,
	S2MPU15_BUCK2,
	S2MPU15_BUCK3,
	S2MPU15_BUCK4,
	S2MPU15_BUCK5,
	S2MPU15_BUCK6,
	S2MPU15_BUCK7,
	S2MPU15_BUCK8,
	S2MPU15_BUCK_SR1,
	S2MPU15_BUCK_SR2,
	S2MPU15_BUCK_SR3,
	S2MPU15_BUCK_SR4,
	S2MPU15_LDO1,
	S2MPU15_LDO2,
	S2MPU15_LDO3,
	S2MPU15_LDO4,
	S2MPU15_LDO5,
	S2MPU15_LDO6,
	S2MPU15_LDO7,
	//S2MPU15_LDO8,
	//S2MPU15_LDO9,
	//S2MPU15_LDO10,
	S2MPU15_LDO11,
	//S2MPU15_LDO12,
	//S2MPU15_LDO13,
	//S2MPU15_LDO14,
	S2MPU15_LDO15,
	S2MPU15_LDO16,
	S2MPU15_LDO17,
	S2MPU15_LDO18,
	S2MPU15_LDO19,
	//S2MPU15_LDO20,
	//S2MPU15_LDO21,
	S2MPU15_LDO22,
	//S2MPU15_LDO23,
	//S2MPU15_LDO24,
	//S2MPU15_LDO25,
	//S2MPU15_LDO26,
	//S2MPU15_LDO27,
	S2MPU15_LDO28,
	S2MPU15_LDO29,
	S2MPU15_LDO30,
	S2MPU15_LDO31,
	S2MPU15_LDO32,
	S2MPU15_LDO33,
	S2MPU15_LDO34,
	S2MPU15_LDO35,
	S2MPU15_REG_MAX,
};

/* BUCKs 1M to 8M */
#define S2MPU15_BUCK_MIN1	300000
#define S2MPU15_BUCK_STEP1	6250
/* BUCKs SR1M to SR3M  */
#define S2MPU15_BUCK_MIN2	300000
#define S2MPU15_BUCK_STEP2	6250
/* BUCKs SR4M */
#define S2MPU15_BUCK_MIN3	700000
#define S2MPU15_BUCK_STEP3	6250
/* (LV) N/PLDOs 1M/3M/5M/8M/9M/12M~15M/17M/19M~21M/23M/25M/27M/31M/34M/35M */
#define S2MPU15_LDO_MIN1	300000
#define S2MPU15_LDO_STEP1	6250
/* (IV) PLDOs 4M/7M/16M/22M/24M/26M/28M/30M */
#define S2MPU15_LDO_MIN2	1500000
#define S2MPU15_LDO_STEP2	12500
/* PLDOs 18M */
#define S2MPU15_LDO_MIN3	700000
#define S2MPU15_LDO_STEP3	25000
/* (MV) PLDOs 2M/6M/10M/11M/29M/32M/33M */
#define S2MPU15_LDO_MIN4	1800000
#define S2MPU15_LDO_STEP4	25000

/* LDO/BUCK output voltage control */
#define S2MPU15_LDO_VSEL_MASK1	0xFF	/* LDO_OUT  */
#define S2MPU15_LDO_VSEL_MASK2	0x3F	/* LDO_CTRL */
#define S2MPU15_BUCK_VSEL_MASK	0xFF	/* BUCK_OUT */
#define S2MPU15_BUCK_N_VOLTAGES (S2MPU15_BUCK_VSEL_MASK + 1)

/* Buck/LDO Enable control [7:6] */
#define S2MPU15_ENABLE_SHIFT	0x06
#define S2MPU15_ENABLE_MASK	(0x03 << S2MPU15_ENABLE_SHIFT)
#define S2MPU15_SEL_VGPIO_ON	(0x01 << S2MPU15_ENABLE_SHIFT)

/* soft start time */
#define S2MPU15_ENABLE_TIME_LDO		128
#define S2MPU15_ENABLE_TIME_BUCK	130
#define S2MPU15_ENABLE_TIME_BUCK_SR	130

#define S2MPU15_REGULATOR_MAX (S2MPU15_REG_MAX)

/* POWER-KEY MASK */
#define S2MPU15_STATUS1_PWRON		(1 << 0)
#define S2MPU15_PWRKEY_PRESS		(1 << 1)
#define S2MPU15_PWRKEY_RELEASE		(1 << 0)

/* VOL-DOWN-KEY MASK */
#define S2MPU15_STATUS1_MRB		(1 << 4)
#define S2MPU15_VOLDN_PRESS		(1 << 7)
#define S2MPU15_VOLDN_RELEASE		(1 << 6)

enum s2mpu15_irq_source {
	S2MPU15_PMIC_INT1 = 0,
	S2MPU15_PMIC_INT2,
	S2MPU15_PMIC_INT3,
	S2MPU15_PMIC_INT4,
	S2MPU15_PMIC_INT5,
	S2MPU15_PMIC_INT6,
	S2MPU15_PMIC_INT7,
	S2MPU15_PMIC_INT8,
	S2MPU15_IRQ_GROUP_NR,
};

#define S2MPU15_NUM_IRQ_PMIC_REGS	8
#define S2MPU15_BUCK_MAX		12
#define S2MPU15_TEMP_MAX		2

enum s2mpu15_irq {
	S2MPU15_PMIC_IRQ_PWRONR_INT1,
	S2MPU15_PMIC_IRQ_PWRONP_INT1,
	S2MPU15_PMIC_IRQ_JIGONBF_INT1,
	S2MPU15_PMIC_IRQ_JIGONBR_INT1,
	S2MPU15_PMIC_IRQ_ACOKBF_INT1,
	S2MPU15_PMIC_IRQ_ACOKBR_INT1,
	S2MPU15_PMIC_IRQ_PWRON1S_INT1,
	S2MPU15_PMIC_IRQ_MRB_INT1,

	S2MPU15_PMIC_IRQ_RTC60S_INT2,
	S2MPU15_PMIC_IRQ_RTCA1_INT2,
	S2MPU15_PMIC_IRQ_RTCA0_INT2,
	S2MPU15_PMIC_IRQ_SMPL_INT2,
	S2MPU15_PMIC_IRQ_RTC1S_INT2,
	S2MPU15_PMIC_IRQ_WTSR_INT2,
	S2MPU15_PMIC_IRQ_BUCK_AUTO_EXIT_INT2,
	S2MPU15_PMIC_IRQ_WRSTB_INT2,

	S2MPU15_PMIC_IRQ_120C_INT3,
	S2MPU15_PMIC_IRQ_140C_INT3,
	S2MPU15_PMIC_IRQ_TSD_INT3,
	S2MPU15_PMIC_IRQ_OVP_INT3,
	S2MPU15_PMIC_IRQ_TX_TRAN_FAIL_INT3,
	S2MPU15_PMIC_IRQ_OTP_CSUM_ERR_INT3,
	S2MPU15_PMIC_IRQ_VOLDNR_INT3,
	S2MPU15_PMIC_IRQ_VOLDNP_INT3,

	S2MPU15_PMIC_IRQ_OCP_B1M_INT4,
	S2MPU15_PMIC_IRQ_OCP_B2M_INT4,
	S2MPU15_PMIC_IRQ_OCP_B3M_INT4,
	S2MPU15_PMIC_IRQ_OCP_B4M_INT4,
	S2MPU15_PMIC_IRQ_OCP_B5M_INT4,
	S2MPU15_PMIC_IRQ_OCP_B6M_INT4,
	S2MPU15_PMIC_IRQ_OCP_B7M_INT4,
	S2MPU15_PMIC_IRQ_OCP_B8M_INT4,

	S2MPU15_PMIC_IRQ_OCP_SR1M_INT5,
	S2MPU15_PMIC_IRQ_OCP_SR2M_INT5,
	S2MPU15_PMIC_IRQ_OCP_SR3M_INT5,
	S2MPU15_PMIC_IRQ_OCP_SR4M_INT5,
	S2MPU15_PMIC_IRQ_PARITY_ERR0_INT5,
	S2MPU15_PMIC_IRQ_PARITY_ERR1_INT5,
	S2MPU15_PMIC_IRQ_PARITY_ERR2_INT5,

	S2MPU15_PMIC_IRQ_OI_B1M_INT6,
	S2MPU15_PMIC_IRQ_OI_B2M_INT6,
	S2MPU15_PMIC_IRQ_OI_B3M_INT6,
	S2MPU15_PMIC_IRQ_OI_B4M_INT6,
	S2MPU15_PMIC_IRQ_OI_B5M_INT6,
	S2MPU15_PMIC_IRQ_OI_B6M_INT6,
	S2MPU15_PMIC_IRQ_OI_B7M_INT6,
	S2MPU15_PMIC_IRQ_OI_B8M_INT6,

	S2MPU15_PMIC_IRQ_OI_SR1M_INT7,
	S2MPU15_PMIC_IRQ_OI_SR2M_INT7,
	S2MPU15_PMIC_IRQ_OI_SR3M_INT7,
	S2MPU15_PMIC_IRQ_OI_SR4M_INT7,
	S2MPU15_PMIC_IRQ_WDT_INT7,
	S2MPU15_PMIC_IRQ_PARITY_ERR3_INT7,

	S2MPU15_PMIC_IRQ_OI_L10M_INT8,
	S2MPU15_PMIC_IRQ_OI_L11M_INT8,
	S2MPU15_PMIC_IRQ_OI_L29M_INT8,
	S2MPU15_PMIC_IRQ_OI_L30M_INT8,
	S2MPU15_PMIC_IRQ_OI_L31M_INT8,

	S2MPU15_IRQ_NR,
};

enum sec_device_type {
	S2MPU15X,
};

struct s2mpu15_dev {
	struct device *dev;
	struct s2mpu15_platform_data *pdata;
	struct i2c_client *i2c;
	struct i2c_client *vgpio;
	struct i2c_client *pmic1;
	struct i2c_client *pmic2;
	struct i2c_client *rtc;
	struct i2c_client *close1;
	struct i2c_client *close2;
	struct i2c_client *adc_i2c;
	struct i2c_client *gpio;
	struct mutex i2c_lock;
	struct mutex irqlock;
	struct apm_ops *ops;

	bool wakeup;
	int type;
	int device_type;

	/* IRQ */
	int irq;
	int irq_base;
	int irq_masks_cur[S2MPU15_IRQ_GROUP_NR];
	int irq_masks_cache[S2MPU15_IRQ_GROUP_NR];

	/* pmic VER/REV register */
	uint8_t pmic_rev;

	/* VGPIO_RX_MONITOR */
	void __iomem *mem_base;

	/* VGPIO_SYSREG */
	void __iomem *sysreg_vgpio2ap;
	void __iomem *sysreg_vgpio2pmu;

	/* Work queue */
	struct workqueue_struct *irq_wqueue;
	struct delayed_work irq_work;
};

enum s2mpu15_types {
	TYPE_S2MPU15,
};

extern int s2mpu15_irq_init(struct s2mpu15_dev *s2mpu15);
extern void s2mpu15_irq_exit(struct s2mpu15_dev *s2mpu15);

/* S2MPU15 shared i2c API function */
extern int s2mpu15_read_reg(struct i2c_client *i2c, uint8_t reg, uint8_t *dest);
extern int s2mpu15_bulk_read(struct i2c_client *i2c, uint8_t reg, int count, uint8_t *buf);
extern int s2mpu15_write_reg(struct i2c_client *i2c, uint8_t reg, uint8_t value);
extern int s2mpu15_bulk_write(struct i2c_client *i2c, uint8_t reg, int count, uint8_t *buf);
extern int s2mpu15_write_word(struct i2c_client *i2c, uint8_t reg, uint16_t value);
extern int s2mpu15_read_word(struct i2c_client *i2c, uint8_t reg);
extern int s2mpu15_update_reg(struct i2c_client *i2c, uint8_t reg, uint8_t val, uint8_t mask);

extern int pmic_read_pwrkey_status(void);
extern int pmic_read_vol_dn_key_status(void);
extern int main_pmic_read_reg(struct i2c_client *i2c, uint8_t reg, uint8_t *val);
extern int main_pmic_update_reg(struct i2c_client *i2c, u8 reg, u8 val, u8 mask);
extern int main_pmic_get_i2c(struct i2c_client **i2c);
#if IS_ENABLED(CONFIG_MFD_S2MPU16_8835)
extern void s2mpu16_call_notifier(void);
#endif
#endif /* __LINUX_MFD_S2MPU15_REGULATOR_H */
