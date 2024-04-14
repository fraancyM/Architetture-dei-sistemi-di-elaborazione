#ifndef __DRAW_H
#define __DRAW_H 

/* Includes ------------------------------------------------------------------*/
#include <string.h>

/* Private function prototypes -----------------------------------------------*/
extern void start(void);

extern void drawStatusMenu(int sec, int min, int hour);
extern void drawFoodMenu(void);

extern void drawTamagotchi(int x0, int y0);
extern void drawTamagotchi_2(int x0, int y0);
extern void drawDeadTamagotchi(int x0, int y0); //Panda verso destra
extern void drawPandaSteso(int x0, int y0);

extern void drawMeal(void);
extern void drawSnack(void);
extern void drawCuore(void);

extern void draw_battery_S(int val);
extern void draw_battery_H(int val);

extern void battery_Happiness_zero(void);
extern void battery_Happiness_one(void);
extern void battery_Happiness_two(void);
extern void battery_Happiness_three(void);
extern void battery_Happiness_full(void);

extern void battery_Satiety_zero(void);
extern void battery_Satiety_one(void);
extern void battery_Satiety_two(void);
extern void battery_Satiety_three(void);
extern void battery_Satiety_full(void);

extern void PandaRight(void);
extern void PandaMeal(void);
extern void PandaSnack(void);

extern void drawReset(void);

#endif 
