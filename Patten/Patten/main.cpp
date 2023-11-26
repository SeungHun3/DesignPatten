#include "01_Soild_main.h"
#include "02_Builder_main.h"
#include "03_Factory_main.h"

int main()
{
	//Solid_main();
	//Builder_main();
	Factory_main();
	auto drink_factory = make_unique<DrinkFactory>();
	auto tea = drink_factory->make_drink("hot_tea");


	return 0;
}