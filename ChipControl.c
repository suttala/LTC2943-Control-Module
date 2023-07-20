/**
 * @file ChipControl.c
 * @author Alarik Sutter (alarik.sutter@aalto.fi)
 * @brief Source for the LTC2943 ChipControl C-module
 *
 * @date 2023-07-20
 */
#include "ChipControl.h"
#include "LTC2943.h"

/* STATIC HELPER FUNCTIONS */

/**
 * @brief Returns a byte where a given mask was applied
 *
 * @param data : The whole register
 * @param mask : Mask that is used to null out unnecessary bits from the register
 * @return uint8_t
 */
static uint8_t get_bits_by_mask(uint8_t data, uint8_t mask) {
    return data & mask;
}

/**
 * @brief Alters the data to hold the given values according to the mask
 *
 * @param data : The byte that is being altered
 * @param mask : Mask used in finding which bits to set
 * @param value : Byte that defines new binary values
 */
static void set_bits_by_mask(uint8_t *data, uint8_t mask, uint8_t value) {
    *data = (*data & ~mask) | (value & mask);
}

/**
 * @brief Gets the most significant byte from a 16-bit value
 *
 * @param data : The 16-bit value to get the high byte from
 * @return uint8_t
 */
static uint8_t get_high_byte(uint16_t data) {
    return (data >> 8) & 0xFF;
}

/**
 * @brief Gets the least significant byte from a 16-bit value
 *
 * @param data : The 16-bit value to get the low byte from
 * @return uint8_t
 */
static uint8_t get_low_byte(uint16_t data) {
    return data & 0xFF;
}

/**
 * @brief Set the LTC2943 ADC mode
 *
 * @param adc_mode : New ADC to be set
 * @return cmd_status_t
 *
 * @note This service checks if the given state is already inhabited -
 *       if so, no write action is needed and the command is considered
 *       successful.
 */
static cmd_status_t set_adc_mode(adc_mode_t adc_mode) {
    uint8_t data;
    if (!LTC2943_Read(LTC2943_B_CONTROL, &data, 1)) {
        return CMD_STATUS_READ_FAILURE;
    }
    if (get_bits_by_mask(data, MASK_ADC_MODE) == adc_mode) {
        return CMD_STATUS_SUCCESS;
    }

    set_bits_by_mask(&data, MASK_ADC_MODE, adc_mode);

    if (!LTC2943_Write(LTC2943_B_CONTROL, &data, 1)) {
        return CMD_STATUS_WRITE_FAILURE;
    }
    return CMD_STATUS_SUCCESS;
}

/* LTC2943 CHIPCONTROL API */

cmd_status_t get_adc_mode(adc_mode_t *resp) {
    uint8_t data;
    if (!LTC2943_Read(LTC2943_B_CONTROL, &data, 1)) {
        return CMD_STATUS_READ_FAILURE;
    }
    *resp = get_bits_by_mask(data, MASK_ADC_MODE);
    return CMD_STATUS_SUCCESS;
}

cmd_status_t set_adc_mode_auto() {
    return set_adc_mode(LTC2943_ADC_MODE_AUTO);
}

cmd_status_t set_adc_mode_scan() {
    return set_adc_mode(LTC2943_ADC_MODE_SCAN);
}

cmd_status_t set_adc_mode_manual() {
    return set_adc_mode(LTC2943_ADC_MODE_MANUAL);
}

cmd_status_t set_adc_mode_sleep() {
    return set_adc_mode(LTC2943_ADC_MODE_SLEEP);
}

cmd_status_t check_temp_alert(temp_status_t *resp) {
    uint8_t data;
    if (!LTC2943_Read(LTC2943_A_STATUS, &data, 1)) {
        return CMD_STATUS_READ_FAILURE;
    }

    *resp = get_bits_by_mask(data, MASK_TEMP_ALRT);
    return CMD_STATUS_SUCCESS;
}

cmd_status_t check_charge_status(chrg_status_t *resp) {
    uint8_t data;
    if (!LTC2943_Read(LTC2943_A_STATUS, &data, 1)) {
        return CMD_STATUS_READ_FAILURE;
    }

    *resp = get_bits_by_mask(data, MASK_CHRG_ALRT);
    return CMD_STATUS_SUCCESS;
}

cmd_status_t set_charge_treshold(uint16_t min, uint16_t max) {
    uint8_t max_msb = get_high_byte(max);
    uint8_t max_lsb = get_low_byte(max);
    uint8_t min_msb = get_high_byte(min);
    uint8_t min_lsb = get_low_byte(min);

    if (!LTC2943_Write(LTC2943_E_CHRG_TRSHLD, &max_msb, 1)) {
        return CMD_STATUS_WRITE_FAILURE;
    }
    if (!LTC2943_Write(LTC2943_F_CHRG_TRSHLD, &max_lsb, 1)) {
        return CMD_STATUS_WRITE_FAILURE;
    }
    if (!LTC2943_Write(LTC2943_G_CHRG_TRSHLD, &min_msb, 1)) {
        return CMD_STATUS_WRITE_FAILURE;
    }
    if (!LTC2943_Write(LTC2943_H_CHRG_TRSHLD, &min_lsb, 1)) {
        return CMD_STATUS_WRITE_FAILURE;
    }
    return CMD_STATUS_SUCCESS;
}
