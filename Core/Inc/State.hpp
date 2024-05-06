#pragma once
#include <memory>
#include "StateManager.hpp"
#include <cmath>


#define SLEEP_Z_AXIS_ACCELERATION_THRESHOLD (8.5F)
#define IDLE_LED_PWM (50)
#define NAUSEA_Y_AXIS_ANGULAR_VELOCITY_THRESHOLD (50)
#define COOKIE_ABS_MAGNETIC_THRESHOLD_MIN (20)
#define COOKIE_ABS_MAGNETIC_THRESHOLD_MAX (70)

namespace StateMachine {

    enum class StateType{
        STATE_IDLE,
        STATE_SLEEP,
        STATE_COOKIE,
        STATE_NAUSEA
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
        void initState() override;
        [[nodiscard]] StateType checkState() override;
        [[nodiscard]] inline StateType getStateType() const override;
        void executeState() override;
    private:
        float currentMagUT = 0;
    };

    class StateNausea : public State {
        inline void initState() override;
        [[nodiscard]] StateType checkState() override;
        [[nodiscard]] inline StateType getStateType() const override;
        void executeState() override;
    };

    class StateIdle : public State{
        void initState() override;
        [[nodiscard]] StateType checkState() override;
        [[nodiscard]] inline StateType getStateType() const override;
        inline void executeState() override;
    };

    class StateSleep : public State{
        void initState() override;
        [[nodiscard]] StateType checkState() override;
        [[nodiscard]] inline StateType getStateType() const override;
        inline void executeState() override;
    };


}