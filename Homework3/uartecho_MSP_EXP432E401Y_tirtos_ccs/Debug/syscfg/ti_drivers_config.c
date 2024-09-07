/*
 *  ======== ti_drivers_config.c ========
 *  Configured TI-Drivers module definitions
 *
 *  DO NOT EDIT - This file is generated for the MSP_EXP432E401Y
 *  by the SysConfig tool.
 */

#include <stddef.h>
#include <stdint.h>

#ifndef DeviceFamily_MSP432E401Y
#define DeviceFamily_MSP432E401Y
#endif

#include <ti/devices/DeviceFamily.h>

#include "ti_drivers_config.h"


/*
 *  =============================== GPIO ===============================
 */

#include <ti/drivers/GPIO.h>
#include <ti/drivers/gpio/GPIOMSP432E4.h>

#define CONFIG_GPIO_COUNT 8

/*
 *  ======== gpioPinConfigs ========
 *  Array of Pin configurations
 */
GPIO_PinConfig gpioPinConfigs[CONFIG_GPIO_COUNT] = {
    /* CONFIG_GPIO_LED0 : LaunchPad LED D1 */
    GPIOMSP432E4_PN1 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW,
    /* CONFIG_GPIO_LED1 : LaunchPad LED D2 */
    GPIOMSP432E4_PN0 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW,
    /* CONFIG_GPIO_LED2 : LaunchPad LED D3 */
    GPIOMSP432E4_PF4 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW,
    /* CONFIG_GPIO_LED3 : LaunchPad LED D4 */
    GPIOMSP432E4_PF0 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW,
    /* CONFIG_GPIO_AUDIO_PWR */
    GPIOMSP432E4_PK5 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW,
    /* CONFIG_GPIO_MIC_PWR */
    GPIOMSP432E4_PD4 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_LOW,
    /* CONFIG_GPIO_SW1 : LaunchPad Button USR_SW1 (Left) */
    GPIOMSP432E4_PJ0 | GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING,
    /* CONFIG_GPIO_SW2 : LaunchPad Button USR_SW2 (Right) */
    GPIOMSP432E4_PJ1 | GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING,
};

/*
 *  ======== gpioCallbackFunctions ========
 *  Array of callback function pointers
 *
 *  NOTE: Unused callback entries can be omitted from the callbacks array to
 *  reduce memory usage by enabling callback table optimization
 *  (GPIO.optimizeCallbackTableSize = true)
 */
GPIO_CallbackFxn gpioCallbackFunctions[] = {
    /* CONFIG_GPIO_LED0 : LaunchPad LED D1 */
    NULL,
    /* CONFIG_GPIO_LED1 : LaunchPad LED D2 */
    NULL,
    /* CONFIG_GPIO_LED2 : LaunchPad LED D3 */
    NULL,
    /* CONFIG_GPIO_LED3 : LaunchPad LED D4 */
    NULL,
    /* CONFIG_GPIO_AUDIO_PWR */
    NULL,
    /* CONFIG_GPIO_MIC_PWR */
    NULL,
    /* CONFIG_GPIO_SW1 : LaunchPad Button USR_SW1 (Left) */
    NULL,
    /* CONFIG_GPIO_SW2 : LaunchPad Button USR_SW2 (Right) */
    NULL,
};

const uint_least8_t CONFIG_GPIO_LED0_CONST = CONFIG_GPIO_LED0;
const uint_least8_t CONFIG_GPIO_LED1_CONST = CONFIG_GPIO_LED1;
const uint_least8_t CONFIG_GPIO_LED2_CONST = CONFIG_GPIO_LED2;
const uint_least8_t CONFIG_GPIO_LED3_CONST = CONFIG_GPIO_LED3;
const uint_least8_t CONFIG_GPIO_AUDIO_PWR_CONST = CONFIG_GPIO_AUDIO_PWR;
const uint_least8_t CONFIG_GPIO_MIC_PWR_CONST = CONFIG_GPIO_MIC_PWR;
const uint_least8_t CONFIG_GPIO_SW1_CONST = CONFIG_GPIO_SW1;
const uint_least8_t CONFIG_GPIO_SW2_CONST = CONFIG_GPIO_SW2;

/*
 *  ======== GPIOMSP432E4_config ========
 */
const GPIOMSP432E4_Config GPIOMSP432E4_config = {
    .pinConfigs = (GPIO_PinConfig *)gpioPinConfigs,
    .callbacks = (GPIO_CallbackFxn *)gpioCallbackFunctions,
    .numberOfPinConfigs = CONFIG_GPIO_COUNT,
    .numberOfCallbacks = 8,
    .intPriority = (~0)
};


/*
 *  =============================== Power ===============================
 */

#include <ti/drivers/Power.h>
#include <ti/drivers/power/PowerMSP432E4.h>
#include <ti/devices/msp432e4/inc/msp432.h>

extern void PowerMSP432E4_sleepPolicy(void);

const PowerMSP432E4_Config PowerMSP432E4_config = {
    .policyFxn             = PowerMSP432E4_sleepPolicy,
    .enablePolicy          = true
};


/*
 *  =============================== UART ===============================
 */

#include <ti/drivers/UART.h>
#include <ti/drivers/uart/UARTMSP432E4.h>
#include <ti/devices/msp432e4/driverlib/interrupt.h>

#define CONFIG_UART_COUNT 2

UARTMSP432E4_Object uartMSP432E4Objects[CONFIG_UART_COUNT];

static unsigned char uartMSP432E4RingBuffer0[32];
static unsigned char uartMSP432E4RingBuffer1[32];
static const UARTMSP432E4_HWAttrs uartMSP432E4HWAttrs[CONFIG_UART_COUNT] = {
  {
    .baseAddr           = UART0_BASE,
    .intNum             = INT_UART0,
    .intPriority        = 0x80,
    .flowControl        = UARTMSP432E4_FLOWCTRL_NONE,
    .ringBufPtr         = uartMSP432E4RingBuffer0,
    .ringBufSize        = sizeof(uartMSP432E4RingBuffer0),
    .rxPin              = UARTMSP432E4_PA0_U0RX,
    .txPin              = UARTMSP432E4_PA1_U0TX,
    .ctsPin             = UARTMSP432E4_PIN_UNASSIGNED,
    .rtsPin             = UARTMSP432E4_PIN_UNASSIGNED,
    .errorFxn           = NULL
  },
  {
    .baseAddr           = UART6_BASE,
    .intNum             = INT_UART6,
    .intPriority        = (~0),
    .flowControl        = UARTMSP432E4_FLOWCTRL_NONE,
    .ringBufPtr         = uartMSP432E4RingBuffer1,
    .ringBufSize        = sizeof(uartMSP432E4RingBuffer1),
    .rxPin              = UARTMSP432E4_PP0_U6RX,
    .txPin              = UARTMSP432E4_PP1_U6TX,
    .ctsPin             = UARTMSP432E4_PIN_UNASSIGNED,
    .rtsPin             = UARTMSP432E4_PIN_UNASSIGNED,
    .errorFxn           = NULL
  },
};

const UART_Config UART_config[CONFIG_UART_COUNT] = {
    {   /* CONFIG_UART_0 */
        .fxnTablePtr = &UARTMSP432E4_fxnTable,
        .object      = &uartMSP432E4Objects[CONFIG_UART_0],
        .hwAttrs     = &uartMSP432E4HWAttrs[CONFIG_UART_0]
    },
    {   /* CONFIG_UART_1 */
        .fxnTablePtr = &UARTMSP432E4_fxnTable,
        .object      = &uartMSP432E4Objects[CONFIG_UART_1],
        .hwAttrs     = &uartMSP432E4HWAttrs[CONFIG_UART_1]
    },
};

const uint_least8_t CONFIG_UART_0_CONST = CONFIG_UART_0;
const uint_least8_t CONFIG_UART_1_CONST = CONFIG_UART_1;
const uint_least8_t UART_count = 2;


#include <ti/drivers/Board.h>

/*
 *  ======== Board_initHook ========
 *  Perform any board-specific initialization needed at startup.  This
 *  function is declared weak to allow applications to override it if needed.
 */
void __attribute__((weak)) Board_initHook(void)
{
}

/*
 *  ======== Board_init ========
 *  Perform any initialization needed before using any board APIs
 */
void Board_init(void)
{
    /* ==== /ti/drivers/Power initialization ==== */
    Power_init();

    /* Grant the DMA access to all FLASH memory */
    FLASH_CTRL->PP |= FLASH_PP_DFA;

    /* Region start address - match FLASH start address */
    FLASH_CTRL->DMAST = 0x00000000;

    /*
     * Access to FLASH is granted to the DMA in 2KB regions.  The value
     * assigned to DMASZ is the amount of 2KB regions to which the DMA will
     * have access.  The value can be determined via the following:
     *     2 * (num_regions + 1) KB
     *
     * To grant full access to entire 1MB of FLASH:
     *     2 * (511 + 1) KB = 1024 KB (1 MB)
     */
    FLASH_CTRL->DMASZ = 511;

    Board_initHook();
}
