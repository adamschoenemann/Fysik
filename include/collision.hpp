#ifndef COLLISION_HPP_INCLUDED
#define COLLISION_HPP_INCLUDED


struct CollisionData {

	real interpenetration;
	Vector2 normal;

	bool isCollision;
	CollisionData(real inter, Vector2 normal):interpenetration(inter), normal(normal){
		isCollision = true;
	}

	CollisionData(bool state){
		isCollision = state;
		interpenetration = 0;
	}

	CollisionData(){
		interpenetration = 0;
		isCollision = false;
	}

	friend ostream& operator<< (ostream& out, CollisionData data){
		out << "penetration: " << data.interpenetration << "\nnormal: " << data.normal <<
			"\nisCollision: " << data.isCollision << endl;
		return out;
	}

};

class ICollideable : virtual public IDynamic {
	public:
	virtual Rectangle getAABB() = 0;

};

struct Contact {
	ICollideable* objs[2];
	Vector2 normal;
	real penetration;
	real restitution;

	Contact(){
		objs[0] = NULL;
		objs[1] = NULL;
		penetration = 0;
	}

	void add(ICollideable* obj){
		if(obj->getInverseMass() == 0) return;
		if(objs[0] == NULL){
			objs[0] = obj;
		}
		else if(objs[1] == NULL){
			objs[1] = obj;
		}

	}

	real calcSepVel(){
		Vector2 relVel = objs[0]->getVelocity();
		if(objs[1]) relVel -= objs[1]->getVelocity();
		return relVel * normal;
	}

	void resolve(real duration){
		resolveVelocity(duration);
		resolvePenetration();
	}

	void resolvePenetration(){
		if(penetration <= 0) return;


		real totalImass = objs[0]->getInverseMass();
		if(objs[1]) totalImass += objs[1]->getInverseMass();

		if(totalImass <= 0) return;

		Vector2 movePerImass = normal * (-penetration / totalImass);

		objs[0]->setPosition(objs[0]->getPosition() - movePerImass * objs[0]->getInverseMass());
		if(objs[1]) objs[1]->setPosition(objs[1]->getPosition() + movePerImass * objs[1]->getInverseMass());
	}

	void resolveVelocity(real duration){

		real sepVel = calcSepVel();

		if(sepVel > 0) return;

		real newSepVel = -sepVel * restitution;
		real deltaVel = newSepVel - sepVel;

		real totalIMass = objs[0]->getInverseMass();
		if(objs[1]) totalIMass += objs[1]->getInverseMass();

		real impulse = deltaVel / totalIMass;
		Vector2 impulsePerIMass = normal * impulse;

		Vector2 accCausedVelocity = objs[0]->getAcceleration();
		if (objs[1]) accCausedVelocity -= objs[1]->getAcceleration();
		real accCausedSepVelocity = accCausedVelocity * normal * duration;
		// If we’ve got a closing velocity due to acceleration build-up,
		// remove it from the new separating velocity.
		if (accCausedSepVelocity < 0){
			newSepVel += accCausedSepVelocity;
			// Make sure we haven’t removed more than was
			// there to remove.
			if (newSepVel < 0) newSepVel = 0;
		}

		objs[0]->setVelocity(objs[0]->getVelocity() + (impulsePerIMass * objs[0]->getInverseMass()));
		if(objs[1])
			objs[1]->setVelocity(objs[1]->getVelocity() - (impulsePerIMass * objs[1]->getInverseMass()));

	}

	bool has(ICollideable* a, ICollideable* b){
		if((objs[0] == a || objs[0] == b) && (objs[1] == b || objs[1] == a))
			return true;
		else
			return false;
	}
};

class CollisionEngine {
	private:
	typedef list<ICollideable*> CollisionObjects;
	CollisionObjects objs;

	typedef list<Contact> Contacts;
	Contacts contacts;

	public:

	// TODO
	void checkCollisions(real duration){
		for(CollisionObjects::iterator i = objs.begin(); i != objs.end(); i++){
			for(CollisionObjects::iterator j = objs.begin(); j != objs.end(); j++){
				if(*i != *j){
					if((*i)->getInverseMass() == 0 && (*j)->getInverseMass() == 0)
						continue;
					Rectangle A = (*i)->getAABB();
					Rectangle B = (*j)->getAABB();
					if(intersects(&A, &B)){
						if(!(hasContact(*i, *j))){
//							cout << "COLLISION!\n";
							Vector2 normal = ((*i)->getPosition() - (*j)->getPosition());
							normal.normalize();
							Contact c;
							c.normal = normal;
							if((*i)->getInverseMass() != 0){
								c.add(*i);
							}
							if((*j)->getInverseMass() != 0){
								c.add(*j);
							}
							contacts.push_back(c);
						}
					}
				}
			}
		}
		resolveContacts(duration);
		contacts.clear();
	}

	void resolveContacts(real duration){
		for(Contacts::iterator i = contacts.begin(); i != contacts.end(); i++){
			(*i).resolve(duration);
		}
	}

	void add(ICollideable* obj){
		objs.push_back(obj);
	}

	bool intersects(Rectangle* A, Rectangle* B){

//		cout << "A:";
//		cout << "\n\t left: " << A->left();
//		cout << "\n\t right: " << A->right();
//		cout << "\n\t top: " << A->top();
//		cout << "\n\t bottom: " << A->bottom();
//		cout << endl;
//		cout << "B:";
//		cout << "\n\t left: " << B->left();
//		cout << "\n\t right: " << B->right();
//		cout << "\n\t top: " << B->top();
//		cout << "\n\t bottom: " << B->bottom();
//		cout << endl;

		if((A->right() < B->left() ||
				A->bottom() < B->top() ||
				A->left() > B->right() ||
				A->top() > B->bottom()))
		{
			return false;
		} else return true;
	}

	bool hasContact(ICollideable* a, ICollideable* b){
		for(Contacts::iterator i = contacts.begin(); i != contacts.end(); i++){
			if((*i).has(a, b))
				return true;
		}
		return false;
	}

};

#endif // COLLISION_HPP_INCLUDED
