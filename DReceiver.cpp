
#include "DReceiver.h"
#include"GroundZ.h"




using namespace::std;

void DReceiver::DReceiverStart()
{
	pcap_t *fp;
	pcap_dumper_t *ffp = NULL;
	pcap_t *p = NULL;
	//char* dev = NULL;
	//pcap_if_t *alldevs, *ads;
	char errbuf[PCAP_ERRBUF_SIZE];
	//char source[PCAP_BUF_SIZE];
	struct bpf_program bp;
/*	char filter_exp[] = "port 2368 or port 8308";

	for (int i = 0; i < dstPort.length(); i++)
	{
		filter_exp[i + 5] = dstPort[i];
	}

	for (int i = 0; i < gpsPort.length(); i++)
	{
		filter_exp[i + 18] = gpsPort[i];
	}*/

	Z1.arrayFlow.resize(24000);
	Z1.arrayFlow.reserve(10000000);

	bpf_u_int32 mask, net;
	pcap_pkthdr *header = 0;
	const u_char *pkt_data = 0;
	//u_int i = 0;
	int res = 0;
	int packet = 1;
	int c = 0;


	int laser_id = 0;
	double rotating_Angle_rate = 0;
	u_char *pkt_temp_data;
	int pointIndex = 0;
	int count = 0;
	int fra = 0;
	int tempIndex1 = 0;
	int mod1 = 0;
	int frameIndex = 0;

	pair<double, double>point;
	//frameIndex++;
	double temp_azimuth = 0;
	long int interp_timestamp = 0;
	int azimuth = 0;
	//double rotating_Angle_rate = 0;
	double angle = 0;
	double azimuth_offset = 0;
	int Single_Dual = 0;

	double interp_azimuth = 0;
	int mod = -1;
	//BasicInfo::Point* newData = new Point;
	//Frame* frameData = new Frame;

	unsigned int packetCount = 0;//data packet
								 //unsigned int positionCount = 0;//position packet
	/*if (hasGroundFile == false)
	{
		string GroundFile = "F:\\wildhorse\\ground1.csv";
		fstream groundfile(GroundFile);
		string groundstring;
		for (int i = 0; i < 120; i++)
		{
			//getline(groundFile, groundstring,',');
		
			//Area1->vectorGround.push_back(stod(groundstring));
		
			for (int j = 0; j < 200; j++)
			{
				//Area1->groundZvalue[i][j] = groundstring[j];
				getline(groundfile, groundstring, ',');
				//cout << groundstring;
				//system("pause");
				Z1.groundZvalue[i][j] = stof(groundstring);
				//cout << "x: " << j << " y: " << i << " value: " << Z1.groundZvalue[i][j] << endl;
			}
		}
	}*/
	string GroundFile = "realground.csv";
	fstream groundfile(GroundFile);
	string groundstring;
	//getline(groundfile, groundstring, '\n');
	for (int i = 0; i < 120; i++)
	{
		//getline(groundFile, groundstring,',');
		//cout << groundstring;
		//Area1->vectorGround.push_back(stod(groundstring));
		//system("pause");
		for (int j = 0; j < 200; j++)
		{
			//Area1->groundZvalue[i][j] = groundstring[j];
			getline(groundfile, groundstring,',');
			cout << groundstring<<endl;
			Z1.groundZvalue[i][j] = stof(groundstring);
			cout << "x: " << j << " y: " << i << " value: " << Z1.groundZvalue[i][j] << endl;
		}
		getline(groundfile, groundstring, '\n');
		//system("pause");
	}
	ofstream out00("ground6.csv", ios::ate | ios::out);
	ofstream out01("ground7.csv", ios::ate | ios::out);
	string directory = "G:/";
	string filename = "2022-5-26-2-30-0.pcap";
	string fileNameIn = directory + filename;
	string outputFilename(fileNameIn);
	const char* infilenameC = outputFilename.c_str();// "E:/GREENVALLEY/2019-6-25-7-0-0.pcap";
	if ((fp = pcap_open_offline(infilenameC, errbuf)) == NULL)
	{
		printf("unable");
		throw errbuf;
	}

	pcap_setbuff(fp, 256 * 1024 * 1024);
	//pcap_setuserbuffer(fp, 1 * 1024 * 1024 * 1024);

	int nt = 0;
	int tempint = 0;
	while ((res = pcap_next_ex(fp, &header, &pkt_data)) >= 0)
	{
		//int pointIndex = 0;
		//int count = 0;

		unsigned char currentAzimuth_byte_0 = 0x00;
		unsigned char currentAzimuth_byte_1 = 0x00;

		int dataCount = 0;
		int dataBlock = 1;
		tempIndex1 = 0;
		laser_id = 0;

		int tempIndex[1248] = { 0 };

		if (header->caplen == 554)//position packet
		{
			//pcap_dump((u_char *)fp2, header, pkt_data);
		}
		else//data packet
		{
			auto timestamp = ((pkt_data[1245] << 24) | (pkt_data[1244] << 16) | (pkt_data[1243] << 8) | (pkt_data[1242]));

			//printf("%x\n", pkt_data[1246]);
			//printf("%x\n", pkt_data[1247]);
			//CM = Channel_Mode(1);
			if (frameIndex < 1)
			{


				//	system("PAUSE");
				//cout << timestamp << endl;
				auto sazm = ((pkt_data[145] << 8) | (pkt_data[144]));
				auto eazm = ((pkt_data[245] << 8) | (pkt_data[244]));

				if (eazm < sazm)
				{
					eazm += 36000;
				}
				rotating_Angle_rate = (eazm - sazm) / (55.296);
			}

			for (unsigned int i = 42; i < header->caplen; i++)
			{
				//	qDebug() << "laserid:" << laser_id;
					//if (packet>300*166)
				{
					if (i > 42 && i < 1242)
					{
						int val = (i - 42) % 100;
						if (i > 42 && val == 0)
						{
							dataBlock++;
						}

						//pkt_temp_data1[i] = 0x00;

						Single_Dual = 1;
						if (Single_Dual == 1)
						{
							switch (val)
							{
							case 2:
								currentAzimuth_byte_0 = pkt_data[i];
								break;
							case 3:
								currentAzimuth_byte_1 = pkt_data[i];

								break;
							}
							if (laser_id == 32)
							{
								laser_id = 0;
								tempIndex1++;
								//dataBlockCount++;
							}

							if (dataCount == 32)
							{
								dataCount = 0;
								//tempIndex1 = 0;
							}




							if (val < 100 && val>3)
							{

								//switch (val - (3 * dataCount))
								if (((val - (3 * dataCount)) == 6))
								{
									//if (pkt_data[i] != 0x00)
									{

										auto azimuth = ((currentAzimuth_byte_1 << 8) | (currentAzimuth_byte_0));

										auto i_distance = ((pkt_data[i - 1] << 8) | (pkt_data[i - 2]));
										double distance;
										int tem1 = 0;
										interp_timestamp = timestamp + round(55.296*(dataBlock - 1) + 2.304*static_cast<int>(laser_id / 2));//timestamp of each point
										interp_azimuth = ceil(azimuth + ((2.304*static_cast<int>(laser_id / 2))*rotating_Angle_rate));//azimuth of each point
										angle = laser_id_to_angle_32[laser_id];
										azimuth_offset = azimuth_offset_32[laser_id];
										distance = (i_distance * 4.0) / 1000.0;

										if (interp_azimuth > 36000)
										{
											interp_azimuth = interp_azimuth - 36000;
										}


										double PX = distance * cos((M_PI * angle) / 180.0) * sin(M_PI * (interp_azimuth + azimuth_offset * 100) / (100.0* 180.0));
										double PY = distance * cos((M_PI * angle) / 180.0) * cos(M_PI * (interp_azimuth + azimuth_offset * 100) / (100.0* 180.0));
										double PZ = distance * sin((M_PI * angle) / 180.0);
										//cout << "x" << PX << "Y" << PY << "z" << PZ << endl;
										//cout << "distance" << distance<<endl;


										if (interp_azimuth < temp_azimuth)
										{
											//time(&ti);
											//localtime_s(&local, &ti);
											//if (local.tm_hour == 2 && local.tm_min == 59 && local.tm_sec == 59)
											{

												//sleep(1);
												//emit sendPackets(0);
												//break;
												//emit returnResult(-1);
												//return;
											}


											//std:unique_lock<std::mutex> lock(P_FrameData_mutex);



												//qDebug() << "SendOrNot:" << SendOrNot << endl;

												//if (SendOrNot)
											{
												//if (frameData.Points_Frame.size()>0)
												{
													//writeCSV_frame(&frameData);
													//qDebug() << frameData.Points_Frame.size() << endl;
													//m_mutex3.lock();
													//emit sendPackets(1);
													//emit sendPackets(frameIndex+1);
													//frameIndex_DP = frameIndex + 1;
													//DP_Started = true;
													/*if (P_FrameData.Points_Frame.size() > 0)
													{
														qDebug() << "frameIndex:" << P_FrameData.Points_Frame[0].GetFrameIndex();
													}*/

													//emit sendControl(frameIndex + 1);
													//m_mutex3.unlock();

													//sleep(0.001);
													//emit sendControl(frameIndex + 1);
													//DP_Buffer.wakeAll();
													//m_mutex3.lock();
													//qDebug("m_mutex3.lock()");
													//DR_Buffer.wait(&m_mutex3);
													//m_mutex3.unlock();

													//qDebug() << "frameIndex:" << frameIndex << endl;
													//Control_P(0);
													//qDebug() << "frameIndex:" << frameIndex << endl;
													nt++;

												}



											}
											//

											//qDebug() << "frameIndex:" << endl;				

											frameIndex++;
											pointIndex = 0;
											cout << frameIndex<<endl;
											if (hasGroundFile == false)
											{
												if (frameIndex == 400)
												{
													for (int i = 0; i < 120; i++)
													{
														for (int j = 0; j < 200; j++)
														{
															if (Z1.groundZvalue[i][j] != 200)
															{
																Z1.aroundValue[i][j] = -300;
															}

															
														}

													}
													for (int i = 0; i < 120; i++)
													{
														for (int j = 0; j < 200; j++)
														{
															if (Z1.percentile_95(Z1.arrayFlow[i * 200 + j]) == 400)
															{
																/*if(Z1.groundZvalue[i][j] == -50)
																{
																	float aroundvalue = 0;
																	int k = 1;
																	while (aroundvalue == 0)
																	{
																		for (int a = 0; a < (4 * k - 4); a++)
																		{
																			if (Z1.groundZvalue[i - (a / k)][j - (k / 2) + (a%k)] != 200 && Z1.groundZvalue[i - (a / k)][j - (k / 2) + (a%k)] != -50)
																			{
																				aroundvalue = Z1.groundZvalue[i - (a / k)][j - (k / 2) + (a%k)];
																			}
																		}
																		k+=2;
																	}
																}*/
															}
															else if(Z1.groundZvalue[i][j] != 200)
															{
																Z1.groundZvalue[i][j] = Z1.percentile_95(Z1.arrayFlow[i * 200 + j]);
															}
															
															vector<float>().swap(Z1.arrayFlow[i + j]);
															cout << setw(2) << Z1.groundZvalue[i][j] << "   ";
															out00 << Z1.groundZvalue[i][j] << ",";
															//cout << setprecision(4) << Z1->groundZvalue[i][j] <<",";
														}

														out00 << endl;
														cout.setf(ios::internal);
														cout << endl;


													}
													//int a = 1;
													//while (a != 0)
													//{
														//a = 0;
														for (int i = 0; i < 120; i++)
														{
															for (int j = 0; j < 200; j++)
															{
																if (Z1.groundZvalue[i][j] == -50)
																{
																	//a++;
																	int k = 1;
																	while (Z1.aroundValue[i][j] == -300)
																	{
																		for (int a = 0; a <= (k*k); a++)
																		{
																			//cout << "x: " << j - (k / 2) + (a%k) << " y: " << i + (k / 2) - (a / k) << endl;
																			if ((i + (k/2) - (a / k)) >= 0 && (i + (k/2)- (a / k)) < 120 && (j - (k / 2) + (a%k)) >= 0 && (j - (k / 2) + (a%k)) < 200)
																			{
																				//cout << "tx: " << (j - (k / 2) + (a%k)) << "  ty: " << (i + k / 2 - (a / k)) << endl;
																				if ((Z1.groundZvalue[i +(k/2) - (a / k)][j - (k / 2) + (a%k)] != 200) && (Z1.groundZvalue[i + (k/2) - (a / k)][j - (k / 2) + (a%k)] != -50))
																				{
																					Z1.aroundValue[i][j] = Z1.groundZvalue[i + (k/2) - (a / k)][j - (k / 2) + (a%k)];
																					//Z1.groundZvalue[i][j] = aroundvalue;
																					//cout << "x: " << j - (k / 2) + (a%k) << " y: " << i + (k / 2) - (a / k) << endl;
																					break;
																				}
																			}
																		}
																		k = k + 2;
																	//	cout << "k:" << k << endl;
																	}
																}
																cout <<"y: "<< i << "  x: "<<j<<endl;
															}
															
														}

														for (int i = 0; i < 120; i++)
														{
															for (int j = 0; j < 200; j++)
															{
																if(Z1.groundZvalue[i][j] == -50)
																	Z1.groundZvalue[i][j] = Z1.aroundValue[i][j];
															}
														}
														cout << "finish";
													//}

													for (int i = 0; i < 120; i++)
													{
														for (int j = 0; j < 200; j++)
														{
															out01 << Z1.groundZvalue[i][j] << ",";
															cout << setw(2) << Z1.groundZvalue[i][j] << "   ";
														}
														out01 << endl;
													}

													system("pause");
													cout << endl;
													/*for (int i = 0; i < 12; i++)
													{
														for (int j = 0; j < 20; j++)
														{

															cout << setw(8) << Z1->highestZx[i][j] << "   ";
														}
														cout.setf(ios::internal);
														cout << endl;

													}
													cout << endl;
													for (int i = 0; i < 12; i++)
													{
														for (int j = 0; j < 20; j++)
														{

															cout << setw(8) << Z1->highestZy[i][j] << "   ";
														}
														cout.setf(ios::internal);
														cout << endl;

													}*/

												}
											}
											if (hasGroundFile == true)
											{
												for (int i = 0; i < 12; i++)
												{
													for (int j = 0; j < 20; j++)
													{
														cout << setw(8) << Z1.higherPointNum[i][j];														
														//cout << setprecision(4) << Z1->groundZvalue[i][j] <<",";
													}

													cout << endl;


												}
												system("pause");
												cout << endl;
											}

											memset(Z1.higherPointNum,0,sizeof(Z1.higherPointNum));

											//LogTrigger("3", "frameIndex", frameIndex, "run");


											//time(&ti1);
										//	if (frameIndex > 5325 && frameIndex < 5340)
										//	{
										//		qDebug() << ti1 << ":" << ti << "tempint:" << (ti1 - ti) << endl;
											//	system("PAUSE");
											//}
											//time(&ti);
											//if (local.tm_min % 30 == 0 && local.tm_sec == 0&&frameIndex>10)
											//{
												//frameIndex = 0;
												//frameTrigger = 0;
											//}

											//qDebug() << "frameIndex:" << frameIndex << endl;
											//sleep(0.01);

											//qDebug()  << "SendOrNot11:"  << endl;
											//int hh = 0;													
											//while (true)
											//{
												//m_mutex3.lock();
												//if (SendOrNot)
												//{
											//	break;
												//}
												//m_mutex3.unlock();																														
												//sleep(0.1);
											//}
											//qDebug() << frameIndex_DP << "SendOrNot222:"  << endl;


										}



										temp_azimuth = interp_azimuth;
										if (hasGroundFile == false)
										{
											Z1.highestZ(PX, PY, PZ);
										}
										else if (hasGroundFile == true)
										{
											pointHigherThanGround(PX, PY, PZ);
										}


									}
									
									laser_id++;
									dataCount++;

								}
							}
						}
					}
				}
			}

		}
	}
}

void DReceiver::pointHigherThanGround(double x, double y, double z)
{
	if (hasGroundFile = true)
	{
		int xIndex = (x + 100) / 10;
		int yIndex = 11 - ((y + 40) / 10);
		if (xIndex < 20 && xIndex >= 0 && yIndex < 12 && yIndex >= 0 && z>Z1.groundZvalue[yIndex][xIndex])
		{
			Z1.higherPointNum[yIndex][xIndex] ++;
		}

	}
}

void DReceiver::BackgroundFileSeparate(string DATA_DIR, vector<string> &files)
{
	F1.getFiles(DATA_DIR,files);
	for (int i = 0; i < files.size(); i++)
	{
		cout << files[i] << endl;
		ifstream BackFile(files[i]);
		int pos = files[i].find_last_of(".");
		int pos1 = files[i].find_last_of("\\");
		string datename(files[i].substr(pos1 + 1, pos - pos1 - 1));
		string filterDirBac = DATA_DIR +"\\"+ "back"+datename + ".csv";
		string filterDirObj = DATA_DIR +"\\"+ "obj"+datename + ".csv";
		ofstream BackFileBac(filterDirBac, ios::out | ios::app);
		ofstream BackFileObject(filterDirObj, ios::out | ios::app);
		
		
		while (!BackFile.eof())
		{
			try
			{
				string str2;
				getline(BackFile, str2, '\n');
				stringstream ss(str2);
				double X, Y, Z;
				int clas;
				for (int j = 0; j < 4; j++)
				{

					string str1;
					switch (j)
					{
					case 0:
						getline(ss, str1, ',');
						X = stod(str1);
						break;
					case 1:
						getline(ss, str1, ',');
						Y = stod(str1);
						break;
					case 2:
						getline(ss, str1, ',');
						Z = stod(str1);
						break;
					case 3:
						getline(ss, str1, '\n');
						clas = stoi(str1);
						break;
					}

				}
				//getline(BackFile, str1, '\n');
				if (clas == 1)
				{
					BackFileBac << X << "," << Y << "," << Z << endl;
				}
				if (clas == 2)
				{
					BackFileObject << X << "," << Y << "," << Z << endl;
				}
			}
			catch (const std::exception&)
			{
				continue;
			}
			
		}
	}

}

/*void DReceiver::CSVtoPCD()
{
//#include "pch.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


	using namespace std;

	typedef struct tagPOINT_3D
	{
		double x;  //mm world coordinate x
		double y;  //mm world coordinate y
		double z;  //mm world coordinate z
		double i;
	}POINT_WORLD;

		vector<tagPOINT_3D> my_csvPoints;
		tagPOINT_3D csvPoint;



		ifstream fin("onezhen.csv");
		string line;
		int i = 0;
		while (getline(fin, line))
		{
			//cout << "原始字符串：" << line << endl; //整行输出
			istringstream sin(line);
			vector<string> fields;
			string field;
			while (getline(sin, field, ','))
			{
				fields.push_back(field);
			}
			if (i != 0) {
				csvPoint.x = atof(fields[3].c_str());
				csvPoint.y = atof(fields[4].c_str());
				csvPoint.z = atof(fields[5].c_str());
				csvPoint.i = atof(fields[6].c_str());
				//cout << "处理之后的字符串：" << csvPoint.x << "\t" << csvPoint.y << "\t" << csvPoint.z << "\t" << csvPoint.i << endl;
				my_csvPoints.push_back(csvPoint);
			}
			else
				i++;
		}
		//cout << my_csvPoints.size() << endl;
		int number_Txt = my_csvPoints.size();

		pcl::PointCloud<pcl::PointXYZI> cloud;
		// Fill in the cloud data
		cloud.width = number_Txt;
		cloud.height = 1;
		cloud.is_dense = false;
		cloud.points.resize(cloud.width * cloud.height);

		for (size_t i = 0; i < cloud.points.size(); ++i)
		{
			cloud.points[i].x = my_csvPoints[i].x;
			cloud.points[i].y = my_csvPoints[i].y;
			cloud.points[i].z = my_csvPoints[i].z;
			cloud.points[i].intensity = my_csvPoints[i].i;
		}
		pcl::io::savePCDFileASCII("mydata.pcd", cloud);
		std::cerr << "Saved " << cloud.points.size() << " data points to txt2pcd.pcd." << std::endl;

	


}*/
