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
	HtmlBuilder& add_Flow_child(string child_name, string child_text)
	{
		HtmlElement e{ child_name,child_text };
		root.elements.emplace_back(e);
		return *this; // ���� ����
	}

	string str() { return root.str(); }

};