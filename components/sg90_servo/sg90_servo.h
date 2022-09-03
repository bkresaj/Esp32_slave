/* Servo Motor control example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#ifndef __SG90_SERVO_H__
#define __SG90_SERVO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/mcpwm.h"

static const char *TAG = "servo";

// You can get these value from the datasheet of servo you use, in general pulse width varies between 1000 to 2000 mocrosecond
#define SERVO_MIN_PULSEWIDTH_US (1115) // Minimum pulse width in microsecond
#define SERVO_MAX_PULSEWIDTH_US (1605) // Maximum pulse width in microsecond
#define SERVO_MAX_DEGREE        (90)   // Maximum angle in degree upto which servo can rotate

#define SERVO_PULSE_GPIO        (5)   // GPIO connects to the PWM signal line

static TaskHandle_t servoHandle;
static void servo_task( void * pvParameters );
static void init_servo_motor();
static void run_servo_motor();
static void deinit_servo_motor();
static void suspend_servo_motor();
static void resume_servo_motor();
static uint32_t example_convert_servo_angle_to_duty_us(int angle);
static int _angle, _prev_angle;
static void switch_mode();

class sg90_servo_t{
    public:
    void init();
    void run();
    void deinit();
    void suspend();
    void resume();
    void change_angle(int angle);

};

#ifdef __cplusplus
}
#endif

#endif  //sg90_servo.h

