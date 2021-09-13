#pragma once

#include <allegro.h>

unsigned int INPUT_time_now = 0;

inline void incr_time() {
	INPUT_time_now += 1;
}

inline void INPUT_Init() {
	install_keyboard();
	install_mouse();
	install_timer();
	
	install_int(incr_time, 100);
}
