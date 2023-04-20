#ifndef  FPS_H_
#define  FPS_H_


class Fps
{
public:
	Fps();
	~Fps();
	void start();
	int get_tick_();
private:
	int start_tick_;
	int paused_tick_;
	bool is_started_;
	bool is_paused_;
};

#endif