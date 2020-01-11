#include "ili9341.h"
#include "driver/spi_common.h"
#include "driver/spi_master.h"

int ili9341_init(ili9341_lcd_t* lcd, ili9341_conf_t conf)
{
	esp_err_t status;
	
	spi_bus_config_t bus_conf = {
		.miso_io_num = conf.miso_pin,
		.mosi_io_num = conf.mosi_pin,
		.sclk_io_num = conf.clk_pin,
		.quadwp_io_num = -1,
		.quadhd_io_num = -1,
		/* Max transfer size should be the width * height * depth + 4 bytes for control bytes */
		/* For depth, we'll err on the side of caution and use 3 bytes, since the max possible depth is */
		/* 18 bits on the ili9341. Usually we'll be using 16-bit depth */
		.max_transfer_sz = conf.width * conf.height * 3 + 4,
	};

	spi_device_interface_config_t dev_conf = {

	};

	status = spi_bus_initialize(conf.spi_host, &bus_conf, conf.dma_chan);

	status = spi_bus_add_device(conf.spi_host, &dev_conf, &lcd->spi_dev);
}