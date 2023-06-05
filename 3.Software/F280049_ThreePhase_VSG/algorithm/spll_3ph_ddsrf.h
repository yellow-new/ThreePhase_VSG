#ifndef _SPLL_3PH_DDSRF_
#define _SPLL_3PH_DDSRF_

#include "F28x_Project.h"
#include "board.h"
#include "math.h"





//
// SPLL
//
typedef struct{
//3ph V
    float32_t Va;
    float32_t Vb;
    float32_t Vc;

    float32_t Alpha;
    float32_t Beta;
    float32_t Z;


    float32 cos_2theta;
    float32 sin_2theta;

    float32_t d_p;
    float32_t q_p;
    float32_t d_n;
    float32_t q_n;

    float32_t d_p_decoupl;
    float32_t q_p_decoupl;
    float32_t d_n_decoupl;
    float32_t q_n_decoupl;


    float32_t d_p_decoupl_lpf;
    float32_t q_p_decoupl_lpf;
    float32_t d_n_decoupl_lpf;
    float32_t q_n_decoupl_lpf;

    float32_t x[2];
    float32_t y[2];
    float32_t z[2];
    float32_t w[2];

    float32_t k1;
    float32_t k2;

    float32 v_q[2];


	float32 ylf[2];

    float32 fo;
    float32 fn;
    float32 theta[2];
    float32 delta_T;


    float32 B0_lf;
    float32 B1_lf;
    float32 A1_lf;




}SPLL_3PH_DDSRF;


void SPLL_3ph_init(SPLL_3PH_DDSRF *spll_obj);
void SPLL_3ph_run( volatile SPLL_3PH_DDSRF *spll_obj);

#endif // _SPLL_3PH_DDSRF_
