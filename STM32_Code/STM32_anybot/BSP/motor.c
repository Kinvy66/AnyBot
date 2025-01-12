/**
* @file motor.c
* @author Kinvy
* @email kinvy66@163.com
* @date: 2025/1/12 16:25
* @description: 
**/
#include "motor.h"
#include "main.h"
#include "stm32f1xx_hal.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;

// 电机1正转
#define MOTOR1_CW       HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_SET); \
                        HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_RESET)
// 电机1=2反转
#define MOTOR1_CWW      HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_RESET); \
                        HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_SET)

// 电机1正转
#define MOTOR2_CW       HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_SET); \
                        HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_RESET)
// 电机1=2反转
#define MOTOR2_CWW      HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_RESET); \
                        HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_SET)


/**
 * @brief 输出pwm 控制电机
 * @param pwm1 +顺时针，-逆时针
 * @param pwm2 +逆时针，-顺时针
 */
void pwmOutputTb6612(int pwm1, int pwm2) {
    if (pwm1 < 0) {
        pwm1 = -pwm1;
        MOTOR1_CW;
    } else {
        MOTOR1_CWW;
    }
    if (pwm2 < 0) {
        pwm2 = -pwm2;
        MOTOR2_CW;
    } else {
        MOTOR2_CWW;
    }
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,pwm1);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4,pwm2);
}
