#include <iostream>
#include "01_Solid_Patten.h"
#include "02_Builder.h"
int main()
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

	// 02. builder
	
	//// ´Ü¼ø ºô´õ
	//HtmlBuilder simplebuilder{ "ul" };
	//simplebuilder.add_Simple_child("li", "hello");
	//simplebuilder.add_Simple_child("li", "world");
	//cout << simplebuilder.str() << endl;
	//
	//// Èå¸§½Ä ºô´õ
	//HtmlBuilder flowbuilder{ "ul" };
	//flowbuilder.add_Flow_child("li", "hello").add_Flow_child("li", "wolrd");
	//cout << flowbuilder.str() << endl;

	// ºô´õ °­Á¦½ÃÅ°±â
	HtmlBuilder static_builder = HtmlElement::build("ul")->add_Flow_child("li", "hello").add_Flow_child("li", "wolrd");
	cout << static_builder.str() << endl;


	// ±×·çºñ ½ºÅ¸ÀÏ ºô´õ
	auto TagBuilder =  P{ IMG{ "http:aaaa"} };
	cout << P{ IMG{ "http:aaaa"} } << endl;
	cout << TagBuilder << endl;




	return 0;
}