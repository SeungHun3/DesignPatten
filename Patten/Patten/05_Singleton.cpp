#include "05_Singleton.h"



void singleton_main()
{
    // ������ �ν��Ͻ� ���
    SingleDatabase& db = SingleDatabase::get();
    SingleDatabase& pdb = SingleDatabase::heapget();
    pdb.a = 3;
    SingleDatabase& tempdb = SingleDatabase::heapget();
    cout << tempdb.a << endl;
    /*
    SingleDatabase db2{db}; // ���� ������ ȣ�� (������ ����)
    SingleDatabase db3{std::move(db)}; // �̵� ������ ȣ�� (������ ����)
    SingleDatabase db4;
    db4 = db; // ���� ���� ������ ȣ�� (������ ����)
    SingleDatabase db5;
    db5 = std::move(db); // �̵� ���� ������ ȣ�� (������ ����)
    */

}
