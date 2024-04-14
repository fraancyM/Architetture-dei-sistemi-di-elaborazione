/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <string.h>
#include "lpc17xx.h"
#include "timer.h"
#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"
#include "../draw.h"
#include "../adc/adc.h"

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

int sec=0, min=0, hour=0;
volatile int sec_coccole = 0;
volatile int CLOSE = 0;
volatile int i=0;
volatile int n = 0;

extern volatile int count_meal; //numero di barre
extern volatile int count_snack; //numero di barre

extern volatile int finito;
extern volatile int panda_left;
extern volatile int coccole;
extern volatile int MEAL, SNACK;
extern volatile int left, right;
extern volatile int volume;


void TIMER0_IRQHandler (void) //Timer0 per l'age, batterie e animazioni
{
	sec++;
	
	if(volume == 0){
		drawVol(0);
	}else if (volume == 400){
		drawVol(1);
	}else if(volume == 800){
		drawVol(2);
	}else if(volume == 1200){
		drawVol(3);
	}
	
	while(sec>59){
	sec-=60;
	min++;
	}
	
	while(min>59){
		min-=60;
		hour++;
	}

	
	//Vita esaurita
	if(count_meal == 0 || count_snack == 0)
		panda_left = 1;
	
	if(panda_left==1){
		if(finito){
			n=0;
			i=0;
		}
		
		if(n==0){
			disable_timer(2); //Se stava già suonando deve fermarsi
			disable_timer(1);
			i=0;
			init_timer(2, 0x4C5248); //   con 18 note : 0x41EB00   altrimenti con do re mi fa 0xE4D608
			enable_timer(2);
		}
		PandaRight(n);
		n++;
		
	}
	else {
	
	//Sta mangiando meal
	if(MEAL == 1 && SNACK == 0 && finito == 0 && coccole == 0){
		//Quando inizia a mangiare musica	
		if(n==0){
			i=0;
			
			reset_timer(2);
			init_timer(2, 0x35FFFF);
			enable_timer(2);
		}
			
		PandaMeal(n);
		n++;
		drawStatusMenu3(sec, min, hour);

			if(n==3){ //Ho finito l'animazione, resetto le variabili
				n=0; 
				i = 0;
				MEAL = 0; 
				
				//reset_timer(2); 
				disable_timer(2);
				//reset_timer(1);
				disable_timer(1);
			}
	}
	else { // sta mangiando snack
		if(SNACK ==1 && MEAL == 0 && finito == 0 && coccole == 0){
			//Quando inizia a mangiare musica
			if(n==0){
				i=0;
				reset_timer(2);
				init_timer(2, 0x35FFFF);
				enable_timer(2);
			}
			PandaSnack(n);
			n++;
			drawStatusMenu3(sec, min, hour);
			
			if(n==3){
				n=0;
				i = 0;
				SNACK = 0;
				CLOSE = 0;
				
				disable_timer(2);
				reset_timer(1);
			}
		}
	}
	
	//Se non sta mangiando, può esserci l'animazione base + coccole
	if(MEAL == 0 && SNACK == 0 && finito == 0){
		
		if(sec % 2 == 0)
			drawStatusMenu(sec, min, hour); //Stampo il timer vita aggiornato
		else
			drawStatusMenu2(sec, min, hour); //Stampo il timer vita aggiornato
		
		
		//Disegno coccole
		if(finito == 0 && coccole == 1){
			if(n==0){ //inizio animazione coccole
				i=0;
				init_timer(2, 0x4C4A78); 
				enable_timer(2);
			}
			
			//Disegno cuori per le coccole
			PandaCuddles(n);
			n++;
			if(sec_coccole == 3){
				n=0;
				sec_coccole=0;
			}
		}
		
	}
}
	if(finito == 1){
		sec = 0;
		min = 0;
		hour = 0;
		
		finito = 0;
		n = 0;
	}
	
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

uint16_t SinTable[45] =
{
    410, 467, 523, 576, 627, 673, 714, 749, 778,
    799, 813, 819, 817, 807, 789, 764, 732, 694, 
    650, 602, 550, 495, 438, 381, 324, 270, 217,
    169, 125, 87 , 55 , 30 , 12 , 2  , 0  , 6  ,   
    20 , 41 , 70 , 105, 146, 193, 243, 297, 353
};

void TIMER1_IRQHandler (void) //Timer per il suono
{
	static int ticks = 0;
	//DAC management
	LPC_DAC->DACR = (volume*SinTable[ticks]/1000)<<6;
	ticks++;
	if(ticks==45)
		ticks = 0;
	
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}


const int nota_meal[14] = {1684,0,1684, 0, 1684, 0, 2124, 1684, 0, 1417,1417, 0, 2834, 2834}; //e e 0 e 0 c e 0 g 0 g super mario
const int nota_snack[14] = {1684,0,1684, 0, 1684, 0, 2124, 1684, 0, 1417,1417, 0, 2834, 2834}; //super mario

const int nota_cocc[9] = {2120, 1684, 1417, 2120, 1684, 1417, 1417, 1684, 2120}; //savage love coccole

const int nota_left[1] = {2124}; //do
const int nota_right[1] = {2124}; //do

//const int nota_finito[18] = {2124, 1890, 0, 2124, 1890, 0, 2124, 1890, 1684, 0, 2124, 1890, 0, 2124, 1890, 1684, 1890, 0 };
//const int nota_finito[5] = {2124, 1890, 1684, 1592, 1417}; //do re mi fa sol
const int nota_finito[11] = {2124, 1786, 1592, 1502, 1592, 1786, 2124, 0, 2364, 1890, 2124};
	
void TIMER2_IRQHandler (void) //Timer2 per il suono
{
	disable_timer(1);
	reset_timer(1);
	
	if(panda_left == 1){ // panda va via
			init_timer(1, nota_finito[i]);
			enable_timer(1);
	}
		
	if(coccole == 1){ //coccole
		if(i<=9){
			init_timer(1, nota_cocc[i]);
			enable_timer(1);
		}
	}
	
	if(MEAL == 1){ //meal
		if(i<=14){
			init_timer(1, nota_meal[i]);
			enable_timer(1);
		}
	}
	
	if(SNACK == 1){ //snack
			if(i<=14){
				init_timer(1, nota_snack[i]);
				enable_timer(1);
			}
	}
	
	if(left == 1){ //left
		if(i<=0){	
		init_timer(1, nota_left[i]);
			enable_timer(1);}
	}
	
	if(right == 1 ){ //right
			if(i<=0)
			{init_timer(1, nota_right[i]);
			enable_timer(1);}
	}
	
		
	i++; //Nota successiva
			
	LPC_TIM2->IR = 1; /* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
