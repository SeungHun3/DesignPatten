#pragma once
#include<iostream>
#include <fstream>
#include <vector>
#include <string>
//#include <boost/lexical_cast.hpp>
using namespace std;


// SRP : 단일 책임원칙 = manager구현
struct Journal
{
	string title;

	vector<string> entries;

	explicit Journal(const string& title) 
		: title{ title } // string 중괄호 생성자
	{
	}

	void add(const string& entry)
	{
		static int count = 1;
		entries.push_back(to_string(count++) + ":" + entry);
	}

};
// 클래스들의 저장을 맡는 Manager을 구현한다
struct PersistenceManager
{
	static void save(const Journal& j, const string& filename)
	{
		ofstream ofs(filename);
		for (auto& s : j.entries)
		{
			ofs << s << endl;
		}
	}
};

// OCP : 열림닫힘 원칙 == (순수 가상함수) 확장에는 열려있지만 수정에는 닫혀있다

enum class Color{Red, Green, Blue};
enum class Size{Small, Medium, Large};

struct Product
{
	string name;
	Color color;
	Size size;
};

template <typename T> struct Specificaton
{
	virtual bool is_satisfied(T* item) = 0;
};
// 확장
struct ColorSpecification : Specificaton<Product>
{
	Color color;
	explicit ColorSpecification(const Color color)
		:
		color{ color }
	{

	}
	bool is_satisfied(Product* item) override
	{
		return item->color == color;
	}
};

template <typename T> struct Filter
{
	virtual vector<T*> filter(vector<T*> items, Specificaton<T>& spec) = 0;
};
// 확장
struct BetterFilter : Filter<Product>
{
	vector<Product*> filter(vector<Product*> items, Specificaton<Product>& spec) override
	{
		vector<Product*> result;
		for (auto& p : items)
		{
			if (spec.is_satisfied(p))
			{
				result.push_back(p);
			}
		}
		return result;
	}
};