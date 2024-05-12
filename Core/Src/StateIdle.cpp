#include "State.hpp"

void StateMachine::StateIdle::initState() {
    TIM3->CCR3 = IDLE_LED_PWM;
    TIM3->CCR4 = IDLE_LED_PWM;
}

void StateMachine::StateIdle::executeState() {

}

StateMachine::StateType StateMachine::StateIdle::checkState() {
    Sensors::SensorManager& sensorManager = Sensors::SensorManager::getInstance();
    float zAcc = sensorManager.getAccData().z;
    float totalMag = sensorManager.getMagData().abs();
    float yAngVel = std::abs(sensorManager.getGyroData().y);
    if(zAcc >= SLEEP_Z_AXIS_ACCELERATION_THRESHOLD){
        return StateType::STATE_SLEEP;
    }else if(yAngVel >= NAUSEA_Y_AXIS_ANGULAR_VELOCITY_THRESHOLD){
        return StateType::STATE_NAUSEA;
    }else if(totalMag>=COOKIE_ABS_MAGNETIC_THRESHOLD_MIN){
        return StateType::STATE_COOKIE;
    }else{
        return StateType::STATE_IDLE;
    }
}

StateMachine::StateType StateMachine::StateIdle::getStateType() const {
    return StateMachine::StateType::STATE_IDLE;
}