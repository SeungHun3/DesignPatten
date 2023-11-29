#include "09_Decorator.h"



void decorator_main()
{
	// 동적 데커레이터
	{
		Deco_Circle circle{ 0.5f };
		Deco_Square square;
		// 색상 추가
		ColoredShape red_circle{ circle,"red" };
		// 투명도 추가
		TransparentShape trans_circle{ red_circle ,15 };
		TransparentShape trans_square{ square ,10 };

		cout << trans_circle.str() << endl;
		cout << trans_square.str() << endl;
		cout << "================================================" << endl;
	}

	// 정적 데커레이터 : 단점 다이아몬드 문제가 발생할 수 있음
	{
		Color_template<Transparency_template<Deco_Circle>> templateShape{ "blue" };
		templateShape.radius = 0.1f;
		templateShape.transparency = 10;
		templateShape.resize(2);
		cout << templateShape.str() << endl;

		Transparency_template<Deco_Square> temp;
		temp.transparency = 50;
		cout << temp.str() << endl;
		// 문제점 : 제일 마지막의 생성자만 호출되어 여러 데커레이션을 한번에 초기화할수가 없다 

		// 가변길이 템플릿을 이용한 해결
		Color_template<Transparency_template<Deco_Circle>> argtemplate{ "green",20,2.f };
		cout << argtemplate.str() << endl;
		cout << "================================================" << endl;
	}



	// 함수형 데커레이터
	{
		{
			Logger mylog([]() {cout << "Hello" << endl; }, "mylog"); //=> 함수를 담아 생성을 한 후
			mylog(); // 호출시킴
		}
		Logger([]() {cout << "Hello" << endl; }, "temp")();

		//템플릿 생성자를 통한 호출
		auto myLambda = []() { cout << "Hello" << endl; };
		Logger2<decltype(myLambda)>(myLambda, "myLambda")();

		// 템플릿 함수를 통한 호출
		{
			auto template_func = make_logger2([]() {cout << "Hello" << endl; }, "template_func");
			template_func();
		}
		make_logger2([]() {cout << "Hello" << endl; }, "template_temp")();

		// 다른 함수에 로그기능을 추가
		{
			auto logged_add = make_logger3(add, "Add_Func");
			int result = logged_add(3, 4);
		}
		{
			make_logger3(add, "Add_temp")(5, 4);
		}
	}
}
