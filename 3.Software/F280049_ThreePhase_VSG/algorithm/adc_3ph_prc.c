#include "adc_3ph_prc.h"

void data_get(volatile union ADC_DATA  *data)
{
    GpioDataRegs.GPBCLEAR.bit.GPIO39 = 1;
    DEVICE_DELAY_US(1);  
    data->bit->DB_0 = GpioDataRegs.GPADAT.bit.GPIO22;
    data->bit->DB_1 = GpioDataRegs.GPADAT.bit.GPIO23;
    data->bit->DB_2 = GpioDataRegs.GPADAT.bit.GPIO13;
    data->bit->DB_3 = GpioDataRegs.GPADAT.bit.GPIO18;
    data->bit->DB_4 = GpioDataRegs.GPBDAT.bit.GPIO58;
    data->bit->DB_5 = GpioDataRegs.GPADAT.bit.GPIO27;
    data->bit->DB_6 = GpioDataRegs.GPADAT.bit.GPIO26;
    data->bit->DB_7 = GpioDataRegs.GPBDAT.bit.GPIO40;
    data->bit->DB_8 = GpioDataRegs.GPADAT.bit.GPIO31;
    data->bit->DB_9 = GpioDataRegs.GPADAT.bit.GPIO24;
    data->bit->DB_10 = GpioDataRegs.GPADAT.bit.GPIO17;
    data->bit->DB_11 = GpioDataRegs.GPADAT.bit.GPIO16;
    data->bit->DB_12 = GpioDataRegs.GPBDAT.bit.GPIO33;
    data->bit->DB_13 = GpioDataRegs.GPADAT.bit.GPIO12;
    data->bit->DB_14 = GpioDataRegs.GPADAT.bit.GPIO25;
    data->bit->DB_15 = GpioDataRegs.GPADAT.bit.GPIO28;

     DEVICE_DELAY_US(1); 
    GpioDataRegs.GPBSET.bit.GPIO39 = 1;
}







