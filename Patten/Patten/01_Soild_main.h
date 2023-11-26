#pragma once
#include <iostream>
#include "01_Solid_Patten.h"

void Solid_main()
{
	// 01. Solid Patten
	// SRP
	Journal j{ "Dirary" };
	j.add("i win");
	j.add("rainy day");

	// OCP
	Product apple{ "Apple", Color::Green, Size::Small };
	Product tree{ "Tree", Color::Green, Size::Large };
	Product house{ "House", Color::Blue, Size::Large };

	vector<Product*> all{ &apple, &tree, &house };
	BetterFilter bf;
	ColorSpecification green(Color::Green);

	auto green_things = bf.filter(all, green);
	for (auto& x : green_things)
	{
		cout << x->name << " is green" << endl;
	}


}