#ifndef INIT_H
#define INIT_H

#include <xc.h>
#include <libpic30.h>
#include <stdio.h>
#include <stdlib.h>

#define Fcy   2000000
#define FPWM  25000

#define SCL 3 //F
#define SDA 2 //F
#define CUR 2 //B
#define RET_A 0 //D
#define RET_B 1 //D
#define RET_C 4 //B
#define STATE 13 //C
#define PWM1L 0 //E
#define PWM1H 1 //E
#define PWM2L 2 //E
#define PWM2H 3 //E
#define PWM3L 4 //E
#define PWM3H 5 //E

#define START_VALUE 100

#define DsPIC_I2C_ADDR  0x0040

void InitPin(void);
void InitAdc(void);
void InitPWM(void);
void InitTMR3(void);
void InitCN(void);
void InitI2C(void);
void InitSPI(void);
void Init(void);

#endif //INIT_H