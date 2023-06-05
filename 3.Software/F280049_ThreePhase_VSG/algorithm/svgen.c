#include "svgen.h"
void svgen_run(volatile SVGEN * v)
{   
    v->tmp1= v->Beta;															
	v->tmp2= (float32_t)0.5*v->Beta + (float32_t)0.8660254*v->Alpha;
    v->tmp3= v->tmp2 - v->tmp1;													
																				
	v->VecSector=3;																
	v->VecSector=(v->tmp2> 0)?( v->VecSector-1):v->VecSector;						
	v->VecSector=(v->tmp3> 0)?( v->VecSector-1):v->VecSector;						
	v->VecSector=(v->tmp1< 0)?(7-v->VecSector) :v->VecSector;						
																				
	if     (v->VecSector==1 || v->VecSector==4)                                   
      {     v->Ta= v->tmp2; 														
      		v->Tb= v->tmp1-v->tmp3; 												
      		v->Tc=-v->tmp2;														
      }								    										
   																				
    else if(v->VecSector==2 || v->VecSector==5)                                   
      {     v->Ta= v->tmp3+v->tmp2; 												
      		v->Tb= v->tmp1; 														
      		v->Tc=-v->tmp1;														
      }																	   		
   																				
    else                                                                        
      {     v->Ta= v->tmp3; 														
      		v->Tb=-v->tmp3; 														
      		v->Tc=-(v->tmp1+v->tmp2);												
      }							
}


