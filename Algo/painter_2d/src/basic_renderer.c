
///////////////////////////////////////////////////////////////////////////////

#include "renderers.h"

#include <stdlib.h>
#include "ppm.h"

///////////////////////////////////////////////////////////////////////////////

void basic_rederer() {
	uint8_t* vga = malloc(WIDTH*HEIGHT*3);

	for(int y = 0; y < HEIGHT; y++){
		for(int x = 0; x < WIDTH; x++){
			int idx = (y*WIDTH+x)*3;
			vga[idx + 0] = 255;
			vga[idx + 1] = 0;
			vga[idx + 2] = 255;
		}
	}

	save_ppm("basic.ppm", vga, WIDTH, HEIGHT);

	free(vga);
}

///////////////////////////////////////////////////////////////////////////////

