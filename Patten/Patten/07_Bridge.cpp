#include "07_Bridge.h"

// bridge_Person 내부의 (클래스, 구조체) 정의
struct bridge_Person::PersonImpl
{
	void greet(bridge_Person* p);
};
void bridge_Person::PersonImpl::greet(bridge_Person* p)
{
	cout << p->name + " : hello" << endl;
}

bridge_Person::bridge_Person()
	: impl(new PersonImpl)
{
}
bridge_Person::~bridge_Person()
{
	delete impl;
}
void bridge_Person::greet()
{
	impl->greet(this);
}

void bridge_main()
{
	// 구현부를 포인터로 참조하여 실행
	bridge_Person p;
	p.name = "john";
	p.greet();

	//브릿지 : 클래스를 참조값으로 넘겨 구현부 실행
	RasterRenderer rr;
	Circle raster_circle{ rr,5,5,5 };
	raster_circle.draw();
	// 브릿지 = RasterRenderer
	VectorRenderer vr;
	Circle vector_circle{ vr,5,5,5 };
	vector_circle.draw();
	// 브릿지 = VectorRenderer
}