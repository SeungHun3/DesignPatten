#include "09_Decorator.h"

void decorator_main()
{
	// ���� ��Ŀ������
	Deco_Circle circle{ 0.5f };
	Deco_Square square;
	// ���� �߰�
	ColoredShape red_circle{ circle,"red" };
	// ���� �߰�
	TransparentShape trans_circle{ red_circle ,15 };
	TransparentShape trans_square{ square ,10 };

	cout << trans_circle.str() << endl;
	cout << trans_square.str() << endl;

	// ���� ��Ŀ������ : ���� ���̾Ƹ�� ������ �߻��� �� ����
	Color_template<Transparency_template<Deco_Circle>> templateShape{"blue"};
	templateShape.radius = 0.1f;
	templateShape.transparency = 10;
	templateShape.resize(2);
	cout << templateShape.str() << endl;

	Transparency_template<Deco_Square> temp;
	temp.transparency = 50;
	cout << temp.str() << endl;
	// ������ : ���� �������� �����ڸ� ȣ��Ǿ� ���� ��Ŀ���̼��� �ѹ��� �ʱ�ȭ�Ҽ��� ���� 

	// �������� ���ø��� �̿��� �ذ�
	Color_template<Transparency_template<Deco_Circle>> argtemplate{ "green",20,2.f };
	cout << argtemplate.str() << endl;

}
