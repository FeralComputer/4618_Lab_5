#pragma once
#ifdef _WIN32
#include "opencv.hpp"
#elif linux
#include <opencv2/opencv.hpp>
#endif
#include "Pong.h"
#include "CVObject.h"

class CBall:public CCVObject
{
protected:
	cv::Point centerpoint;
	cv::Point2f speed;
	int radius=20;

public:
	CBall();
	CBall(cv::Point centerpoint);
	CBall(cv::Point centerpoint,cv::Point speed);
	~CBall();
	void update(std::vector<CCVObject*> objects);
	void draw(cv::Mat &canvas);
	int getradius();
	cv::Point2f getSpeed();
	cv::Point getCenterPoint();
	bool isCollision(int xa, int ya, CCVObject *object);
	bool isOutOfBounds(int xa, int ya);
	void setSpeed(cv::Point2f speed);
	int getWidth();
	int getHeight();

};

