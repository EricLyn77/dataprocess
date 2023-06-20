#include "processdata.h"

void processdata::caculateRate(string filePath, vector<string>& files)
{
	F1.getFiles(filePath,files);
	ofstream outFile("OriginalwrongResultRate.csv", ios::ate | ios::out);
	outFile << "objectID" << "," << "FrameDetected" << "," << "wrongRate" <<","<<"RateHigherThan80%Frame"<< endl;
	for (int i = 0; i < files.size(); i++)
	{

		ifstream inFile(files[i], ios::in);
		string fileString;
		
		int n = 0;
		int m = 0;
		//int *seq = new int[1000];
		int *wrongTimes = new int[30000];
		int *wrongClass = new int[30000];
		int *detectedTimes = new int[30000];
		int *lastFrame = new int[30000];
		vector<int> objectID;
		double *wrongRate = new double[30000];
		double *lowWrongRate = new double[30000];
		memset(wrongTimes, 0, sizeof(int)*30000);
		memset(wrongClass, 0, sizeof(int) * 30000);
		memset(detectedTimes, 0, sizeof(int) * 30000);
		memset(wrongRate, 0, sizeof(double) * 30000);
		memset(lastFrame, 0, sizeof(int) * 30000);
		memset(lowWrongRate, 0, sizeof(double) * 30000);
		//memset(objectID, 0, sizeof(int) * 1000);
		//int index = -1;
		outFile << files[i] << endl;
		cout<<files[i]<<endl;
		while (!inFile.eof())
		{
			int index = -1;
			//system("pause");
			for (int j = 0; j < 5; j++)
			{
				getline(inFile, fileString, ',');
				//cout << fileString << endl;
				//system("pause");
				try
				{
					if (j == 0)
					{
						if (stoi(fileString) == 1)
						{
							m = 1;
						}
					}
					if (j == 1)
					{
						if (stoi(fileString) == 1)
						{
							n=1;
						}
					}
					if (j == 3)
					{
						
						for (int i = 0; i < objectID.size(); i++)
						{
							if (stoi(fileString) == objectID[i])
							{
								index = i;
							}
						}
						if (index == -1)
						{
							index = objectID.size();
							objectID.push_back(stoi(fileString));
							lowWrongRate[index] = 1;
						}
						//cout << objectID << endl;
						detectedTimes[index]++;
						//cout << index<<endl;
						//cout << detectedTimes[objectID] << endl;
					}
					if (j == 4)
					{
						if (m == 1)
						{
							wrongClass[index]++;
							m = 0;
						}
						if (n == 1)
						{
							wrongTimes[index]++;
							//cout << wrongTimes[objectID] << endl;
							//cout << objectID << endl;
							//system("pause");
							if ((detectedTimes[index]>5)&&(((double)wrongTimes[index] / (double)detectedTimes[index]) > wrongRate[index]))
							{
								wrongRate[index] = (double)wrongTimes[index] / (double)detectedTimes[index];
							}
							if ((detectedTimes[index] > 5) && (((double)wrongTimes[index] / (double)detectedTimes[index]) < lowWrongRate[index]))
							{
								lowWrongRate[index] = (double)wrongTimes[index] / (double)detectedTimes[index];
							}
							if ((detectedTimes[index] > 5)&&(double)wrongTimes[index] / (double)detectedTimes[index] >= 0.90)
							{
								lastFrame[index] ++;
							}
							
							n = 0;
						}
					}
				
				}
				catch(...)
				{
					continue;
				}


			}
			
			getline(inFile, fileString, '\n');
		}
		for (int i = 0; i < objectID.size(); i++)
		{
			if (detectedTimes[i] > 5)
			{
				outFile << objectID[i] << "," << wrongClass[i]<<","<<detectedTimes[i] << "," << wrongRate[i] <<","<<lastFrame[i]<<","<<lowWrongRate[i]<< endl;
			}
		}
		delete[] wrongTimes;
		delete[] detectedTimes;
		delete[] wrongRate;
		delete[] lastFrame;
		vector<int>().swap(objectID);
	}

}
