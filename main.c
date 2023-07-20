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
    adc_mode_t resp;

    // Initialize the LTC2943 Driver
    if(!LTC2943_Initialise()) {
        return -1;
    }

    // Retrieve and print the current ADC mode
    if (get_adc_mode(&resp) != CMD_STATUS_SUCCESS) {
        return -1;
    }
    printf("Current ADC mode: %02X\n\n", resp);

    // Change the ADC mode to AUTO and print the result
    printf("Setting ADC mode to: %02X ...\n\n", LTC2943_ADC_MODE_AUTO);
    if (set_adc_mode_auto() != CMD_STATUS_SUCCESS) {
        return -1;
    }
    if (get_adc_mode(&resp) != CMD_STATUS_SUCCESS) {
        return -1;
    }
    printf("New ADC mode: %02X\n", resp);

    return 0;
}