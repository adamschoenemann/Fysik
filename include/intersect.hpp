#ifndef INTERSECT_HPP_INCLUDED
#define INTERSECT_HPP_INCLUDED

class Intersect {
	public:
	static CollisionData pointInRectangle(Vector2 p, Rectangle rect){

	}

	static CollisionData pointInPoly(Vector2 p, PolygonShape poly){

	}

	static CollisionData CircleLine(Circle crc, Line L){

	}

	static CollisionData circleCircle(ICircle* A, ICircle* B){
		Vector2 distance = A->getCenter() - B->getCenter();
		real mag = distance.magnitude();
		real penetration = (A->getRadius() + B->getRadius()) - mag;
		if(penetration < 0){
			return CollisionData(false);
		}
		else {
			distance.normalize(); // is now collision normal
			return CollisionData(penetration, distance);
		}
	}

	static CollisionData rectRect(IRectangle* A, IRectangle* B){
		Vector2 deltaPos = A->getCenter() - B->getCenter();
//		cout << "deltaPos: " << deltaPos << endl;
		Vector2 extA = A->getExtends();
		Vector2 extB = B->getExtends();
		Vector2 extTot = extA + extB;
//		cout << "extTot: " << extTot << endl;
		Vector2 overlap = extTot - deltaPos.getAbs();
//		overlap.projectTo(deltaPos);
//		real pene = overlap.magnitude();
		real pene;
		Vector2 normal;
		if(overlap.x > overlap.y){
			normal = Vector2(overlap.x, 0).normalize();
		}
		else {
			normal = Vector2(0, overlap.y).normalize();
		}
		pene = overlap.minDimension();
		if(overlap.x > 0 && overlap.y > 0){
			return CollisionData(pene, normal);
		}
		else return CollisionData(false);
	}

	static CollisionData lineLine(Line* L1, Line* L2){

	}

};
#endif // INTERSECT_HPP_INCLUDED
