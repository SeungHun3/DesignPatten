#pragma once
#include <iostream>
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


// �߻� ���丮
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

// ���Ḧ �����Ͽ� �����ϴ� �Լ�
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

//==> tea, �� coffee�� ����� ��� ��������
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

// ������ ���ᵵ ���� �� �ְ� ���� ���丮���� ������ ���ο� ���� �� �ִ� ���丮 Ŭ���� ����
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
