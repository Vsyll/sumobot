#ifndef TOF_H
#define TOF_H

#include <Arduino.h>
#include <VL53L0X.h>
#include "config.h"

class TOF
{
public:
    void begin();
    void update();

    uint16_t getDistance(SensorID id) const;

private:
    // =========================================
    // Sensor
    // =========================================

    VL53L0X sensors[SENSOR_COUNT];
    uint16_t distances[SENSOR_COUNT] = {0};
    bool sensorReady[SENSOR_COUNT] = {false};
    void initSensor(uint8_t id);

    // =========================================
    // Median Filter
    // =========================================
    
    struct MedianFilter
    {
        uint16_t readings[FILTER_SIZE];
        uint8_t index = 0;
        bool full = false;
    };

    MedianFilter filters[SENSOR_COUNT];

    uint16_t updateMedian(
        MedianFilter &filter,
        uint16_t value
    );

    // =========================================
    // Threshold Tof
    // =========================================

    uint16_t applyThreshold(uint16_t distance);
};

#endif