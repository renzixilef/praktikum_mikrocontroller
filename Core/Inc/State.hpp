#pragma once
#include <memory>
#include "SensorManager.hpp"
#include <stm32f0xx_hal.h>
#include <cmath>


#define TIM_POWER_LEVELS (20)
#define SLEEP_Z_AXIS_ACCELERATION_THRESHOLD (8.5F)
#define IDLE_LED_PWM (TIM_POWER_LEVELS/2)
#define NAUSEA_Y_AXIS_ANGULAR_VELOCITY_THRESHOLD (25)
#define COOKIE_ABS_MAGNETIC_THRESHOLD_MIN (20)
#define COOKIE_ABS_MAGNETIC_THRESHOLD_MAX (70)

namespace StateMachine {

    enum class StateType{
        STATE_IDLE,
        STATE_SLEEP,
        STATE_COOKIE,
        STATE_NAUSEA,
        STATE_CUDDLES
    };

    class State {
    public:
        virtual void initState() = 0;
        [[nodiscard]] virtual StateType checkState() = 0;
        virtual ~State() = default;
        [[nodiscard]] virtual StateType getStateType() const = 0;
        virtual void executeState() = 0;

    protected:
        State() {}

    };

    class StateCookie : public State {
    public:
        void initState() override;
        [[nodiscard]] StateType checkState() override;
        [[nodiscard]] inline StateType getStateType() const override;
        void executeState() override;
    private:
        float currentMagUT = 0;
    };

    class StateNausea : public State {
    public:
        void initState() override;
        [[nodiscard]] StateType checkState() override;
        [[nodiscard]] inline StateType getStateType() const override;
        void executeState() override;
    private:
        bool maxPWMToogle = false;
    };

    class StateIdle : public State{
    public:
        void initState() override;
        [[nodiscard]] StateType checkState() override;
        [[nodiscard]] inline StateType getStateType() const override;
        inline void executeState() override;
    };

    class StateSleep : public State{
    public:
        void initState() override;
        [[nodiscard]] StateType checkState() override;
        [[nodiscard]] inline StateType getStateType() const override;
        inline void executeState() override;
    };

    class StateCuddles : public State{
    public:
        void initState() override;
    private:
        [[nodiscard]] StateType checkState() override {return StateType::STATE_CUDDLES;}
        [[nodiscard]] inline StateType getStateType() const override {return StateType::STATE_CUDDLES;}
        inline void executeState() override{}

    };


}