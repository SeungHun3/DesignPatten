#include "07_Bridge.h"

// bridge_Person ������ (Ŭ����, ����ü) ����
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
	// �����θ� �����ͷ� �����Ͽ� ����
	bridge_Person p;
	p.name = "john";
	p.greet();

	//�긴�� : Ŭ������ ���������� �Ѱ� ������ ����
	RasterRenderer rr;
	Circle raster_circle{ rr,5,5,5 };
	raster_circle.draw();
	// �긴�� = RasterRenderer
	VectorRenderer vr;
	Circle vector_circle{ vr,5,5,5 };
	vector_circle.draw();
	// �긴�� = VectorRenderer
}