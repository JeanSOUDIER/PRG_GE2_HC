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

/*
                         Main application
 */
uint16_t Vitesse = 0, Angle = 10;
uint8_t Data, Type;
state PosUart = S_Idle;

void MyTimer2ISR(void) {
    uint16_t g = I2C_Read2ByteRegister(ADDR_MPU_R, GYRO_Z_REG_L-1);
    //gestion MPU
    //PID
    PWM3_LoadDutyValue((uint8_t)(Angle/3)+31);  //31 - 63
    if(BAT_GetValue()) {
        EUSART_Write('B');
        EUSART_Write('1');
        EUSART_Write('s');
        I2C_Write1ByteRegister(ADDR_DSPIC, VITESSE_REG, 0x05);
    } else {
        EUSART_Write('B');
        EUSART_Write('0');
        EUSART_Write('r');
        I2C_Write1ByteRegister(ADDR_DSPIC, VITESSE_REG, 0x00);
    }
}

void MyUART_ISR(void) {
    unsigned char c = RC1REG;
    if(c) {
        switch(PosUart) {
            case S_Idle:
                if(c == 'V' || c == 'A' || c == 'P') {
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
                    if(Type == 'V') {
                        Vitesse = Data;
                    } else if(Type == 'A') {
                        Angle = Data;
                    } else if(Type == 'P') {
                        EUSART_Write('P');
                        EUSART_Write('+');
                        EUSART_Write('{');
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
    
    I2C_Write1ByteRegister(ADDR_MPU_W, FILTER_REG, FILTER_92HZ);
    I2C_Write1ByteRegister(ADDR_MPU_W, GYRO_SCALE_REG, SCALE);
    
    TMR2_SetInterruptHandler(MyTimer2ISR);
    TMR2_WriteTimer(255);
    TMR2_StartTimer();
    
    EUSART_SetRxInterruptHandler(MyUART_ISR);
    
    INTERRUPT_PeripheralInterruptEnable();
    INTERRUPT_GlobalInterruptEnable();
    
    while (1) {
        STATE_Toggle();
        __delay_ms(500);
    }
}

/**
 End of File
*/