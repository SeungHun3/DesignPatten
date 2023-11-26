#pragma once
#include<iostream>
#include <vector>
#include <string>

using namespace std;

// 단순 빌더, 흐름식 빌더
struct HtmlBuilder;

struct HtmlElement
{
	string name;
	string text;
	vector<HtmlElement> elements;
	const size_t inded_size = 2;

	// Builder로만 생성 강제
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
	// 단순빌더
	void add_Simple_child(string child_name, string child_text)
	{
		HtmlElement e{ child_name,child_text };
		root.elements.emplace_back(e); // 객체생성하지 않고 직접 집어넣기
	}
	// 흐름식 빌더
	HtmlBuilder& add_Flow_child(string child_name, string child_text)
	{
		HtmlElement e{ child_name,child_text };
		root.elements.emplace_back(e);
		return *this; // 본인 리턴
	}

	string str() { return root.str(); }

};


// 그루비 스타일 빌더
struct Tag
{
	string name;
	string text;
	vector<Tag> children;
	vector<pair<string, string>> attributes;


	// 일반함수를 통한 연산자 오버로딩 == 이 일반함수는 멤버함수가 아닌 전역함수로써 멤버접근에 불가함 따라서 friend 선언을 꼭 해줘야함
	// 오버로딩 사용법 https://showmiso.tistory.com/32
	Tag operator+(const Tag& tag/*Right*/)
	{
		string test_name = name + tag.name;
		return Tag(test_name, ""); // 임시객체 생성 후 반환시 삭제 // 삭제 원치 않는다면 Tag&로 *this 반환
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
		: Tag{"p", text} // 명시적
	{

	}
	P(initializer_list<Tag> children)
		: Tag("p",children) // 자식개체가 들어갈 수 있으니 암시적
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


// 컴포지트 빌더 == 객체 하나 생성시 복수의 빌더가 사용되는 경우 (언리얼 eos 시스템 구조)

class PersonAddressBuilder;
class PersonJobBuilder;
class PersonBuilder;
// PersonBulider 통해 객체 생성하기
class Person
{
public:
	//주소
	string street_address, post_code, city;
	//직업
	string company_name, position;
	int annual_income = 0;


	// 생성사 구분이유: 새로운 객체생성은 builder통해, 정보 담는 
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

// PersonBuilder 의 Person객체를 참조받음
class PersonBuilderBase
{
protected:
	Person& person; // 생성중인 객체에 대한 참조만 가질 뿐 생성된 객체는 가지지 않는다
	
	explicit PersonBuilderBase(Person& person)
		:person{ person }
	{

	}
public:
	/*
	operator Person() 함수는 타입 변환 연산자로서, PersonBuilderBase 클래스의 객체를 Person 클래스로 암시적으로 변환해주는 함수
	PersonBuilderBase builder(person); // person은 PersonBuilder를 통한 PersonBuilderBase의 생성자에서 전달된 Person 객체를 가리킴
	==> Person person_instance = builder; // 이 순간 operator Person() 함수가 호출되어 PersonBuilderBase를 Person으로 변환
	*/
	operator Person()
	{
		// std::move 함수 : 주어진 객체를 다른 객체로 이동(객체의 소유권을 전환)시키는데 사용 (필요한 복사를 피하고 성능을 향상시킴)
		return move(person); 
	}

	// 하위빌더의 인터페이스를 리턴
	PersonAddressBuilder lives() const; // return PersonAddressBuilder{ person };
	PersonJobBuilder works() const;		// return PersonJobBuilder{ person };
	// 하위 빌더에서 각각 주소, 직업정보를 초기화
};

// 생성하고 있는 객체 자체
class PersonBuilder :public PersonBuilderBase
{
	Person p; // 생성중인 객체
	
public:
	PersonBuilder() 
		: PersonBuilderBase{p}
	{
	
	}
};

//PersonBuilderBase 에서 파생된 각각의 빌더들 호출 
// 하위빌더 호출할때마다 person에 대한 참조만 가진채로 각각의 다른빌더들이 값을 채워주는 형식 live().at().with_
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