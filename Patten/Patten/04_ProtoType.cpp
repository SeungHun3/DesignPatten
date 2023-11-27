#include "04_ProtoType.h"


// Ŭ�������ο� �������� ���� �Ǿ��־� ��𿡼� �޸𸮰� �������� �������� ����
// => ���� �����Ͽ� �޸� �Ҵ��� �������
Contact EmployeeFactory::main = { "", new Address{"123 gangnam","seoul",0} };
Contact EmployeeFactory::aux = { "", new Address{"111 gangnam","seoul",0} };

void proto_main()
{
	// ������Ÿ�� ��ü
	Contact worker{ "", new Address{"123 gangnam","seoul",0} };

	// ������Ÿ���� �����Ͽ� ��ü�� ����
	// ������ ���� (���������)
	Contact john{ worker };
	Contact dan{ worker };
	john.name = "john";
	john.address->suite = 10;


	// ������ ���� ==> operator�� ���� ���������� �ʴ´ٸ� ���� ������ �ּҰ� �����ǹ����⿡ ����, �����޴� ������ ���� �ٲ��
	Contact hun = worker;

	// �����Լ�
	Contact* ham = worker.CLONE(); //unique_ptr<Contact> ham(worker.CLONE());
	delete ham;
	
	// ������ Ÿ�� ���丮
	auto fmain = EmployeeFactory::NewMainOfficeEmployee("fmain", 101);
	auto faux = EmployeeFactory::NewAuxOfficeEmployee("faux", 21);
}
