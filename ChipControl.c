#include "ChipControl.h"
#include "LTC2943.h"

/* Static helper functions */
static uint8_t get_bits_by_mask(uint8_t data, uint8_t mask) {
    return data & mask;
}


/* LTC2948 CHIPCONTROL API */


cmd_status_t get_adc_mode(uint8_t *resp) {
    uint8_t data;
    if (!LTC2943_Read(LTC2943_B_CONTROL, &data, 1)) {
        return CMD_STATUS_FAILURE;
    } else {

        *resp = get_bits_by_mask(data, MASK_ADC_MODE);
        return CMD_STATUS_SUCCESS;
    }
}