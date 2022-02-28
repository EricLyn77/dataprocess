#pragma once

#define WIN32

#define HAVE_REMOTE
#include<string>
#include<map>
#include<filesystem>
#include<sstream>
#include<io.h>
#include<iostream>
#include<fstream>
#include"getfiles.h"
#include "pcap.h"

static map<unsigned int, double> azimuth_offset_32 = {
	{ 0, 1.4 },{ 1, -4.2 },{ 2, 1.4 },{ 3, -1.4 },{ 4, 1.4 },{ 5, -1.4 },{ 6, 4.2 },{ 7, -1.4 },{ 8, 1.4 },{ 9, -4.2 },{ 10, 1.4 },{ 11, -1.4 },{ 12, 4.2 },{ 13, -1.4 },{ 14, 4.2 },{ 15, -1.4 },
{ 16, 1.4 },{ 17, -4.2 },{ 18, 1.4 },{ 19, -4.2 },{ 20, 4.2 },{ 21, -1.4 },{ 22, 1.4 },{ 23, -1.4 },{ 24, 1.4 },{ 25, -1.4 },{ 26, 1.4 },{ 27, -4.2 },{ 28, 4.2 },{ 29, -1.4 },{ 30, 1.4 },{ 31, -1.4 } };

using namespace std;

class PcapToCSV
{

public:
	void dataconvert(const char * DataDir, int set_azimuth);

	vector<string> files;
};