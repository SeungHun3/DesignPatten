#pragma once
#include<iostream>
#include <vector>
#include <string>

using namespace std;

// �ܼ� ����, �帧�� ����
struct HtmlBuilder;

struct HtmlElement
{
	string name;
	string text;
	vector<HtmlElement> elements;
	const size_t inded_size = 2;

	// Builder�θ� ���� ����
	static unique_ptr<HtmlBuilder> build(const string& root_name)
	{
		return make_unique<HtmlBuilder>(root_name);
	}

protected:
	HtmlElement() {}
	HtmlElement(const string& name, const string& text)
		: name{ name }
		, text{ text }
	{

	}
	friend struct HtmlBuilder;

public:
	string str(int indent = 0)
	{
		string result = string(indent, ' ') + "<" + name + ">\n";
		if (!text.empty())
		{
			result += string(indent + 2, ' ') + text + "\n";
		}

		for (auto& e : elements)
		{
			result += e.str(indent + 2);
		}

		result += string(indent, ' ') + "</" + name + ">\n";

		return result;
	}
};

struct HtmlBuilder
{

	HtmlElement root;

	HtmlBuilder(string root_name) { root.name = root_name; }
	// �ܼ�����
	void add_Simple_child(string child_name, string child_text)
	{
		HtmlElement e{ child_name,child_text };
		root.elements.emplace_back(e); // ��ü�������� �ʰ� ���� ����ֱ�
	}
	// �帧�� ����
	HtmlBuilder& add_Flow_child(string child_name, string child_text)
	{
		HtmlElement e{ child_name,child_text };
		root.elements.emplace_back(e);
		return *this; // ���� ����
	}

	string str() { return root.str(); }

};


// �׷�� ��Ÿ�� ����
struct Tag
{
	string name;
	string text;
	vector<Tag> children;
	vector<pair<string, string>> attributes;


	// �Ϲ��Լ��� ���� ������ �����ε� == �� �Ϲ��Լ��� ����Լ��� �ƴ� �����Լ��ν� ������ٿ� �Ұ��� ���� friend ������ �� �������
	// �����ε� ���� https://showmiso.tistory.com/32
	Tag operator+(const Tag& tag/*Right*/)
	{
		string test_name = name + tag.name;
		return Tag(test_name, ""); // �ӽð�ü ���� �� ��ȯ�� ���� // ���� ��ġ �ʴ´ٸ� Tag&�� *this ��ȯ
	}

	friend ostream& operator<<(ostream & os/*Left*/, const Tag& tag/*Right*/)
	{
		os << "<" << tag.name;

		for (const auto& attr : tag.attributes)
		{
			os << " " << attr.first << "=\"" << attr.second << "\"";
		}

		if (tag.children.empty() && tag.text.empty())
		{
			os << "/>";
		}
		else
		{
			os << ">";

			for (const auto& child : tag.children)
			{
				os << child;
			}

			os << tag.text << "</" << tag.name << ">";
		}

		return os;
	}

protected:
	Tag(const string& name, const string& text)
		: name{name}
		, text{text}
	{

	}

	Tag(const string& name, const vector<Tag>& children)
		: name{ name }
		, children{ children }
	{

	}

};

struct P : Tag
{

	explicit P(const string& text)
		: Tag{"p", text} // �����
	{

	}
	P(initializer_list<Tag> children)
		: Tag("p",children) // �ڽİ�ü�� �� �� ������ �Ͻ���
	{

	}
};

struct IMG : Tag
{
	explicit IMG(const string& url)
		:Tag{ "img","" }
	{
		attributes.emplace_back("src", url);
	}

};


// ������Ʈ ���� == ��ü �ϳ� ������ ������ ������ ���Ǵ� ��� (�𸮾� eos �ý��� ����)

class PersonAddressBuilder;
class PersonJobBuilder;
class PersonBuilder;
// PersonBulider ���� ��ü �����ϱ�
class Person
{
public:
	//�ּ�
	string street_address, post_code, city;
	//����
	string company_name, position;
	int annual_income = 0;


	// ������ ��������: ���ο� ��ü������ builder����, ���� ��� 
private:
	Person(){}
public:
	static PersonBuilder create(); // return PersonBuilder{};

	Person(Person&& other)
		: street_address{ move(other.street_address) },
		post_code{ move(other.post_code) },
		city{ move(other.city) },
		company_name{ move(other.company_name) },
		position{ move(other.position) },
		annual_income{ other.annual_income }
	{
	}

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

	friend class PersonBuilder;
	friend class PersonAddressBuilder;
	friend class PersonJobBuilder;
};

// PersonBuilder �� Person��ü�� ��������
class PersonBuilderBase
{
protected:
	Person& person; // �������� ��ü�� ���� ������ ���� �� ������ ��ü�� ������ �ʴ´�
	
	explicit PersonBuilderBase(Person& person)
		:person{ person }
	{

	}
public:
	/*
	operator Person() �Լ��� Ÿ�� ��ȯ �����ڷμ�, PersonBuilderBase Ŭ������ ��ü�� Person Ŭ������ �Ͻ������� ��ȯ���ִ� �Լ�
	PersonBuilderBase builder(person); // person�� PersonBuilder�� ���� PersonBuilderBase�� �����ڿ��� ���޵� Person ��ü�� ����Ŵ
	==> Person person_instance = builder; // �� ���� operator Person() �Լ��� ȣ��Ǿ� PersonBuilderBase�� Person���� ��ȯ
	*/
	operator Person()
	{
		// std::move �Լ� : �־��� ��ü�� �ٸ� ��ü�� �̵�(��ü�� �������� ��ȯ)��Ű�µ� ��� (�ʿ��� ���縦 ���ϰ� ������ ����Ŵ)
		return move(person); 
	}

	// ���������� �������̽��� ����
	PersonAddressBuilder lives() const; // return PersonAddressBuilder{ person };
	PersonJobBuilder works() const;		// return PersonJobBuilder{ person };
	// ���� �������� ���� �ּ�, ���������� �ʱ�ȭ
};

// �����ϰ� �ִ� ��ü ��ü
class PersonBuilder :public PersonBuilderBase
{
	Person p; // �������� ��ü
	
public:
	PersonBuilder() 
		: PersonBuilderBase{p}
	{
	
	}
};

//PersonBuilderBase ���� �Ļ��� ������ ������ ȣ�� 
// �������� ȣ���Ҷ����� person�� ���� ������ ����ä�� ������ �ٸ��������� ���� ä���ִ� ���� live().at().with_
class PersonAddressBuilder :public PersonBuilderBase
{
	typedef PersonAddressBuilder Self;
public:
	explicit PersonAddressBuilder(Person& person)
		: PersonBuilderBase{ person }
	{
	}

	Self& at(std::string street_address)
	{
		person.street_address = street_address;
		return *this;
	}

	Self& with_postcode(std::string post_code)
	{
		person.post_code = post_code;
		return *this;
	}

	Self& in(std::string city)
	{
		person.city = city;
		return *this;
	}
};

class PersonJobBuilder : public PersonBuilderBase
{
	typedef PersonJobBuilder Self;
public:
	explicit PersonJobBuilder(Person& person)
		: PersonBuilderBase{ person }
	{
	}

	Self& at(std::string company_name)
	{
		person.company_name = company_name;
		return *this;
	}

	Self& as_a(std::string position)
	{
		person.position = position;
		return *this;
	}

	Self& earning(int annual_income)
	{
		person.annual_income = annual_income;
		return *this;
	}
};