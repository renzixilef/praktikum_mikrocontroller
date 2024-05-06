#include "State.hpp"

void StateMachine::StateSleep::initState() {
    TIM3->CCR3 = 0;
    TIM3->CCR4 = 0;
}

void StateMachine::StateSleep::executeState() {

}

StateMachine::StateType StateMachine::StateSleep::checkState() {
    float y_acc = Sensors::SensorManager::getInstance().getAccData().y;
    if(y_acc < SLEEP_Z_AXIS_ACCELERATION_THRESHOLD){
        return StateType::STATE_IDLE;
    }else{
        return StateType::STATE_SLEEP;
    }
}

StateMachine::StateType StateMachine::StateSleep::getStateType() const {
    return StateMachine::StateType::STATE_SLEEP;
}