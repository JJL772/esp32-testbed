/*

ili9341.h

ILI9341 SPI TFT LCD Driver

*/
#include "driver/spi_common.h"
#include "driver/spi_master.h"

#include <stdint.h>
#include <stddef.h>

typedef struct
{
	spi_device_handle_t spi_dev;
} ili9341_lcd_t;

typedef struct
{
	uint32_t spi_host;
	uint16_t miso_pin;
	uint16_t mosi_pin;
	uint16_t clk_pin;
	uint16_t cs_pin;
	uint16_t width;
	uint16_t height;
	uint16_t dma_chan;
} ili9341_conf_t;

typedef enum
{
	PIXEL_FMT_16BIT,
	PIXEL_FMT_18BIT,
} ili9341_pixel_fmt_t;

int ili9341_init(ili9341_lcd_t* lcd, ili9341_conf_t conf);

#define ILI9341_OPCODE_SLEEP 0x10
#define ILI9341_OPCODE_WAKE 0x11
#define ILI9341_OPCODE_PARTIAL_MODE_ON 0x12
#define ILI9341_OPCODE_PARTIAL_MODE_OFF 0x13
#define ILI9341_OPCODE_INVERSION_OFF 0x20
#define ILI9341_OPCODE_INVERSION_ON 0x21
#define ILI9341_OPCODE_DISPLAY_OFF 0x28
#define ILI9341_OPCODE_DISPLAY_ON 0x29

/*
Sends a simple one-byte command to the LCD
*/
void ili9341_send_simple_command(ili9341_lcd_t* lcd, unsigned char cmd);

void ili9341_nop(ili9341_lcd_t* lcd);

void ili9341_soft_reset(ili9341_lcd_t* lcd);

void ili9341_read_disp_id(ili9341_lcd_t* lcd, unsigned char* manu_id, unsigned char* driver_version, unsigned char* drv_id);

#define DISPLAY_STATUS_VOLTAGE_BOOSTER_MASK (1<<31)
#define DISPLAY_STATUS_ROW_ADDR_ORDER_MASK (1<<30)
#define DISPLAY_STATUS_COL_ADDR_ORDER_MASK (1<<29)
#define DISPLAY_STATUS_ROW_COL_XCHG_MASK (1<<28)
#define DISPLAY_STATUS_VERT_REFRESH_MASK (1<<27)
#define DISPLAY_STATUS_RGB_BGR_ORDER_MASK (1<<26)
#define DISPLAY_STATUS_HORIZ_REFRESH_MASK (1<<25)
#define DISPLAY_STATUS_PIXEL_FORMAT_MASK ((1<<22) | (1<<21) | (1<<20))
#define DISPLAY_STATUS_IDLE_MODE_MASK (1<<19)
#define DISPLAY_STATUS_PARTIAL_MODE_MASK (1<<18)
#define DISPLAY_STATUS_SLEEP_IN_OUT_MASK (1<<17)
#define DISPLAY_STATUS_NORMAL_MODE_MASK (1<<16)
#define DISPLAY_STATUS_VERT_SCROLL_STAT_MASK (1<<15)
#define DISPLAY_STATUS_INVERSION_MASK (1<<13)
#define DISPLAY_STATUS_ALL_PIXEL_ON_MASK (1<<12)
#define DISPLAY_STATUS_ALL_PIXEL_OFF_MASK (1<<11)
#define DISPLAY_STATUS_DISP_ON_OFF_MASK (1<<10)
#define DISPLAY_STATUS_TEAR_EFF_LINE_MASK (1<<9)
#define DISPLAY_STATUS_GAMMA_CURVE_SEL_MASK ((0b11) << 6)
#define DISPLAY_STATUS_TEAR_EFF_LINE_MODE (1<<5)

void ili9341_read_disp_status(ili9341_lcd_t* lcd, unsigned int* disp_stat);

void ili9341_read_power_mode(ili9341_lcd_t* lcd, unsigned char* pwr_stat);

void ili9341_read_madctl(ili9341_lcd_t* lcd, unsigned char* madctl);

void ili9341_read_pixel_format(ili9341_lcd_t* lcd, ili9341_pixel_fmt_t* mcu_fmt, ili9341_pixel_fmt_t* disp_fmt);

void ili9341_read_image_format(ili9341_lcd_t* lcd, unsigned char* out);

void ili9341_read_signal_mode(ili9341_lcd_t* lcd, unsigned char* sigmode);

void ili9341_read_diag_result(ili9341_lcd_t* lcd, unsigned char* out);

void ili9341_gamma_set(ili9341_lcd_t* lcd, unsigned char gamma);

/*
=========================================================================

Simple ILI9341 commands

=========================================================================
*/

void ili9341_sleep(ili9341_lcd_t* lcd);

void ili9341_wake(ili9341_lcd_t* lcd);

void ili9341_partial_mode_on(ili9341_lcd_t* lcd);

void ili9341_partial_mode_off(ili9341_lcd_t* lcd);

void ili9341_invert_on(ili9341_lcd_t* lcd);

void ili9341_invert_off(ili9341_lcd_t* lcd);

void ili9341_display_on(ili9341_lcd_t* lcd);

void ili9341_display_off(ili9341_lcd_t* lcd);

