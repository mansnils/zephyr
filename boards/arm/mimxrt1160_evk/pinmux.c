/*
 * Copyright (c) 2021, NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <init.h>
#include <fsl_iomuxc.h>
#include <fsl_gpio.h>
#include <soc.h>
#include <logging/log.h>

LOG_MODULE_REGISTER(mimxrt1160_evk, LOG_LEVEL_INF);

#if DT_NODE_HAS_STATUS(DT_NODELABEL(enet), okay) && CONFIG_NET_L2_ETHERNET
static gpio_pin_config_t enet_gpio_config = {
	.direction = kGPIO_DigitalOutput,
	.outputLogic = 0,
	.interruptMode = kGPIO_NoIntmode
};
#endif

static int mimxrt1160_evk_init(const struct device *dev)
{
	ARG_UNUSED(dev);

	CLOCK_EnableClock(kCLOCK_Iomuxc);

	/* Enable USER_LED_CTRL1 */
	IOMUXC_SetPinMux(IOMUXC_GPIO_AD_04_GPIO9_IO03, 0U);

#if DT_NODE_HAS_STATUS(DT_NODELABEL(lpuart1), okay) && CONFIG_SERIAL
	/* LPUART1 TX/RX */
	IOMUXC_SetPinMux(IOMUXC_GPIO_AD_24_LPUART1_TXD, 0U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_AD_25_LPUART1_RXD, 0U);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_24_LPUART1_TXD, 0x02U);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_25_LPUART1_RXD, 0x02U);
#endif

#if DT_NODE_HAS_STATUS(DT_NODELABEL(flexcan3), okay) && CONFIG_CAN
	IOMUXC_SetPinMux(IOMUXC_GPIO_LPSR_00_FLEXCAN3_TX, 1U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_LPSR_01_FLEXCAN3_RX, 1U);

	IOMUXC_SetPinConfig(IOMUXC_GPIO_LPSR_00_FLEXCAN3_TX, 0x02U);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_LPSR_01_FLEXCAN3_RX, 0x02U);
#endif

#if DT_NODE_HAS_STATUS(DT_NODELABEL(lpspi1), okay) && CONFIG_SPI
	/* LPSPI1 SCK, PCS0, SIN, SOUT */
	IOMUXC_SetPinMux(IOMUXC_GPIO_AD_28_LPSPI1_SCK, 0U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_AD_29_LPSPI1_PCS0, 0U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_AD_30_LPSPI1_SOUT, 0U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_AD_31_LPSPI1_SIN, 0U);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_28_LPSPI1_SCK, 0x02U);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_29_LPSPI1_PCS0, 0x02U);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_30_LPSPI1_SOUT, 0x02U);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_31_LPSPI1_SIN, 0x02U);
#endif

#if DT_NODE_HAS_STATUS(DT_NODELABEL(lpi2c1), okay) && CONFIG_I2C
	/* LPI2C1 SDA, SCL */
	IOMUXC_SetPinMux(IOMUXC_GPIO_AD_08_LPI2C1_SCL, 1U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_AD_09_LPI2C1_SDA, 1U);
	/* Open drain, with software input on */
	IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_08_LPI2C1_SCL, 0x10U);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_09_LPI2C1_SDA, 0x10U);
#endif

#if DT_NODE_HAS_STATUS(DT_NODELABEL(lpi2c5), okay) && CONFIG_FXOS8700
#if !defined(CONFIG_FXOS8700_TRIGGER_NONE)
	IOMUXC_SetPinMux(IOMUXC_GPIO_DISP_B2_13_GPIO11_IO14, 0U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_DISP_B2_14_GPIO11_IO15, 0U);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_DISP_B2_13_GPIO11_IO14, 0x02U);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_DISP_B2_14_GPIO11_IO15, 0x02U);
#endif
	/* LPI2C5 SDA, SCL */
	IOMUXC_SetPinMux(IOMUXC_GPIO_LPSR_04_LPI2C5_SDA, 1U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_LPSR_05_LPI2C5_SCL, 1U);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_LPSR_04_LPI2C5_SDA, 0x20U);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_LPSR_05_LPI2C5_SCL, 0x20U);
#endif

#if DT_NODE_HAS_STATUS(DT_NODELABEL(flexpwm1_pwm2), okay) && CONFIG_PWM
	IOMUXC_SetPinMux(IOMUXC_GPIO_AD_04_FLEXPWM1_PWM2_A, 0U);
#endif

#if DT_NODE_HAS_STATUS(DT_NODELABEL(flexspi), okay) && CONFIG_MEMC_MCUX_FLEXSPI
	/* Force input on all FLEXSPI pads */
	IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B2_05_FLEXSPI1_A_DQS, 1U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B2_06_FLEXSPI1_A_SS0_B, 1U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B2_07_FLEXSPI1_A_SCLK, 1U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B2_08_FLEXSPI1_A_DATA00, 1U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B2_09_FLEXSPI1_A_DATA01, 1U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B2_10_FLEXSPI1_A_DATA02, 1U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B2_11_FLEXSPI1_A_DATA03, 1U);
	/* Pull down enabled, normal drive strength */
	IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B2_05_FLEXSPI1_A_DQS, 0x0AU);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B2_06_FLEXSPI1_A_SS0_B, 0x0AU);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B2_07_FLEXSPI1_A_SCLK, 0x0AU);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B2_08_FLEXSPI1_A_DATA00, 0x0AU);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B2_09_FLEXSPI1_A_DATA01, 0x0AU);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B2_10_FLEXSPI1_A_DATA02, 0x0AU);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B2_11_FLEXSPI1_A_DATA03, 0x0AU);
#endif


#if DT_NODE_HAS_STATUS(DT_NODELABEL(enet), okay) && CONFIG_NET_L2_ETHERNET
	IOMUXC_SetPinMux(IOMUXC_GPIO_AD_12_GPIO9_IO11, 0U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_AD_32_ENET_MDC, 0U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_AD_33_ENET_MDIO, 0U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_DISP_B2_02_ENET_TX_DATA00, 0U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_DISP_B2_03_ENET_TX_DATA01, 0U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_DISP_B2_04_ENET_TX_EN, 0U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_DISP_B2_05_ENET_REF_CLK, 1U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_DISP_B2_06_ENET_RX_DATA00, 1U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_DISP_B2_07_ENET_RX_DATA01, 1U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_DISP_B2_08_ENET_RX_EN, 0U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_DISP_B2_09_ENET_RX_ER, 0U);
	IOMUXC_GPR->GPR4 = ((IOMUXC_GPR->GPR4 &
		(~(IOMUXC_GPR_GPR4_ENET_REF_CLK_DIR_MASK))) |
			IOMUXC_GPR_GPR4_ENET_REF_CLK_DIR(0x01U));
	IOMUXC_SetPinMux(IOMUXC_GPIO_LPSR_12_GPIO12_IO12, 0U);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_12_GPIO9_IO11, 0x06U);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_DISP_B2_02_ENET_TX_DATA00, 0x02U);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_DISP_B2_03_ENET_TX_DATA01, 0x02U);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_DISP_B2_04_ENET_TX_EN, 0x02U);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_DISP_B2_05_ENET_REF_CLK, 0x03U);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_DISP_B2_06_ENET_RX_DATA00, 0x06U);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_DISP_B2_07_ENET_RX_DATA01, 0x06U);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_DISP_B2_08_ENET_RX_EN, 0x06U);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_DISP_B2_09_ENET_RX_ER, 0x06U);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_LPSR_12_GPIO12_IO12, 0x0EU);

	/* Initialize ENET_INT GPIO */
	GPIO_PinInit(GPIO9, 11, &enet_gpio_config);
	GPIO_PinInit(GPIO12, 12, &enet_gpio_config);

	/* pull up the ENET_INT before RESET. */
	GPIO_WritePinOutput(GPIO9, 11, 1);
	GPIO_WritePinOutput(GPIO12, 12, 0);

	/* 50M ENET_REF_CLOCK output to PHY and ENET module. */
	IOMUXC_GPR->GPR4 |= 0x3;
#endif

	return 0;
}

#if DT_NODE_HAS_STATUS(DT_NODELABEL(enet), okay) && CONFIG_NET_L2_ETHERNET
static int mimxrt1170_evk_phy_reset(const struct device *dev)
{
	/* RESET PHY chip. */
	k_busy_wait(USEC_PER_MSEC * 10U);
	GPIO_WritePinOutput(GPIO12, 12, 1);

	return 0;
}
#endif

SYS_INIT(mimxrt1160_evk_init, PRE_KERNEL_1, 0);

#if DT_NODE_HAS_STATUS(DT_NODELABEL(enet), okay) && CONFIG_NET_L2_ETHERNET
SYS_INIT(mimxrt1170_evk_phy_reset, POST_KERNEL, CONFIG_PHY_INIT_PRIORITY);
#endif