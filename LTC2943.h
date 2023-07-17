/**
 * @file LTC2943.h
 *
 * @brief Driver API for LTC2943 Chip
 */
#ifndef LTC2943_H_
#define LTC2943_H_

#include <stdint.h>

/**
 * @brief Initialise the Driver
 *
 * @return Status of the Driver initialisation : bool
 */
bool LTC2943_Initialise();

/**
 * @brief Read data from the chip @address to dest
 *
 * @param address : Chip address to read from
 * @param dest : Read destination
 * @param dataSize : Size of read
 *
 * @return Status of read action : bool
 */
bool LTC2943_Read(uint8_t address, uint8_t *dest, uint8_t dataSize);


/**
 * @brief Write data from src to the chip @address
 *
 * @param address : Chip address to write to
 * @param dest : Write source
 * @param dataSize : Size of write
 *
 * @return Status of write action : bool
 */
bool LTC2973_Write(uint8_t address, uint8_t *src, uint8_t dataSize);

#endif  // LTC2943_H_