﻿#include "CommonFunc.h"
#include "BaseObject.h"
#include "GameMap.h"
#include "MainObject.h"
#include "Fps.h"
#include "TextObject.h"
#include "ThreatsObject.h"

BaseObject g_background[numberOfMap];
BaseObject MenuVolumeOn;
BaseObject MenuVolumeOff;
BaseObject Victory;
BaseObject Tutorial;
BaseObject Introduce;
BaseObject Level;

Mix_Music* InGameSound;
Mix_Music* MenuSound;
Mix_Music* WinSound;

TTF_Font* font_time = NULL;


bool InitData()
{
	//init sound
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

	InGameSound = Mix_LoadMUS(InGame_Sound_File);
	MenuSound = Mix_LoadMUS(Menu_Sound_File);
	WinSound = Mix_LoadMUS(Win_Sound_File);

	//create window
	bool success = true;
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret < 0) return false;
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	g_window = SDL_CreateWindow("Jump Girl", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (g_window == NULL)
	{
		success = false;
	}
	else
	{
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if (g_screen == NULL)
		{
			success = false;
		}
		else
		{
			SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) && imgFlags))
			{
				success = false;
			}
		}

		if (TTF_Init() == -1)
		{
			success = false;
		}

		font_time = TTF_OpenFont(font, 15);
		if (font_time == NULL)
		{
			success = false;
		}
	}
	return success;
}

void LoadBackground()
{
	MenuVolumeOn.LoadImg(MenuVolumeOn_File_Name, g_screen);
	MenuVolumeOff.LoadImg(MenuVolumeOff_File_Name, g_screen);
	Victory.LoadImg(Victory_File_Name, g_screen);
	Tutorial.LoadImg(Turtorial_File_Name, g_screen);
	Introduce.LoadImg(Introduce_File_Name, g_screen);
	Level.LoadImg(Level_File_Name, g_screen);

	char file_img[10];
	for (int i = 0; i < numberOfMap; i++)
	{
		sprintf_s(file_img, "Img/%d.png", i);
		g_background[i].LoadImg(file_img, g_screen);
	}
}

bool Win(float x, float y)
{
	if (y == 300 && x < 700 && x > 649)
	{
		return true;
	}
	return false;
}

void close()
{
	for (int i = 0; i < numberOfMap; i++)
	{
		g_background[i].Free();
	}

	MenuVolumeOn.Free();
	MenuVolumeOff.Free();
	Victory.Free();
	Tutorial.Free();

	SDL_DestroyRenderer(g_screen);
	g_screen;
	SDL_DestroyWindow(g_window);
	g_window = NULL;
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* argv[])
{
	string Map_File_Name;
	GameMap game_map;
	MainObject player;
	Fps fps_timer;

	if (InitData() == false)
	{
		return -1;
	}

	LoadBackground();

	bool off = true;
	bool _off = false;

	bool menu = true;
	bool tutorial = false;
	bool volume = true;
	bool introduce = false;

	bool new_game = false;

	bool level = false;

	double second = 0;

	auto start = std::chrono::steady_clock::now();

	while (menu)
	{
		if (!off)
		{
			Mix_HaltMusic();
		}


		if (!Mix_PlayingMusic() && off)
		{
			Mix_PlayMusic(MenuSound, 0);
		}

		SDL_RenderClear(g_screen);
		if (tutorial)
		{
			Tutorial.Render(g_screen, NULL);

		}
		else
		{
			if (level)
			{
				Level.Render(g_screen, NULL);

			}
			else
			{
				if (introduce)
				{
					Introduce.Render(g_screen, NULL);
				}
				else
				{
					if (!off)
					{
						MenuVolumeOff.Render(g_screen, NULL);
					}
					else
					{
						MenuVolumeOn.Render(g_screen, NULL);
					}
				}
			}
		}
		SDL_RenderPresent(g_screen);
		while (SDL_PollEvent(&g_event))
		{
			switch (g_event.type)
			{
			case SDL_QUIT:
				close();
				return 0;
			case SDL_KEYDOWN:
				switch (g_event.key.keysym.sym)
				{
				case SDLK_x:
				{
					Mix_HaltMusic();
					menu = false;
					start = std::chrono::steady_clock::now();
					ifstream file(Time_Save_File);
					double sec;
					file >> sec;
					second = sec;
					file.close();
					ifstream Mapfile(Map_Save_File);
					Mapfile >> Map_File_Name;
					Mapfile.close();
				}
				break;
				case SDLK_n:
				{
					close();
					return 0;
				}
				case SDLK_t:
				{
					if (!tutorial)
					{
						tutorial = true;
					}
					else
					{
						tutorial = false;
					}
				}
				break;
				case SDLK_o:
				{
					if (off)
					{
						off = false;
					}
					else
					{
						off = true;
					}
					break;
				}
				case SDLK_y:
				{
					if (level)
					{
						level = false;
					}
					else
					{
						level = true;
					}
				}
				break;
				case SDLK_i:
				{
					if (!introduce)
					{
						introduce = true;
					}
					else
					{
						introduce = false;
					}
				}
				break;
				case SDLK_h:
				{
					new_game = true;
					Mix_HaltMusic();
					menu = false;
					start = std::chrono::steady_clock::now();
					Map_File_Name = Map_File_Name1;
					level = false;
				}
				break;
				case SDLK_m:
				{
					new_game = true;
					Mix_HaltMusic();
					menu = false;
					start = std::chrono::steady_clock::now();
					Map_File_Name = Map_File_Name2;
					level = false;
				}
				break;
				case SDLK_e:
				{
					new_game = true;
					Mix_HaltMusic();
					menu = false;
					start = std::chrono::steady_clock::now();
					Map_File_Name = Map_File_Name3;
					level = false;
				}
				break;
				}
			default:
				break;
			}
		}
	}

	bool play = true;
	while (play && !menu && !level)
	{
		ofstream MapSaveF(Map_Save_File);
		MapSaveF << Map_File_Name;
		MapSaveF.close();

		player.LoadImg(Right_File_Name, g_screen);
		player.set_clips();
		player.LoadMix();
		game_map.LoadMap(Map_File_Name);
		game_map.LoadTiles(g_screen);
		Map map_data_ = game_map.getMap();
		map_level = 1;
		camera.x = 0;

		if (!new_game)
		{
			float x_pos1, y_pos1;
			ifstream pos1_file(Save_Position);
			pos1_file >> x_pos1;
			pos1_file >> y_pos1;
			pos1_file.close();
			player.x_pos_set(x_pos1);
			player.y_pos_set(y_pos1);
		}
		else
		{
			float x_pos2, y_pos2;
			ifstream pos2_file(FirstTime_Position);
			pos2_file >> x_pos2;
			pos2_file >> y_pos2;
			pos2_file.close();
			player.x_pos_set(x_pos2);
			player.y_pos_set(y_pos2);
		}

		//text
		TextObject time_game;
		time_game.SetColor(TextObject::WHITE_TEXT);

		TextObject high_score;
		high_score.SetColor(TextObject::WHITE_TEXT);

		TextObject money_count;
		money_count.SetColor(TextObject::WHITE_TEXT);

		bool in_quit = false;
		while (!in_quit)
		{
			fps_timer.start();
			while (SDL_PollEvent(&g_event) != false)
			{
				if (g_event.type == SDL_QUIT)
				{
					in_quit = true;
					play = false;
				}
				if (g_event.type == SDL_KEYDOWN)
				{
					switch (g_event.key.keysym.sym)
					{
					case SDLK_n:
					{
						close();
						return 0;
					}
					break;
					case SDLK_o:
					{
						if (off)
						{
							off = false;
						}
						else
						{
							off = true;
						}
					}
					case SDLK_i:
					{
						if (_off)
						{
							_off = false;
						}
						else
						{
							_off = true;
						}
					}
					}
				}
				player.HandelInputAction(g_event, g_screen);
			}

			player.off(_off);

			SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
			SDL_RenderClear(g_screen);

			player.DoPlayer(map_data_);

			map_level = (player.y_pos_get() + (TILE_SIZE / 2)) / SCREEN_HEIGHT;

			camera.y = map_level * SCREEN_HEIGHT;
			g_background[map_level].Render(g_screen, NULL);

			game_map.DrawMap(g_screen, map_level);

			player.Show(g_screen, camera.y);

			auto end = std::chrono::steady_clock::now();
			auto diff = end - start;

			double seconds = std::chrono::duration<double>(diff).count() / 100000;

			string str_time = "Time: " + to_string(second + seconds);

			ofstream TimeSaveFileout(Time_Save_File);
			TimeSaveFileout << seconds;
			TimeSaveFileout.close();

			time_game.SetText(str_time);
			time_game.LoadFromRenderText(font_time, g_screen);
			time_game.RenderText(g_screen, SCREEN_WIDTH - 200, 15);

			int Prev_High_Score;

			ifstream in(High_Score_Save);
			in >> Prev_High_Score;
			in.close();

			string highScore = "High Score: " + to_string(Prev_High_Score);

			high_score.SetText(highScore);
			high_score.LoadFromRenderText(font_time, g_screen);
			high_score.RenderText(g_screen, 15, 15);

			string moneyCount = "Money: " + to_string(player.getMoney());

			//money_count.SetText(moneyCount);
			//money_count.LoadFromRenderText(font_time, g_screen);
			//money_count.RenderText(g_screen, SCREEN_WIDTH / 2, 15);

			SDL_RenderPresent(g_screen);

			int real_imp_timer = fps_timer.get_tick_();
			int timer_one_frame = 1000 / FRAME_PER_SECOND;
			if (real_imp_timer < timer_one_frame)
			{
				int delay_timer = timer_one_frame - real_imp_timer;
				SDL_Delay(delay_timer);
			}

			if (!off)
			{
				Mix_HaltMusic();
			}

			if (!Mix_PlayingMusic() && off)
			{
				Mix_PlayMusic(InGameSound, 0);
			}

			ofstream file(Save_Position);
			file << player.x_pos_get() << endl;
			file << player.y_pos_get();
			file.close();

			if (Win(player.x_pos_get(), player.y_pos_get()))
			{
				Mix_PlayMusic(WinSound, 0);

				float x_pos, y_pos;
				ifstream infile(FirstTime_Position);
				infile >> x_pos;
				infile >> y_pos;
				infile.close();

				ofstream outfile(Save_Position);
				outfile << x_pos << endl;
				outfile << y_pos;
				outfile.close();

				if (Prev_High_Score < seconds)
				{
					ofstream out(High_Score_Save);
					out << seconds;
					out.close();
				}

				bool play = true;
				while (play)
				{
					if (!off)
					{
						Mix_HaltMusic();
					}

					if (!Mix_PlayingMusic() && off)
					{
						Mix_PlayMusic(WinSound, 0);
					}

					SDL_RenderClear(g_screen);
					Victory.Render(g_screen, NULL);
					SDL_RenderPresent(g_screen);

					while (SDL_PollEvent(&g_event) != false)
					{
						if (g_event.type == SDL_QUIT)
						{
							close();
							return 0;
						}
						if (g_event.type == SDL_KEYDOWN)
						{
							switch (g_event.key.keysym.sym)
							{
							case SDLK_y:
							{
								Mix_HaltMusic();
								play = false;
								in_quit = true;
							}
							break;
							case SDLK_a:
							{
								close();
								return 0;
							}
							break;
							case SDLK_o:
							{
								if (off)
								{
									off = false;
								}
								else
								{
									off = true;
								}
							}
							break;
							}
						}
					}
				}
			}
		}
	}
	close();
	return 0;
}