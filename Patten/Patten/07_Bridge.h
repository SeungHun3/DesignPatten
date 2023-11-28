#pragma once
#include <iostream>

using namespace std;
void bridge_main();

// Pimple : pointer to implement == 구현부를 포인터로 참조

// 클래스 구현부를 감출 수 있다
// 바이너리 호환성 보증이 쉽다
// 구현부로 인해 클라이언트에서 필요없는 헤더를 사용하지 않아도 된다

struct bridge_Person
{
	string name;
	void greet(); // 구조체 내부의 클래스 PersonImpl의 greet함수에 제어를 위임
	
	bridge_Person();
	~bridge_Person();

	struct PersonImpl; // bridge_Person 클래스의 구현부를 PersonImpl에 숨기고자하는 의도
	PersonImpl* impl; // PersonImpl 전방선언 후 구현 클래스를 cpp파일에 정의하는 것이 핵심
};

// bridge example
// 
// Renderer 인터페이스
struct Renderer
{
	virtual void render_circle(float x, float y, float radius) = 0;
};
struct VectorRenderer : Renderer
{
	void render_circle(float x, float y, float radius) override
	{
		cout << "Vector Render" << endl;
	}
};
struct RasterRenderer : Renderer
{
	void render_circle(float x, float y, float radius) override
	{
		cout << "Raster Render" << endl;
	}
};

// Renderer 브릿지를 이용한 Shape 구현
struct Shape
{
protected:
	Renderer& renderer;
	Shape(Renderer& _renderer)
		:renderer{ _renderer }
	{

	}
public:
	virtual void draw() = 0;
	virtual void resize(float factor) = 0;
};

//Shape 의 구현부
struct Circle : Shape
{
	float x, y, radius;

	void draw() override
	{
		renderer.render_circle(x, y, radius);
	}
	void resize(float factor) override
	{
		radius *= factor;
	}

	Circle(Renderer& _renderer, float _x, float _y, float _radius)
		: Shape{ _renderer }
		, x{ _x }
		, y{ _y }
		, radius{ _radius }
	{
	}
};