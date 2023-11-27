#pragma once
#include <iostream>

using namespace std;
void singleton_main();

// ������ü�μ��� �̱��� : �ѹ��� �ν��Ͻ�ȭ


struct Database
{
	int a;
	Database()
	:a(0)
	{}
};
// �ǵ����� ���� ������� ��ü�� �ϳ� �� ������ �� �ְ� �ȴ�

// => ������ü�� ���
//static Database database{};
// ������ : ���� �ʱ�ȭ ���� �ʾ����� ȣ��� �� ����

// �����Լ��� ����Ͽ� ��ü ����
inline Database& get_database()
{
	static Database database;
	return database;
}
// ������ : �ٸ� �̱����� ������ �Ҹ��ڿ��� ũ���� ���ɼ�����
// �ν��Ͻ��� �߰������� ���� ���� ����


// �����ڸ� ����, �����ϰ� �ϳ��� �����ϴ� �ν��Ͻ��� �����ϴ� �Լ��� �����Ѵ�
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
	// ��ü ��ü�� �ƴ� �����͸� static���� ����
	static SingleDatabase& heapget()
	{
		static SingleDatabase* heap_singleDatabase = new SingleDatabase();
		return *heap_singleDatabase;
	}

	SingleDatabase(SingleDatabase const&) = delete; // ���� ������ ����
	SingleDatabase(SingleDatabase&&) = delete;		// �̵� ������ ����
	SingleDatabase& operator=(SingleDatabase const&) = delete;   // ���� ���� ������ ����
	SingleDatabase& operator=(SingleDatabase&&) = delete;		 // �̵� ���� ������ ����

};
/*
* heapget �Լ�
* 
�ڵ�(�ؽ�Ʈ) ����:
heapget �Լ��� ���� �ڵ尡 ����ȴ�. �� �ڵ�� ���α׷��� ����� �� CPU�� ���� ����ȴ�.

���� ���� ����:
heap_singleDatabase��� ����(local static) ������ ����ǰ� �ʱ�ȭ�ȴ�. �� ������ �Լ� ���ο��� �������� �Ҵ�Ǿ� �־� ���α׷��� ���� ���� �޸𸮿� �����ȴ�.
�ش� ������ ���� SingleDatabase ��ü�� ����Ű�� �����͸� �����Ѵ�.

��(Heap) ����:
new SingleDatabase()�� ���� ���� �������� SingleDatabase ��ü�� �����ȴ�.
�� ��ü�� �޸� �ּҴ� heap_singleDatabase�� ����� �����Ϳ� �Ҵ�ȴ�.

����(Stack) ����:
�Լ��� ȣ��� ������ �ش� �Լ��� ���� ���� �� �Ű������� ���ÿ� �Ҵ�ȴ�. ������ ���⿡���� ���ÿ� ���������� �Լ��� ���õ� ���� ������ ����.

������(Data) ����:
heap_singleDatabase�� ������ ������ ����Ǵ� �����̴�. ���⿡�� ���� �������� ����ȴ�.

�� ���� (SingleDatabase ��ü):
heap_singleDatabase�� ����Ű�� �޸� ��ġ�� �ִ� ���� �Ҵ�� SingleDatabase ��ü�� �ִ�.
return *heap_singleDatabase; �������� ��ü�� ���� ������ ��ȯ�ȴ�.

���α׷� ������� ����־� �Ҹ����� ȣ���� �ʿ����
������� �����͸� ����� �����ڰ� ȣ����� �ʰ� �Ѵ�
�޸� ������ ����

��Ƽ �������� ������ : �ΰ��� �����尡 ���ÿ� ȣ��Ǿ �ι��������� �ʴ´� but c++11 ���������� ���߰��� ��ŷ�� �Ͽ� ������ ��ȣ�� �ؾ��Ѵ�
*/