/**
 * @file LTC2943.c
 * @author Alarik Sutter (alarik.sutter@aalto.fi)
 * @brief Example Driver API code for the LTC2943 Device
 *
 * @date 2023-07-20
 * @note THIS "DUMMY" SOURCE CODE IS ONLY FOR TESTING THE
 *       CHIPCONTROL MODULE WITH THE PROVIDED MAIN.C
 */
#include "LTC2943.h"

static uint8_t resp = 0x00;
/* Mocks the initialization of the LTC2943 Driver */
bool LTC2943_Initialise() { return true; }

/* Mocks reading any register from the LTC2943 device, always returns resp-value */
bool LTC2943_Read(uint8_t address, uint8_t *dest, uint8_t dataSize) {
    *dest = resp;
    return true;
}

/* Mocks writing to any register on the LTC2943 device, writes on top of the resp-value */
bool LTC2943_Write(uint8_t address, uint8_t *src, uint8_t dataSize) {
    resp = *src;
    return true;
}
