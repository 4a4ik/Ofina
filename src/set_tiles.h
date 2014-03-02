void clean_up( vector<Tile> &tiles )
{
    //Free the surface
    SDL_FreeSurface( tileSheet );
	SDL_FreeSurface( manSheet );
	SDL_FreeSurface( menuSheet );
	SDL_FreeSurface( monsterSheet );

	tiles.clear();

    //Quit SDL
    SDL_Quit();
}

//IF man touches wall when falling... for monster i did different in monster.h
bool touches_wall( SDL_Rect box, vector<Tile> &tiles )
{
    //Go through the tiles
	for( int t = 0; t < (int)tiles.size(); t++ )
    {
        //If the tile is a wall type tile
		if( ( tiles[ t ].get_type() >= TILE_WALL ) && ( tiles[ t ].get_type() <= TILE_FLOOR ) )
        {
            //If the collision box touches the wall tile
            if( check_collision( box, tiles[ t ].get_box() ) == true )
            {
				crate_col = t;
                return true;
            }
        }
    }
    //If no wall tiles were touched
    return false;
}

void touches_coins( SDL_Rect box, vector<Tile> &tiles )
{
    //Go through the tiles
    for( int t = 0; t < (int)tiles.size(); t++ )
    {
        //If the tile is a wall type tile
        if( ( tiles[ t ].get_type() == TILE_COINS ) )
        {
            //If the collision box touches the wall tile
            if( check_collision( box, tiles[ t ].get_box() ) == true )
            {
                SCORE++;
				tiles[ t ].type = TILE_EMPTY;
            }
        }
    }
}

//check if next tile on what monster step on is empty tile
bool monster_reaches_end( SDL_Rect box, vector<Tile> &tiles, bool goes_right )
{
	//check if he not stand on GROUND lowest level and if he not goes in to a wall of level
	if( box.y + box.h / 2 < LEVEL_HEIGHT - TILE_HEIGHT && box.x > TILE_WIDTH && box.x < LEVEL_WIDTH - TILE_WIDTH )
	{
		unsigned int P = 0;
		bool stands_on_wall = false;
		bool stands_next_to_hole_on_right = false;
		bool stands_next_to_hole_on_left = false;
		//Go through the tiles
		for( int t = 0; t < (int)tiles.size(); t++ )
		{ 
			//If the center X of monster inside this tile
			if( box.x + box.w / 2 >= tiles[ t ].X && box.x + box.w / 2 <= tiles[ t ].X + TILE_WIDTH )
			{
				//If the center Y of monster inside this tile
				if( box.y + box.h / 2 >= tiles[ t ].Y && box.y + box.h / 2 <= tiles[ t ].Y + TILE_HEIGHT )
				{
					//If the tile is an empty tile
					if( ( tiles[ t ].get_type() == TILE_EMPTY ) )
					{
						P = t;
					}
				}
			}
		}
		//check if tile under monster is not empty
		if ( tiles[ P + LEVEL_WIDTH / TILE_WIDTH ].type >= TILE_WALL && tiles[ P + LEVEL_WIDTH / TILE_WIDTH  ].type < TILE_MAN )
		{
			stands_on_wall = true;
		}
		//check if monster stands on wall and P not first ot almost last tile 
		if( stands_on_wall &&  P >= 1 && P < tiles.size() )
		{
			//IF tile x + 1 y + 1 is an empty tile
			if ( tiles[ P + 1 + LEVEL_WIDTH / TILE_WIDTH ].get_type() == TILE_EMPTY && goes_right == true )
			{
				stands_next_to_hole_on_right = true;
			}
			//IF tile x - 1 y + 1 is an empty tile
			if ( tiles[ P - 1 + LEVEL_WIDTH / TILE_WIDTH].get_type() == TILE_EMPTY )//&& goes_right == false )
			{ 
				stands_next_to_hole_on_left = true;
			}
			//check in what direction is hole
			if( stands_next_to_hole_on_right )
			{
				//If the collision box touches the wall tile
				if( check_collision( box, tiles[ P + 1 ].get_box() ) == true )
				{
					return true;
				}
			}
			//check in what direction is hole
			if( stands_next_to_hole_on_left )
			{
				//If the collision box touches the wall tile
				if( check_collision( box, tiles[ P - 1 ].get_box() ) == true )
				{
					return true;
				}
			}
		}
	}
	//if all fine
	return false; 
}

bool set_tiles( vector<Tile> &tiles )
{
	//clear all existing tiles before creating new
	tiles.clear();

    //The tile offsets
    int x = 0, y = 0;

    //Open the map
    std::ifstream map( "4a4ik.map" );

    //If the map couldn't be loaded
    if( map == NULL )
    {
        return false;
    }

	//Determines what kind of tile will be made
    int tileType = -1;

	//Read size of map from file
    map >> tileType;
	LEVEL_WIDTH = tileType;
	map >> tileType;
	LEVEL_HEIGHT = tileType;

    //Initialize the tiles
    for ( int n = 0; n < ( LEVEL_WIDTH / TILE_WIDTH ) * ( LEVEL_HEIGHT / TILE_HEIGHT ); n++ )
    {
		if( map.eof() == false )
		{
			//Read tile from map file
			map >> tileType;
		}

		//If there was a problem in reading the map
        if( map.bad() == true )
        {
            //Stop loading map
            map.close();
            return false;
        }

        //If the number is a valid tile number
        if( ( tileType >= 0 ) && ( tileType < TILE_SPRITES ) && map.eof() == false )
        {
			//If tile where man start game
			if ( tileType == TILE_MAN )
			{ 
				MAN_START_X = x;
				MAN_START_Y = y;
				MAN_START_POINT = true;
			}
            tiles.push_back( Tile( x, y, tileType ) );
        }
		//Check if he created tile// n + 1 because n = 0 tiles.size = 1
		if( (int)tiles.size() < n + 1 )
		{
			tiles.push_back( Tile( x, y, 0 ) );
		}

        //Move to next tile spot
        x += TILE_WIDTH;

        //If we've gone too far
        if( x >= LEVEL_WIDTH && y < LEVEL_HEIGHT - TILE_HEIGHT )
        {
            //Move back
            x = 0;

            //Move to the next row
            y += TILE_HEIGHT;
        }
    }

    //Close the file
    map.close();

    //If the map was loaded fine
    return true;
}