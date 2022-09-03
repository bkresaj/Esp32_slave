#pragma once

#ifndef __JOYSTICK_ALGORITHM_H__
#define __JOYSTICK_ALGORITHM_H__

#include "stdio.h"
#include "stdint.h"

/*  modes for direction and speed
*   0 - standing still
*   1 - moving forward with 70%
*   2 - moving forward with 85%
*   3 - moving forward with 100%
*   4 - moving backwards with 70%
*   5 - moving backwards with 85%
*   6 - moving backwards with 100%
*   angle - turning right or left from 90 to -90
*   0 - zero angle
*   1 - 30 angle (right)
*   2 - 60 angle (right)
*   3 - 90 angle (right)
*   4- -30 angle (left)
*   5- -60 angle (left)
*   6- -90 angle (left)
*/

//desno i gore su pozitivne vrijednosti, x je za ljevo desno, a y za gore dolje

int joystick_algorithm_speed(char speed);
int joystick_algorithm_angle(char angle);

#endif  //joystick_algorithm.h