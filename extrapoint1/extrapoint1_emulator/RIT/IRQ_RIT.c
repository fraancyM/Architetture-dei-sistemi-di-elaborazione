/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../led/led.h"
#include "../GLCD/GLCD.h" 
#include "../timer/timer.h"
#include "../draw.h"


/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

volatile int left = 0, right = 0, select = 0;
extern volatile int finito;
extern int sec, min, hour;

void RIT_IRQHandler (void)
{	
	static int j_left = 0, j_right = 0, j_select = 0;
	
	if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){	
		/* Joytick Select pressed p1.25*/
		/* Joytick Down pressed p1.25 --> using J_DOWN due to emulator issues*/
		
		j_select ++;
		
		switch(j_select){
			case 1:
				
			if(left==1){ //selezionato meal
				PandaMeal();
				left = 0; //resetto left
			}
			
			if(right==1){ //Seleziono snack
				PandaSnack();
				right = 0;	//Resetto right
			}
			
			if(finito==1){	//Devo resettare
				
				finito = 0;
				
				LCD_Clear(White);
				start(); //Menù iniziale
				
				sec = 0;
				min = 0;
				hour = 0;
				
				disable_timer(0);
				init_timer(0, 0x17D7840);
				enable_timer(0);
			}
				
			break;
			
//			case 2:
//				left = 0;
//				right = 0;
//				
//				break;
			
			default:
				break;
		}
	}
	else {
		j_select=0;
	}
	
	
	/* Joystick LEFT */
	if((LPC_GPIO1->FIOPIN & (1<<27)) == 0){
	/* Joytick Down pressed p1.27 --> using J_LEFT due to emulator issues*/
		
		j_left++;
		j_right = 0;
		
		
		switch(j_left){			
			
			case 1:
			
			//Resetto meal di nero
			LCD_DrawLine(0,280, MAX_X, 280, Black); //Linea orizzontale
			LCD_DrawLine(0,281, MAX_X, 281, Black); //Linea orizzontale per spessire
			LCD_DrawLine(0,281, MAX_X, 281, Black); //Linea orizzontale per spessire
		
			LCD_DrawLine(MAX_X/2, 282, MAX_X/2, MAX_Y, Black); //Linea verticale
			LCD_DrawLine(MAX_X/2-1, 282, MAX_X/2-1, MAX_Y, Black); //Linea verticale per spessire
			LCD_DrawLine(MAX_X/2+1, 282, MAX_X/2+1, MAX_Y, Black); //Linea verticale per spessire
			
			//Coloro meal
			LCD_DrawLine(0,280, MAX_X/2, 280, Red); //Linea orizzontale
			LCD_DrawLine(0,281, MAX_X/2, 281, Red); //Linea orizzontale per spessire
			LCD_DrawLine(0,281, MAX_X/2, 281, Red); //Linea orizzontale per spessire
		
			LCD_DrawLine(MAX_X/2, 282, MAX_X/2, MAX_Y, Red); //Linea verticale
			LCD_DrawLine(MAX_X/2-1, 282, MAX_X/2-1, MAX_Y, Red); //Linea verticale per spessire
			LCD_DrawLine(MAX_X/2+1, 282, MAX_X/2+1, MAX_Y, Red); //Linea verticale per spessire
				
			left = 1;
			right = 0;
			break;
		
			default:
			break;
		}
	}
	else
		j_left=0;
		
		
	/* Joystick RIGHT */
	if((LPC_GPIO1->FIOPIN & (1<<28)) == 0){
	/* Joytick Down pressed p1.28 --> using J_RIGHT due to emulator issues*/
		
		j_right++;
		j_left = 0;
		
		switch(j_right){			
			
			case 1:
				
			//Resetto snack di nero
			LCD_DrawLine(0,280, MAX_X, 280, Black); //Linea orizzontale
			LCD_DrawLine(0,281, MAX_X, 281, Black); //Linea orizzontale per spessire
			LCD_DrawLine(0,281, MAX_X, 281, Black); //Linea orizzontale per spessire
		
		
			LCD_DrawLine(MAX_X/2, 282, MAX_X/2, MAX_Y, Black); //Linea verticale
			LCD_DrawLine(MAX_X/2-1, 282, MAX_X/2-1, MAX_Y, Black); //Linea verticale per spessire
			LCD_DrawLine(MAX_X/2+1, 282, MAX_X/2+1, MAX_Y, Black); //Linea verticale per spessire
			
			//Coloro snack
			LCD_DrawLine(MAX_X/2,280, MAX_X, 280, Red); //Linea orizzontale
			LCD_DrawLine(MAX_X/2,281, MAX_X, 281, Red); //Linea orizzontale per spessire
			LCD_DrawLine(MAX_X/2,281, MAX_X, 281, Red); //Linea orizzontale per spessire
		
		
			LCD_DrawLine(MAX_X/2, 282, MAX_X/2, MAX_Y, Red); //Linea verticale
			LCD_DrawLine(MAX_X/2-1, 282, MAX_X/2-1, MAX_Y, Red); //Linea verticale per spessire
			LCD_DrawLine(MAX_X/2+1, 282, MAX_X/2+1, MAX_Y, Red); //Linea verticale per spessire
			
			right = 1;
			left = 0;
			break;
			
			default:
				break;
		}
	}
	else
		j_right=0;
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
