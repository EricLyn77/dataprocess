#include "GroundZ.h"
#include<iostream>

void groundZ::highestZ(double x, double y, double z)
{
	int xIndex = (int)(x + 100);
	int yIndex = ceil(119-(y + 40));
	//cout << xIndex <<"    "<< yIndex<<endl;
	if (xIndex < 200 && xIndex >= 0 && yIndex < 120 && yIndex >= 0&&z>groundZvalue[yIndex][xIndex]&&z<3)
	{
			//cout <<x<<"   "<<y<<"   "<<z<<endl;
			//cout << xIndex << "   " << yIndex << endl;
			//system("pause");
			arrayFlow[yIndex*200 + xIndex].push_back(z);
			//groundZvalue[yIndex][xIndex] = z;
			//highestZx[yIndex][xIndex] = x;
			//highestZy[yIndex][xIndex] = y;
			
	}

}

float groundZ::percentile_95(vector<float>& x)
{
	//cout << x.size();
	//cout << "1";
	
	/*for (int i = 0; i < x.size(); i++)
	{
		for (int j = i+1; j < x.size(); j++)
		{
			if (x[i] > x[j])
			{
				double temp;
				temp = x[i];
				x[i] = x[j];
				x[j] = temp;
			}
		}
	}*/
	
	if (x.size() <=400)
		return 400;
	sort(x.begin(), x.end());
/*	int i = 0;
	double highestZ  =x[x.size()-1];
	while (x[x.size() - 1 - i] >= 3&&(x.size()-1-i>0))
	{
		highestZ = x[x.size() - 1 - (i + 1)];
		i++;
	}
	return highestZ;*/
	return x[0.98*x.size()];
}


