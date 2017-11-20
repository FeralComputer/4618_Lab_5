#include "stdafx.h"
#include "Ball.h"
#include <math.h>

CBall::CBall()
{
	this->centerpoint = cv::Point(CPong::screensize / 2, CPong::screensize / 2);
	//speed = cv::Point(1, 5);
	objectType = CCVObject::BALL;
}

CBall::CBall(cv::Point centerpoint)
{
	this->centerpoint = centerpoint;
	//speed = cv::Point(5, 10);
	objectType = CCVObject::BALL;
}

CBall::CBall(cv::Point centerpoint, cv::Point speed)
{
	this->centerpoint = centerpoint;
	this->speed = speed;
	objectType = CCVObject::BALL;
}


CBall::~CBall()
{
}

void CBall::update(std::vector<CCVObject*> objects)
{
	//check for collision
	if (isOutOfBounds(speed.x,speed.y))
	{
		//std::cout << "Ball hit bounds\n";
	}
	for (int i = 0; i < objects.size(); i++)
	{
		if (centerpoint != objects[i]->getCenterPoint())
		{
			if (isCollision(speed.x, speed.y, objects[i]))
			{
				//std::cout << "ball collision\n";
			}
		}
		
	}
	centerpoint.x += (int)speed.x;
	centerpoint.y += (int)speed.y;
}

void CBall::draw(cv::Mat &canvas)
{
	cv::circle(canvas,centerpoint,radius,cv::Scalar(255,255,255),-1);
}

int CBall::getradius()
{
	return radius;
}

cv::Point2f CBall::getSpeed()
{
	return speed;
}

cv::Point CBall::getCenterPoint()
{
	return centerpoint;
}

bool CBall::isCollision(int xa, int ya, CCVObject *object)
{
	bool collision = false;
	if (object->getObjectType() == CCVObject::BALL)
	{
		if (objectType == CCVObject::BALL)
		{//ball vs ball collision
			cv::Point point = object->getCenterPoint();
			int dx = (centerpoint.x + xa - point.x);
			int dy = (centerpoint.y + ya - point.y);
			float distance = std::sqrt(dx*dx + dy*dy);
			if (distance < (object->getHeight() + radius))
			{
				//change direction of this object
				collision = true;
				float angle = std::atan2f(dy, dx);
				float speedsqr = std::sqrt(speed.x*speed.x + speed.y*speed.y);
				speed.x = (speedsqr*std::cos(angle));
				speed.y = (speedsqr*std::sin(angle));
				
				//change direction of colliding object
				cv::Point2f objectspeed = object->getSpeed();
				speedsqr = std::sqrt(objectspeed.x*objectspeed.x + objectspeed.y*objectspeed.y);
				objectspeed.x = -(speedsqr*std::cos(angle));
				objectspeed.y = -(speedsqr*std::sin(angle));
				object->setSpeed(objectspeed);
			}
		}
	}
	else if (object->getObjectType() == CCVObject::PADDLE)
	{
		cv::Point point = object->getCenterPoint();
		int dx = (centerpoint.x + xa - point.x);
		int dy = (centerpoint.y + ya - point.y);

		//check corners!!!!
		int objheight = object->getHeight()/2;
		int objwidth = object->getWidth()/2;
		//check along the vertical plane of rectangle
		if (std::abs(dx)<(radius + objwidth ))
		{//invert balls speed in x axis
			if (std::abs(dy) < (objheight+radius))
			{
				if (dx > 0)
				{
					speed.x = std::abs(speed.x);
				}
				else if (dx < 0)
				{
					speed.x = -std::abs(speed.x);
				}
				//speed.x = -speed.x;
			}
		}
		//check along the horizontal plane of rectangle
		else if (std::abs(dy)<(radius + objheight))
		{//invert balls speed in y axis
			if (std::abs(dx) < (objwidth+radius))
			{
				if (dy > 0)
				{
					speed.y = std::abs(speed.y);
				}
				else if (dy < 0)
				{
					speed.y = -std::abs(speed.y);
				}
				//speed.y = -speed.y;
			}
		}
	}
	return collision;
}

bool CBall::isOutOfBounds(int xa, int ya)
{
	bool hitbounds = false;
	if (centerpoint.x+xa - radius < 0)
	{
		speed.x = -speed.x;
		hitbounds = true;
	}
	else if (centerpoint.x+xa + radius > CPong::screensize)
	{
		speed.x = -speed.x;
		hitbounds = true;
	}
	if (centerpoint.y +ya - radius < 0)
	{
		speed.y = -speed.y;
		hitbounds = true;
	}
	else if (centerpoint.y+ya + radius > CPong::screensize)
	{
		speed.y = -speed.y;
		hitbounds = true;
	}
	return hitbounds;
}

void CBall::setSpeed(cv::Point2f speed)
{
	this->speed = speed;
}

int CBall::getWidth()
{
	return radius;
}

int CBall::getHeight()
{
	return radius;
}
