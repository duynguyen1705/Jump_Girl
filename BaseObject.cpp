#include "BaseObject.h"
#include "CommonFunc.h"

BaseObject::BaseObject()
{
	p_object_ = NULL;
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = 0;
	rect_.h = 0;
}

BaseObject::~BaseObject()
{
	Free();
}

bool BaseObject::LoadImg(string path, SDL_Renderer* screen)
{
	if (p_object_ != NULL)
	{
		SDL_DestroyTexture(p_object_);
	}
	SDL_Texture* new_texture = NULL;
	SDL_Surface* load_sunrface = IMG_Load(path.c_str());
	if (load_sunrface != NULL)
	{
		SDL_SetColorKey(load_sunrface, SDL_FALSE, SDL_MapRGB(load_sunrface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
		new_texture = SDL_CreateTextureFromSurface(screen, load_sunrface);
		if (new_texture != NULL)
		{
			rect_.w = load_sunrface->w;
			rect_.h = load_sunrface->h;
		}
		SDL_FreeSurface(load_sunrface);
	}
	p_object_ = new_texture;
	return p_object_ != NULL;
}

void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip)
{
	SDL_Rect renderquad = { rect_.x, rect_.y, rect_.w, rect_.h };
	SDL_RenderCopy(des, p_object_, clip, &renderquad);
}

void BaseObject::Free()
{
	SDL_DestroyTexture(p_object_);
	p_object_ = NULL;
	rect_.w = 0;
	rect_.h = 0;
}
