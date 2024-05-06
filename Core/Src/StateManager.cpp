#include "StateManager.hpp"

void StateMachine::StateManager::pressButtonInterrupt() {

}

void StateMachine::StateManager::checkForStateTransition() {
    Sensors::SensorManager::getInstance().readSensors();
    StateType newState = currentState->checkState();
    if (newState != currentState->getStateType()) {
        switch (newState){
            case StateType::STATE_IDLE:
            default:
                currentState = std::make_unique<StateIdle>();
                currentState->initState();
                break;
            case StateType::STATE_SLEEP:
                currentState = std::make_unique<StateSleep>();
                currentState->initState();
                break;
            case StateType::STATE_COOKIE:
                currentState = std::make_unique<StateCookie>();
                currentState->initState();
                break;
            case StateType::STATE_NAUSEA:
                currentState = std::make_unique<StateNausea>();
                currentState->initState();
                break;
        }
    } else {
        currentState->executeState();
    }
}

