/*
  Software serial multple serial test
 
 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.
 
 The circuit: 
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)
 
 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts, 
 so only the following can be used for RX: 
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69
 
 Not all pins on the Leonardo support change interrupts, 
 so only the following can be used for RX: 
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).
 
 created back in the mists of time
 modified 25 May 2012
 by Tom Igoe
 based on Mikal Hart's example
 
 This example code is in the public domain.
 
 */
#include <SoftwareSerial.h>

#define IDLE  1
#define DATA  2
#define CHECK 3

SoftwareSerial mySerial(2, 3); // RX, TX

int cpt = 0;
uint16_t Vitesse = 0, Angle = 10;
uint8_t Buf[9], PosUart = 0, Data, Type;

void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  //mySerial.println("Hello, world?");
  pinMode(13, OUTPUT);
  digitalWrite(13, 0);
}

void loop() // run over and over
{
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
  if (mySerial.available()) {
    //Serial.write(mySerial.read());
    unsigned char c = mySerial.read();
    if(c) {
        switch(PosUart) {
            case IDLE:
                if(c == 'V' || c == 'A' || c == 'P') {
                    Type = c;
                    PosUart = DATA;
                }
                break;
            case DATA:
                Data = c;
                PosUart = CHECK;
                break;
            case CHECK:
                if((Type+Data)%256 == c) {
                    if(Type == 'V') {
                        Vitesse = Data;
                        Serial.print("V=");
                        Serial.println(Vitesse);
                    } else if(Type == 'A') {
                        Angle = Data;
                        Serial.print("A=");
                        Serial.println(Angle);
                    } else if(Type == 'P') {
                        mySerial.print("P+{");
                        Serial.println("Ping");
                    } else {
                        mySerial.print("$Mq");
                        Serial.println("Err msg");
                    }
                } else {
                    mySerial.print("$Cg");
                    Serial.println("Err CS");
                }
                PosUart = IDLE;
                break;
            default:
                PosUart = IDLE;
                break;
        }
    }
  }
}

