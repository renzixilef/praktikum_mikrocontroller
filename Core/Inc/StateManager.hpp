#pragma once
#include "State.hpp"
#include <stm32f0xx_hal.h>
#include "SensorManager.hpp"
#include <memory>
#include <typeinfo>

namespace StateMachine{

    class StateManager{
    public:
        static inline StateManager& getInstance(){
            static StateManager instance;
            return instance;
        }
        bool buttonInterrupt = false;
        void checkForStateTransition();
        StateManager(const StateManager&) = delete;
        StateManager& operator=(const StateManager&) = delete;

    private:
        std::unique_ptr<State> currentState = std::make_unique<StateIdle>();
        StateManager(){}
        ~StateManager() = default;
    };

}