#include "03_Factory.h"



unique_ptr<HotDrink> make_drink(string type)
{
	unique_ptr<HotDrink> drink;
	if (type == "hot_tea")
	{
		drink = make_unique<Tea>();
		drink->prepare(200);
	}
	else if(type == "hot_coffee")
	{
		drink = make_unique<Coffee>();
		drink->prepare(50);
	}
	return drink;
}

void factory_main()
{
	Point p = Point::NewPolar(5.f, 3.14f);
	p.cout_x_y();
	Point p2 = outter_Factory::NewCartesian(5.f, 1.f);
	p2.cout_x_y();
	Point p3 = Point::Factory_inner.NewCartesian(4.f, 2.f);
	p3.cout_x_y();

	auto d = make_drink("tea"); 
	auto drink_factory = make_unique<DrinkFactory>();
	auto tea = drink_factory->make_drink("hot_tea");
}