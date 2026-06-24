#pragma once

#include <Arduino.h>

// =====================================================
// I2C
// =====================================================

inline constexpr uint8_t I2C_SDA_PIN = PB7;
inline constexpr uint8_t I2C_SCL_PIN = PB6;

// =====================================================
// Tof
// =====================================================

enum SensorID
{
    FRONT1 = 0, FRONT2, RIGHT, LEFT,
    SENSOR_COUNT
};

inline constexpr uint8_t XSHUT_PINS[SENSOR_COUNT] =
{
    PA1, // FRONT1 
    PA2, // FRONT2
    PA3, // RIGHT
    PA4  // LEFT
};

inline constexpr uint8_t SENSOR_ADDRESSES[SENSOR_COUNT] =
{
    0x30, 0x31, 0x32, 0x33
};

inline constexpr const char* SENSOR_NAMES[SENSOR_COUNT] =
{
    "Front1", "Front2", "Right", "Left"
};

inline constexpr uint16_t TOF_TIMEOUT = 100;
inline constexpr uint32_t TOF_TIMING_BUDGET = 33000;
inline constexpr uint32_t I2C_CLOCK = 400000;

// =====================================================
// Median Filter Configuration
// =====================================================

inline constexpr uint8_t FILTER_SIZE = 3;

// =====================================================
// TOF Threshold
// =====================================================

inline constexpr uint16_t TOF_MIN_DISTANCE = 30;
inline constexpr uint16_t TOF_MAX_DISTANCE = 1200;

// =====================================================
// Debug Configuration
// =====================================================

inline constexpr uint32_t SERIAL_BAUDRATE = 115200;

// =====================================================
// Motor TB6612
// =====================================================

inline constexpr uint8_t MOTOR_STBY_PIN = PB12;

// Motor Kiri (A)

inline constexpr uint8_t LEFT_IN1_PIN = PB0;
inline constexpr uint8_t LEFT_IN2_PIN = PB1;
inline constexpr uint8_t LEFT_PWM_PIN = PB6;

// Motor Kanan (B)

inline constexpr uint8_t RIGHT_IN1_PIN = PB10;
//inline constexpr uint8_t RIGHT_IN2_PIN = PB11;
inline constexpr uint8_t RIGHT_PWM_PIN = PB7;

// =====================================================
// Motor Configuration
// =====================================================

inline constexpr uint16_t MOTOR_MAX_PWM = 255;

// 20 kHz
inline constexpr uint32_t MOTOR_PWM_FREQUENCY = 20000;

// =====================================================
// IR
// =====================================================

inline constexpr uint8_t IR_FRONT_LEFT_PIN  = PA5;
inline constexpr uint8_t IR_FRONT_RIGHT_PIN = PA6;
inline constexpr uint8_t IR_REAR_PIN        = PA7;

// =====================================================
// DIP SWITCH
// =====================================================

inline constexpr uint8_t DIP1_PIN = PA8;
inline constexpr uint8_t DIP2_PIN = PA9;

// =====================================================
// Simulation
// =====================================================

inline constexpr bool SIMULATION_MODE = false;

// =====================================================
// Strategy
// =====================================================

enum StrategyID
{
    STRATEGY_1,
    STRATEGY_2,
    STRATEGY_3,
    STRATEGY_4
};
inline constexpr uint16_t ATTACK_DISTANCE = 600;
inline constexpr uint16_t LAST_SEEN_TIMEOUT = 1000;

// =====================================================
// Manual State
// =====================================================

inline constexpr bool MANUAL_STRATEGY = true;
inline constexpr StrategyID TEST_STRATEGY = STRATEGY_1;