#ifndef DYNAMIC_HPP_INCLUDED
#define DYNAMIC_HPP_INCLUDED

class IDynamic {

	public:
	virtual void setMass(real val) = 0;
	virtual void setInverseMass(real val) = 0;
	virtual void integrate(real duration) = 0;
	virtual void setPosition(const Vector2 pos) = 0;
	virtual Vector2 getPosition() const = 0;
	virtual void setVelocity(const Vector2 vel) = 0;
	virtual Vector2 getVelocity() const = 0;
	virtual void setAcceleration(const Vector2 acc) = 0;
	virtual Vector2 getAcceleration() const = 0;
	virtual void setDamping(real val) = 0;
	virtual real getDamping() const = 0;
	virtual real getMass() const = 0;
	virtual real getInverseMass() const = 0;
	virtual real getRestitution() const = 0;
	virtual void setRestitution(real val) = 0;
	virtual void clearAccumulator() = 0;
	virtual void addForce(const Vector2& force) = 0;
	virtual bool hasFiniteMass() const = 0;
};

class Dynamic : public virtual IDynamic {
	protected:
	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
	Vector2 forceAccum;
	real damping;
	real inverseMass;
	real restitution;

	public:
	string name;

	Dynamic(){
		damping = 1.0f;
		inverseMass = 0.0f;
	}
	void setMass(real val){
		assert(val != 0.0);
		inverseMass = real(1) / val;
	}

	void setInverseMass(real val){
		inverseMass = val;
	}

	void integrate(real duration) {
		assert(duration > 0.0);
		if(inverseMass == 0) return;
		position.addScaledVector(velocity, duration);

		Vector2 resultingAcc = acceleration;
		resultingAcc.addScaledVector(forceAccum, inverseMass);

		velocity.addScaledVector(resultingAcc, duration);

		velocity *= real_pow(damping, duration);

		clearAccumulator();
//		cout << "Acceleration: " << acceleration << "\t" << "Velocity: " << velocity << endl;

	}

	void setPosition(const Vector2 pos){
		position = pos;
	}

	void setPosition(real x, real y){
		position.x = x;
		position.y = y;
	}

	Vector2 getPosition() const {
		return position;
	}

	void setVelocity(real x, real y){
		velocity.x = x;
		velocity.y = y;
	}

	void setVelocity(const Vector2 vel){
		velocity = vel;
	}

	Vector2 getVelocity() const{
		return velocity;
	}

	void setAcceleration(const Vector2 acc){
		acceleration = acc;
	}

	void setAcceleration(real x, real y){
		acceleration.x = x;
		acceleration.y = y;
	}

	Vector2 getAcceleration() const{
		return acceleration;
	}

	void setDamping(real val){
		damping = val;
	}

	real getDamping() const{
		return damping;
	}

	real getMass() const{
		if(inverseMass == 0){
			return INFINITY;
		}
		else return (real(1) / inverseMass);
	}

	real getInverseMass() const {
		return inverseMass;
	}

	real getRestitution() const {
		return restitution;
	}

	void setRestitution(real val){
		restitution = val;
	}

	void clearAccumulator(){
		forceAccum.clear();
	}

	void addForce(const Vector2& force){
		forceAccum += force;
	}

	bool hasFiniteMass() const{
		return (inverseMass >= 0.0f);
	}
};

class Particle : public Dynamic {

};

#endif // DYNAMIC_HPP_INCLUDED
