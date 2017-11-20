#include "stdafx.h"
#include "CVObject.h"


CCVObject::CCVObject()
{
}


CCVObject::~CCVObject()
{
}

void CCVObject::update(std::vector<CCVObject*> objects)
{
}

void CCVObject::draw(cv::Mat & canvas)
{
}

bool CCVObject::isCollision(int xa, int ya, CCVObject object)
{
	return false;
}

int CCVObject::getObjectType()
{
	return objectType;
}

cv::Point CCVObject::getCenterPoint()
{
	return centerpoint;
}

void CCVObject::setSpeed(cv::Point2f speed)
{
}

cv::Point2f CCVObject::getSpeed()
{
	return cv::Point2f();
}

int CCVObject::getWidth()
{
	return 0;
}

int CCVObject::getHeight()
{
	return 0;
}

