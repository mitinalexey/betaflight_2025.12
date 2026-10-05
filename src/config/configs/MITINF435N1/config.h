/*
 * This file is part of Betaflight.
 *
 * Betaflight is free software. You can redistribute this software
 * and/or modify this software under the terms of the GNU General
 * Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later
 * version.
 * 
 * Betaflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this software.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#define FC_TARGET_MCU        AT32F435G
//#define USE_ATBSP_DRIVER
#define BOARD_NAME           MITINF435N1
#define MANUFACTURER_ID      MITIN


#define USE_FLASH
#define USE_FLASH_M25P16
#define USE_FLASH_W25N01G    // 1Gb NAND flash support
#define USE_FLASH_W25M       // Stacked die support
#define USE_FLASH_W25M512    // 512Kb (256Kb x 2 stacked) NOR flash support
#define USE_FLASH_W25M02G    // 2Gb (1Gb x 2 stacked) NAND flash support
#define USE_FLASH_W25Q128FV  // 16MB Winbond 25Q128
#define USE_FLASH_PY25Q128HA // 16MB PUYA SEMI 25Q128

#define USE_MAX7456

#define USE_SHOCKSENSOR
#define USE_BEEPER
#define BEEPER_INVERTED
#define BEEPER_PIN              PC9

// TMR2_CH1-CH4
#define MOTOR1_PIN              PA5
#define MOTOR2_PIN              PA1
#define MOTOR3_PIN              PB10
#define MOTOR4_PIN              PB11
// TMR3_CH1-CH4
#define MOTOR5_PIN              PA6
#define MOTOR6_PIN              PA7
#define MOTOR7_PIN              PB0
#define MOTOR8_PIN              PB1

// TMR8_CH4
#define USE_LED_STRIP
//#define LED_STRIP_PIN           PC9

//#define CAMERA SWITCH CONTROL
#define PINIO1_PIN              PB2
#define PINIO1_BOX              32

#define UART1_RX_PIN            PA10
#define UART1_TX_PIN            PA9
#define UART2_RX_PIN            PA3
#define UART2_TX_PIN            PA2
#define UART3_RX_PIN            PC5
#define UART3_TX_PIN            PC4
#define UART4_RX_PIN            PC11
#define UART4_TX_PIN            PC10
#define UART5_RX_PIN            PD2
#define UART5_TX_PIN            PC12
#define UART8_RX_PIN            PC3
#define UART8_TX_PIN            PC8

#define I2C1_SCL_PIN            PB8
#define I2C1_SDA_PIN            PB9

#define USE_GPS
#define UART6_RX_PIN            PC7
#define UART6_TX_PIN            PC6

#define ESC_SENSOR_UART         SERIAL_PORT_USART2
#define SERIALRX_UART           SERIAL_PORT_UART5
#define GPS_UART                SERIAL_PORT_USART6
#define VTX_TRAMP_UART          SERIAL_PORT_USART8

// vtx configuration
#define MAX_CHANNEL_ACTIVATION_CONDITION_COUNT 30
#define DISABLED_LOCK_ARMING_FLAG_VTX 1

#define USE_BARO
#define USE_BARO_BMP280
#define USE_BARO_QMP6988
#define USE_BARO_DPS310
//#define USE_BARO_BMP388
#define I2C2_SCL_PIN            PH2
#define I2C2_SDA_PIN            PH3
#define BARO_I2C_INSTANCE       (I2CDEV_2)

#define USE_MAG
#define MAG_I2C_INSTANCE        (I2CDEV_2)

#define LED0_PIN                PC13
#define LED1_PIN                PC14
#define LED2_PIN                PC15

#define FLASH_SPI_INSTANCE      SPI1
#define MAX7456_SPI_INSTANCE    SPI1

#define FLASH_CS_PIN            PB6
#define MAX7456_SPI_CS_PIN      PB7
#define USE_MCO
#define SPI1_SCK_PIN            PB3 // sck
#define SPI1_SDI_PIN            PB4 // miso
#define SPI1_SDO_PIN            PB5 // mosi

#define ADC_VBAT_PIN            PC1
#define ADC_CURR_PIN            PC0
#define ADC_RSSI_PIN            PC2
#define ADC_EXTERNAL1_PIN       PA4        // ADC1  ADC_VBAT2_PIN
#define ADC_EXTERNAL2_PIN       PA0        // ADC1  ADC_CURR2_PIN 

#define DEFAULT_CURRENT_METER_SOURCE    CURRENT_METER_ADC
#define DEFAULT_VOLTAGE_METER_SOURCE    VOLTAGE_METER_ADC

#define USE_ACC
#define USE_GYRO
//#define USE_ACCGYRO_BMI270
#define USE_ACCGYRO_QMI8658
#define GYRO_1_SPI_INSTANCE     SPI2
#define GYRO_1_ALIGN            CW90_DEG

#define GYRO_1_EXTI_PIN         PA15
#define GYRO_1_CS_PIN           PB12
#define SPI2_SCK_PIN            PB13 // sck
#define SPI2_SDI_PIN            PB14 // miso
#define SPI2_SDO_PIN            PB15 // mosi

#define TIMER_PIN_MAPPING       TIMER_PIN_MAP(0, PA5, 1, 0) \
                                TIMER_PIN_MAP(1, PA1, 1, 1) \
                                TIMER_PIN_MAP(2, PB10, 1, 2) \
                                TIMER_PIN_MAP(3, PB11, 1, 3) \
                                TIMER_PIN_MAP(4, PA6, 1, 4) \
                                TIMER_PIN_MAP(5, PA7, 1, 5) \
                                TIMER_PIN_MAP(6, PB0, 2, 6) \
                                TIMER_PIN_MAP(7, PB1, 2, 7) \
                                TIMER_PIN_MAP(8, PC9, 2, 12) \

#define ADC_INSTANCE            ADC1
#define ADC1_DMA_OPT            11

#define DEFAULT_BLACKBOX_DEVICE     BLACKBOX_DEVICE_FLASH
#define DEFAULT_DSHOT_BURST         DSHOT_DMAR_AUTO

#define SYSTEM_HSE_MHZ          25

// 10mV = 1A
#define DEFAULT_CURRENT_METER_SCALE 100

// 110 = 11:1 voltage divider (10k:1k) * 100 for 0.01V
#define DEFAULT_VOLTAGE_METER_SCALE 110
// 210 = 21:1 voltage divider (20k:1k) * 100 for 0.01V
// #define DEFAULT_VOLTAGE_METER_SCALE 210

/*
#define PINIO1_CONFIG                   129  
#define PINIO2_CONFIG                   1
#define PINIO1_BOX                      40
#define PINIO2_BOX                      41
#define BOX_USER1_NAME                  "BEC SWITCH"
#define BOX_USER2_NAME                  "CAM 1,2"
*/