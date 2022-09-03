/* Servo Motor control example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#ifndef __DC_MOTOR_H__
#define __DC_MOTOR_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "math.h"
#include "esp_log.h"
#include "driver/mcpwm.h"

#define DC_MOTOR_GPIO_IN3       GPIO_NUM_18  
#define DC_MOTOR_GPIO_IN4       GPIO_NUM_23   
#define DC_MOTOR_GPIO_PWM       (19)   // GPIO connects to the PWM signal line

#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_MODE               LEDC_LOW_SPEED_MODE  
#define LEDC_OUTPUT_IO          DC_MOTOR_GPIO_PWM // Define the output GPIO
#define LEDC_CHANNEL            LEDC_CHANNEL_0
#define LEDC_DUTY_RES           LEDC_TIMER_13_BIT // Set duty resolution to 13 bits
#define LEDC_DUTY               (0) 
#define LEDC_FREQUENCY          (5000) // Frequency in Hertz. Set frequency at 5 kHz

#define SPEED_MODE_0     ((pow(2.0, 13.0) - 1) * 0.0) // off
#define SPEED_MODE_70    ((pow(2.0, 13.0) - 1) * 0.7) // 50%
#define SPEED_MODE_85    ((pow(2.0, 13.0) - 1) * 0.85) // 75%
#define SPEED_MODE_100   (8191) // 100% = (2 ** 13) - 1

static const char *tag = "dc_motor";

static TaskHandle_t dcMotorHandle;
static int _speed, _prev_speed;
static void switch_mode();

class dc_motor_t{
    private:
    
    public:
    void init();
    void run();
    void deinit();
    void suspend();
    void resume();
    void change_speed(int speed);

};

#ifdef __cplusplus
}
#endif

#endif  //dc_motor.h