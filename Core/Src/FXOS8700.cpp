#include "../Inc/FXOS8700.h"

void Sensors::FXOS8700::setSensorMode(Sensors::FXOS8700Mode mode) {
    uint8_t buffer[2];
    buffer[0] = FXOS8700_M_CTRL_REG1;
    HAL_StatusTypeDef err;
    err = HAL_I2C_Master_Transmit(i2c_dev.get(), FXOS8700_ID, buffer, 1, 10);
    if (err != HAL_OK) {
        // Error Handling here
    }
    err = HAL_I2C_Master_Receive(i2c_dev.get(), FXOS8700_ID, &buffer[1], 1, 10);
    if (err != HAL_OK) {
        // Error Handling here
    }
    buffer[1] = (buffer[1] & 0xFC) | (static_cast<uint8_t>(mode));
    err = HAL_I2C_Master_Transmit(i2c_dev.get(), FXOS8700_ID, buffer, 2, 10);
    if (err != HAL_OK) {
        // Error Handling here
    }
}

void Sensors::FXOS8700::setAccelRange(Sensors::FXOS8700AccelRange range) {
    uint8_t buffer[2];
    buffer[0] = FXOS8700_XYZ_DATA_CFG;
    HAL_StatusTypeDef err;
    err = HAL_I2C_Master_Transmit(i2c_dev.get(), FXOS8700_ID, buffer, 1, 10);
    if (err != HAL_OK) {
        // Error Handling here
    }
    err = HAL_I2C_Master_Receive(i2c_dev.get(), FXOS8700_ID, &buffer[1], 1, 10);
    if (err != HAL_OK) {
        // Error Handling here
    }
    buffer[1] = (buffer[1] & 0xFC) | (static_cast<uint8_t>(range));
    err = HAL_I2C_Master_Transmit(i2c_dev.get(), FXOS8700_ID, buffer, 2, 10);
    if (err != HAL_OK) {
        // Error Handling here
    }
}


void Sensors::FXOS8700::setStatus(FXOS8700Status status) {
    uint8_t buffer[2];
    buffer[0] = FXOS8700_CTRL_REG1;
    HAL_StatusTypeDef err;
    err = HAL_I2C_Master_Transmit(i2c_dev.get(), FXOS8700_ID, buffer, 1, 10);
    if (err != HAL_OK) {
        // Error Handling here
    }
    err = HAL_I2C_Master_Receive(i2c_dev.get(), FXOS8700_ID, &buffer[1], 1, 10);
    if (err != HAL_OK) {
        // Error Handling here
    }
    buffer[1] = (buffer[1] & 0xFE) | (static_cast<uint8_t>(status));
    err = HAL_I2C_Master_Transmit(i2c_dev.get(), FXOS8700_ID, buffer, 2, 10);
    if (err != HAL_OK) {
        // Error Handling here
    }
}

void Sensors::FXOS8700::readMagData() {
    uint8_t buffer[6];
    buffer[0] = FXOS8700_M_OUT_X_MSB;
    HAL_StatusTypeDef err;
    err = HAL_I2C_Master_Transmit(i2c_dev.get(), FXOS8700_ID, buffer, 1, 10);
    if (err != HAL_OK) {
        // Error Handling here
    }
    err = HAL_I2C_Master_Receive(i2c_dev.get(), FXOS8700_ID, buffer, 6, 10);
    if (err != HAL_OK) {
        // Error Handling here
    }
    magMicroT.x = (float) ((buffer[0] << 8) | buffer[1]) * FXOS8700_MAG_UT_LSB;
    magMicroT.y = (float) ((buffer[2] << 8) | buffer[3]) * FXOS8700_MAG_UT_LSB;
    magMicroT.z = (float) ((buffer[4] << 8) | buffer[5]) * FXOS8700_MAG_UT_LSB;
}

void Sensors::FXOS8700::readAccelData() {
    uint8_t buffer[6];
    buffer[0] = FXOS8700_OUT_X_MSB;
    HAL_StatusTypeDef err;
    err = HAL_I2C_Master_Transmit(i2c_dev.get(), FXOS8700_ID, buffer, 1, 10);
    if (err != HAL_OK) {
        // Error Handling here
    }
    err = HAL_I2C_Master_Receive(i2c_dev.get(), FXOS8700_ID, buffer, 6, 10);
    if (err != HAL_OK) {
        // Error Handling here
    }
    if (currentAccelRange == FXOS8700AccelRange::ACCEL_RANGE_2G) {
        accelSI.x = (float) ((buffer[0] << 6) | (buffer[1] & FXOS8700_6_BIT_MASK)) * FXOS8700_G_LSB_2G *
                    FXOS8700_GRAVITATIONAL_CONSTANT;
        accelSI.y = (float) ((buffer[2] << 6) | (buffer[3] & FXOS8700_6_BIT_MASK)) * FXOS8700_G_LSB_2G *
                    FXOS8700_GRAVITATIONAL_CONSTANT;
        accelSI.z = (float) ((buffer[4] << 6) | (buffer[5] & FXOS8700_6_BIT_MASK)) * FXOS8700_G_LSB_2G *
                    FXOS8700_GRAVITATIONAL_CONSTANT;
    } else if (currentAccelRange == FXOS8700AccelRange::ACCEL_RANGE_4G) {
        accelSI.x = (float) ((buffer[0] << 6) | (buffer[1] & FXOS8700_6_BIT_MASK)) * FXOS8700_G_LSB_4G *
                    FXOS8700_GRAVITATIONAL_CONSTANT;
        accelSI.y = (float) ((buffer[2] << 6) | (buffer[3] & FXOS8700_6_BIT_MASK)) * FXOS8700_G_LSB_4G *
                    FXOS8700_GRAVITATIONAL_CONSTANT;
        accelSI.z = (float) ((buffer[4] << 6) | (buffer[5] & FXOS8700_6_BIT_MASK)) * FXOS8700_G_LSB_4G *
                    FXOS8700_GRAVITATIONAL_CONSTANT;
    } else if (currentAccelRange == FXOS8700AccelRange::ACCEL_RANGE_8G) {
        accelSI.x = (float) ((buffer[0] << 6) | (buffer[1] & FXOS8700_6_BIT_MASK)) * FXOS8700_G_LSB_8G *
                    FXOS8700_GRAVITATIONAL_CONSTANT;
        accelSI.y = (float) ((buffer[2] << 6) | (buffer[3] & FXOS8700_6_BIT_MASK)) * FXOS8700_G_LSB_8G *
                    FXOS8700_GRAVITATIONAL_CONSTANT;
        accelSI.z = (float) ((buffer[4] << 6) | (buffer[5] & FXOS8700_6_BIT_MASK)) * FXOS8700_G_LSB_8G *
                    FXOS8700_GRAVITATIONAL_CONSTANT;
    }
}

