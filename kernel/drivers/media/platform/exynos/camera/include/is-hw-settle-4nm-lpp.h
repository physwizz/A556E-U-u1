// SPDX-License-Identifier: GPL-2.0
/*
 * Samsung Exynos SoC series Pablo driver
 *
 * Copyright (c) 2023 Samsung Electronics Co., Ltd
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

const u32 is_csi_settle_table[] = {
	6500,		37,
	6490,		37,
	6480,		37,
	6470,		37,
	6460,		37,
	6450,		37,
	6440,		36,
	6430,		36,
	6420,		36,
	6410,		36,
	6400,		36,
	6390,		36,
	6380,		36,
	6370,		36,
	6360,		36,
	6350,		36,
	6340,		36,
	6330,		36,
	6320,		36,
	6310,		36,
	6300,		36,
	6290,		36,
	6280,		36,
	6270,		35,
	6260,		35,
	6250,		35,
	6240,		35,
	6230,		35,
	6220,		35,
	6210,		35,
	6200,		35,
	6190,		35,
	6180,		35,
	6170,		35,
	6160,		35,
	6150,		35,
	6140,		35,
	6130,		35,
	6120,		35,
	6110,		34,
	6100,		34,
	6090,		34,
	6080,		34,
	6070,		34,
	6060,		34,
	6050,		34,
	6040,		34,
	6030,		34,
	6020,		34,
	6010,		34,
	6000,		34,
	5990,		34,
	5980,		34,
	5970,		34,
	5960,		34,
	5950,		34,
	5940,		33,
	5930,		33,
	5920,		33,
	5910,		33,
	5900,		33,
	5890,		33,
	5880,		33,
	5870,		33,
	5860,		33,
	5850,		33,
	5840,		33,
	5830,		33,
	5820,		33,
	5810,		33,
	5800,		33,
	5790,		33,
	5780,		33,
	5770,		32,
	5760,		32,
	5750,		32,
	5740,		32,
	5730,		32,
	5720,		32,
	5710,		32,
	5700,		32,
	5690,		32,
	5680,		32,
	5670,		32,
	5660,		32,
	5650,		32,
	5640,		32,
	5630,		32,
	5620,		32,
	5610,		32,
	5600,		31,
	5590,		31,
	5580,		31,
	5570,		31,
	5560,		31,
	5550,		31,
	5540,		31,
	5530,		31,
	5520,		31,
	5510,		31,
	5500,		31,
	5490,		31,
	5480,		31,
	5470,		31,
	5460,		31,
	5450,		31,
	5440,		30,
	5430,		30,
	5420,		30,
	5410,		30,
	5400,		30,
	5390,		30,
	5380,		30,
	5370,		30,
	5360,		30,
	5350,		30,
	5340,		30,
	5330,		30,
	5320,		30,
	5310,		30,
	5300,		30,
	5290,		30,
	5280,		30,
	5270,		29,
	5260,		29,
	5250,		29,
	5240,		29,
	5230,		29,
	5220,		29,
	5210,		29,
	5200,		29,
	5190,		29,
	5180,		29,
	5170,		29,
	5160,		29,
	5150,		29,
	5140,		29,
	5130,		29,
	5120,		29,
	5110,		29,
	5100,		28,
	5090,		28,
	5080,		28,
	5070,		28,
	5060,		28,
	5050,		28,
	5040,		28,
	5030,		28,
	5020,		28,
	5010,		28,
	5000,		28,
	4990,		28,
	4980,		28,
	4970,		28,
	4960,		28,
	4950,		28,
	4940,		28,
	4930,		27,
	4920,		27,
	4910,		27,
	4900,		27,
	4890,		27,
	4880,		27,
	4870,		27,
	4860,		27,
	4850,		27,
	4840,		27,
	4830,		27,
	4820,		27,
	4810,		27,
	4800,		27,
	4790,		27,
	4780,		27,
	4770,		26,
	4760,		26,
	4750,		26,
	4740,		26,
	4730,		26,
	4720,		26,
	4710,		26,
	4700,		26,
	4690,		26,
	4680,		26,
	4670,		26,
	4660,		26,
	4650,		26,
	4640,		26,
	4630,		26,
	4620,		26,
	4610,		26,
	4600,		25,
	4590,		25,
	4580,		25,
	4570,		25,
	4560,		25,
	4550,		25,
	4540,		25,
	4530,		25,
	4520,		25,
	4510,		25,
	4500,		25,
	4490,		25,
	4480,		25,
	4470,		25,
	4460,		25,
	4450,		25,
	4440,		25,
	4430,		24,
	4420,		24,
	4410,		24,
	4400,		24,
	4390,		24,
	4380,		24,
	4370,		24,
	4360,		24,
	4350,		24,
	4340,		24,
	4330,		24,
	4320,		24,
	4310,		24,
	4300,		24,
	4290,		24,
	4280,		24,
	4270,		23,
	4260,		23,
	4250,		23,
	4240,		23,
	4230,		23,
	4220,		23,
	4210,		23,
	4200,		23,
	4190,		23,
	4180,		23,
	4170,		23,
	4160,		23,
	4150,		23,
	4140,		23,
	4130,		23,
	4120,		23,
	4110,		23,
	4100,		22,
	4090,		22,
	4080,		22,
	4070,		22,
	4060,		22,
	4050,		22,
	4040,		22,
	4030,		22,
	4020,		22,
	4010,		22,
	4000,		22,
	3990,		22,
	3980,		22,
	3970,		22,
	3960,		22,
	3950,		22,
	3940,		22,
	3930,		21,
	3920,		21,
	3910,		21,
	3900,		21,
	3890,		21,
	3880,		21,
	3870,		21,
	3860,		21,
	3850,		21,
	3840,		21,
	3830,		21,
	3820,		21,
	3810,		21,
	3800,		21,
	3790,		21,
	3780,		21,
	3770,		21,
	3760,		20,
	3750,		20,
	3740,		20,
	3730,		20,
	3720,		20,
	3710,		20,
	3700,		20,
	3690,		20,
	3680,		20,
	3670,		20,
	3660,		20,
	3650,		20,
	3640,		20,
	3630,		20,
	3620,		20,
	3610,		20,
	3600,		19,
	3590,		19,
	3580,		19,
	3570,		19,
	3560,		19,
	3550,		19,
	3540,		19,
	3530,		19,
	3520,		19,
	3510,		19,
	3500,		19,
	3490,		19,
	3480,		19,
	3470,		19,
	3460,		19,
	3450,		19,
	3440,		19,
	3430,		18,
	3420,		18,
	3410,		18,
	3400,		18,
	3390,		18,
	3380,		18,
	3370,		18,
	3360,		18,
	3350,		18,
	3340,		18,
	3330,		18,
	3320,		18,
	3310,		18,
	3300,		18,
	3290,		18,
	3280,		18,
	3270,		18,
	3260,		17,
	3250,		17,
	3240,		17,
	3230,		17,
	3220,		17,
	3210,		17,
	3200,		17,
	3190,		17,
	3180,		17,
	3170,		17,
	3160,		17,
	3150,		17,
	3140,		17,
	3130,		17,
	3120,		17,
	3110,		17,
	3100,		17,
	3090,		16,
	3080,		16,
	3070,		16,
	3060,		16,
	3050,		16,
	3040,		16,
	3030,		16,
	3020,		16,
	3010,		16,
	3000,		16,
	2990,		16,
	2980,		16,
	2970,		16,
	2960,		16,
	2950,		16,
	2940,		16,
	2930,		15,
	2920,		15,
	2910,		15,
	2900,		15,
	2890,		15,
	2880,		15,
	2870,		15,
	2860,		15,
	2850,		15,
	2840,		15,
	2830,		15,
	2820,		15,
	2810,		15,
	2800,		15,
	2790,		15,
	2780,		15,
	2770,		15,
	2760,		14,
	2750,		14,
	2740,		14,
	2730,		14,
	2720,		14,
	2710,		14,
	2700,		14,
	2690,		14,
	2680,		14,
	2670,		14,
	2660,		14,
	2650,		14,
	2640,		14,
	2630,		14,
	2620,		14,
	2610,		14,
	2600,		14,
	2590,		13,
	2580,		13,
	2570,		13,
	2560,		13,
	2550,		13,
	2540,		13,
	2530,		13,
	2520,		13,
	2510,		13,
	2500,		13,
	2490,		13,
	2480,		13,
	2470,		13,
	2460,		13,
	2450,		13,
	2440,		13,
	2430,		13,
	2420,		12,
	2410,		12,
	2400,		12,
	2390,		12,
	2380,		12,
	2370,		12,
	2360,		12,
	2350,		12,
	2340,		12,
	2330,		12,
	2320,		12,
	2310,		12,
	2300,		12,
	2290,		12,
	2280,		12,
	2270,		12,
	2260,		11,
	2250,		11,
	2240,		11,
	2230,		11,
	2220,		11,
	2210,		11,
	2200,		11,
	2190,		11,
	2180,		11,
	2170,		11,
	2160,		11,
	2150,		11,
	2140,		11,
	2130,		11,
	2120,		11,
	2110,		11,
	2100,		11,
	2090,		10,
	2080,		10,
	2070,		10,
	2060,		10,
	2050,		10,
	2040,		10,
	2030,		10,
	2020,		10,
	2010,		10,
	2000,		10,
	1990,		10,
	1980,		10,
	1970,		10,
	1960,		10,
	1950,		10,
	1940,		10,
	1930,		10,
	1920,		9,
	1910,		9,
	1900,		9,
	1890,		9,
	1880,		9,
	1870,		9,
	1860,		9,
	1850,		9,
	1840,		9,
	1830,		9,
	1820,		9,
	1810,		9,
	1800,		9,
	1790,		9,
	1780,		9,
	1770,		9,
	1760,		9,
	1750,		8,
	1740,		8,
	1730,		8,
	1720,		8,
	1710,		8,
	1700,		8,
	1690,		8,
	1680,		8,
	1670,		8,
	1660,		8,
	1650,		8,
	1640,		8,
	1630,		8,
	1620,		8,
	1610,		8,
	1600,		8,
	1590,		7,
	1580,		7,
	1570,		7,
	1560,		7,
	1550,		7,
	1540,		7,
	1530,		7,
	1520,		7,
	1510,		7,
	1500,		7,
	1490,		73,
	1480,		72,
	1470,		72,
	1460,		71,
	1450,		71,
	1440,		70,
	1430,		70,
	1420,		69,
	1410,		69,
	1400,		68,
	1390,		68,
	1380,		67,
	1370,		67,
	1360,		66,
	1350,		66,
	1340,		66,
	1330,		65,
	1320,		65,
	1310,		64,
	1300,		64,
	1290,		63,
	1280,		63,
	1270,		62,
	1260,		62,
	1250,		61,
	1240,		61,
	1230,		60,
	1220,		60,
	1210,		59,
	1200,		59,
	1190,		58,
	1180,		58,
	1170,		57,
	1160,		57,
	1150,		56,
	1140,		56,
	1130,		55,
	1120,		55,
	1110,		55,
	1100,		54,
	1090,		54,
	1080,		53,
	1070,		53,
	1060,		52,
	1050,		52,
	1040,		51,
	1030,		51,
	1020,		50,
	1010,		50,
	1000,		49,
	990,		49,
	980,		48,
	970,		48,
	960,		47,
	950,		47,
	940,		46,
	930,		46,
	920,		45,
	910,		45,
	900,		44,
	890,		44,
	880,		44,
	870,		43,
	860,		43,
	850,		42,
	840,		42,
	830,		41,
	820,		41,
	810,		40,
	800,		40,
	790,		39,
	780,		39,
	770,		38,
	760,		38,
	750,		37,
	740,		37,
	730,		36,
	720,		36,
	710,		35,
	700,		35,
	690,		34,
	680,		34,
	670,		34,
	660,		33,
	650,		33,
	640,		32,
	630,		32,
	620,		31,
	610,		31,
	600,		30,
	590,		30,
	580,		29,
	570,		29,
	560,		28,
	550,		28,
	540,		27,
	530,		27,
	520,		26,
	510,		26,
	500,		25,
	490,		25,
	480,		24,
	470,		24,
	460,		23,
	450,		23,
	440,		23,
	430,		22,
	420,		22,
	410,		21,
	400,		21,
	390,		20,
	380,		20,
	370,		19,
	360,		19,
	350,		18,
	340,		18,
	330,		17,
	320,		17,
	310,		16,
	300,		16,
	290,		15,
	280,		15,
	270,		14,
	260,		14,
	250,		13,
	240,		13,
	230,		12,
	220,		12,
	210,		12,
	200,		11,
	190,		11,
	180,		10,
	170,		10,
	160,		9,
	150,		9,
	140,		8,
	130,		8,
	120,		7,
	110,		7,
	100,		6,
	90,		6,
	80,		5,
};

const u32 is_csi_settle_table_cphy[] = {
	6000,		9,
	5990,		9,
	5980,		9,
	5970,		9,
	5960,		9,
	5950,		9,
	5940,		9,
	5930,		9,
	5920,		9,
	5910,		9,
	5900,		9,
	5890,		9,
	5880,		9,
	5870,		9,
	5860,		9,
	5850,		9,
	5840,		9,
	5830,		9,
	5820,		9,
	5810,		9,
	5800,		9,
	5790,		9,
	5780,		9,
	5770,		9,
	5760,		9,
	5750,		9,
	5740,		9,
	5730,		9,
	5720,		9,
	5710,		9,
	5700,		9,
	5690,		9,
	5680,		9,
	5670,		9,
	5660,		9,
	5650,		9,
	5640,		9,
	5630,		9,
	5620,		9,
	5610,		9,
	5600,		9,
	5590,		9,
	5580,		9,
	5570,		9,
	5560,		9,
	5550,		9,
	5540,		9,
	5530,		9,
	5520,		9,
	5510,		9,
	5500,		9,
	5490,		9,
	5480,		9,
	5470,		9,
	5460,		9,
	5450,		9,
	5440,		9,
	5430,		9,
	5420,		9,
	5410,		9,
	5400,		9,
	5390,		9,
	5380,		9,
	5370,		9,
	5360,		9,
	5350,		9,
	5340,		9,
	5330,		9,
	5320,		9,
	5310,		9,
	5300,		9,
	5290,		9,
	5280,		9,
	5270,		9,
	5260,		9,
	5250,		9,
	5240,		9,
	5230,		9,
	5220,		9,
	5210,		9,
	5200,		9,
	5190,		9,
	5180,		9,
	5170,		9,
	5160,		9,
	5150,		9,
	5140,		9,
	5130,		9,
	5120,		9,
	5110,		9,
	5100,		9,
	5090,		9,
	5080,		9,
	5070,		9,
	5060,		9,
	5050,		9,
	5040,		9,
	5030,		9,
	5020,		9,
	5010,		9,
	5000,		9,
	4990,		9,
	4980,		9,
	4970,		9,
	4960,		9,
	4950,		9,
	4940,		9,
	4930,		9,
	4920,		9,
	4910,		9,
	4900,		9,
	4890,		9,
	4880,		9,
	4870,		9,
	4860,		9,
	4850,		9,
	4840,		9,
	4830,		9,
	4820,		9,
	4810,		9,
	4800,		9,
	4790,		9,
	4780,		9,
	4770,		9,
	4760,		9,
	4750,		9,
	4740,		9,
	4730,		9,
	4720,		9,
	4710,		9,
	4700,		9,
	4690,		9,
	4680,		9,
	4670,		9,
	4660,		9,
	4650,		9,
	4640,		9,
	4630,		9,
	4620,		9,
	4610,		9,
	4600,		9,
	4590,		9,
	4580,		9,
	4570,		9,
	4560,		9,
	4550,		9,
	4540,		9,
	4530,		9,
	4520,		9,
	4510,		9,
	4500,		9,
	4490,		9,
	4480,		9,
	4470,		9,
	4460,		9,
	4450,		9,
	4440,		9,
	4430,		9,
	4420,		9,
	4410,		9,
	4400,		9,
	4390,		9,
	4380,		9,
	4370,		9,
	4360,		9,
	4350,		9,
	4340,		9,
	4330,		9,
	4320,		9,
	4310,		9,
	4300,		9,
	4290,		9,
	4280,		9,
	4270,		9,
	4260,		9,
	4250,		9,
	4240,		9,
	4230,		9,
	4220,		9,
	4210,		9,
	4200,		9,
	4190,		9,
	4180,		9,
	4170,		9,
	4160,		9,
	4150,		9,
	4140,		9,
	4130,		9,
	4120,		9,
	4110,		9,
	4100,		9,
	4090,		9,
	4080,		9,
	4070,		9,
	4060,		9,
	4050,		9,
	4040,		9,
	4030,		9,
	4020,		9,
	4010,		9,
	4000,		9,
	3990,		9,
	3980,		9,
	3970,		9,
	3960,		9,
	3950,		9,
	3940,		9,
	3930,		9,
	3920,		9,
	3910,		9,
	3900,		9,
	3890,		9,
	3880,		9,
	3870,		9,
	3860,		9,
	3850,		9,
	3840,		9,
	3830,		9,
	3820,		9,
	3810,		9,
	3800,		9,
	3790,		9,
	3780,		9,
	3770,		9,
	3760,		9,
	3750,		9,
	3740,		9,
	3730,		9,
	3720,		9,
	3710,		9,
	3700,		9,
	3690,		9,
	3680,		9,
	3670,		9,
	3660,		9,
	3650,		9,
	3640,		9,
	3630,		9,
	3620,		9,
	3610,		9,
	3600,		9,
	3590,		9,
	3580,		9,
	3570,		9,
	3560,		9,
	3550,		9,
	3540,		9,
	3530,		9,
	3520,		9,
	3510,		9,
	3500,		9,
	3490,		9,
	3480,		9,
	3470,		9,
	3460,		9,
	3450,		9,
	3440,		9,
	3430,		9,
	3420,		9,
	3410,		9,
	3400,		9,
	3390,		9,
	3380,		9,
	3370,		9,
	3360,		9,
	3350,		9,
	3340,		9,
	3330,		9,
	3320,		9,
	3310,		9,
	3300,		9,
	3290,		9,
	3280,		9,
	3270,		9,
	3260,		9,
	3250,		9,
	3240,		9,
	3230,		9,
	3220,		9,
	3210,		9,
	3200,		9,
	3190,		9,
	3180,		9,
	3170,		9,
	3160,		9,
	3150,		9,
	3140,		9,
	3130,		9,
	3120,		9,
	3110,		9,
	3100,		9,
	3090,		9,
	3080,		9,
	3070,		9,
	3060,		9,
	3050,		9,
	3040,		9,
	3030,		9,
	3020,		9,
	3010,		9,
	3000,		9,
	2990,		9,
	2980,		9,
	2970,		9,
	2960,		9,
	2950,		9,
	2940,		9,
	2930,		9,
	2920,		9,
	2910,		9,
	2900,		9,
	2890,		9,
	2880,		9,
	2870,		9,
	2860,		9,
	2850,		9,
	2840,		9,
	2830,		9,
	2820,		9,
	2810,		9,
	2800,		9,
	2790,		9,
	2780,		9,
	2770,		9,
	2760,		9,
	2750,		9,
	2740,		9,
	2730,		9,
	2720,		9,
	2710,		9,
	2700,		9,
	2690,		9,
	2680,		9,
	2670,		9,
	2660,		9,
	2650,		9,
	2640,		9,
	2630,		9,
	2620,		9,
	2610,		9,
	2600,		9,
	2590,		9,
	2580,		9,
	2570,		9,
	2560,		9,
	2550,		9,
	2540,		9,
	2530,		9,
	2520,		9,
	2510,		9,
	2500,		9,
	2490,		9,
	2480,		9,
	2470,		9,
	2460,		9,
	2450,		9,
	2440,		9,
	2430,		9,
	2420,		9,
	2410,		9,
	2400,		9,
	2390,		9,
	2380,		9,
	2370,		9,
	2360,		9,
	2350,		9,
	2340,		9,
	2330,		9,
	2320,		9,
	2310,		9,
	2300,		9,
	2290,		9,
	2280,		9,
	2270,		9,
	2260,		9,
	2250,		9,
	2240,		9,
	2230,		9,
	2220,		9,
	2210,		9,
	2200,		9,
	2190,		9,
	2180,		9,
	2170,		9,
	2160,		9,
	2150,		9,
	2140,		9,
	2130,		9,
	2120,		9,
	2110,		9,
	2100,		9,
	2090,		9,
	2080,		9,
	2070,		9,
	2060,		9,
	2050,		9,
	2040,		9,
	2030,		9,
	2020,		9,
	2010,		9,
	2000,		9,
	1990,		9,
	1980,		9,
	1970,		9,
	1960,		9,
	1950,		9,
	1940,		9,
	1930,		9,
	1920,		9,
	1910,		9,
	1900,		9,
	1890,		9,
	1880,		9,
	1870,		9,
	1860,		9,
	1850,		9,
	1840,		9,
	1830,		9,
	1820,		9,
	1810,		9,
	1800,		9,
	1790,		9,
	1780,		9,
	1770,		9,
	1760,		9,
	1750,		9,
	1740,		9,
	1730,		9,
	1720,		9,
	1710,		9,
	1700,		9,
	1690,		9,
	1680,		9,
	1670,		9,
	1660,		9,
	1650,		9,
	1640,		9,
	1630,		9,
	1620,		9,
	1610,		9,
	1600,		9,
	1590,		9,
	1580,		9,
	1570,		9,
	1560,		9,
	1550,		9,
	1540,		9,
	1530,		9,
	1520,		9,
	1510,		9,
	1500,		9,
	1490,		10,
	1480,		10,
	1470,		10,
	1460,		10,
	1450,		10,
	1440,		10,
	1430,		10,
	1420,		10,
	1410,		10,
	1400,		10,
	1390,		10,
	1380,		10,
	1370,		10,
	1360,		10,
	1350,		10,
	1340,		10,
	1330,		10,
	1320,		10,
	1310,		10,
	1300,		10,
	1290,		10,
	1280,		10,
	1270,		10,
	1260,		10,
	1250,		10,
	1240,		10,
	1230,		10,
	1220,		10,
	1210,		10,
	1200,		10,
	1190,		10,
	1180,		10,
	1170,		10,
	1160,		10,
	1150,		10,
	1140,		10,
	1130,		10,
	1120,		10,
	1110,		10,
	1100,		10,
	1090,		10,
	1080,		10,
	1070,		10,
	1060,		10,
	1050,		10,
	1040,		10,
	1030,		10,
	1020,		10,
	1010,		10,
	1000,		10,
	990,		10,
	980,		10,
	970,		10,
	960,		10,
	950,		10,
	940,		10,
	930,		10,
	920,		10,
	910,		10,
	900,		10,
	890,		10,
	880,		10,
	870,		10,
	860,		10,
	850,		10,
	840,		10,
	830,		10,
	820,		10,
	810,		10,
	800,		10,
	790,		10,
	780,		10,
	770,		10,
	760,		10,
	750,		10,
	740,		10,
	730,		10,
	720,		10,
	710,		10,
	700,		10,
	690,		10,
	680,		10,
	670,		10,
	660,		10,
	650,		10,
	640,		10,
	630,		10,
	620,		10,
	610,		10,
	600,		10,
	590,		10,
	580,		10,
	570,		10,
	560,		10,
	550,		10,
	540,		10,
	530,		10,
	520,		10,
	510,		10,
	500,		10,
	490,		10,
	480,		10,
	470,		10,
	460,		10,
	450,		10,
	440,		10,
	430,		10,
	420,		10,
	410,		10,
	400,		10,
	390,		10,
	380,		10,
	370,		10,
	360,		10,
	350,		10,
	340,		10,
	330,		10,
	320,		10,
	310,		10,
	300,		10,
	290,		10,
	280,		10,
	270,		10,
	260,		10,
	250,		10,
	240,		10,
	230,		10,
	220,		10,
	210,		10,
	200,		10,
	190,		10,
	180,		10,
	170,		10,
	160,		10,
	150,		10,
	140,		10,
	130,		10,
	120,		10,
	110,		10,
	100,		10,
	90,		10,
	80,		10,
};