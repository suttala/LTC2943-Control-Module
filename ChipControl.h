#ifndef CHIPCONTROL_H_
#define CHIPCONTROL_H_

#include <stdint.h>
#include <stdbool.h>

/* Defining register addresses */
#define LTC2943_A_STATUS      0b00000000
#define LTC2943_B_CONTROL     0b00000001
#define LTC2943_B_CONTROL     0b00000001
#define LTC2948_E_CHRG_TRSHLD 0b00000100
#define LTC2948_F_CHRG_TRSHLD 0b00000101
#define LTC2948_G_CHRG_TRSHLD 0b00000110
#define LTC2948_H_CHRG_TRSHLD 0b00000111

/* Defining operation masks */
#define MASK_ADC_MODE         0b11000000
#define MASK_TEMP_ALRT        0b00010000
#define MASK_CHRG_ALRT        0b00001100

/* ADC modes */
#define ADC_MODE_AUTOMATIC    0b11000000
#define ADC_MODE_SCAN         0b10000000
#define ADC_MODE_MANUAL       0b01000000
#define ADC_MODE_SLEEP        0b00000000

/* Command status codes */
typedef enum {
    CMD_STATUS_FAILURE = 0, // Sending command was unsuccessful
    CMD_STATUS_SUCCESS = 1, // Sending command was successful
} cmd_status_t;

/* Charge status codes */
typedef enum {
    LTC2948_CHRG_STATUS_OK    = 0, // Charge is between tresholds
    LTC2948_CHRG_STATUS_HIGH  = 1, // Charge is above the high treshold
    LTC2948_CHRG_STATUS_LOW   = 2, // Charge is below the low treshold
    LTC2948_CHRG_STATUS_ERROR = 3, // Both HIGH and LOW statuses reported
} chrg_status_t;

/* Temperature status codes */
typedef enum {
    LTC2948_TEMP_STATUS_OK    = 0, // Sending command was unsuccessful
    LTC2948_TEMP_STATUS_ALERT = 1, // Sending command was successful
} temp_status_t;


/* LTC2948 CHIPCONTROL API */


/**
 * @brief Get the current LTC2948 ADC mode
 *
 * @param resp : uint8_t where the two MSB represent the ADC mode
 * @return cmd_status_t
 */
cmd_status_t get_adc_mode(uint8_t *resp);

/**
 * @brief Set the LTC2948 ADC mode
 *
 * @param adc_mode : New ADC to be set
 * @return cmd_status_t
 */
cmd_status_t set_adc_mode(uint8_t adc_mode);

/**
 * @brief Checks the LTC2948 temperature alert status
 *
 * @param resp : temp_status_t value where 0 is OK and 1 an active alert
 * @return cmd_status_t
 */
cmd_status_t check_temp_alert(temp_status_t *resp);

/**
 * @brief Set LTC2948 charge tresholds
 *
 * @param min : Minimum charge treshold to be set
 * @param max : Maximum charge treshold to be set
 * @return cmd_status_t
 */
cmd_status_t set_charge_treshold(uint8_t min, uint8_t max);

/**
 * @brief Check if the LTC2948 charge is within its tresholds
 *
 * @param resp : chrg_status_t value
 * @return cmd_status_t
 */
cmd_status_t check_charge_status(chrg_status_t *resp);


#endif  // CHIPCONTROL_H_
