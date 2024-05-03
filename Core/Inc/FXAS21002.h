#pragma once

#include <stm32f0xx_hal.h>
#include <memory>

// gyro
#define FXAS21002_OUT_X_MSB (0x01)
#define FXAS21002_DPS_LSB_2000 (0.0625F)
#define FXAS21002_DPS_LSB_1000 (0.03125F)
#define FXAS21002_DPS_LSB_500 (0.015625F)
#define FXAS21002_DPS_LSB_250 (0.0078125F)


// general
#define FXAS21002_ID (0xD7)
#define FXAS21002_CTRL_REG0 (0x0D)
#define FXAS21002_CTRL_REG1 (0x13)

namespace Sensors {
    enum class FXAS21002GyroRange{
        GYRO_RANGE_2000 = 0x00,
        GYRO_RANGE_1000 = 0x01,
        GYRO_RANGE_500 = 0x02,
        GYRO_RANGE_250 = 0x03
    };

    enum class FXAS21002Status{
        STANDBY = 0x00,
        READY = 0x01,
        ACTIVE = 0x02
    };

    struct FXAS21002Data{
        float x;
        float y;
        float z;
    };

    class FXAS21002 {
    public:
        explicit FXAS21002(const std::shared_ptr<I2C_HandleTypeDef>& thisI2cDev);
        void readGyroData();
    private:
        FXAS21002Data gyroSI = {0,0,0};
        FXAS21002GyroRange currentGyroRange = FXAS21002GyroRange::GYRO_RANGE_250;
        FXAS21002Status currentStatus = FXAS21002Status::STANDBY;
        std::shared_ptr<I2C_HandleTypeDef> i2cDev;
        void setStatus(FXAS21002Status status);
        void setGyroRange(FXAS21002GyroRange range);
    };

}