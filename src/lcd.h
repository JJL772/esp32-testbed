/*

lcd.h

Common interface for LCD drivers

*/
#pragma once

#include "fb.h"

typedef struct
{
	fb_t* curr_fb;
} lcd_state_t;

/*
---------------------------------------------
Notes on the LCD API
	There can be only one bound FB to an LCD. That will be the framebuffer to draw.

	Higher level operations (e.g. DrawRect or DrawLine) are not implemented by LCD drivers
	Those should be implemented on a higher level in the driver stack & they should operate
	on framebuffer objects, which will eventually be given to the LCD driver for drawing.
---------------------------------------------
*/

typedef struct
{
	/* Device name */
	const char* name;
	/* Init device */
	int(*pfnInit)();
	/* Shutdown device */
	void(*pfnShutdown)();
	/* Sets the internal LCD state */
	void(*pfnSetLCDState)(lcd_state_t*);
	/* Binds the specified framebuffer to the device */
	void(*pfnBindFB)(fb_t*);
	/* Unbind a bound framebuffer, first parameter is used to receive the pointer to the former fb */
	void(*pfnUnbindFB)(fb_t**);
	/* Draws the current framebuffer to the device. This should be non-blocking, we dont want to wait for a bulk data transfer to finish */
	void(*pfnDraw)();
	/* Powers off the LCD */
	void(*pfnPowerOff)();
	/* Powers on the LCD */
	void(*pfnPowerOn)();
} lcd_driver_t;

extern lcd_driver_t* lcd_drivers[];