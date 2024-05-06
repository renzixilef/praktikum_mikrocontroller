#pragma once

#include <stm32f0xx_hal.h>
#include <memory>
#include <cmath>

// accelerometer
#define FXOS8700_OUT_X_MSB (0x01)
#define FXOS8700_6_BIT_MASK (0x3F)
#define FXOS8700_GRAVITATIONAL_CONSTANT (9.81F)
#define FXOS8700_G_LSB_2G (0.000244F)
#define FXOS8700_G_LSB_4G (0.000488F)
#define FXOS8700_G_LSB_8G (0.000976F)

// magnetometer
#define FXOS8700_M_OUT_X_MSB (0x33)
#define FXOS8700_MAG_UT_LSB (0.1F)

//general
#define FXOS8700_CTRL_REG1 (0x2A)
#define FXOS8700_M_CTRL_REG1 (0x5B)
#define FXOS8700_XYZ_DATA_CFG (0x0E)
#define FXOS8700_ID (0xC7)

namespace Sensors {

    enum class FXOS8700Status{
        STANDBY = 0x00,
        ACTIVE = 0x01
    };
    enum class FXOS8700Mode{
        ACCELEROMETER = 0x00,
        MAGNETOMETER = 0x01,
        BOTH = 0x02
    };
    enum class FXOS8700AccelRange{
        ACCEL_RANGE_2G = 0x00,
        ACCEL_RANGE_4G = 0x01,
        ACCEL_RANGE_8G = 0x02
    };
    struct FXOS8700Data{
        float x;
        float y;
        float z;
        [[nodiscard]] float abs() const {
            return std::sqrt(x*x + y*y + z*z);
        }
    };

    class FXOS8700 {
    public:
        explicit FXOS8700(const std::shared_ptr<I2C_HandleTypeDef>& thisI2cDev);
        void readAccelData();
        void readMagData();
        FXOS8700Data accelSI = {0,0,0};
        FXOS8700Data magMicroT = {0,0,0};
    private:
        FXOS8700AccelRange currentAccelRange = FXOS8700AccelRange::ACCEL_RANGE_2G;
        std::shared_ptr<I2C_HandleTypeDef> i2cDev;
        void setStatus(FXOS8700Status status);
        void setSensorMode(FXOS8700Mode mode);
        void setAccelRange(FXOS8700AccelRange range);
    };

}

