/*

fb.h

Cool framebuffers

*/
#pragma once

#include <memory>

typedef enum
{
	FB_DEPTH_8BIT = 1,
	FB_DEPTH_16BIT,
	FB_DEPTH_24BIT,
	FB_DEPTH_32BIT,
} efb_depth_t;

typedef struct
{
	/* pointer to the actual memory slab */
	void* base_ptr;
	/* Total length of the framebuffer */
	size_t size;
	/* depth of the data */
	efb_depth_t depth;
	/* x and y of fb */
	uint32_t width, height;
} fb_t;

/*
-----------------------------------
Static framebuffer support
	Static framebuffers are just statically allocated framebuffers,
	so you don't need to call evil malloc/free during runtime
	can save some cycles as well.
-----------------------------------
*/
#define DECLARE_STATIC_FRAMEBUFFER(name) extern fb_t name

#define DEFINE_STATIC_FRAMEBUFFER(name, width, height, depth) \
			char __ ## name ## _internal_mem[width * height * depth]; \
			fb_t name = { .base_ptr = __ ## name ## _internal_mem, .size = height * width * depth, .depth = depth, .width = width, .height = height }

/*
-----------------------------------
Dynamic framebuffer support
	Dynamically allocated framebuffers
-----------------------------------
*/
fb_t* fb_alloc(uint32_t width, uint32_t height, efb_depth_t depth);

void fb_free(fb_t* fb);