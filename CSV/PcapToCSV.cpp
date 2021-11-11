#include"PcapToCSV.h"
#include<string>
#include<vector>

#define u_char unsigned char

void PcapToCSV::dataconvert(const char * DataDir)
{
	pcap_t *fp;
	char errbuf[PCAP_ERRBUF_SIZE];
	//char source[PCAP_BUF_SIZE];
	pcap_pkthdr *header = 0;
	const u_char *pkt_data = 0;
	int res;
	int frameIndex = 0;
	unsigned int packetCount = 0;
	vector<string> Framedata;
	vector<vector<string>> output;
	double interp_azimuth=0;
	double azimuth_offset=0;
	double temp_azimuth = 0;
	vector<string> files;
	getfiles F1;
	F1.getFiles(DataDir, files);
	cout << files[0] << endl;
	for (int j = 0; j < files.size(); j++)
	{
		int postion_begin = files[j].find("2019");
		int postion_end = files[j].find(".pcap");
		string realtime = files[j].substr(postion_begin, postion_end - postion_begin);
		string hour = realtime.substr(10, (realtime.find("-", 10) - 10));
		string initial_min = realtime.substr(12, (realtime.find("-", 12) - 12));
		string min = initial_min;
		cout << realtime << endl;
		cout << hour << endl;
		cout << initial_min << endl;
		int Azimuth = 0;
		int FrameIndex = 0;
		int pointDistance = 0;
		int laser_id = 0;

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
										if (interp_azimuth == 4700)
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
											Framedata.push_back(hour + "-" + min + "-" + sec);
											//Framedata.push_back(to_string(real_time));
											
											cout << Framedata[3] << endl;
											output.push_back(Framedata);

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
	}
	

/*	for (int i = 0; i < output.size(); i++)
	{
		for (int j = 0; j < output[i].size(); j++)
		{
			out0 << output[i][j] << ",";

		}
		out0 << endl;
	}*/

}
