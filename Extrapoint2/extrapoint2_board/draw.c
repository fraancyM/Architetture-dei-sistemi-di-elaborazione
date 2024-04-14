#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "TouchPanel/TouchPanel.h"
#include "timer/timer.h"
#include "draw.h"

volatile int meal; //da quanto non mangia meal
volatile int snack; //da quanto non mangia snack
volatile int count_meal; //numero di barre
volatile int count_snack; //numero di barre

volatile int finito = 0; //flag per dire se è finito tutto il gioco
volatile int panda_left = 0;

extern int coccole;
extern int sec, min, hour;
extern volatile int sec_coccole;
extern volatile int select, MEAL, SNACK;
extern volatile int n;
extern volatile int CLOSE, i;

void start(){
	
	init_timer(0, 0x17D7840);
	enable_timer(0); //age & control menu food
	reset_timer(1);
	reset_timer(2);
	
	meal=5;
	snack=5;
	count_meal=4; // barre di vita
	count_snack=4;
	
	n=0;
	CLOSE = 0;
	select = 0;
	MEAL = 0;
	SNACK = 0;
	coccole = 0;
	
	panda_left = 0;
	
	sec = 0;
	min = 0;
	hour = 0;
				
	drawFoodMenu();
	drawStatusMenu(0,0,0);
}

void draw_battery_S(int val){
	
	switch(val){
		case 0: 
			battery_Satiety_zero();
			LCD_DrawRectangle(206,73,10,20, White);
			LCD_DrawRectangle(192,73,10,20, White);
			LCD_DrawRectangle(177,73,10,20, White);
			LCD_DrawRectangle(163,73,10,20, White);
			break;
		case 1: 
			battery_Satiety_one();
			LCD_DrawRectangle(206,73,10,20, White);
			LCD_DrawRectangle(192,73,10,20, White);
			LCD_DrawRectangle(177,73,10,20, White);
			break;
		case 2: 
			battery_Satiety_two();
			LCD_DrawRectangle(206,73,10,20, White);
			LCD_DrawRectangle(192,73,10,20, White);
			break;
		case 3: 
			battery_Satiety_three();
			LCD_DrawRectangle(206,73,10,20, White); //Ultima barra verde diventa bianca
			break;
		case 4: 
			battery_Satiety_full();
			break;
	}
}

void draw_battery_H(int val){
	switch(val){
		case 0: 
			battery_Happiness_zero();
			LCD_DrawRectangle(65,73,10,20, White);
			LCD_DrawRectangle(51,73,10,20, White);
			LCD_DrawRectangle(37,73,10,20, White);
			LCD_DrawRectangle(23,73,10,20, White); //rettangolo rosso
			break;
		case 1: 
			battery_Happiness_one();
			LCD_DrawRectangle(65,73,10,20, White);
			LCD_DrawRectangle(51,73,10,20, White);
			LCD_DrawRectangle(37,73,10,20, White);
			break;
		case 2: 
			battery_Happiness_two();
			LCD_DrawRectangle(65,73,10,20, White);
			LCD_DrawRectangle(51,73,10,20, White);
			break;
		case 3: 
			battery_Happiness_three();
			LCD_DrawRectangle(65,73,10,20, White); //Rettangolo verde diventa bianco
			break;
		case 4: 
			battery_Happiness_full();
			break;
	}
}

void PandaMeal(int n){
	
	switch(n){
		case 0:
			drawMeal();
			LCD_DrawRectangle(80,100,100,180,White);
			drawTamagotchi(90, 165);
			break;
		case 1:
			LCD_DrawRectangle(50,100,100,180,White);
			drawTamagotchi(40, 165);
			drawCuore(100, 160, Magenta);
			break;
		case 2:
			LCD_DrawRectangle(2,100,200,180,White);
		
			if(count_meal<4)
				count_meal++;
			
			meal = 5;
			
			break;
			
		default:
			break;
	}
}


void PandaSnack(int n){
	
		switch(n){
			case 0:
				drawSnack();
				LCD_DrawRectangle(80,100,100,180,White); //Rettangolo bianco centrale
				drawTamagotchiRight(120, 165);
				break;
			case 1:
				LCD_DrawRectangle(80,100,100,180,White);
				drawTamagotchiRight(170, 165);
				drawCuore(100, 160, Magenta);
			break;
		case 2:
				LCD_DrawRectangle(100,100,MAX_X,180,White);	
			
				if(count_snack<4)
					count_snack++;
			
				snack = 5;
			
			break;
		default:
			break;
	}

}

void PandaCuddles(int n){
	
		switch(n){
			case 0:
				drawCuore(40, 230, Red);
				drawCuore(180, 140, Red);
				drawCuore(35, 150, Red);
				drawCuore(190, 200, Red);
				
				sec_coccole++;
				break;
			case 1:
				drawCuore(40, 230, Red);
				drawCuore(180, 140, Red);
				drawCuore(35, 150, Red);
				drawCuore(190, 200, Red);
				
				sec_coccole++;
			break;
			
		case 2:
				//Cancello i cuori
				LCD_DrawRectangle(40,230,40,40,White);
				LCD_DrawRectangle(180,140,40,40,White);
				LCD_DrawRectangle(35,150,40,40,White);
				LCD_DrawRectangle(190,200,40,40,White);
				
				sec_coccole++;
			
				if(count_snack<4)
					count_snack++;
			
				snack = 5;
				
				n = 0;
				coccole = 0;
				i = 0;
				CLOSE = 0;
			break;
		default:
			break;
	}
			
}

void drawReset(){
	
	LCD_Clear(Blue);
	LCD_Clear(White);
	GUI_Text(80, 120, (uint8_t *) "Buonanotte", Black, White);
	
	drawPandaSteso(120, 165);
	
	GUI_Text(100, 290, (uint8_t *) "Reset", Black, White);
	
	LCD_DrawLine(0,280, MAX_X, 280, Red);
	LCD_DrawLine(0,281, MAX_X, 281, Red);
	LCD_DrawLine(0,282, MAX_X, 282, Red);

}


void battery_Happiness_zero(){
	
	//Linea superiore
	LCD_DrawLine(20, 68, 80, 68, Black);
	LCD_DrawLine(20, 69, 80, 69, Black);
	LCD_DrawLine(20, 70, 80, 70, Black);
	
	//Linea sinistra
	LCD_DrawLine(18, 71, 18, 95, Black);
	LCD_DrawLine(17, 71, 17, 95, Black);
	LCD_DrawLine(16, 71, 16, 95, Black);

	//Nessun rettangolo dentro
	
	//Linea in basso
	LCD_DrawLine(20, 96, 80, 96, Black);
	LCD_DrawLine(20, 97, 80, 97, Black);
	LCD_DrawLine(20, 98, 80, 98, Black);
	
	//Linea a destra
	LCD_DrawLine(81, 71, 81, 95, Black);
	LCD_DrawLine(82, 71, 82, 95, Black);
	LCD_DrawLine(83, 71, 83, 95, Black);
	
	//Pezzettino batteria
	LCD_DrawLine(84, 78, 84, 88, Black);
	LCD_DrawLine(85, 78, 85, 88, Black);
	LCD_DrawLine(86, 78, 86, 88, Black);
	
}

void battery_Happiness_one(){
	
	//Linea superiore
	LCD_DrawLine(20, 68, 80, 68, Black);
	LCD_DrawLine(20, 69, 80, 69, Black);
	LCD_DrawLine(20, 70, 80, 70, Black);
	
	//Linea sinistra
	LCD_DrawLine(18, 71, 18, 95, Black);
	LCD_DrawLine(17, 71, 17, 95, Black);
	LCD_DrawLine(16, 71, 16, 95, Black);

	//Rettangoli colorati
	LCD_DrawRectangle(23,73,10,20, Red); 
	
	
	//Linea in basso
	LCD_DrawLine(20, 96, 80, 96, Black);
	LCD_DrawLine(20, 97, 80, 97, Black);
	LCD_DrawLine(20, 98, 80, 98, Black);
	
	//Linea a destra
	LCD_DrawLine(81, 71, 81, 95, Black);
	LCD_DrawLine(82, 71, 82, 95, Black);
	LCD_DrawLine(83, 71, 83, 95, Black);
	
	//Pezzettino batteria
	LCD_DrawLine(84, 78, 84, 88, Black);
	LCD_DrawLine(85, 78, 85, 88, Black);
	LCD_DrawLine(86, 78, 86, 88, Black);

	
}

void battery_Happiness_two(){
	
	//Linea superiore
	LCD_DrawLine(20, 68, 80, 68, Black);
	LCD_DrawLine(20, 69, 80, 69, Black);
	LCD_DrawLine(20, 70, 80, 70, Black);
	
	//Linea sinistra
	LCD_DrawLine(18, 71, 18, 95, Black);
	LCD_DrawLine(17, 71, 17, 95, Black);
	LCD_DrawLine(16, 71, 16, 95, Black);

	//Rettangoli colorati
	LCD_DrawRectangle(23,73,10,20, Red); 
	LCD_DrawRectangle(37,73,10,20, Yellow);
	
	//Linea in basso
	LCD_DrawLine(20, 96, 80, 96, Black);
	LCD_DrawLine(20, 97, 80, 97, Black);
	LCD_DrawLine(20, 98, 80, 98, Black);
	
	//Linea a destra
	LCD_DrawLine(81, 71, 81, 95, Black);
	LCD_DrawLine(82, 71, 82, 95, Black);
	LCD_DrawLine(83, 71, 83, 95, Black);
	
	//Pezzettino batteria
	LCD_DrawLine(84, 78, 84, 88, Black);
	LCD_DrawLine(85, 78, 85, 88, Black);
	LCD_DrawLine(86, 78, 86, 88, Black);
	
}

void battery_Happiness_three(){
	
	//Linea superiore
	LCD_DrawLine(20, 68, 80, 68, Black);
	LCD_DrawLine(20, 69, 80, 69, Black);
	LCD_DrawLine(20, 70, 80, 70, Black);
	
	//Linea sinistra
	LCD_DrawLine(18, 71, 18, 95, Black);
	LCD_DrawLine(17, 71, 17, 95, Black);
	LCD_DrawLine(16, 71, 16, 95, Black);

	//Rettangoli colorati
	LCD_DrawRectangle(23,73,10,20, Red); 
	LCD_DrawRectangle(37,73,10,20, Yellow);
	LCD_DrawRectangle(51,73,10,20, Green);	
	
	//Linea in basso
	LCD_DrawLine(20, 96, 80, 96, Black);
	LCD_DrawLine(20, 97, 80, 97, Black);
	LCD_DrawLine(20, 98, 80, 98, Black);
	
	//Linea a destra
	LCD_DrawLine(81, 71, 81, 95, Black);
	LCD_DrawLine(82, 71, 82, 95, Black);
	LCD_DrawLine(83, 71, 83, 95, Black);
	
	//Pezzettino batteria
	LCD_DrawLine(84, 78, 84, 88, Black);
	LCD_DrawLine(85, 78, 85, 88, Black);
	LCD_DrawLine(86, 78, 86, 88, Black);
}

void battery_Happiness_full(){
	
	//Linea superiore
	LCD_DrawLine(20, 68, 80, 68, Black);
	LCD_DrawLine(20, 69, 80, 69, Black);
	LCD_DrawLine(20, 70, 80, 70, Black);
	
	//Linea sinistra
	LCD_DrawLine(18, 71, 18, 95, Black);
	LCD_DrawLine(17, 71, 17, 95, Black);
	LCD_DrawLine(16, 71, 16, 95, Black);

	//Rettangoli colorati
	LCD_DrawRectangle(23,73,10,20, Red); 
	LCD_DrawRectangle(37,73,10,20, Yellow);
	LCD_DrawRectangle(51,73,10,20, Green);
	LCD_DrawRectangle(65,73,10,20, Green);
	
	//Linea in basso
	LCD_DrawLine(20, 96, 80, 96, Black);
	LCD_DrawLine(20, 97, 80, 97, Black);
	LCD_DrawLine(20, 98, 80, 98, Black);
	
	//Linea a destra
	LCD_DrawLine(81, 71, 81, 95, Black);
	LCD_DrawLine(82, 71, 82, 95, Black);
	LCD_DrawLine(83, 71, 83, 95, Black);
	
	//Pezzettino batteria
	LCD_DrawLine(84, 78, 84, 88, Black);
	LCD_DrawLine(85, 78, 85, 88, Black);
	LCD_DrawLine(86, 78, 86, 88, Black);
}





void drawSnack(){
	
	int x0 = 180;
	int y0 = 240;
	int n = 2;
	
	LCD_DrawRectangle(x0+2*n,y0,4*n,n,Black);
	y0=y0+n;
	
	//2
	LCD_DrawRectangle(x0+1*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+5*n,y0,n,n,Green);
	LCD_DrawRectangle(x0+6*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+8*n,y0,3*n,n,Green);
	y0=y0+n;
	
	//3
	LCD_DrawRectangle(x0+3*n,y0,4*n,n,Green);
	LCD_DrawRectangle(x0+7*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+8*n,y0,5*n,n,Green);
	y0=y0+n;
	
	//4
	LCD_DrawRectangle(x0+1*n,y0,10*n,n,Green);
	LCD_DrawRectangle(x0+11*n,y0,n,n,Red);
	LCD_DrawRectangle(x0+12*n,y0,2*n,n,Green);
	y0=y0+n;
	
	//5
	LCD_DrawRectangle(x0,y0,2*n,n,Green);
	LCD_DrawRectangle(x0+2*n,y0,n,n,Red);
	LCD_DrawRectangle(x0+3*n,y0,n,n,Green);
	LCD_DrawRectangle(x0+4*n,y0,2*n,n,Red);
	LCD_DrawRectangle(x0+6*n,y0,2*n,n,Green);
	LCD_DrawRectangle(x0+8*n,y0,n,n,Red);
	LCD_DrawRectangle(x0+10*n,y0,n,n,Green);
	LCD_DrawRectangle(x0+11*n,y0,2*n,n,Red);
	LCD_DrawRectangle(x0+13*n,y0,n,n,Green);
	y0=y0+n;
	
	//6
	LCD_DrawRectangle(x0,y0,n,n,Green);
	LCD_DrawRectangle(x0+1*n,y0,5*n,n,Red);
	LCD_DrawRectangle(x0+6*n,y0,n,n,Green);
	LCD_DrawRectangle(x0+7*n,y0,4*n,n,Red);
	LCD_DrawRectangle(x0+12*n,y0,2*n,n,Red);
	LCD_DrawRectangle(x0+14*n,y0,n,n,Green);
	y0=y0+n;
	
	//7
	LCD_DrawRectangle(x0+1*n,y0,3*n,n,Red);
	LCD_DrawRectangle(x0+4*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+5*n,y0,5*n,n,Red);
	LCD_DrawRectangle(x0+10*n,y0,1*n,n,Black);
	LCD_DrawRectangle(x0+11*n,y0,3*n,n,Red);
	y0=y0+n;
	
	//8
	LCD_DrawRectangle(x0+1*n,y0,n,n,Red);
	LCD_DrawRectangle(x0+2*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+3*n,y0,4*n,n,Red);
	LCD_DrawRectangle(x0+7*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+8*n,y0,4*n,n,Red);
	LCD_DrawRectangle(x0+12*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+13*n,y0,n,n,Red);
	y0=y0+n;
	
	//9
	LCD_DrawRectangle(x0+1*n,y0,4*n,n,Red);
	LCD_DrawRectangle(x0+5*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+6*n,y0,6*n,n,Red);
	LCD_DrawRectangle(x0+13*n,y0,1*n,n,Red);
	y0=y0+n;
	
	//10
	LCD_DrawRectangle(x0+2*n,y0,7*n,n,Red);
	LCD_DrawRectangle(x0+9*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+10*n,y0,3*n,n,Red);
	y0=y0+n;	
	
	//11
	LCD_DrawRectangle(x0+2*n,y0,11*n,n,Red);
	y0=y0+n;
	
	//12
	LCD_DrawRectangle(x0+3*n,y0,n,n,Red);
	LCD_DrawRectangle(x0+4*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+5*n,y0,2*n,n,Red);
	LCD_DrawRectangle(x0+7*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+8*n,y0,4*n,n,Red);
	y0=y0+n;
	
	//13
	LCD_DrawRectangle(x0+5*n,y0,6*n,n,Red);
	y0=y0+n;

	//14
	LCD_DrawRectangle(x0+5*n,y0,5*n,n,Red);
	y0=y0+n;

	//15
	LCD_DrawRectangle(x0+6*n,y0,2*n,n,Red);
	y0=y0+n;
	
}



void drawCuore(int x0, int y0, int color){
	
//	int x0 = 100;
//	int y0 = 160;
	int n = 3;
	
	LCD_DrawRectangle(x0+1*n,y0,2*n,n,Black);
	LCD_DrawRectangle(x0+6*n,y0,2*n,n,Black);
	y0=y0+n;
	
	LCD_DrawRectangle(x0,y0,n,n,Black);
	LCD_DrawRectangle(x0+1*n,y0,2*n,n,color);
	LCD_DrawRectangle(x0+3*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+5*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+6*n,y0,2*n,n,color);
	LCD_DrawRectangle(x0+8*n,y0,n,n,Black);
	y0=y0+n;
	
	LCD_DrawRectangle(x0,y0,n,n,Black);
	LCD_DrawRectangle(x0+1*n,y0,3*n,n,color);
	LCD_DrawRectangle(x0+4*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+5*n,y0,3*n,n,color);
	LCD_DrawRectangle(x0+8*n,y0,n,n,Black);
	y0=y0+n;
	
	LCD_DrawRectangle(x0,y0,n,n,Black);
	LCD_DrawRectangle(x0+1*n,y0,7*n,n,color);
	LCD_DrawRectangle(x0+8*n,y0,n,n,Black);
	y0=y0+n;
	
	LCD_DrawRectangle(x0+1*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+2*n,y0,5*n,n,color);
	LCD_DrawRectangle(x0+7*n,y0,n,n,Black);
	y0=y0+n;
	
	LCD_DrawRectangle(x0+2*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+3*n,y0,3*n,n,color);
	LCD_DrawRectangle(x0+6*n,y0,n,n,Black);
	y0=y0+n;
	
	LCD_DrawRectangle(x0+3*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+4*n,y0,n,n,color);
	LCD_DrawRectangle(x0+5*n,y0,n,n,Black);
	y0=y0+n;
	
	LCD_DrawRectangle(x0+4*n,y0,n,n,Black);
	y0=y0+n;
	
}



void battery_Satiety_zero(){
	
	//Linea superiore
	LCD_DrawLine(160, 68, 220, 68, Black);
	LCD_DrawLine(160, 69, 220, 69, Black);
	LCD_DrawLine(160, 70, 220, 70, Black);
	
	//Linea sinistra
	LCD_DrawLine(158, 71, 158, 95, Black);
	LCD_DrawLine(157, 71, 157, 95, Black);
	LCD_DrawLine(156, 71, 156, 95, Black);

	//Nessun rettangolo usato
	
	//Linea in basso
	LCD_DrawLine(160, 96, 220, 96, Black);
	LCD_DrawLine(160, 97, 220, 97, Black);
	LCD_DrawLine(160, 98, 220, 98, Black);
	
	//Linea a destra
	LCD_DrawLine(221, 71, 221, 95, Black);
	LCD_DrawLine(222, 71, 222, 95, Black);
	LCD_DrawLine(223, 71, 223, 95, Black);
	
	LCD_DrawLine(224, 78, 224, 88, Black);
	LCD_DrawLine(225, 78, 225, 88, Black);
	LCD_DrawLine(226, 78, 226, 88, Black);
}

void battery_Satiety_one(){
	battery_Satiety_zero();
	LCD_DrawRectangle(163,73,10,20, Red);
}

void battery_Satiety_two(){
	battery_Satiety_one();
	LCD_DrawRectangle(177,73,10,20, Yellow);
}

void battery_Satiety_three(){
	battery_Satiety_two();
	LCD_DrawRectangle(192,73,10,20, Green);
}
void battery_Satiety_full(){
	
	//Linea superiore
	LCD_DrawLine(160, 68, 220, 68, Black);
	LCD_DrawLine(160, 69, 220, 69, Black);
	LCD_DrawLine(160, 70, 220, 70, Black);
	
	//Linea sinistra
	LCD_DrawLine(158, 71, 158, 95, Black);
	LCD_DrawLine(157, 71, 157, 95, Black);
	LCD_DrawLine(156, 71, 156, 95, Black);
	
	//LCD_DrawRectangle(163,73,40,20, Blue);
	LCD_DrawRectangle(163,73,10,20, Red);
	LCD_DrawRectangle(177,73,10,20, Yellow);
	LCD_DrawRectangle(192,73,10,20, Green);
	LCD_DrawRectangle(206,73,10,20, Green);
	
	//Linea in basso
	LCD_DrawLine(160, 96, 220, 96, Black);
	LCD_DrawLine(160, 97, 220, 97, Black);
	LCD_DrawLine(160, 98, 220, 98, Black);
	
	//Linea a destra
	LCD_DrawLine(221, 71, 221, 95, Black);
	LCD_DrawLine(222, 71, 222, 95, Black);
	LCD_DrawLine(223, 71, 223, 95, Black);
	
	LCD_DrawLine(224, 78, 224, 88, Black);
	LCD_DrawLine(225, 78, 225, 88, Black);
	LCD_DrawLine(226, 78, 226, 88, Black);
}



void drawStatusMenu(int sec, int min, int hour){
	
	char time_in_char[32] = "";	
	
	sprintf(time_in_char, "Age: %02d:%02d:%02d ", hour, min,	sec);
	GUI_Text(MAX_X/4, 15, (uint8_t *) time_in_char, Black, White);

	GUI_Text(20, 50, (uint8_t *) "Happiness", Black, White);
	GUI_Text(160, 50, (uint8_t *) "Satiety", Black, White);
	
	//controllo se ha mangiato meal
	if(snack<=0){
		if((snack%5)==0){
			count_snack--;
		}
	}
	
	//controllo se ha mangiato snack
	if(meal<=0){
		if((meal%5)==0){
			count_meal--;
		}
	}
	
	//disegno batterie
	draw_battery_H(count_snack);
	draw_battery_S(count_meal);

	meal--;
	snack--;
	
	//drawFoodMenu();
	
	drawTamagotchi(MAX_X/2, 165);
	
	//Vita esaurita
	if(count_meal == 0 || count_snack == 0){
		panda_left = 1;
	}
		
}


void drawStatusMenu2(int sec, int min, int hour){
	
	char time_in_char[32] = "";
	
	sprintf(time_in_char, "Age: %02d:%02d:%02d ", hour, min,	sec);
	GUI_Text(MAX_X/4, 15, (uint8_t *) time_in_char, Black, White);

	GUI_Text(20, 50, (uint8_t *) "Happiness", Black, White);
	GUI_Text(160, 50, (uint8_t *) "Satiety", Black, White);
	
	
	//controllo se ha mangiato meal
	if(snack<=0){
		if((snack%5)==0){
			count_snack--;
		}
	}
	
	//controllo se ha mangiato snack
	if(meal<=0){
		if((meal%5)==0){
			count_meal--;
		}
	}
	
	//disegno batterie
	draw_battery_H(count_snack);
	draw_battery_S(count_meal);

	meal--;
	snack--;
	
	//drawFoodMenu();
	
	drawTamagotchi_2(MAX_X/2, 165);
	
	//Vita esaurita
	if(count_meal == 0 || count_snack == 0){
		panda_left = 1;
	}
		
}




void drawStatusMenu3(int sec, int min, int hour){
	
	char time_in_char[32] = "";
	
	sprintf(time_in_char, "Age: %02d:%02d:%02d ", hour, min,	sec);
	GUI_Text(MAX_X/4, 15, (uint8_t *) time_in_char, Black, White);

	GUI_Text(20, 50, (uint8_t *) "Happiness", Black, White);
	GUI_Text(160, 50, (uint8_t *) "Satiety", Black, White);
	
	
	//controllo se ha mangiato meal
	if(snack<=0){
		if((snack%5)==0){
			count_snack--;
		}
	}
	
	//controllo se ha mangiato snack
	if(meal<=0){
		if((meal%5)==0){
			count_meal--;
		}
	}
	
	//disegno batterie
	draw_battery_H(count_snack);
	draw_battery_S(count_meal);

	meal--;
	snack--;
	
	//drawFoodMenu();
	
	//Vita esaurita
	if(count_meal == 0 || count_snack == 0){
		finito = 1;
		panda_left = 1;
	}
		
}

void drawPandaSteso(int x0, int y0){
	
	//Disegno del panda steso
	
	int n = 3;

	//1
	LCD_DrawRectangle(x0,y0,5*n,n,Black); 
	LCD_DrawRectangle(x0+6*n,y0,4*n,n,Black);
	LCD_DrawRectangle(x0+18*n,y0,4*n,n,Black); //zeta
	y0 = y0+n;
	
	//2
	LCD_DrawRectangle(x0-7*n,y0,3*n,n,Black);
	LCD_DrawRectangle(x0-3*n,y0,3*n,n,Black);
	LCD_DrawRectangle(x0+5*n,y0,6*n,n,Black);
	LCD_DrawRectangle(x0+21*n,y0,n,n,Black); //zeta
	y0 = y0+n;
	
	//3
	LCD_DrawRectangle(x0-8*n,y0,5*n,n,Black);
	LCD_DrawRectangle(x0+8*n,y0,3*n,n,Black);
	LCD_DrawRectangle(x0+20*n,y0,n,n,Black); //zeta
	y0 = y0+n;
	
	//4
	LCD_DrawRectangle(x0-9*n,y0,5*n,n,Black);
	LCD_DrawRectangle(x0+9*n,y0,2*n,n,Black);
	LCD_DrawRectangle(x0+19*n,y0,n,n,Black);
	y0 = y0+n;
	
	//5
	LCD_DrawRectangle(x0-9*n,y0,4*n,n,Black);
	LCD_DrawRectangle(x0+10*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+14*n,y0,3*n,n,Black); //zeta
	LCD_DrawRectangle(x0+18*n,y0,n,n,Black); //zeta
	y0 = y0+n;
	
	//6
	LCD_DrawRectangle(x0-9*n,y0,3*n,n,Black);
	LCD_DrawRectangle(x0+10*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+16*n,y0,n,n,Black); //zeta
	LCD_DrawRectangle(x0+18*n,y0,4*n,n,Black); //zeta
	y0 = y0+n;
	
	//7
	LCD_DrawRectangle(x0-8*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+11*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+15*n,y0,n,n,Black); //zeta
	y0 = y0+n;
	
	//8
	LCD_DrawRectangle(x0-16*n,y0,3*n,n,Black);
	LCD_DrawRectangle(x0-9*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+11*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+14*n,y0,n,n,Black);
	y0 = y0+n;
	
	//9
	LCD_DrawRectangle(x0-17*n,y0,5*n,n,Black);
	LCD_DrawRectangle(x0-9*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-3*n,y0,4*n,n,Black);
	LCD_DrawRectangle(x0+8*n,y0,4*n,n,Black);
	LCD_DrawRectangle(x0+14*n,y0,3*n,n,Black); //zeta
	y0 = y0+n;
	
	//10
	LCD_DrawRectangle(x0-17*n,y0,8*n,n,Black);
	LCD_DrawRectangle(x0-4*n,y0,6*n,n,Black);
	LCD_DrawRectangle(x0+7*n,y0,5*n,n,Black);
	y0 = y0+n;
	
	//riga 11
	LCD_DrawRectangle(x0-17*n,y0,5*n,n,Black);
	LCD_DrawRectangle(x0-10*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-5*n,y0,8*n,n,Black);
	LCD_DrawRectangle(x0+7*n,y0,6*n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-16*n,y0,3*n,n,Black);
	LCD_DrawRectangle(x0-10*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-5*n,y0,8*n,n,Black);
	LCD_DrawRectangle(x0+7*n,y0,7*n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-15*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-10*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-5*n,y0,8*n,n,Black);
	LCD_DrawRectangle(x0+8*n,y0,6*n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-16*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-10*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-4*n,y0,6*n,n,Black);
	LCD_DrawRectangle(x0+4*n,y0,3*n,n,Black);
	LCD_DrawRectangle(x0+9*n,y0,3*n,n,Black);
	LCD_DrawRectangle(x0+14*n,y0,n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-16*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-10*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-3*n,y0,4*n,n,Black);
	LCD_DrawRectangle(x0+5*n,y0,2*n,n,Black);
	LCD_DrawRectangle(x0+14*n,y0,n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-17*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-11*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+13*n,y0,n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-19*n,y0,3*n,n,Black);
	LCD_DrawRectangle(x0-11*n,y0,4*n,n,Black);
	LCD_DrawRectangle(x0+12*n,y0,2*n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-20*n,y0,4*n,n,Black);
	LCD_DrawRectangle(x0-11*n,y0,10*n,n,Black);
	LCD_DrawRectangle(x0+11*n,y0,4*n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-20*n,y0,5*n,n,Black);
	LCD_DrawRectangle(x0-10*n,y0,12*n,n,Black);
	LCD_DrawRectangle(x0+9*n,y0,6*n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-20*n,y0,6*n,n,Black);
	LCD_DrawRectangle(x0-10*n,y0,12*n,n,Black);
	LCD_DrawRectangle(x0+6*n,y0,9*n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-19*n,y0,33*n,n,Black);
	y0 = y0+n;
	
}



void PandaRight(int n){
	
	//Il panda va verso destra
	
	switch(n){
		case 0:
			LCD_DrawRectangle(80,100,100,175,White);
			drawTamagotchiRight(MAX_X/2, 165);
			break;
		case 1:
			LCD_DrawRectangle(80,100,100,175,White);
			drawTamagotchiRight(160, 165);
			break;
		case 2:
			LCD_DrawRectangle(120,100,100,175,White);
			drawTamagotchiRight(220,165);
			break;
		default:
			break;
	}
	
	if(n==3){
		
		disable_timer(0);
		disable_timer(2);
		disable_timer(1);
		drawReset();
		n=0;
	}
}


void drawTamagotchi(int x0, int y0){
	
	int y=y0;
	int n = 3;

	LCD_DrawRectangle(x0,y0,8*n,n,Black); //Riga sopra
	LCD_DrawRectangle(x0-5*n,y0,n,n,Black); //Riga sopra
	
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-9*n,y0,3*n,n,Black);
	LCD_DrawRectangle(x0-5*n,y0,1*n,n,Black);
	LCD_DrawRectangle(x0-3*n,y0,3*n,n,Black);
	LCD_DrawRectangle(x0+8*n,y0,3*n,n,Black);
	LCD_DrawRectangle(x0+14*n,y0,3*n,n,Black);
	
	y0 = y0+n;
	
	//terza riga
	LCD_DrawRectangle(x0-10*n,y0,7*n,n,Black);
	LCD_DrawRectangle(x0+11*n,y0,7*n,n,Black);
	y0 = y0+n;
	
	//Quarta riga
	LCD_DrawRectangle(x0-11*n,y0,6*n,n,Black);
	LCD_DrawRectangle(x0+13*n,y0,6*n,n,Black);
	y0 = y0+n;
	
	//5
	LCD_DrawRectangle(x0-11*n,y0,5*n,n,Black);
	LCD_DrawRectangle(x0+14*n,y0,5*n,n,Black);
	y0 = y0+n;
	
	//6
	LCD_DrawRectangle(x0-11*n,y0,4*n,n,Black);
	LCD_DrawRectangle(x0+15*n,y0,4*n,n,Black);
	y0 = y0+n;
	
	//7
	LCD_DrawRectangle(x0-11*n,y0,4*n,n,Black);
	LCD_DrawRectangle(x0+16*n,y0,3*n,n,Black);
	y0 = y0+n;
	
	//8
	LCD_DrawRectangle(x0-10*n,y0,2*n,n,Black);
	LCD_DrawRectangle(x0+17*n,y0,n,n,Black);
	y0 = y0+n;
	
	//9
	LCD_DrawRectangle(x0-10*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+17*n,y0,n,n,Black);
	y0 = y0+n;
	
	//10
	LCD_DrawRectangle(x0-10*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+17*n,y0,n,n,Black);
	y0 = y0+n;
	
	//11
	LCD_DrawRectangle(x0-10*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+18*n,y0,n,n,Black);
	y0 = y0+n;
	
	//12
	LCD_DrawRectangle(x0-11*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-7*n,y0,5*n,n,Black);
	LCD_DrawRectangle(x0+9*n,y0,5*n,n,Black);
	LCD_DrawRectangle(x0+18*n,y0,n,n,Black);
	y0 = y0+n;
	
	//13
	LCD_DrawRectangle(x0-11*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-8*n,y0,7*n,n,Black);
	LCD_DrawRectangle(x0+8*n,y0,7*n,n,Black);
	LCD_DrawRectangle(x0+18*n,y0,n,n,Black);
	y0 = y0+n;
	
	//14
	LCD_DrawRectangle(x0-11*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-8*n,y0,8*n,n,Black);
	LCD_DrawRectangle(x0+8*n,y0,8*n,n,Black);
	LCD_DrawRectangle(x0+18*n,y0,n,n,Black);
	y0 = y0+n;
	
	//15
	LCD_DrawRectangle(x0-11*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-8*n,y0,3*n,n,Black);
	LCD_DrawRectangle(x0-3*n,y0,3*n,n,Black);
	LCD_DrawRectangle(x0+8*n,y0,3*n,n,Black);
	LCD_DrawRectangle(x0+13*n,y0,3*n,n,Black);
	LCD_DrawRectangle(x0+18*n,y0,n,n,Black);
	y0 = y0+n;
	
	//16
	LCD_DrawRectangle(x0-11*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-8*n,y0,2*n,n,Black);
	LCD_DrawRectangle(x0-5*n,y0,2*n,n,Black);
	LCD_DrawRectangle(x0-2*n,y0,2*n,n,Black);
	LCD_DrawRectangle(x0+18*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+2*n,y0,2*n,n,Black);
	LCD_DrawRectangle(x0+8*n,y0,2*n,n,Black);
	LCD_DrawRectangle(x0+11*n,y0,2*n,n,Black);
	LCD_DrawRectangle(x0+14*n,y0,2*n,n,Black);
	y0 = y0+n;
	
	//17
	LCD_DrawRectangle(x0-11*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-8*n,y0,8*n,n,Black);
	LCD_DrawRectangle(x0+2*n,y0,3*n,n,Black);
	LCD_DrawRectangle(x0+8*n,y0,8*n,n,Black);
	LCD_DrawRectangle(x0+18*n,y0,n,n,Black);
	y0 = y0+n;
	
	//18
	LCD_DrawRectangle(x0-11*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-8*n,y0,8*n,n,Black);
	LCD_DrawRectangle(x0+3*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+8*n,y0,8*n,n,Black);
	LCD_DrawRectangle(x0+18*n,y0,n,n,Black);
	y0 = y0+n;
	
	//19
	LCD_DrawRectangle(x0-10*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-7*n,y0,6*n,n,Black);
	LCD_DrawRectangle(x0+1*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+3*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+5*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+9*n,y0,6*n,n,Black);
	LCD_DrawRectangle(x0+17*n,y0,n,n,Black);
	
	LCD_DrawRectangle(x0-8*n,y0,1*n,n,White);
	LCD_DrawRectangle(x0+15*n,y0,1*n,n,White);

	y0 = y0+n;
	
	//20
	LCD_DrawRectangle(x0-10*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-6*n,y0,4*n,n,Black);
	LCD_DrawRectangle(x0+2*n,y0,3*n,n,Black);
	LCD_DrawRectangle(x0+10*n,y0,4*n,n,Black);
	LCD_DrawRectangle(x0+17*n,y0,n,n,Black);
	
	LCD_DrawRectangle(x0-8*n,y0,2*n,n,White);
	LCD_DrawRectangle(x0+14*n,y0,2*n,n,White);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-9*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+16*n,y0,n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-8*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+15*n,y0,n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-7*n,y0,2*n,n,Black);
	LCD_DrawRectangle(x0+13*n,y0,2*n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-5*n,y0,18*n,n,Black);
	y0 = y0+n;
	
	//Corpo
	LCD_DrawRectangle(x0-5*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-2*n,y0,12*n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-5*n,y0,4*n,n,Black);
	LCD_DrawRectangle(x0+3*n,y0,8*n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-6*n,y0,4*n,n,Black);
	LCD_DrawRectangle(x0+2*n,y0,6*n,n,Black);
	LCD_DrawRectangle(x0+10*n,y0,n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-6*n,y0,4*n,n,Black);
	LCD_DrawRectangle(x0+1*n,y0,6*n,n,Black);
	LCD_DrawRectangle(x0+10*n,y0,n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-5*n,y0,3*n,n,Black);
	LCD_DrawRectangle(x0+2*n,y0,5*n,n,Black);
	LCD_DrawRectangle(x0+11*n,y0,n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-5*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-3*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+2*n,y0,4*n,n,Black);
	LCD_DrawRectangle(x0+11*n,y0,n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-5*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-3*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+11*n,y0,n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-6*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-3*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+10*n,y0,n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-8*n,y0,2*n,n,Black);
	LCD_DrawRectangle(x0-2*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+10*n,y0,2*n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-1*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+2*n,y0,6*n,n,Black);
	LCD_DrawRectangle(x0+9*n,y0,3*n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0,y0,9*n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0,y0,8*n,n,Black);
	y0 = y0+n;
	
	//Palloncino
	y0 = y;
	LCD_DrawRectangle(x0-6*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-5*n,y0,n,n,LightBlue);
	LCD_DrawRectangle(x0-4*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0-6*n,y0,3*n,n,Black);
	y0 = y0-n;
		
	LCD_DrawRectangle(x0-7*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-6*n,y0,3*n,n,LightBlue);
	LCD_DrawRectangle(x0-3*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0-8*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-7*n,y0,5*n,n,LightBlue);
	LCD_DrawRectangle(x0-2*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0-9*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-8*n,y0,7*n,n,LightBlue);
	LCD_DrawRectangle(x0-1*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0-10*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-9*n,y0,9*n,n,LightBlue);
	LCD_DrawRectangle(x0,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0-11*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-10*n,y0,11*n,n,LightBlue);
	LCD_DrawRectangle(x0+1*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0-11*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-10*n,y0,11*n,n,LightBlue);
	LCD_DrawRectangle(x0+1*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0-12*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-11*n,y0,13*n,n,LightBlue);
	LCD_DrawRectangle(x0+2*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0-12*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-11*n,y0,13*n,n,LightBlue);
	LCD_DrawRectangle(x0+2*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0-12*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-11*n,y0,13*n,n,LightBlue);
	LCD_DrawRectangle(x0+2*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0-12*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-11*n,y0,13*n,n,LightBlue);
	LCD_DrawRectangle(x0+2*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0-12*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-11*n,y0,13*n,n,LightBlue);
	LCD_DrawRectangle(x0+2*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0-12*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-11*n,y0,13*n,n,LightBlue);
	LCD_DrawRectangle(x0+2*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0-11*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-10*n,y0,11*n,n,LightBlue);
	LCD_DrawRectangle(x0+1*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0-11*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-10*n,y0,11*n,n,LightBlue);
	LCD_DrawRectangle(x0+1*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0-10*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-9*n,y0,9*n,n,LightBlue);
	LCD_DrawRectangle(x0,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0-9*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-8*n,y0,7*n,n,LightBlue);
	LCD_DrawRectangle(x0-1*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0-8*n,y0,7*n,n,Black);
	y0 = y0-n;
		
}


void drawTamagotchi_2(int x0, int y0){
	
	//int x0 = MAX_X/2;
	//int y0 = 165;
	int y=y0;
	int n = 3;

	LCD_DrawRectangle(x0,y0,8*n,n,Black); //Riga sopra
	LCD_DrawRectangle(x0-5*n,y0,n,n,Black); //Riga sopra
	
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-9*n,y0,3*n,n,Black);
	LCD_DrawRectangle(x0-5*n,y0,1*n,n,Black);
	LCD_DrawRectangle(x0-3*n,y0,3*n,n,Black);
	LCD_DrawRectangle(x0+8*n,y0,3*n,n,Black);
	LCD_DrawRectangle(x0+14*n,y0,3*n,n,Black);
	
	y0 = y0+n;
	
	//terza riga
	LCD_DrawRectangle(x0-10*n,y0,7*n,n,Black);
	LCD_DrawRectangle(x0+11*n,y0,7*n,n,Black);
	y0 = y0+n;
	
	//Quarta riga
	LCD_DrawRectangle(x0-11*n,y0,6*n,n,Black);
	LCD_DrawRectangle(x0+13*n,y0,6*n,n,Black);
	y0 = y0+n;
	
	//5
	LCD_DrawRectangle(x0-11*n,y0,5*n,n,Black);
	LCD_DrawRectangle(x0+14*n,y0,5*n,n,Black);
	y0 = y0+n;
	
	//6
	LCD_DrawRectangle(x0-11*n,y0,4*n,n,Black);
	LCD_DrawRectangle(x0+15*n,y0,4*n,n,Black);
	y0 = y0+n;
	
	//7
	LCD_DrawRectangle(x0-11*n,y0,4*n,n,Black);
	LCD_DrawRectangle(x0+16*n,y0,3*n,n,Black);
	y0 = y0+n;
	
	//8
	LCD_DrawRectangle(x0-10*n,y0,2*n,n,Black);
	LCD_DrawRectangle(x0+17*n,y0,n,n,Black);
	y0 = y0+n;
	
	//9
	LCD_DrawRectangle(x0-10*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+17*n,y0,n,n,Black);
	y0 = y0+n;
	
	//10
	LCD_DrawRectangle(x0-10*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+17*n,y0,n,n,Black);
	y0 = y0+n;
	
	//11
	LCD_DrawRectangle(x0-10*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+18*n,y0,n,n,Black);
	y0 = y0+n;
	
	//12
	LCD_DrawRectangle(x0-11*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-7*n,y0,5*n,n,Black);
	LCD_DrawRectangle(x0+9*n,y0,5*n,n,Black);
	LCD_DrawRectangle(x0+18*n,y0,n,n,Black);
	y0 = y0+n;
	
	//13
	LCD_DrawRectangle(x0-11*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-8*n,y0,7*n,n,Black);
	LCD_DrawRectangle(x0+8*n,y0,7*n,n,Black);
	LCD_DrawRectangle(x0+18*n,y0,n,n,Black);
	y0 = y0+n;
	
	//14
	LCD_DrawRectangle(x0-11*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-8*n,y0,8*n,n,Black);
	LCD_DrawRectangle(x0+8*n,y0,8*n,n,Black);
	LCD_DrawRectangle(x0+18*n,y0,n,n,Black);
	y0 = y0+n;
	
	//15
	LCD_DrawRectangle(x0-11*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-8*n,y0,3*n,n,Black);
	LCD_DrawRectangle(x0-3*n,y0,3*n,n,Black);
	LCD_DrawRectangle(x0+8*n,y0,3*n,n,Black);
	LCD_DrawRectangle(x0+13*n,y0,3*n,n,Black);
	LCD_DrawRectangle(x0+18*n,y0,n,n,Black);
	y0 = y0+n;
	
	//16
	LCD_DrawRectangle(x0-11*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-8*n,y0,2*n,n,Black);
	LCD_DrawRectangle(x0-5*n,y0,2*n,n,Black);
	LCD_DrawRectangle(x0-2*n,y0,2*n,n,Black);
	LCD_DrawRectangle(x0+18*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+2*n,y0,2*n,n,Black);
	LCD_DrawRectangle(x0+8*n,y0,2*n,n,Black);
	LCD_DrawRectangle(x0+11*n,y0,2*n,n,Black);
	LCD_DrawRectangle(x0+14*n,y0,2*n,n,Black);
	y0 = y0+n;
	
	//17
	LCD_DrawRectangle(x0-11*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-8*n,y0,8*n,n,Black);
	LCD_DrawRectangle(x0+2*n,y0,3*n,n,Black);
	LCD_DrawRectangle(x0+8*n,y0,8*n,n,Black);
	LCD_DrawRectangle(x0+18*n,y0,n,n,Black);
	y0 = y0+n;
	
	//18
	LCD_DrawRectangle(x0-11*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-8*n,y0,8*n,n,Black);
	LCD_DrawRectangle(x0+3*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+8*n,y0,8*n,n,Black);
	LCD_DrawRectangle(x0+18*n,y0,n,n,Black);
	y0 = y0+n;
	
	//19
	LCD_DrawRectangle(x0-10*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-8*n,y0,3*n,n,Magenta);
	LCD_DrawRectangle(x0-5*n,y0,4*n,n,Black);
	LCD_DrawRectangle(x0+1*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+3*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+5*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+9*n,y0,4*n,n,Black);
	LCD_DrawRectangle(x0+13*n,y0,3*n,n,Magenta);
	LCD_DrawRectangle(x0+17*n,y0,n,n,Black);
	y0 = y0+n;
	
	//20
	LCD_DrawRectangle(x0-10*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-8*n,y0,3*n,n,Magenta);
	LCD_DrawRectangle(x0-5*n,y0,3*n,n,Black);
	LCD_DrawRectangle(x0+2*n,y0,3*n,n,Black);
	LCD_DrawRectangle(x0+10*n,y0,3*n,n,Black);
	LCD_DrawRectangle(x0+13*n,y0,3*n,n,Magenta);
	LCD_DrawRectangle(x0+17*n,y0,n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-9*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+16*n,y0,n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-8*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+15*n,y0,n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-7*n,y0,2*n,n,Black);
	LCD_DrawRectangle(x0+13*n,y0,2*n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-5*n,y0,18*n,n,Black);
	y0 = y0+n;
	
	//Corpo
	LCD_DrawRectangle(x0-5*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-2*n,y0,12*n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-5*n,y0,4*n,n,Black);
	LCD_DrawRectangle(x0+3*n,y0,8*n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-6*n,y0,4*n,n,Black);
	LCD_DrawRectangle(x0+2*n,y0,6*n,n,Black);
	LCD_DrawRectangle(x0+10*n,y0,n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-6*n,y0,4*n,n,Black);
	LCD_DrawRectangle(x0+1*n,y0,6*n,n,Black);
	LCD_DrawRectangle(x0+10*n,y0,n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-5*n,y0,3*n,n,Black);
	LCD_DrawRectangle(x0+2*n,y0,5*n,n,Black);
	LCD_DrawRectangle(x0+11*n,y0,n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-5*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-3*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+2*n,y0,4*n,n,Black);
	LCD_DrawRectangle(x0+11*n,y0,n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-5*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-3*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+11*n,y0,n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-6*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-3*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+10*n,y0,n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-8*n,y0,2*n,n,Black);
	LCD_DrawRectangle(x0-2*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+10*n,y0,2*n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-1*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+2*n,y0,6*n,n,Black);
	LCD_DrawRectangle(x0+9*n,y0,3*n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0,y0,9*n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0,y0,8*n,n,Black);
	y0 = y0+n;
	
	//Palloncino
	y0 = y;
	LCD_DrawRectangle(x0-6*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-5*n,y0,n,n,LightBlue);
	LCD_DrawRectangle(x0-4*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0-6*n,y0,3*n,n,Black);
	y0 = y0-n;
		
	LCD_DrawRectangle(x0-7*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-6*n,y0,3*n,n,LightBlue);
	LCD_DrawRectangle(x0-3*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0-8*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-7*n,y0,5*n,n,LightBlue);
	LCD_DrawRectangle(x0-2*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0-9*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-8*n,y0,7*n,n,LightBlue);
	LCD_DrawRectangle(x0-1*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0-10*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-9*n,y0,9*n,n,LightBlue);
	LCD_DrawRectangle(x0,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0-11*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-10*n,y0,11*n,n,LightBlue);
	LCD_DrawRectangle(x0+1*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0-11*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-10*n,y0,11*n,n,LightBlue);
	LCD_DrawRectangle(x0+1*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0-12*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-11*n,y0,13*n,n,LightBlue);
	LCD_DrawRectangle(x0+2*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0-12*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-11*n,y0,13*n,n,LightBlue);
	LCD_DrawRectangle(x0+2*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0-12*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-11*n,y0,13*n,n,LightBlue);
	LCD_DrawRectangle(x0+2*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0-12*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-11*n,y0,13*n,n,LightBlue);
	LCD_DrawRectangle(x0+2*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0-12*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-11*n,y0,13*n,n,LightBlue);
	LCD_DrawRectangle(x0+2*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0-12*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-11*n,y0,13*n,n,LightBlue);
	LCD_DrawRectangle(x0+2*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0-11*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-10*n,y0,11*n,n,LightBlue);
	LCD_DrawRectangle(x0+1*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0-11*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-10*n,y0,11*n,n,LightBlue);
	LCD_DrawRectangle(x0+1*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0-10*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-9*n,y0,9*n,n,LightBlue);
	LCD_DrawRectangle(x0,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0-9*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-8*n,y0,7*n,n,LightBlue);
	LCD_DrawRectangle(x0-1*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0-8*n,y0,7*n,n,Black);
	y0 = y0-n;
	
		
}


void drawMeal(){
	
	int x0 = 30;
	int y0 = 240;
	int n = 4;
	
	LCD_DrawRectangle(x0,y0,n,n,Green);
	y0=y0+n;
	
	LCD_DrawRectangle(x0,y0,n,n,Green);
	LCD_DrawRectangle(x0+3*n,y0,n,n,Green);
	y0=y0+n;
	
	LCD_DrawRectangle(x0,y0,n,n,Green);
	LCD_DrawRectangle(x0+2*n,y0,n,n,Green);
	y0=y0+n;
	
	LCD_DrawRectangle(x0+1*n,y0,n,n,Green);
	y0=y0+n;
	
	LCD_DrawRectangle(x0+1*n,y0,n,n,Green);
	y0=y0+n;
	
	LCD_DrawRectangle(x0+1*n,y0,n,n,Green);
	LCD_DrawRectangle(x0-2*n,y0,n,n,Green);
	y0=y0+n;
	
	LCD_DrawRectangle(x0-1*n,y0,3*n,n,Green);
	y0=y0+n;
	
	LCD_DrawRectangle(x0+1*n,y0,n,n,Green);
	y0=y0+n;
	
	LCD_DrawRectangle(x0+1*n,y0,n,n,Green);
	y0=y0+n;
	
	
}


void drawTamagotchiRight(int x0, int y0){
	
	int y=y0;
	int n = 3;

	LCD_DrawRectangle(x0,y0,8*n,n,Black); //Riga sopra
	LCD_DrawRectangle(x0+12*n,y0,n,n,Black); //Riga sopra
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-9*n,y0,3*n,n,Black);
	LCD_DrawRectangle(x0-3*n,y0,3*n,n,Black);
	LCD_DrawRectangle(x0+12*n,y0,1*n,n,Black);
	LCD_DrawRectangle(x0+8*n,y0,3*n,n,Black);
	LCD_DrawRectangle(x0+14*n,y0,3*n,n,Black);
	y0 = y0+n;
	
	//terza riga
	LCD_DrawRectangle(x0-10*n,y0,7*n,n,Black);
	LCD_DrawRectangle(x0+11*n,y0,7*n,n,Black);
	y0 = y0+n;
	
	//Quarta riga
	LCD_DrawRectangle(x0-11*n,y0,6*n,n,Black);
	LCD_DrawRectangle(x0+13*n,y0,6*n,n,Black);
	y0 = y0+n;
	
	//5
	LCD_DrawRectangle(x0-11*n,y0,5*n,n,Black);
	LCD_DrawRectangle(x0+14*n,y0,5*n,n,Black);
	y0 = y0+n;
	
	//6
	LCD_DrawRectangle(x0-11*n,y0,4*n,n,Black);
	LCD_DrawRectangle(x0+15*n,y0,4*n,n,Black);
	y0 = y0+n;
	
	//7
	LCD_DrawRectangle(x0-11*n,y0,4*n,n,Black);
	LCD_DrawRectangle(x0+15*n,y0,3*n,n,Black);
	y0 = y0+n;
	
	//8
	LCD_DrawRectangle(x0-10*n,y0,2*n,n,Black);
	LCD_DrawRectangle(x0+16*n,y0,n,n,Black);
	y0 = y0+n;
	
	//9
	LCD_DrawRectangle(x0-10*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+17*n,y0,n,n,Black);
	y0 = y0+n;
	
	//10
	LCD_DrawRectangle(x0-10*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+17*n,y0,n,n,Black);
	y0 = y0+n;
	
	//11
	LCD_DrawRectangle(x0-11*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+17*n,y0,n,n,Black);
	y0 = y0+n;
	
	//12
	LCD_DrawRectangle(x0-11*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-6*n,y0,5*n,n,Black);
	LCD_DrawRectangle(x0+9*n,y0,5*n,n,Black);
	LCD_DrawRectangle(x0+18*n,y0,n,n,Black);
	y0 = y0+n;
	
	//13
	LCD_DrawRectangle(x0-11*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-7*n,y0,7*n,n,Black);
	LCD_DrawRectangle(x0+8*n,y0,7*n,n,Black);
	LCD_DrawRectangle(x0+18*n,y0,n,n,Black);
	y0 = y0+n;
	
	//14
	LCD_DrawRectangle(x0-11*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-8*n,y0,8*n,n,Black);
	LCD_DrawRectangle(x0+8*n,y0,8*n,n,Black);
	LCD_DrawRectangle(x0+18*n,y0,n,n,Black);
	y0 = y0+n;
	
	//15
	LCD_DrawRectangle(x0-11*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-8*n,y0,3*n,n,Black);
	LCD_DrawRectangle(x0-3*n,y0,3*n,n,Black);
	LCD_DrawRectangle(x0+8*n,y0,3*n,n,Black);
	LCD_DrawRectangle(x0+13*n,y0,3*n,n,Black);
	LCD_DrawRectangle(x0+18*n,y0,n,n,Black);
	y0 = y0+n;
	
	//16
	LCD_DrawRectangle(x0-11*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-8*n,y0,2*n,n,Black);
	LCD_DrawRectangle(x0-5*n,y0,2*n,n,Black);
	LCD_DrawRectangle(x0-2*n,y0,2*n,n,Black);
	LCD_DrawRectangle(x0+18*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+4*n,y0,2*n,n,Black);
	LCD_DrawRectangle(x0+8*n,y0,2*n,n,Black);
	LCD_DrawRectangle(x0+11*n,y0,2*n,n,Black);
	LCD_DrawRectangle(x0+14*n,y0,2*n,n,Black);
	y0 = y0+n;
	
	//17
	LCD_DrawRectangle(x0-11*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-8*n,y0,8*n,n,Black);
	LCD_DrawRectangle(x0+3*n,y0,3*n,n,Black);
	LCD_DrawRectangle(x0+8*n,y0,8*n,n,Black);
	LCD_DrawRectangle(x0+18*n,y0,n,n,Black);
	y0 = y0+n;
	
	//18
	LCD_DrawRectangle(x0-11*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-8*n,y0,8*n,n,Black);
	LCD_DrawRectangle(x0+4*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+8*n,y0,8*n,n,Black);
	LCD_DrawRectangle(x0+18*n,y0,n,n,Black);
	y0 = y0+n;
	
		//19
	LCD_DrawRectangle(x0-10*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-7*n,y0,6*n,n,Black);
	LCD_DrawRectangle(x0+2*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+4*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+6*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+9*n,y0,6*n,n,Black);
	LCD_DrawRectangle(x0+17*n,y0,n,n,Black);
	
//	LCD_DrawRectangle(x0-8*n,y0,1*n,n,White);
//	LCD_DrawRectangle(x0+15*n,y0,1*n,n,White);

	y0 = y0+n;
	
	//20
	LCD_DrawRectangle(x0-10*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-6*n,y0,4*n,n,Black);
	LCD_DrawRectangle(x0+3*n,y0,3*n,n,Black);
	LCD_DrawRectangle(x0+10*n,y0,4*n,n,Black);
	LCD_DrawRectangle(x0+17*n,y0,n,n,Black);
	
	LCD_DrawRectangle(x0-8*n,y0,2*n,n,White);
	LCD_DrawRectangle(x0+14*n,y0,2*n,n,White);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-9*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+16*n,y0,n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-8*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+15*n,y0,n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-7*n,y0,2*n,n,Black);
	LCD_DrawRectangle(x0+13*n,y0,2*n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-5*n,y0,18*n,n,Black);
	y0 = y0+n;
	
	//Corpo
	LCD_DrawRectangle(x0+12*n,y0,n,n,Black);
	LCD_DrawRectangle(x0-2*n,y0,12*n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-3*n,y0,8*n,n,Black);
	LCD_DrawRectangle(x0+9*n,y0,4*n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-3*n,y0,n,n,Black);
	LCD_DrawRectangle(x0,y0,6*n,n,Black);
	LCD_DrawRectangle(x0+10*n,y0,4*n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-3*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+1*n,y0,6*n,n,Black);
	LCD_DrawRectangle(x0+10*n,y0,4*n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-4*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+1*n,y0,5*n,n,Black);
	LCD_DrawRectangle(x0+10*n,y0,3*n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-4*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+2*n,y0,4*n,n,Black);
	LCD_DrawRectangle(x0+10*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+12*n,y0,n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-4*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+10*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+12*n,y0,n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-3*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+10*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+12*n,y0,n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-4*n,y0,2*n,n,Black);
	LCD_DrawRectangle(x0+9*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+13*n,y0,2*n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-4*n,y0,3*n,n,Black);
	LCD_DrawRectangle(x0,y0,6*n,n,Black);
	LCD_DrawRectangle(x0+8*n,y0,n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0-1*n,y0,9*n,n,Black);
	y0 = y0+n;
	
	LCD_DrawRectangle(x0,y0,8*n,n,Black);
	y0 = y0+n;
	
	//Palloncino
	y0 = y;
	LCD_DrawRectangle(x0+11*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+12*n,y0,n,n,LightBlue);
	LCD_DrawRectangle(x0+13*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0+11*n,y0,3*n,n,Black);
	y0 = y0-n;
		
	LCD_DrawRectangle(x0+10*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+11*n,y0,3*n,n,LightBlue);
	LCD_DrawRectangle(x0+14*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0+9*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+10*n,y0,5*n,n,LightBlue);
	LCD_DrawRectangle(x0+15*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0+8*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+9*n,y0,7*n,n,LightBlue);
	LCD_DrawRectangle(x0+16*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0+7*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+8*n,y0,9*n,n,LightBlue);
	LCD_DrawRectangle(x0+17*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0+6*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+7*n,y0,11*n,n,LightBlue);
	LCD_DrawRectangle(x0+18*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0+6*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+7*n,y0,11*n,n,LightBlue);
	LCD_DrawRectangle(x0+18*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0+5*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+6*n,y0,13*n,n,LightBlue);
	LCD_DrawRectangle(x0+19*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0+5*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+6*n,y0,13*n,n,LightBlue);
	LCD_DrawRectangle(x0+19*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0+5*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+6*n,y0,13*n,n,LightBlue);
	LCD_DrawRectangle(x0+19*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0+5*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+6*n,y0,13*n,n,LightBlue);
	LCD_DrawRectangle(x0+19*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0+5*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+6*n,y0,13*n,n,LightBlue);
	LCD_DrawRectangle(x0+19*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0+5*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+6*n,y0,13*n,n,LightBlue);
	LCD_DrawRectangle(x0+19*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0+6*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+7*n,y0,11*n,n,LightBlue);
	LCD_DrawRectangle(x0+18*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0+6*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+7*n,y0,11*n,n,LightBlue);
	LCD_DrawRectangle(x0+18*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0+7*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+8*n,y0,9*n,n,LightBlue);
	LCD_DrawRectangle(x0+17*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0+8*n,y0,n,n,Black);
	LCD_DrawRectangle(x0+9*n,y0,7*n,n,LightBlue);
	LCD_DrawRectangle(x0+16*n,y0,n,n,Black);
	y0 = y0-n;
	
	LCD_DrawRectangle(x0+9*n,y0,7*n,n,Black);
	y0 = y0-n;
	
}


void drawFoodMenu(){
	
	GUI_Text(40, 290, (uint8_t *) "Meal", Black, White);
	GUI_Text(160, 290, (uint8_t *) "Snack", Black, White);
	
	LCD_DrawLine(0,280, MAX_X, 280, Black); //Linea orizzontale
	LCD_DrawLine(0,281, MAX_X, 281, Black); //Linea orizzontale per spessire
	LCD_DrawLine(0,281, MAX_X, 281, Black); //Linea orizzontale per spessire
	
	LCD_DrawLine(MAX_X/2, 282, MAX_X/2, MAX_Y, Black); //Linea verticale
	LCD_DrawLine(MAX_X/2-1, 282, MAX_X/2-1, MAX_Y, Black); //Linea verticale per spessire
	LCD_DrawLine(MAX_X/2+1, 282, MAX_X/2+1, MAX_Y, Black); //Linea verticale per spessire
}



void drawVol(int val){
	
	switch(val){
		case 0: 
			drawSimboloVolume(20,15);
			break;
		case 1: 
			draw_one_level_vol(20,15);
			break;
		case 2: 
			draw_two_level_vol(20,15);
			break;
		case 3: 
			draw_three_level_vol(20,15);
			break;
		default: 
			break;
	}
	
}

void drawVolume(void){
	
	int x0 = 5;
	int y0 = 100;
	int n = 2;
	int y2;
	
	//1
	LCD_DrawRectangle(x0+8*n,y0,n,n,Black);
	y0=y0+n;
	
	//2
	LCD_DrawRectangle(x0+7*n,y0,2*n,n,Black);
	y0=y0+n;
	
	//3
	y2=y0;
	LCD_DrawRectangle(x0+6*n,y0,3*n,n,Black);
	y0=y0+n;
	
	//4
	LCD_DrawRectangle(x0+5*n,y0,2*n,n,Black);
	LCD_DrawRectangle(x0+8*n,y0,n,n,Black);
	y0=y0+n;
	
	//5
	LCD_DrawRectangle(x0,y0,6*n,n,Black);
	LCD_DrawRectangle(x0+7*n,y0,2*n,n,Black);
	y0=y0+n;
	
	//6
	LCD_DrawRectangle(x0,y0,2*n,n,Black);
	LCD_DrawRectangle(x0+6*n,y0,3*n,n,Black);
	y0=y0+n;
		
	//7
	LCD_DrawRectangle(x0,y0,9*n,n,Black);
	y0=y0+n;
	
	//8
	LCD_DrawRectangle(x0,y0,9*n,n,Black);
	y0=y0+n;
	
	//9
	LCD_DrawRectangle(x0,y0,9*n,n,Black);
	y0=y0+n;
	
	//10
	LCD_DrawRectangle(x0,y0,9*n,n,Black);
	y0=y0+n;
	
	//11
	LCD_DrawRectangle(x0,y0,9*n,n,Black);
	y0=y0+n;
	
	//12
	LCD_DrawRectangle(x0,y0,9*n,n,Black);
	y0=y0+n;
	
	//13
	LCD_DrawRectangle(x0+5*n,y0,4*n,n,Black);
	y0=y0+n;

	//14
	LCD_DrawRectangle(x0+6*n,y0,3*n,n,Black);
	y0=y0+n;
	
	//15
	LCD_DrawRectangle(x0+7*n,y0,2*n,n,Black);
	y0=y0+n;

	//16
	LCD_DrawRectangle(x0+8*n,y0,n,n,Black);
	y0=y0+n;
	
	
	//Tacche volume
	LCD_DrawRectangle(x0+16*n,y2,n,n,Black); //terza tacca
	y2=y2+n;
	
	LCD_DrawRectangle(x0+13*n,y2,n,n,Black); //seconda tacca
	LCD_DrawRectangle(x0+17*n,y2,n,n,Black); //terza tacca
	y2=y2+n;
	
	LCD_DrawRectangle(x0+14*n,y2,n,n,Black); //seconda tacca
	LCD_DrawRectangle(x0+17*n,y2,n,n,Black); //terza tacca
	y2=y2+n;
		
	LCD_DrawRectangle(x0+11*n,y2,n,n,Black); //prima tacca
	LCD_DrawRectangle(x0+15*n,y2,n,n,Black); //seconda tacca
	LCD_DrawRectangle(x0+18*n,y2,n,n,Black); //terza tacca
	y2=y2+n;
	
	LCD_DrawRectangle(x0+12*n,y2,n,n,Black); //prima tacca
	LCD_DrawRectangle(x0+15*n,y2,n,n,Black); //seconda tacca
	LCD_DrawRectangle(x0+18*n,y2,n,n,Black); //terza tacca
	y2=y2+n;
		
	LCD_DrawRectangle(x0+12*n,y2,n,n,Black); //prima tacca
	LCD_DrawRectangle(x0+15*n,y2,n,n,Black); //seconda tacca
	LCD_DrawRectangle(x0+18*n,y2,n,n,Black); //terza tacca
	y2=y2+n;
		
	LCD_DrawRectangle(x0+12*n,y2,n,n,Black); //prima tacca
	LCD_DrawRectangle(x0+15*n,y2,n,n,Black); //seconda tacca
	LCD_DrawRectangle(x0+18*n,y2,n,n,Black); //terza tacca
	y2=y2+n;
		
	LCD_DrawRectangle(x0+12*n,y2,n,n,Black); //prima tacca
	LCD_DrawRectangle(x0+15*n,y2,n,n,Black); //seconda tacca
	LCD_DrawRectangle(x0+18*n,y2,n,n,Black); //terza tacca
	y2=y2+n;
		
	LCD_DrawRectangle(x0+11*n,y2,n,n,Black); //prima tacca
	LCD_DrawRectangle(x0+15*n,y2,n,n,Black); //seconda tacca
	LCD_DrawRectangle(x0+18*n,y2,n,n,Black); //terza tacca
	y2=y2+n;
		
	LCD_DrawRectangle(x0+14*n,y2,n,n,Black); //seconda tacca
	LCD_DrawRectangle(x0+17*n,y2,n,n,Black); //terza tacca
	y2=y2+n;
	
	LCD_DrawRectangle(x0+13*n,y2,n,n,Black); //seconda tacca
	LCD_DrawRectangle(x0+17*n,y2,n,n,Black); //terza tacca
	y2=y2+n;
		
	LCD_DrawRectangle(x0+16*n,y2,n,n,Black); //terza tacca
	
	
	//Croce
//	LCD_DrawRectangle(x0+11*n,y,n,n,Red);
//	LCD_DrawRectangle(x0+15*n,y,n,n,Red);
//	y=y+n;
//	
//	LCD_DrawRectangle(x0+12*n,y,n,n,Red);
//	LCD_DrawRectangle(x0+14*n,y,n,n,Red);
//	y=y+n;
//	
//	LCD_DrawRectangle(x0+13*n,y,n,n,Red);
//	y=y+n;
//	
//	LCD_DrawRectangle(x0+12*n,y,n,n,Red);
//	LCD_DrawRectangle(x0+14*n,y,n,n,Red);
//	y=y+n;
//	
//	LCD_DrawRectangle(x0+11*n,y,n,n,Red);
//	LCD_DrawRectangle(x0+15*n,y,n,n,Red);
//	y=y+n;
	
}

void draw_muteVolume(int x0, int y0){
	
	int n = 2;
	int y=y0;
	
	//Croce
	LCD_DrawRectangle(x0+11*n,y,n,n,Red);
	LCD_DrawRectangle(x0+15*n,y,n,n,Red);
	y=y+n;
	
	LCD_DrawRectangle(x0+12*n,y,n,n,Red);
	LCD_DrawRectangle(x0+14*n,y,n,n,Red);
	y=y+n;
	
	LCD_DrawRectangle(x0+13*n,y,n,n,Red);
	y=y+n;
	
	LCD_DrawRectangle(x0+12*n,y,n,n,Red);
	LCD_DrawRectangle(x0+14*n,y,n,n,Red);
	y=y+n;
	
	LCD_DrawRectangle(x0+11*n,y,n,n,Red);
	LCD_DrawRectangle(x0+15*n,y,n,n,Red);
	y=y+n;
	
}


void drawSimboloVolume(int x0, int y0){
	
	int n = 1;
	int y=y0;
	
	//1
	LCD_DrawRectangle(x0+8*n,y0,n,n,Black);
	y0=y0+n;
	
	//2
	LCD_DrawRectangle(x0+7*n,y0,2*n,n,Black);
	y0=y0+n;
	
	//3
	LCD_DrawRectangle(x0+6*n,y0,3*n,n,Black);
	y0=y0+n;
	
	//4
	LCD_DrawRectangle(x0+5*n,y0,2*n,n,Black);
	LCD_DrawRectangle(x0+8*n,y0,n,n,Black);
	y0=y0+n;
	
	//5
	LCD_DrawRectangle(x0,y0,6*n,n,Black);
	LCD_DrawRectangle(x0+7*n,y0,2*n,n,Black);
	y0=y0+n;
	
	//6
	y = y0;
	LCD_DrawRectangle(x0,y0,2*n,n,Black);
	LCD_DrawRectangle(x0+6*n,y0,3*n,n,Black);
	y0=y0+n;
		
	//7
	LCD_DrawRectangle(x0,y0,9*n,n,Black);
	y0=y0+n;
	
	//8
	LCD_DrawRectangle(x0,y0,9*n,n,Black);
	y0=y0+n;
	
	//9
	LCD_DrawRectangle(x0,y0,9*n,n,Black);
	y0=y0+n;
	
	//10
	LCD_DrawRectangle(x0,y0,9*n,n,Black);
	y0=y0+n;
	
	//11
	LCD_DrawRectangle(x0,y0,9*n,n,Black);
	y0=y0+n;
	
	//12
	LCD_DrawRectangle(x0,y0,9*n,n,Black);
	y0=y0+n;
	
	//13
	LCD_DrawRectangle(x0+5*n,y0,4*n,n,Black);
	y0=y0+n;

	//14
	LCD_DrawRectangle(x0+6*n,y0,3*n,n,Black);
	y0=y0+n;
	
	//15
	LCD_DrawRectangle(x0+7*n,y0,2*n,n,Black);
	y0=y0+n;

	//16
	LCD_DrawRectangle(x0+8*n,y0,n,n,Black);
	y0=y0+n;
	
	
	LCD_DrawRectangle(x0+10*n,15,20*n,17*n,White);
	
	
	//Croce rossa
	LCD_DrawRectangle(x0+11*n,y,n,n,Red);
	LCD_DrawRectangle(x0+15*n,y,n,n,Red);
	y=y+n;
	
	LCD_DrawRectangle(x0+12*n,y,n,n,Red);
	LCD_DrawRectangle(x0+14*n,y,n,n,Red);
	y=y+n;
	
	LCD_DrawRectangle(x0+13*n,y,n,n,Red);
	y=y+n;
	
	LCD_DrawRectangle(x0+12*n,y,n,n,Red);
	LCD_DrawRectangle(x0+14*n,y,n,n,Red);
	y=y+n;
	
	LCD_DrawRectangle(x0+11*n,y,n,n,Red);
	LCD_DrawRectangle(x0+15*n,y,n,n,Red);
	y=y+n;
	
	
}
void draw_one_level_vol(int x0, int y0){
	
	int n = 1;
	int y2=y0;
	
	LCD_DrawRectangle(x0+10*n,15,20*n,17*n,White);
	
	//1
	LCD_DrawRectangle(x0+8*n,y0,n,n,Black);
	y0=y0+n;
	
	//2
	LCD_DrawRectangle(x0+7*n,y0,2*n,n,Black);
	y0=y0+n;
	
	//3
	y2=y0;
	LCD_DrawRectangle(x0+6*n,y0,3*n,n,Black);
	y0=y0+n;
	
	//4
	LCD_DrawRectangle(x0+5*n,y0,2*n,n,Black);
	LCD_DrawRectangle(x0+8*n,y0,n,n,Black);
	y0=y0+n;
	
	//5
	LCD_DrawRectangle(x0,y0,6*n,n,Black);
	LCD_DrawRectangle(x0+7*n,y0,2*n,n,Black);
	y0=y0+n;
	
	//6
	LCD_DrawRectangle(x0,y0,2*n,n,Black);
	LCD_DrawRectangle(x0+6*n,y0,3*n,n,Black);
	y0=y0+n;
		
	//7
	LCD_DrawRectangle(x0,y0,9*n,n,Black);
	y0=y0+n;
	
	//8
	LCD_DrawRectangle(x0,y0,9*n,n,Black);
	y0=y0+n;
	
	//9
	LCD_DrawRectangle(x0,y0,9*n,n,Black);
	y0=y0+n;
	
	//10
	LCD_DrawRectangle(x0,y0,9*n,n,Black);
	y0=y0+n;
	
	//11
	LCD_DrawRectangle(x0,y0,9*n,n,Black);
	y0=y0+n;
	
	//12
	LCD_DrawRectangle(x0,y0,9*n,n,Black);
	y0=y0+n;
	
	//13
	LCD_DrawRectangle(x0+5*n,y0,4*n,n,Black);
	y0=y0+n;

	//14
	LCD_DrawRectangle(x0+6*n,y0,3*n,n,Black);
	y0=y0+n;
	
	//15
	LCD_DrawRectangle(x0+7*n,y0,2*n,n,Black);
	y0=y0+n;

	//16
	LCD_DrawRectangle(x0+8*n,y0,n,n,Black);
	y0=y0+n;
	
	
	//Tacche volume

	y2=y2+n;
	y2=y2+n;
	y2=y2+n;
		
	LCD_DrawRectangle(x0+11*n,y2,n,n,Black); //prima tacca
	y2=y2+n;
	
	LCD_DrawRectangle(x0+12*n,y2,n,n,Black); //prima tacca
	y2=y2+n;
		
	LCD_DrawRectangle(x0+12*n,y2,n,n,Black); //prima tacca
	y2=y2+n;
		
	LCD_DrawRectangle(x0+12*n,y2,n,n,Black); //prima tacca
	y2=y2+n;
		
	LCD_DrawRectangle(x0+12*n,y2,n,n,Black); //prima tacca
	y2=y2+n;
		
	LCD_DrawRectangle(x0+11*n,y2,n,n,Black); //prima tacca

	
}
void draw_two_level_vol(int x0, int y0){
	
	//int n=7/4;
	int n = 1;
	int y2=y0;
	
	LCD_DrawRectangle(x0+10*n,15,20*n,17*n,White);
	
	//1
	LCD_DrawRectangle(x0+8*n,y0,n,n,Black);
	y0=y0+n;
	
	//2
	LCD_DrawRectangle(x0+7*n,y0,2*n,n,Black);
	y0=y0+n;
	
	//3
	y2=y0;
	LCD_DrawRectangle(x0+6*n,y0,3*n,n,Black);
	y0=y0+n;
	
	//4
	LCD_DrawRectangle(x0+5*n,y0,2*n,n,Black);
	LCD_DrawRectangle(x0+8*n,y0,n,n,Black);
	y0=y0+n;
	
	//5
	LCD_DrawRectangle(x0,y0,6*n,n,Black);
	LCD_DrawRectangle(x0+7*n,y0,2*n,n,Black);
	y0=y0+n;
	
	//6
	LCD_DrawRectangle(x0,y0,2*n,n,Black);
	LCD_DrawRectangle(x0+6*n,y0,3*n,n,Black);
	y0=y0+n;
		
	//7
	LCD_DrawRectangle(x0,y0,9*n,n,Black);
	y0=y0+n;
	
	//8
	LCD_DrawRectangle(x0,y0,9*n,n,Black);
	y0=y0+n;
	
	//9
	LCD_DrawRectangle(x0,y0,9*n,n,Black);
	y0=y0+n;
	
	//10
	LCD_DrawRectangle(x0,y0,9*n,n,Black);
	y0=y0+n;
	
	//11
	LCD_DrawRectangle(x0,y0,9*n,n,Black);
	y0=y0+n;
	
	//12
	LCD_DrawRectangle(x0,y0,9*n,n,Black);
	y0=y0+n;
	
	//13
	LCD_DrawRectangle(x0+5*n,y0,4*n,n,Black);
	y0=y0+n;

	//14
	LCD_DrawRectangle(x0+6*n,y0,3*n,n,Black);
	y0=y0+n;
	
	//15
	LCD_DrawRectangle(x0+7*n,y0,2*n,n,Black);
	y0=y0+n;

	//16
	LCD_DrawRectangle(x0+8*n,y0,n,n,Black);
	y0=y0+n;
	
	
	//Tacche volume bianche
	y2=y2+n;
	
	LCD_DrawRectangle(x0+13*n,y2,n,n,Black); //seconda tacca
	y2=y2+n;
	
	LCD_DrawRectangle(x0+14*n,y2,n,n,Black); //seconda tacca
	y2=y2+n;
		
	LCD_DrawRectangle(x0+11*n,y2,n,n,Black); //prima tacca
	LCD_DrawRectangle(x0+15*n,y2,n,n,Black); //seconda tacca
	y2=y2+n;
	
	LCD_DrawRectangle(x0+12*n,y2,n,n,Black); //prima tacca
	LCD_DrawRectangle(x0+15*n,y2,n,n,Black); //seconda tacca
	y2=y2+n;
		
	LCD_DrawRectangle(x0+12*n,y2,n,n,Black); //prima tacca
	LCD_DrawRectangle(x0+15*n,y2,n,n,Black); //seconda tacca
	y2=y2+n;
		
	LCD_DrawRectangle(x0+12*n,y2,n,n,Black); //prima tacca
	LCD_DrawRectangle(x0+15*n,y2,n,n,Black); //seconda tacca
	y2=y2+n;
		
	LCD_DrawRectangle(x0+12*n,y2,n,n,Black); //prima tacca
	LCD_DrawRectangle(x0+15*n,y2,n,n,Black); //seconda tacca
	y2=y2+n;
		
	LCD_DrawRectangle(x0+11*n,y2,n,n,Black); //prima tacca
	LCD_DrawRectangle(x0+15*n,y2,n,n,Black); //seconda tacca
	y2=y2+n;
		
	LCD_DrawRectangle(x0+14*n,y2,n,n,Black); //seconda tacca
	y2=y2+n;
	
	LCD_DrawRectangle(x0+13*n,y2,n,n,Black); //seconda tacca
	y2=y2+n;
		
	
}

void draw_three_level_vol(int x0, int y0){
	
	int n = 1;
	int y2=y0;
	
	LCD_DrawRectangle(x0+10*n,15,20*n,17*n,White); //Rettangolo bianco grosso
	
	
	//1
	LCD_DrawRectangle(x0+8*n,y0,n,n,Black);
	y0=y0+n;
	
	//2
	LCD_DrawRectangle(x0+7*n,y0,2*n,n,Black);
	y0=y0+n;
	
	//3
	y2=y0;
	LCD_DrawRectangle(x0+6*n,y0,3*n,n,Black);
	y0=y0+n;
	
	//4
	LCD_DrawRectangle(x0+5*n,y0,2*n,n,Black);
	LCD_DrawRectangle(x0+8*n,y0,n,n,Black);
	y0=y0+n;
	
	//5
	LCD_DrawRectangle(x0,y0,6*n,n,Black);
	LCD_DrawRectangle(x0+7*n,y0,2*n,n,Black);
	y0=y0+n;
	
	//6
	LCD_DrawRectangle(x0,y0,2*n,n,Black);
	LCD_DrawRectangle(x0+6*n,y0,3*n,n,Black);
	y0=y0+n;
		
	//7
	LCD_DrawRectangle(x0,y0,9*n,n,Black);
	y0=y0+n;
	
	//8
	LCD_DrawRectangle(x0,y0,9*n,n,Black);
	y0=y0+n;
	
	//9
	LCD_DrawRectangle(x0,y0,9*n,n,Black);
	y0=y0+n;
	
	//10
	LCD_DrawRectangle(x0,y0,9*n,n,Black);
	y0=y0+n;
	
	//11
	LCD_DrawRectangle(x0,y0,9*n,n,Black);
	y0=y0+n;
	
	//12
	LCD_DrawRectangle(x0,y0,9*n,n,Black);
	y0=y0+n;
	
	//13
	LCD_DrawRectangle(x0+5*n,y0,4*n,n,Black);
	y0=y0+n;

	//14
	LCD_DrawRectangle(x0+6*n,y0,3*n,n,Black);
	y0=y0+n;
	
	//15
	LCD_DrawRectangle(x0+7*n,y0,2*n,n,Black);
	y0=y0+n;

	//16
	LCD_DrawRectangle(x0+8*n,y0,n,n,Black);
	y0=y0+n;
	
		
	//Tacche volume bianche
	LCD_DrawRectangle(x0+16*n,y2,n,n,Black); //terza tacca
	y2=y2+n;
	
	LCD_DrawRectangle(x0+13*n,y2,n,n,Black); //seconda tacca
	LCD_DrawRectangle(x0+17*n,y2,n,n,Black); //terza tacca
	y2=y2+n;
	
	LCD_DrawRectangle(x0+14*n,y2,n,n,Black); //seconda tacca
	LCD_DrawRectangle(x0+17*n,y2,n,n,Black); //terza tacca
	y2=y2+n;
		
	LCD_DrawRectangle(x0+11*n,y2,n,n,Black); //prima tacca
	LCD_DrawRectangle(x0+15*n,y2,n,n,Black); //seconda tacca
	LCD_DrawRectangle(x0+18*n,y2,n,n,Black); //terza tacca
	y2=y2+n;
	
	LCD_DrawRectangle(x0+12*n,y2,n,n,Black); //prima tacca
	LCD_DrawRectangle(x0+15*n,y2,n,n,Black); //seconda tacca
	LCD_DrawRectangle(x0+18*n,y2,n,n,Black); //terza tacca
	y2=y2+n;
		
	LCD_DrawRectangle(x0+12*n,y2,n,n,Black); //prima tacca
	LCD_DrawRectangle(x0+15*n,y2,n,n,Black); //seconda tacca
	LCD_DrawRectangle(x0+18*n,y2,n,n,Black); //terza tacca
	y2=y2+n;
		
	LCD_DrawRectangle(x0+12*n,y2,n,n,Black); //prima tacca
	LCD_DrawRectangle(x0+15*n,y2,n,n,Black); //seconda tacca
	LCD_DrawRectangle(x0+18*n,y2,n,n,Black); //terza tacca
	y2=y2+n;
		
	LCD_DrawRectangle(x0+12*n,y2,n,n,Black); //prima tacca
	LCD_DrawRectangle(x0+15*n,y2,n,n,Black); //seconda tacca
	LCD_DrawRectangle(x0+18*n,y2,n,n,Black); //terza tacca
	y2=y2+n;
		
	LCD_DrawRectangle(x0+11*n,y2,n,n,Black); //prima tacca
	LCD_DrawRectangle(x0+15*n,y2,n,n,Black); //seconda tacca
	LCD_DrawRectangle(x0+18*n,y2,n,n,Black); //terza tacca
	y2=y2+n;
		
	LCD_DrawRectangle(x0+14*n,y2,n,n,Black); //seconda tacca
	LCD_DrawRectangle(x0+17*n,y2,n,n,Black); //terza tacca
	y2=y2+n;
	
	LCD_DrawRectangle(x0+13*n,y2,n,n,Black); //seconda tacca
	LCD_DrawRectangle(x0+17*n,y2,n,n,Black); //terza tacca
	y2=y2+n;
		
	LCD_DrawRectangle(x0+16*n,y2,n,n,Black); //terza tacca
	
}
