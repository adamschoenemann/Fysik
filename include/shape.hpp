#ifndef SHAPE_HPP_INCLUDED
#define SHAPE_HPP_INCLUDED

class IShape {

	public:
	enum Type {
		SHAPE_CIRCLE = 0,
		SHAPE_POLYGON = 1
	};

	protected:
	Type type;

	public:
	Type getType(){
		return type;
	}

	virtual Rectangle computeAABB() = 0;

};

class PolygonShape : public IShape {
	private:
	typedef list<Vector2> Vertices;
	Vertices vertices;
	size_t numVerts;

	public:

	PolygonShape(){
		type = SHAPE_POLYGON;
		numVerts = 0;
	}

	void setAsBox(real halfWidth, real halfHeight){
		vertices.clear();
		vertices.push_back(Vector2(-halfWidth, -halfHeight));
		vertices.push_back(Vector2(halfWidth, -halfHeight));
		vertices.push_back(Vector2(halfWidth, halfHeight));
		vertices.push_back(Vector2(-halfWidth, halfHeight));
		numVerts = 4;
	}

	void addVertex(real x, real y){
		vertices.push_back(Vector2(x, y));
		numVerts++;
	}

	void addVertex(const Vector2 vec){
		vertices.push_back(vec);
		numVerts++;
	}

	void getVertices(Vector2** target){
		size_t count = 0;
		for(Vertices::iterator i = vertices.begin(); i != vertices.end(); i++){
			target[count] = &(*i);
			count++;
		}
		assert(count == numVerts);
	}

	size_t getNumVerts(){
		return numVerts;
	}

	Rectangle computeAABB(){
		Vector2 min, max;
		Vertices::iterator iter = vertices.begin();
		min = *(iter);
		max = *(iter);
		iter++;
		for(; iter != vertices.end(); iter++){
			Vector2 vert = *iter;
			if(vert.x < min.x) min.x = vert.x;
			if(vert.x > max.x) max.x = vert.x;
			if(vert.y < min.y) min.y = vert.y;
			if(vert.y > max.y) max.y = vert.y;
		}
		real width = max.x - min.x;
		real height = max.y - min.y;
		return Rectangle(width, height, Vector2(), Rectangle::CORNER);
	}
};


#endif // SHAPE_HPP_INCLUDED
