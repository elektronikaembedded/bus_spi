/*******************************************************************************
 * @file        bus_spi.h
 * @author      Sarath S
 * @date        2026-01-02
 * @version     1.0
 * @brief       SPI bus abstraction interface
 *
 * @details
 * This module provides a simple and portable abstraction for SPI
 * communication.
 *
 * It separates device drivers from platform-specific SPI implementations.
 * Drivers (ST7735, W25Qxx, PN532, etc.) interact with SPI through this
 * interface without depending on any MCU or SDK.
 *
 * Each platform must provide its own implementation of the SPI operations.
 *
 * @note
 * - This module handles only SPI data transfer.
 * - Chip Select (CS) handling is responsibility of the driver.
 *
 * @contact     elektronikaembedded@gmail.com
 * @website     https://elektronikaembedded.wordpress.com
 ******************************************************************************/

#ifndef BUS_SPI_H
#define BUS_SPI_H

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Includes
 *******************************************************************************/
#include <stdint.h>
#include <stdbool.h>

/*******************************************************************************
 * Types
 *******************************************************************************/

/**
 * @brief SPI error codes
 */
typedef enum
{
    BUS_SPI_OK = 0,
    BUS_SPI_ERR_NULL = -1,
    BUS_SPI_ERR_IO = -2,
    BUS_SPI_ERR_BUSY = -3,
    BUS_SPI_ERR_NOT_SUPPORTED = -4
} bus_spi_err_t;

typedef struct bus_spi bus_spi_t;

/**
 * @brief SPI operations table
 *
 * Platform-specific implementation must fill this structure.
 */
typedef struct
{
    bus_spi_err_t (*init)(bus_spi_t *bus);
    bus_spi_err_t (*deinit)(bus_spi_t *bus);

    bus_spi_err_t (*transfer)(bus_spi_t *bus,
                              const uint8_t *tx,
                              uint8_t *rx,
                              uint16_t len);

    bus_spi_err_t (*write)(bus_spi_t *bus,
                           const uint8_t *tx,
                           uint16_t len);

    bus_spi_err_t (*read)(bus_spi_t *bus,
                          uint8_t *rx,
                          uint16_t len);

    bool (*is_busy)(bus_spi_t *bus);

} bus_spi_ops_t;

/*******************************************************************************
 * Bus Object
 *******************************************************************************/

/**
 * @brief SPI bus instance
 *
 * Holds the operations table and platform-specific context.
 */
struct bus_spi
{
    const bus_spi_ops_t *ops; /**< SPI operations */
    void *ctx;                /**< Platform-specific handle (SPI, DMA, etc.) */
};

/*******************************************************************************
 * API
 *******************************************************************************/

/**
 * @brief Initialize SPI bus
 *
 * @param bus Pointer to bus object
 * @param ops Pointer to operations table
 *
 * @return BUS_SPI_OK on success
 */
bus_spi_err_t bus_spi_init(bus_spi_t *bus, const bus_spi_ops_t *ops);

/**
 * @brief Deinitialize SPI bus
 *
 * @param bus Pointer to bus object
 *
 * @return BUS_SPI_OK on success
 */
bus_spi_err_t bus_spi_deinit(bus_spi_t *bus);

#ifdef __cplusplus
}
#endif

#endif /* BUS_SPI_H */

/****************************** End of file ***********************************/