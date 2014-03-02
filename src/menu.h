class Menu
{
	public : 

		SDL_Rect box;

		Menu();

		bool lighted;
		bool used;
		int num;

		void handle_input();
		void use();
		void show();
};

Menu::Menu()
{
	box.x = 220;
	//Y in use{}
	box.h = 50;
	box.w = 200;

	lighted = false;
	used = false;
}

void Menu::handle_input()
{
	//The mouse offsets
    int x = 0, y = 0;
    
    //If the mouse moved
	if( event.type == SDL_MOUSEMOTION && PAUSE == true )
    {
        //Get the mouse offsets
        x = event.motion.x;
        y = event.motion.y;
        
        //If the mouse is over the button
        if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
        {
            //Light the button
            lighted = true;
        }
		else 
		{
			lighted = false;
		}
    }
	 //If a mouse button was released
    if( event.type == SDL_MOUSEBUTTONUP && PAUSE == true )
    {
        //If the left mouse button was released
        if( event.button.button == SDL_BUTTON_LEFT )
        { 
            //Get the mouse offsets
            x = event.button.x;
            y = event.button.y;
        
            //If the mouse is over the button
            if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
            {
                used = true;
            }
        }
    }
}

void Menu::use()
{
	box.y = 25 + 80 * num;
	if ( used )
	{
		if ( num == MENU_RESUME && GAME_STARTED == true )
		{
			PAUSE = false;
		}
		if ( num == MENU_NEW_GAME )
		{
			NEW_GAME = true;
		}
		if ( num == 2 )
		{
			//move camera to beginning of the level
			camera.x = 0;
			LEVEL_SAVED = false;
			EDIT_LEVEL = true;
			PAUSE = false;
			EDIT_PUT_TILES = true;
			GAME_STARTED = false;
		}
		if ( num == 4 )
		{
			quit = true;
		}
		used = false;
	}
}

void Menu::show()
{
	if ( PAUSE )
	{
		if ( lighted == false )
		{ apply_surface( box.x, box.y, menuSheet, screen, &menu_clips[ num ] ); }
		if ( lighted == true )
		{ apply_surface( box.x, box.y, menuSheet, screen, &menu_clips[ num + 5 ] ); }
	}
}