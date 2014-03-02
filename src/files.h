/*This source code copyrighted by Lazy Foo' Productions (2004-2009) and may not
be redestributed without written permission.*/

//The headers
#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include <fstream>
#include <vector>

using namespace std;

//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//The frame rate
const int FRAMES_PER_SECOND = 50;

//The dimensions of the level
int LEVEL_WIDTH = 1920;
int LEVEL_HEIGHT = 480;

//Where player goes
bool DIRECTION_RIGHT = true;

//Tile constants
const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;
const int TILE_SPRITES = 9;

//The different tile sprites
const int TILE_EMPTY = 0;
const int TILE_COINS = 1;
const int TILE_WALL = 2;
const int TILE_GRASS_LEFT = 3;
const int TILE_GRASS_CENTER = 4;
const int TILE_GRASS_RIGHT = 5;
const int TILE_FLOOR = 6;
const int TILE_MAN = 7;
const int TILE_SNAIL = 8;

//Man stuff
const int MAN_SPRITES = 6;

const int MAN_WIDTH = 18;
const int MAN_HEIGHT = 25;

const int MAN_RIGHT_1 = 0;
const int MAN_RIGHT_2 = 1;
const int MAN_LEFT_1 = 3;
const int MAN_LEFT_2 = 4;

int MAN_START_X = 0;
int MAN_START_Y = 0;

const int MOVE_SPEED = 4;
const int JUMP_SPEED = 8;

//Menu sheets
const int TOTAL_MENU = 5;
const int MENU_SPRITES = 10;

const int MENU_WIDTH = 200;
const int MENU_HEIGHT = 50;

const int MENU_RESUME = 0;
const int MENU_NEW_GAME = 1;
const int MENU_LEVEL_EDITOR = 2;
const int MENU_OPTIONS = 3;
const int MENU_EXIT = 4;
const int MENU_RESUME_LIGHTED = 5;
const int MENU_NEW_GAME_LIGHTED = 6;
const int MENU_LEVEL_EDITOR_LIGHTED = 7;
const int MENU_OPTIONS_LIGHTED = 8;
const int MENU_EXIT_LIGHTED = 9;

//Game int's
int SCORE = 0;
int DEATHS = 0;
bool GAME_STARTED = false;
bool PAUSE = true;
bool EDIT_LEVEL = false;
bool NEW_GAME = false;
bool NEW_MAN = false;
bool EDIT_PUT_TILES = false;

//level editor stuff
bool MAN_START_POINT = false;
bool LEVEL_SAVED = true;

//MOnster stuff
const int SNAIL = 0;
const int SNAIL_WIDTH = 40;
const int SNAIL_HEIGHT = 29;
const int SNAIL_SPEED = 1;
const int SNAIL_CHANGE_SPRITE_TIME = 14;
const int SNAIL_SPRITES = 4;
const int SNAIL_RIGHT_1 = 0;
const int SNAIL_RIGHT_2 = 1;
const int SNAIL_LEFT_1 = 2;
const int SNAIL_LEFT_2 = 3;

//what crate touches man
int crate_col = 0;

//The surfaces
SDL_Surface *screen = NULL;
SDL_Surface *tileSheet = NULL;
SDL_Surface *manSheet = NULL;
SDL_Surface *menuSheet = NULL;
SDL_Surface *monsterSheet = NULL;

//Sprite from the tile sheet
SDL_Rect clips[ TILE_SPRITES ];
SDL_Rect man_clips[ MAN_SPRITES ];
SDL_Rect menu_clips[ MENU_SPRITES ];
SDL_Rect snail_clips[ SNAIL_SPRITES ];

//The camera
SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

//The event structure
SDL_Event event;

//File stream for the game log.
std::ofstream logger( "log.txt" );

//Quit flag
bool quit = false;

SDL_Surface *load_image( std::string filename )
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old surface
        SDL_FreeSurface( loadedImage );

        //If the surface was optimized
        if( optimizedImage != NULL )
        {
            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }

    //Return the optimized surface
    return optimizedImage;
}

bool load_files()
{
	tileSheet = load_image( "gfx/tileSheet.png" );
	manSheet = load_image( "gfx/manSheet.png" );
	menuSheet = load_image( "gfx/menuSheet.png" );
	monsterSheet = load_image( "gfx/monsterSheet.png" );

    //If there was a problem in loading the square
    if( tileSheet == NULL || manSheet == NULL || menuSheet == NULL || monsterSheet == NULL )
    {
        return false;
    }

    //If everything loaded fine
    return true;
}

void log( std::string file, int line, string message = "" )
{
    //Write message to file
    logger << file << ", " << line << ":" << message << endl;
    
    //Flush the buffer
    logger.flush();
}

