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
	string azimuth;
	unsigned long initial_realtime;
	unsigned long initial_timestamp;
	string DATA_DIR;
    vector<string> files;
	getfiles F1;
	tm initial_time;
	tm t1;
	int hourindex[44] = { 0,0,1,1,10,10,11,11,12,12,13,13,14,14,15,15,16,16,17,17,18,18,19,19,2,2,20,20,21,21,3,3,4,4,5,5,6,6,7,7,8,8,9,9 };
	int minindex[44] = {0,30,0,30,0,30,0,30,0,30,0,30,0,30,0,30,0,30,0,30,0,30,0,30,0,30,0,30,0,30,0,30,0,30,0,30,0,30,0,30,0,30,0,30 };


	void average(string DATA_DIR, vector<string> &files)
	{
		vector<vector<string>> strArray33;
		vector<vector<string>> Average_t;
		strArray33.reserve(10000000);
		F1.getFiles(DATA_DIR, files);
		for (size_t i = 0; i < files.size(); i++)
		{
			long a = 0;
		//	ifstream inFileAxx(axx, ios::in);
			ifstream inFile(files[i], ios::in);
			cout << "rest:  " << files.size() - i << endl;
			cout << files[i] << endl;
			vector<string> lineArray;
			lineArray.reserve(100000);
			long double standard;
			int standard_indensity;
			string laser_id;
			string azimuth;
			double sum = 0;
			double averagevalue;
			string preframe = "45";
			int n = 0;
			string lineStr;
			t1.tm_hour = initial_time.tm_hour;
			t1.tm_min = initial_time.tm_min;
			t1.tm_sec = initial_time.tm_sec;
		//	while (getline(inFileAxx, lineStr))
			while (getline(inFile, lineStr)) //getline来自sstream
			{
				a++;
				//打印整行字符串
			//	cout<<lineStr<<endl;
				//存成二维表结构
				stringstream ss(lineStr);//来自sstream
				string str;
				vector<string> lineArray;

		//		cout << "3" << endl;
				while (getline(ss, str, ','))
					lineArray.push_back(str);//一行数据以vector保存
				vector<string>Average;
				laser_id = lineArray[4];
				sum = sum + stod(lineArray[6]);
				n++;
				if (lineArray[14] != preframe)
				{
					/*t1.tm_min = t1.tm_min + 30;
					if ((t1.tm_min >= 0) && (t1.tm_min < 31))
					{
						t1.tm_min = 30;
					}
					else
					{
						t1.tm_min = 0;
						t1.tm_hour++;
					}*/
					t1.tm_hour = hourindex[stoi(lineArray[14])];
					t1.tm_min = minindex[stoi(lineArray[14])];
					Average.push_back(to_string(sum / n));
					Average.push_back(to_string(t1.tm_hour)+":"+to_string(t1.tm_min)+";"+to_string(t1.tm_sec));
					Average_t.push_back(Average);
					sum = 0;
					n = 0;

				}
				preframe = lineArray[14];
	//			strArray33.push_back(lineArray);
			}
	
			cout << "cycle done" << endl;
			string pathorigin0 = "D:\\study\\project\\LiDAR_CSV\\average\\";
			ofstream out0(pathorigin0.append(laser_id).append("average").append(".csv"));
			for (int i = 0; i < Average_t.size(); i++)
			{
				for (int j = 0; j < Average_t[i].size(); j++)
				{
					out0 << Average_t[i][j] << ",";
	
				}
				out0 << endl;
			}
			cout << "laser:" << laser_id << "done" << endl;
			Average_t.clear();
	
		}
	}

	void offset(string DATA_DIR, vector<string> &files)
	{
	//	string axx = "D:\\7.14 80degree\\result\\28000.csv";
		vector<vector<string>> strArray32;
		strArray32.reserve(10000000);
		F1.getFiles(DATA_DIR, files);
		string lineStr;
		int b = 0;
		for (size_t i = 0; i < files.size(); i++)
		{
			b++;
			long a = 0;
	//		ifstream inFileAxx(axx, ios::in);
			ifstream inFile(files[i], ios::in);
			cout << "rest:  " << files.size() - i << endl;
			cout << files[i] << endl;
			vector<string> lineArray;
			lineArray.reserve(10000);
			long double standard;
			int standard_indensity=0;
			string laser_id;
			string azimuth;
			string preframe="0";
			t1.tm_hour = initial_time.tm_hour;
			t1.tm_min = initial_time.tm_min;
			t1.tm_sec = initial_time.tm_sec;
			//while(getline(inFileAxx,lineStr))
			while (getline(inFile, lineStr)) //getline来自sstream
			{
				a++;
				//打印整行字符串
			//	cout<<lineStr<<endl;
				//存成二维表结构
				stringstream ss(lineStr);//来自sstream
				string str;
				vector<string> lineArray;
				
				
				while (getline(ss, str, ','))
					lineArray.push_back(str);//一行数据以vector保存
				string hour;
				string min;
				string sec;
				try
				{
					if (stoi(lineArray[0]) == NULL)
					{
						cout << "wrong" << endl;
						continue;
					}
					if (a == 1)
					{
						initial_time.tm_min = 0;
					}
/*				if (lineArray[14]!=preframe)
				{

					if ((t1.tm_min >= 0) && (t1.tm_min < 31))
					{
						initial_time.tm_min = 30;
					}
					else
					{
						initial_time.tm_min = 0;
						t1.tm_hour ++;
					}

				}*/
				t1.tm_hour = hourindex[stoi(lineArray[14])];
				t1.tm_min = minindex[stoi(lineArray[14])];
				t1.tm_sec = initial_time.tm_sec + (stoi(lineArray[13]) / 10);
				if (t1.tm_sec > 59)
				{
					t1.tm_min = t1.tm_min + (t1.tm_sec / 60);
					t1.tm_sec = t1.tm_sec % 60;
				}

				hour = to_string(t1.tm_hour);
				min = to_string(t1.tm_min);
				sec = to_string(t1.tm_sec);
				lineArray.push_back(hour + ":" + min + ":" + sec);

							//	cout << to_string(t1.tm_hour) << endl;

						
						
				preframe = lineArray[14];
				//cout <<lineArray[0]<<endl;
				//system("pause");


					if (a == 1)
					{

					//	cout << "2" << endl;
						laser_id = lineArray[4];
						azimuth = lineArray[5];
						standard = stod(lineArray[6]);
						standard_indensity = stoi(lineArray[3]);
					//	cout << standard_indensity;
					}
					//			cout << lineArray[3]<<endl;
					//cout << abs(stoi(lineArray[0]) - standard_indensity) << endl;
					if (abs(stoi(lineArray[3])-standard_indensity)<3)
					{
			//			cout << "1" << endl;
					//	cout << lineArray[3] << endl;
						lineArray[6] = to_string(standard - stod(lineArray[6]));
					//	cout << lineArray[3] << endl;
						strArray32.push_back(lineArray);
					//	lineArray.clear();
					//	cout << a << endl;

					}
				}
				catch (const std::exception&)
				{
					//cout << "1" << endl;
					//continue;
					
				}

			}
			cout << "cycle done" << endl;
			string pathorigin0 = "D:\\study\\project\\LiDAR_CSV\\\offset\\";
			ofstream out0(pathorigin0.append(laser_id).append("offset").append(".csv"));
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
	void dataprocess(long initial_realtime,string azimuth,string DATA_DIR,vector<string> &files)
	{
		F1.getFiles(DATA_DIR, files);
		clock_t startT, finishT;
		double usedT;
		string lineStr;
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
		long b = 0;
		long realtime;
		vector<string> lineArray;
		lineArray.reserve(2000);
//		for (int i = 0; i <20; i++)
		for (int i = 0; i < files.size(); i++)
		{

			b++;
			unsigned long a = 0;
			ifstream inFile(files[i], ios::in);
			cout << "rest:  " << files.size() - i << endl;
			cout << files[i] << endl;
	//		vector<string> lineArray;

		
			while (getline(inFile, lineStr)) //getline来自sstream
			{
				
				a++;
				//打印整行字符串
		//		cout<<lineStr<<endl;
				//存成二维表结构
				stringstream ss(lineStr);//来自sstream
				string str;
				vector<string> lineArray;
	//			lineArray.reserve(2000);
				//按照逗号分隔
				while (getline(ss, str, ','))
					lineArray.push_back(str);//一行数据以vector保存



			//	cout << typeid(lineArray[5].c_str()).name()<<endl;
				try
				{
					//startT = clock();
					if (a > 2)
					{

						if((azimuth==lineArray[5])&&(lineArray[4]=="0"))						
					//	if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "0"))
						{
						//	cout << lineArray[2].c_str() << endl;
							strArray0.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth == lineArray[5]) && (lineArray[4] == "1"))
					//	if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "1"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray1.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth == lineArray[5]) && (lineArray[4] == "2"))
					//	if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "2"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray2.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth == lineArray[5]) && (lineArray[4] == "3"))
					//	if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "3"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray3.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth == lineArray[5]) && (lineArray[4] == "4"))
					//	if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "4"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray4.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth == lineArray[5]) && (lineArray[4] == "5"))
					//	if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "5"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray5.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth == lineArray[5]) && (lineArray[4] == "6"))
					//	if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "6"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray6.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth == lineArray[5]) && (lineArray[4] == "7"))
					//	if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "7"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray7.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth == lineArray[5]) && (lineArray[4] == "8"))
					//	if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "8"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray8.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth == lineArray[5]) && (lineArray[4] == "9"))
					//	if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "9"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray9.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth == lineArray[5]) && (lineArray[4] == "10"))
					//	if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "10"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray10.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth == lineArray[5]) && (lineArray[4] == "11"))
					//	if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "11"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray11.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth == lineArray[5]) && (lineArray[4] == "12"))
					//	if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "12"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray12.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth == lineArray[5]) && (lineArray[4] == "13"))
					//	if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "13"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray13.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth == lineArray[5]) && (lineArray[4] == "14"))
					//	if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "14"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray14.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth == lineArray[5]) && (lineArray[4] == "15"))
					//	if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "15"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray15.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth == lineArray[5]) && (lineArray[4] == "16"))
					//	if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "16"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray16.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth == lineArray[5]) && (lineArray[4] == "17"))
					//	if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "17"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray17.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth == lineArray[5]) && (lineArray[4] == "18"))
					//	if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "18"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray18.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth == lineArray[5]) && (lineArray[4] == "19"))
					//	if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "19"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray19.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth == lineArray[5]) && (lineArray[4] == "20"))
					//	if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "20"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray20.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth == lineArray[5]) && (lineArray[4] == "21"))
					//	if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "21"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray21.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth == lineArray[5]) && (lineArray[4] == "22"))
					//	if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "22"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray22.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth == lineArray[5]) && (lineArray[4] == "23"))
					//	if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "23"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray23.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth == lineArray[5]) && (lineArray[4] == "24"))
					//	if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "24"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray24.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth == lineArray[5]) && (lineArray[4] == "25"))
					//	if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "25"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray25.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth == lineArray[5]) && (lineArray[4] == "26"))
					//	if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "26"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray26.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth == lineArray[5]) && (lineArray[4] == "27"))
					//	if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "27"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray27.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth == lineArray[5]) && (lineArray[4] == "28"))
					//	if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "28"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray28.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth == lineArray[5]) && (lineArray[4] == "29"))
					//	if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "29"))
						{
						//	cout << lineArray[2].c_str() << endl;
							strArray29.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth == lineArray[5]) && (lineArray[4] == "30"))
					//	if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "30"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray30.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth == lineArray[5]) && (lineArray[4] == "31"))
					//	if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "31"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray31.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
					//	finishT = clock();
					//	usedT = double(finishT - startT) / CLOCKS_PER_SEC;
					//	cout << "time used:" << usedT * 1000000 << endl;
					//	system("pause");
						
					}
				}
				catch (const std::exception&)
				{
					continue;
				}
				lineArray.clear();

				


			}
			string pathorigin0 = "E:\\datashift\\result\\";
			string pathorigin1 = "E:\\datashift\\result\\";
			string pathorigin2 = "E:\\datashift\\result\\";
			string pathorigin3 = "E:\\datashift\\result\\";
			string pathorigin4 = "E:\\datashift\\result\\";
			string pathorigin5 = "E:\\datashift\\result\\";
			string pathorigin6 = "E:\\datashift\\result\\";
			string pathorigin7 = "E:\\datashift\\result\\";
			string pathorigin8 = "E:\\datashift\\result\\";
			string pathorigin9 = "E:\\datashift\\result\\";
			string pathorigin10 = "E:\\datashift\\result\\";
			string pathorigin11 = "E:\\datashift\\result\\";
			string pathorigin12 = "E:\\datashift\\result\\";
			string pathorigin13 = "E:\\datashift\\result\\";
			string pathorigin14 = "E:\\datashift\\result\\";
			string pathorigin15 = "E:\\datashift\\result\\";
			string pathorigin16 = "E:\\datashift\\result\\";
			string pathorigin17 = "E:\\datashift\\result\\";
			string pathorigin18 = "E:\\datashift\\result\\";
			string pathorigin19 = "E:\\datashift\\result\\";
			string pathorigin20 = "E:\\datashift\\result\\";
			string pathorigin21 = "E:\\datashift\\result\\";
			string pathorigin22 = "E:\\datashift\\result\\";
			string pathorigin23 = "E:\\datashift\\result\\";
			string pathorigin24 = "E:\\datashift\\result\\";
			string pathorigin25 = "E:\\datashift\\result\\";
			string pathorigin26 = "E:\\datashift\\result\\";
			string pathorigin27 = "E:\\datashift\\result\\";
			string pathorigin28 = "E:\\datashift\\result\\";
			string pathorigin29 = "E:\\datashift\\result\\";
			string pathorigin30 = "E:\\datashift\\result\\";
			string pathorigin31 = "E:\\datashift\\result\\";

			ofstream out0(pathorigin0.append("0").append(azimuth).append(".csv"), ios::app);
			ofstream out1(pathorigin1.append("1").append(azimuth).append(".csv"), ios::app);
			ofstream out2(pathorigin2.append("2").append(azimuth).append(".csv"), ios::app);
			ofstream out3(pathorigin3.append("3").append(azimuth).append(".csv"), ios::app);
			ofstream out4(pathorigin4.append("4").append(azimuth).append(".csv"), ios::app);
			ofstream out5(pathorigin5.append("5").append(azimuth).append(".csv"), ios::app);
			ofstream out6(pathorigin6.append("6").append(azimuth).append(".csv"), ios::app);
			ofstream out7(pathorigin7.append("7").append(azimuth).append(".csv"), ios::app);
			ofstream out8(pathorigin8.append("8").append(azimuth).append(".csv"), ios::app);
			ofstream out9(pathorigin9.append("9").append(azimuth).append(".csv"), ios::app);
			ofstream out10(pathorigin10.append("10").append(azimuth).append(".csv"), ios::app);
			ofstream out11(pathorigin11.append("11").append(azimuth).append(".csv"), ios::app);
			ofstream out12(pathorigin12.append("12").append(azimuth).append(".csv"), ios::app);
			ofstream out13(pathorigin13.append("13").append(azimuth).append(".csv"), ios::app);
			ofstream out14(pathorigin14.append("14").append(azimuth).append(".csv"), ios::app);
			ofstream out15(pathorigin15.append("15").append(azimuth).append(".csv"), ios::app);
			ofstream out16(pathorigin16.append("16").append(azimuth).append(".csv"), ios::app);
			ofstream out17(pathorigin17.append("17").append(azimuth).append(".csv"), ios::app);
			ofstream out18(pathorigin18.append("18").append(azimuth).append(".csv"), ios::app);
			ofstream out19(pathorigin19.append("19").append(azimuth).append(".csv"), ios::app);
			ofstream out20(pathorigin20.append("20").append(azimuth).append(".csv"), ios::app);
			ofstream out21(pathorigin21.append("21").append(azimuth).append(".csv"), ios::app);
			ofstream out22(pathorigin22.append("22").append(azimuth).append(".csv"), ios::app);
			ofstream out23(pathorigin23.append("23").append(azimuth).append(".csv"), ios::app);
			ofstream out24(pathorigin24.append("24").append(azimuth).append(".csv"), ios::app);
			ofstream out25(pathorigin25.append("25").append(azimuth).append(".csv"), ios::app);
			ofstream out26(pathorigin26.append("26").append(azimuth).append(".csv"), ios::app);
			ofstream out27(pathorigin27.append("27").append(azimuth).append(".csv"), ios::app);
			ofstream out28(pathorigin28.append("28").append(azimuth).append(".csv"), ios::app);
			ofstream out29(pathorigin29.append("29").append(azimuth).append(".csv"), ios::app);
			ofstream out30(pathorigin30.append("30").append(azimuth).append(".csv"), ios::app);
			ofstream out31(pathorigin31.append("31").append(azimuth).append(".csv"), ios::app);

			string buffer;
			buffer = pathorigin0;

			for (int i = 0; i < strArray0.size(); i++)
			{
				for (int j = 0; j < strArray0[i].size(); j++)
				{
					out0 << strArray0[i][j] << ",";

				}
				out0 << endl;
			}
			cout << "laser0 done" << endl;
			for (int i = 0; i < strArray1.size(); i++)
			{
				for (int j = 0; j < strArray1[i].size(); j++)
				{
					out1 << strArray0[i][j] << ",";

				}
				out1 << endl;
			}
			cout << "laser1 done" << endl;
			for (int i = 0; i < strArray2.size(); i++)
			{
				for (int j = 0; j < strArray2[i].size(); j++)
				{
					out2 << strArray2[i][j] << ",";

				}
				out2 << endl;
			}
			cout << "laser2 done" << endl;
			for (int i = 0; i < strArray3.size(); i++)
			{
				for (int j = 0; j < strArray3[i].size(); j++)
				{
					out3 <<strArray3[i][j] << ",";

				}
				out3 << endl;
			}
			cout << "laser3 done" << endl;
			for (int i = 0; i < strArray4.size(); i++)
			{
				for (int j = 0; j < strArray4[i].size(); j++)
				{
					out4 << strArray4[i][j] << ",";

				}
				out4 << endl;
			}
			cout << "laser4 done" << endl;
			for (int i = 0; i < strArray5.size(); i++)
			{
				for (int j = 0; j < strArray5[i].size(); j++)
				{
					out5 << strArray5[i][j] << ",";

				}
				out5 << endl;
			}
			cout << "laser5 done" << endl;
			for (int i = 0; i < strArray6.size(); i++)
			{
				for (int j = 0; j < strArray6[i].size(); j++)
				{
					out6 << strArray6[i][j] << ",";

				}
				out6 << endl;

			}
			cout << "laser6 done" << endl;
			for (int i = 0; i < strArray7.size(); i++)
			{
				for (int j = 0; j < strArray7[i].size(); j++)
				{
					out7 << strArray7[i][j] << ",";

				}
				out7 << endl;
			}
			cout << "laser7 done" << endl;
			for (int i = 0; i < strArray8.size(); i++)
			{
				for (int j = 0; j < strArray8[i].size(); j++)
				{
					out8 << strArray8[i][j] << ",";

				}
				out8 << endl;
			}
			cout << "laser8 done" << endl;
			for (int i = 0; i < strArray9.size(); i++)
			{
				for (int j = 0; j < strArray9[i].size(); j++)
				{
					out9 << strArray9[i][j] << ",";

				}
				out9 << endl;
			}
			cout << "laser9 done" << endl;
			for (int i = 0; i < strArray10.size(); i++)
			{
				for (int j = 0; j < strArray10[i].size(); j++)
				{
					out10 << strArray10[i][j] << ",";

				}
				out10 << endl;
			}
			cout << "laser10 done" << endl;
			for (int i = 0; i < strArray11.size(); i++)
			{
				for (int j = 0; j < strArray11[i].size(); j++)
				{
					out11 << strArray11[i][j] << ",";

				}
				out0 << endl;
			}
			cout << "laser11 done" << endl;
			for (int i = 0; i < strArray12.size(); i++)
			{
				for (int j = 0; j < strArray12[i].size(); j++)
				{
					out12 << strArray12[i][j] << ",";

				}
				out12 << endl;
			}
			cout << "laser12 done" << endl;
			for (int i = 0; i < strArray13.size(); i++)
			{
				for (int j = 0; j < strArray13[i].size(); j++)
				{
					out13 << strArray13[i][j] << ",";

				}
				out13 << endl;
			}
			cout << "laser13 done" << endl;
			for (int i = 0; i < strArray14.size(); i++)
			{
				for (int j = 0; j < strArray14[i].size(); j++)
				{
					out14 << strArray14[i][j] << ",";

				}
				out14 << endl;
			}
			cout << "laser14 done" << endl;
			for (int i = 0; i < strArray15.size(); i++)
			{
				for (int j = 0; j < strArray15[i].size(); j++)
				{
					out15 << strArray15[i][j] << ",";

				}
				out15 << endl;
			}
			cout << "laser15 done" << endl;
			for (int i = 0; i < strArray16.size(); i++)
			{
				for (int j = 0; j < strArray16[i].size(); j++)
				{
					out16 << strArray16[i][j] << ",";

				}
				out16 << endl;
			}
			cout << "laser16 done" << endl;
			for (int i = 0; i < strArray17.size(); i++)
			{
				for (int j = 0; j < strArray17[i].size(); j++)
				{
					out17 << strArray17[i][j] << ",";

				}
				out17 << endl;
			}
			cout << "laser17 done" << endl;
			for (int i = 0; i < strArray18.size(); i++)
			{
				for (int j = 0; j < strArray18[i].size(); j++)
				{
					out18 << strArray18[i][j] << ",";

				}
				out18 << endl;
			}
			cout << "laser18 done" << endl;
			for (int i = 0; i < strArray19.size(); i++)
			{
				for (int j = 0; j < strArray19[i].size(); j++)
				{
					out19 << strArray19[i][j] << ",";

				}
				out19 << endl;
			}
			cout << "laser19 done" << endl;
			for (int i = 0; i < strArray20.size(); i++)
			{
				for (int j = 0; j < strArray20[i].size(); j++)
				{
					out20 << strArray20[i][j] << ",";

				}
				out20 << endl;
			}
			cout << "laser20 done" << endl;
			for (int i = 0; i < strArray21.size(); i++)
			{
				for (int j = 0; j < strArray21[i].size(); j++)
				{
					out21 << strArray21[i][j] << ",";

				}
				out21 << endl;
			}
			cout << "laser21 done" << endl;
			for (int i = 0; i < strArray22.size(); i++)
			{
				for (int j = 0; j < strArray22[i].size(); j++)
				{
					out22 << strArray22[i][j] << ",";

				}
				out22 << endl;
			}
			cout << "laser22 done" << endl;
			for (int i = 0; i < strArray23.size(); i++)
			{
				for (int j = 0; j < strArray23[i].size(); j++)
				{
					out23 << strArray23[i][j] << ",";

				}
				out23 << endl;
			}
			cout << "laser23 done" << endl;
			for (int i = 0; i < strArray24.size(); i++)
			{
				for (int j = 0; j < strArray24[i].size(); j++)
				{
					out24 << strArray24[i][j] << ",";

				}
				out24 << endl;
			}
			cout << "laser24 done" << endl;
			for (int i = 0; i < strArray25.size(); i++)
			{
				for (int j = 0; j < strArray25[i].size(); j++)
				{
					out25 << strArray25[i][j] << ",";

				}
				out25 << endl;
			}
			cout << "laser25 done" << endl;
			for (int i = 0; i < strArray26.size(); i++)
			{
				for (int j = 0; j < strArray26[i].size(); j++)
				{
					out26 << strArray26[i][j] << ",";

				}
				out26 << endl;
			}
			cout << "laser26 done" << endl;
			for (int i = 0; i < strArray27.size(); i++)
			{
				for (int j = 0; j < strArray27[i].size(); j++)
				{
					out27 << strArray27[i][j] << ",";

				}
				out27 << endl;
			}
			cout << "laser27 done" << endl;
			for (int i = 0; i < strArray28.size(); i++)
			{
				for (int j = 0; j < strArray28[i].size(); j++)
				{
					out28 << strArray28[i][j] << ",";

				}
				out28 << endl;
			}
			cout << "laser28 done" << endl;
			for (int i = 0; i < strArray29.size(); i++)
			{
				for (int j = 0; j < strArray29[i].size(); j++)
				{
					out29 << strArray29[i][j] << ",";

				}
				out29 << endl;
			}
			cout << "laser29 done" << endl;
			for (int i = 0; i < strArray30.size(); i++)
			{
				for (int j = 0; j < strArray30[i].size(); j++)
				{
					out30 << strArray30[i][j] << ",";

				}
				out30 << endl;
			}
			cout << "laser30 done" << endl;
			for (int i = 0; i < strArray31.size(); i++)
			{
				for (int j = 0; j < strArray31[i].size(); j++)
				{
					out31 << strArray31[i][j] << ",";

				}
				out31 << endl;
			}
			cout << "laser31 done" << endl;
			strArray0.clear();
			strArray1.clear();
			strArray2.clear();
			strArray3.clear();
			strArray4.clear();
			strArray5.clear();
			strArray6.clear();
			strArray7.clear();
			strArray8.clear();
			strArray9.clear();
			strArray10.clear();
			strArray11.clear();
			strArray12.clear();
			strArray13.clear();
			strArray14.clear();
			strArray15.clear();
			strArray16.clear();
			strArray17.clear();
			strArray18.clear();
			strArray19.clear();
			strArray20.clear();
			strArray21.clear();
			strArray22.clear();
			strArray23.clear();
			strArray24.clear();
			strArray25.clear();
			strArray26.clear();
			strArray27.clear();
			strArray28.clear();
			strArray29.clear();
			strArray30.clear();
			strArray31.clear();
		}
	}

};