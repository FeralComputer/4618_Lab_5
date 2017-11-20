#include "stdafx.h"
#include "PongScore.h"




CPongScore::CPongScore(cv::Point centerpoint)
{
	this->centerpoint = centerpoint;
	this->objectType = CCVObject::PADDLE;
}

CPongScore::~CPongScore()
{
}

void CPongScore::setFPS(float fps)
{
	this->fps = fps;
}

void CPongScore::setUPS(float ups)
{
	this->ups = ups;
}

void CPongScore::incrementPlayer1Score()
{
	player1score++;
}

void CPongScore::incrementPlayer2Score()
{
	player2score++;
}

void CPongScore::update(std::vector<CCVObject*> objects)
{

}

void CPongScore::draw(cv::Mat & canvas)
{
	int baseline = 0;
	std::string score = std::to_string(player2score) + " - " + std::to_string(player1score);
	cv::Size size=cv::getTextSize(score,cv::FONT_HERSHEY_COMPLEX,1,3,&baseline);
	cv::Point textOrg((CPong::screensize - size.width) / 2,(size.height)*2);

	putText(canvas, score, textOrg, cv::FONT_HERSHEY_COMPLEX, 1,cv::Scalar::all(255),3, 8);

	std::string speedinfo = "FPS: " + std::to_string(fps) + "  UPS: " + std::to_string(ups);
	size = cv::getTextSize(speedinfo, cv::FONT_HERSHEY_COMPLEX, 0.5f, 1, &baseline);
	cv::Point testOrg((CPong::screensize - size.width) / 2, (size.height) * 2+50);

	putText(canvas, speedinfo, testOrg, cv::FONT_HERSHEY_COMPLEX, 0.5f,cv::Scalar::all(255), 1, 8);
}
