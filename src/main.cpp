#include "files.h"
#include "timer.h"
#include "voids.h"
#include "clips.h"
#include "menu.h"
#include "tile.h"
#include "set_tiles.h"
#include "man.h"
#include "level_editor.h"
#include "monster.h"
#include "keypresses.h"

int main( int argc, char* args[] )
{
    //The frame rate regulator
    Timer fps;

	//Stuff
	Man myMan;
	Menu myMenu[ TOTAL_MENU ];
	Level_editor Level_editor;
	vector<class Monster> monsters;

	for ( int n = 0; n < TOTAL_MENU; n++ )
	{ myMenu[ n ].num = n; }

	//The tiles that will be used
    vector<Tile> tiles;

    //Initialize
    if( init() == false )
    {
        return 1;
    }

    //Load the files
    if( load_files() == false )
    {
        return 1;
    }

	clip_tiles();

	//Set the tiles
    if( set_tiles( tiles ) == false )
    {
        return 1;
    }
	
	//Set the monsters in monster.h
    if( set_monsters( monsters ) == false )
    {
        return 1;
    }

    //While the user hasn't quit
    while( quit == false )
    {
        //Start the frame timer
        fps.start();

        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
			myMan.handle_input();

			for ( int n = 0; n < TOTAL_MENU; n++ )
			{ myMenu[ n ].handle_input(); }

			//handle key presses
			keypresses();

			Level_editor.handle_input( tiles );

            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }

		//create new game when in menu pressed new game
		create_new_game( tiles, monsters );

		//Check menu uses
		for ( int n = 0; n < TOTAL_MENU; n++ )
		{ myMenu[ n ].use(); }

		 //Make collision boxes
        for( int t = 0; t < (int)tiles.size(); t++ )
        {
			tiles[ t ].check_types();
        }

		//Check fot all monsters
		for ( int n = 0; n < (int)monsters.size(); n++ )
		{
			monsters[ n ].check_type();
		}

		//MOve stuff
		myMan.move( tiles );

		//Check fot all monsters
		for ( int n = 0; n < (int)monsters.size(); n++ )
		{
			monsters[ n ].move( tiles );
		}

		//set camera
		myMan.set_camera();
		Level_editor.set_camera();

        //Fill the screen white
        SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0, 150, 200 ) );

		//Show the tiles
        for( int t = 0; t < (int)tiles.size(); t++ )
        {
            tiles[ t ].show();
        }

		//Check fot all monsters
		for ( int n = 0; n < (int)monsters.size(); n++ )
		{
			monsters[ n ].show();
		}

		myMan.show();

		Level_editor.show();

		if ( PAUSE )
		{
			//Fill the screen BLACK
			SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0, 0, 0 ) );
		}

		for ( int n = 0; n < TOTAL_MENU; n++ )
		{ myMenu[ n ].show(); }

        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }

        //Cap the frame rate
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
	}
	
    //Save the tile map
    save_tiles( tiles );

    //Clean up
    clean_up( tiles );

	//Delete all monsters
	monsters.clear();

	//log( __FILE__, __LINE__ );

    return 0;
}
