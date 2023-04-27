#include"ThreatsObject.h"

ThreatsObject::ThreatsObject()
{
	width_frame_ = 0;
	height_frame_ = 0;
	x_val_ = 0.0;
	y_val_ = 0.0;
	x_pos_ = 0.0;
	y_pos_ = 0.0;
	on_ground_ = 0;
	come_back_time_ = 0;
	frame_ = 0;
}

ThreatsObject::~ThreatsObject()
{
	Free();
}

bool ThreatsObject::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);
	if (ret)
	{
		width_frame_ = rect_.w / THREAT_FRAME_NUM;
		height_frame_ = rect_.h / THREAT_FRAME_NUM;
	}
}

void ThreatsObject::set_clips()
{
	if (width_frame_ > 0 && height_frame_ > 0)
	{
		for (int i = 0; i < THREAT_FRAME_NUM; i++)
		{
			frame_clip_[i].x = i * width_frame_;
			frame_clip_[i].y = 0;
			frame_clip_[i].w = width_frame_;
			frame_clip_[i].h = height_frame_;
		}
	}
};

void ThreatsObject::Show(SDL_Renderer* des)
{
	if (come_back_time_ == 0)
	{
		rect_.x = x_pos_ - map_x_;
		rect_.y = y_pos_ - map_y_;
		frame_++;
		if (frame_ >= THREAT_FRAME_NUM)
		{
			frame_ = 0;
		}

		SDL_Rect* currentClip = &frame_clip_[frame_];
		SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };
		SDL_RenderCopy(des, p_object_, currentClip, &renderQuad);
	}
}

void ThreatsObject::DoPlayer(Map& gmap)
{
	if (come_back_time_ == 0)
	{
		x_val_ = 0;
		y_val_ += THREAT_GRAVITY_SPEED;
		if (y_val_ >= THREAT_MAX_FALL_SPEED)
		{
			if (y_val_ >= THREAT_MAX_FALL_SPEED)
				y_val_ = THREAT_MAX_FALL_SPEED;
		}

		CheckToMap(gmap);
	}
	else if (come_back_time_ > 0)
	{
		come_back_time_--;
		if (come_back_time_ == 0)
		{
			x_val_ = 0;
			y_val_ = 0;
			if (x_pos_ > 256)
			{
				x_pos_ -= 256;
			}
			else
			{
				x_pos_ = 0;
			}
			y_pos_ = 0;
			come_back_time_ = 0;
		}
	}
}

void ThreatsObject::CheckToMap(Map& map_data)
{
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
			if (map_data.tile[y1][x2] != BLANKTILE || map_data.tile[y2][x2] != BLANKTILE)
			{
				x_pos_ = x2 * TILE_SIZE;
				x_pos_ -= TILE_SIZE + 1;
				x_val_ = 0;
			}
		}
		else if (x_val_ < 0)
		{
			if (map_data.tile[y1][x1] != BLANKTILE || map_data.tile[y2][x1] != BLANKTILE)
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
			if (map_data.tile[y2][x1] != BLANKTILE || map_data.tile[y2][x2] != BLANKTILE)
			{
				y_pos_ = y2 * TILE_SIZE;
				y_pos_ -= TILE_SIZE;
				y_val_ = 0;
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
