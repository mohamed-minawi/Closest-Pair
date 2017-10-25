#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void closestpairBF(vector<float>, float& , float &, float &);
void closestpairPS(vector<float>, float& , float &, float &);
float closespairDC(vector<float>, float & p1, float & p2);
float closespairDCmain(vector<float>, float & p1, float & p2);

int main()
{
	vector<float> arr;
	arr.push_back(1.45);
	arr.push_back(0.5);
	arr.push_back(0.75);
	arr.push_back(1.5);
	arr.push_back(1.3);

	float p1, p2;
	float Dmin;

	cout << "The array has the following elements: " << endl <<"{";
	for (int i = 0; i < arr.size(); i++)
		cout << arr[i] << " , ";
	cout << "}" << endl << endl;

	cout << "Brute Force Algorithim Result: " << endl;
	closestpairBF(arr, p1, p2, Dmin);
	cout << "Point 1: " << p1 <<endl<< "Point 2: " << p2 <<endl<< "Difference: " << Dmin << endl << endl;

	cout << "PreSorting then Scanning Algorithim Result: " << endl;
	closestpairPS(arr, p1, p2, Dmin);
	cout << "Point 1: " << p1 << endl << "Point 2: " << p2 << endl << "Difference: " << Dmin << endl << endl;

	cout << "Divide and Conquer Algorithim Results: " << endl;
	Dmin = closespairDC(arr, p1, p2);
	cout << "Point 1: " << p1 << endl << "Point 2: " << p2 << endl << "Difference: " << Dmin << endl << endl;

	system("pause");
	return 0;
}

void closestpairBF(vector<float> x, float& p1, float & p2,float &Dmin)
{
	Dmin = 100000000000;
	 p1 = p2 = -1;

	for (int i = 0; i < x.size() - 1; i++)
		for (int j = i + 1; j < x.size(); j++)
			if (abs(x[j] - x[i]) < Dmin)
				Dmin = abs(x[j] - x[i]), p1 = x[i], p2 = x[j];
}

void closestpairPS(vector<float> x, float& p1, float & p2, float &Dmin)
{
	Dmin = 100000000000;
	p1 = p2 = -1;
	sort(x.begin(),x.end());
	for(int i=0;i<x.size()-1;i++)
		if (abs(x[i] - x[i+1]) < Dmin)
			Dmin = abs(x[i] - x[i+1]), p1 = x[i], p2 = x[i+1];
}

float closespairDC(vector<float> x, float & p1, float & p2)
{
	sort(x.begin(), x.end());
	p1 = p2 = -1;
	return closespairDCmain(x, p1, p2);
}

float closespairDCmain(vector<float> x, float & p1, float& p2)
{

	if (x.size() == 1)
	{
		p1 = p2 = -1;
		return 10000000000;
	}
	else if (x.size() == 2)
	{
		p1 = x[0];
		p2 = x[1];
		return abs(x[0] - x[1]);
	}
	else
	{
		vector<float> temp1(x.begin(), x.begin() + x.size() / 2 );
		vector<float> temp2(x.begin() + x.size() / 2 + 1, x.end());

		float xy = x[x.size() / 2];

		float a, b, c, d;
		float min1 = closespairDCmain(temp1, a, b);
		float min2 = closespairDCmain(temp2, c, d);
		float min3 = abs(xy - x[x.size() / 2 - 1]);
		float min4 = abs(xy - x[x.size() / 2 + 1]);

		float Dmin = min(min1, min2);
		float Dmin2 = min(min3, min4);
	
		float finalmin = min(Dmin, Dmin2);

		if (finalmin == Dmin)
		{
			if (Dmin == min1)
			{
				p1 = a;
				p2 = b;
				return min1;
			}
			else
			{
				p1 = c;
				p2 = d;
				return min2;
			}
		}
		else
		{
			if (Dmin2 == min3)
			{
				p1 = xy;
				p2 = x[x.size() / 2 - 1];
				return min3;
			}
			else
			{
				p1 = xy;
				p2 = x[x.size() / 2 + 1];
				return min4;
			}
		}
	}

}