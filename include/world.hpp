#ifndef WORLD_HPP_INCLUDED
#define WORLD_HPP_INCLUDED


class World {
	private:
	typedef list<Body*> Bodies;
	Bodies bodies;
	CollisionEngine collider;

	public:
	Body* createBody(IShape* sh, string name){
		Body* b = new Body(sh);
		b->name = name;
		bodies.push_back(b);
		collider.add(b);
		return b;
	}

	Body* createBody(IShape* sh){
		Body* b = new Body(sh);
		bodies.push_back(b);
		collider.add(b);
		return b;
	}

	void step(real duration){
		collider.checkCollisions(duration);
		integrate(duration);
	}

	void integrate(real duration){
		for(Bodies::iterator i = bodies.begin(); i != bodies.end(); i++){
			cout << (*i)->name << endl;
			(*i)->integrate(duration);
		}
	}

	Bodies* getBodies(){
		return &bodies;
	}

	Body* getBodyAt(size_t index){
		size_t count = 0;
		for(Bodies::iterator i = bodies.begin(); i != bodies.end(); i++){
			if(count == index)
				return (*i);
			count++;
		}
		return NULL;
	}

	Body* getBodyByName(string name){
		for(Bodies::iterator i = bodies.begin(); i != bodies.end(); i++){
			if((*i)->name == name)
				return (*i);
		}
		return NULL;
	}



};


#endif // WORLD_HPP_INCLUDED
