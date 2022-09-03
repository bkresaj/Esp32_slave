#include "dc_motor.h"

static void switch_mode() {

        if(_speed > 0){
            gpio_set_level(DC_MOTOR_GPIO_IN3, 1);
            gpio_set_level(DC_MOTOR_GPIO_IN4, 0);
        }
        else if(_speed < 0){
            _speed = -(_speed);
            gpio_set_level(DC_MOTOR_GPIO_IN3, 0);
            gpio_set_level(DC_MOTOR_GPIO_IN4, 1);
        }
        else {
            gpio_set_level(DC_MOTOR_GPIO_IN3, 0);
            gpio_set_level(DC_MOTOR_GPIO_IN4, 0);
        }
        switch (_speed) {
            case 0:
                ESP_LOGI(tag, "0 percentage of speed");
                // Set duty to 0%
                ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, SPEED_MODE_0));
                // Update duty to apply the new value
                ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));
                break;
            
            case 70:
                ESP_LOGI(tag, "70 percentage of speed");
                // Set duty to 90%
                ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, SPEED_MODE_70));
                // Update duty to apply the new value
                ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));
                break;
            case 85:
                ESP_LOGI(tag, "85 percentage of speed");
                // Set duty to 100%
                ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, SPEED_MODE_85));
                // Update duty to apply the new value
                ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));
                break;
            case 100:
                ESP_LOGI(tag, "100 percentage of speed");
                // Set duty to 100%
                ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, SPEED_MODE_100));
                // Update duty to apply the new value
                ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));
                break;
            default:
                ESP_LOGI(tag, "0 percentage of speed");
                // Set duty to 50%
                ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, SPEED_MODE_0));
                // Update duty to apply the new value
                ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));
        }
}

static void dc_motor_task( void * pvParameters )
{   
    while(1) {
    if(_speed != _prev_speed){
    switch_mode();
    _prev_speed = _speed;
    }
    vTaskDelay(pdMS_TO_TICKS(200));
    }
}

void dc_motor_t::init(void){
    // Prepare and then apply the LEDC PWM timer configuration
    ledc_timer_config_t ledc_timer = {
            .speed_mode       = LEDC_MODE,
            .duty_resolution  = LEDC_DUTY_RES,
            .timer_num        = LEDC_TIMER,
            .freq_hz          = LEDC_FREQUENCY,  // Set output frequency at 5 kHz
            .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    // Prepare and then apply the LEDC PWM channel configuration
    ledc_channel_config_t ledc_channel = {
            .gpio_num       = LEDC_OUTPUT_IO,
            .speed_mode     = LEDC_MODE,
            .channel        = LEDC_CHANNEL,
            .intr_type      = LEDC_INTR_DISABLE,
            .timer_sel      = LEDC_TIMER,
            .duty           = 0, // Set duty to 0%
            .hpoint         = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));

    gpio_reset_pin(DC_MOTOR_GPIO_IN3);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(DC_MOTOR_GPIO_IN3, GPIO_MODE_OUTPUT);

    gpio_reset_pin(DC_MOTOR_GPIO_IN4);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(DC_MOTOR_GPIO_IN4, GPIO_MODE_OUTPUT);
}

void dc_motor_t::run(){
    xTaskCreate(dc_motor_task, "dc_motor_task", 2048*8, NULL, 6, &dcMotorHandle);
}

void dc_motor_t::deinit(void){
    vTaskDelete(dcMotorHandle);
}

void dc_motor_t::suspend(void){
    vTaskSuspend(dcMotorHandle);
}

void dc_motor_t::resume(void){
    vTaskResume(dcMotorHandle);
}

void dc_motor_t::change_speed(int speed){
    _speed = speed;
}
