class Lom
{
	public : 

		SDL_Rect box;

		Lom( Man *myman );

		int attack_time;
		bool kill;

		void handle_input();
		void move( Man *myman );
		void attack();
};

Lom::Lom( Man *myman )
{
	box.x = myman->box.x + myman->box.w;
	box.y = myman->box.h;
	box.h = 20;
	box.w = 20;

	attack_time = 0;
	kill = false;
}

void Lom::handle_input()
{
	 //If a key was pressed
    if( event.type == SDL_KEYDOWN )
    {
        //Adjust the velocity
        switch( event.key.keysym.sym )
        {
            case SDLK_DOWN: kill = true; break;    
        }
    }
}

void Lom::move( Man *myman )
{
	if( DIRECTION_RIGHT == true )
	{
		box.x = myman->box.x + myman->box.w;
	}
	else
	{
		box.x = myman->box.x - myman->box.w;
	}
	box.y = myman->box.y;
}

void Lom::attack()
{
	if ( kill )
	{
		attack_time++;
		if ( attack_time >= 10 )
		{
			attack_time = 0;
			kill = false;
		}
	}
}