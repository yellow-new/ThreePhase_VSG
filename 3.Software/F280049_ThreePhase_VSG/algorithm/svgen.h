#ifndef _SVGEN_H
#define _SVGEN_H

#include "F28x_Project.h"
#include "board.h"



typedef struct{

    float32_t Alpha;
    float32_t Beta;

    float32_t  Ta;
    float32_t  Tb;
    float32_t  Tc;

    float32_t  tmp1;
    float32_t  tmp2;
    float32_t  tmp3;

    uint16_t  VecSector;
}SVGEN;

void svgen_run(volatile SVGEN * v);

#endif /*_SVGEN_H*/









