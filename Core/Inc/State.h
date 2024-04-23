#pragma once

#include "SensorBoard.h"

namespace StateMachine {

    class State{

    public:
        virtual void initState()=0;
        virtual bool getStateConditionsMet()=0;
        virtual ~State() = default;
        virtual void executeState()=0;
    protected:
        State(){}

    };

}