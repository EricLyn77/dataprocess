#pragma once

#include"PcapToCSV.h"
#include<string>
#include<vector>
#include<iostream>


#define u_char unsigned char


void PcapToCSV::dataconvert(const char * DataDir, int set_azimuth)
{
	pcap_t *fp;
	char errbuf[PCAP_ERRBUF_SIZE];
	//char source[PCAP_BUF_SIZE];
	pcap_pkthdr *header = 0;
	const u_char *pkt_data = 0;
	int res;
	
	unsigned int packetCount = 0;
	vector<string> Framedata;
	vector<vector<string>> output0;
	vector<vector<string>> output1;
	vector<vector<string>> output2;
	vector<vector<string>> output3;
	vector<vector<string>> output4;
	vector<vector<string>> output5;
	vector<vector<string>> output6;
	vector<vector<string>> output7;
	vector<vector<string>> output8;
	vector<vector<string>> output9;
	vector<vector<string>> output10;
	vector<vector<string>> output11;
	vector<vector<string>> output12;
	vector<vector<string>> output13;
	vector<vector<string>> output14;
	vector<vector<string>> output15;
	vector<vector<string>> output16;
	vector<vector<string>> output17;
	vector<vector<string>> output18;
	vector<vector<string>> output19;
	vector<vector<string>> output20;
	vector<vector<string>> output21;
	vector<vector<string>> output22;
	vector<vector<string>> output23;
	vector<vector<string>> output24;
	vector<vector<string>> output25;
	vector<vector<string>> output26;
	vector<vector<string>> output27;
	vector<vector<string>> output28;
	vector<vector<string>> output29;
	vector<vector<string>> output30;
	vector<vector<string>> output31;
	output0.reserve(1000000);
	output1.reserve(1000000);
	output2.reserve(1000000);
	output3.reserve(1000000);
	output4.reserve(1000000);
	output5.reserve(1000000);
	output6.reserve(1000000);
	output7.reserve(1000000);
	output8.reserve(1000000);
	output9.reserve(1000000);
	output10.reserve(1000000);
	output11.reserve(1000000);
	output12.reserve(1000000);
	output13.reserve(1000000);
	output14.reserve(1000000);
	output15.reserve(1000000);
	output16.reserve(1000000);
	output17.reserve(1000000);
	output18.reserve(1000000);
	output19.reserve(1000000);
	output20.reserve(1000000);
	output21.reserve(1000000);
	output22.reserve(1000000);
	output23.reserve(1000000);
	output24.reserve(1000000);
	output25.reserve(1000000);
	output26.reserve(1000000);
	output27.reserve(1000000);
	output28.reserve(1000000);
	output29.reserve(1000000);
	output30.reserve(1000000);
	output31.reserve(1000000);
	double interp_azimuth=0;
	double azimuth_offset=0;
	double temp_azimuth = 0;
	vector<string> files;
	getfiles F1;
	F1.getFiles(DataDir, files);
	cout << files[0] << endl;
	for (int j = 0; j < files.size(); j++)
	{
		string filename = files[j].substr(files[j].find_first_of("2019",5));
		cout << filename << endl;
		int postion_begin = filename.find("2019");
		int postion_end = filename.find(".pcap");
		string realtime = filename.substr(postion_begin, postion_end - postion_begin);
		string hour = realtime.substr(10, (realtime.find("-", 10) - 10));
		string initial_min = realtime.substr(realtime.find_last_of("-") + 1);
		string min = initial_min;
		cout << realtime << endl;
		cout << hour << endl;
		cout << initial_min << endl;
		int Azimuth = 0;
		int FrameIndex = 0;
		int pointDistance = 0;
		int laser_id = 0;
		int frameIndex = 0;

	//	try
	//	{
			if ((fp = pcap_open_offline(const_cast<char *>(files[j].c_str()), errbuf)) == NULL)
			{
				throw errbuf;
			}
			while ((res = pcap_next_ex(fp, &header, &pkt_data)) >= 0)
			{
				//cout << "1" << endl;
				if (res == 0)//获取报文超时
				{
					cout << "0" << endl;
					continue;
				}
				if (packetCount < 100000)
				{
					int dataBlockCount = 0;
					int pointIndex = 0;
					int dataCount = 0;
					unsigned char currentAzimuth_byte_0 = 0x00;
					unsigned char currentAzimuth_byte_1 = 0x00;


					

					if (header->caplen == 554)
					{
					}
					else
					{
						auto sazm = ((pkt_data[145] << 8) | (pkt_data[144]));
						auto eazm = ((pkt_data[245] << 8) | (pkt_data[244]));

						if (eazm < sazm)
						{
							eazm += 36000;
						}

						double rotating_Angle_rate = (eazm - sazm) / (55.296);//dual return mode for 16 laser, need to check 32 laser single mode

						for (unsigned int i = 42; i < header->caplen; i++)
						{
							Framedata.reserve(1000);

							if (i > 42 && i < 1242)
							{
								int val = (i - 42) % 100;
								if (val == 0)
								{
									dataBlockCount++;
									dataCount = 0;
								}
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

								}
								if (val < 100 && val>3)
								{
									if ((val - (3 * dataCount)) == 6)
									{
										auto azimuth = ((currentAzimuth_byte_1 << 8) | (currentAzimuth_byte_0));
										auto intensity = pkt_data[i];
										auto i_distance = ((pkt_data[i - 1] << 8) | (pkt_data[i - 2]));//顺序？
										double distance;
									//	cout << azimuth << endl;
									//	cout << temp_azimuth << endl;
										interp_azimuth = ceil((azimuth + ((2.304*static_cast<int>(laser_id / 2))*rotating_Angle_rate)));
										azimuth_offset = azimuth_offset_32[laser_id];//是否影响最终的azimuth？
										distance = (i_distance * 4.0) / 1000.0;
										//cout << interp_azimuth << endl;
										//system("pause");
										//cout << distance << endl;
										//cout << interp_azimuth<< endl;
									if (interp_azimuth > 36000)
										{
											interp_azimuth = interp_azimuth - 36000;
										}
										if (interp_azimuth < temp_azimuth)
										{

											//writeCSV_frame(outfilename2, &frameData)
											frameIndex++;
											
										}
										temp_azimuth = interp_azimuth;
										if (interp_azimuth == set_azimuth)
										{
											string sec = to_string((frameIndex / 10));
											if (stoi(sec) > 59)
											{
												min = to_string(stoi(initial_min) + (stoi(sec) / 60));
												sec = to_string(stoi(sec) % 60);
											}
											

											Framedata.push_back(to_string(laser_id));
											Framedata.push_back(to_string(distance));
											Framedata.push_back(to_string(intensity));
											Framedata.push_back(hour + ":" + min + ":" + sec);
											//cout << interp_azimuth<< endl;
											//Framedata.push_back(to_string(real_time));
											cout << Framedata[3] << endl;
											cout << laser_id << endl;
											cout << frameIndex << endl;
											switch (laser_id)
											{
											case 0: output0.push_back(Framedata);
												break;
											case 1: output1.push_back(Framedata);
												break;
											case 2: output2.push_back(Framedata);
												break;
											case 3: output3.push_back(Framedata);
												break;
											case 4: output4.push_back(Framedata);
												break;
											case 5: output5.push_back(Framedata);
												break;
											case 6: output6.push_back(Framedata);
												break;
											case 7: output7.push_back(Framedata);
												break;
											case 8: output8.push_back(Framedata);
												break;
											case 9: output9.push_back(Framedata);
												break;
											case 10: output10.push_back(Framedata);
												break;
											case 11: output11.push_back(Framedata);
												break;
											case 12: output12.push_back(Framedata);
												break;
											case 13: output13.push_back(Framedata);
												break;
											case 14: output14.push_back(Framedata);
												break;
											case 15: output15.push_back(Framedata);
												break;
											case 16: output16.push_back(Framedata);
												break;
											case 17: output17.push_back(Framedata);
												break;
											case 18: output18.push_back(Framedata);
												break;
											case 19: output19.push_back(Framedata);
												break;
											case 20: output20.push_back(Framedata);
												break;
											case 21: output21.push_back(Framedata);
												break;
											case 22: output22.push_back(Framedata);
												break;
											case 23: output23.push_back(Framedata);
												break;
											case 24: output24.push_back(Framedata);
												break;
											case 25: output25.push_back(Framedata);
												break;
											case 26: output26.push_back(Framedata);
												break;
											case 27: output27.push_back(Framedata);
												break;
											case 28: output28.push_back(Framedata);
												break;
											case 29: output29.push_back(Framedata);
												break;
											case 30: output30.push_back(Framedata);
												break;
											case 31: output31.push_back(Framedata);
												break;
											}

											Framedata.clear();
											vector<string>().swap(Framedata);
										}


										dataCount++;
										laser_id++;


										}
									}
										
							}

						}
					}
				}
			}
	//	}
	//	catch (errbuf)
	//	{

	//	}
			string pathorigin0 = "E:\\datashift\\result\\2019-4-15\\";
			ofstream out0(pathorigin0.append("laserid=0").append(to_string(set_azimuth)).append(".csv"),ios::app);
			for (int i = 0; i < output0.size(); i++)
			{
				for (int j = 0; j < output0[i].size(); j++)
				{
					out0 << output0[i][j] << ",";

				}
				out0 << endl;
			}
			pathorigin0 = "E:\\datashift\\result\\2019-4-15\\";
			ofstream out1(pathorigin0.append("laserid=1").append(to_string(set_azimuth)).append(".csv"), ios::app);
			for (int i = 0; i < output1.size(); i++)
			{
				for (int j = 0; j < output1[i].size(); j++)
				{
					out1 << output1[i][j] << ",";

				}
				out1 << endl;
			}
			pathorigin0 = "E:\\datashift\\result\\2019-4-15\\";
			ofstream out2(pathorigin0.append("laserid=2").append(to_string(set_azimuth)).append(".csv"), ios::app);
			for (int i = 0; i < output2.size(); i++)
			{
				for (int j = 0; j < output2[i].size(); j++)
				{
					out2 << output2[i][j] << ",";

				}
				out2 << endl;
			}
			pathorigin0 = "E:\\datashift\\result\\2019-4-15\\";
			ofstream out3(pathorigin0.append("laserid=3").append(to_string(set_azimuth)).append(".csv"), ios::app);
			for (int i = 0; i < output3.size(); i++)
			{
				for (int j = 0; j < output3[i].size(); j++)
				{
					out3 << output3[i][j] << ",";

				}
				out3 << endl;
			}
			 pathorigin0 = "E:\\datashift\\result\\2019-4-15\\";
			ofstream out4(pathorigin0.append("laserid=4").append(to_string(set_azimuth)).append(".csv"), ios::app);
			for (int i = 0; i < output4.size(); i++)
			{
				for (int j = 0; j < output4[i].size(); j++)
				{
					out4 << output4[i][j] << ",";

				}
				out4 << endl;
			}
			 pathorigin0 = "E:\\datashift\\result\\2019-4-15\\";
			ofstream out5(pathorigin0.append("laserid=5").append(to_string(set_azimuth)).append(".csv"), ios::app);
			for (int i = 0; i < output5.size(); i++)
			{
				for (int j = 0; j < output5[i].size(); j++)
				{
					out5 << output5[i][j] << ",";

				}
				out5 << endl;
			}
			 pathorigin0 = "E:\\datashift\\result\\2019-4-15\\";
			ofstream out6(pathorigin0.append("laserid=6").append(to_string(set_azimuth)).append(".csv"), ios::app);
			for (int i = 0; i < output6.size(); i++)
			{
				for (int j = 0; j < output6[i].size(); j++)
				{
					out6 << output6[i][j] << ",";

				}
				out6 << endl;
			}
			 pathorigin0 = "E:\\datashift\\result\\2019-4-15\\";
			ofstream out7(pathorigin0.append("laserid=7").append(to_string(set_azimuth)).append(".csv"), ios::app);
			for (int i = 0; i < output7.size(); i++)
			{
				for (int j = 0; j < output7[i].size(); j++)
				{
					out7 << output7[i][j] << ",";

				}
				out7 << endl;
			}
			 pathorigin0 = "E:\\datashift\\result\\2019-4-15\\";
			ofstream out8(pathorigin0.append("laserid=8").append(to_string(set_azimuth)).append(".csv"), ios::app);
			for (int i = 0; i < output8.size(); i++)
			{
				for (int j = 0; j < output8[i].size(); j++)
				{
					out8 << output8[i][j] << ",";

				}
				out8 << endl;
			}
			 pathorigin0 = "E:\\datashift\\result\\2019-4-15\\";
			ofstream out9(pathorigin0.append("laserid=9").append(to_string(set_azimuth)).append(".csv"), ios::app);
			for (int i = 0; i < output9.size(); i++)
			{
				for (int j = 0; j < output9[i].size(); j++)
				{
					out9 << output9[i][j] << ",";

				}
				out9 << endl;
			}
			 pathorigin0 = "E:\\datashift\\result\\2019-4-15\\";
			ofstream out10(pathorigin0.append("laserid=10").append(to_string(set_azimuth)).append(".csv"), ios::app);
			for (int i = 0; i < output10.size(); i++)
			{
				for (int j = 0; j < output10[i].size(); j++)
				{
					out10 << output10[i][j] << ",";

				}
				out10 << endl;
			}
			 pathorigin0 = "E:\\datashift\\result\\2019-4-15\\";
			ofstream out11(pathorigin0.append("laserid=11").append(to_string(set_azimuth)).append(".csv"), ios::app);
			for (int i = 0; i < output11.size(); i++)
			{
				for (int j = 0; j < output11[i].size(); j++)
				{
					out11 << output11[i][j] << ",";

				}
				out11 << endl;
			}
			 pathorigin0 = "E:\\datashift\\result\\2019-4-15\\";
			ofstream out12(pathorigin0.append("laserid=12").append(to_string(set_azimuth)).append(".csv"), ios::app);
			for (int i = 0; i < output12.size(); i++)
			{
				for (int j = 0; j < output12[i].size(); j++)
				{
					out12 << output12[i][j] << ",";

				}
				out12 << endl;
			}
			 pathorigin0 = "E:\\datashift\\result\\2019-4-15\\";
			ofstream out13(pathorigin0.append("laserid=13").append(to_string(set_azimuth)).append(".csv"), ios::app);
			for (int i = 0; i < output13.size(); i++)
			{
				for (int j = 0; j < output13[i].size(); j++)
				{
					out13 << output13[i][j] << ",";

				}
				out13 << endl;
			}
			 pathorigin0 = "E:\\datashift\\result\\2019-4-15\\";
			ofstream out14(pathorigin0.append("laserid=14").append(to_string(set_azimuth)).append(".csv"), ios::app);
			for (int i = 0; i < output14.size(); i++)
			{
				for (int j = 0; j < output14[i].size(); j++)
				{
					out14 << output14[i][j] << ",";

				}
				out14 << endl;
			}
			 pathorigin0 = "E:\\datashift\\result\\2019-4-15\\";
			ofstream out15(pathorigin0.append("laserid=15").append(to_string(set_azimuth)).append(".csv"), ios::app);
			for (int i = 0; i < output15.size(); i++)
			{
				for (int j = 0; j < output15[i].size(); j++)
				{
					out15 << output15[i][j] << ",";

				}
				out15 << endl;
			}
			 pathorigin0 = "E:\\datashift\\result\\2019-4-15\\";
			ofstream out16(pathorigin0.append("laserid=16").append(to_string(set_azimuth)).append(".csv"), ios::app);
			for (int i = 0; i < output16.size(); i++)
			{
				for (int j = 0; j < output16[i].size(); j++)
				{
					out16 << output16[i][j] << ",";

				}
				out16 << endl;
			}
			 pathorigin0 = "E:\\datashift\\result\\2019-4-15\\";
			ofstream out17(pathorigin0.append("laserid=17").append(to_string(set_azimuth)).append(".csv"), ios::app);
			for (int i = 0; i < output17.size(); i++)
			{
				for (int j = 0; j < output17[i].size(); j++)
				{
					out17 << output17[i][j] << ",";

				}
				out17 << endl;
			}
			 pathorigin0 = "E:\\datashift\\result\\2019-4-15\\";
			ofstream out18(pathorigin0.append("laserid=18").append(to_string(set_azimuth)).append(".csv"), ios::app);
			for (int i = 0; i < output18.size(); i++)
			{
				for (int j = 0; j < output18[i].size(); j++)
				{
					out18 << output18[i][j] << ",";

				}
				out18 << endl;
			}
			 pathorigin0 = "E:\\datashift\\result\\2019-4-15\\";
			ofstream out19(pathorigin0.append("laserid=19").append(to_string(set_azimuth)).append(".csv"), ios::app);
			for (int i = 0; i < output19.size(); i++)
			{
				for (int j = 0; j < output19[i].size(); j++)
				{
					out19 << output19[i][j] << ",";

				}
				out19 << endl;
			}
			 pathorigin0 = "E:\\datashift\\result\\2019-4-15\\";
			ofstream out20(pathorigin0.append("laserid=20").append(to_string(set_azimuth)).append(".csv"), ios::app);
			for (int i = 0; i < output20.size(); i++)
			{
				for (int j = 0; j < output20[i].size(); j++)
				{
					out20 << output20[i][j] << ",";

				}
				out20 << endl;
			}
			 pathorigin0 = "E:\\datashift\\result\\2019-4-15\\";
			ofstream out21(pathorigin0.append("laserid=21").append(to_string(set_azimuth)).append(".csv"), ios::app);
			for (int i = 0; i < output21.size(); i++)
			{
				for (int j = 0; j < output21[i].size(); j++)
				{
					out21 << output21[i][j] << ",";

				}
				out21 << endl;
			}
			 pathorigin0 = "E:\\datashift\\result\\2019-4-15\\";
			ofstream out22(pathorigin0.append("laserid=22").append(to_string(set_azimuth)).append(".csv"), ios::app);
			for (int i = 0; i < output22.size(); i++)
			{
				for (int j = 0; j < output22[i].size(); j++)
				{
					out22 << output22[i][j] << ",";

				}
				out22 << endl;
			}
			 pathorigin0 = "E:\\datashift\\result\\2019-4-15\\";
			ofstream out23(pathorigin0.append("laserid=23").append(to_string(set_azimuth)).append(".csv"), ios::app);
			for (int i = 0; i < output23.size(); i++)
			{
				for (int j = 0; j < output23[i].size(); j++)
				{
					out23 << output23[i][j] << ",";

				}
				out23 << endl;
			}
			 pathorigin0 = "E:\\datashift\\result\\2019-4-15\\";
			ofstream out24(pathorigin0.append("laserid=24").append(to_string(set_azimuth)).append(".csv"), ios::app);
			for (int i = 0; i < output24.size(); i++)
			{
				for (int j = 0; j < output24[i].size(); j++)
				{
					out24 << output24[i][j] << ",";

				}
				out24 << endl;
			}
			 pathorigin0 = "E:\\datashift\\result\\2019-4-15\\";
			ofstream out25(pathorigin0.append("laserid=25").append(to_string(set_azimuth)).append(".csv"), ios::app);
			for (int i = 0; i < output25.size(); i++)
			{
				for (int j = 0; j < output25[i].size(); j++)
				{
					out25 << output25[i][j] << ",";

				}
				out25 << endl;
			}
			 pathorigin0 = "E:\\datashift\\result\\2019-4-15\\";
			ofstream out26(pathorigin0.append("laserid=26").append(to_string(set_azimuth)).append(".csv"), ios::app);
			for (int i = 0; i < output26.size(); i++)
			{
				for (int j = 0; j < output26[i].size(); j++)
				{
					out26 << output26[i][j] << ",";

				}
				out26 << endl;
			}
			 pathorigin0 = "E:\\datashift\\result\\2019-4-15\\";
			ofstream out27(pathorigin0.append("laserid=27").append(to_string(set_azimuth)).append(".csv"), ios::app);
			for (int i = 0; i < output27.size(); i++)
			{
				for (int j = 0; j < output27[i].size(); j++)
				{
					out27 << output27[i][j] << ",";

				}
				out27 << endl;
			}
			 pathorigin0 = "E:\\datashift\\result\\2019-4-15\\";
			ofstream out28(pathorigin0.append("laserid=28").append(to_string(set_azimuth)).append(".csv"), ios::app);
			for (int i = 0; i < output28.size(); i++)
			{
				for (int j = 0; j < output28[i].size(); j++)
				{
					out28 << output28[i][j] << ",";

				}
				out28 << endl;
			}
			 pathorigin0 = "E:\\datashift\\result\\2019-4-15\\";
			ofstream out29(pathorigin0.append("laserid=29").append(to_string(set_azimuth)).append(".csv"), ios::app);
			for (int i = 0; i < output29.size(); i++)
			{
				for (int j = 0; j < output29[i].size(); j++)
				{
					out29 << output29[i][j] << ",";

				}
				out29 << endl;
			}
			 pathorigin0 = "E:\\datashift\\result\\2019-4-15\\";
			ofstream out30(pathorigin0.append("laserid=30").append(to_string(set_azimuth)).append(".csv"), ios::app);
			for (int i = 0; i < output30.size(); i++)
			{
				for (int j = 0; j < output30[i].size(); j++)
				{
					out30 << output30[i][j] << ",";

				}
				out30 << endl;
			}
			 pathorigin0 = "E:\\datashift\\result\\2019-4-15\\";
			ofstream out31(pathorigin0.append("laserid=31").append(to_string(set_azimuth)).append(".csv"), ios::app);
			for (int i = 0; i < output31.size(); i++)
			{
				for (int j = 0; j < output31[i].size(); j++)
				{
					out31 << output31[i][j] << ",";

				}
				out31 << endl;
			}
			output0.clear();
			output1.clear();
			output2.clear();
			output3.clear();
			output4.clear();
			output5.clear();
			output6.clear();
			output7.clear();
			output8.clear();
			output9.clear();
			output10.clear();
			output11.clear();
			output12.clear();
			output13.clear();
			output14.clear();
			output15.clear();
			output16.clear();
			output17.clear();
			output18.clear();
			output19.clear();
			output20.clear();
			output21.clear();
			output22.clear();
			output23.clear();
			output24.clear();
			output25.clear();
			output26.clear();
			output27.clear();
			output28.clear();
			output29.clear();
			output30.clear();
			output31.clear();

	}
	


}
