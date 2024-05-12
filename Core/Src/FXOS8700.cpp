#include "../Inc/FXOS8700.hpp"

Sensors::FXOS8700::FXOS8700(const std::shared_ptr<I2C_HandleTypeDef> &thisI2cDev) : i2cDev(thisI2cDev) {
    setAccelRange(FXOS8700AccelRange::ACCEL_RANGE_2G);
    setSensorMode(FXOS8700Mode::BOTH);
    setStatus(FXOS8700Status::ACTIVE);
}

void Sensors::FXOS8700::setSensorMode(Sensors::FXOS8700Mode mode) {
    uint8_t buffer;
    HAL_StatusTypeDef err;
    err = HAL_I2C_Mem_Read(i2cDev.get(), FXOS8700_ID_TRANSMIT, FXOS8700_M_CTRL_REG1, I2C_MEMADD_SIZE_8BIT, &buffer, 1,
                           HAL_MAX_DELAY);
    if (err != HAL_OK) {
        // Error Handling here
    }
    buffer = (buffer & 0xFC) | (static_cast<uint8_t>(mode));
    err = HAL_I2C_Mem_Write(i2cDev.get(), FXOS8700_ID_TRANSMIT, FXOS8700_M_CTRL_REG1,I2C_MEMADD_SIZE_8BIT,
                           &buffer, 1, HAL_MAX_DELAY);
    if (err != HAL_OK) {
        // Error Handling here
    }
}

void Sensors::FXOS8700::setAccelRange(Sensors::FXOS8700AccelRange range) {
    uint8_t buffer;
    HAL_StatusTypeDef err;
    err = HAL_I2C_Mem_Read(i2cDev.get(), FXOS8700_ID_TRANSMIT, FXOS8700_XYZ_DATA_CFG, I2C_MEMADD_SIZE_8BIT, &buffer, 1,
                           HAL_MAX_DELAY);
    if (err != HAL_OK) {
        // Error Handling here
    }
    buffer = (buffer & 0xFC) | (static_cast<uint8_t>(range));
    err = HAL_I2C_Mem_Write(i2cDev.get(), FXOS8700_ID_TRANSMIT, FXOS8700_XYZ_DATA_CFG, I2C_MEMADD_SIZE_8BIT, &buffer, 1,
                           HAL_MAX_DELAY);
    if (err != HAL_OK) {
        // Error Handling here
    }
    currentAccelRange = range;
}


void Sensors::FXOS8700::setStatus(FXOS8700Status status) {
    uint8_t buffer;
    buffer = FXOS8700_CTRL_REG1;
    HAL_StatusTypeDef err;
    err = HAL_I2C_Mem_Read(i2cDev.get(), FXOS8700_ID_TRANSMIT, FXOS8700_CTRL_REG1, I2C_MEMADD_SIZE_8BIT, &buffer, 1,
                           HAL_MAX_DELAY);
    if (err != HAL_OK) {
        // Error Handling here
    }
    buffer = (buffer & 0xFE) | (static_cast<uint8_t>(status));
    err = HAL_I2C_Mem_Write(i2cDev.get(), FXOS8700_ID_TRANSMIT, FXOS8700_CTRL_REG1, I2C_MEMADD_SIZE_8BIT, &buffer, 1,
                            HAL_MAX_DELAY);
    if (err != HAL_OK) {
        // Error Handling here
    }
}

void Sensors::FXOS8700::readMagData() {
    uint8_t buffer[6];
    HAL_StatusTypeDef err;
    err = HAL_I2C_Mem_Read(i2cDev.get(), FXOS8700_ID_TRANSMIT, FXOS8700_M_OUT_X_MSB, I2C_MEMADD_SIZE_8BIT, buffer, 6,
                           HAL_MAX_DELAY);
    if (err != HAL_OK) {
        HAL_Delay(10000);
        // Error Handling here
    }
    int32_t raw_x = ((buffer[0] << 8) | buffer[1]);
    int32_t raw_y = ((buffer[2] << 8) | buffer[3]);
    int32_t raw_z = ((buffer[4] << 8) | buffer[5]);
    // 2's complement
    raw_x = raw_x & 0x8000 ? -((~raw_x + 1) & 0xFFFF) : raw_x;
    raw_y = raw_y & 0x8000 ? -((~raw_y + 1) & 0xFFFF) : raw_y;
    raw_z = raw_z & 0x8000 ? -((~raw_z + 1) & 0xFFFF) : raw_z;
    magMicroT.x = (float) raw_x * FXOS8700_MAG_UT_LSB;
    magMicroT.y = (float) raw_y * FXOS8700_MAG_UT_LSB;
    magMicroT.z = (float) raw_z * FXOS8700_MAG_UT_LSB;
}

void Sensors::FXOS8700::readAccelData() {
    uint8_t buffer[6];
    buffer[0] = FXOS8700_OUT_X_MSB;
    HAL_StatusTypeDef err;
    err = HAL_I2C_Mem_Read(i2cDev.get(), FXOS8700_ID_TRANSMIT, FXOS8700_OUT_X_MSB, I2C_MEMADD_SIZE_8BIT, buffer, 6,
                           HAL_MAX_DELAY);
    if (err != HAL_OK) {
        // Error Handling here
    }
    int32_t raw_x = ((buffer[0] << 6) | (buffer[1] & FXOS8700_6_BIT_MASK));
    int32_t raw_y = ((buffer[2] << 6) | (buffer[3] & FXOS8700_6_BIT_MASK));
    int32_t raw_z = ((buffer[4] << 6) | (buffer[1] & FXOS8700_6_BIT_MASK));
    // 2's complement
    raw_x = raw_x & 0x2000 ? -((~raw_x + 1) & 0x3FFF) : raw_x;
    raw_y = raw_y & 0x2000 ? -((~raw_y + 1) & 0x3FFF) : raw_y;
    raw_z = raw_z & 0x2000 ? -((~raw_z + 1) & 0x3FFF) : raw_z;
    if (currentAccelRange == FXOS8700AccelRange::ACCEL_RANGE_2G) {
        accelSI.x = (float) raw_x * FXOS8700_G_LSB_2G * FXOS8700_GRAVITATIONAL_CONSTANT;
        accelSI.y = (float) raw_y * FXOS8700_G_LSB_2G * FXOS8700_GRAVITATIONAL_CONSTANT;
        accelSI.z = (float) raw_z * FXOS8700_G_LSB_2G * FXOS8700_GRAVITATIONAL_CONSTANT;
    } else if (currentAccelRange == FXOS8700AccelRange::ACCEL_RANGE_4G) {
        accelSI.x = (float) raw_x * FXOS8700_G_LSB_4G * FXOS8700_GRAVITATIONAL_CONSTANT;
        accelSI.y = (float) raw_y * FXOS8700_G_LSB_4G * FXOS8700_GRAVITATIONAL_CONSTANT;
        accelSI.z = (float) raw_z * FXOS8700_G_LSB_4G * FXOS8700_GRAVITATIONAL_CONSTANT;
    } else if (currentAccelRange == FXOS8700AccelRange::ACCEL_RANGE_8G) {
        accelSI.x = (float) raw_x * FXOS8700_G_LSB_8G * FXOS8700_GRAVITATIONAL_CONSTANT;
        accelSI.y = (float) raw_y * FXOS8700_G_LSB_8G * FXOS8700_GRAVITATIONAL_CONSTANT;
        accelSI.z = (float) raw_z * FXOS8700_G_LSB_8G * FXOS8700_GRAVITATIONAL_CONSTANT;
    }
}


