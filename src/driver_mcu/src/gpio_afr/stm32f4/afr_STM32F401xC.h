#ifndef AFR_STM32F401XC_H_included
#define AFR_STM32F401XC_H_included

//PA0
#define AFR_PA0_TIM2_CH1   AFR_1
#define AFR_PA0_TIM2_ETR   AFR_1
#define AFR_PA0_TIM5_CH1   AFR_2
#define AFR_PA0_USART2_CTS AFR_7

//PA1
#define AFR_PA1_TIM2_CH2   AFR_1
#define AFR_PA1_TIM5_CH2   AFR_2
#define AFR_PA1_USART2_RTS AFR_7

//PA10
#define AFR_PA10_TIM1_CH3      AFR_1
#define AFR_PA10_USART1_RX     AFR_7
#define AFR_PA10_USB_OTG_FS_ID AFR_10

//PA11
#define AFR_PA11_TIM1_CH4      AFR_1
#define AFR_PA11_USART1_CTS    AFR_7
#define AFR_PA11_USART6_TX     AFR_8
#define AFR_PA11_USB_OTG_FS_DM AFR_10

//PA12
#define AFR_PA12_TIM1_ETR      AFR_1
#define AFR_PA12_USART1_RTS    AFR_7
#define AFR_PA12_USART6_RX     AFR_8
#define AFR_PA12_USB_OTG_FS_DP AFR_10

//PA13
#define AFR_PA13_SYS_JTMS_SWDIO AFR_0

//PA14
#define AFR_PA14_I2S3ext_WS     AFR_5
#define AFR_PA14_SYS_JTCK_SWCLK AFR_0

//PA15
#define AFR_PA15_I2S3_WS  AFR_6
#define AFR_PA15_SPI1_NSS AFR_5
#define AFR_PA15_SPI3_NSS AFR_6
#define AFR_PA15_SYS_JTDI AFR_0
#define AFR_PA15_TIM2_CH1 AFR_1
#define AFR_PA15_TIM2_ETR AFR_1

//PA2
#define AFR_PA2_TIM2_CH3  AFR_1
#define AFR_PA2_TIM5_CH3  AFR_2
#define AFR_PA2_TIM9_CH1  AFR_3
#define AFR_PA2_USART2_TX AFR_7

//PA3
#define AFR_PA3_TIM2_CH4  AFR_1
#define AFR_PA3_TIM5_CH4  AFR_2
#define AFR_PA3_TIM9_CH2  AFR_3
#define AFR_PA3_USART2_RX AFR_7

//PA4
#define AFR_PA4_I2S3_WS   AFR_6
#define AFR_PA4_SPI1_NSS  AFR_5
#define AFR_PA4_SPI3_NSS  AFR_6
#define AFR_PA4_USART2_CK AFR_7

//PA5
#define AFR_PA5_SPI1_SCK AFR_5
#define AFR_PA5_TIM2_CH1 AFR_1
#define AFR_PA5_TIM2_ETR AFR_1

//PA6
#define AFR_PA6_SPI1_MISO AFR_5
#define AFR_PA6_TIM1_BKIN AFR_1
#define AFR_PA6_TIM3_CH1  AFR_2

//PA7
#define AFR_PA7_SPI1_MOSI AFR_5
#define AFR_PA7_TIM1_CH1N AFR_1
#define AFR_PA7_TIM3_CH2  AFR_2

//PA8
#define AFR_PA8_I2C3_SCL       AFR_4
#define AFR_PA8_RCC_MCO_1      AFR_0
#define AFR_PA8_TIM1_CH1       AFR_1
#define AFR_PA8_USART1_CK      AFR_7
#define AFR_PA8_USB_OTG_FS_SOF AFR_10

//PA9
#define AFR_PA9_I2C3_SMBA AFR_4
#define AFR_PA9_TIM1_CH2  AFR_1
#define AFR_PA9_USART1_TX AFR_7

//PB0
#define AFR_PB0_TIM1_CH2N AFR_1
#define AFR_PB0_TIM3_CH3  AFR_2

//PB1
#define AFR_PB1_TIM1_CH3N AFR_1
#define AFR_PB1_TIM3_CH4  AFR_2

//PB10
#define AFR_PB10_I2C2_SCL AFR_4
#define AFR_PB10_I2S2_CK  AFR_5
#define AFR_PB10_SPI2_SCK AFR_5
#define AFR_PB10_TIM2_CH3 AFR_1

//PB11
#define AFR_PB11_I2C2_SDA AFR_4
#define AFR_PB11_TIM2_CH4 AFR_1

//PB12
#define AFR_PB12_I2C2_SMBA  AFR_4
#define AFR_PB12_I2S2_WS    AFR_5
#define AFR_PB12_I2S2ext_WS AFR_6
#define AFR_PB12_SPI2_NSS   AFR_5
#define AFR_PB12_TIM1_BKIN  AFR_1

//PB13
#define AFR_PB13_I2S2_CK    AFR_5
#define AFR_PB13_I2S2ext_CK AFR_6
#define AFR_PB13_SPI2_SCK   AFR_5
#define AFR_PB13_TIM1_CH1N  AFR_1

//PB14
#define AFR_PB14_I2S2_ext_SD AFR_6
#define AFR_PB14_SPI2_MISO   AFR_5
#define AFR_PB14_TIM1_CH2N   AFR_1

//PB15
#define AFR_PB15_I2S2_SD      AFR_5
#define AFR_PB15_I2S2ext_MISO AFR_6
#define AFR_PB15_RTC_REFIN    AFR_0
#define AFR_PB15_SPI2_MOSI    AFR_5
#define AFR_PB15_TIM1_CH3N    AFR_1

//PB3
#define AFR_PB3_I2C2_SDA     AFR_9
#define AFR_PB3_I2S3_CK      AFR_6
#define AFR_PB3_SPI1_SCK     AFR_5
#define AFR_PB3_SPI3_SCK     AFR_6
#define AFR_PB3_SYS_JTDO_SWO AFR_0
#define AFR_PB3_TIM2_CH2     AFR_1

//PB4
#define AFR_PB4_I2C3_SDA    AFR_9
#define AFR_PB4_I2S3_ext_SD AFR_7
#define AFR_PB4_SPI1_MISO   AFR_5
#define AFR_PB4_SPI3_MISO   AFR_6
#define AFR_PB4_SYS_JTRST   AFR_0
#define AFR_PB4_TIM3_CH1    AFR_2

//PB5
#define AFR_PB5_I2C1_SMBA AFR_4
#define AFR_PB5_I2S3_SD   AFR_6
#define AFR_PB5_SPI1_MOSI AFR_5
#define AFR_PB5_SPI3_MOSI AFR_6
#define AFR_PB5_TIM3_CH2  AFR_2

//PB6
#define AFR_PB6_I2C1_SCL  AFR_4
#define AFR_PB6_TIM4_CH1  AFR_2
#define AFR_PB6_USART1_TX AFR_7

//PB7
#define AFR_PB7_I2C1_SDA  AFR_4
#define AFR_PB7_TIM4_CH2  AFR_2
#define AFR_PB7_USART1_RX AFR_7

//PB8
#define AFR_PB8_I2C1_SCL  AFR_4
#define AFR_PB8_SDIO_D4   AFR_12
#define AFR_PB8_TIM10_CH1 AFR_3
#define AFR_PB8_TIM4_CH3  AFR_2

//PB9
#define AFR_PB9_I2C1_SDA  AFR_4
#define AFR_PB9_I2S2_WS   AFR_5
#define AFR_PB9_SDIO_D5   AFR_12
#define AFR_PB9_SPI2_NSS  AFR_5
#define AFR_PB9_TIM11_CH1 AFR_3
#define AFR_PB9_TIM4_CH4  AFR_2

//PC10
#define AFR_PC10_I2S3_CK    AFR_6
#define AFR_PC10_I2S3ext_CK AFR_5
#define AFR_PC10_SDIO_D2    AFR_12
#define AFR_PC10_SPI3_SCK   AFR_6

//PC11
#define AFR_PC11_I2S3_ext_SD AFR_5
#define AFR_PC11_SDIO_D3     AFR_12
#define AFR_PC11_SPI3_MISO   AFR_6

//PC12
#define AFR_PC12_I2S3_SD      AFR_6
#define AFR_PC12_I2S3ext_MISO AFR_5
#define AFR_PC12_SDIO_CK      AFR_12
#define AFR_PC12_SPI3_MOSI    AFR_6

//PC2
#define AFR_PC2_I2S2_ext_SD AFR_6
#define AFR_PC2_SPI2_MISO   AFR_5

//PC3
#define AFR_PC3_I2S2_SD   AFR_5
#define AFR_PC3_SPI2_MOSI AFR_5

//PC6
#define AFR_PC6_I2S2_MCK  AFR_5
#define AFR_PC6_SDIO_D6   AFR_12
#define AFR_PC6_TIM3_CH1  AFR_2
#define AFR_PC6_USART6_TX AFR_8

//PC7
#define AFR_PC7_I2S3_MCK  AFR_6
#define AFR_PC7_SDIO_D7   AFR_12
#define AFR_PC7_TIM3_CH2  AFR_2
#define AFR_PC7_USART6_RX AFR_8

//PC8
#define AFR_PC8_SDIO_D0   AFR_12
#define AFR_PC8_TIM3_CH3  AFR_2
#define AFR_PC8_USART6_CK AFR_8

//PC9
#define AFR_PC9_I2C3_SDA  AFR_4
#define AFR_PC9_I2S_CKIN  AFR_5
#define AFR_PC9_RCC_MCO_2 AFR_0
#define AFR_PC9_SDIO_D1   AFR_12
#define AFR_PC9_TIM3_CH4  AFR_2

//PD12
#define AFR_PD12_TIM4_CH1 AFR_2

//PD13
#define AFR_PD13_TIM4_CH2 AFR_2

//PD14
#define AFR_PD14_TIM4_CH3 AFR_2

//PD15
#define AFR_PD15_TIM4_CH4 AFR_2

//PD2
#define AFR_PD2_SDIO_CMD AFR_12
#define AFR_PD2_TIM3_ETR AFR_2

//PD3
#define AFR_PD3_I2S2_CK    AFR_5
#define AFR_PD3_SPI2_SCK   AFR_5
#define AFR_PD3_USART2_CTS AFR_7

//PD4
#define AFR_PD4_USART2_RTS AFR_7

//PD5
#define AFR_PD5_USART2_TX AFR_7

//PD6
#define AFR_PD6_I2S3_SD   AFR_5
#define AFR_PD6_SPI3_MOSI AFR_5
#define AFR_PD6_USART2_RX AFR_7

//PD7
#define AFR_PD7_USART2_CK AFR_7

//PE0
#define AFR_PE0_TIM4_ETR AFR_2

//PE10
#define AFR_PE10_TIM1_CH2N AFR_1

//PE11
#define AFR_PE11_SPI4_NSS AFR_5
#define AFR_PE11_TIM1_CH2 AFR_1

//PE12
#define AFR_PE12_SPI4_SCK  AFR_5
#define AFR_PE12_TIM1_CH3N AFR_1

//PE13
#define AFR_PE13_SPI4_MISO AFR_5
#define AFR_PE13_TIM1_CH3  AFR_1

//PE14
#define AFR_PE14_SPI4_MOSI AFR_5
#define AFR_PE14_TIM1_CH4  AFR_1

//PE15
#define AFR_PE15_TIM1_BKIN AFR_1

//PE2
#define AFR_PE2_SPI4_SCK     AFR_5
#define AFR_PE2_SYS_TRACECLK AFR_0

//PE3
#define AFR_PE3_SYS_TRACED0 AFR_0

//PE4
#define AFR_PE4_SPI4_NSS    AFR_5
#define AFR_PE4_SYS_TRACED1 AFR_0

//PE5
#define AFR_PE5_SPI4_MISO   AFR_5
#define AFR_PE5_SYS_TRACED2 AFR_0
#define AFR_PE5_TIM9_CH1    AFR_3

//PE6
#define AFR_PE6_SPI4_MOSI   AFR_5
#define AFR_PE6_SYS_TRACED3 AFR_0
#define AFR_PE6_TIM9_CH2    AFR_3

//PE7
#define AFR_PE7_TIM1_ETR AFR_1

//PE8
#define AFR_PE8_TIM1_CH1N AFR_1

//PE9
#define AFR_PE9_TIM1_CH1 AFR_1

#endif
