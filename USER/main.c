
#include "adc.h"
#include "delay.h"
#include "lcd.h"

#include <math.h>

typedef struct
{
	u8 x ;
	float y;
	u8 z ;
	u8 handle_z[3];
}seq;


void hardware()
{
	u8 n1;
	delay_init();
	LCD_Init();
	Adc_Init();
	delay_ms(500);
	
	//铠装电缆对芯装置		
	for(n1=0;n1<10;n1++)
	{
		LCD_ShowHz_48(50+45*n1,16,n1,0);
	}		

}

void swap(u8 *x,u8 *y)
{
	u8 temp;
	temp = *x;
	*x = *y;
	*y = temp;	
}

	int main()
	{
		u8 i=0,j=0;
		u8 time = 0;
		u8 n=0,n1=0;
		u8 k=0,k1=0;
		
		u8 num = 0;

		seq ad[12];
		float temp1;
		
		
		hardware();	
		for(i=0;i<12;i++)
		{
			if(i+1>9) LCD_printf(90+k1*160,90+n1*32,150,32,32,"%d -- ",i+1 );
			
			else 	LCD_printf(90+k1*160,90+n1*32,150,32,32,"%d --- ",i+1 );	
			
					n1++;
				if(n1==6)
				{
					n1=0;
					k1++;
				}				
		}
		
while(1)
{
	
	
	
	k=0;	
	
	/***********************************存储**********************************/
	for(time= 0;time<3;time++)
{	
		for(i = 0;i<12;i++)
		{

			ad[i].x =i;	
			ad[i].y  =get_value(i);
			ad[i].z =i;
			
				
				//显示AD电压值
		    		//放在for前面
//				LCD_printf(0+k*400,10+n*32,150,32,32,"%.3f",ad[i].y  );		
//				n++;
//			if(n==6)
//			{
//				n=0;
//				k++;
//			
//		}
		}
		/*********************************对序***********************************/	
		

	for(i=0;i<12;i++)
	{
				for(j=i+1;j<12;j++)
				{
					if(ad[i].y < ad[j].y )
					{
						swap(&ad[i].z ,&ad[j].z );
						temp1 = ad[i].y ;
						ad[i].y =ad[j].y ;
						ad[j].y =temp1;
								
					}
					
						ad[i].handle_z[time]=ad[i].z ;
						ad[j].handle_z[time]=ad[j].z ;					
					
				}			
	
	}		
	
}
	/******************************结果处理及显示*************************************/	
	

	k1 = 0;	
	n1 = 0;
	for(i=0;i<12;i++)
		{
			if(ad[i].handle_z[0]==ad[i].handle_z[1])
			{
				ad[i].z =ad[i].handle_z[0];
			}
			else if(ad[i].handle_z[0]==ad[i].handle_z[2])
			{
				ad[i].z =ad[i].handle_z[0];
			}			
			else if(ad[i].handle_z[1]==ad[i].handle_z[2])
			{
				ad[i].z =ad[i].handle_z[1];
			}	
			else {}			
			
			
			
			if(ad[i].y <=0.5) 
			{
			
			LCD_Fill(90+k1*160,90+n1*32,230+150*k1,132+n1*32,WHITE);
			if(ad[i].x+1 >9) LCD_printf(90+k1*160,90+n1*32,150,32,32,"%d -- NC",ad[i].x+1  );	
			else 	LCD_printf(90+k1*160,90+n1*32,150,32,32,"%d --- NC",ad[i].x+1  );		
					n1++;
				if(n1==6)
				{
					n1=0;
					k1++;
				}	
				
			}

	else{
			LCD_Fill(90+k1*160,90+n1*32,230+150*k1,132+n1*32,WHITE);
			if(ad[i].x+1 >9) LCD_printf(90+k1*160,90+n1*32,150,32,32,"%d -- %d",ad[i].x+1 ,ad[i].z+1 );	
			else 	LCD_printf(90+k1*160,90+n1*32,150,32,32,"%d --- %d",ad[i].x+1 ,ad[i].z+1 );		
					n1++;
				if(n1==6)
				{
					n1=0;
					k1++;
				}	
			}	
				
			}	
		
			if(k1) LCD_Fill(90+k1*160,90+n1*32,480,320,WHITE);
			else  LCD_Fill(250,90,480,320,WHITE);
			
		for(num=0;num<10;num++)
		{
			delay_ms(500);
		}
		

			
	}


}
	
		
