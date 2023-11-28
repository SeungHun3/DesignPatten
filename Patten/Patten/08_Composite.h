#pragma once
#include <iostream>
#include <array>
#include <numeric>
#include <vector>

using namespace std;
void composite_main();

// 컴포지트 패턴 : 여러 객체들의 집합에 대해 개별 인터페이스를 동일하게 갖는 것

// 배열에 기반한 속성
class Creature
{
	enum Abilities{str,agl,intl,count};
	// 속성을 정의 후 적절한 크기의 배열 생성
	array<int, count> abilities;
	/* array 사용법 : array<자료형, 크기> 변수명; =>크기 정보, 안전한 인덱스 접근( at() 함수 제공 ), Iterator 지원
	* std::array<int, 5> myArray = {1, 2, 3, 4, 5};
	
    for (const auto& element : myArray) {
        std::cout << element << " ";
    }
	*/
public:

	int get_strength()const { return abilities[str]; }
	void set_strength(int value) { abilities[str] = value; }
	int sum() const
	{
		return accumulate(abilities.begin(), abilities.end(), 0);
	}

	Creature()
		:abilities{ 0,0,0 }
	{
	}
};
class Player : public Creature
{

};
class Monster : public Creature
{

};

// 그루핑 : 서로 다른 객체들을 드래그하여 하나의 객체처럼 다루는 작업 

//그래픽객체의 그루핑
struct GraphicObject
{
	virtual void draw() = 0;
	~GraphicObject()
	{
		cout << "delete" << endl;
	}
};
struct CircleObject : GraphicObject
{
	void draw() override
	{
		cout << "Circle" << endl;
	}
};
struct RectangleObject : GraphicObject
{
	void draw() override
	{
		cout << "Rectangle" << endl;
	}
};
// 여러개의 객체를 가지는 GraphicObject를 정의
struct Group : GraphicObject
{
	string name;
	vector<GraphicObject*> objects;

	explicit Group(const string& _name)
		: name{_name}
	{
	}

	void add(GraphicObject* _obj)
	{
		objects.push_back(_obj);
	}
	void draw() override
	{
		cout << "Group : " << name.c_str() << "\t contains : " << endl;
		for (auto&& o : objects)
		{
			o->draw();
		}
	}
	void deleteAll()
	{
		for (auto& it : objects)
		{
			if (it)
				delete it;
				it = nullptr;
		}
	}
	
};