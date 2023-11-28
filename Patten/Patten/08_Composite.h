#pragma once
#include <iostream>
#include <array>
#include <numeric>
#include <vector>

using namespace std;
void composite_main();

// ������Ʈ ���� : ���� ��ü���� ���տ� ���� ���� �������̽��� �����ϰ� ���� ��

// �迭�� ����� �Ӽ�
class Creature
{
	enum Abilities{str,agl,intl,count};
	// �Ӽ��� ���� �� ������ ũ���� �迭 ����
	array<int, count> abilities;
	/* array ���� : array<�ڷ���, ũ��> ������; =>ũ�� ����, ������ �ε��� ����( at() �Լ� ���� ), Iterator ����
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

// �׷��� : ���� �ٸ� ��ü���� �巡���Ͽ� �ϳ��� ��üó�� �ٷ�� �۾� 

//�׷��Ȱ�ü�� �׷���
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
// �������� ��ü�� ������ GraphicObject�� ����
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

// ���� ��Ʈ��ũ

struct Neuron;
//////////////////////////////////////////////////////////
// 03
// ���ø����� �������� => this�� ��ȸ�ϱ� ���� Self�� ���
template <typename Self>
struct SomeNeurons // Neuron, Neuron�� ��ӹ��� ���̾�
{
	template <typename T> void connect_to(T& other)
	{
		// �������� Ÿ�� T(Neuron)�� other�� ���� *this�� ��ȸ�ϸ� other�� ������ ����
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
		this->id = id++; // ���������� ����� �����ø��� ������ id�� �ο�
	}
	// �ٸ� ������ ����ǵ���
	void simple_connect_to(Neuron& _other)
	{
		out.push_back(&_other);
		_other.in.push_back(this);
	}
	// �������̾�� vector�� ��ӹް� �־� begin, end iterator�� ������ Neuron�� ����
	// �ڱ� �ڽ��� ��ȸ�� �� �ֵ��� ���� ����
	Neuron* begin() { return this; }
	Neuron* end() { return this + 1; }
};
// connect_to�Լ��� �������� ���Ḹ �Ҽ��ִ�

//////////////////////////////////////////////////////////
//02
// ���͸� ��ӹ��� layer ����
struct NeuronLayer : vector<Neuron>, SomeNeurons<NeuronLayer>
	//��� ����: NeuronLayer�� vector<Neuron>�� ����ϹǷ�, vector�� ��� ��� ���� �� �Լ��� �����
	//			���� �迭�� ũ�� ����, ��ҿ� �����ϴ� ���� �۾� ����
	//��� �Լ� : NeuronLayer ��ü�� vector�� ��� �Լ����� ���� ȣ���� �� �ִ�. ex) push_back �Լ��� ����� Neuron�� ���̾ �߰��� �� ����.
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

// ���̾�͵� ������ �� �ִ� �Լ� �ʿ�
// => ���̽�Ŭ������ �����Լ��� ����� ���߻���� �̿���
