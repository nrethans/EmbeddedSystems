/*
 *  ======== ti_drivers_config.h ========
 *  Configured TI-Drivers module declarations
 *
 *  The macros defines herein are intended for use by applications which
 *  directly include this header. These macros should NOT be hard coded or
 *  copied into library source code.
 *
 *  Symbols declared as const are intended for use with libraries.
 *  Library source code must extern the correct symbol--which is resolved
 *  when the application is linked.
 *
 *  DO NOT EDIT - This file is generated for the MSP_EXP432E401Y
 *  by the SysConfig tool.
 */
#ifndef ti_drivers_config_h
#define ti_drivers_config_h

#define CONFIG_SYSCONFIG_PREVIEW

#define CONFIG_MSP_EXP432E401Y
#ifndef DeviceFamily_MSP432E401Y
#define DeviceFamily_MSP432E401Y
#endif

#include <ti/devices/DeviceFamily.h>

#include <stdint.h>

/* support C++ sources */
#ifdef __cplusplus
extern "C" {
#endif


/*
 *  ======== ADCBuf ========
 */

extern const uint_least8_t          CONFIG_ADCBUF_0_CONST;
#define CONFIG_ADCBUF_0             0

/*
 * ======== ADCBuf Channels ========
 */

/* PD5 */
extern const uint_least8_t          ADCBUF_CHANNEL_0_CONST;
#define ADCBUF_CHANNEL_0            0


/*
 *  ======== GPIO ========
 */

/* PN1, LaunchPad LED D1 */
extern const uint_least8_t          CONFIG_GPIO_LED0_CONST;
#define CONFIG_GPIO_LED0            0
/* PN0, LaunchPad LED D2 */
extern const uint_least8_t          CONFIG_GPIO_LED1_CONST;
#define CONFIG_GPIO_LED1            1
/* PF4, LaunchPad LED D3 */
extern const uint_least8_t          CONFIG_GPIO_LED2_CONST;
#define CONFIG_GPIO_LED2            2
/* PF0, LaunchPad LED D4 */
extern const uint_least8_t          CONFIG_GPIO_LED3_CONST;
#define CONFIG_GPIO_LED3            3
/* PK5 */
extern const uint_least8_t          CONFIG_GPIO_AUDIO_PWR_CONST;
#define CONFIG_GPIO_AUDIO_PWR       4
/* PD4 */
extern const uint_least8_t          CONFIG_GPIO_MIC_PWR_CONST;
#define CONFIG_GPIO_MIC_PWR         5
/* PJ0, LaunchPad Button USR_SW1 (Left) */
extern const uint_least8_t          CONFIG_GPIO_SW1_CONST;
#define CONFIG_GPIO_SW1             6
/* PJ1, LaunchPad Button USR_SW2 (Right) */
extern const uint_least8_t          CONFIG_GPIO_SW2_CONST;
#define CONFIG_GPIO_SW2             7

/* LEDs are active high */
#define CONFIG_GPIO_LED_ON  (1)
#define CONFIG_GPIO_LED_OFF (0)

#define CONFIG_LED_ON  (CONFIG_GPIO_LED_ON)
#define CONFIG_LED_OFF (CONFIG_GPIO_LED_OFF)


/*
 *  ======== SPI ========
 */

/*
 *  MOSI: PQ2
 *  MISO: Unassigned
 *  SCLK: PQ0
 *  SS: PQ1
 */
extern const uint_least8_t          CONFIG_SPI_0_CONST;
#define CONFIG_SPI_0                0


/*
 *  ======== Timer ========
 */

extern const uint_least8_t          CONFIG_TIMER_0_CONST;
#define CONFIG_TIMER_0              0
extern const uint_least8_t          CONFIG_TIMER_1_CONST;
#define CONFIG_TIMER_1              1

/*
 *  ======== UART ========
 */

/*
 *  TX: PA1
 *  RX: PA0
 *  XDS110 UART
 */
extern const uint_least8_t          CONFIG_UART_0_CONST;
#define CONFIG_UART_0               0
/*
 *  TX: PC5
 *  RX: PC4
 */
extern const uint_least8_t          CONFIG_UART_1_CONST;
#define CONFIG_UART_1               1


/*
 *  ======== Board_init ========
 *  Perform all required TI-Drivers initialization
 *
 *  This function should be called once at a point before any use of
 *  TI-Drivers.
 */
extern void Board_init(void);

/*
 *  ======== Board_initGeneral ========
 *  (deprecated)
 *
 *  Board_initGeneral() is defined purely for backward compatibility.
 *
 *  All new code should use Board_init() to do any required TI-Drivers
 *  initialization _and_ use <Driver>_init() for only where specific drivers
 *  are explicitly referenced by the application.  <Driver>_init() functions
 *  are idempotent.
 */
#define Board_initGeneral Board_init

#ifdef __cplusplus
}
#endif

#endif /* include guard */
