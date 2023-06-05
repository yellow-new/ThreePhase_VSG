
#include "spll_3ph_ddsrf.h"




void SPLL_3ph_init(SPLL_3PH_DDSRF *spll_obj)
{
    


}



void SPLL_3ph_run( volatile SPLL_3PH_DDSRF *spll_obj)
{
//
// (a,b,c)->(Alpha,Beta,0)
//
// v_alpha = 2/3 * (a - 1/2 * (b + c))
// v_beta = sqrt(3)/3 * (b - c)
// v_z = 1/sqrt(3) * (a + b + c)
//
//
spll_obj->Alpha = (0.66666666677f) * (spll_obj->Va - 0.5f * (spll_obj->Vb + spll_obj->Vc));
spll_obj->Beta  = (0.57735026913f) * (spll_obj->Vb - spll_obj->Vc);
spll_obj->Z     = (0.57735026913f) * (spll_obj->Va + spll_obj->Vb + spll_obj->Vc);

//
// (Alpha,Beta,0)->(dqz+)
// (Alpha,Beta,0)->(dqz-)
//
spll_obj->d_n = spll_obj->Alpha * spll_obj->cos_2theta - spll_obj->Beta *spll_obj->sin_2theta;
spll_obj->q_n = spll_obj->Alpha * spll_obj->sin_2theta   + spll_obj->Beta * spll_obj->cos_2theta;

spll_obj->d_p = spll_obj->Alpha * spll_obj->cos_2theta + spll_obj->Beta *spll_obj->sin_2theta;
spll_obj->q_p = -spll_obj->Alpha * spll_obj->sin_2theta   + spll_obj->Beta * spll_obj->cos_2theta;

//
// Decoupling Network
//   
spll_obj->d_p_decoupl=spll_obj->d_p - (spll_obj->d_n_decoupl_lpf*spll_obj->cos_2theta) - (spll_obj->q_n_decoupl*spll_obj->sin_2theta);
spll_obj->q_p_decoupl=spll_obj->q_p + (spll_obj->d_n_decoupl_lpf*spll_obj->sin_2theta) - (spll_obj->q_n_decoupl*spll_obj->cos_2theta);

spll_obj->d_n_decoupl=spll_obj->d_n - (spll_obj->d_p_decoupl_lpf*spll_obj->cos_2theta) + (spll_obj->q_p_decoupl*spll_obj->sin_2theta);
spll_obj->q_n_decoupl=spll_obj->q_n - (spll_obj->d_p_decoupl_lpf*spll_obj->sin_2theta) - (spll_obj->q_p_decoupl*spll_obj->cos_2theta);

//
// Low pass filter
//     
spll_obj->y[1]=(spll_obj->d_p_decoupl*spll_obj->k1) - (spll_obj->y[0]*spll_obj->k2);
spll_obj->d_p_decoupl_lpf=spll_obj->y[1] + spll_obj->y[0];
spll_obj->y[0]=spll_obj->y[1];

spll_obj->x[1]=(spll_obj->q_p_decoupl*spll_obj->k1) - (spll_obj->x[0]*spll_obj->k2);
spll_obj->q_p_decoupl_lpf=spll_obj->x[1] + spll_obj->x[0];
spll_obj->x[0]=spll_obj->x[1];

spll_obj->w[1]=(spll_obj->d_n_decoupl*spll_obj->k1) - (spll_obj->w[0]*spll_obj->k2);
spll_obj->d_n_decoupl_lpf=spll_obj->w[1] + spll_obj->w[0];
spll_obj->w[0]=spll_obj->w[1];

spll_obj->z[1]=(spll_obj->q_n_decoupl*spll_obj->k1) - (spll_obj->z[0]*spll_obj->k2);
spll_obj->q_n_decoupl_lpf=spll_obj->z[1] + spll_obj->z[0];
spll_obj->z[0]=spll_obj->z[1];

spll_obj->v_q[0]=spll_obj->q_p_decoupl;

//
// Loop Filter
//
spll_obj->ylf[0]=spll_obj->ylf[1] + (spll_obj->B0_lf*spll_obj->v_q[0]) + (spll_obj->B1_lf*spll_obj->v_q[1]);
spll_obj->ylf[1]=spll_obj->ylf[0];
spll_obj->v_q[1]=spll_obj->v_q[0];

//
// VCO
//
spll_obj->fo=spll_obj->fn+spll_obj->ylf[0];

spll_obj->theta[0]=spll_obj->theta[1] + ((spll_obj->fo*spll_obj->delta_T)*(float32)(2*3.1415926));
if(spll_obj->theta[0]>(float32)(2*3.1415926))
    spll_obj->theta[0]=spll_obj->theta[0] - (float32)(2*3.1415926);

spll_obj->theta[1]=spll_obj->theta[0];


}
 






















