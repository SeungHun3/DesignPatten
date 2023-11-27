#include "04_ProtoType.h"


// 클래스내부엔 전역변수 선언만 되어있어 어디에서 메모리가 참조될지 정해지지 않음
// => 직접 정의하여 메모리 할당을 해줘야함
Contact EmployeeFactory::main = { "", new Address{"123 gangnam","seoul",0} };
Contact EmployeeFactory::aux = { "", new Address{"111 gangnam","seoul",0} };

void proto_main()
{
	// 프로토타입 객체
	Contact worker{ "", new Address{"123 gangnam","seoul",0} };

	// 프로토타입을 복제하여 객체를 수정
	// 생성자 복제 (복사생성자)
	Contact john{ worker };
	Contact dan{ worker };
	john.name = "john";
	john.address->suite = 10;


	// 연산자 복제 ==> operator를 직접 구현해주지 않는다면 내부 포인터 주소가 공유되버리기에 원본, 참조받는 모든곳의 값이 바뀐다
	Contact hun = worker;

	// 복제함수
	Contact* ham = worker.CLONE(); //unique_ptr<Contact> ham(worker.CLONE());
	delete ham;
	
	// 프로토 타입 팩토리
	auto fmain = EmployeeFactory::NewMainOfficeEmployee("fmain", 101);
	auto faux = EmployeeFactory::NewAuxOfficeEmployee("faux", 21);
}
