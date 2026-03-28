/*******************************************************************************
 * @file        bus_spi.c
 * @author      Sarath S
 * @date        2026-01-02
 * @version     1.0
 * @brief       SPI bus abstraction implementation
 *
 * @details
 * This file implements the common SPI bus interface.
 *
 * The actual SPI operations are provided by platform-specific
 * implementations through the operations table.
 *
 * This layer ensures that device drivers remain independent from
 * hardware-specific SPI details.
 ******************************************************************************/

/*******************************************************************************
 * Includes
 *******************************************************************************/
#include "bus_spi.h"
#include "stddef.h"
/*******************************************************************************
 * Functions
 *******************************************************************************/

/**
 * @brief Initialize SPI bus
 */
bus_spi_err_t bus_spi_init(bus_spi_t *bus, bus_spi_config_t *conf, const bus_spi_ops_t *ops)
{
    if ((bus == NULL) || (ops == NULL))
    {
        return BUS_SPI_ERR_NULL;
    }

    bus->ops = ops;
    bus->ctx = NULL;
    bus->conf = conf;

    /* Call platform init if available */
    if (bus->ops->init)
    {
        return bus->ops->init(bus);
    }

    return BUS_SPI_OK;
}

/**
 * @brief Deinitialize SPI bus
 */
bus_spi_err_t bus_spi_deinit(bus_spi_t *bus)
{
    if (bus == NULL)
    {
        return BUS_SPI_ERR_NULL;
    }

    if (bus->ops && bus->ops->deinit)
    {
        return bus->ops->deinit(bus);
    }

    return BUS_SPI_OK;
}

/****************************** End of file ***********************************/
