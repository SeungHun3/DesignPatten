#pragma once
#include <iostream>
#include <string>

using namespace std;
void decorator_main();

// 데커레이터 : 열림-닫힘 OCP 원칙 준수
// 기존코드 수정x , 새로운 기능추가

struct Deco_Shape
{
	virtual string str() const = 0; // 특정 도형의 상태를 텍스트로 나타내기위해
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

// 동적 데커레이터 : 참조를 주고 받으며 런타임에 동적으로 합성하여 유연성있는 방식
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

// 정적 데커레이터 : 컴파일 시점에 추가기능이 합성, 나중에 수정할 수 없음
// 위의 코드에서 redcircle 의 resize함수를 호출 못함
// =>MixIn 상속 이용 : 템플릿을 통한 다중 상속 합성


template <typename T> 
struct Color_template : T
{
	// 템플릿 파라미터를 제약할수 없어 assert로 Deco_Shape을 강제함 string str() override 사용위해
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
	// 문제점 : 제일 마지막의 생성자만 호출되어 여러 데커레이션을 한번에 초기화할수가 없다 


	// 가변길이 템플릿 note.text  143줄
	// 생성자에 여러 인자를 담아(생성순서 지키며) 호출 => 상속구조로 인자를 올려주고 빼주며 부모생성자를 차례로 호출시킴
	template <typename...Args>
	Color_template(const string& _color, Args ...args)
		: T(std::forward<Args>(args)...), color{ _color }
		// 여기서 베이스 클래스의 소멸자를 호출할 수는 없다.
		// 왜냐면 소멸자를 알 수가 없기 때문이다.
	{
	}

};
template <typename T>
struct Transparency_template : T
{
	// 템플릿 파라미터를 제약할수 없어 assert로 Deco_Shape을 강제함
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