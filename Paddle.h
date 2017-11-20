#pragma once
#include "CVObject.h"
#include "Control.h"
#include "Pong.h"

class CPaddle :public CCVObject
{
private:
	CControl *com;
	bool isOutOfBounds(int ya);
	int playernumber = -1;
	cv::Point centerpoint;
	cv::Point2f speed;
	int width;
	int height;
public:
	static const float deadband;
	typedef enum
	{
		UNDEFINED_PLAYER,
		PLAYER_1,
		PLAYER_2
	}PLAYERS;
	CPaddle(std::string comport,int playernumber, cv::Point centerpoint,cv::Point2f speed,int width=30,int height=CPong::screensize/4);
	~CPaddle();
	void update(std::vector<CCVObject*> objects);
	void draw(cv::Mat &canvas);
	cv::Point getCenterPoint();
	cv::Point2f getSpeed();
	int getWidth();
	int getHeight();
};

