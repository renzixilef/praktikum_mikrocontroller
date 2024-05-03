#pragma once

#include <memory>
#include <stm32f0xx_hal.h>
#include "FXAS21002.h"
#include "FXOS8700.h"

namespace Sensors {
    class SensorManager {
    public:
        static inline SensorManager& getInstance(){
            static SensorManager instance;
            return instance;
        }

        void initSensors(const std::shared_ptr<I2C_HandleTypeDef>& i2c_dev);
        void readSensors();

        SensorManager(const SensorManager&) = delete;
        SensorManager& operator=(const SensorManager&) = delete;

    private:
        std::unique_ptr<FXOS8700> magAndAccSensor = nullptr;
        std::unique_ptr<FXAS21002> gyroSensor = nullptr;
        SensorManager(){}
        ~SensorManager() = default;

    };
}

