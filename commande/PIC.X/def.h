#include "mcc_generated_files/examples/i2c_master_example.h"

#define ADDR_MPU_R      0xE8
#define ADDR_MPU_W      0x68
#define ADDR_MPU        0x68

#define GYRO_Z_REG_H    0x47
#define GYRO_Z_REG_L    0x48
#define FILTER_REG      0x26
#define GYRO_SCALE_REG  0x27

#define FILTER_92HZ     0x02 //0x05
#define SCALE           0x10 //8G

#define ADDR_DSPIC      0x40

#define STOP_MOTEUR     101

void MyTimer2ISR(void);
void MyUART_ISR(void);


typedef enum {S_Idle, S_Data, S_Check} state;
typedef enum {S_leds_off, S_led_r, S_led_l, S_leds_on} state_led;
typedef enum {S_bat_low, S_bat_high} state_bat;