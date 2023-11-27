#include "05_Singleton.h"



void singleton_main()
{
    // 유일한 인스턴스 얻기
    SingleDatabase& db = SingleDatabase::get();
    SingleDatabase& pdb = SingleDatabase::heapget();
    pdb.a = 3;
    SingleDatabase& tempdb = SingleDatabase::heapget();
    cout << tempdb.a << endl;
    /*
    SingleDatabase db2{db}; // 복사 생성자 호출 (컴파일 오류)
    SingleDatabase db3{std::move(db)}; // 이동 생성자 호출 (컴파일 오류)
    SingleDatabase db4;
    db4 = db; // 복사 대입 연산자 호출 (컴파일 오류)
    SingleDatabase db5;
    db5 = std::move(db); // 이동 대입 연산자 호출 (컴파일 오류)
    */

}
