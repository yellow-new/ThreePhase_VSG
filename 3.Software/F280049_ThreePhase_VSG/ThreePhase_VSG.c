//###########################################################################
//
// FILE:   ThreePhase_VSG


//
// Included Files
//
#include "F28x_Project.h"
#include "board.h"
#include "adc_3ph_prc.h"

//
// Globals
//
volatile uint16_t CCR_data = 50;
volatile uint16_t result[8] = {0};
uint16_t i;
//
// Global Struct
//


volatile union ADC_DATA  Adc_data;
__interrupt void mainISR(void);


//
// Main
//
void main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pull ups.
    //
    Device_initGPIO();

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Assign the interrupt service routines to ePWM interrupts
    //
    Interrupt_register(INT_EPWM1, &mainISR);

    //
    // Disable sync(Freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Configure GPIO0/1 , GPIO2/3 and GPIO4/5 as ePWM1A/1B, ePWM2A/2B and
    // ePWM3A/3B pins respectively
    // Configure EPWM Modules
    //
    Board_init();

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Enable ePWM interrupts
    //
    Interrupt_enable(INT_EPWM1);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // IDLE loop. Just sit and loop forever (optional):
    //
    for(;;)
    {
        //
        // CON single start
        //
        GpioDataRegs.GPACLEAR.bit.GPIO30 = 1;
        GpioDataRegs.GPASET.bit.GPIO30 = 1;
        //read result in AD7606
        while(GpioDataRegs.GPADAT.bit.GPIO15);
        if(GpioDataRegs.GPADAT.bit.GPIO15 == 0)
        {
            
            for( i = 0;i<8;i++)
            {
                data_get(&Adc_data);
                result[i]=Adc_data.result;
                if(i ==0 &&  GpioDataRegs.GPBDAT.bit.GPIO34 != 1) {break;}
            }
        }
        
        NOP;
    }
}

//
// epwm1ISR - ePWM 1 ISR
//
__interrupt void mainISR(void)
{

    //
    // Clear INT flag for this timer
    //
    EPWM_clearEventTriggerInterruptFlag(myEPWM1_BASE);

    //
    // Acknowledge interrupt group
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);
}


