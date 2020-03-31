// DSPIC30F2010 Configuration Bit Settings

// 'C' source line config statements

#include "def.h"

const unsigned int StateLoTable[] = {0x0000, 0x0210, 0x2004, 0x0204, 0x0801, 0x0810, 0x2001, 0x0000};
unsigned int HallValue = 0, Current = 0;
unsigned char Vitesse = 0, Validation = 0;
state State = Idle;

int test = 0;

int main(int argc, char** argv) {
    Init();
    START_MOTOR();
    LED_OFF();
    while(1) {
        if(State == ErrCur) {
            __delay_ms(100);
            LED_ON();
            __delay_ms(100);
            LED_OFF();
        } else if(State == ErrRec) {
            LED_ON();
        } else {
            __delay_ms(500);
            LED_ON();
            __delay_ms(500);
            LED_OFF();
        }
    }
    return (EXIT_SUCCESS);
}

void __attribute__((__interrupt__, __auto_psv__)) _CNInterrupt(void) {
    IFS0bits.CNIF = 0;          //clear flag
    HallValue = PORTB & 0x0038; //mask RB3, 4, 5
    HallValue = HallValue >> 3;
    OVDCON = StateLoTable[HallValue];
}

void __attribute__((__interrupt__, __auto_psv__)) _ADCInterrupt(void) {
    IFS0bits.ADIF = 0;
    Current = ADCBUF0;
    /*PDC1 = Vitesse;
    PDC3 = Vitesse;
    PDC3 = Vitesse;*/
}

void __attribute__((__interrupt__, __auto_psv__)) _T3Interrupt(void) {
	IFS0bits.T3IF = 0;
    if(Current > LIM_CUR) {
        PDC1 = 0;
        PDC3 = 0;
        PDC3 = 0;
        State = ErrCur;
    } else {
        if(Validation) {
            PDC1 = Vitesse;
            PDC3 = Vitesse;
            PDC3 = Vitesse;
            Validation--;
            State = Idle;
        } else {
            PDC1 = 0;
            PDC3 = 0;
            PDC3 = 0;
            State = ErrRec;
        }
    }
}

void __attribute__((__interrupt__, __auto_psv__)) _SI2CInterrupt(void) {
    IFS0bits.SI2CIF = 0;
    unsigned char temp = I2CRCV;
    if(temp < 102 && temp > 0) {
        if(temp == 101) {
            Vitesse = 0;
        } else {
            Vitesse = (100-temp)<<1;
        }
        Validation = 4;
    }
}
