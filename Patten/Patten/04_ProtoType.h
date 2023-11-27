#pragma once
#include <iostream>

using namespace std;
void proto_main();

// 프로토타입 : 객체의 복제가 주요기능

struct Address
{
	string street, city;
	int suite;

	Address(const string& _street, const string& _city, const int _suite)
		: street{_street}
		, city{_city}
		, suite{_suite}
	{

	}
	Address(const Address& other)
		: street{ other.street },
		city{ other.city },
		suite{ other.suite }
	{
	}

	Address()
		: street{ "" },
		city{ "" },
		suite{ 0 }
	{
	}
};
struct Contact
{
	string name;
	Address *address;

public:
	Contact() 
		: name{""}, address(nullptr)
	{
	}
	Contact(string name, Address* address)
		: name{ name }, address{ address }
	{
		
	}
	// 여기서 복제 후 수정시 다른 객체가 사용하는 address도 수정된다
	// 중복방지 위해 복사생성자를 구현
	Contact(const Contact& other)
		: name{other.name}
		, address{new Address{*other.address}}
	{
	}
	~Contact()
	{
		delete address;
	}
	
	// 연산자 복제 직접 구현
	Contact& operator=(const Contact& other)
	{
		if (this == &other)
			return *this;
		name = other.name;
		address = other.address;
		return *this;
	}
	
	// 복제 매크로를 이용한 복사
	Contact* CLONE()
	{
		return new Contact{ *this };
	}
};


// 자주사용하는 여러 전역변수를 사용한 팩토리복제
struct EmployeeFactory
{
	static Contact main;
	static Contact aux;

	static unique_ptr<Contact> NewMainOfficeEmployee(string name, int suite)
	{
		return NewEmployee(name, suite, main);
	}

	static unique_ptr<Contact> NewAuxOfficeEmployee(string name, int suite)
	{
		return NewEmployee(name, suite, aux);
	}

private:
	static unique_ptr<Contact> NewEmployee(string name, int suite, Contact& proto)
	{
		auto result = make_unique<Contact>(proto);
		result->name = name;
		result->address->suite = suite;
		return result;
	}
};