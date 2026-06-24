#include "tof.h"
#include <Wire.h>

// =====================================================
// Tof
// =====================================================

void TOF::initSensor(uint8_t id)
{
    digitalWrite(XSHUT_PINS[id], HIGH);
    delay(10);
    sensors[id].setTimeout(TOF_TIMEOUT);

     if (!sensors[id].init())
    {
        // Serial.print(SENSOR_NAMES[id]);
        // Serial.println(" gagal init!");

        sensorReady[id] = false;
        return;
    }

    sensors[id].setAddress(SENSOR_ADDRESSES[id]);
    sensors[id].setMeasurementTimingBudget(TOF_TIMING_BUDGET);
    sensors[id].startContinuous();

    sensorReady[id] = true;
    // Serial.print(SENSOR_NAMES[id]);
    // Serial.print(" OK");
}

void TOF::begin()
{
    Wire.setSDA(I2C_SDA_PIN);
    Wire.setSCL(I2C_SCL_PIN);
    Wire.begin();
    Wire.setClock(I2C_CLOCK);
    
    for (int i = 0; i < SENSOR_COUNT; i++)
    {
        pinMode(XSHUT_PINS[i], OUTPUT);
        digitalWrite(XSHUT_PINS[i],LOW);
    }
    delay(10);

    for (int i = 0; i < 2; i++)
    {
        initSensor(i);
    }
    //Serial.println("Semua TOF siap");
}

void TOF::update()
{   
    for (int i = 0; i < 2; i++)
    {
        if (!sensorReady[i])
        {
            distances[i] = 0;
            continue;
        }

        uint16_t raw = sensors[i].readRangeContinuousMillimeters();
        if (sensors[i].timeoutOccurred() || raw >= 8190)
        {
            distances[i] = 0;
            continue;
        }

        uint16_t filtered = updateMedian(filters[i], raw);
        distances[i] = applyThreshold(filtered);
    }
}

uint16_t TOF::getDistance (SensorID id) const
{
    return distances[id];
}

// =====================================================
// Median Filter
// =====================================================

uint16_t TOF::updateMedian(MedianFilter &filter, uint16_t value)
{
    filter.readings[filter.index] = value;
    filter.index = (filter.index + 1) % FILTER_SIZE;
    if (filter.index == 0)
    {
        filter.full = true;
    }
    int count = filter.full ? FILTER_SIZE : filter.index;

    if (count == 0)
    {
        return value;
    }

    uint16_t sorted[FILTER_SIZE];

    memcpy(sorted, filter.readings, count * sizeof(uint16_t));

    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (sorted[j] > sorted[j + 1])
            {
                uint16_t temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }
    return sorted[count / 2];
}

// =========================================
// Threshold Tof
// =========================================

uint16_t TOF::applyThreshold(uint16_t distance)
{
    if (distance < TOF_MIN_DISTANCE || distance > TOF_MAX_DISTANCE) {
        return 0;
    }
    return distance;
}