#ifndef __DRAW_H
#define __DRAW_H 

/* Includes ------------------------------------------------------------------*/
#include <string.h>

/* Private function prototypes -----------------------------------------------*/
extern void start(void);

extern void drawStatusMenu(int sec, int min, int hour);
extern void drawStatusMenu2(int sec, int min, int hour);
extern void drawStatusMenu3(int sec, int min, int hour);

extern void drawFoodMenu(void);

extern void drawTamagotchi(int x0, int y0);
extern void drawTamagotchi_2(int x0, int y0);
extern void drawTamagotchiRight(int x0, int y0); //Panda verso destra quando va via
extern void drawPandaSteso(int x0, int y0);

extern void drawMeal(void);
extern void drawSnack(void);
extern void drawCuore(int x0, int y0, int color);

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

extern void PandaRight(int n);
extern void PandaMeal(int n);
extern void PandaSnack(int n);
extern void PandaCuddles(int n);

extern void drawReset(void);

extern void drawVolume(void);

extern void drawSimboloVolume(int x0, int y0);
extern void draw_one_level_vol(int x0, int y0);
extern void draw_two_level_vol(int x0, int y0);
extern void draw_three_level_vol(int x0, int y0);
extern void draw_muteVolume(int x0, int y0);
extern void drawVol(int val);

#endif 
