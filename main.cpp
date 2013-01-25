#include <iostream>
#include "include/fysik.hpp"

using namespace std;
using namespace Fysik;

int main()
{
	Vector2 aPos(0, 0);
	Rectangle A(6, 5, aPos);

	Vector2 bPos(-10, 0);
	Rectangle B(5, 5, bPos);

	CollisionData data = Intersect::rectRect(&A, &B);

	Vector2 pene(-2, 1);
	Vector2 normal(-9, 1);
	pene.projectTo(normal);
	cout << pene << endl;

  return 0;
}
