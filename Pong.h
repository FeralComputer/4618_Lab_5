#pragma once
#include "Base4618.h"
#include "Ball.h"
#include "CVObject.h"
#include "PongScore.h"
#include <chrono>
#include <mutex>

class CPong : public CBase4618
{
private:
	std::mutex vectorMutex;
	CPongScore *score;
	std::vector<CCVObject*> objects;
	bool isrunning=true;
	static const int UPS = 34;
	static const int FPS = 34;
	

	static int update_thread(CPong *pong, bool *running);
	static int draw_thread(CPong *pong, bool *running);

public:
	static const int screensize = 900;
	typedef std::chrono::duration<int, std::ratio<1, FPS>> FPS_Duration;
	typedef std::chrono::duration<int, std::ratio<1, UPS>> UPS_Duration;

	CPong();
	~CPong();
	void draw();
	void update();
	void run();

};

