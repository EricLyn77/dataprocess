#pragma once
#include<string>
#include<vector>
#include<iostream>
#include<filesystem>
#include<fstream>
#include<sstream>
#include<io.h>
#include "getfiles.h"

using namespace std;


class processdata
{
public:
	//string laser_id;
	int azimuth;
	string DATA_DIR;
    vector<string> files;
	getfiles F1;
	vector<vector<string>> strArray0;
	vector<vector<string>> strArray1;
	vector<vector<string>> strArray2;
	vector<vector<string>> strArray3;
	vector<vector<string>> strArray4;
	vector<vector<string>> strArray5;
	vector<vector<string>> strArray6;
	vector<vector<string>> strArray7;
	vector<vector<string>> strArray8;
	vector<vector<string>> strArray9;
	vector<vector<string>> strArray10;
	vector<vector<string>> strArray11;
	vector<vector<string>> strArray12;
	vector<vector<string>> strArray13;
	vector<vector<string>> strArray14;
	vector<vector<string>> strArray15;
	vector<vector<string>> strArray16;
	vector<vector<string>> strArray17;
	vector<vector<string>> strArray18;
	vector<vector<string>> strArray19;
	vector<vector<string>> strArray20;
	vector<vector<string>> strArray21;
	vector<vector<string>> strArray22;
	vector<vector<string>> strArray23;
	vector<vector<string>> strArray24;
	vector<vector<string>> strArray25;
	vector<vector<string>> strArray26;
	vector<vector<string>> strArray27;
	vector<vector<string>> strArray28;
	vector<vector<string>> strArray29;
	vector<vector<string>> strArray30;
	vector<vector<string>> strArray31;

	void caculateRate(string filePath, vector<string> &files);

	void offset(string DATA_DIR, vector<string> &files)
	{
		vector<vector<string>> strArray32;
		strArray32.reserve(10000000);
		F1.getFiles(DATA_DIR, files);
		string lineStr;
		for (int i = 0; i < files.size(); i++)
		{
			long a = 0;
			ifstream inFile(files[i], ios::in);
			cout << "rest:  " << files.size() - i << endl;
			cout << files[i] << endl;
			vector<string> lineArray;
			long double standard;
			long double pre;
			long double last;
			string laser_id;
			string azimuth;
			while (getline(inFile, lineStr)) //getline来自sstream
			{
				a++;
				//打印整行字符串
			//	cout<<lineStr<<endl;
				//存成二维表结构
				stringstream ss(lineStr);//来自sstream
				string str;
			
				vector<string> lineArray;
				lineArray.reserve(1000);
				while (getline(ss, str, ','))
					lineArray.push_back(str);//一行数据以vector保存
				try
				{
					if (a == 1)
					{

						//cout << "2" << endl;
						laser_id = lineArray[1];
						azimuth = lineArray[2];
						standard = stold(lineArray[3]);
					}
					//			cout << lineArray[3]<<endl;
					
					if ((labs(stold(lineArray[3]) - pre) < 2)&&(labs(stold(lineArray[3]) - last) < 2))
					{
						//cout << "1" << endl;
						
						lineArray[3] = to_string(standard - stold(lineArray[3]));
						//			cout << lineArray[3] << endl;
						strArray32.push_back(lineArray);

					}

					
					if ((a % 20 )== 0)
					{
						last = pre;
						pre = stold(lineArray[3]);
						
					}
				}
				catch (const std::exception&)
				{
					cout << "1" << endl;
					//continue;
					
				}

			}
			cout << "cycle done" << endl;
			string pathorigin0 = "D:\\7.14 50degree\\offset";
			ofstream out0(pathorigin0.append(to_string(i)).append("offset").append(".csv"));
			for (int i = 0; i < strArray32.size(); i++)
			{
				for (int j = 0; j < strArray32[i].size(); j++)
				{
					out0 << strArray32[i][j] << ",";

				}
				out0 << endl;
			}
			cout << "laser:" << laser_id << "done" << endl;
			strArray32.clear();

		}



	}
	void dataprocess(int azimuth,string DATA_DIR,vector<string> &files)
	{
		F1.getFiles(DATA_DIR, files);
		string lineStr;
		strArray0.reserve(10000000);
		strArray1.reserve(10000000);
		strArray2.reserve(10000000);
		strArray3.reserve(10000000);
		strArray4.reserve(10000000);
		strArray5.reserve(10000000);
		strArray6.reserve(10000000);
		strArray7.reserve(10000000);
		strArray8.reserve(10000000);
		strArray9.reserve(10000000);
		strArray10.reserve(10000000);
		strArray11.reserve(10000000);
		strArray12.reserve(10000000);
		strArray13.reserve(10000000);
		strArray14.reserve(10000000);
		strArray15.reserve(10000000);
		strArray16.reserve(10000000);
		strArray17.reserve(10000000);
		strArray18.reserve(10000000);
		strArray19.reserve(10000000);
		strArray20.reserve(10000000);
		strArray21.reserve(10000000);
		strArray22.reserve(10000000);
		strArray23.reserve(10000000);
		strArray24.reserve(10000000);
		strArray25.reserve(10000000);
		strArray26.reserve(10000000);
		strArray27.reserve(10000000);
		strArray28.reserve(10000000);
		strArray29.reserve(10000000);
		strArray30.reserve(10000000);
		strArray31.reserve(10000000);
		//	for (int i = 0; i <2; i++)
		for (int i = 0; i < files.size(); i++)
		{
			long a = 0;
			ifstream inFile(files[i], ios::in);
			cout << "rest:  " << files.size() - i << endl;
			cout << files[i] << endl;
			vector<string> lineArray;
			lineArray.reserve(1000);
			while (getline(inFile, lineStr)) //getline来自sstream
			{
				a++;
				//打印整行字符串
		//		cout<<lineStr<<endl;
				//存成二维表结构
				stringstream ss(lineStr);//来自sstream
				string str;
				//按照逗号分隔
				while (getline(ss, str, ','))
					lineArray.push_back(str);//一行数据以vector保存
			//	cout << typeid(lineArray[5].c_str()).name()<<endl;
				if (a > 2)
				{
					if ((azimuth < stol(lineArray[2])) && (stol(lineArray[2]) < azimuth + 10) && (lineArray[1] == "0"))
					{
						//cout << lineArray[2].c_str() << endl;
						strArray0.push_back(lineArray);//每一行vector数据都放到strArray中去
					}
					if ((azimuth < stol(lineArray[2])) && (stol(lineArray[2]) < azimuth + 10) && (lineArray[1] == "1"))
					{
						//cout << lineArray[2].c_str() << endl;
						strArray1.push_back(lineArray);//每一行vector数据都放到strArray中去
					}
					if ((azimuth < stol(lineArray[2])) && (stol(lineArray[2]) < azimuth + 10) && (lineArray[1] == "2"))
					{
						//cout << lineArray[2].c_str() << endl;
						strArray2.push_back(lineArray);//每一行vector数据都放到strArray中去
					}
					if ((azimuth < stol(lineArray[2])) && (stol(lineArray[2]) < azimuth + 10) && (lineArray[1] == "3"))
					{
						//cout << lineArray[2].c_str() << endl;
						strArray3.push_back(lineArray);//每一行vector数据都放到strArray中去
					}
					if ((azimuth < stol(lineArray[2])) && (stol(lineArray[2]) < azimuth + 10) && (lineArray[1] == "4"))
					{
						//cout << lineArray[2].c_str() << endl;
						strArray4.push_back(lineArray);//每一行vector数据都放到strArray中去
					}
					if ((azimuth < stol(lineArray[2])) && (stol(lineArray[2]) < azimuth + 10) && (lineArray[1] == "5"))
					{
						//cout << lineArray[2].c_str() << endl;
						strArray5.push_back(lineArray);//每一行vector数据都放到strArray中去
					}
					if ((azimuth < stol(lineArray[2])) && (stol(lineArray[2]) < azimuth + 10) && (lineArray[1] == "6"))
					{
						//cout << lineArray[2].c_str() << endl;
						strArray6.push_back(lineArray);//每一行vector数据都放到strArray中去
					}
					if ((azimuth < stol(lineArray[2])) && (stol(lineArray[2]) < azimuth + 10) && (lineArray[1] == "7"))
					{
						//cout << lineArray[2].c_str() << endl;
						strArray7.push_back(lineArray);//每一行vector数据都放到strArray中去
					}
					if ((azimuth < stol(lineArray[2])) && (stol(lineArray[2]) < azimuth + 10) && (lineArray[1] == "8"))
					{
						//cout << lineArray[2].c_str() << endl;
						strArray8.push_back(lineArray);//每一行vector数据都放到strArray中去
					}
					if ((azimuth < stol(lineArray[2])) && (stol(lineArray[2]) < azimuth + 10) && (lineArray[1] == "9"))
					{
						//cout << lineArray[2].c_str() << endl;
						strArray9.push_back(lineArray);//每一行vector数据都放到strArray中去
					}
					if ((azimuth < stol(lineArray[2])) && (stol(lineArray[2]) < azimuth + 10) && (lineArray[1] == "10"))
					{
						//cout << lineArray[2].c_str() << endl;
						strArray10.push_back(lineArray);//每一行vector数据都放到strArray中去
					}
					if ((azimuth < stol(lineArray[2])) && (stol(lineArray[2]) < azimuth + 10) && (lineArray[1] == "11"))
					{
						//cout << lineArray[2].c_str() << endl;
						strArray11.push_back(lineArray);//每一行vector数据都放到strArray中去
					}
					if ((azimuth < stol(lineArray[2])) && (stol(lineArray[2]) < azimuth + 10) && (lineArray[1] == "12"))
					{
						//cout << lineArray[2].c_str() << endl;
						strArray12.push_back(lineArray);//每一行vector数据都放到strArray中去
					}
					if ((azimuth < stol(lineArray[2])) && (stol(lineArray[2]) < azimuth + 10) && (lineArray[1] == "13"))
					{
						//cout << lineArray[2].c_str() << endl;
						strArray13.push_back(lineArray);//每一行vector数据都放到strArray中去
					}
					if ((azimuth < stol(lineArray[2])) && (stol(lineArray[2]) < azimuth + 10) && (lineArray[1] == "14"))
					{
						//cout << lineArray[2].c_str() << endl;
						strArray14.push_back(lineArray);//每一行vector数据都放到strArray中去
					}
					if ((azimuth < stol(lineArray[2])) && (stol(lineArray[2]) < azimuth + 10) && (lineArray[1] == "15"))
					{
						//cout << lineArray[2].c_str() << endl;
						strArray15.push_back(lineArray);//每一行vector数据都放到strArray中去
					}
					if ((azimuth < stol(lineArray[2])) && (stol(lineArray[2]) < azimuth + 10) && (lineArray[1] == "16"))
					{
						//cout << lineArray[2].c_str() << endl;
						strArray16.push_back(lineArray);//每一行vector数据都放到strArray中去
					}
					if ((azimuth < stol(lineArray[2])) && (stol(lineArray[2]) < azimuth + 10) && (lineArray[1] == "17"))
					{
						//cout << lineArray[2].c_str() << endl;
						strArray17.push_back(lineArray);//每一行vector数据都放到strArray中去
					}
					if ((azimuth < stol(lineArray[2])) && (stol(lineArray[2]) < azimuth + 10) && (lineArray[1] == "18"))
					{
						//cout << lineArray[2].c_str() << endl;
						strArray18.push_back(lineArray);//每一行vector数据都放到strArray中去
					}
					if ((azimuth < stol(lineArray[2])) && (stol(lineArray[2]) < azimuth + 10) && (lineArray[1] == "19"))
					{
						//cout << lineArray[2].c_str() << endl;
						strArray19.push_back(lineArray);//每一行vector数据都放到strArray中去
					}
					if ((azimuth < stol(lineArray[2])) && (stol(lineArray[2]) < azimuth + 10) && (lineArray[1] == "20"))
					{
						//cout << lineArray[2].c_str() << endl;
						strArray20.push_back(lineArray);//每一行vector数据都放到strArray中去
					}
					if ((azimuth < stol(lineArray[2])) && (stol(lineArray[2]) < azimuth + 10) && (lineArray[1] == "21"))
					{
						//cout << lineArray[2].c_str() << endl;
						strArray21.push_back(lineArray);//每一行vector数据都放到strArray中去
					}
					if ((azimuth < stol(lineArray[2])) && (stol(lineArray[2]) < azimuth + 10) && (lineArray[1] == "22"))
					{
						//cout << lineArray[2].c_str() << endl;
						strArray22.push_back(lineArray);//每一行vector数据都放到strArray中去
					}
					if ((azimuth < stol(lineArray[2])) && (stol(lineArray[2]) < azimuth + 10) && (lineArray[1] == "23"))
					{
						//cout << lineArray[2].c_str() << endl;
						strArray23.push_back(lineArray);//每一行vector数据都放到strArray中去
					}
					if ((azimuth < stol(lineArray[2])) && (stol(lineArray[2]) < azimuth + 10) && (lineArray[1] == "24"))
					{
						//cout << lineArray[2].c_str() << endl;
						strArray24.push_back(lineArray);//每一行vector数据都放到strArray中去
					}
					if ((azimuth < stol(lineArray[2])) && (stol(lineArray[2]) < azimuth + 10) && (lineArray[1] == "25"))
					{
						//cout << lineArray[2].c_str() << endl;
						strArray25.push_back(lineArray);//每一行vector数据都放到strArray中去
					}
					if ((azimuth < stol(lineArray[2])) && (stol(lineArray[2]) < azimuth + 10) && (lineArray[1] == "26"))
					{
						//cout << lineArray[2].c_str() << endl;
						strArray26.push_back(lineArray);//每一行vector数据都放到strArray中去
					}
					if ((azimuth < stol(lineArray[2])) && (stol(lineArray[2]) < azimuth + 10) && (lineArray[1] == "27"))
					{
						//cout << lineArray[2].c_str() << endl;
						strArray27.push_back(lineArray);//每一行vector数据都放到strArray中去
					}
					if ((azimuth < stol(lineArray[2])) && (stol(lineArray[2]) < azimuth + 10) && (lineArray[1] == "28"))
					{
						//cout << lineArray[2].c_str() << endl;
						strArray28.push_back(lineArray);//每一行vector数据都放到strArray中去
					}
					if ((azimuth < stol(lineArray[2])) && (stol(lineArray[2]) < azimuth + 10) && (lineArray[1] == "29"))
					{
						cout << lineArray[2].c_str() << endl;
						strArray29.push_back(lineArray);//每一行vector数据都放到strArray中去
					}
					if ((azimuth < stol(lineArray[2])) && (stol(lineArray[2]) < azimuth + 10) && (lineArray[1] == "30"))
					{
						//cout << lineArray[2].c_str() << endl;
						strArray30.push_back(lineArray);//每一行vector数据都放到strArray中去
					}
					if ((azimuth < stol(lineArray[2])) && (stol(lineArray[2]) < azimuth + 10) && (lineArray[1] == "31"))
					{
						//cout << lineArray[2].c_str() << endl;
						strArray31.push_back(lineArray);//每一行vector数据都放到strArray中去
					}

				}

			}
		}
	}

};