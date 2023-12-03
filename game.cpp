#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

float player_pos = 0.f;

internal void 
simulate_game(Input* input) {
	clear_screen(0x000000);
	if (pressed(BUTTON_UP))player_pos += 1.f;

	draw_rect(0, player_pos, 1, 1, 0xff0000);
	draw_rect(30, 30, 5, 5, 0xffffff);
	draw_rect(-20, 20, 8, 3, 0xffffff);
}