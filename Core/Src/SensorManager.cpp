#include "SensorManager.h"

void Sensors::SensorManager::initSensors(const std::shared_ptr<I2C_HandleTypeDef>& i2c_dev) {
    magAndAccSensor = std::make_unique<FXOS8700>(i2c_dev);
    gyroSensor = std::make_unique<FXAS21002>(i2c_dev);
}

void Sensors::SensorManager::readSensors() {
    magAndAccSensor->readAccelData();
    magAndAccSensor->readMagData();
    gyroSensor->readGyroData();
}

