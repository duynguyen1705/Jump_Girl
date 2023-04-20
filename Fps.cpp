#include "FPS.h"
#include "CommonFunc.h"

Fps::Fps()
{
	start_tick_ = 0;
	paused_tick_ = 0;
	is_paused_ = false;
	is_started_ = false;
}

Fps::~Fps()
{

}

void Fps::start()
{
	is_started_ = true;
	is_paused_ = false;
	start_tick_ = SDL_GetTicks();
}

int Fps::get_tick_()
{
	if (is_started_ == true)
	{
		if (is_paused_ == true)
		{
			return paused_tick_;
		}
		else
		{
			return SDL_GetTicks() - start_tick_;
		}
	}
	return 0;
}
