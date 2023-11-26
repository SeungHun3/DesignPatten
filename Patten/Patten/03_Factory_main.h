#pragma once
#include "03_factory.h"

using namespace std;
#define PI 3.14f

static void Factory_main()
{
	Point p = Point::NewPolar(5.f, 3.14f);
	p.cout_x_y();
	Point p2 = outter_Factory::NewCartesian(5.f, 1.f);
	p2.cout_x_y();
	Point p3 = Point::Factory_inner.NewCartesian(4.f, 2.f);
	p3.cout_x_y();

	//auto d = make_drink("tea"); 
	//auto drink_factory = make_unique<DrinkFactory>();
	//auto tea = drink_factory->make_drink("hot_tea");

}