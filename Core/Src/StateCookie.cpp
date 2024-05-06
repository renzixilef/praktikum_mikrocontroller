#include "State.hpp"

void StateMachine::StateCookie::initState() {
    currentMagUT = Sensors::SensorManager::getInstance().getMagData().abs();
}

void StateMachine::StateCookie::executeState() {
    currentMagUT = Sensors::SensorManager::getInstance().getMagData().abs();
}

StateMachine::StateType StateMachine::StateCookie::checkState() {
    if(currentMagUT<COOKIE_ABS_MAGNETIC_THRESHOLD_MIN){
        return StateType::STATE_IDLE;
    }
}

StateMachine::StateType StateMachine::StateCookie::getStateType() const {
    return StateMachine::StateType::STATE_COOKIE;
}
