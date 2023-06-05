//###########################################################################
//
// FILE:   ThreePhase_VSG


//
// Included Files
//
#include "F28x_Project.h"
#include "board.h"
#include "adc_3ph_prc.h"
#include "spll_3ph_ddsrf.h"
#include "svgen.h"
#include "math.h"


//
// Define
//
#define PI 3.1425926f
#define N  400
#define delta 2*PI/N
#define M 0.9f
#define NUMBER 400U
#define ARRAY_DEBUG 1
//
// Globals
//
//volatile uint16_t CCR_data = 50;
volatile uint16_t CCR_Ta = 0;
volatile uint16_t CCR_Tb = 0;
volatile uint16_t CCR_Tc = 0;
volatile uint16_t result[8] = {0};
uint16_t i,j;
#pragma DATA_SECTION(Voltage1,"RAMM0");
#pragma DATA_SECTION(Voltage2,"RAMM0");
#pragma DATA_SECTION(Voltage3,"RAMM0");
float32 Voltage1[NUMBER];
float32 Voltage2[NUMBER];
float32 Voltage3[NUMBER];
uint16_t ConversionCount;
float32_t theta;


//
// Global Struct
//


volatile union ADC_DATA  Adc_data;
volatile SPLL_3PH_DDSRF spll1;
volatile SVGEN svgen1;

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
        GpioDataRegs.GPASET.bit.GPIO30 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO30 = 1;

        //
        // test busy in AD7606
        //
        while(GpioDataRegs.GPADAT.bit.GPIO15);
        if(GpioDataRegs.GPADAT.bit.GPIO15 == 0)
        {

            for( j = 0;j<8;j++)
            {
                data_get(&Adc_data);
                result[j]=Adc_data.result;
                if(j ==0 &&  GpioDataRegs.GPBDAT.bit.GPIO34 != 1) {break;}
            }
        }
    }
}

//
// epwm1ISR - ePWM 1 ISR
//
__interrupt void mainISR(void)
{
//    //
//    // CON single start
//    //
    GpioDataRegs.GPASET.bit.GPIO30 = 1;
    GpioDataRegs.GPACLEAR.bit.GPIO30 = 1;
//
//    //
//    // test busy in AD7606
//    //
//    while(GpioDataRegs.GPADAT.bit.GPIO15);
//    if(GpioDataRegs.GPADAT.bit.GPIO15 == 0)
//    {
//
//        for( i = 0;i<8;i++)
//        {
//            data_get(&Adc_data);
//            result[i]=Adc_data.result;
//            if(i ==0 &&  GpioDataRegs.GPBDAT.bit.GPIO34 != 1) {break;}
//        }
//    }
//
//
//    //
//    // spll
//    //
//    spll1.Va = result[0];
//    spll1.Vb = result[1];
//    spll1.Vc = result[2];

    //SPLL_3ph_run(&spll1);

   // theta = (float)i*delta;

   svgen1.Alpha = M*sinf((float)i*delta);
   svgen1.Beta = M*cosf((float)i*delta);

    svgen_run(&svgen1);

    i++;
    if(i>=N)
    i=0;


    CCR_Ta = (svgen1.Ta+1)*0.5*2500;
    CCR_Tb = (svgen1.Tb+1)*0.5*2500;
    CCR_Tc = (svgen1.Tc+1)*0.5*2500;

    EPwm1Regs.CMPA.bit.CMPA = CCR_Ta;
    EPwm1Regs.CMPB.bit.CMPB = CCR_Ta;
    EPwm2Regs.CMPA.bit.CMPA = CCR_Tb;
    EPwm2Regs.CMPB.bit.CMPB = CCR_Tb;
    EPwm3Regs.CMPA.bit.CMPA = CCR_Tc;
    EPwm3Regs.CMPB.bit.CMPB = CCR_Tc;

    /* 波形放入数组    */
 #if ARRAY_DEBUG
      Voltage1[ConversionCount] = svgen1.Ta;
      Voltage2[ConversionCount] = svgen1.Tb;
      Voltage3[ConversionCount] = svgen1.Tc;
    if(ConversionCount == NUMBER - 1)
    {
        //asm(" ESTOP0");
        ConversionCount = 0;
    }
    else
    {
        ConversionCount++;
    }
    /*  END  */
 #endif



    //
    // Clear INT flag for this timer
    //
    EPWM_clearEventTriggerInterruptFlag(myEPWM1_BASE);

    //
    // Acknowledge interrupt group
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);
}


