/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.79.0
        Device            :  PIC16F1619
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include "def.h"

//#define I2C1
#define I2C2

/*
                         Main application
 */
uint16_t Vitesse = 0, Angle = 10;
uint8_t Data, Type, Validation = 4;
state PosUart = S_Idle;
state_led StateLeds = S_leds_off;
state_bat StateBat = S_bat_high;

void MyTimer2ISR(void) {
    #ifdef I2C1
    uint16_t g = I2C_Read2ByteRegister(ADDR_MPU_R, GYRO_Z_REG_L-1);
    #endif
    //gestion MPU
    //PID
    PWM3_LoadDutyValue((uint8_t)(Angle/2)+20);  //31 - 63
    if(BAT_GetValue()) {
        if(StateBat == S_bat_low) {
            EUSART_Write('B');
            EUSART_Write('1');
            EUSART_Write('s');
            StateBat = S_bat_high;
        }
        if(Validation) {
            #ifdef I2C2
            if(Vitesse > 100) {Vitesse = 100;}
            I2C_Write1ByteRegister(ADDR_DSPIC, Vitesse, 0);
            #endif
            Validation--;
        } else {
            #ifdef I2C2
            I2C_Write1ByteRegister(ADDR_DSPIC, STOP_MOTEUR, 0);
            #endif
        }
    } else {
        if(StateBat == S_bat_high) {
            EUSART_Write('B');
            EUSART_Write('0');
            EUSART_Write('r');
            StateBat = S_bat_low;
        }
        #ifdef I2C2
        I2C_Write1ByteRegister(ADDR_DSPIC, STOP_MOTEUR, 0);
        #endif
    }
}

void MyUART_ISR(void) {
    unsigned char c = RC1REG;
    if(c) {
        switch(PosUart) {
            case S_Idle:
                if(c == 'V' || c == 'A' || c == 'P' || c == 'L') {
                    Type = c;
                    PosUart = S_Data;
                }
                break;
            case S_Data:
                Data = c;
                PosUart = S_Check;
                break;
            case S_Check:
                if((Type+Data)%256 == c) {
                    Validation = 4;
                    if(Type == 'V') {
                        Vitesse = Data;
                    } else if(Type == 'A') {
                        Angle = Data;
                    } else if(Type == 'P') {
                        EUSART_Write('P');
                        EUSART_Write('+');
                        EUSART_Write('{');
                    } else if(Type == 'L') {
                        StateLeds++;
                        switch(StateLeds) {
                            case S_leds_off:
                                LED_R_SetLow();
                                LED_L_SetLow();
                                break;
                            case S_led_r:
                                LED_R_SetHigh();
                                LED_L_SetLow();
                                break;
                            case S_led_l:
                                LED_R_SetLow();
                                LED_L_SetHigh();
                                break;
                            case S_leds_on:
                                LED_R_SetHigh();
                                LED_L_SetHigh();
                                break;
                            default:
                                LED_R_SetLow();
                                LED_L_SetLow();
                                StateLeds = S_leds_off;
                                break;
                        }
                    } else {
                        EUSART_Write('$');
                        EUSART_Write('M');
                        EUSART_Write('q');
                    }
                } else {
                    EUSART_Write('$');
                    EUSART_Write('C');
                    EUSART_Write('g');
                }
                PosUart = S_Idle;
                break;
            default:
                PosUart = S_Idle;
                break;
        }
    }
}

void main(void) {
    SYSTEM_Initialize();
    
    CMD_EN_SetHigh();
    STATE_SetHigh();
    
    #ifdef I2C1
    I2C_Write1ByteRegister(ADDR_MPU_W, FILTER_REG, FILTER_92HZ);
    I2C_Write1ByteRegister(ADDR_MPU_W, GYRO_SCALE_REG, SCALE);
    #endif
    
    TMR2_SetInterruptHandler(MyTimer2ISR);
    TMR2_WriteTimer(255);
    TMR2_StartTimer();
    
    EUSART_SetRxInterruptHandler(MyUART_ISR);
    
    INTERRUPT_PeripheralInterruptEnable();
    INTERRUPT_GlobalInterruptEnable();
    
    while (1) {
        if(BAT_GetValue()) {
            if(Validation) {
                STATE_Toggle();
                __delay_ms(500);
            } else {
                STATE_Toggle();
                __delay_ms(100);
            }
        } else {
            STATE_SetHigh();
        }
    }
}

/**
 End of File
*/