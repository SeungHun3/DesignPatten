#pragma once
#include <iostream>
using namespace std;


enum class PointType
{
	artesian, 
	polar,
};

struct Point
{
private:
	float x , y; // ��ǥ��
public:
	void cout_x_y() 
	{
		cout << "x : " << x << ", y : " << y << endl;
	}

	//Point(const float a, const float b, PointType type = PointType::artesian)
	//{
	//	if (type == PointType::artesian)
	//	{
	//		x = a;
	//		y = b;
	//	}
	//	else
	//	{
	//		x = a * cos(b);
	//		y = a * sin(b);
	//	}
	//}
	// == >������ : �׻� Ÿ�԰� ���� �̸��� ����
	

protected:
	Point(const float _x, const float _y)
		: x{ _x }
		, y{ _y }
	{

	}

public:
	// �����Լ��� ����� �޼ҵ带 ���� ��ü�� �����Ͽ� ��ȯ�ϵ��� ��
	static Point NewCartesian(float x, float y)
	{
		return Point{ x, y };
	}
	
	static Point NewPolar(float r, float theta)
	{
		return Point{ r * cos(theta),r * sin(theta) };
	}
	// �� ������� ���丮 (Ŭ����, ����ü)���� ����

	// �ܺ� ���丮
	friend struct outter_Factory;

private:
	// ���� ���丮
	struct inner_Factory
	{
	private:
		inner_Factory(){}
	public:
		static Point NewCartesian(float x, float y)
		{
			return Point{ x, y };
		}

		static Point NewPolar(float r, float theta)
		{
			return Point{ r * cos(theta),r * sin(theta) };
		}
	};
public:
	static inner_Factory Factory_inner;
};

struct outter_Factory
{
	static Point NewCartesian(float x, float y)
	{
		return Point{ x, y };
	}

	static Point NewPolar(float r, float theta)
	{
		return Point{ r * cos(theta),r * sin(theta) };
	}
};