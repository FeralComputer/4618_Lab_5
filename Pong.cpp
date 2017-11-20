#include "stdafx.h"
#include "Pong.h"
#include "Paddle.h"
#include <thread>
#include <chrono> 



int CPong::update_thread(CPong * pong, bool *running)
{
	while (*running)
	{
		pong->update();

	}
	return 0;
}

int CPong::draw_thread(CPong * pong, bool *running)
{
	while (*running)
	{
		pong->draw();
	}
	return 0;
}

CPong::CPong()
{
	*canvas= cv::Mat::zeros(cv::Size(screensize, screensize), CV_8UC3);

	//create ball
	score=new CPongScore(cv::Point(screensize / 2, 0));
	objects.push_back(new CBall(cv::Point(screensize*3 / 4, screensize*3 / 4), cv::Point((rand() % 30 - 15), (rand() % 30 - 15))));
	objects.push_back(new CBall(cv::Point(screensize / 4, screensize / 4), cv::Point((rand() % 30 - 15), (rand() % 30 - 15))));
	objects.push_back(new CBall(cv::Point(screensize / 5, screensize / 4), cv::Point((rand() % 30 - 15), (rand() % 30 - 15))));
	objects.push_back(new CBall(cv::Point(screensize / 6, screensize / 4), cv::Point((rand() % 30 - 15), (rand() % 30 - 15))));
	objects.push_back(new CBall(cv::Point(screensize / 4, screensize / 2), cv::Point((rand() % 30 - 15), (rand() % 30 - 15))));
	objects.push_back(new CBall(cv::Point(screensize / 4, screensize / 3), cv::Point((rand() % 30 - 15), (rand() % 30 - 15))));
	objects.push_back(new CPaddle("COM5",CPaddle::PLAYER_1,cv::Point(screensize-40,screensize/2),cv::Point2f(0,30)));
	//objects.push_back(new CPaddle("COM6", CPaddle::PLAYER_2, cv::Point(40, screensize / 2), cv::Point2f(0, 30)));
}


CPong::~CPong()
{
}

void CPong::draw()
{

	auto time = std::chrono::steady_clock::now();
	auto endtime = time + FPS_Duration(1);
	//clear canvas
	*canvas = cv::Mat::zeros(cv::Size(screensize, screensize), CV_8UC3);

	
	//vectorMutex.lock();
	for (int i = (objects.size()-1); i >=0; i--)
	{
		objects[i]->draw(*canvas);
	}
	//vectorMutex.unlock();
	//must be last
	score->draw(*canvas);

	cv::imshow("Pong", *canvas);
	switch (cv::waitKey(1))
	{
		case 'q':
		case 'Q':
			isrunning = false;
			return;
		default:
			break;
	}
	std::this_thread::sleep_until(endtime);
	auto delta = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - time).count();
	score->setFPS((1000000000.0f) / ((float)delta));
}

void CPong::update()
{
	auto time = std::chrono::steady_clock::now();
	auto endtime = time + UPS_Duration(1);
	//vectorMutex.lock();
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->getObjectType() == CCVObject::SHAPE::BALL)
		{
			cv::Point centerpoint = objects[i]->getCenterPoint();
			int radius = objects[i]->getWidth();
			if (centerpoint.x - radius-objects[i]->getSpeed().x-10 < 0)
			{
				score->incrementPlayer1Score();
				objects[i] = new CBall(cv::Point(screensize / 2, screensize / 2), cv::Point((rand() % 30 - 15), (rand() % 30 - 15)));
			}
			else if(centerpoint.x+radius+ objects[i]->getSpeed().x+5>screensize)
			{
				score->incrementPlayer2Score();
				objects[i] = new CBall(cv::Point(screensize / 2, screensize / 2), cv::Point((rand() % 30 - 15), (rand() % 30 - 15)));
			}
			else
			{
				objects[i]->update(objects);
			}
		}
		else
		{
			objects[i]->update(objects);
		}
		
	}
	//vectorMutex.unlock();
	
	std::this_thread::sleep_until(endtime);
	//must be last
	auto delta = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - time).count();
	score->setUPS((1000000000.0f)/ ((float)delta) );
	score->update(objects);

}

void CPong::run()
{
	std::thread t1(&CPong::update_thread,this,&isrunning);
	std::thread t2(&CPong::draw_thread, this,&isrunning);
	while (isrunning)
	{
		
	}
	t1.join();
	t2.join();
}
