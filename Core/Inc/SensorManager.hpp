#pragma once

#include <memory>
#include <stm32f0xx_hal.h>
#include "FXAS21002.hpp"
#include "FXOS8700.hpp"

namespace Sensors {
    class SensorManager {
    public:
        static inline SensorManager& getInstance(){
            static SensorManager instance;
            return instance;
        }

        void initSensors(const std::shared_ptr<I2C_HandleTypeDef>& i2c_dev);
        void readSensors();
        inline FXOS8700Data& getMagData(){return magAndAccSensor->magMicroT;}
        inline FXOS8700Data& getAccData(){return magAndAccSensor->accelSI;}
        inline FXAS21002Data& getGyroData(){return gyroSensor->gyroSI;}

        SensorManager(const SensorManager&) = delete;
        SensorManager& operator=(const SensorManager&) = delete;

    private:
        std::unique_ptr<FXOS8700> magAndAccSensor = nullptr;
        std::unique_ptr<FXAS21002> gyroSensor = nullptr;
        SensorManager(){}
        ~SensorManager() = default;

    };
}

