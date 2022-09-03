/* Servo Motor control example
   This example code is in the Public Domain (or CC0 licensed, at your option.)
   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/mcpwm.h"
#include "gatt_client.c"
#include "sg90_servo.h"
#include "dc_motor.h"

extern "C" {
    #include "joystick_algorithm.h"
	void app_main(void);
}

void main_task(void * pvParameters){
    sg90_servo_t sg90_servo;
    dc_motor_t dc_motor;

    sg90_servo.init();
    dc_motor.init();
    ble_init();

    sg90_servo.run();
    dc_motor.run();

    while(1){

    dc_motor.change_speed(joystick_algorithm_speed(get_speed()));
    sg90_servo.change_angle(joystick_algorithm_angle(get_angle()));
    vTaskDelay(pdMS_TO_TICKS(200));
    
    }
}

extern "C" void app_main(void){
    
    xTaskCreatePinnedToCore(main_task,"main_task",2048*8,NULL,5,NULL,0);
}