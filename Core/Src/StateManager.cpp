#include "StateManager.hpp"

void StateMachine::StateManager::checkForStateTransition() {
    StateType currentStateStateType = currentState->getStateType();
    if(buttonInterrupt){
        if(currentStateStateType != StateType::STATE_NAUSEA && currentStateStateType!=StateType::STATE_SLEEP ){
            StateCuddles().initState();
            buttonInterrupt = false;
        }
    }
    Sensors::SensorManager::getInstance().readSensors();
    StateType newState = currentState->checkState();
    if (newState != currentStateStateType) {
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

