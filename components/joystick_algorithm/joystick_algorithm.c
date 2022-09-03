#include "joystick_algorithm.h"

int joystick_algorithm_speed(char speed){
    int _speed;
    switch(speed - 48){
        case 0:
        _speed =  0;
        break;
        case 1:
        _speed =  70;
        break;
        case 2:
        _speed =  85;
        break;
        case 3:
        _speed =  100;
        break;
        case 4:
        _speed =  -70;
        break;
        case 5:
        _speed =  -85;
        break;
        case 6:
        _speed =  -100;
        break;
        default:
        _speed =  0;
        break;
    }
    return _speed;
}

int joystick_algorithm_angle(char angle){
    int _angle;
    switch(angle - 48){
        case 0:
        _angle =  0;
        break;
        case 1:
        _angle =  30;
        break;
        case 2:
        _angle =  60;
        break;
        case 3:
        _angle =  90;
        break;
        case 4:
        _angle =  -30;
        break;
        case 5:
        _angle =  -60;
        break;
        case 6:
        _angle =  -90;
        break;
        default:
        _angle =  0;
        break;
    }
    return _angle;
}