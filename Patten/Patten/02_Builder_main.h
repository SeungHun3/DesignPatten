#pragma once
#include <iostream>
#include "02_Builder.h"


static void Builder_main()
{
	// 02. builder

	//// 단순 빌더
	//HtmlBuilder simplebuilder{ "ul" };
	//simplebuilder.add_Simple_child("li", "hello");
	//simplebuilder.add_Simple_child("li", "world");
	//cout << simplebuilder.str() << endl;
	//
	//// 흐름식 빌더
	//HtmlBuilder flowbuilder{ "ul" };
	//flowbuilder.add_Flow_child("li", "hello").add_Flow_child("li", "wolrd");
	//cout << flowbuilder.str() << endl;

	// 빌더 강제시키기
	HtmlBuilder static_builder = HtmlElement::build("ul")->add_Flow_child("li", "hello").add_Flow_child("li", "wolrd");
	cout << static_builder.str() << endl;


	// 그루비 스타일 빌더
	auto TagBuilder = P{ IMG{ "http:aaaa"} };
	cout << P{ IMG{ "http:aaaa"} } << endl;
	cout << TagBuilder << endl;

	// 컴포지트 빌더
	Person p = Person::create()
		.lives().at("gangnam").with_postcode("5413").in("seoul")
		.works().as_a("mycompany").at("mycompany").earning(120);
	/* 정보 담은 뒤

	PersonBuilderBase가 Person으로 형변환 될때

	직접구현된 형변환 함수
	 operator Person()
	{
		return move(person);
	}

	move함수 통해 person의 정보를 가진(이동시킨) 새로운 Person 객체(rValue)가 생성됨

	=>
	Person(Person&& other)
		: street_address{ move(other.street_address) },
		post_code{ move(other.post_code) },
		city{ move(other.city) },
		company_name{ move(other.company_name) },
		position{ move(other.position) },
		annual_income{ other.annual_income }
	{
	}
	생성자 호출 후

	Person p 에 대입할 대입연산

	Person& operator=(Person&& other)
	{
		if (this == &other)
			return *this;
		street_address = move(other.street_address);
		post_code = move(other.post_code);
		city = move(other.city);
		company_name = move(other.company_name);
		position = move(other.position);
		annual_income = other.annual_income;
		return *this;
	}

	이 이루어짐

	*/
}
