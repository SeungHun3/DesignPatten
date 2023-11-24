#include <iostream>
#include "Solid_Patten.h"
#include "02_Builder.h"
int main()
{
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

	// builder
	
	// �ܼ� ����
	HtmlBuilder simplebuilder{ "ul" };
	simplebuilder.add_Simple_child("li", "hello");
	simplebuilder.add_Simple_child("li", "world");
	cout << simplebuilder.str() << endl;

	// �帧�� ����
	HtmlBuilder flowbuilder{ "ul" };
	flowbuilder.add_Flow_child("li", "hello").add_Flow_child("li", "wolrd");
	cout << flowbuilder.str() << endl;
	// ���� ������Ű��
	return 0;
}