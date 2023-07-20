/**
 * @file ChipControl.h
 * @author Alarik Sutter (alarik.sutter@aalto.fi)
 * @brief Header for the LTC2943 ChipControl C-module
 *
 * @date 2023-07-20
 */
#ifndef CHIPCONTROL_H_
#define CHIPCONTROL_H_

#include <stdint.h>
#include <stdbool.h>

/* Defining register addresses */
#define LTC2943_A_STATUS      0x00
#define LTC2943_B_CONTROL     0x01
#define LTC2943_E_CHRG_TRSHLD 0x04
#define LTC2943_F_CHRG_TRSHLD 0x05
#define LTC2943_G_CHRG_TRSHLD 0x06
#define LTC2943_H_CHRG_TRSHLD 0x07

/* Defining operation masks */
#define MASK_ADC_MODE         0xC0
#define MASK_TEMP_ALRT        0x10
#define MASK_CHRG_ALRT        0x0C

/* Command status codes */
typedef enum {
    CMD_STATUS_SUCCESS       = 0, // Executing command was successful
    CMD_STATUS_READ_FAILURE  = 1, // Error in reading value from the LTC2943
    CMD_STATUS_WRITE_FAILURE = 2, // Error in writing value to the LTC2943
} cmd_status_t;

/* ADC modes */
typedef enum {
    LTC2943_ADC_MODE_AUTO   = 0xC0,
    LTC2943_ADC_MODE_SCAN   = 0x80,
    LTC2943_ADC_MODE_MANUAL = 0x40,
    LTC2943_ADC_MODE_SLEEP  = 0x00,
} adc_mode_t;

/* Charge status codes */
typedef enum {
    LTC2943_CHRG_STATUS_OK    = 0x00, // Charge is between tresholds
    LTC2943_CHRG_STATUS_HIGH  = 0x08, // Charge is above the high treshold
    LTC2943_CHRG_STATUS_LOW   = 0x04, // Charge is below the low treshold
    LTC2943_CHRG_STATUS_ERROR = 0x0C, // Both HIGH and LOW statuses reported
} chrg_status_t;

/* Temperature status codes */
typedef enum {
    LTC2943_TEMP_STATUS_OK    = 0x00, // No temperature alert
    LTC2943_TEMP_STATUS_ALERT = 0x10, // Temperature alert found
} temp_status_t;


/* LTC2943 CHIPCONTROL API */

/*
   All Read and Write operations in the below services are expected
   to return true if the operation was successful and false if not.
   In case of a failure, a suitable CMD_STATUS error code is returned.

   If no failure is detected, the ChipControl-module assumes that the
   command operation went through successfully.
*/

/**
 * @brief Get the current LTC2943 ADC mode
 *
 * @param resp : uint8_t where the two MSB represent the ADC mode
 * @return cmd_status_t
 */
cmd_status_t get_adc_mode(adc_mode_t *resp);

/**
 * @brief Set the ADC mode to AUTO
 *
 * @return cmd_status_t
 *
 * @note See static function 'set_adc_mode' in ChipControl.c for
 *       more information on how IO is handled with LTC2943
 */
cmd_status_t set_adc_mode_auto();

/**
 * @brief Set the ADC mode to SCAN
 *
 * @return cmd_status_t
 *
 * @note See static function 'set_adc_mode' in ChipControl.c for
 *       more information on how IO is handled with LTC2943
 */
cmd_status_t set_adc_mode_scan();

/**
 * @brief Set the ADC mode to MANUAL
 *
 * @return cmd_status_t
 *
 * @note See static function 'set_adc_mode' in ChipControl.c for
 *       more information on how IO is handled with LTC2943
 */
cmd_status_t set_adc_mode_manual();

/**
 * @brief Set the ADC mode to SLEEP
 *
 * @return cmd_status_t
 *
 * @note See static function 'set_adc_mode' in ChipControl.c for
 *       more information on how IO is handled with LTC2943
 */
cmd_status_t set_adc_mode_sleep();


/**
 * @brief Checks the LTC2943 temperature alert status
 *
 * @param resp : temp_status_t value where 0 is OK and 1 an active alert
 * @return cmd_status_t
 */
cmd_status_t check_temp_alert(temp_status_t *resp);

/**
 * @brief Set LTC2943 charge tresholds
 *
 * @param min : Minimum charge treshold to be set
 * @param max : Maximum charge treshold to be set
 * @return cmd_status_t
 */
cmd_status_t set_charge_treshold(uint16_t min, uint16_t max);

/**
 * @brief Check if the LTC2943 charge is within its tresholds
 *
 * @param resp : chrg_status_t value
 * @return cmd_status_t
 */
cmd_status_t check_charge_status(chrg_status_t *resp);


#endif  // CHIPCONTROL_H_
