
#ifndef _ADC_3PH_PRC_H_
#define _ADC_3PH_PRC_H_

#include "F28x_Project.h"
#include "board.h"



 struct ADC_BITS {
    Uint16 DB_0:1;
    Uint16 DB_1:1;                     
    Uint16 DB_2:1;                    
    Uint16 DB_3:1;                  
    Uint16 DB_4:1;
    Uint16 DB_5:1;
    Uint16 DB_6:1;
    Uint16 DB_7:1;
    Uint16 DB_8:1;
    Uint16 DB_9:1;
    Uint16 DB_10:1;
    Uint16 DB_11:1;
    Uint16 DB_12:1;
    Uint16 DB_13:1;
    Uint16 DB_14:1;
    Uint16 DB_15:1;                  
};

union ADC_DATA {
    Uint16  result;
    struct  ADC_BITS * bit;
};


void data_get(volatile union ADC_DATA  *data);






#endif /* _ADC_3PH_PRC_H_ */



