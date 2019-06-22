#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"


void Adc_Init(void);
u16  Get_Adc(u8 ch); 
u16 Get_Adc_Average(u8 ch,u8 times); 

float get_ad_value(u8 ch);
float get_value(u8 i);
 
#endif 
