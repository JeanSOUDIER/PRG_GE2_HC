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
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65.2
        Device            :  PIC16F1619
        Driver Version    :  2.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.45
        MPLAB 	          :  MPLAB X 4.15	
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

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set MesBat aliases
#define MesBat_TRIS                 TRISAbits.TRISA0
#define MesBat_LAT                  LATAbits.LATA0
#define MesBat_PORT                 PORTAbits.RA0
#define MesBat_WPU                  WPUAbits.WPUA0
#define MesBat_OD                   ODCONAbits.ODA0
#define MesBat_ANS                  ANSELAbits.ANSA0
#define MesBat_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define MesBat_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define MesBat_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define MesBat_GetValue()           PORTAbits.RA0
#define MesBat_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define MesBat_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define MesBat_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define MesBat_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define MesBat_SetPushPull()        do { ODCONAbits.ODA0 = 0; } while(0)
#define MesBat_SetOpenDrain()       do { ODCONAbits.ODA0 = 1; } while(0)
#define MesBat_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define MesBat_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set State aliases
#define State_TRIS                 TRISAbits.TRISA1
#define State_LAT                  LATAbits.LATA1
#define State_PORT                 PORTAbits.RA1
#define State_WPU                  WPUAbits.WPUA1
#define State_OD                   ODCONAbits.ODA1
#define State_ANS                  ANSELAbits.ANSA1
#define State_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define State_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define State_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define State_GetValue()           PORTAbits.RA1
#define State_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define State_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define State_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define State_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define State_SetPushPull()        do { ODCONAbits.ODA1 = 0; } while(0)
#define State_SetOpenDrain()       do { ODCONAbits.ODA1 = 1; } while(0)
#define State_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define State_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set SDA aliases
#define SDA_TRIS                 TRISBbits.TRISB4
#define SDA_LAT                  LATBbits.LATB4
#define SDA_PORT                 PORTBbits.RB4
#define SDA_WPU                  WPUBbits.WPUB4
#define SDA_OD                   ODCONBbits.ODB4
#define SDA_ANS                  ANSELBbits.ANSB4
#define SDA_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define SDA_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define SDA_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define SDA_GetValue()           PORTBbits.RB4
#define SDA_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define SDA_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define SDA_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define SDA_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define SDA_SetPushPull()        do { ODCONBbits.ODB4 = 0; } while(0)
#define SDA_SetOpenDrain()       do { ODCONBbits.ODB4 = 1; } while(0)
#define SDA_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define SDA_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set RB5 procedures
#define RB5_SetHigh()               do { LATBbits.LATB5 = 1; } while(0)
#define RB5_SetLow()                do { LATBbits.LATB5 = 0; } while(0)
#define RB5_Toggle()                do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define RB5_GetValue()              PORTBbits.RB5
#define RB5_SetDigitalInput()       do { TRISBbits.TRISB5 = 1; } while(0)
#define RB5_SetDigitalOutput()      do { TRISBbits.TRISB5 = 0; } while(0)
#define RB5_SetPullup()             do { WPUBbits.WPUB5 = 1; } while(0)
#define RB5_ResetPullup()           do { WPUBbits.WPUB5 = 0; } while(0)
#define RB5_SetAnalogMode()         do { ANSELBbits.ANSB5 = 1; } while(0)
#define RB5_SetDigitalMode()        do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set SCL aliases
#define SCL_TRIS                 TRISBbits.TRISB6
#define SCL_LAT                  LATBbits.LATB6
#define SCL_PORT                 PORTBbits.RB6
#define SCL_WPU                  WPUBbits.WPUB6
#define SCL_OD                   ODCONBbits.ODB6
#define SCL_ANS                  ANSELBbits.ANSB6
#define SCL_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define SCL_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define SCL_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define SCL_GetValue()           PORTBbits.RB6
#define SCL_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define SCL_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define SCL_SetPullup()          do { WPUBbits.WPUB6 = 1; } while(0)
#define SCL_ResetPullup()        do { WPUBbits.WPUB6 = 0; } while(0)
#define SCL_SetPushPull()        do { ODCONBbits.ODB6 = 0; } while(0)
#define SCL_SetOpenDrain()       do { ODCONBbits.ODB6 = 1; } while(0)
#define SCL_SetAnalogMode()      do { ANSELBbits.ANSB6 = 1; } while(0)
#define SCL_SetDigitalMode()     do { ANSELBbits.ANSB6 = 0; } while(0)

// get/set RC6 procedures
#define RC6_SetHigh()               do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()                do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()                do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()              PORTCbits.RC6
#define RC6_SetDigitalInput()       do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()      do { TRISCbits.TRISC6 = 0; } while(0)
#define RC6_SetPullup()             do { WPUCbits.WPUC6 = 1; } while(0)
#define RC6_ResetPullup()           do { WPUCbits.WPUC6 = 0; } while(0)
#define RC6_SetAnalogMode()         do { ANSELCbits.ANSC6 = 1; } while(0)
#define RC6_SetDigitalMode()        do { ANSELCbits.ANSC6 = 0; } while(0)

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