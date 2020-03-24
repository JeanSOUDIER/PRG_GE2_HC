#include <p30F2010.h>

#include "init.h"

void InitPin(void) {
    LATC = 0x0000;
    LATE = 0x0000;
    TRISC = ~(1<<STATE);
    TRISB = (1<<RET_C)|(1<<CUR);
    TRISD = (1<<RET_A)|(1<<RET_B);
    TRISE = ~((1<<PWM1L)|(1<<PWM1H)|(1<<PWM2L)|(1<<PWM2H)|(1<<PWM3L)|(1<<PWM3H)|(1<<SCL));
    TRISF = ~(1<<SDA);
}

void InitAdc(void) {
    ADPCFG = 0xFFFB;
    ADCON1 = 0x0064;
    ADCON2 = 0x0200;
    ADCON3 = 0x0080;
    ADCHS = 0x0002;
    
    IFS0bits.ADIF = 0;
    IEC0bits.ADIE = 1;
    
    ADCON1bits.ADON = 1;
}

void InitPWM(void) {
    PTPER = Fcy/FPWM - 1;
    
    PWMCON1 = 0x0700;
    //OVDCON = 0x0000;
    OVDCON = 0x0210;
    PDC1 = START_VALUE;
    PDC3 = START_VALUE;
    PDC3 = START_VALUE;
    SEVTCMP = PTPER;
    PWMCON2 = 0x0F00;
    PTCON = 0x8000;
}

void InitTMR3(void) {
    T3CON = 0x0030;
    TMR3 = 0;
    PR3 = 0x0090;           //20 ms
    IFS0bits.T3IF = 1;
    IEC0bits.T3IE = 1;
    
    T3CONbits.TON = 1;
}

void InitCN(void) {
    CNEN1 = 0x00E0;
    IFS0bits.CNIF = 0;
    IEC0bits.CNIE = 1;
}

void InitI2C(void) {
    I2CADD = DsPIC_I2C_ADDR;
    I2CCON = 0x9480;
    
}

void Init(void) {
    InitPin();
    InitAdc();
    InitPWM();
    InitTMR3();
    InitCN();
    InitI2C();
}

