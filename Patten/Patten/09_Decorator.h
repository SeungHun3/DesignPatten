#pragma once
#include <iostream>
#include <string>

using namespace std;
void decorator_main();

// ��Ŀ������ : ����-���� OCP ��Ģ �ؼ�
// �����ڵ� ����x , ���ο� ����߰�

struct Deco_Shape
{
	virtual string str() const = 0; // Ư�� ������ ���¸� �ؽ�Ʈ�� ��Ÿ��������
};
struct Deco_Circle : Deco_Shape
{
	float radius;


	Deco_Circle() {}
	explicit Deco_Circle(const float _radius)
		: radius{ radius }
	{
	}
	void resize(float factor)
	{
		radius *= factor;
	}
	string str() const override
	{
		//cout << "Circle" << endl;
		return string{ "Circle" };
	}
};
struct Deco_Square : Deco_Shape
{
	string str() const override
	{
		return string{ "Square" };
	}
};

// ���� ��Ŀ������ : ������ �ְ� ������ ��Ÿ�ӿ� �������� �ռ��Ͽ� �������ִ� ���
struct ColoredShape : Deco_Shape
{
	Deco_Shape& shape;
	string color;

	ColoredShape(Deco_Shape& _shape, const string& _color)
		: shape{ _shape }
		, color{ _color }
	{
	}
	string str() const override
	{
		return string{ shape.str() + " has the color " + color };
	}
};
struct TransparentShape : Deco_Shape
{
	Deco_Shape& shape;
	uint8_t transparency;

	TransparentShape(Deco_Shape& _shape, const uint8_t _transparency)
		: shape{ _shape }
		, transparency{ _transparency }
	{
	}
	string str() const override
	{
		return string{ shape.str() + " has transparency " + to_string(transparency) };
	}

};

// ���� ��Ŀ������ : ������ ������ �߰������ �ռ�, ���߿� ������ �� ����
// ���� �ڵ忡�� redcircle �� resize�Լ��� ȣ�� ����
// =>MixIn ��� �̿� : ���ø��� ���� ���� ��� �ռ�


template <typename T> 
struct Color_template : T
{
	// ���ø� �Ķ���͸� �����Ҽ� ���� assert�� Deco_Shape�� ������ string str() override �������
	static_assert(is_base_of< Deco_Shape, T>::value, "Template argument must be a Shape");

	string color;
	string str() const override
	{
		return string{ T::str() + " has the color " + color };
	}

	Color_template() {}
	Color_template(const string& _color)
		: color{ _color }
	{}
	// ������ : ���� �������� �����ڸ� ȣ��Ǿ� ���� ��Ŀ���̼��� �ѹ��� �ʱ�ȭ�Ҽ��� ���� 


	// �������� ���ø� note.text  143��
	// �����ڿ� ���� ���ڸ� ���(�������� ��Ű��) ȣ�� => ��ӱ����� ���ڸ� �÷��ְ� ���ָ� �θ�����ڸ� ���ʷ� ȣ���Ŵ
	template <typename...Args>
	Color_template(const string& _color, Args ...args)
		: T(std::forward<Args>(args)...), color{ _color }
		// ���⼭ ���̽� Ŭ������ �Ҹ��ڸ� ȣ���� ���� ����.
		// �ֳĸ� �Ҹ��ڸ� �� ���� ���� �����̴�.
	{
	}

};
template <typename T>
struct Transparency_template : T
{
	// ���ø� �Ķ���͸� �����Ҽ� ���� assert�� Deco_Shape�� ������
	static_assert(is_base_of< Deco_Shape, T>::value, "Template argument must be a Shape");

	uint8_t transparency;
	string str() const override
	{
		return string{ T::str() + " has transparency " + to_string(transparency) };
	}
	Transparency_template(){}
	Transparency_template(const uint8_t _transparency)
		: transparency{_transparency}
	{}

	template<typename...Args>
	Transparency_template(const uint8_t _transparency, Args ...args)
		: T(std::forward<Args>(args)...), transparency{ _transparency }
	{
	}
};