#include "FXAS21002.h"


Sensors::FXAS21002::FXAS21002(const std::shared_ptr<I2C_HandleTypeDef> &thisI2cDev) : i2cDev(thisI2cDev) {
    setGyroRange(FXAS21002GyroRange::GYRO_RANGE_250);
    setStatus(FXAS21002Status::ACTIVE);
}

void Sensors::FXAS21002::setStatus(Sensors::FXAS21002Status status) {
    uint8_t buffer[2];
    buffer[0] = FXAS21002_CTRL_REG1;
    HAL_StatusTypeDef err;
    err = HAL_I2C_Master_Transmit(i2cDev.get(), FXAS21002_ID, buffer, 1, 10);
    if (err != HAL_OK) {
        // Error Handling here
    }
    err = HAL_I2C_Master_Receive(i2cDev.get(), FXAS21002_ID, &buffer[1], 1, 10);
    if (err != HAL_OK) {
        // Error Handling here
    }
    buffer[1] = (buffer[1] & 0xFC) | (static_cast<uint8_t>(status));
    err = HAL_I2C_Master_Transmit(i2cDev.get(), FXAS21002_ID, buffer, 2, 10);
    if (err != HAL_OK) {
        // Error Handling here
    }
}

void Sensors::FXAS21002::setGyroRange(Sensors::FXAS21002GyroRange range) {
    FXAS21002Status originalStatus = currentStatus;
    if (originalStatus == FXAS21002Status::ACTIVE) {
        setStatus(FXAS21002Status::STANDBY);
    }
    uint8_t buffer[2];
    buffer[0] = FXAS21002_CTRL_REG0;
    HAL_StatusTypeDef err;
    err = HAL_I2C_Master_Transmit(i2cDev.get(), FXAS21002_ID, buffer, 1, 10);
    if (err != HAL_OK) {
        // Error Handling here
    }
    err = HAL_I2C_Master_Receive(i2cDev.get(), FXAS21002_ID, &buffer[1], 1, 10);
    if (err != HAL_OK) {
        // Error Handling here
    }
    buffer[1] = (buffer[1] & 0xFC) | (static_cast<uint8_t>(range));
    err = HAL_I2C_Master_Transmit(i2cDev.get(), FXAS21002_ID, buffer, 2, 10);
    if (err != HAL_OK) {
        // Error Handling here
    }
    if (currentStatus != originalStatus) {
        setStatus(originalStatus);
    }
}

void Sensors::FXAS21002::readGyroData() {
    uint8_t buffer[6];
    buffer[0] = FXAS21002_OUT_X_MSB;
    HAL_StatusTypeDef err;
    err = HAL_I2C_Master_Transmit(i2cDev.get(), FXAS21002_ID, buffer, 1, 10);
    if (err != HAL_OK) {
        // Error Handling here
    }
    err = HAL_I2C_Master_Receive(i2cDev.get(), FXAS21002_ID, buffer, 6, 10);
    if (err != HAL_OK) {
        // Error Handling here
    }
    if (currentGyroRange == FXAS21002GyroRange::GYRO_RANGE_2000) {
        gyroSI.x = (float) ((buffer[0] << 8) | buffer[1]) * FXAS21002_DPS_LSB_2000;
        gyroSI.y = (float) ((buffer[2] << 8) | buffer[3]) * FXAS21002_DPS_LSB_2000;
        gyroSI.z = (float) ((buffer[4] << 8) | buffer[5]) * FXAS21002_DPS_LSB_2000;
    } else if (currentGyroRange == FXAS21002GyroRange::GYRO_RANGE_1000) {
        gyroSI.x = (float) ((buffer[0] << 8) | buffer[1]) * FXAS21002_DPS_LSB_1000;
        gyroSI.y = (float) ((buffer[2] << 8) | buffer[3]) * FXAS21002_DPS_LSB_1000;
        gyroSI.z = (float) ((buffer[4] << 8) | buffer[5]) * FXAS21002_DPS_LSB_1000;
    } else if (currentGyroRange == FXAS21002GyroRange::GYRO_RANGE_500) {
        gyroSI.x = (float) ((buffer[0] << 8) | buffer[1]) * FXAS21002_DPS_LSB_500;
        gyroSI.y = (float) ((buffer[2] << 8) | buffer[3]) * FXAS21002_DPS_LSB_500;
        gyroSI.z = (float) ((buffer[4] << 8) | buffer[5]) * FXAS21002_DPS_LSB_500;
    } else if (currentGyroRange == FXAS21002GyroRange::GYRO_RANGE_250) {
        gyroSI.x = (float) ((buffer[0] << 8) | buffer[1]) * FXAS21002_DPS_LSB_250;
        gyroSI.y = (float) ((buffer[2] << 8) | buffer[3]) * FXAS21002_DPS_LSB_250;
        gyroSI.z = (float) ((buffer[4] << 8) | buffer[5]) * FXAS21002_DPS_LSB_250;
    }
}
