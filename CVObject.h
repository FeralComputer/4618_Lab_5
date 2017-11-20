#pragma once
#ifdef _WIN32
#include "opencv.hpp"
#elif linux
#include <opencv2/opencv.hpp>
#endif
class CCVObject
{
protected:
	int objectType = -1;
	cv::Point centerpoint;
public:
	typedef enum {
		BALL,		//if ball type
		PADDLE,		//if paddle type
		TEXT
	}SHAPE;
	CCVObject();
	~CCVObject();
	virtual void update(std::vector<CCVObject*> objects);
	virtual void draw(cv::Mat &canvas);
	virtual bool isCollision(int xa,int ya,CCVObject object);
	int getObjectType();
	virtual cv::Point getCenterPoint();
	virtual void setSpeed(cv::Point2f speed);
	virtual cv::Point2f getSpeed();
	virtual int getWidth();
	virtual int getHeight();
};

