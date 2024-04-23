#pragma once
#include "State.h"
#include "memory"

namespace StateMachine{

    class StateManager{
    public:
        template<typename StateType>
        void performStateTransition(){
            currentState = std::make_unique<StateType>();
            currentState->initState();
        }

        inline void executeState(){
            currentState->executeState();
        }

    private:
        std::unique_ptr<State> currentState;
    };

}