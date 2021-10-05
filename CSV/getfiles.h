#pragma once
#include<string>
#include<vector>
#include<iostream>
#include<filesystem>
#include<fstream>
#include<sstream>
#include<io.h>



using namespace::std;

class getfiles
{
public:

//	string path;
//	string path;

	void getFiles(string path, vector<string>& files)
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
		//cout << files[0] << endl;
	}
};
