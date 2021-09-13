#pragma once

#include <cmath>
#include <algorithm>
#include <allegro.h>

#define SCR_WIDTH  320
#define SCR_HEIGHT 240

typedef uint8_t Uint8;

struct VIDEO_Color {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

struct VIDEO_Surface {
	unsigned int w, h;
	BITMAP* bmp;
};

VIDEO_Surface frame_buffer;

int depth_select(int depth) {
	set_color_depth(depth);
	return set_gfx_mode(GFX_AUTODETECT, SCR_WIDTH, SCR_HEIGHT, 0, 0) == 0;
}

inline VIDEO_Surface* VIDEO_InitVideo() {
	if (allegro_init() != 0) return NULL;
	
	if (!(depth_select(24) || depth_select(16) || depth_select(15))) return NULL;
	
	BITMAP* bmp = create_bitmap(SCR_WIDTH, SCR_HEIGHT);
	clear(bmp);
	
	frame_buffer = VIDEO_Surface{
		SCR_WIDTH, SCR_HEIGHT, bmp
	};
	
	return &frame_buffer;
}

// blits a single colored pixel onto the given surface at the given point
inline void VIDEO_Blit(VIDEO_Surface* surface, int x, int y, const VIDEO_Color& color) {
	putpixel(surface->bmp, x, y, makecol(color.r, color.g, color.b));
}

// reads the color of a single pixel in the given surface
inline VIDEO_Color VIDEO_ReadPixel(VIDEO_Surface* surface, int x, int y) {
	return VIDEO_Color{0,0,0,0};
}

// samples a pixel in the given surface using normalized coordinates
inline VIDEO_Color VIDEO_Sample(VIDEO_Surface* surface, float u, float v)
{
	auto x = (int)(0.0f + u * (float(surface->w) - 0.0f));
	auto y = (int)(float(surface->h) + v * (0.0f - float(surface->h)));
	
	
	if (x >= 0 && x <= surface->w && y >= 0 && y <= surface->h) { 
		int color = getpixel(surface->bmp, std::min(x, (int)surface->w - 1), std::min(y, (int)surface->h - 1));
		return VIDEO_Color{getr(color), getg(color), getb(color), 255};
	}
	
	return VIDEO_Color{ 0, 0, 0, 255 };
}

VIDEO_Surface* VIDEO_ImgLoad(char* filename) {
	BITMAP* bmp = load_bitmap(filename, 0);
	VIDEO_Surface* surface = new VIDEO_Surface{
		bmp->w, bmp->h, bmp
	};
	return surface;
}

inline void VIDEO_UpdateAndPresent() {
	blit(frame_buffer.bmp, screen, 0, 0, 0, 0, SCR_WIDTH, SCR_HEIGHT);
	clear(frame_buffer.bmp);
}

inline void VIDEO_quit() {
	return;
}