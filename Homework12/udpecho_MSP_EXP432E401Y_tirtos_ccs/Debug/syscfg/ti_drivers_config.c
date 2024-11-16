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
 *  =============================== ADCBuf ===============================
 */

#include <ti/drivers/ADCBuf.h>
#include <ti/drivers/adcbuf/ADCBufMSP432E4.h>

#include <ti/devices/msp432e4/inc/msp432.h>

#define CONFIG_ADCBUF_COUNT 1

/*
 *  ======== adcbufMSP432E4Objects ========
 */
ADCBufMSP432E4_Object adcbufMSP432E4Objects[CONFIG_ADCBUF_COUNT];

/*
 *  ======== ADCBuf Channels ========
 */
ADCBufMSP432E4_Channels adcBuf0MSP432E4Channels[] = {
    /* ADCBUF_CHANNEL_0 */
    {
        .adcPin = ADCBufMSP432E4_PD_5_A6,
        .adcSequence = ADCBufMSP432E4_Seq_0,
        .adcInputMode = ADCBufMSP432E4_SINGLE_ENDED,
        .adcDifferentialPin = ADCBufMSP432E4_PIN_NONE,
        .adcInternalSource = ADCBufMSP432E4_INTERNAL_SOURCE_MODE_OFF,
        .refVoltage = 3300000
    },
};

/*
 *  ======== ADCBuf Seqeunce Priorities ========
 */
static ADCBufMSP432E4_SequencePriorities seqPriorities0[ADCBufMSP432E4_SEQUENCER_COUNT] = {
    /* Sequencer 0 */
    ADCBufMSP432E4_Priority_0,
    /* Sequencer 1 */
    ADCBufMSP432E4_Seq_Disable,
    /* Sequencer 2 */
    ADCBufMSP432E4_Seq_Disable,
    /* Sequencer 3 */
    ADCBufMSP432E4_Seq_Disable,
};

/*
 *  ======== ADCBuf Seqeunce Trigger Sources ========
 */
static ADCBufMSP432E4_TriggerSource triggerSource0[ADCBufMSP432E4_SEQUENCER_COUNT] = {
    /* Sequencer 0 trigger source */
    ADCBufMSP432E4_TIMER_TRIGGER,
    /* Sequencer 1 trigger source */
    ADCBufMSP432E4_SOFTWARE_AUTOMATIC_TRIGGER,
    /* Sequencer 2 trigger source */
    ADCBufMSP432E4_SOFTWARE_AUTOMATIC_TRIGGER,
    /* Sequencer 3 trigger source */
    ADCBufMSP432E4_SOFTWARE_AUTOMATIC_TRIGGER,
};

/*
 *  ======== adcbufMSP432E4HWAttrs ========
 */
const ADCBufMSP432E4_HWAttrsV1 adcbufMSP432E4HWAttrs[CONFIG_ADCBUF_COUNT] = {
    /* CONFIG_ADCBUF_0 */
    {
        .intPriority = (~0),
        .adcBase = ADC0_BASE,
        .channelSetting = adcBuf0MSP432E4Channels,
        .sequencePriority = seqPriorities0,
        .adcTriggerSource = triggerSource0,
        .modulePhase = ADCBufMSP432E4_Phase_Delay_0,
        .refSource = ADCBufMSP432E4_VREF_INTERNAL,
        .useDMA = 1,
        .adcTimerSource = TIMER3_BASE
    },
};

/*
 *  ======== ADCBuf_config ========
 */
const ADCBuf_Config ADCBuf_config[CONFIG_ADCBUF_COUNT] = {
    /* CONFIG_ADCBUF_0 */
    {
        .fxnTablePtr = &ADCBufMSP432E4_fxnTable,
        .object = &adcbufMSP432E4Objects[CONFIG_ADCBUF_0],
        .hwAttrs = &adcbufMSP432E4HWAttrs[CONFIG_ADCBUF_0]
    },
};

const uint_least8_t CONFIG_ADCBUF_0_CONST = CONFIG_ADCBUF_0;
const uint_least8_t ADCBUF_CHANNEL_0_CONST = ADCBUF_CHANNEL_0;
const uint_least8_t ADCBuf_count = CONFIG_ADCBUF_COUNT;


/*
 *  =============================== DMA ===============================
 */

#include <ti/drivers/dma/UDMAMSP432E4.h>
#include <ti/devices/msp432e4/inc/msp432.h>
#include <ti/devices/msp432e4/driverlib/interrupt.h>
#include <ti/devices/msp432e4/driverlib/udma.h>

/* Ensure DMA control table is aligned as required by the uDMA Hardware */
static tDMAControlTable dmaControlTable[64] __attribute__ ((aligned (1024)));

/* This is the handler for the uDMA error interrupt. */
static void dmaErrorFxn(uintptr_t arg)
{
    int status = uDMAErrorStatusGet();
    uDMAErrorStatusClear();

    /* Suppress unused variable warning */
    (void)status;

    while (1);
}

UDMAMSP432E4_Object udmaMSP432E4Object;

const UDMAMSP432E4_HWAttrs udmaMSP432E4HWAttrs = {
    .controlBaseAddr = (void *)dmaControlTable,
    .dmaErrorFxn     = (UDMAMSP432E4_ErrorFxn)dmaErrorFxn,
    .intNum          = INT_UDMAERR,
    .intPriority     = (~0)
};

const UDMAMSP432E4_Config UDMAMSP432E4_config = {
    .object  = &udmaMSP432E4Object,
    .hwAttrs = &udmaMSP432E4HWAttrs
};


/*
 *  =============================== EMAC ===============================
 */

/*
 *  EMAC device pin resources used:
 *  LED 0: PK4
 *  LED 1: PK6
 */

#include <ti/devices/msp432e4/driverlib/interrupt.h>
#include <ti/drivers/emac/EMACMSP432E4.h>

/*
 *  Ethernet MAC address
 *  NOTE: By default (i.e. when each octet is 0xff), the driver reads the MAC
 *        address that's stored in flash.
 */
static uint8_t macAddress[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

/* EMAC configuration structure */
const EMACMSP432E4_HWAttrs EMACMSP432E4_hwAttrs = {
    .baseAddr = EMAC0_BASE,
    .intNum = INT_EMAC0,
    .intPriority = (~0),
    .led0Pin = EMACMSP432E4_PK4_EN0LED0,
    .led1Pin = EMACMSP432E4_PK6_EN0LED1,
    .macAddress = macAddress
};


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
    GPIOMSP432E4_PK5 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_HIGH,
    /* CONFIG_GPIO_MIC_PWR */
    GPIOMSP432E4_PD4 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_MED | GPIO_CFG_OUT_HIGH,
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
extern void GPIO_SW1_Callback(uint_least8_t index);
extern void GPIO_SW2_Callback(uint_least8_t index);

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
    GPIO_SW1_Callback,
    /* CONFIG_GPIO_SW2 : LaunchPad Button USR_SW2 (Right) */
    GPIO_SW2_Callback,
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
 *  =============================== SPI ===============================
 */

#include <ti/drivers/SPI.h>
#include <ti/drivers/spi/SPIMSP432E4DMA.h>

#include <ti/devices/msp432e4/inc/msp432.h>
#include <ti/devices/msp432e4/driverlib/adc.h>
#include <ti/devices/msp432e4/driverlib/interrupt.h>
#include <ti/devices/msp432e4/driverlib/pwm.h>
#include <ti/devices/msp432e4/driverlib/sysctl.h>
#include <ti/devices/msp432e4/driverlib/udma.h>

#define CONFIG_SPI_COUNT 1

/*
 *  ======== spiMSP432E4DMAObjects ========
 */
SPIMSP432E4DMA_Object spiMSP432E4DMAObjects[CONFIG_SPI_COUNT];

/*
 *  ======== spiMSP432E4DMAHWAttrs ========
 */
const SPIMSP432E4DMA_HWAttrs spiMSP432E4DMAHWAttrs[CONFIG_SPI_COUNT] = {
    /* CONFIG_SPI_0 */
    {
        .baseAddr = SSI3_BASE,
        .intNum = INT_SSI3,
        .intPriority = 0x20,
        .defaultTxBufValue = ~0,
        .rxDmaChannel = NULL,
        .txDmaChannel = UDMA_CH15_SSI3TX,
        .clkPinMask  = SPIMSP432E4_PQ0_SSI3CLK,
        .xdat0PinMask = SPIMSP432E4_PQ2_SSI3XDAT0,
        .xdat1PinMask = SPIMSP432E4_PIN_NO_CONFIG,
        .fssPinMask  = SPIMSP432E4_PQ1_SSI3FSS,
        .minDmaTransferSize = 10
    },
};

/*
 *  ======== SPI_config ========
 */
const SPI_Config SPI_config[CONFIG_SPI_COUNT] = {
    /* CONFIG_SPI_0 */
    {
        .fxnTablePtr = &SPIMSP432E4DMA_fxnTable,
        .object = &spiMSP432E4DMAObjects[CONFIG_SPI_0],
        .hwAttrs = &spiMSP432E4DMAHWAttrs[CONFIG_SPI_0]
    },
};

const uint_least8_t CONFIG_SPI_0_CONST = CONFIG_SPI_0;
const uint_least8_t SPI_count = CONFIG_SPI_COUNT;


/*
 *  =============================== Timer ===============================
 */

#include <ti/drivers/Timer.h>
#include <ti/drivers/timer/TimerMSP432E4.h>
#include <ti/devices/msp432e4/inc/msp432e401y.h>
#include <ti/devices/msp432e4/driverlib/interrupt.h>

#define CONFIG_TIMER_COUNT 2

/*
 *  ======== timerMSP432E4Objects ========
 */
TimerMSP432E4_Object timerMSP432E4Objects[CONFIG_TIMER_COUNT];

/*
 *  ======== timerMSP432E4HWAttrs ========
 */
const TimerMSP432E4_HWAttrs timerMSP432E4HWAttrs[CONFIG_TIMER_COUNT] = {
    /* CONFIG_TIMER_0 */
    {
        .baseAddress = TIMER2_BASE,
        .subTimer    = TimerMSP432E4_timer32,
        .intNum      = INT_TIMER2A,
        .intPriority = 0x20
    },
    /* CONFIG_TIMER_1 */
    {
        .baseAddress = TIMER1_BASE,
        .subTimer    = TimerMSP432E4_timer32,
        .intNum      = INT_TIMER1A,
        .intPriority = 0x80
    },
};

/*
 *  ======== Timer_config ========
 */
const Timer_Config Timer_config[CONFIG_TIMER_COUNT] = {
    /* CONFIG_TIMER_0 */
    {
        .fxnTablePtr = &TimerMSP432E4_fxnTable,
        .object      = &timerMSP432E4Objects[CONFIG_TIMER_0],
        .hwAttrs     = &timerMSP432E4HWAttrs[CONFIG_TIMER_0]
    },
    /* CONFIG_TIMER_1 */
    {
        .fxnTablePtr = &TimerMSP432E4_fxnTable,
        .object      = &timerMSP432E4Objects[CONFIG_TIMER_1],
        .hwAttrs     = &timerMSP432E4HWAttrs[CONFIG_TIMER_1]
    },
};

const uint_least8_t CONFIG_TIMER_0_CONST = CONFIG_TIMER_0;
const uint_least8_t CONFIG_TIMER_1_CONST = CONFIG_TIMER_1;
const uint_least8_t Timer_count = CONFIG_TIMER_COUNT;


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
    .baseAddr           = UART7_BASE,
    .intNum             = INT_UART7,
    .intPriority        = (~0),
    .flowControl        = UARTMSP432E4_FLOWCTRL_NONE,
    .ringBufPtr         = uartMSP432E4RingBuffer1,
    .ringBufSize        = sizeof(uartMSP432E4RingBuffer1),
    .rxPin              = UARTMSP432E4_PC4_U7RX,
    .txPin              = UARTMSP432E4_PC5_U7TX,
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
