#include "08_Composite.h"

void composite_main()
{
	//배열
	Player player;
	player.set_strength(5);
	Monster monster;
	monster.set_strength(1);
	cout <<"Player : "<< player.sum() << "  Monster : " << monster.sum() << endl;

	// 그루핑
	CircleObject* circleObj = new CircleObject();
	RectangleObject* rectangleObj = new RectangleObject();

	Group group("group");
	group.add(circleObj);
	group.add(rectangleObj);

	group.draw();
	group.deleteAll();

	// 뉴럴네트워크
	Neuron n1, n2;
	n1.simple_connect_to(n2); // 단순 뉴런간 연결

	NeuronLayer l1{ 5 };
	Neuron n3;
	l1.connect_to(n3); // 뉴런, 레이어 연결

	NeuronLayer l2{ 2 }, l3{ 3 };
	l2.connect_to(l3); // 레이어, 레이어 연결

}
