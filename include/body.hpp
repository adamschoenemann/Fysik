#ifndef BODY_HPP_INCLUDED
#define BODY_HPP_INCLUDED


class Body : public Dynamic, public ICollideable {
	private:
	IShape* shape;


	public:
	Body(IShape* shape):shape(shape){

	}

	IShape* getShape(){
		return shape;
	}

	Rectangle getAABB(){
		Rectangle ret;
		ret = shape->computeAABB();
		return Rectangle();
//		return Rectangle(getPosition(), ret.getWidth(), ret.getHeight());
	}

};

#endif // BODY_HPP_INCLUDED
