//The tile
class Tile
{
    public:
    //The attributes of the tile
    SDL_Rect box;

    //The tile type
    int type, X, Y;

    //Initializes the variables
    Tile( int x, int y, int tileType );

	//Make proper collision boxes for tiles
	void check_types();
    //Shows the tile
    void show();

    //Get the tile type
    int get_type();

    //Get the collision box
    SDL_Rect get_box();
};

Tile::Tile( int x, int y, int tileType )
{
    //Get the offsets
    box.x = x;
    box.y = y;
	X = x;
	Y = y;

    //Set the collision box
    box.w = TILE_WIDTH;
    box.h = TILE_HEIGHT;

    //Get the tile type
    type = tileType;
}

void Tile::check_types()
{
	if ( type == TILE_COINS )
	{
		box.x = X + 7;
		box.y = Y + 8;
		box.w = 19;
		box.h = 19;
	}
}

void Tile::show()
{
    //If the tile is on screen
    if( check_collision( camera, box ) == true )
    {
		if ( type >= TILE_MAN && type <= TILE_SNAIL )
		{
			// if in game show empty tile
			if ( EDIT_LEVEL == false )
			{
				//Show the tile
				apply_surface( X - camera.x, Y - camera.y, tileSheet, screen, &clips[ TILE_EMPTY ] );
			}
			//if in level editor show tile
			if ( EDIT_LEVEL == true )
			{
				//Show the tile
				apply_surface( X - camera.x, Y - camera.y, tileSheet, screen, &clips[ type ] );
			}
		}
		else
		{
			//Show the tile
			apply_surface( X - camera.x, Y - camera.y, tileSheet, screen, &clips[ type ] );
		}
    }
}

int Tile::get_type()
{
    return type;
}

SDL_Rect Tile::get_box()
{
    return box;
}