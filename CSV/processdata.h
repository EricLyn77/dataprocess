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
	unsigned long initial_realtime;
	unsigned long initial_timestamp;
	string DATA_DIR;
    vector<string> files;
	getfiles F1;
	tm initial_time;
	tm t1;
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

	void average(string DATA_DIR, vector<string> &files)
	{
		vector<vector<string>> strArray33;
		vector<vector<string>> Average_t;
		vector<string>Average;
		strArray33.reserve(100000000);
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
			int preframe = 0;
			int n = 0;
			string lineStr;
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
				sum = sum + stod(lineArray[6]);
				if (abs(stoi(lineArray[13]) - preframe) > 9000)
				{
					Average.push_back(to_string(sum / n));
					Average.push_back(lineArray[14]);
					Average_t.push_back(Average);
					sum = 0;
					n = 0;

				}
				preframe = stoi(lineArray[13]);
	//			strArray33.push_back(lineArray);
			}
	
			cout << "cycle done" << endl;
			string pathorigin0 = "D:\\7.14 80degree\\offset\\";
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
		string axx = "D:\\7.14 80degree\\result\\28000.csv";
		vector<vector<string>> strArray32;
		strArray32.reserve(100000000);
		F1.getFiles(DATA_DIR, files);
		string lineStr;
	//	for (size_t i = 0; i < files.size(); i++)
	//	{
			long a = 0;
			ifstream inFileAxx(axx, ios::in);
			//ifstream inFile(files[i], ios::in);
			//cout << "rest:  " << files.size() - i << endl;
			//cout << files[i] << endl;
			vector<string> lineArray;
			lineArray.reserve(100000);
			long double standard;
			int standard_indensity;
			string laser_id;
			string azimuth;
			while(getline(inFileAxx,lineStr))
			//while (getline(inFile, lineStr)) //getline来自sstream
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
				//cout <<lineArray[0]<<endl;
				//system("pause");
				if (stoi(lineArray[0]) == NULL)
				{
					cout << "wrong" << endl;
					continue;
				}
				try
				{
					if (a == 1)
					{

					//	cout << "2" << endl;
						laser_id = lineArray[1];
						azimuth = lineArray[2];
						standard = stod(lineArray[3]);
						standard_indensity = stoi(lineArray[0]);
					//	cout << standard_indensity;
					}
					//			cout << lineArray[3]<<endl;
					//cout << abs(stoi(lineArray[0]) - standard_indensity) << endl;
					if ((abs(stoi(lineArray[0])-standard_indensity)<3)&&(stoi(lineArray[2])==8001))
					{
			//			cout << "1" << endl;
					//	cout << lineArray[3] << endl;
						lineArray[3] = to_string(standard - stod(lineArray[3]));
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
			string pathorigin0 = "D:\\7.14 80degree\\offset\\";
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

	//	}



	}
	void dataprocess(long initial_realtime,int azimuth,string DATA_DIR,vector<string> &files)
	{
		F1.getFiles(DATA_DIR, files);
		clock_t startT, finishT;
		double usedT;
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
	//		string preframe;
		
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


				//string hour;
				//string min;
				//string sec;
			//	cout << typeid(lineArray[5].c_str()).name()<<endl;
				try
				{
					startT = clock();
					if (a > 2)
					{
		/*				if (b > 1)
						{
							if ((lineArray[13] == "0") && (preframe != "0"))
							{
								if ((t1.tm_min >= 0) && (t1.tm_min < 31))
								{
									initial_time.tm_min = 30;
								}
								else
								{
									initial_time.tm_min = 0;
									initial_time.tm_hour++;
									t1.tm_hour = initial_time.tm_hour;
								}

							}
							t1.tm_sec = initial_time.tm_sec + (stoi(lineArray[13]) / 10);
							if (t1.tm_sec > 59)
							{
								t1.tm_min = initial_time.tm_min + (t1.tm_sec / 60);
								t1.tm_sec = t1.tm_sec % 60;
							}

							hour = to_string(t1.tm_hour);
							min = to_string(t1.tm_min);
							sec = to_string(t1.tm_sec);
							lineArray.push_back(hour + ":" + min + ":" + sec);

							//	cout << to_string(t1.tm_hour) << endl;
							if (a == 3)
							{
							//	cout << lineArray[14] << endl;
							//	cout << initial_time.tm_min << endl;
							}
							
						}*/
					//	preframe = lineArray[13];
						if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "0"))
						{
						//	cout << lineArray[2].c_str() << endl;
							strArray0.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "1"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray1.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "2"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray2.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "3"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray3.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "4"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray4.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "5"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray5.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "6"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray6.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "7"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray7.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "8"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray8.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "9"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray9.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "10"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray10.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "11"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray11.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "12"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray12.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "13"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray13.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "14"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray14.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "15"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray15.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "16"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray16.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "17"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray17.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "18"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray18.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "19"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray19.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "20"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray20.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "21"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray21.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "22"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray22.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "23"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray23.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "24"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray24.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "25"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray25.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "26"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray26.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "27"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray27.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "28"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray28.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "29"))
						{
						//	cout << lineArray[2].c_str() << endl;
							strArray29.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "30"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray30.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						if ((azimuth < stol(lineArray[5])) && (stol(lineArray[5]) < azimuth + 10) && (lineArray[4] == "31"))
						{
							//cout << lineArray[2].c_str() << endl;
							strArray31.push_back(lineArray);//每一行vector数据都放到strArray中去
						}
						finishT = clock();
						usedT = double(finishT - startT) / CLOCKS_PER_SEC;
						cout << "time used:" << usedT * 1000000 << endl;
						system("pause");
						
					}
				}
				catch (const std::exception&)
				{
					continue;
				}
				lineArray.clear();

				


			}

		}
	}

};