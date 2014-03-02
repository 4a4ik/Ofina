void keypresses()
{
	//If a mouse button was pressed
    if( event.type == SDL_KEYDOWN )
    {
		switch( event.key.keysym.sym )
		{
			case SDLK_ESCAPE: PAUSE = !PAUSE; break;    
		}
    }
}

void create_new_game(  vector<Tile> &tiles, std::vector<class Monster> &monsters )
{
	if ( NEW_GAME )
	{
		if ( EDIT_LEVEL )
		{
			//Save the tile map
			save_tiles( tiles );
			SDL_WM_SetCaption( "OFINA", NULL );
		}
		if ( LEVEL_SAVED == true )
		{
			GAME_STARTED = true;
			NEW_GAME = true;
			NEW_MAN = true;
			
			camera.x = 0;
			set_tiles( tiles );
			set_monsters( monsters );
			EDIT_LEVEL = false;
			PAUSE = false;
			NEW_GAME = false;
		}
	}
	//If pressed level editor create tiles
	else if ( EDIT_PUT_TILES )
	{
		set_tiles( tiles );
		EDIT_PUT_TILES = false;
	}
}