class Man
{
	public : 

		SDL_Rect box;

		Man();

		int xVel, yVel;
		int fall, sprite;
		int D_sprite;
		bool standing;
		bool jump;

		void set_camera();
		void handle_input();
		void move( vector<Tile> &tiles );
		void show();
};

Man::Man()
{
	box.x = 0;
	box.y = 0;
	box.h = MAN_HEIGHT;
	box.w = MAN_WIDTH;

	xVel = 0;
	yVel = 0;
	fall = 0;
	sprite = 0;
	D_sprite = 0;
	standing = false;
	jump = true;
}

void Man::handle_input()
{
	if ( PAUSE == false || EDIT_LEVEL == false )
	{
		 //If a key was pressed
		if( event.type == SDL_KEYDOWN )
		{
			//Adjust the velocity
			switch( event.key.keysym.sym )
			{
				case SDLK_UP: if ( yVel == 0 && jump == false ) { fall = 0; yVel = -JUMP_SPEED; jump = true; }; break;
				case SDLK_LEFT: xVel -= MOVE_SPEED; break;
				case SDLK_RIGHT: xVel += MOVE_SPEED; break;    
			}
		}
		//If a key was released
		else if( event.type == SDL_KEYUP )
		{
			//Adjust the velocity
			switch( event.key.keysym.sym )
			{
				case SDLK_LEFT: xVel += MOVE_SPEED; break;
				case SDLK_RIGHT: xVel -= MOVE_SPEED; break;   
			}        
		}
	}
}

void Man::move( vector<Tile> &tiles )
{
	if ( PAUSE == false && EDIT_LEVEL == false )
	{
		if ( NEW_MAN )
		{
			box.x = MAN_START_X;
			box.y = MAN_START_Y;
			xVel = 0;
			yVel = 0;
			NEW_MAN = false;
		}
		//If touches coins
		touches_coins( box, tiles );

		//Check what direction man goes
		//RIght
		if ( xVel > 0 )
		{
			//If he walked to left
			if ( DIRECTION_RIGHT == false )
			{ 
				D_sprite = 0;
				sprite = MAN_RIGHT_1;
				DIRECTION_RIGHT = true;
			}

			D_sprite++;

			if ( D_sprite >= 8 )
			{ sprite++; D_sprite = 0; }

			if ( sprite >= MAN_RIGHT_2 + 1 )
			{
				sprite = MAN_RIGHT_1;
			}
		}
		//LEFT
		if ( xVel < 0 )
		{
			if ( DIRECTION_RIGHT == true )
			{ 
				D_sprite = 0;
				sprite = MAN_LEFT_1;
				DIRECTION_RIGHT = false;
			}

			D_sprite++;

			if ( D_sprite >= 8 )
			{ sprite++; D_sprite = 0; }

			if ( sprite >= MAN_LEFT_2 + 1 )
			{
				sprite = MAN_LEFT_1;
			}
		}
		if ( xVel == 0 )
		{
			if ( DIRECTION_RIGHT == true )
			{
				sprite = MAN_RIGHT_1;
			}
			else
			{
				sprite = MAN_LEFT_1;
			}
		}

		//Move the dot left or right
		box.x += xVel;
	    
		//If the dot went too far to the left or right
		if( ( box.x < 0 ) || ( box.x + box.w > LEVEL_WIDTH ) || touches_wall( box, tiles ) )
		{
			//move back
			box.x -= xVel;    
		}

			// calculate if man not falling
		if ( yVel == 0 && ( box.y == LEVEL_HEIGHT - box.w || touches_wall( box, tiles ) ) )
		{ standing = true;	}
		else { standing = false; }

		if ( standing == false )
		{
			fall++;
			if ( fall >= 2 )
			{
				yVel += 1;
				fall = 0;
			}
		}
	    
		//Move the dot up or down
		box.y += yVel;

		//check for collision with crate
		if (  box.y + box.h > LEVEL_HEIGHT || box.y < 0 || touches_wall( box, tiles ) )
		{
			//IF fall
			if ( yVel > 0 )
			{	box.y = tiles[ crate_col ].Y - box.h;	}
			else 
			{	box.y = tiles[ crate_col ].Y + TILE_HEIGHT;	}
			yVel = 0;
			fall = 0;
			jump = false;
		}
	}
}

void Man::set_camera()
{
	if ( PAUSE == false && EDIT_LEVEL == false )
	{
		//Center the camera over the dot
		camera.x = ( box.x + MAN_WIDTH / 2 ) - SCREEN_WIDTH / 2;
		camera.y = ( box.y + MAN_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;
	    
		//Keep the camera in bounds.
		if( camera.x < 0 )
		{
			camera.x = 0;    
		}
		if( camera.y < 0 )
		{
			camera.y = 0;    
		}
		if( camera.x > LEVEL_WIDTH - camera.w )
		{
			camera.x = LEVEL_WIDTH - camera.w;    
		}
		if( camera.y > LEVEL_HEIGHT - camera.h )
		{
			camera.y = LEVEL_HEIGHT - camera.h;    
		}    
	}
}

void Man::show()
{
	if ( PAUSE == false && EDIT_LEVEL == false )
	{ apply_surface( box.x - camera.x, box.y - camera.y, manSheet, screen, &man_clips[ sprite ] ); }
}