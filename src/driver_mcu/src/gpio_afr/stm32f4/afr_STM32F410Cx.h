#ifndef AFR_STM32F410CX_H_included
#define AFR_STM32F410CX_H_included

//PA0
#define AFR_PA0_EVENTOUT   AFR_15
#define AFR_PA0_TIM5_CH1   AFR_2
#define AFR_PA0_USART2_CTS AFR_7

//PA1
#define AFR_PA1_EVENTOUT   AFR_15
#define AFR_PA1_TIM5_CH2   AFR_2
#define AFR_PA1_USART2_RTS AFR_7

//PA10
#define AFR_PA10_EVENTOUT  AFR_15
#define AFR_PA10_I2S5_SD   AFR_6
#define AFR_PA10_SPI5_MOSI AFR_6
#define AFR_PA10_TIM1_CH3  AFR_1
#define AFR_PA10_USART1_RX AFR_7

//PA11
#define AFR_PA11_EVENTOUT   AFR_15
#define AFR_PA11_TIM1_CH4   AFR_1
#define AFR_PA11_USART1_CTS AFR_7
#define AFR_PA11_USART6_TX  AFR_8

//PA12
#define AFR_PA12_EVENTOUT   AFR_15
#define AFR_PA12_SPI5_MISO  AFR_6
#define AFR_PA12_TIM1_ETR   AFR_1
#define AFR_PA12_USART1_RTS AFR_7
#define AFR_PA12_USART6_RX  AFR_8

//PA13
#define AFR_PA13_EVENTOUT       AFR_15
#define AFR_PA13_SYS_JTMS_SWDIO AFR_0

//PA14
#define AFR_PA14_EVENTOUT       AFR_15
#define AFR_PA14_SYS_JTCK_SWCLK AFR_0

//PA15
#define AFR_PA15_EVENTOUT  AFR_15
#define AFR_PA15_I2S1_WS   AFR_5
#define AFR_PA15_SPI1_NSS  AFR_5
#define AFR_PA15_SYS_JTDI  AFR_0
#define AFR_PA15_USART1_TX AFR_7

//PA2
#define AFR_PA2_EVENTOUT  AFR_15
#define AFR_PA2_I2S_CKIN  AFR_5
#define AFR_PA2_TIM5_CH3  AFR_2
#define AFR_PA2_TIM9_CH1  AFR_3
#define AFR_PA2_USART2_TX AFR_7

//PA3
#define AFR_PA3_EVENTOUT  AFR_15
#define AFR_PA3_I2S2_MCK  AFR_5
#define AFR_PA3_TIM5_CH4  AFR_2
#define AFR_PA3_TIM9_CH2  AFR_3
#define AFR_PA3_USART2_RX AFR_7

//PA4
#define AFR_PA4_EVENTOUT  AFR_15
#define AFR_PA4_I2S1_WS   AFR_5
#define AFR_PA4_SPI1_NSS  AFR_5
#define AFR_PA4_USART2_CK AFR_7

//PA5
#define AFR_PA5_EVENTOUT AFR_15
#define AFR_PA5_I2S1_CK  AFR_5
#define AFR_PA5_SPI1_SCK AFR_5

//PA6
#define AFR_PA6_EVENTOUT  AFR_15
#define AFR_PA6_I2S2_MCK  AFR_6
#define AFR_PA6_SPI1_MISO AFR_5
#define AFR_PA6_TIM1_BKIN AFR_1

//PA7
#define AFR_PA7_EVENTOUT  AFR_15
#define AFR_PA7_I2S1_SD   AFR_5
#define AFR_PA7_SPI1_MOSI AFR_5
#define AFR_PA7_TIM1_CH1N AFR_1

//PA8
#define AFR_PA8_EVENTOUT    AFR_15
#define AFR_PA8_FMPI2C1_SCL AFR_4
#define AFR_PA8_RCC_MCO_1   AFR_0
#define AFR_PA8_TIM1_CH1    AFR_1
#define AFR_PA8_USART1_CK   AFR_7

//PA9
#define AFR_PA9_EVENTOUT  AFR_15
#define AFR_PA9_TIM1_CH2  AFR_1
#define AFR_PA9_USART1_TX AFR_7

//PB0
#define AFR_PB0_EVENTOUT  AFR_15
#define AFR_PB0_I2S5_CK   AFR_6
#define AFR_PB0_SPI5_SCK  AFR_6
#define AFR_PB0_TIM1_CH2N AFR_1

//PB1
#define AFR_PB1_EVENTOUT  AFR_15
#define AFR_PB1_I2S5_WS   AFR_6
#define AFR_PB1_SPI5_NSS  AFR_6
#define AFR_PB1_TIM1_CH3N AFR_1

//PB10
#define AFR_PB10_EVENTOUT    AFR_15
#define AFR_PB10_FMPI2C1_SCL AFR_9
#define AFR_PB10_I2C2_SCL    AFR_4
#define AFR_PB10_I2S1_MCK    AFR_6
#define AFR_PB10_I2S2_CK     AFR_5
#define AFR_PB10_SPI2_SCK    AFR_5

//PB11
#define AFR_PB11_EVENTOUT    AFR_15
#define AFR_PB11_I2C2_SDA    AFR_4
#define AFR_PB11_I2S_CKIN    AFR_5
#define AFR_PB11_SYS_TRACED3 AFR_0
#define AFR_PB11_TIM5_CH4    AFR_2

//PB12
#define AFR_PB12_EVENTOUT  AFR_15
#define AFR_PB12_I2C2_SMBA AFR_4
#define AFR_PB12_I2S2_WS   AFR_5
#define AFR_PB12_SPI2_NSS  AFR_5
#define AFR_PB12_TIM1_BKIN AFR_1
#define AFR_PB12_TIM5_CH1  AFR_2

//PB13
#define AFR_PB13_EVENTOUT     AFR_15
#define AFR_PB13_FMPI2C1_SMBA AFR_4
#define AFR_PB13_I2S2_CK      AFR_5
#define AFR_PB13_SPI2_SCK     AFR_5
#define AFR_PB13_TIM1_CH1N    AFR_1

//PB14
#define AFR_PB14_EVENTOUT    AFR_15
#define AFR_PB14_FMPI2C1_SDA AFR_4
#define AFR_PB14_SPI2_MISO   AFR_5
#define AFR_PB14_TIM1_CH2N   AFR_1

//PB15
#define AFR_PB15_EVENTOUT    AFR_15
#define AFR_PB15_FMPI2C1_SCL AFR_4
#define AFR_PB15_I2S2_SD     AFR_5
#define AFR_PB15_RTC_REFIN   AFR_0
#define AFR_PB15_SPI2_MOSI   AFR_5
#define AFR_PB15_TIM1_CH3N   AFR_1

//PB2
#define AFR_PB2_EVENTOUT   AFR_15
#define AFR_PB2_LPTIM1_OUT AFR_1

//PB3
#define AFR_PB3_EVENTOUT     AFR_15
#define AFR_PB3_FMPI2C1_SDA  AFR_4
#define AFR_PB3_I2C2_SDA     AFR_9
#define AFR_PB3_I2S1_CK      AFR_5
#define AFR_PB3_SPI1_SCK     AFR_5
#define AFR_PB3_SYS_JTDO_SWO AFR_0
#define AFR_PB3_USART1_RX    AFR_7

//PB4
#define AFR_PB4_EVENTOUT  AFR_15
#define AFR_PB4_SPI1_MISO AFR_5
#define AFR_PB4_SYS_JTRST AFR_0

//PB5
#define AFR_PB5_EVENTOUT   AFR_15
#define AFR_PB5_I2C1_SMBA  AFR_4
#define AFR_PB5_I2S1_SD    AFR_5
#define AFR_PB5_LPTIM1_IN1 AFR_1
#define AFR_PB5_SPI1_MOSI  AFR_5

//PB6
#define AFR_PB6_EVENTOUT   AFR_15
#define AFR_PB6_I2C1_SCL   AFR_4
#define AFR_PB6_LPTIM1_ETR AFR_1
#define AFR_PB6_USART1_TX  AFR_7

//PB7
#define AFR_PB7_EVENTOUT   AFR_15
#define AFR_PB7_I2C1_SDA   AFR_4
#define AFR_PB7_LPTIM1_IN2 AFR_1
#define AFR_PB7_USART1_RX  AFR_7

//PB8
#define AFR_PB8_EVENTOUT   AFR_15
#define AFR_PB8_I2C1_SCL   AFR_4
#define AFR_PB8_I2S5_SD    AFR_6
#define AFR_PB8_LPTIM1_OUT AFR_1
#define AFR_PB8_SPI5_MOSI  AFR_6

//PB9
#define AFR_PB9_EVENTOUT  AFR_15
#define AFR_PB9_I2C1_SDA  AFR_4
#define AFR_PB9_I2C2_SDA  AFR_9
#define AFR_PB9_I2S2_WS   AFR_5
#define AFR_PB9_SPI2_NSS  AFR_5
#define AFR_PB9_TIM11_CH1 AFR_3

//PC0
#define AFR_PC0_EVENTOUT   AFR_15
#define AFR_PC0_LPTIM1_IN1 AFR_1

//PC1
#define AFR_PC1_EVENTOUT   AFR_15
#define AFR_PC1_LPTIM1_OUT AFR_1

//PC10
#define AFR_PC10_EVENTOUT    AFR_15
#define AFR_PC10_SYS_TRACED0 AFR_0
#define AFR_PC10_TIM5_CH2    AFR_2

//PC11
#define AFR_PC11_EVENTOUT    AFR_15
#define AFR_PC11_SYS_TRACED1 AFR_0
#define AFR_PC11_TIM5_CH3    AFR_2

//PC12
#define AFR_PC12_EVENTOUT    AFR_15
#define AFR_PC12_SYS_TRACED2 AFR_0
#define AFR_PC12_TIM11_CH1   AFR_3

//PC13
#define AFR_PC13_EVENTOUT AFR_15

//PC14
#define AFR_PC14_EVENTOUT AFR_15

//PC15
#define AFR_PC15_EVENTOUT AFR_15

//PC2
#define AFR_PC2_EVENTOUT   AFR_15
#define AFR_PC2_LPTIM1_IN2 AFR_1
#define AFR_PC2_SPI2_MISO  AFR_5

//PC3
#define AFR_PC3_EVENTOUT   AFR_15
#define AFR_PC3_I2S2_SD    AFR_5
#define AFR_PC3_LPTIM1_ETR AFR_1
#define AFR_PC3_SPI2_MOSI  AFR_5

//PC4
#define AFR_PC4_EVENTOUT AFR_15
#define AFR_PC4_TIM9_CH1 AFR_3

//PC5
#define AFR_PC5_EVENTOUT     AFR_15
#define AFR_PC5_FMPI2C1_SMBA AFR_4
#define AFR_PC5_TIM9_CH2     AFR_3

//PC6
#define AFR_PC6_EVENTOUT     AFR_15
#define AFR_PC6_FMPI2C1_SCL  AFR_4
#define AFR_PC6_I2S2_MCK     AFR_5
#define AFR_PC6_SYS_TRACECLK AFR_0
#define AFR_PC6_USART6_TX    AFR_8

//PC7
#define AFR_PC7_EVENTOUT    AFR_15
#define AFR_PC7_FMPI2C1_SDA AFR_4
#define AFR_PC7_I2S1_MCK    AFR_6
#define AFR_PC7_I2S2_CK     AFR_5
#define AFR_PC7_SPI2_SCK    AFR_5
#define AFR_PC7_USART6_RX   AFR_8

//PC8
#define AFR_PC8_EVENTOUT  AFR_15
#define AFR_PC8_USART6_CK AFR_8

//PC9
#define AFR_PC9_EVENTOUT    AFR_15
#define AFR_PC9_FMPI2C1_SDA AFR_4
#define AFR_PC9_I2S_CKIN    AFR_5
#define AFR_PC9_RCC_MCO_2   AFR_0

//PH0 
#define AFR_PH0 _EVENTOUT AFR_15

//PH1 
#define AFR_PH1 _EVENTOUT AFR_15

#endif
