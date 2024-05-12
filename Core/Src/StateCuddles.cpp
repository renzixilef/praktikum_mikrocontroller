#include "State.hpp"

void StateMachine::StateCuddles::initState() {
    uint8_t ccr3Value = TIM3->CCR3;
    uint8_t ccr4Value = TIM3->CCR4;
    TIM3->CCR3 = 0;
    TIM3->CCR4 = 0;
    for(uint8_t pwm_val = 0;pwm_val<=TIM_POWER_LEVELS;pwm_val++) {
        TIM3->CCR3 = pwm_val;
        TIM3->CCR4 = pwm_val;
        HAL_Delay(100);
    }
    TIM3->CCR3 = ccr3Value;
    TIM3->CCR4 = ccr4Value;
}