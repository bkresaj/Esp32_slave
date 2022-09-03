#include "sg90_servo.h"


mcpwm_config_t servo_pwm_config = {
        .frequency = 50, // frequency = 50Hz, i.e. for every servo motor time period should be 20ms
        .cmpr_a = 0,     // duty cycle of PWMxA = 0
        .duty_mode = MCPWM_DUTY_MODE_0,
        .counter_mode = MCPWM_UP_COUNTER,
        
    };

static void servo_task( void * pvParameters )
{   
    while(1) {
    if(_angle != _prev_angle){
    ESP_ERROR_CHECK(mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, example_convert_servo_angle_to_duty_us(_angle)));
    _prev_angle = _angle;
    }
    vTaskDelay(pdMS_TO_TICKS(200)); //Add delay, since it takes time for servo to rotate, generally 100ms/60degree rotation under 5V power supply
    }
}

static void init_servo_motor(){
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, SERVO_PULSE_GPIO); // To drive a RC servo, one MCPWM generator is enough

    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &servo_pwm_config);
}

static void run_servo_motor(){
    xTaskCreate(servo_task, "servo_task", 2048*8, NULL, 6, &servoHandle);
}

static void deinit_servo_motor(){
    vTaskDelete(servoHandle);
}

static void suspend_servo_motor(){
    vTaskSuspend(servoHandle);
}

static void resume_servo_motor(void){
    vTaskResume(servoHandle);
}

static uint32_t example_convert_servo_angle_to_duty_us(int angle){
    return (angle + SERVO_MAX_DEGREE) * (SERVO_MAX_PULSEWIDTH_US - SERVO_MIN_PULSEWIDTH_US) / (2 * SERVO_MAX_DEGREE) + SERVO_MIN_PULSEWIDTH_US;
}

void sg90_servo_t::init(){
    init_servo_motor();
}

void sg90_servo_t::run(){
    run_servo_motor();
}

void sg90_servo_t::deinit(){
    deinit_servo_motor();
}

void sg90_servo_t::suspend(){
    suspend_servo_motor();
}

void sg90_servo_t::resume(){
    resume_servo_motor();
}

void sg90_servo_t::change_angle(int angle){
    _angle = angle;
}