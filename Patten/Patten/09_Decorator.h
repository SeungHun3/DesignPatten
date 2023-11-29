#pragma once
#include <iostream>
#include <string>
#include <functional>

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

// �Լ��� ��Ŀ������
// �α׸� ������ ��Ȳ�� �´ٸ� => �α�������Ʈ�� ���ٸ� �ѱ�

struct Logger
{
	function<void()> func;
	string name;
	Logger(const function<void()>& _func, const string& _name)
		: func{ _func }
		, name{ _name }
	{
		cout << "Create Logger : " << name << endl;
	}
	~Logger() 
	{
		cout << "Delete Logger : " << name << endl;
	}
	void operator()() const //Logger myLogger; �� ������ myLogger();�� ȣ��
	{
		cout << "Enter : " << name << endl;
		func();
		cout << "Exit : " <<name<< endl;
	}
};

// ���ø��� �̿��� �ΰ� �����
// ���ø� Ŭ���� ����
template<typename Func>
struct Logger2
{
	Func func; // function���� �������� �ʰ� ���ڷ� ���޹���
	string name;
	Logger2(const Func& _func, const string& _name)
		: func{ _func }
		, name{ _name }
	{
		cout << "Create Logger2 : " << name << endl;
	}
	~Logger2()
	{
		cout << "Delete Logger2 : " << name << endl;
	}
	void operator()() const 
	{
		cout << "Enter : " << name << endl;
		func();
		cout << "Exit : " << name << endl;
	}
};
// ������ ���� ���� �� ������ Ư��Ŭ������ �����ʾƵ� �Ǵ� ȣ���Լ� ����
template <typename Func>
auto make_logger2(Func _func, const string& _name)
{
	return Logger2<Func>{_func, _name};
}

// ���� �Լ��� �αױ���� �߰��ϴ� ��� ...���� �Ű������� Args�� ������
// int add(int a, int b){return a+b}; ��� �Լ��� �ִٸ�
//  R    ... ���� ���� ... �� int, int �̴�
template <typename R, typename... Args> 
struct Logger3
{
	function<int(int, int)> addFunction = [](int a, int b) { return a + b; };
	function<R(Args...)> func;
	string name;

	Logger3(function<R(Args...)> _func, const string& _name)
		: func{ _func }
		, name{ _name }
	{
		cout << "Create Logger3" << endl;
	}
	R operator() (Args ...args)
	{
		cout << "Enter : " << name << endl;
		/*int*/ R result = func(args...); /*�Լ����� �� ��� ��*/
		cout << "Exit : " << name << endl;
		return result;
	}

	~Logger3()
	{
		cout << "Delete Logger3" << endl;
	}
};
template <typename R, typename ... Args>
auto make_logger3(R(*func)(Args...),const string& name)
{
	// �Լ��� return �ڷ��� int = R
	// �Լ��� �ּ� *func
	// �Լ��� �Ű����� ... = int, int
	return Logger3<R,Args...>(function<R(Args...)>(func), name);
	//           ���ø� �ڷ���          ȣ������1          ȣ������2
}
inline int add(int a, int b)
{
	cout << "add �Լ����� : " << a + b << endl;;
	return a + b;
}