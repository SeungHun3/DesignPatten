#pragma once
#include <iostream>
#include "02_Builder.h"


static void Builder_main()
{
	// 02. builder

	//// �ܼ� ����
	//HtmlBuilder simplebuilder{ "ul" };
	//simplebuilder.add_Simple_child("li", "hello");
	//simplebuilder.add_Simple_child("li", "world");
	//cout << simplebuilder.str() << endl;
	//
	//// �帧�� ����
	//HtmlBuilder flowbuilder{ "ul" };
	//flowbuilder.add_Flow_child("li", "hello").add_Flow_child("li", "wolrd");
	//cout << flowbuilder.str() << endl;

	// ���� ������Ű��
	HtmlBuilder static_builder = HtmlElement::build("ul")->add_Flow_child("li", "hello").add_Flow_child("li", "wolrd");
	cout << static_builder.str() << endl;


	// �׷�� ��Ÿ�� ����
	auto TagBuilder = P{ IMG{ "http:aaaa"} };
	cout << P{ IMG{ "http:aaaa"} } << endl;
	cout << TagBuilder << endl;

	// ������Ʈ ����
	Person p = Person::create()
		.lives().at("gangnam").with_postcode("5413").in("seoul")
		.works().as_a("mycompany").at("mycompany").earning(120);
	/* ���� ���� ��

	PersonBuilderBase�� Person���� ����ȯ �ɶ�

	���������� ����ȯ �Լ�
	 operator Person()
	{
		return move(person);
	}

	move�Լ� ���� person�� ������ ����(�̵���Ų) ���ο� Person ��ü(rValue)�� ������

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
	������ ȣ�� ��

	Person p �� ������ ���Կ���

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

	�� �̷����

	*/
}
