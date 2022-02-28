#include<iostream>
#include<filesystem>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include<io.h>
#include "getfiles.h"
#include "processdata.h"
#include "Dreceiver.h"

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

/*	string DATA_DIR = "F:\\CSV";
	vector<string> files;
	getfiles F1;
	//F1.getFiles(DATA_DIR, files);
	processdata P1;
	cout << "azimuth:";
	cin >> P1.azimuth;
	cout << P1.azimuth << endl;
	P1.dataprocess(int(P1.azimuth),DATA_DIR,files);

	string pathorigin0 = "D:\\study\\project\\LiDAR_CSV\\result\\";
	string pathorigin1 = "D:\\study\\project\\LiDAR_CSV\\result\\";
	string pathorigin2 = "D:\\study\\project\\LiDAR_CSV\\result\\";
	string pathorigin3 = "D:\\study\\project\\LiDAR_CSV\\result\\";
	string pathorigin4 = "D:\\study\\project\\LiDAR_CSV\\result\\";
	string pathorigin5 = "D:\\study\\project\\LiDAR_CSV\\result\\";
	string pathorigin6 = "D:\\study\\project\\LiDAR_CSV\\result\\";
	string pathorigin7 = "D:\\study\\project\\LiDAR_CSV\\result\\";
	string pathorigin8 = "D:\\study\\project\\LiDAR_CSV\\result\\";
	string pathorigin9 = "D:\\study\\project\\LiDAR_CSV\\result\\";
	string pathorigin10 = "D:\\study\\project\\LiDAR_CSV\\result\\";
	string pathorigin11 = "D:\\study\\project\\LiDAR_CSV\\result\\";
	string pathorigin12 = "D:\\study\\project\\LiDAR_CSV\\result\\";
	string pathorigin13 = "D:\\study\\project\\LiDAR_CSV\\result\\";
	string pathorigin14 = "D:\\study\\project\\LiDAR_CSV\\result\\";
	string pathorigin15 = "D:\\study\\project\\LiDAR_CSV\\result\\";
	string pathorigin16 = "D:\\study\\project\\LiDAR_CSV\\result\\";
	string pathorigin17 = "D:\\study\\project\\LiDAR_CSV\\result\\";
	string pathorigin18 = "D:\\study\\project\\LiDAR_CSV\\result\\";
	string pathorigin19= "D:\\study\\project\\LiDAR_CSV\\result\\";
	string pathorigin20 = "D:\\study\\project\\LiDAR_CSV\\result\\";
	string pathorigin21 = "D:\\study\\project\\LiDAR_CSV\\result\\";
	string pathorigin22 = "D:\\study\\project\\LiDAR_CSV\\result\\";
	string pathorigin23 = "D:\\study\\project\\LiDAR_CSV\\result\\";
	string pathorigin24 = "D:\\study\\project\\LiDAR_CSV\\result\\";
	string pathorigin25 = "D:\\study\\project\\LiDAR_CSV\\result\\";
	string pathorigin26 = "D:\\study\\project\\LiDAR_CSV\\result\\";
	string pathorigin27 = "D:\\study\\project\\LiDAR_CSV\\result\\";
	string pathorigin28 = "D:\\study\\project\\LiDAR_CSV\\result\\";
	string pathorigin29 = "D:\\study\\project\\LiDAR_CSV\\result\\";
	string pathorigin30 = "D:\\study\\project\\LiDAR_CSV\\result\\";
	string pathorigin31 = "D:\\study\\project\\LiDAR_CSV\\result\\";

	ofstream out0(pathorigin0.append("0").append(to_string(P1.azimuth)).append(".csv"), ios::app);
	ofstream out1(pathorigin1.append("1").append(to_string(P1.azimuth)).append(".csv"), ios::app);
	ofstream out2(pathorigin2.append("2").append(to_string(P1.azimuth)).append(".csv"), ios::app);
	ofstream out3(pathorigin3.append("3").append(to_string(P1.azimuth)).append(".csv"), ios::app);
	ofstream out4(pathorigin4.append("4").append(to_string(P1.azimuth)).append(".csv"), ios::app);
	ofstream out5(pathorigin5.append("5").append(to_string(P1.azimuth)).append(".csv"), ios::app);
	ofstream out6(pathorigin6.append("6").append(to_string(P1.azimuth)).append(".csv"), ios::app);
	ofstream out7(pathorigin7.append("7").append(to_string(P1.azimuth)).append(".csv"), ios::app);
	ofstream out8(pathorigin8.append("8").append(to_string(P1.azimuth)).append(".csv"), ios::app);
	ofstream out9(pathorigin9.append("9").append(to_string(P1.azimuth)).append(".csv"), ios::app);
	ofstream out10(pathorigin10.append("10").append(to_string(P1.azimuth)).append(".csv"), ios::app);
	ofstream out11(pathorigin11.append("11").append(to_string(P1.azimuth)).append(".csv"), ios::app);
	ofstream out12(pathorigin12.append("12").append(to_string(P1.azimuth)).append(".csv"), ios::app);
	ofstream out13(pathorigin13.append("13").append(to_string(P1.azimuth)).append(".csv"), ios::app);
	ofstream out14(pathorigin14.append("14").append(to_string(P1.azimuth)).append(".csv"), ios::app);
	ofstream out15(pathorigin15.append("15").append(to_string(P1.azimuth)).append(".csv"), ios::app);
	ofstream out16(pathorigin16.append("16").append(to_string(P1.azimuth)).append(".csv"), ios::app);
	ofstream out17(pathorigin17.append("17").append(to_string(P1.azimuth)).append(".csv"), ios::app);
	ofstream out18(pathorigin18.append("18").append(to_string(P1.azimuth)).append(".csv"), ios::app);
	ofstream out19(pathorigin19.append("19").append(to_string(P1.azimuth)).append(".csv"), ios::app);
	ofstream out20(pathorigin20.append("20").append(to_string(P1.azimuth)).append(".csv"), ios::app);
	ofstream out21(pathorigin21.append("21").append(to_string(P1.azimuth)).append(".csv"), ios::app);
	ofstream out22(pathorigin22.append("22").append(to_string(P1.azimuth)).append(".csv"), ios::app);
	ofstream out23(pathorigin23.append("23").append(to_string(P1.azimuth)).append(".csv"), ios::app);
	ofstream out24(pathorigin24.append("24").append(to_string(P1.azimuth)).append(".csv"), ios::app);
	ofstream out25(pathorigin25.append("25").append(to_string(P1.azimuth)).append(".csv"), ios::app);
	ofstream out26(pathorigin26.append("26").append(to_string(P1.azimuth)).append(".csv"), ios::app);
	ofstream out27(pathorigin27.append("27").append(to_string(P1.azimuth)).append(".csv"), ios::app);
	ofstream out28(pathorigin28.append("28").append(to_string(P1.azimuth)).append(".csv"), ios::app);
	ofstream out29(pathorigin29.append("29").append(to_string(P1.azimuth)).append(".csv"), ios::app);
	ofstream out30(pathorigin30.append("30").append(to_string(P1.azimuth)).append(".csv"), ios::app);
	ofstream out31(pathorigin31.append("31").append(to_string(P1.azimuth)).append(".csv"), ios::app);

	string buffer;
	buffer = pathorigin0;

	for (int i = 0; i < P1.strArray0.size(); i++)
	{
		for (int j = 0; j < P1.strArray0[i].size(); j++)
		{
			out0<< P1.strArray0[i][j] << ",";
			
		}
		out0<<endl;
	}
	cout << "laser0 done" << endl;
	for (int i = 0; i < P1.strArray1.size(); i++)
	{
		for (int j = 0; j < P1.strArray1[i].size(); j++)
		{
			out1 << P1.strArray0[i][j] << ",";

		}
		out1 << endl;
	}
	cout << "laser1 done" << endl;
	for (int i = 0; i < P1.strArray2.size(); i++)
	{
		for (int j = 0; j < P1.strArray2[i].size(); j++)
		{
			out2 << P1.strArray2[i][j] << ",";

		}
		out2 << endl;
	}
	cout << "laser2 done" << endl;
	for (int i = 0; i < P1.strArray3.size(); i++)
	{
		for (int j = 0; j < P1.strArray3[i].size(); j++)
		{
			out3 << P1.strArray3[i][j] << ",";

		}
		out3 << endl;
	}
	cout << "laser3 done" << endl;
	for (int i = 0; i < P1.strArray4.size(); i++)
	{
		for (int j = 0; j < P1.strArray4[i].size(); j++)
		{
			out4 << P1.strArray4[i][j] << ",";

		}
		out4 << endl;
	}
	cout << "laser4 done" << endl;
	for (int i = 0; i < P1.strArray5.size(); i++)
	{
		for (int j = 0; j < P1.strArray5[i].size(); j++)
		{
			out5 << P1.strArray5[i][j] << ",";

		}
		out5 << endl;
	}
	cout << "laser5 done" << endl;
	for (int i = 0; i < P1.strArray6.size(); i++)
	{
		for (int j = 0; j < P1.strArray6[i].size(); j++)
		{
			out6 << P1.strArray6[i][j] << ",";

		}
		out6 << endl;

	}
	cout << "laser6 done" << endl;
	for (int i = 0; i < P1.strArray7.size(); i++)
	{
		for (int j = 0; j < P1.strArray7[i].size(); j++)
		{
			out7 << P1.strArray7[i][j] << ",";

		}
		out7 << endl;
	}
	cout << "laser7 done" << endl;
	for (int i = 0; i < P1.strArray8.size(); i++)
	{
		for (int j = 0; j < P1.strArray8[i].size(); j++)
		{
			out8 << P1.strArray8[i][j] << ",";

		}
		out8 << endl;
	}
	cout << "laser8 done" << endl;
	for (int i = 0; i < P1.strArray9.size(); i++)
	{
		for (int j = 0; j < P1.strArray9[i].size(); j++)
		{
			out9 << P1.strArray9[i][j] << ",";

		}
		out9 << endl;
	}
	cout << "laser9 done" << endl;
	for (int i = 0; i < P1.strArray10.size(); i++)
	{
		for (int j = 0; j < P1.strArray10[i].size(); j++)
		{
			out10 << P1.strArray10[i][j] << ",";

		}
		out10 << endl;
	}
	cout << "laser10 done" << endl;
	for (int i = 0; i < P1.strArray11.size(); i++)
	{
		for (int j = 0; j < P1.strArray11[i].size(); j++)
		{
			out11 << P1.strArray11[i][j] << ",";

		}
		out0 << endl;
	}
	cout << "laser11 done" << endl;
	for (int i = 0; i < P1.strArray12.size(); i++)
	{
		for (int j = 0; j < P1.strArray12[i].size(); j++)
		{
			out12 << P1.strArray12[i][j] << ",";

		}
		out12 << endl;
	}
	cout << "laser12 done" << endl;
	for (int i = 0; i < P1.strArray13.size(); i++)
	{
		for (int j = 0; j < P1.strArray13[i].size(); j++)
		{
			out13 << P1.strArray13[i][j] << ",";

		}
		out13 << endl;
	}
	cout << "laser13 done" << endl;
	for (int i = 0; i < P1.strArray14.size(); i++)
	{
		for (int j = 0; j < P1.strArray14[i].size(); j++)
		{
			out14 << P1.strArray14[i][j] << ",";

		}
		out14 << endl;
	}
	cout << "laser14 done" << endl;
	for (int i = 0; i < P1.strArray15.size(); i++)
	{
		for (int j = 0; j < P1.strArray15[i].size(); j++)
		{
			out15 << P1.strArray15[i][j] << ",";

		}
		out15 << endl;
	}
	cout << "laser15 done" << endl;
	for (int i = 0; i < P1.strArray16.size(); i++)
	{
		for (int j = 0; j < P1.strArray16[i].size(); j++)
		{
			out16 << P1.strArray16[i][j] << ",";

		}
		out16 << endl;
	}
	cout << "laser16 done" << endl;
	for (int i = 0; i < P1.strArray17.size(); i++)
	{
		for (int j = 0; j < P1.strArray17[i].size(); j++)
		{
			out17 << P1.strArray17[i][j] << ",";

		}
		out17 << endl;
	}
	cout << "laser17 done" << endl;
	for (int i = 0; i < P1.strArray18.size(); i++)
	{
		for (int j = 0; j < P1.strArray18[i].size(); j++)
		{
			out18 << P1.strArray18[i][j] << ",";

		}
		out18 << endl;
	}
	cout << "laser18 done" << endl;
	for (int i = 0; i < P1.strArray19.size(); i++)
	{
		for (int j = 0; j < P1.strArray19[i].size(); j++)
		{
			out19 << P1.strArray19[i][j] << ",";

		}
		out19 << endl;
	}
	cout << "laser19 done" << endl;
	for (int i = 0; i < P1.strArray20.size(); i++)
	{
		for (int j = 0; j < P1.strArray20[i].size(); j++)
		{
			out20 << P1.strArray20[i][j] << ",";

		}
		out20 << endl;
	}
	cout << "laser20 done" << endl;
	for (int i = 0; i < P1.strArray21.size(); i++)
	{
		for (int j = 0; j < P1.strArray21[i].size(); j++)
		{
			out21 << P1.strArray21[i][j] << ",";

		}
		out21 << endl;
	}
	cout << "laser21 done" << endl;
	for (int i = 0; i < P1.strArray22.size(); i++)
	{
		for (int j = 0; j < P1.strArray22[i].size(); j++)
		{
			out22 << P1.strArray22[i][j] << ",";

		}
		out22 << endl;
	}
	cout << "laser22 done" << endl;
	for (int i = 0; i < P1.strArray23.size(); i++)
	{
		for (int j = 0; j < P1.strArray23[i].size(); j++)
		{
			out23 << P1.strArray23[i][j] << ",";

		}
		out23 << endl;
	}
	cout << "laser23 done" << endl;
	for (int i = 0; i < P1.strArray24.size(); i++)
	{
		for (int j = 0; j < P1.strArray24[i].size(); j++)
		{
			out24 << P1.strArray24[i][j] << ",";

		}
		out24 << endl;
	}
	cout << "laser24 done" << endl;
	for (int i = 0; i < P1.strArray25.size(); i++)
	{
		for (int j = 0; j < P1.strArray25[i].size(); j++)
		{
			out25 << P1.strArray25[i][j] << ",";

		}
		out25 << endl;
	}
	cout << "laser25 done" << endl;
	for (int i = 0; i < P1.strArray26.size(); i++)
	{
		for (int j = 0; j < P1.strArray26[i].size(); j++)
		{
			out26 << P1.strArray26[i][j] << ",";

		}
		out26 << endl;
	}
	cout << "laser26 done" << endl;
	for (int i = 0; i < P1.strArray27.size(); i++)
	{
		for (int j = 0; j < P1.strArray27[i].size(); j++)
		{
			out27 << P1.strArray27[i][j] << ",";

		}
		out27 << endl;
	}
	cout << "laser27 done" << endl;
	for (int i = 0; i < P1.strArray28.size(); i++)
	{
		for (int j = 0; j < P1.strArray28[i].size(); j++)
		{
			out28 << P1.strArray28[i][j] << ",";

		}
		out28 << endl;
	}
	cout << "laser28 done" << endl;
	for (int i = 0; i < P1.strArray29.size(); i++)
	{
		for (int j = 0; j < P1.strArray29[i].size(); j++)
		{
			out29 << P1.strArray29[i][j] << ",";

		}
		out29 << endl;
	}
	cout << "laser29 done" << endl;
	for (int i = 0; i < P1.strArray30.size(); i++)
	{
		for (int j = 0; j < P1.strArray30[i].size(); j++)
		{
			out30 << P1.strArray30[i][j] << ",";

		}
		out30 << endl;
	}
	cout << "laser30 done" << endl;
	for (int i = 0; i < P1.strArray31.size(); i++)
	{
		for (int j = 0; j < P1.strArray31[i].size(); j++)
		{
			out31 << P1.strArray31[i][j] << ",";

		}
		out31 << endl;
	}
	cout << "laser31 done" << endl;

	getchar();*/


	
/*	string DATA_DIR = "D:\\7.14 50degree\\result";
	vector<string> files;
	getfiles F1;
	processdata P1;
	P1.offset(DATA_DIR,files);*/
DReceiver D1;
D1.hasGroundFile = false;
D1.DReceiverStart();

}




