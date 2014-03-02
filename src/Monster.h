class Monster
{
	public : 

		SDL_Rect box;

		Monster( int x, int y, int monsterType );

		int xVel, yVel, X, Y;
		int fall, sprite;
		int D_sprite;
		int touched_tile;
		int type, speed;
		int sprite_change_time;
		bool monster_right;
		bool standing;

		bool monster_touches_wall( vector<Tile> &tiles );
		bool monster_stands_on_wall( vector<Tile> &tiles );
		void check_type();
		void move( vector<Tile> &tiles );
		void show();
};

Monster::Monster( int x, int y, int monsterType )
{
	box.x = x;
	box.y = y;
	X = x;
	Y = y;
	box.h = SNAIL_HEIGHT;
	box.w = SNAIL_WIDTH;

	type = monsterType;
	xVel = 0;
	yVel = 0;
	fall = 0;
	sprite = 0;
	touched_tile = 0;
	D_sprite = 0;
	speed = 1;
	sprite_change_time = 1;
	standing = false;
	monster_right = true;
}

bool Monster::monster_touches_wall( vector<Tile> &tiles )
{
    //Go through the tiles
    for( int t = 0; t < (int)tiles.size(); t++ )
    {
		//check if he colide with wall
		//If the tile is a wall type tile
		if( ( tiles[ t ].type >= TILE_WALL ) && ( tiles[ t ].type <= TILE_FLOOR ) )
		{ 
			if ( check_collision( box, tiles[ t ].box ) == true )
			{
				return true;
			}
		}
    }
    //If no wall tiles were touched
    return false;
}

bool Monster::monster_stands_on_wall( vector<Tile> &tiles )
{
    //Go through the tiles
    for( int t = 0; t < (int)tiles.size(); t++ )
    {
		//Check if he stands on wall
        //check if X of monster on tile
        if( box.x >= tiles[ t ].X && box.x <= tiles[ t ].X + TILE_WIDTH )
        { 
			//check if Y of monster inside tile
			if( box.y + box.h + 1 >= tiles[ t ].Y && box.y + box.h + 1 <= tiles[ t ].Y + TILE_HEIGHT )
			{ 
				//If the tile is a wall type tile
				if( ( tiles[ t ].get_type() >= TILE_WALL ) && ( tiles[ t ].get_type() <= TILE_FLOOR ) )
				{	
					touched_tile = t;
					return true;
				}
			}
		}
		//check if RIGHT PART of monster on tile
        if( box.x + box.w >= tiles[ t ].X && box.x + box.w <= tiles[ t ].X + TILE_WIDTH )
        { 
			//check if Y of monster inside tile
			if( box.y + box.h + 1 >= tiles[ t ].Y && box.y + box.h + 1 <= tiles[ t ].Y + TILE_HEIGHT )
			{ 
				//If the tile is a wall type tile
				if( ( tiles[ t ].get_type() >= TILE_WALL ) && ( tiles[ t ].get_type() <= TILE_FLOOR ) )
				{	
					touched_tile = t;
					return true;
				}
			}
        }
    }
    //If no wall tiles were touched
    return false;
}


void Monster::check_type()
{
	if ( type == SNAIL )
	{
		box.w = SNAIL_WIDTH;
		box.h = SNAIL_HEIGHT;
		speed = SNAIL_SPEED;
		sprite_change_time = SNAIL_CHANGE_SPRITE_TIME;
	}
}

void Monster::move( vector<Tile> &tiles )
{
	//if monster goes right and not falling
	if ( monster_right == true && standing == true )
	{ xVel = speed; }

	if ( monster_right == false && standing == true )
	{ xVel = -speed; }

	if ( PAUSE == false && EDIT_LEVEL == false )
	{
		//Check what direction monster goes
		//RIght
		if ( xVel > 0 )
		{
			D_sprite++;

			if ( D_sprite >= sprite_change_time )
			{ sprite++; D_sprite = 0; }

			if ( sprite >= 2 )
			{
				sprite = 0;
			}
		}
		//LEFT
		if ( xVel < 0 )
		{
			D_sprite++;

			if ( D_sprite >= sprite_change_time )
			{ sprite++; D_sprite = 0; }

			if ( sprite >= 4 )
			{
				sprite = 2;
			}
		}

		// calculate if monster not falling
		if ( monster_stands_on_wall( tiles ) == true )
		{ 
			standing = true;
		}
		else 
		{ 
			standing = false; 
		}

		if ( standing == false )
		{
			xVel = 0;
			fall++;
			if ( fall >= 2 )
			{
				yVel += 1;
				fall = 0;
			}
		}

		if ( monster_right == true && standing == true )
		{ xVel = speed; }

		if ( monster_right == false && standing == true )
		{ xVel = -speed; }

		// if he stands ONLY then check if he reaches end
		if ( standing == true )
		{
			if ( monster_reaches_end( box, tiles, monster_right ) == true || monster_touches_wall( tiles ) == true )
			{ 
				monster_right = !monster_right;
				D_sprite = 0;
				if ( monster_right == true )
				{
					//Inverted because i change monster_right just before it
					box.x += speed + 1;
					sprite = 0;
				}
				else
				{
					box.x -= speed + 1;
					sprite = 2;
				}
			}
		}

		//Move the dot left or right
		box.x += xVel;
	    
		//If the dot went too far to the left or right
		if( ( box.x < 0 ) || ( box.x + box.w > LEVEL_WIDTH ) )
		{
			monster_right = !monster_right;
			D_sprite = 0;
			if ( monster_right == true )
			{
				//Inverted because i change monster_right just before it
				box.x += speed + 1;
				sprite = 0;
			}
			else
			{
				box.x -= speed + 1;
				sprite = 2;
			}
		}
	    
		//Move the dot up or down
		box.y += yVel;

		//check for collision with crate
		if (  box.y + box.h > LEVEL_HEIGHT || box.y < 0 || monster_stands_on_wall( tiles ) == true && standing == false )
		{
			//IF fall
			if ( yVel > 0 )
			{	box.y = tiles[ touched_tile ].Y - box.h;	}
			else 
			{	box.y = tiles[ touched_tile ].Y + TILE_HEIGHT;	}
			yVel = 0;
			fall = 0;
		}
	}
}

void Monster::show( )
{
	if ( PAUSE == false && EDIT_LEVEL == false && check_collision( camera, box ) == true )
	{ 
		if ( type == SNAIL )
		{ apply_surface( box.x - camera.x, box.y - camera.y, monsterSheet, screen, &snail_clips[ sprite ] ) ; }
	}	
}

bool set_monsters( vector<Monster> &monsters )
{
	//Delete all monsters
	monsters.clear();

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

	//2 times read because there width and height of level
	map >> tileType;
	map >> tileType;

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
        if( ( tileType == TILE_SNAIL ) )
        {
			monsters.push_back( Monster( x, y, 0 ) );
        }

        //Move to next tile spot
        x += TILE_WIDTH;

        //If we've gone too far
        if( x >= LEVEL_WIDTH )
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