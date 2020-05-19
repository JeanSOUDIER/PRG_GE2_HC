/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.79.0
        Device            :  PIC16F1619
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.10 and above
        MPLAB 	          :  MPLAB X 5.30	
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set RA2 procedures
#define RA2_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define RA2_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define RA2_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define RA2_GetValue()              PORTAbits.RA2
#define RA2_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define RA2_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define RA2_SetPullup()             do { WPUAbits.WPUA2 = 1; } while(0)
#define RA2_ResetPullup()           do { WPUAbits.WPUA2 = 0; } while(0)
#define RA2_SetAnalogMode()         do { ANSELAbits.ANSA2 = 1; } while(0)
#define RA2_SetDigitalMode()        do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set BAT aliases
#define BAT_TRIS                 TRISAbits.TRISA4
#define BAT_LAT                  LATAbits.LATA4
#define BAT_PORT                 PORTAbits.RA4
#define BAT_WPU                  WPUAbits.WPUA4
#define BAT_OD                   ODCONAbits.ODA4
#define BAT_ANS                  ANSELAbits.ANSA4
#define BAT_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define BAT_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define BAT_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define BAT_GetValue()           PORTAbits.RA4
#define BAT_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define BAT_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define BAT_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define BAT_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define BAT_SetPushPull()        do { ODCONAbits.ODA4 = 0; } while(0)
#define BAT_SetOpenDrain()       do { ODCONAbits.ODA4 = 1; } while(0)
#define BAT_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define BAT_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set STATE aliases
#define STATE_TRIS                 TRISAbits.TRISA5
#define STATE_LAT                  LATAbits.LATA5
#define STATE_PORT                 PORTAbits.RA5
#define STATE_WPU                  WPUAbits.WPUA5
#define STATE_OD                   ODCONAbits.ODA5
#define STATE_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define STATE_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define STATE_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define STATE_GetValue()           PORTAbits.RA5
#define STATE_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define STATE_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define STATE_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define STATE_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define STATE_SetPushPull()        do { ODCONAbits.ODA5 = 0; } while(0)
#define STATE_SetOpenDrain()       do { ODCONAbits.ODA5 = 1; } while(0)

// get/set RB4 procedures
#define RB4_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define RB4_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define RB4_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define RB4_GetValue()              PORTBbits.RB4
#define RB4_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define RB4_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define RB4_SetPullup()             do { WPUBbits.WPUB4 = 1; } while(0)
#define RB4_ResetPullup()           do { WPUBbits.WPUB4 = 0; } while(0)
#define RB4_SetAnalogMode()         do { ANSELBbits.ANSB4 = 1; } while(0)
#define RB4_SetDigitalMode()        do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set RB5 procedures
#define RB5_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define RB5_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define RB5_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define RB5_GetValue()              PORTBbits.RB5
#define RB5_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define RB5_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define RB5_SetPullup()             do { WPUBbits.WPUB5 = 1; } while(0)
#define RB5_ResetPullup()           do { WPUBbits.WPUB5 = 0; } while(0)
#define RB5_SetAnalogMode()         do { ANSELBbits.ANSB5 = 1; } while(0)
#define RB5_SetDigitalMode()        do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set RB6 procedures
#define RB6_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define RB6_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define RB6_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define RB6_GetValue()              PORTBbits.RB6
#define RB6_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define RB6_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define RB6_SetPullup()             do { WPUBbits.WPUB6 = 1; } while(0)
#define RB6_ResetPullup()           do { WPUBbits.WPUB6 = 0; } while(0)
#define RB6_SetAnalogMode()         do { ANSELBbits.ANSB6 = 1; } while(0)
#define RB6_SetDigitalMode()        do { ANSELBbits.ANSB6 = 0; } while(0)

// get/set RB7 procedures
#define RB7_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define RB7_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define RB7_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define RB7_GetValue()              PORTBbits.RB7
#define RB7_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define RB7_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define RB7_SetPullup()             do { WPUBbits.WPUB7 = 1; } while(0)
#define RB7_ResetPullup()           do { WPUBbits.WPUB7 = 0; } while(0)
#define RB7_SetAnalogMode()         do { ANSELBbits.ANSB7 = 1; } while(0)
#define RB7_SetDigitalMode()        do { ANSELBbits.ANSB7 = 0; } while(0)

// get/set LED_AR aliases
#define LED_AR_TRIS                 TRISCbits.TRISC4
#define LED_AR_LAT                  LATCbits.LATC4
#define LED_AR_PORT                 PORTCbits.RC4
#define LED_AR_WPU                  WPUCbits.WPUC4
#define LED_AR_OD                   ODCONCbits.ODC4
#define LED_AR_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define LED_AR_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define LED_AR_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define LED_AR_GetValue()           PORTCbits.RC4
#define LED_AR_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define LED_AR_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define LED_AR_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define LED_AR_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define LED_AR_SetPushPull()        do { ODCONCbits.ODC4 = 0; } while(0)
#define LED_AR_SetOpenDrain()       do { ODCONCbits.ODC4 = 1; } while(0)

// get/set CMD_EN aliases
#define CMD_EN_TRIS                 TRISCbits.TRISC5
#define CMD_EN_LAT                  LATCbits.LATC5
#define CMD_EN_PORT                 PORTCbits.RC5
#define CMD_EN_WPU                  WPUCbits.WPUC5
#define CMD_EN_OD                   ODCONCbits.ODC5
#define CMD_EN_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define CMD_EN_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define CMD_EN_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define CMD_EN_GetValue()           PORTCbits.RC5
#define CMD_EN_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define CMD_EN_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define CMD_EN_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define CMD_EN_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define CMD_EN_SetPushPull()        do { ODCONCbits.ODC5 = 0; } while(0)
#define CMD_EN_SetOpenDrain()       do { ODCONCbits.ODC5 = 1; } while(0)

// get/set LED_R aliases
#define LED_R_TRIS                 TRISCbits.TRISC6
#define LED_R_LAT                  LATCbits.LATC6
#define LED_R_PORT                 PORTCbits.RC6
#define LED_R_WPU                  WPUCbits.WPUC6
#define LED_R_OD                   ODCONCbits.ODC6
#define LED_R_ANS                  ANSELCbits.ANSC6
#define LED_R_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define LED_R_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define LED_R_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define LED_R_GetValue()           PORTCbits.RC6
#define LED_R_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define LED_R_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define LED_R_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define LED_R_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define LED_R_SetPushPull()        do { ODCONCbits.ODC6 = 0; } while(0)
#define LED_R_SetOpenDrain()       do { ODCONCbits.ODC6 = 1; } while(0)
#define LED_R_SetAnalogMode()      do { ANSELCbits.ANSC6 = 1; } while(0)
#define LED_R_SetDigitalMode()     do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set LED_L aliases
#define LED_L_TRIS                 TRISCbits.TRISC7
#define LED_L_LAT                  LATCbits.LATC7
#define LED_L_PORT                 PORTCbits.RC7
#define LED_L_WPU                  WPUCbits.WPUC7
#define LED_L_OD                   ODCONCbits.ODC7
#define LED_L_ANS                  ANSELCbits.ANSC7
#define LED_L_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define LED_L_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define LED_L_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define LED_L_GetValue()           PORTCbits.RC7
#define LED_L_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define LED_L_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define LED_L_SetPullup()          do { WPUCbits.WPUC7 = 1; } while(0)
#define LED_L_ResetPullup()        do { WPUCbits.WPUC7 = 0; } while(0)
#define LED_L_SetPushPull()        do { ODCONCbits.ODC7 = 0; } while(0)
#define LED_L_SetOpenDrain()       do { ODCONCbits.ODC7 = 1; } while(0)
#define LED_L_SetAnalogMode()      do { ANSELCbits.ANSC7 = 1; } while(0)
#define LED_L_SetDigitalMode()     do { ANSELCbits.ANSC7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/