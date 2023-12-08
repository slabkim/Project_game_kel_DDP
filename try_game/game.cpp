#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

float player_p1, player_dp1;
float player_p2, player_dp2;
float player_p3 = 33, player_dp3;
float player_p4 = 33, player_dp4;
float player_p5 = -33, player_dp5;
float player_p6 = -33, player_dp6;

float arena_half_size_x = 85, arena_half_size_y = 45;
float player_half_size_x = 2, player_half_size_y = 10;   //x=2.5 y=12
float player_half_size_x2 = 1, player_half_size_y2 = 12;
float ball_p_x, ball_p_y, ball_dp_x = 100, ball_dp_y, ball_half_size = 1, ball_half_size2 = 0.5;
int player_score_1 = 0, player_score_2 = 0;

enum Gamemode {
	GM_MENU, GM_GAMEPLAY,
};

Gamemode current_gamemode;
int hot_button;

internal void
simulate_game(Input* input, float dt) {

	//gambar arena
	clear_screen(0xffffff);
	draw_rect(0, 0, arena_half_size_x, arena_half_size_y, 0x000000);

	//movement player
	if (current_gamemode == GM_GAMEPLAY) {
		draw_rect(87, 0, 2, 21, 0x000ff);
		draw_rect(-87, 0, 2, 21, 0xff0000);
		float player_ddp1 = 0.f;
		if (is_down(BUTTON_UP))player_ddp1 += 2000;
		if (is_down(BUTTON_DOWN))player_ddp1 -= 2000;


		float player_ddp2 = 0.f;
		if (is_down(BUTTON_W))player_ddp2 += 2000;
		if (is_down(BUTTON_S))player_ddp2 -= 2000;

		float player_ddp3 = 0.f;
		float player_ddp4 = 0.f;
		float player_ddp5 = 0.f;
		float player_ddp6 = 0.f;

		//batasan player1
		player_ddp1 -= player_dp1 * 10.f;
		player_p1 = player_p1 + player_dp1 * dt + player_ddp1 * dt * dt * .5f;
		player_dp1 = player_dp1 + player_ddp1 * dt;

		if (player_p1 + player_half_size_y > arena_half_size_y) {
			player_p1 = arena_half_size_y - player_half_size_y;
			player_dp1 *= -1;
		}
		else if (player_p1 - player_half_size_y < -arena_half_size_y) {
			player_p1 = -arena_half_size_y + player_half_size_y;
			player_dp1 *= -1;
		}
		//batasan player2
		player_ddp2 -= player_dp2 * 10.f;
		player_p2 = player_p2 + player_dp2 * dt + player_ddp2 * dt * dt * .5f;
		player_dp2 = player_dp2 + player_ddp2 * dt;

		if (player_p2 + player_half_size_y > arena_half_size_y) {
			player_p2 = arena_half_size_y - player_half_size_y;
			player_dp2 *= -1;
		}
		else if (player_p2 - player_half_size_y < -arena_half_size_y) {
			player_p2 = -arena_half_size_y + player_half_size_y;
			player_dp2 *= -1;
		}
		//batasan player3
		player_ddp3 -= player_dp3 * 10.f;
		player_p3 = player_p3 + player_dp3 * dt + player_ddp3 * dt * dt * .5f;
		player_dp3 = player_dp3 + player_ddp3 * dt;

		if (player_p3 + player_half_size_y2 > arena_half_size_y) {
			player_p3 = arena_half_size_y - player_half_size_y2;
			player_dp3 *= -1;
		}
		else if (player_p3 - player_half_size_y2 < -arena_half_size_y) {
			player_p3 = -arena_half_size_y + player_half_size_y2;
			player_dp3 *= -1;
		}
		//batasan player4
		player_ddp4 -= player_dp4 * 10.f;
		player_p4 = player_p4 + player_dp4 * dt + player_ddp4 * dt * dt * .5f;
		player_dp4 = player_dp4 + player_ddp4 * dt;

		if (player_p4 + player_half_size_y2 > arena_half_size_y) {
			player_p4 = arena_half_size_y - player_half_size_y2;
			player_dp4 *= -1;
		}
		else if (player_p4 - player_half_size_y2 < -arena_half_size_y) {
			player_p4 = -arena_half_size_y + player_half_size_y2;
			player_dp4 *= -1;
		}
		//batasan player5
		player_ddp5 -= player_dp5 * 10.f;
		player_p5 = player_p5 + player_dp5 * dt + player_ddp5 * dt * dt * .5f;
		player_dp5 = player_dp5 + player_ddp5 * dt;

		if (player_p5 + player_half_size_y2 > arena_half_size_y) {
			player_p5 = arena_half_size_y - player_half_size_y2;
			player_dp5 *= -1;
		}
		else if (player_p5 - player_half_size_y2 < -arena_half_size_y) {
			player_p5 = -arena_half_size_y + player_half_size_y2;
			player_dp5 *= -1;
		}
		//batasan player6
		player_ddp6 -= player_dp6 * 10.f;
		player_p6 = player_p6 + player_dp6 * dt + player_ddp4 * dt * dt * .5f;
		player_dp6 = player_dp6 + player_ddp6 * dt;

		if (player_p6 + player_half_size_y2 > arena_half_size_y) {
			player_p6 = arena_half_size_y - player_half_size_y2;
			player_dp6 *= -1;
		}
		else if (player_p6 - player_half_size_y2 < -arena_half_size_y) {
			player_p6 = -arena_half_size_y + player_half_size_y2;
			player_dp6 *= -1;
		}



		ball_p_x += ball_dp_x * dt;
		ball_p_y += ball_dp_y * dt;

		//gambar bola
		draw_rect(ball_p_x, ball_p_y, 1, 1, 0xffffff);
		//batasan bola
		if (ball_p_x + ball_half_size > 80 - player_half_size_x &&
			ball_p_x - ball_half_size < 80 + player_half_size_x &&
			ball_p_y + ball_half_size > player_p1 - player_half_size_y &&
			ball_p_y + ball_half_size < player_p1 + player_half_size_y) {
			ball_p_x = 80 - player_half_size_x - ball_half_size;
			ball_dp_x *= -1;

			ball_dp_y = (ball_p_y - player_p1) * 2 + player_dp1 * .75f;

		}
		else if (ball_p_x + ball_half_size > -80 - player_half_size_x &&
			ball_p_x - ball_half_size < -80 + player_half_size_x &&
			ball_p_y + ball_half_size > player_p2 - player_half_size_y &&
			ball_p_y + ball_half_size < player_p2 + player_half_size_y) {
			ball_p_x = -80 + player_half_size_x + ball_half_size;
			ball_dp_x *= -1;

			ball_dp_y = (ball_p_y - player_p2) * 2 + player_dp2 * .75f;

		}
		else if (ball_p_x + ball_half_size2 > 85 - player_half_size_x2 &&
			ball_p_x - ball_half_size2 < 85 + player_half_size_x2 &&
			ball_p_y + ball_half_size2 > player_p3 - player_half_size_y2 &&
			ball_p_y + ball_half_size2 < player_p3 + player_half_size_y2) {
			ball_p_x = 85 - player_half_size_x2 - ball_half_size2;
			ball_dp_x *= -1;

		}
		else if (ball_p_x + ball_half_size2 > -85 - player_half_size_x2 &&
			ball_p_x - ball_half_size2 < -85 + player_half_size_x2 &&
			ball_p_y + ball_half_size2 > player_p4 - player_half_size_y2 &&
			ball_p_y + ball_half_size2 < player_p4 + player_half_size_y2) {
			ball_p_x = -85 + player_half_size_x2 + ball_half_size2;
			ball_dp_x *= -1;

		}
		else if (ball_p_x + ball_half_size2 > 85 - player_half_size_x2 &&
			ball_p_x - ball_half_size2 < 85 + player_half_size_x2 &&
			ball_p_y + ball_half_size2 > player_p5 - player_half_size_y2 &&
			ball_p_y + ball_half_size2 < player_p5 + player_half_size_y2) {
			ball_p_x = 85 - player_half_size_x2 - ball_half_size2;
			ball_dp_x *= -1;

		}
		else if (ball_p_x + ball_half_size2 > -85 - player_half_size_x2 &&
			ball_p_x - ball_half_size2 < -85 + player_half_size_x2 &&
			ball_p_y + ball_half_size2 > player_p6 - player_half_size_y2 &&
			ball_p_y + ball_half_size2 < player_p6 + player_half_size_y2) {
			ball_p_x = -85 + player_half_size_x2 + ball_half_size2;
			ball_dp_x *= -1;

		}


		if (ball_p_y + ball_half_size > arena_half_size_y) {
			ball_p_y = arena_half_size_y - ball_half_size;
			ball_dp_y *= -1;
		}
		else if (ball_p_y - ball_half_size < -arena_half_size_y) {
			ball_p_y = -arena_half_size_y + ball_half_size;
			ball_dp_y *= -1;
		}
		if (ball_p_x + ball_half_size > arena_half_size_x) {
			ball_dp_x *= -1;
			ball_dp_y = 0;
			ball_p_x = 0;
			ball_p_y = 0;
			player_score_1++;
		}
		else if (ball_p_x - ball_half_size < -arena_half_size_x) {
			ball_dp_x *= -1;
			ball_dp_y = 0;
			ball_p_x = 0;
			ball_p_y = 0;
			player_score_2++;
		}

		draw_number(player_score_1, -10, 40, 1.f, 0x00ff00);
		draw_number(player_score_2, 10, 40, 1.f, 0x00ff00);

		//gambar pemain
		draw_rect(80, player_p1, player_half_size_x, player_half_size_y, 0x0000ff);
		draw_rect(-80, player_p2, player_half_size_x, player_half_size_y, 0xff0000);

		draw_rect(85, player_p3, player_half_size_x2, player_half_size_y2, 0x0000ff);
		draw_rect(-85, player_p4, player_half_size_x2, player_half_size_y2, 0xff0000);
		draw_rect(85, player_p5, player_half_size_x2, player_half_size_y2, 0x0000ff);
		draw_rect(-85, player_p6, player_half_size_x2, player_half_size_y2, 0xff0000);
	}else {
		if (pressed(BUTTON_LEFT) || pressed(BUTTON_RIGHT)) {
			hot_button = !hot_button;
		}

		if (pressed(BUTTON_ENTER)) {
			current_gamemode = GM_GAMEPLAY;
		}
		if (hot_button == 0) {
			draw_text("PRESS", -35, 0, 1, 0xffffff);
			draw_text("ENTER", 20, 0, 1, 0xff0000);
		}
		else{
			draw_text("PRESS", -35, 0, 1, 0xff0000);
			draw_text("ENTER", 20, 0, 1, 0xffffff);
		}
		
	}if (player_score_1 == 5) {
		player_score_1 = 0;
		player_score_2 = 0;
		current_gamemode = GM_MENU;

	}else if (player_score_2 == 5) {
		player_score_1 = 0;
		player_score_2 = 0;
		current_gamemode = GM_MENU;
	}
}
