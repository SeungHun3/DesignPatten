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
	float x , y; // 좌표값
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
	// == >문제점 : 항상 타입과 같은 이름을 가짐
	

protected:
	Point(const float _x, const float _y)
		: x{ _x }
		, y{ _y }
	{

	}

public:
	// 전역함수를 사용해 메소드를 지닌 객체를 생성하여 반환하도록 함
	static Point NewCartesian(float x, float y)
	{
		return Point{ x, y };
	}
	
	static Point NewPolar(float r, float theta)
	{
		return Point{ r * cos(theta),r * sin(theta) };
	}
	// 이 내용들을 팩토리 (클래스, 구조체)에서 실현

	// 외부 팩토리
	friend struct outter_Factory;

private:
	// 내부 팩토리
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