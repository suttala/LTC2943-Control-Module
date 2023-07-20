#include "ChipControl.h"
#include "LTC2943.h"

/* Static helper functions */
static uint8_t get_bits_by_mask(uint8_t data, uint8_t mask) {
    return data & mask;
}

static void set_bits_by_mask(uint8_t *data, uint8_t mask, uint8_t value) {
    *data = (*data & ~mask) | (value & mask);
}

static uint8_t get_high_byte(uint16_t data) {
    return (data >> 8) & 0xFF;
}

static uint8_t get_low_byte(uint16_t data) {
    return data & 0xFF;
}


/* LTC2948 CHIPCONTROL API */


cmd_status_t get_adc_mode(adc_mode_t *resp) {
    uint8_t data;
    if (!LTC2943_Read(LTC2943_B_CONTROL, &data, 1)) {
        return CMD_STATUS_FAILURE;
    }
    *resp = get_bits_by_mask(data, MASK_ADC_MODE);
    return CMD_STATUS_SUCCESS;
}

cmd_status_t set_adc_mode(adc_mode_t adc_mode) {
    uint8_t data;
    if (!LTC2943_Read(LTC2943_B_CONTROL, &data, 1)) {
        return CMD_STATUS_FAILURE;
    }
    if (get_bits_by_mask(data, MASK_ADC_MODE) == adc_mode) {
        return CMD_STATUS_SUCCESS;
    }

    set_bits_by_mask(&data, MASK_ADC_MODE, adc_mode);
    return (cmd_status_t)LTC2943_Write(LTC2943_B_CONTROL, &data, 1);
}

cmd_status_t check_temp_alert(temp_status_t *resp) {
    uint8_t data;
    if (!LTC2943_Read(LTC2943_A_STATUS, &data, 1)) {
        return CMD_STATUS_FAILURE;
    }

    *resp = get_bits_by_mask(data, MASK_TEMP_ALRT);
    return CMD_STATUS_SUCCESS;
}

cmd_status_t check_charge_status(chrg_status_t *resp) {
    uint8_t data;
    if (!LTC2943_Read(LTC2943_A_STATUS, &data, 1)) {
        return CMD_STATUS_FAILURE;
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
        return CMD_STATUS_FAILURE;
    }
    if (!LTC2943_Write(LTC2943_F_CHRG_TRSHLD, &max_lsb, 1)) {
        return CMD_STATUS_FAILURE;
    }
    if (!LTC2943_Write(LTC2943_G_CHRG_TRSHLD, &min_msb, 1)) {
        return CMD_STATUS_FAILURE;
    }
    if (!LTC2943_Write(LTC2943_H_CHRG_TRSHLD, &min_lsb, 1)) {
        return CMD_STATUS_FAILURE;
    }
    return CMD_STATUS_SUCCESS;
}
