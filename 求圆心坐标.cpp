#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

ofstream fout;

typedef struct 
{
	double x;
	double y;
}Point;

double Y_Coordinates(double x,double y,double k,double x0);//4个参数
void Circle_Center(Point p1,Point p2,double dRadius);
bool Data_Validation(Point p1,Point p2,double dRadius);
void ReadData(Point &p1,Point &p2,double &dRadius);

void main()
{
	Point p1,p2;
	double dRadius = 0.0;

	ReadData(p1,p2,dRadius);

	fout.open("Result.txt");
	Circle_Center(p1,p2,dRadius);
	fout.close();
}

void Circle_Center(Point p1,Point p2,double dRadius)
{
	double k = 0.0,k_verticle = 0.0;
	double mid_x = 0.0,mid_y = 0.0;
	double a = 1.0;
	double b = 1.0;
	double c = 1.0;
	Point center1,center2;
	k = (p2.y - p1.y) / (p2.x - p1.x);
	if(k == 0)
	{
		center1.x = (p1.x + p2.x) / 2.0;
		center2.x = (p1.x + p2.x) / 2.0;
		center1.y = p1.y + sqrt(dRadius * dRadius -(p1.x - p2.x) * (p1.x - p2.x) / 4.0);
		center2.y = p2.y - sqrt(dRadius * dRadius -(p1.x - p2.x) * (p1.x - p2.x) / 4.0);
	}
	else
	{
		k_verticle = -1.0 / k;
		mid_x = (p1.x + p2.x) / 2.0;
		mid_y = (p1.y + p2.y) / 2.0;
		a = 1.0 + k_verticle * k_verticle;
		b = -2 * mid_x - k_verticle * k_verticle * (p1.x + p2.x);
		c = mid_x * mid_x + k_verticle * k_verticle * (p1.x + p2.x) * (p1.x + p2.x) / 4.0 - 
			(dRadius * dRadius - ((mid_x - p1.x) * (mid_x - p1.x) + (mid_y - p1.y) * (mid_y - p1.y)));
		
		center1.x = (-1.0 * b + sqrt(b * b -4 * a * c)) / (2 * a);
		center2.x = (-1.0 * b - sqrt(b * b -4 * a * c)) / (2 * a);
		center1.y = Y_Coordinates(mid_x,mid_y,k_verticle,center1.x);
		center2.y = Y_Coordinates(mid_x,mid_y,k_verticle,center2.x);
	}

	fout << center1.x << "	" << center1.y << endl;
	fout << center2.x << "	" << center2.y << endl;
}

double Y_Coordinates(double x,double y,double k,double x0)
{
	return k * x0 - k * x + y;
}


bool Data_Validation(Point p1,Point p2,double dRadius)
{
	double dDistance = 0.0;
	dDistance = sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
	if(dDistance == 0.0)
	{
		cout << "\n输入了相同的点!\n";
		return false;
	}
	if((2 * dRadius) >= dDistance)
		return true;
	else
	{
		cout << "\n两点间距离大于直径!\n";
		return false;
	}
}

void ReadData(Point &p1,Point &p2,double &dRadius)
{
	cout << "请输入圆周上一点的坐标：";
	cin >> p1.x >> p1.y;
	cout << "请输入圆周上另一点的坐标：";
	cin >> p2.x >> p2.y;
	cout << "请输入圆的半径：";
	cin >> dRadius;

	if(! Data_Validation(p1,p2,dRadius))
	{
		cout << endl << "数据不合理!\n";
		exit(0);
	}
}