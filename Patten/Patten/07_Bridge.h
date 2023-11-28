#pragma once
#include <iostream>

using namespace std;
void bridge_main();

// Pimple : pointer to implement == �����θ� �����ͷ� ����

// Ŭ���� �����θ� ���� �� �ִ�
// ���̳ʸ� ȣȯ�� ������ ����
// �����η� ���� Ŭ���̾�Ʈ���� �ʿ���� ����� ������� �ʾƵ� �ȴ�

struct bridge_Person
{
	string name;
	void greet(); // ����ü ������ Ŭ���� PersonImpl�� greet�Լ��� ��� ����
	
	bridge_Person();
	~bridge_Person();

	struct PersonImpl; // bridge_Person Ŭ������ �����θ� PersonImpl�� ��������ϴ� �ǵ�
	PersonImpl* impl; // PersonImpl ���漱�� �� ���� Ŭ������ cpp���Ͽ� �����ϴ� ���� �ٽ�
};

// bridge example
// 
// Renderer �������̽�
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

// Renderer �긴���� �̿��� Shape ����
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

//Shape �� ������
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