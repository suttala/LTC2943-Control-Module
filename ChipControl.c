#include "ChipControl.h"
#include "LTC2943.h"

/* Static helper functions */
static uint8_t get_bits_by_mask(uint8_t data, uint8_t mask) {
    return data & mask;
}

static void set_bits_by_mask(uint8_t *data, uint8_t mask, uint8_t value) {
    *data = (*data & ~mask) | (value & mask);
}

/* LTC2948 CHIPCONTROL API */


cmd_status_t get_adc_mode(uint8_t *resp) {
    uint8_t data;
    if (!LTC2943_Read(LTC2943_B_CONTROL, &data, 1)) {
        return CMD_STATUS_FAILURE;
    }
    *resp = get_bits_by_mask(data, MASK_ADC_MODE);
    return CMD_STATUS_SUCCESS;
}

cmd_status_t set_adc_mode(uint8_t adc_mode) {
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
    *resp = LTC2948_TEMP_STATUS_OK;
    if (!(get_bits_by_mask(data, MASK_TEMP_ALRT) == 0)) {
        *resp = LTC2948_TEMP_STATUS_ALERT;
    }
    return CMD_STATUS_SUCCESS;
}

cmd_status_t check_charge_status(chrg_status_t *resp) {
    uint8_t data;
    if (!LTC2943_Read(LTC2943_A_STATUS, &data, 1)) {
        return CMD_STATUS_FAILURE;
    }
    *resp = 0;
    if (!(get_bits_by_mask(data, MASK_CHRG_ALRT) == 0)) {
        *resp = 1;
    }
    switch (get_bits_by_mask(data, MASK_CHRG_ALRT)) {
        case 0b00000000:
            *resp = LTC2948_CHRG_STATUS_OK;
            break;
        case 0b00001000:
            *resp = LTC2948_CHRG_STATUS_HIGH;
            break;
        case 0b00000100:
            *resp = LTC2948_CHRG_STATUS_LOW;
            break;
        case 0b00001100:
            *resp = LTC2948_CHRG_STATUS_ERROR;
            break;
    }
    return CMD_STATUS_SUCCESS;
}
