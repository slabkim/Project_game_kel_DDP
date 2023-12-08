internal void render_backrgound() {
	unsigned int* pixel = (u32*)render_state.memory;
	for (int y = 0; y < render_state.height; y++) {
		for (int x = 0; x < render_state.width; x++) {
			*pixel++ = 0xff00ff * x + 0x00ff00 * y;
		}
	}
}

internal void 
clear_screen(u32 color) {
	unsigned int* pixel = (u32*)render_state.memory;
	for (int y = 0; y < render_state.height; y++) {
		for (int x = 0; x < render_state.width; x++) {
			*pixel++ = color;
		}
	}
}


internal void
draw_rect_in_pixels(int x0, int y0, int x1, int y1, u32 color) {

	x0 = clamp(0, x0, render_state.width);
	x1 = clamp(0, x1, render_state.width);
	y0 = clamp(0, y0, render_state.height);
	y1 = clamp(0, y1, render_state.height);


	for (int y = y0; y < y1; y++) {
		unsigned int* pixel = (u32*)render_state.memory + x0 + y*render_state.width;
		for (int x = x0; x < x1; x++) {
			*pixel++ = color;
		}
	}
}

global_variable float render_scale = 0.01f;

internal void
draw_rect(float x, float y, float half_size_x, float half_size_y, u32 color) {

	x *= render_state.height * render_scale;
	y *= render_state.height * render_scale;
	half_size_x *= render_state.height * render_scale;
	half_size_y *= render_state.height * render_scale;

	x += render_state.width / 2.f;
	y += render_state.height / 2.f;

	int x0 = x - half_size_x;
	int x1 = x + half_size_x;
	int y0 = y - half_size_y;
	int y1 = y + half_size_y;

	draw_rect_in_pixels(x0, y0, x1, y1, color);
}

const char* letters[][7] = {
	  " 00",
	"0  0",
	"0  0",
	"0000",
	"0  0",
	"0  0",
	"0  0",

	"000",
	"0  0",
	"0  0",
	"000",
	"0  0",
	"0  0",
	"000",

	" 000",
	"0",
	"0",
	"0",
	"0",
	"0",
	" 000",

	"000",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"000",

	"0000",
	"0",
	"0",
	"000",
	"0",
	"0",
	"0000",

	"0000",
	"0",
	"0",
	"000",
	"0",
	"0",
	"0",

	" 000",
	"0",
	"0",
	"0 00",
	"0  0",
	"0  0",
	" 000",

	"0  0",
	"0  0",
	"0  0",
	"0000",
	"0  0",
	"0  0",
	"0  0",

	"000",
	" 0",
	" 0",
	" 0",
	" 0",
	" 0",
	"000",

	" 000",
	"   0",
	"   0",
	"   0",
	"0  0",
	"0  0",
	" 000",

	"0  0",
	"0  0",
	"0 0",
	"00",
	"0 0",
	"0  0",
	"0  0",

	"0",
	"0",
	"0",
	"0",
	"0",
	"0",
	"0000",

	"00 00",
	"0 0 0",
	"0 0 0",
	"0   0",
	"0   0",
	"0   0",
	"0   0",

	"00  0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	"0  00",

	"0000",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0000",

	" 000",
	"0  0",
	"0  0",
	"000",
	"0",
	"0",
	"0",

	" 000 ",
	"0   0",
	"0   0",
	"0   0",
	"0 0 0",
	"0  0 ",
	" 00 0",

	"000",
	"0  0",
	"0  0",
	"000",
	"0  0",
	"0  0",
	"0  0",

	" 000",
	"0",
	"0 ",
	" 00",
	"   0",
	"   0",
	"000 ",

	"00000",
	"  0",
	"  0",
	"  0",
	"  0",
	"  0",
	"  0",

	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	" 00",

	"0   0",
	"0   0",
	"0   0",
	"0   0",
	"0   0",
	" 0 0",
	"  0",

	"0   0 ",
	"0   0",
	"0   0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	" 0 0 ",

	"0   0",
	"0   0",
	" 0 0",
	"  0",
	" 0 0",
	"0   0",
	"0   0",

	"0   0",
	"0   0",
	" 0 0",
	"  0",
	"  0",
	"  0",
	"  0",

	"0000",
	"   0",
	"  0",
	" 0",
	"0",
	"0",
	"0000",

	"00",
	" 0",
	" 0",
	" 0",
	" 0",
	" 0",
	"000",

	" 000 ",
	"0   0",
	"    0",
	"  0",
	" 0",
	"0",
	"00000",
};

internal void draw_text(const char *text, float x, float y, float size, u32 color) {
	float half_size = size * .5f;
	float original_y = y;

	while (*text) {
		const char** letter;;
		if (*text == 47) letter = letters[27];
		else if (*text == 46) letter = letters[26];
		else letter = letters[*text - 'A'];
		float original_x = x;

		for (int i = 0; i < 7; i++) {
			const char* row = letter[i];
			while (*row) {
				if (*row == '0') {
					draw_rect(x, y, half_size, half_size, color);
				}
				x += size;
				row++;
			}
			y -= size;
			x = original_x;
		}
		text++;
		x += size * 6.f;
		y = original_y;
	}
}

internal void draw_number(int number, float x, float y, float size, u32 color) {
	float half_size = size * .5f;
	switch (number) {
	case 0: {
		draw_rect(x - size, y, half_size, 2.5f * size, color);
		draw_rect(x + size, y, half_size, 2.5f * size, color);
		draw_rect(x, y + size * 2.f, half_size, half_size, color);
		draw_rect(x, y - size * 2.f, half_size, half_size, color);
		x -= size * 4.f;
	}break;
	case 1: {
		draw_rect(x + size, y, half_size, 2.5f * size, color);
		x -= size * 2.f;
	}break;
	case 2: {
		draw_rect(x, y + size * 2.f, 1.5f * size, half_size, color);
		draw_rect(x, y, 1.5f * size, half_size, color);
		draw_rect(x, y - size * 2.f, 1.5f * size, half_size, color);
		draw_rect(x + size, y + size, half_size, half_size, color);
		draw_rect(x - size, y - size, half_size, half_size, color);
		x -= size * 4.f;
	} break;
	case 3: {
		draw_rect(x - half_size, y + size * 2.f, size, half_size, color);
		draw_rect(x - half_size, y, size, half_size, color);
		draw_rect(x - half_size, y - size * 2.f, size, half_size, color);
		draw_rect(x + size, y, half_size, 2.5f * size, color);
		x -= size * 4.f;
	}break;
	case 4: {
		draw_rect(x + size, y, half_size, 2.5f * size, color);
		draw_rect(x - size, y + size, half_size, 1.5f * size, color);
		draw_rect(x, y, half_size, half_size, color);
		x -= size * 4.f;
	}break;
	case 5: {
		draw_rect(x, y + size * 2.f, 1.5f * size, half_size, color);
		draw_rect(x, y, 1.5f * size, half_size, color);
		draw_rect(x, y - size * 2.f, 1.5f * size, half_size, color);
		draw_rect(x - size, y + size, half_size, half_size, color);
		draw_rect(x + size, y - size, half_size, half_size, color);
		x -= size * 4.f;
	}break;
	}
}
