#include<iostream>
#include<filesystem>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include<io.h>
#include "getfiles.h"
#include "processdata.h"
#include "PcapToCSV.h"



//using namespace std;


/*void getFiles(string path, vector<string>& files)
{
	//文件句柄  
		//文件句柄
	intptr_t hFile = 0;
	//文件信息
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之
			//如果不是,加入列表
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
				//cout << files.back() << endl;
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}

	
}*/


int main() 
{

/*	string DATA_DIR = "F:\\2019-4-10\\CSV";
	vector<string> files;
	getfiles F1;
	processdata P1;
	cout << "azimuth:";
	cin >> P1.azimuth;
	cout << P1.azimuth << endl;

	P1.dataprocess(long(P1.initial_realtime),P1.azimuth,DATA_DIR,files);*/



	//getchar();


	
	/*string DATA_DIR = "D:\\study\\project\\LiDAR_CSV\\2019-4-11\\realtime";
	vector<string> files;
	getfiles F1;
	processdata P1;
	P1.offset(DATA_DIR,files);*/

	/*string DATA_DIR = "D:\\study\\project\\LiDAR_CSV\\2019-4-11\\result";
	vector<string> files;
	getfiles F1;
	processdata P1;
	P1.AddTime(DATA_DIR, files);*/

	/*string DATA_DIR = "D:\\study\\project\\LiDAR_CSV\\realtime";
	vector<string> files;
	getfiles F1;
	processdata P1;
	P1.Frequency(DATA_DIR, files);*/

	/*string DATA_DIR = "D:\\study\\project\\LiDAR_CSV\\offset";
	vector<string> files;
	getfiles F1;
	processdata P1;
	P1.average(DATA_DIR, files);*/



/*	string DATA_DIR = "D:\\study\\project\\LiDAR_CSV\\offset";
	vector<string> files;
	getfiles F1;
	processdata P1;
	P1.highest(DATA_DIR, files);*/


	string DATA_DIR = "D:\\study\\project\\pcaptest";
	PcapToCSV P1;
	P1.dataconvert(const_cast<char *>(DATA_DIR.c_str()));


	
}




