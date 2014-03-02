void clip_tiles()
{
    //Clip the sprite sheet
    clips[ TILE_EMPTY].x = 0;
    clips[ TILE_EMPTY ].y = 0;
    clips[ TILE_EMPTY ].w = TILE_WIDTH;
    clips[ TILE_EMPTY ].h = TILE_HEIGHT;

    clips[ TILE_COINS ].x = TILE_WIDTH;
    clips[ TILE_COINS ].y = 0;
    clips[ TILE_COINS ].w = TILE_WIDTH;
    clips[ TILE_COINS ].h = TILE_HEIGHT;

	clips[ TILE_WALL ].x = TILE_WIDTH * 2;
    clips[ TILE_WALL ].y = 0;
    clips[ TILE_WALL ].w = TILE_WIDTH;
    clips[ TILE_WALL ].h = TILE_HEIGHT;

	clips[ TILE_GRASS_LEFT ].x = 0;
    clips[ TILE_GRASS_LEFT ].y = TILE_HEIGHT;
    clips[ TILE_GRASS_LEFT ].w = TILE_WIDTH;
    clips[ TILE_GRASS_LEFT ].h = TILE_HEIGHT;

	clips[ TILE_GRASS_CENTER ].x = TILE_WIDTH;
    clips[ TILE_GRASS_CENTER ].y = TILE_HEIGHT;
    clips[ TILE_GRASS_CENTER ].w = TILE_WIDTH;
    clips[ TILE_GRASS_CENTER ].h = TILE_HEIGHT;

	clips[ TILE_GRASS_RIGHT ].x = TILE_WIDTH * 2;
    clips[ TILE_GRASS_RIGHT ].y = TILE_HEIGHT;
    clips[ TILE_GRASS_RIGHT ].w = TILE_WIDTH;
    clips[ TILE_GRASS_RIGHT ].h = TILE_HEIGHT;

	clips[ TILE_FLOOR ].x = 0;
    clips[ TILE_FLOOR ].y = TILE_HEIGHT * 2;
    clips[ TILE_FLOOR ].w = TILE_WIDTH;
    clips[ TILE_FLOOR ].h = TILE_HEIGHT;

	clips[ TILE_MAN ].x = TILE_WIDTH;
    clips[ TILE_MAN ].y = TILE_HEIGHT * 2;
    clips[ TILE_MAN ].w = TILE_WIDTH;
    clips[ TILE_MAN ].h = TILE_HEIGHT;

	clips[ TILE_SNAIL ].x = TILE_WIDTH * 2;
    clips[ TILE_SNAIL ].y = TILE_HEIGHT * 2;
    clips[ TILE_SNAIL ].w = TILE_WIDTH;
    clips[ TILE_SNAIL ].h = TILE_HEIGHT;

	//Man stuff
	man_clips[ MAN_RIGHT_1 ].x = 0;
	man_clips[ MAN_RIGHT_1 ].y = 0;
	man_clips[ MAN_RIGHT_1 ].w = MAN_WIDTH;
	man_clips[ MAN_RIGHT_1 ].h = MAN_HEIGHT;

	man_clips[ MAN_RIGHT_2 ].x = MAN_WIDTH;
	man_clips[ MAN_RIGHT_2 ].y = 0;
	man_clips[ MAN_RIGHT_2 ].w = MAN_WIDTH;
	man_clips[ MAN_RIGHT_2 ].h = MAN_HEIGHT;

	man_clips[ MAN_LEFT_1 ].x = 0;
	man_clips[ MAN_LEFT_1 ].y = MAN_HEIGHT;
	man_clips[ MAN_LEFT_1 ].w = MAN_WIDTH;
	man_clips[ MAN_LEFT_1 ].h = MAN_HEIGHT;

	man_clips[ MAN_LEFT_2 ].x = MAN_WIDTH;
	man_clips[ MAN_LEFT_2 ].y = MAN_HEIGHT;
	man_clips[ MAN_LEFT_2 ].w = MAN_WIDTH;
	man_clips[ MAN_LEFT_2 ].h = MAN_HEIGHT;

	//MENU
	menu_clips[ MENU_RESUME ].x = 0;
	menu_clips[ MENU_RESUME ].y = 0;
	menu_clips[ MENU_RESUME ].w = MENU_WIDTH;
	menu_clips[ MENU_RESUME ].h = MENU_HEIGHT;

	menu_clips[ MENU_NEW_GAME ].x = 0;
	menu_clips[ MENU_NEW_GAME ].y = MENU_HEIGHT;
	menu_clips[ MENU_NEW_GAME ].w = MENU_WIDTH;
	menu_clips[ MENU_NEW_GAME ].h = MENU_HEIGHT;

	menu_clips[ MENU_LEVEL_EDITOR ].x = 0;
	menu_clips[ MENU_LEVEL_EDITOR ].y = MENU_HEIGHT * 2;
	menu_clips[ MENU_LEVEL_EDITOR ].w = MENU_WIDTH;
	menu_clips[ MENU_LEVEL_EDITOR ].h = MENU_HEIGHT;

	menu_clips[ MENU_OPTIONS ].x = 0;
	menu_clips[ MENU_OPTIONS ].y = MENU_HEIGHT * 3;
	menu_clips[ MENU_OPTIONS ].w = MENU_WIDTH;
	menu_clips[ MENU_OPTIONS ].h = MENU_HEIGHT;

	menu_clips[ MENU_EXIT ].x = 0;
	menu_clips[ MENU_EXIT ].y = MENU_HEIGHT * 4;
	menu_clips[ MENU_EXIT ].w = MENU_WIDTH;
	menu_clips[ MENU_EXIT ].h = MENU_HEIGHT;

	//LIGHTED
	menu_clips[ MENU_RESUME_LIGHTED ].x = MENU_WIDTH;
	menu_clips[ MENU_RESUME_LIGHTED ].y = 0;
	menu_clips[ MENU_RESUME_LIGHTED ].w = MENU_WIDTH;
	menu_clips[ MENU_RESUME_LIGHTED ].h = MENU_HEIGHT;

	menu_clips[ MENU_NEW_GAME_LIGHTED ].x = MENU_WIDTH;
	menu_clips[ MENU_NEW_GAME_LIGHTED ].y = MENU_HEIGHT;
	menu_clips[ MENU_NEW_GAME_LIGHTED ].w = MENU_WIDTH;
	menu_clips[ MENU_NEW_GAME_LIGHTED ].h = MENU_HEIGHT;

	menu_clips[ MENU_LEVEL_EDITOR_LIGHTED ].x = MENU_WIDTH;
	menu_clips[ MENU_LEVEL_EDITOR_LIGHTED ].y = MENU_HEIGHT * 2;
	menu_clips[ MENU_LEVEL_EDITOR_LIGHTED ].w = MENU_WIDTH;
	menu_clips[ MENU_LEVEL_EDITOR_LIGHTED ].h = MENU_HEIGHT;

	menu_clips[ MENU_OPTIONS_LIGHTED ].x = MENU_WIDTH;
	menu_clips[ MENU_OPTIONS_LIGHTED ].y = MENU_HEIGHT * 3;
	menu_clips[ MENU_OPTIONS_LIGHTED ].w = MENU_WIDTH;
	menu_clips[ MENU_OPTIONS_LIGHTED ].h = MENU_HEIGHT;

	menu_clips[ MENU_EXIT_LIGHTED ].x = MENU_WIDTH;
	menu_clips[ MENU_EXIT_LIGHTED ].y = MENU_HEIGHT * 4;
	menu_clips[ MENU_EXIT_LIGHTED ].w = MENU_WIDTH;
	menu_clips[ MENU_EXIT_LIGHTED ].h = MENU_HEIGHT;

	//Monsters stuff
	snail_clips[ SNAIL_RIGHT_1 ].x = 0;
	snail_clips[ SNAIL_RIGHT_1 ].y = 0;
	snail_clips[ SNAIL_RIGHT_1 ].w = SNAIL_WIDTH;
	snail_clips[ SNAIL_RIGHT_1 ].h = SNAIL_HEIGHT;

	snail_clips[ SNAIL_RIGHT_2 ].x = SNAIL_WIDTH;
	snail_clips[ SNAIL_RIGHT_2 ].y = 0;
	snail_clips[ SNAIL_RIGHT_2 ].w = SNAIL_WIDTH;
	snail_clips[ SNAIL_RIGHT_2 ].h = SNAIL_HEIGHT;

	snail_clips[ SNAIL_LEFT_1 ].x = SNAIL_WIDTH * 2;
	snail_clips[ SNAIL_LEFT_1 ].y = 0;
	snail_clips[ SNAIL_LEFT_1 ].w = SNAIL_WIDTH;
	snail_clips[ SNAIL_LEFT_1 ].h = SNAIL_HEIGHT;

	snail_clips[ SNAIL_LEFT_2 ].x = SNAIL_WIDTH * 3;
	snail_clips[ SNAIL_LEFT_2 ].y = 0;
	snail_clips[ SNAIL_LEFT_2 ].w = SNAIL_WIDTH;
	snail_clips[ SNAIL_LEFT_2 ].h = SNAIL_HEIGHT;
}