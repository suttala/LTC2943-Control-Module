#ifndef CHIPCONTROL_H_
#define CHIPCONTROL_H_

#include "LTC2943.h"

typedef enum {
    CMD_STATUS_SUCCESS = 0,
    CMD_STATUS_FAILURE = 1,
} cmd_status_t;

typedef enum {
    ADC_MODE_AUTO = 0,
    ADC_MODE_SCAN = 1,
    ADC_MODE_MANUAL = 2,
    ADC_MODE_SLEEP = 3,
} adc_mode_t;

cmd_status_t get_adc_mode();

cmd_status_t set_adc_mode(adc_mode_t *mode);

cmd_status_t check_temp_alert();

cmd_status_t set_charge_treshold(uint8_t *min, uint8_t *max);

cmd_status_t check_charge();


#endif  // CHIPCONTROL_H_