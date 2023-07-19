#ifndef CHIPCONTROL_H_
#define CHIPCONTROL_H_

#include "LTC2943.h"

/* Defining register addresses */
#define LTC2943_A_STATUS      0b00000000
#define LTC2943_B_CONTROL     0b00000001
#define LTC2943_B_CONTROL     0b00000001
#define LTC2948_E_CHRG_TRSHLD 0b00000100
#define LTC2948_F_CHRG_TRSHLD 0b00000101
#define LTC2948_G_CHRG_TRSHLD 0b00000110
#define LTC2948_H_CHRG_TRSHLD 0b00000111

/* Defining operation masks */
#define ADC_MODE_MASK         0b11000000
#define TEMP_ALRT_MASK        0b00010000
#define CHRG_ALRT_HI_MASK     0b00001000
#define CHRG_ALRT_LO_MASK     0b00000100

/* ADC modes */
#define ADC_MODE_AUTOMATIC    0b11000000
#define ADC_MODE_SCAN         0b10000000
#define ADC_MODE_MANUAL       0b01000000
#define ADC_MODE_SLEEP        0b00000000

/* Command status codes */
typedef enum {
    CMD_STATUS_SUCCESS = 0,
    CMD_STATUS_FAILURE = 1,
} cmd_status_t;


cmd_status_t get_adc_mode(uint8_t *resp);

cmd_status_t set_adc_mode(uint8_t *adc_mode);

cmd_status_t check_temp_alert(uint8_t *resp);

cmd_status_t set_charge_treshold(uint8_t min, uint8_t max);

cmd_status_t check_charge_status(uint8_t *resp);


#endif  // CHIPCONTROL_H_