#pragma once

#define WIN32  

#include"pcap.h"
#include<string>
#include <iostream>
#include <map>
#include<utility>
#include "GroundZ.h"
#include<sstream>
#include<filesystem>
#include<io.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define u_int unsigned int
#define u_char unsigned char

using namespace::std;



static double laser_id_to_angle_32[32] = {
	-25,-1,-1.667,-15.639,-11.31,0,-0.667,-8.843,-7.254,0.333,-0.333,-6.148,-5.333,1.333,0.667,-4,-4.667,1.667,1,-3.667,-3.333,3.333,2.333,-2.667,-3,7,4.667,-2.333,-2,15,10.333,-1.333};

static double azimuth_offset_32[32] = {
	1.4,-4.2,1.4,-1.4,1.4,-1.4,4.2,-1.4,1.4,-4.2,1.4,-1.4,4.2,-1.4,4.2,-1.4,1.4,-4.2,1.4,-4.2,4.2,-1.4,1.4,-1.4,1.4,-1.4,1.4,-4.2,4.2,-1.4,1.4,-1.4
};



class DReceiver
{
public:

	groundZ Z1;
	bool hasGroundFile = false;

	void DReceiverStart();
	void pointHigherThanGround(double x, double y, double z);


private:


};