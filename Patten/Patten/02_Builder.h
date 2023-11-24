#pragma once
#include<iostream>
#include <vector>
#include <string>

using namespace std;

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
		: Tag{"p", text}
	{

	}
	P(initializer_list<Tag> children)
		: Tag("p",children)
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