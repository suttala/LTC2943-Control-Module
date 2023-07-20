/**
 * @file main.c
 * @author Alarik Sutter (alarik.sutter@aalto.fi)
 * @brief Simple example on how the ChipControl-module is used
 *        to fetch and assign values to the LTC2943 device
 *
 * @date 2023-07-20
 */
#include "LTC2943.h"
#include "ChipControl.h"
#include <stdio.h>

int main() {
    // Initialize the LTC2943 Driver
    if(!LTC2943_Initialise()) {
        return -1;
    }

    // Retrieve and print the current ADC mode
    adc_mode_t resp;
    if (get_adc_mode(&resp) != CMD_STATUS_SUCCESS) {
        return -1;
    }
    printf("Current ADC mode: %02X\n\n", resp);

    // Change the ADC mode to AUTO and print the result
    adc_mode_t new_mode = LTC2943_ADC_MODE_AUTO;
    printf("Setting ADC mode to: %02X ...\n\n", new_mode);
    if (set_adc_mode(new_mode) != CMD_STATUS_SUCCESS) {
        return -1;
    }
    adc_mode_t resp2;
    if (get_adc_mode(&resp2) != CMD_STATUS_SUCCESS) {
        return -1;
    }
    printf("New ADC mode: %02X\n", resp2);

    return 0;
}