#include "08_Composite.h"

void composite_main()
{
	Player player;
	player.set_strength(5);
	Monster monster;
	monster.set_strength(1);
	cout <<"Player : "<< player.sum() << "  Monster : " << monster.sum() << endl;

	CircleObject* circleObj = new CircleObject();
	RectangleObject* rectangleObj = new RectangleObject();

	Group group("group");
	group.add(circleObj);
	group.add(rectangleObj);

	group.draw();
	group.deleteAll();


}
