#include "MainObject.h"

MainObject::MainObject()
{
	x_val_ = 0;
	y_val_ = 0;
	ifstream pos_file(Save_Position);
	pos_file >> x_pos_;
	pos_file >> y_pos_;
	pos_file.close();
	frame_ = 0;
	input_type_.LEFT_ = 0;
	input_type_.RIGHT_ = 0;
	input_type_.UP_ = 0;
	input_type_.d_ = 0;
	input_type_.a_ = 0;
	on_ground = true;
	off_ = 0;
}

MainObject::~MainObject()
{

}

bool MainObject::LoadImg(string path, SDL_Renderer* screen)
{
	bool set = BaseObject::LoadImg(path, screen);
	return set;
}

void MainObject::set_clips()
{
	for (int i = 0; i < 5; i++)
	{
		frame_clip_[i].x = i * TILE_SIZE;
		frame_clip_[i].y = 0;
		frame_clip_[i].w = TILE_SIZE;
		frame_clip_[i].h = TILE_SIZE;
	}
}

void MainObject::Show(SDL_Renderer* des, int cam_y)
{
	if (num_left_ > 0)
	{
		LoadImg(Jump_Left_File_Name, des);
		if (input_type_.LEFT_ == 1)
		{
			frame_ = 0;
		}
		else if (num_jump_left_ > 0)
		{
			frame_ = 1;
		}
		else frame_ = 2;
	}
	else if (num_right_ > 0)
	{
		LoadImg(Jump_Right_File_Name, des);
		if (input_type_.RIGHT_ == 1)
		{
			frame_ = 0;
		}
		else if (num_jump_right_ > 0)
		{
			frame_ = 1;
		}
		else frame_ = 2;
	}
	else if (input_type_.UP_ == 1 || input_type_.d_ == 1 || input_type_.a_ == 1)
	{
		bool ok = 0;
		if (input_type_.UP_ == 1)
		{
			LoadImg(Jump_Up_File_Name, des);
			ok = 1;
		}
		else if (input_type_.d_ == 1)
		{
			LoadImg(Right_File_Name, des);
			ok = 1;
		}
		else if (input_type_.a_ == 1)
		{
			LoadImg(Left_File_Name, des);
			ok = 1;
		}
		frame_++;
		if (frame_ >= 5)
		{
			frame_ = 0;
		}
	}
	else frame_ = 4;

	rect_.x = x_pos_;
	rect_.y = y_pos_ - cam_y;
	SDL_Rect* current_clip = &frame_clip_[frame_];
	SDL_Rect renderQuad = { rect_.x, rect_.y, TILE_SIZE, TILE_SIZE };
	SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
}

void MainObject::HandelInputAction(SDL_Event events, SDL_Renderer* screen)
{
	if (on_ground == true)
	{
		if (events.type == SDL_KEYDOWN)
		{
			switch (events.key.keysym.sym)
			{
			case SDLK_UP:
			{
				input_type_.UP_ = 1;
				input_type_.d_ = 0;
				input_type_.a_ = 0;
				num_right_ = 0;
				num_jump_right_ = 0;
				num_right_ = 0;
				num_jump_right_ = 0;
				if (off_) Mix_PlayChannel(-1, sound_effect[1], 0);
			}
			break;
			case SDLK_LEFT:
			{
				input_type_.LEFT_ = 1;
				num_right_ = 0;
				num_jump_right_ = 0;
				num_left_ += GO_SPEED;
				if (num_left_ > MAX_X_GO)
				{
					num_left_ = MAX_X_GO;
				}
				num_jump_left_ += JUMP_SPEED;
				if (num_jump_left_ > MAX_Y_UP)
				{
					num_jump_left_ = MAX_Y_UP;
				}
			}
			break;
			case SDLK_RIGHT:
			{
				input_type_.RIGHT_ = 1;
				num_left_ = 0;
				num_jump_left_ = 0;
				num_right_ += GO_SPEED;
				if (num_right_ > MAX_X_GO)
				{
					num_right_ = MAX_X_GO;
				}
				num_jump_right_ += JUMP_SPEED;
				if (num_jump_right_ > MAX_Y_UP)
				{
					num_jump_right_ = MAX_Y_UP;
				}
			}
			break;
			case SDLK_d:
			{
				input_type_.d_ = 1;
				input_type_.a_ = 0;
				if (off_) Mix_PlayChannel(-1, sound_effect[0], 0);
			}
			break;
			case SDLK_a:
			{
				input_type_.a_ = 1;
				input_type_.d_ = 0;
				if (off_) Mix_PlayChannel(-1, sound_effect[0], 0);
			}
			break;
			}
		}
	}
	if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_UP:
		{

		}
		break;
		case SDLK_LEFT:
		{
			input_type_.LEFT_ = 0;
			if (off_) Mix_PlayChannel(-1, sound_effect[1], 0);
		}
		break;
		case SDLK_RIGHT:
		{
			input_type_.RIGHT_ = 0;
			if (off_) Mix_PlayChannel(-1, sound_effect[1], 0);
		}
		break;
		case SDLK_d:
		{
			input_type_.d_ = 0;
		}
		break;
		case SDLK_a:
		{
			input_type_.a_ = 0;
		}
		break;
		}
	}
}

void MainObject::DoPlayer(Map& map_data)
{
	x_val_ = 0;
	if (input_type_.UP_ == 1 && max_up > 0)
	{
		y_val_ = -max_up;
		max_up -= GRAVITY_SPEED;
		if (max_up < 0)
		{
			max_up = 0;
		}
	}
	if (input_type_.d_ == 1)
	{
		x_val_ = GRAVITY_SPEED;
	}
	else if (input_type_.a_ == 1)
	{
		x_val_ = -GRAVITY_SPEED;
	}
	if (input_type_.LEFT_ == 0)
	{
		if (num_left_ > 0 || num_jump_left_ > 0)
		{
			x_val_ = -num_left_;
			num_left_ -= GO_SPEED;
			if (num_left_ < GO_SPEED)
			{
				num_left_ = GO_SPEED;
			}
			if (num_jump_left_ > 0)
			{
				y_val_ = -num_jump_left_;
			}
			num_jump_left_ -= JUMP_SPEED;
			if (num_jump_left_ < 0)
			{
				num_jump_left_ = 0;
			}
		}
	}
	if (input_type_.RIGHT_ == 0)
	{
		if (num_right_ > 0 || num_jump_right_ > 0)
		{
			x_val_ = num_right_;
			num_right_ -= GO_SPEED;
			if (num_right_ < GO_SPEED)
			{
				num_right_ = GO_SPEED;
			}
			if (num_jump_right_ > 0)
			{
				y_val_ = -num_jump_right_;
			}
			num_jump_right_ -= JUMP_SPEED;
			if (num_jump_right_ < 0)
			{
				num_jump_right_ = 0;
			}
		}
	}
	y_val_ += GRAVITY_SPEED;
	if (y_val_ > MAX_FALL_SPEED)
	{
		y_val_ = MAX_FALL_SPEED;
	}
	CheckToMap(map_data);
}

void MainObject::CheckToMap(Map& map_data)
{
	on_ground = false;
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	x1 = (x_pos_ + x_val_) / TILE_SIZE;
	x2 = (x_pos_ + x_val_ + TILE_SIZE - 1) / TILE_SIZE;

	y1 = (y_pos_) / TILE_SIZE;
	y2 = (y_pos_ + TILE_SIZE - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (x_val_ > 0)
		{
			if (map_data.tile[y1][x2] != 0 || map_data.tile[y2][x2] != 0)
			{
				x_pos_ = x2 * TILE_SIZE;
				x_pos_ -= TILE_SIZE + 1;
				x_val_ = 0;
			}
		}
		else if (x_val_ < 0)
		{
			if (map_data.tile[y1][x1] != 0 || map_data.tile[y2][x1] != 0)
			{
				x_pos_ = (x1 + 1) * TILE_SIZE;
				x_val_ = 0;
			}
		}
	}

	x1 = (x_pos_ + 10) / TILE_SIZE;
	x2 = (x_pos_ + TILE_SIZE - 10) / TILE_SIZE;

	y1 = (y_pos_ + y_val_) / TILE_SIZE;
	y2 = (y_pos_ + y_val_ + TILE_SIZE - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (y_val_ > 0)
		{
			if (map_data.tile[y2][x1] != 0 || map_data.tile[y2][x2] != 0)
			{
				y_pos_ = y2 * TILE_SIZE;
				y_pos_ -= TILE_SIZE;
				y_val_ = 0;
				on_ground = true;
				if (input_type_.UP_ == 1)
				{
					if (off_) Mix_PlayChannel(-1, sound_effect[2], 0);
				}
				input_type_.UP_ = 0;
				max_up = 40;
				if (num_right_ > 0 && num_jump_right_ == 0)
				{
					if (off_) Mix_PlayChannel(-1, sound_effect[2], 0);
				}
				if (num_left_ > 0 && num_jump_left_ == 0)
				{
					if (off_) Mix_PlayChannel(-1, sound_effect[2], 0);
				}
				if (num_jump_left_ == 0)
				{
					num_left_ = 0;
				}
				if (num_jump_right_ == 0)
				{
					num_right_ = 0;
				}
			}
		}
		else if (y_val_ < 0)
		{
			if (map_data.tile[y1][x1] != 0 || map_data.tile[y1][x2] != 0)
			{
				y_pos_ = (y1 + 1) * TILE_SIZE;
				y_val_ = 0;
			}
		}
	}

	x_pos_ += x_val_;
	y_pos_ += y_val_;

	if (x_pos_ < 0)
	{
		x_pos_ = 0;
	}
	else if (x_pos_ + TILE_SIZE > MAX_MAP_X * TILE_SIZE)
	{
		x_pos_ = (MAX_MAP_X * TILE_SIZE) - TILE_SIZE - 1;
	}
	if (y_pos_ < 0)
	{
		y_pos_ = 0;
	}
	else if (y_pos_ + TILE_SIZE > MAX_MAP_Y * TILE_SIZE)
	{
		y_pos_ = (MAX_MAP_Y * TILE_SIZE) - TILE_SIZE - 1;
	}
}

void MainObject::LoadMix()
{
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	char file_img[30];
	for (int i = 0; i < 3; i++)
	{
		sprintf_s(file_img, "Sound/%d.wav", i);
		sound_effect[i] = Mix_LoadWAV(file_img);
	}
}
