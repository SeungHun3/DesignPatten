#pragma once
#include <iostream>
#include <functional>
#include <map>
using namespace std;
void factory_main();

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


// 추상 팩토리
struct HotDrink
{
	virtual void prepare(int volume) = 0;
	virtual ~HotDrink() = default;
};

struct Tea : HotDrink
{
	void prepare(int volume) override
	{
		cout << "Take tea bac, boil water, pour " << volume << "ml, add some lemon" << endl;
	}
};
struct Coffee : HotDrink
{
	void prepare(int volume) override
	{
		cout << "Grind some beans, boil water, pour " << volume << "ml, add cream, enjoy!" << endl;
	}
};

// 음료를 생성하여 리턴하는 함수
unique_ptr<HotDrink> make_drink(string type);
/*

unique_ptr<HotDrink> make_drink(string type)
{
	unique_ptr<HotDrink> drink;
	if (type == "tea")
	{
		drink = make_unique<Tea>();
		drink->prepare(200);
	}
	else
	{
		drink = make_unique<Coffee>();
		drink->prepare(50);
	}
	return drink;
}
*/

//==> tea, 와 coffee를 만드는 장비를 구분짓기
struct HotDrinkFactory
{
	virtual unique_ptr<HotDrink> make() const = 0;
};

struct CoffeeFactory : HotDrinkFactory
{
	unique_ptr<HotDrink> make() const override
	{
		return make_unique<Coffee>();
	}
};
struct TeaFactory : HotDrinkFactory
{
	unique_ptr<HotDrink> make() const override
	{
		return make_unique<Tea>();
	}
};

// 차가운 음료도 만들 수 있게 여러 팩토리들의 참조를 내부에 가질 수 있는 팩토리 클래스 구현
// 1개의 팩토리에서  다수의 팩토리를 가짐
class DrinkFactory
{
	map<string, unique_ptr<HotDrinkFactory>> hot_factories;

public:
	DrinkFactory()
	{
		hot_factories["hot_coffee"] = make_unique<CoffeeFactory>();
		hot_factories["hot_tea"] = make_unique<TeaFactory>();
		//cold_factories["cold_tea"] = make_unique<TeaFactory>();
	}

	unique_ptr<HotDrink> make_drink(const string& name)
	{
		auto drink = hot_factories[name]->make();
		drink->prepare(200);
		return drink;
	}
};


// 함수형 팩토리
// 다양한 팩토리의 구현을 하나의 팩토리에서 모두 처리하기에 복잡도를 줄일 수 있음
class DrinkWithVolumeFactory
{
private:
	map<string, function<unique_ptr<HotDrink>()>> factories;

public:
	DrinkWithVolumeFactory()
	{
		factories["hot_tea"] = [] {
			// 람다함수에서 생성과 진행 과정을 거친 후 반환객체를 map factories에 넣어줌
			// => factories["hot_tea"]가 호출되면 내장되어 있는 람다함수를 실행하여 반환값으로 tea가 나옴
			auto tea = make_unique<Tea>();
			tea->prepare(200);
			return tea;
			};
		factories["hot_coffee"] = [] {
			auto coffee = make_unique<Coffee>();
			coffee->prepare(50);
			return coffee;
			};
	}

	unique_ptr<HotDrink> make_drink(const string& name)
	{
		return factories[name]();
	}
};