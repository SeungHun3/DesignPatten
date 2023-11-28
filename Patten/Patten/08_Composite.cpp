#include "08_Composite.h"

void composite_main()
{
	//�迭
	Player player;
	player.set_strength(5);
	Monster monster;
	monster.set_strength(1);
	cout <<"Player : "<< player.sum() << "  Monster : " << monster.sum() << endl;

	// �׷���
	CircleObject* circleObj = new CircleObject();
	RectangleObject* rectangleObj = new RectangleObject();

	Group group("group");
	group.add(circleObj);
	group.add(rectangleObj);

	group.draw();
	group.deleteAll();

	// ������Ʈ��ũ
	Neuron n1, n2;
	n1.simple_connect_to(n2); // �ܼ� ������ ����

	NeuronLayer l1{ 5 };
	Neuron n3;
	l1.connect_to(n3); // ����, ���̾� ����

	NeuronLayer l2{ 2 }, l3{ 3 };
	l2.connect_to(l3); // ���̾�, ���̾� ����

}
