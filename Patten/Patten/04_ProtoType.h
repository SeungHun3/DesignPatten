#pragma once
#include <iostream>

using namespace std;
void proto_main();

// ������Ÿ�� : ��ü�� ������ �ֿ���

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
	// ���⼭ ���� �� ������ �ٸ� ��ü�� ����ϴ� address�� �����ȴ�
	// �ߺ����� ���� ��������ڸ� ����
	Contact(const Contact& other)
		: name{other.name}
		, address{new Address{*other.address}}
	{
	}
	~Contact()
	{
		delete address;
	}
	
	// ������ ���� ���� ����
	Contact& operator=(const Contact& other)
	{
		if (this == &other)
			return *this;
		name = other.name;
		address = other.address;
		return *this;
	}
	
	// ���� ��ũ�θ� �̿��� ����
	Contact* CLONE()
	{
		return new Contact{ *this };
	}
};


// ���ֻ���ϴ� ���� ���������� ����� ���丮����
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