#include "stdafx.h"
#include "Control.h"
#include <iostream>
#include <vector>

#ifdef _WIN32

#include "Packet.h"

bool CControl::sendData(CPacket data)
{
	bool state = true;
	std::string str = data.createString();
	int length = serial->write(str.c_str(),str.length());
	if (length != str.length())
	{
		std::cout << "\n\n\t\tERROR: sentdata did not send entire message\n\n";
		return false;
	}
	return state;
}

bool CControl::receiveData(CPacket &data)
{
	bool startbytefound = false;
	std::string str;

	char c = 0;
	float time = GetTickCount();

	do
	{
		if (serial->read(&c, 1))
		{
			if (GetTickCount() - time > PORTTIMEOUT)
			{
				std::cout << "\n\n\t\tERROR: recievedata timed out\n\n";
				serial->flush();
				return false;
			}
			if (startbytefound)
			{
				str += c;
			}
			else if(c=='$')
			{
				startbytefound = true;
			}
		}
		

	} while (c!='\n');
	data.parseString(str);
	return true;
}


CControl::CControl(std::string comport)
{
	this->comport = comport;
	serial = new Serial();
	if (!serial->open(comport))
	{
		std::cout << "Failed to open port\n";
	}
	//print out controller info
	char c;
	while (serial->read(&c, 1))
	{
		std::cout << c;
	}
	serial->flush();
}

CControl::~CControl()
{
	std::cout << "\t\tERROR: CControl destroyed";
	delete serial;
}

bool CControl::getData(int type, int channel, int & value)
{
	bool state = true;
	serial->flush();
	if (type > SERVO)
	{
		state = false;
		return state;
	}

	//send data
	CPacket sendPacket('G',(char)type,channel);
	state = sendData(sendPacket);
	if (state == false)
	{
		std::cout << "\n\n\t\tERROR: Get data failed to send\n\n";
	}

	//read data
	CPacket receivePacket;
	state = receiveData(receivePacket);

	value = receivePacket.getValue();
	//error checking
	if (receivePacket == sendPacket)
	{
	}
	else
	{
		state = false;
	}
	return state;
}

bool CControl::setData(int type, int channel, int value)
{
	bool state = true;
	serial->flush();
	

	//send data
	CPacket sendPacket('S',type, channel, value);
	state = sendData(sendPacket);
	if (state == false)
	{
		std::cout << "\n\n\t\tERROR: setdata failed to send data\n\n";
	}


	//receive data

	CPacket receivePacket;

	state = receiveData(receivePacket);

	//error checking
	if (receivePacket == sendPacket)
	{
	}
	else
	{
		state = false;
	}
	return state;
	
}

std::string CControl::getComPort()
{
	return comport;
}


//run for pi
#elif linux
#include <pigpio.h>


CControl::CControl(std::string comport)
{
	handle = spiOpen(0, BAUDRATE, 3);
}

CControl::~CControl()
{
	std::cout << "\t\tERROR: CControl destroyed";
	spiClose(handle);
}

bool CControl::getData(int type, int channel, int & value)
{
	bool state = true;
	switch (type)
	{
	case ANALOG:
		value = getValue(handle, channel);
		break;
	case DIGITAL:
		std::cout << "\n\tDIGITAL not done in CControl::getData";
		state = false;
		break;
	case SERVO:
		std::cout << "\n\tSERVO not done in CControl::getData";
		state = false;
	default:
		std::cout << "\n\tdefault case in CControl::getData";
		state = false;
	}
	return state;
}

bool CControl::setData(int type, int channel, int value)
{
	bool state = true;
	state = false;
	std::cout << "\n\tCControl::setData not initialized";
	return state;

}

std::string CControl::getComPort()
{
	return comport;
}
#endif