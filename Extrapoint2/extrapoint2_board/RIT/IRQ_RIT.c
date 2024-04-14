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
#include "../TouchPanel/TouchPanel.h"
#include "../adc/adc.h"


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
volatile int MEAL = 0, SNACK = 0;
volatile int coccole = 0;

extern volatile int finito;
extern volatile int panda_left;
extern volatile int i;
extern volatile int CLOSE;

void RIT_IRQHandler (void)
{	
	static int j_left = 0, j_right = 0, j_select = 0, COUNT = 0;
	
	ADC_start_conversion();
	
	
	if(CLOSE == 1) {
		if(COUNT >=10) {
		CLOSE = 0;
		COUNT = 0;
		i=0;
		disable_timer(1);
		disable_timer(2);
		}
		else
			COUNT++;
	}
	
	if(finito == 1 || panda_left == 1){	//Disabilito i timer per non farlo suonare alla fine
		j_left++;
		j_right++;
		right = 0;
		left = 0;
		select = 1;
	}
	
	if(MEAL == 1 || SNACK == 1 || coccole == 1){
		j_left++;
		j_right++;
		right = 0;
		
		left = 0;
	}else{
		j_left=0;
		j_right=0;
	}
	
	
	if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){	
		/* Joytick Select pressed p1.25*/
		/* Joytick Down pressed p1.25 --> using J_DOWN due to emulator issues*/
		
		j_select++;
		switch(j_select){
			case 1:
				
			if(left==1 && right == 0 && select == 0){ //selezionato meal
				drawFoodMenu(); //resetto di nero le linee
				MEAL = 1;
				SNACK = 0;
				left = 0; //resetto left
			}
			
			if(right==1 && left == 0 && select == 0){ //Seleziono snack
				drawFoodMenu(); //resetto di nero le linee
				SNACK = 1;
				MEAL = 0;
				right = 0;	//Resetto right
			}
			
			if(select == 1 && right == 0 && left == 0){
				disable_timer(2);
				disable_timer(1);
				disable_timer(0);
				
				LCD_Clear(White);
				start(); //Menù iniziale
			}
			
			select = 0;
			left = 0;
			right = 0;
			
			break;
			
			default:
				break;
		}
	}
	else {
		j_select=0;
	}
	
	
	/* Joystick LEFT */
	if((LPC_GPIO1->FIOPIN & (1<<27)) == 0 && finito == 0 && panda_left == 0&& coccole == 0){
	/* Joytick Down pressed p1.27 --> using J_LEFT due to emulator issues*/
		
		j_left++;
		
		switch(j_left){			
			case 1:
			left = 1;
			right = 0;
			j_left = 0;
			drawFoodMenu(); //resetto linee nere
			CLOSE=1;
			i=0;
			init_timer(2, 0x4C4A78);
			enable_timer(2);
			
			//Coloro meal
			LCD_DrawLine(0,280, MAX_X/2, 280, Red); //Linea orizzontale
			LCD_DrawLine(0,281, MAX_X/2, 281, Red); //Linea orizzontale per spessire
			LCD_DrawLine(0,281, MAX_X/2, 281, Red); //Linea orizzontale per spessire
		
			LCD_DrawLine(MAX_X/2, 282, MAX_X/2, MAX_Y, Red); //Linea verticale
			LCD_DrawLine(MAX_X/2-1, 282, MAX_X/2-1, MAX_Y, Red); //Linea verticale per spessire
			LCD_DrawLine(MAX_X/2+1, 282, MAX_X/2+1, MAX_Y, Red); //Linea verticale per spessire
			
			break;
			case 2:
				left = 0;
				right = 0;
				break;
		
			default:
			break;
		}
	}
	else {
		j_left=0;
	}
		
		
	/* Joystick RIGHT */
	if((LPC_GPIO1->FIOPIN & (1<<28)) == 0 && panda_left == 0 && finito == 0 && coccole == 0){
	/* Joytick Down pressed p1.28 --> using J_RIGHT due to emulator issues*/
		
		j_right++;
		
		switch(j_right){			
			case 1:
			
			right = 1;
			left = 0;
			
			drawFoodMenu();
			CLOSE=1;
			j_right = 0;
			i=0;
			init_timer(2, 0x4C4A78);
			enable_timer(2);
			
			
			//Coloro snack
			LCD_DrawLine(MAX_X/2,280, MAX_X, 280, Red); //Linea orizzontale
			LCD_DrawLine(MAX_X/2,281, MAX_X, 281, Red); //Linea orizzontale per spessire
			LCD_DrawLine(MAX_X/2,281, MAX_X, 281, Red); //Linea orizzontale per spessire
		
			LCD_DrawLine(MAX_X/2, 282, MAX_X/2, MAX_Y, Red); //Linea verticale
			LCD_DrawLine(MAX_X/2-1, 282, MAX_X/2-1, MAX_Y, Red); //Linea verticale per spessire
			LCD_DrawLine(MAX_X/2+1, 282, MAX_X/2+1, MAX_Y, Red); //Linea verticale per spessire
			
			break;
			case 2:
				left = 0;
			right = 0;
			break;
			
			default:
				break;
		}
	}
	else {
		j_right=0;
	}
	
	
	//Controllo se tocco
		if(getDisplayPoint(&display, Read_Ads7846(), &matrix ) && finito == 0 && MEAL == 0 && SNACK == 0){
			if( (display.y > 100 && display.y < 279) && (display.x >= 40 && display.x <= 220) ){
				//drawFoodMenu(); //resetto linee nere
				coccole = 1;
			}
		}
	
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
