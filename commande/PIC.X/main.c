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

#define I2C1  //allumage des commandes I2C (1 = IMU, 2 = DsPIC)
#define I2C2

/*
                         Main application
 */
//déclaration des varaibles
uint8_t Data, Type, Validation = 4, CptBat = 0, G = 0, Vitesse = 0, Angle = 45, StateToggle = 0, Pos;
state PosUart = S_Idle;
state_led StateLeds = S_leds_cligno;
state_bat StateBat = S_bat_high;

void MyTimer2ISR(void) {
    StateToggle = ~StateToggle; //changement de l'état test tout les 20 ms
    if(StateToggle) {
        PWM3_LoadDutyValue(((Angle)>>3)+50);  //changement du rapport cyclique (environ entre 31 - 63)
        #ifdef I2C1
        G -= I2C_Read1ByteRegister(ADDR_MPU, GYRO_Z_REG_H); //lecture du registre haut du capteur
        #endif
        MATHACC_PIDController(Angle,G); //lancement du PID interne
    } else {
        PWM3_LoadDutyValue(((Angle)>>3)+50);
        if(BAT_GetValue()) { //si batterrie chargé
            CptBat = 0;      //compteur batterie = 0
            if(StateBat == S_bat_low) { //si l'état batterie est à bas (front montant sur l'état baterrie)
                EUSART_Write('B');      //on actualise l'information sur l'app Type/Donnée/Checksum
                EUSART_Write('1');
                EUSART_Write('s');
                StateBat = S_bat_high;  //on met à jour la variable
            }
            if(Validation) {            //si on à eu récement un message
                #ifdef I2C2
                if(Vitesse > 100) {Vitesse = 100;}  //on sature la vitesse envoyée
                I2C_Write1ByteRegister(ADDR_DSPIC, Vitesse, 0); //on envoi la vitesse au DsPIC
                #endif
                Validation--;   //on décémente le temps depuis le dernier message reçu
            } else {
                CptBat++;       //on incrémente le compteur batterrie
                if(CptBat > 100) {
                    CMD_EN_SetLow();   //si on atteint le seuil, on éteint le régulateur 5V
                }
                #ifdef I2C2
                I2C_Write1ByteRegister(ADDR_DSPIC, STOP_MOTEUR, 0); //on envoi une commande d'arrêt au DsPIC
                #endif
            }
        } else {
            if(StateBat == S_bat_high) {    //on actualise l'état de la batterrie sur l'app
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
}

void MyUART_ISR(void) {
    unsigned char c = RC1REG;       //lecture du caractère reçu en UART
    if(c) {                         //s'il n'est pas nul
        switch(PosUart) {           //on test l'état de réception
            case S_Idle:            //récéption du type
                if(c == 'V' || c == 'A' || c == 'P' || c == 'L') { //Vitesse, Angle, Ping, Lumière
                    Type = c;
                    PosUart = S_Data;   //on passe à l'état de récéption de la donnée
                }
                break;
            case S_Data:
                Data = c;               //récéption de la donnée
                PosUart = S_Check;
                break;
            case S_Check:
                if((Type+Data)%256 == c) {  //on vérifie le checksum
                    Validation = 4;         //on remet le compteur à 0
                    if(Type == 'V') {       //on traite le message
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
                            case S_leds_cligno:
                                //do nothing
                                break;
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
                                StateLeds = S_leds_cligno;
                                break;
                        }
                    } else {
                        EUSART_Write('$');  //on envoi des messages d'erreur en retour
                        EUSART_Write('M');
                        EUSART_Write('q');
                    }
                } else {
                    EUSART_Write('$');  //on envoi des checksum d'erreur en retour
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

void MyDelay(void) {
    uint8_t i;
    for(i=0;i<5;i++) {
        if(100-Vitesse > 4) {
            LED_AR_SetLow();
        } else {
            LED_AR_SetHigh();
        }
        if(StateLeds == S_leds_cligno) {
            if(Angle > 102) {
                LED_R_Toggle();
                LED_L_SetLow();
            } else if(Angle < 98) {
                LED_R_SetLow();
                LED_L_Toggle();
            } else {
                LED_R_SetLow();
                LED_L_SetLow();
            }
        }
        __delay_ms(100);
    }
}

void main(void) {
    SYSTEM_Initialize();    //initialisation du système
    
    LED_AR_SetHigh();
    LED_R_SetLow();
    LED_L_SetLow();
    CMD_EN_SetHigh();       //allumage du régulateur
    STATE_SetHigh();        //allumage de la LED utilisateur
    
    #ifdef I2C1
    I2C_Write1ByteRegister(ADDR_MPU, FILTER_REG, FILTER_92HZ);   //réglage de l'IMU
    I2C_Write1ByteRegister(ADDR_MPU, GYRO_SCALE_REG, SCALE);
    #endif
    
    TMR2_SetInterruptHandler(MyTimer2ISR);  //définition de la fonction 'MyTimer2ISR' comme celle d'interruption du timer 2
    TMR2_WriteTimer(255);
    TMR2_StartTimer();                      //démarrage du timer 2
    
    EUSART_SetRxInterruptHandler(MyUART_ISR); //définition de la fonction 'MyUART_ISR' comme celle d'interruption de l'UART
    
    INTERRUPT_PeripheralInterruptEnable();      //allumage des interruptions périphériques
    INTERRUPT_GlobalInterruptEnable();          //allumage des interruption globales
    
    while (1) {
        if(BAT_GetValue()) {       //test batterrie
            if(Validation) {       //test du compteur de messages
                STATE_Toggle();    //si tout vas bien clignotement lent
                MyDelay();
            } else {
                STATE_Toggle();   //non connecté, clignotement rapide
                LED_AR_SetHigh();
                __delay_ms(100);
            }
        } else {
            LED_AR_SetHigh();
            STATE_SetHigh();      //pas de batterrie, allumé fixe
        }
    }
}


/**
 End of File
*/