#pragma once
#include<iostream>
#include <vector>
#include <string>

using namespace std;

struct HtmlElement
{
	string name;
	string text;
	vector<HtmlElement> elements;

	HtmlElement() {}
	HtmlElement(const string& name, const string& text)
		: name{ name }
		, text{ text }
	{

	}
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