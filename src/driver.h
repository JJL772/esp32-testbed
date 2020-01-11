/*

driver.h

Common definitions for the driver stack

*/

/*
-------------------------------------------------------------------
DESIGN
-------------------------------------------------------------------
The driver system I am thinking about is going to have multiple 
levels with varying levels of abstraction.
An example of this is with the video driver stack design. 

On the lowest level, we've got LCD drivers, which are just in charge
of talking to LCDs. Each LCD driver implements a few functions that
allow for the binding and drawing of framebuffers. They can also
add device-specific extensions to their driver descriptor. (see the
dext parameter in lcd_driver_t).

The next level up isn't much of a "driver", but rather operations
on framebuffers. This will allow you to create framebuffers, render
to them, bind them to LCDs and draw them. Higher level operations
like DrawRect and DrawLine would be located here. 

The next level is an actual graphics API, like OpenGL ES maybe.
Basically some API that will allow you to do actual graphics 
programming like you'd do in a game engine.

If the ESP32 had an on-board GPU with VGA/HDM1/DP output, we'd 
just write drivers for that, but this isn't the case. GPUs are
somewhat rare in embedded systems anyway- at least as far as I'm
aware.
-------------------------------------------------------------------
*/