#pragma once
#include "CVObject.h"
#include "Pong.h"
class CPongScore :
	public CCVObject
{
private:
	int player1score = 0;
	int player2score = 0;
	float fps = 0;
	float ups = 0;
	cv::Point centerpoint;

public:
	CPongScore(cv::Point centerpoint);
	~CPongScore();
	void setFPS(float fps);
	void setUPS(float ups);
	void incrementPlayer1Score();
	void incrementPlayer2Score();
	void update(std::vector<CCVObject*> objects);
	void draw(cv::Mat &canvas);
};

