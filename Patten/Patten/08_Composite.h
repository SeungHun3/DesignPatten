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

// 뉴럴 네트워크

struct Neuron;
//////////////////////////////////////////////////////////
// 03
// 템플릿으로 만든이유 => this를 순회하기 위해 Self를 사용
template <typename Self>
struct SomeNeurons // Neuron, Neuron을 상속받은 레이어
{
	template <typename T> void connect_to(T& other)
	{
		// 지정받은 타입 T(Neuron)의 other에 대해 *this를 순회하며 other의 뉴런을 연결
		for (Neuron& from : *static_cast<Self*>(this))
		{
			for (Neuron& to : other)
			{
				from.out.push_back(&to);
				to.in.push_back(&from);
			}
		}
	}
};
//////////////////////////////////////////////////////////
// 01
struct Neuron : SomeNeurons<Neuron>
{
	vector<Neuron*> in, out;
	unsigned int id;
	Neuron()
	{
		static int id = 1;
		this->id = id++; // 전역변수를 사용해 생성시마다 고유의 id를 부여
	}
	// 다른 뉴런과 연결되도록
	void simple_connect_to(Neuron& _other)
	{
		out.push_back(&_other);
		_other.in.push_back(this);
	}
	// 뉴런레이어는 vector를 상속받고 있어 begin, end iterator가 있지만 Neuron은 없다
	// 자기 자신을 순회할 수 있도록 따로 구현
	Neuron* begin() { return this; }
	Neuron* end() { return this + 1; }
};
// connect_to함수는 뉴런과의 연결만 할수있다

//////////////////////////////////////////////////////////
//02
// 벡터를 상속받은 layer 구성
struct NeuronLayer : vector<Neuron>, SomeNeurons<NeuronLayer>
	//멤버 변수: NeuronLayer는 vector<Neuron>를 상속하므로, vector의 모든 멤버 변수 및 함수를 상속함
	//			동적 배열의 크기 조절, 요소에 접근하는 등의 작업 수행
	//멤버 함수 : NeuronLayer 객체는 vector의 멤버 함수들을 직접 호출할 수 있다. ex) push_back 함수를 사용해 Neuron을 레이어에 추가할 수 있음.
	//NeuronLayer layer;
	//layer.push_back(Neuron());
{
	NeuronLayer(int count)
	{
		while ( 0 < count--)
		{
			emplace_back(Neuron{});
		}
	}
};

// 레이어와도 연결할 수 있는 함수 필요
// => 베이스클래스에 연결함수를 만들고 다중상속을 이용함
