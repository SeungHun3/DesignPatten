#pragma once
#include <iostream>

using namespace std;
void singleton_main();

// 전역객체로서의 싱글턴 : 한번만 인스턴스화


struct Database
{
	int a;
	Database()
	:a(0)
	{}
};
// 의도하지 않은 방식으로 객체를 하나 더 생성할 수 있게 된다

// => 전역객체의 사용
//static Database database{};
// 문제점 : 아직 초기화 되지 않았을때 호출될 수 있음

// 전역함수를 사용하여 객체 리턴
inline Database& get_database()
{
	static Database database;
	return database;
}
// 문제점 : 다른 싱글턴을 참조시 소멸자에서 크래시 가능성높음
// 인스턴스의 추가생성을 막을 수가 없음


// 생성자를 막고, 유일하게 하나만 존재하는 인스턴스를 리턴하는 함수를 구현한다
struct SingleDatabase
{
public:
	int a;

protected:
	SingleDatabase()
		:a(0)
	{
	}
public:
	static SingleDatabase& get()
	{
		static SingleDatabase singleDatabase;
		return singleDatabase;
	}
	// 객체 전체가 아닌 포인터만 static으로 존재
	static SingleDatabase& heapget()
	{
		static SingleDatabase* heap_singleDatabase = new SingleDatabase();
		return *heap_singleDatabase;
	}

	SingleDatabase(SingleDatabase const&) = delete; // 복사 생성자 삭제
	SingleDatabase(SingleDatabase&&) = delete;		// 이동 생성자 삭제
	SingleDatabase& operator=(SingleDatabase const&) = delete;   // 복사 대입 연산자 삭제
	SingleDatabase& operator=(SingleDatabase&&) = delete;		 // 이동 대입 연산자 삭제

};
/*
* heapget 함수
* 
코드(텍스트) 영역:
heapget 함수의 기계어 코드가 저장된다. 이 코드는 프로그램이 실행될 때 CPU에 의해 실행된다.

전역 변수 영역:
heap_singleDatabase라는 정적(local static) 변수가 선언되고 초기화된다. 이 변수는 함수 내부에서 정적으로 할당되어 있어 프로그램의 수명 동안 메모리에 유지된다.
해당 변수는 힙에 SingleDatabase 객체를 가리키는 포인터를 저장한다.

힙(Heap) 영역:
new SingleDatabase()를 통해 힙에 동적으로 SingleDatabase 객체가 생성된다.
이 객체의 메모리 주소는 heap_singleDatabase에 저장된 포인터에 할당된다.

스택(Stack) 영역:
함수가 호출될 때마다 해당 함수의 로컬 변수 및 매개변수가 스택에 할당된다. 하지만 여기에서는 스택에 직접적으로 함수와 관련된 로컬 변수가 없다.

데이터(Data) 영역:
heap_singleDatabase는 데이터 영역에 저장되는 변수이다. 여기에는 정적 변수들이 저장된다.

힙 영역 (SingleDatabase 객체):
heap_singleDatabase가 가리키는 메모리 위치에 있는 힙에 할당된 SingleDatabase 객체가 있다.
return *heap_singleDatabase; 구문에서 객체에 대한 참조가 반환된다.

프로그램 종료까지 살아있어 소멸자의 호출이 필요없다
참조대신 포인터를 사용해 생성자가 호출되지 않게 한다
메모리 누수가 없다

멀티 스레드의 안정성 : 두개의 스레드가 동시에 호출되어도 두번생성되지 않는다 but c++11 이전버전은 이중검증 락킹을 하여 생성자 보호를 해야한다
*/