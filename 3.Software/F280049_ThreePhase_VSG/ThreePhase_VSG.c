//###########################################################################
//
// FILE:   ThreePhase_VSG


//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"

//
// Globals
//
volatile uint16_t CCR_data = 50;

//
//
//
__interrupt void INT_myEPWM0_ISR(void);
__attribute__((interrupt)) void Cla1Task1();


//
// ThreePhase' Current Voltage
//

//
//
//

//
//
//




void main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pullups.
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
    // Board Initialization
    //

    Board_init();

    //
    // Enable global Interrupts and higher priority real-time debug events:
    //
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

    //
    // Take conversions indefinitely in loop
    //
    do
    {


        //
        // change PWM CCR RLG
        //
        EPWM_setCounterCompareValue(myEPWM2_BASE, EPWM_COUNTER_COMPARE_A, CCR_data);

        //
        // Software breakpoint, hit run again to get updated conversions
        //
        asm("   ESTOP0");

    }
    while(1);
}



#pragma CODE_SECTION(INT_myEPWM0_ISR,".TI.ramfunc");

__interrupt void INT_myEPWM0_ISR()
    {



    }


__attribute__((interrupt)) void Cla1Task1()
    {




    }

//
// End of file
//
