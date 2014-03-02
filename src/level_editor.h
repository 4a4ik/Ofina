//What block you wamt to place
int currentType = 1;

void show_type( int tileType )
{
    switch( tileType )
    {        
		case TILE_COINS:
        SDL_WM_SetCaption( "Level Designer. Current Tile: Coin", NULL );
        break;

        case TILE_WALL:
        SDL_WM_SetCaption( "Level Designer. Current Tile: Wall", NULL );
        break;
        
        case TILE_GRASS_LEFT:
        SDL_WM_SetCaption( "Level Designer. Current Tile: Grass Left Side", NULL );
        break;
        
        case TILE_GRASS_CENTER:
        SDL_WM_SetCaption( "Level Designer. Current Tile: Grass Center Part", NULL );
        break;
        
        case TILE_GRASS_RIGHT:
        SDL_WM_SetCaption( "Level Designer. Current Tile: Grass Right Part", NULL );
        break;

		case TILE_FLOOR:
        SDL_WM_SetCaption( "Level Designer. Current Tile: Floor", NULL );
        break;

		case TILE_MAN:
        SDL_WM_SetCaption( "Level Designer. Current Tile: Man Starting Position", NULL );
        break;

		case TILE_SNAIL:
        SDL_WM_SetCaption( "Level Designer. Current Tile: SNAIL Starting Position", NULL );
        break;
    };    
}

void put_tile(  vector<Tile> &tiles, int tileType )
{
	if ( EDIT_LEVEL == true && ( MAN_START_POINT == false || tileType != TILE_MAN ) )
	{
		//Mouse offsets
		int x = 0, y = 0;
	    
		//Get mouse offsets
		SDL_GetMouseState( &x, &y );
	    
		//Adjust to camera
		x += camera.x;
		y += camera.y;
	    
		//Go through tiles
		for( int t = 0; t < (int)tiles.size(); t++ )
		{
			//Get tile's collision box
			SDL_Rect box = tiles[ t ].get_box();
	        
			//If the mouse is inside the tile
			if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) && ( x - camera.x < SCREEN_WIDTH - 60 ) )
			{
				//check if we delete man start point
				if ( tiles[ t ].get_type() == TILE_MAN )
				{ MAN_START_POINT = false; }
	            
				//Replace it with new one
				tiles[ t ].type = tileType;

				//chek if editor created man start point
				if ( tileType == TILE_MAN )
				{ MAN_START_POINT = true; }
			}
		}
	}
}
      
void save_tiles( vector<Tile> &tiles )
{
	if ( EDIT_LEVEL == true )
	{
		//move camera to beginning of level
		camera.x = 0;

		//Open the map
		std::ofstream map( "4a4ik.map" );

		//Write LEVEL width and height to file
		map << LEVEL_WIDTH << " ";
		map << LEVEL_HEIGHT << " ";
	    
		//Go through the tiles
		for( int t = 0; t < (int)tiles.size(); t++ )
		{
			//Write tile type to file
			map << tiles[ t ].get_type() << " ";
		}
	    
		//Close the file
		map.close();

		LEVEL_SAVED = true;
	}
}

class Level_editor
{
	public : 

		SDL_Rect level_editor_box[ 9 ];
		SDL_Rect level_editor_menu;
		
		Level_editor();

		void set_camera();
		void handle_input( vector<Tile> &tiles );
		void show();
};

Level_editor::Level_editor()
{
	for ( int n = 0; n < 8; n++ )
	{
		level_editor_box[ n ].x = SCREEN_WIDTH - 48;
		level_editor_box[ n ].y = 15 + 32 * n; 
		level_editor_box[ n ].h = TILE_HEIGHT;
		level_editor_box[ n ].w = TILE_WIDTH;
	}
	
	level_editor_menu.x = SCREEN_WIDTH - 60;
	level_editor_menu.y = 0;
	level_editor_menu.h = SCREEN_HEIGHT;
	level_editor_menu.w = 60;
}

void Level_editor::handle_input( vector<Tile> &tiles )
{
	//Mouse offsets
	int x = 0, y = 0;
    
	//Get mouse offsets
	SDL_GetMouseState( &x, &y );

    //When the user clicks
	if( event.type == SDL_MOUSEBUTTONDOWN && EDIT_LEVEL == true )
    {
        //On left mouse click
        if( event.button.button == SDL_BUTTON_LEFT )
        {
            //Put the tile
            put_tile( tiles, currentType );

			//If schoose what tile put
			for ( int n = 0; n < 8; n++ )
			{
				if( ( x > level_editor_box[ n ].x ) && ( x < level_editor_box[ n ].x + level_editor_box[ n ].w ) && ( y > level_editor_box[ n ].y ) && ( y < level_editor_box[ n ].y + level_editor_box[ n ].h ) )
				{
					currentType = n + 1;
				}
			}
        }
		//On right mouse click
        if( event.button.button == SDL_BUTTON_RIGHT )
        {
            //Put the tile
            put_tile( tiles, TILE_EMPTY );
        }
        //On mouse wheel scroll
        else if( event.button.button == SDL_BUTTON_WHEELUP )
        {
            //Scroll through tiles
            currentType--;
            
            if( currentType < TILE_COINS )
            {
                currentType = TILE_SNAIL;
            }
            
            //Show the current tile type
            show_type( currentType );
        }
        else if( event.button.button == SDL_BUTTON_WHEELDOWN )
        {
            //Scroll through tiles
            currentType++;
            
            if( currentType > TILE_SNAIL )
            {
				currentType = TILE_COINS;
            }
            
            //Show the current tile type
            show_type( currentType );
        }
	}

}

void Level_editor::set_camera()
{
	if ( PAUSE == false && EDIT_LEVEL == true )
	{
		//Mouse offsets
		int x = 0, y = 0;
	    
		//Get mouse offsets
		SDL_GetMouseState( &x, &y );
	    
		//Move camera to the left if needed
		if( x <= TILE_WIDTH )
		{
			camera.x -= 20;
		}
	    
		//Move camera to the right if needed
		if( x >= SCREEN_WIDTH - TILE_WIDTH )
		{
			camera.x += 20;
		}
	    
		//I don't use up and down
		//Move camera up if needed
		if( y <= TILE_WIDTH )
		{
			camera.y -= 20;
		}
	    
		//I don't use up and down
		//Move camera down if needed
		if( y >= SCREEN_HEIGHT - TILE_WIDTH )
		{
			camera.y += 20;
		}

		//Keep the camera in bounds.
		if( camera.x < 0 )
		{
			camera.x = 0;    
		}
		if( camera.y < 0 )
		{
			camera.y = 0;    
		}
		if( camera.x > LEVEL_WIDTH + 60 - camera.w )
		{
			camera.x = LEVEL_WIDTH + 60 - camera.w;    
		}
		if( camera.y > LEVEL_HEIGHT - camera.h )
		{
			camera.y = LEVEL_HEIGHT - camera.h;    
		} 
	}
}

void Level_editor::show()
{
	if ( EDIT_LEVEL )
	{
		SDL_FillRect ( screen, &level_editor_menu, SDL_MapRGB( screen->format, 123, 122, 122 ) );

		for ( int n = 0; n < 8; n++ )
		{
			apply_surface( level_editor_box[ n ].x, level_editor_box[ n ].y, tileSheet, screen, &clips[ n + 1 ] );
		}
	}
}

