#include "stdafx.h"
#include "Paddle.h"

const float CPaddle::deadband = 0.01f;

bool CPaddle::isOutOfBounds(int ya)
{
	bool hitbounds = false;
	if (centerpoint.y + ya-height/2 < 0)
	{
		hitbounds = true;
	}
	else if (centerpoint.y + ya+ height/2 > CPong::screensize)
	{
		hitbounds = true;
	}
	return hitbounds;
}

CPaddle::CPaddle(std::string comport,int playernumber, cv::Point centerpoint, cv::Point2f speed, int width, int height)
{
	com = new CControl(comport);
	this->playernumber = playernumber;
	this->centerpoint = centerpoint;
	this->speed = speed;
	this->height = height;
	this->width = width;
	this->objectType = CCVObject::PADDLE;
}

CPaddle::~CPaddle()
{
	delete com;
}

void CPaddle::update(std::vector<CCVObject*> objects)
{
	int value=0;
#ifdef _WIN32
	com->getData(CControl::ANALOG, CControl::ANALOG_PORTS::JOYSTICK_Y_RAW, value);
	//proportional speed control
	float ya = -((float)(value - (CControl::ADCRESOLUTION / 2)) / (float)CControl::ADCRESOLUTION);

	if (std::abs(ya) < deadband)
	{
		return;
}
	ya *= speed.y;
	if (!isOutOfBounds(ya))
	{
		//move
		centerpoint.y += ya;
	}
	else
	{//move paddle to min or max distance
		if ((ya > deadband) & (centerpoint.y + speed.y + height / 2>CPong::screensize))
		{
			centerpoint.y = CPong::screensize - height / 2;
		}
		else if ((ya < -deadband)&(centerpoint.y - speed.y - height / 2<0))
		{
			centerpoint.y = height / 2;
		}
	}
#elif linux
	com->getData(CControl::ANALOG,playernumber-1, value);
	//absolute speed control
	float ya = 1.0f-((float)value)/((float)CControl::ADCRESOLUTION);
	ya *= (float)CPong::screensize;
	if (!isOutOfBounds(ya))
	{
		//move
		centerpoint.y += ya;
	}
#endif
	//std::cout << "ADC output for player 1: " << ya << "\n";
	
}

void CPaddle::draw(cv::Mat &canvas)
{
	cv::rectangle(canvas, cv::Rect(centerpoint.x-width/2, centerpoint.y-height/2, width, height), cv::Scalar(255, 255, 255), cv::LineTypes::FILLED);
}

cv::Point CPaddle::getCenterPoint()
{
	return centerpoint;
}

cv::Point2f CPaddle::getSpeed()
{
	return speed;
}

int CPaddle::getWidth()
{
	return width;
}

int CPaddle::getHeight()
{
	return height;
}
