#include "State.hpp"

void StateMachine::StateCookie::initState() {
    currentMagUT = Sensors::SensorManager::getInstance().getMagData().abs();
}

void StateMachine::StateCookie::executeState() {
    if(currentMagUT <= COOKIE_ABS_MAGNETIC_THRESHOLD_MAX) {
        float magPercentage = (currentMagUT - COOKIE_ABS_MAGNETIC_THRESHOLD_MIN) /
                              (COOKIE_ABS_MAGNETIC_THRESHOLD_MAX - COOKIE_ABS_MAGNETIC_THRESHOLD_MIN);
        auto timPWMLevel = static_cast<uint8_t>(std::round(magPercentage * TIM_POWER_LEVELS / 2));
        TIM3->CCR3 = IDLE_LED_PWM+ timPWMLevel;
        TIM3->CCR4 = IDLE_LED_PWM+ timPWMLevel;
    }else{
        TIM3->CCR3 = TIM_POWER_LEVELS;
        TIM3->CCR4 = TIM_POWER_LEVELS;
    }
}

StateMachine::StateType StateMachine::StateCookie::checkState() {
    Sensors::SensorManager &sensorManager = Sensors::SensorManager::getInstance();
    float zAcc = sensorManager.getAccData().z;
    currentMagUT = sensorManager.getMagData().abs();
    float yAngVel = std::abs(sensorManager.getGyroData().y);
    if (zAcc >= SLEEP_Z_AXIS_ACCELERATION_THRESHOLD) {
        return StateType::STATE_SLEEP;
    } else if (yAngVel >= NAUSEA_Y_AXIS_ANGULAR_VELOCITY_THRESHOLD) {
        return StateType::STATE_NAUSEA;
    } else if (currentMagUT >= COOKIE_ABS_MAGNETIC_THRESHOLD_MIN) {
        return StateType::STATE_COOKIE;
    } else {
        return StateType::STATE_IDLE;
    }
}

StateMachine::StateType StateMachine::StateCookie::getStateType() const {
    return StateMachine::StateType::STATE_COOKIE;
}
