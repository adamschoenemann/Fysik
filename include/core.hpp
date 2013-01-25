#ifndef CORE_HPP_INCLUDED
#define CORE_HPP_INCLUDED

class Vector2 {
	public:
	real x, y;

	private:

	public:
	Vector2():x(0), y(0){}
	Vector2(real x, real y): x(x), y(y){}

	void invert(){
		x = -x;
		y = -y;

	}

	Vector2& set(real x, real y){
		this->x = x;
		this->y = y;
		return *this;
	}
	real magnitude() const {
		return std::sqrt(x*x+y*y);
	}

	real squareMagnitude() const {
		return x*x+y*y;
	}

	Vector2 normalize(){
		real mag = magnitude();
		if(mag > 0){
			x *= ((real) 1) / mag;
			y *= ((real) 1) / mag;

		}
		return Vector2(x, y);
	}

	Vector2 getNormalized(){
		real mag = magnitude();
		Vector2 ret(x, y);
		if(mag > 0){
			ret.x *= ((real) 1) / mag;
			ret.y *= ((real) 1) / mag;
		}
		return ret;
	}

	real minDimension(){
		real ax = std::abs(x);
		real ay = std::abs(y);
		return ((ax < ay) ? x : y);
	}

	void projectTo(const Vector2& other){
		real rel = (dotProduct(other) / other.squareMagnitude());
		*this = other * rel;
	}

	Vector2 componentProduct(const Vector2& other) const {
		return Vector2(x * other.x, y * other.y);
	}

	void componentProductUpdate(const Vector2& other){
		x *= other.x;
		y *= other.y;
	}

	real dotProduct(const Vector2& other){
		return x * other.x + y * other.y;
	}

	real crossProduct(const Vector2& other){
		return (x * other.y - y * other.x);
	}

	void addScaledVector(const Vector2& vector, real scale){
		x += vector.x * scale;
		y += vector.y * scale;
	}


	void clear(){
		y = x = 0;
	}

	Vector2& round(){
		x = (int) x;
		y = (int) y;
		return *this;
	}

	Vector2& abs(){
		x = std::abs(x);
		y = std::abs(y);
		return *this;
	}

	Vector2 getAbs(){
		return Vector2(std::abs(x), std::abs(y));
	}

	//---------------------------------OPERATORS----------------------------------
	Vector2 operator* (const real val) const{
		return Vector2(x*val, y*val);
	}

	Vector2 operator+ (const real val) const{
		return Vector2(x+val, y+val);
	}

	Vector2 operator- (const real val) const{
		return Vector2(x-val, y-val);
	}

	Vector2 operator/ (const real val) const{
		return Vector2(x/val, y/val);
	}

	void operator*= (const real val){
		x *= val;
		y *= val;
	}

	Vector2 operator+ (const Vector2& other) const{
		return Vector2(x + other.x, y + other.y);
	}

	void operator+= (const Vector2& other){
		x += other.x;
		y += other.y;
	}

	Vector2 operator- (const Vector2& other) const{
		return Vector2(x - other.x, y - other.y);
	}

	void operator-= (const Vector2& other){
		x -= other.x;
		y -= other.y;
	}

	real operator* (const Vector2& other) const{
		return x * other.x + y * other.y;
	}

	real operator% (const Vector2& other) const{
		return (x * other.y - y * other.x);
	}

	void operator= (const Vector2& other){
		x = other.x;
		y = other.y;
	}

	friend ostream& operator<< (ostream& out, Vector2& vec){
		out << "(" << vec.x << ", " << vec.y << ")";
		return out;
	}

	friend bool operator== (const Vector2& a, const Vector2& b){
		return ((a.x == b.x && a.y == b.y) ? true : false);
	}
};

class Line {
	public:

	Vector2 origin;
	Vector2 dir;

};


class IRectangle {
	public:
	virtual Vector2 getDimensions() const = 0;
	virtual Vector2 getExtends() const = 0;
	virtual Vector2 getCenter() const = 0;
	virtual real getWidth() const = 0;
	virtual real getHeight() const = 0;
};

class Rectangle : public IRectangle {
	private:



	public:
	Vector2 p[4];
	enum RECT_CREATION_TYPE {
		EXTENDS = 1,
		CORNER = 0
	};

	virtual Vector2 getDimensions() const {
		real w = p[2].x - p[0].x;
		real h = p[2].y - p[0].y;
		return Vector2(w, h);
	}

	virtual Vector2 getExtends() const {
		Vector2 ret = getDimensions();
		ret = ret / 2;
//		cout << "Extends: " << ret << endl;
		return ret;
	}

	virtual Vector2 getCenter() const {
		return ((p[2] + p[0]) / 2);
	}

	virtual real getWidth() const {
		return (p[2].x - p[0].x);
	}

	virtual real getHeight() const {
		return (p[2].y - p[0].y);
	}

	real right() const {
		return p[2].x;
	}

	real left() const {
		return p[0].x;
	}

	real top() const {
		return p[0].y;
	}

	real bottom() const {
		return p[2].y;
	}

	//-----------------------------CONSTRUCTORS-----------------------------------
	Rectangle(){
		Vector2 zero(0, 0);
		p[0] = zero;
		p[1] = zero;
		p[2] = zero;
		p[3] = zero;
	}
	Rectangle(Vector2 A, Vector2 B, Vector2 C, Vector2 D){
		p[0] = A;
		p[1] = B;
		p[2] = C;
		p[3] = D;
	}

	Rectangle(real w, real h, const Vector2& pos, RECT_CREATION_TYPE type = EXTENDS){
		Vector2 A, B, C, D;
		real px = pos.x;
		real py = pos.y;
		if(type == EXTENDS){
			A.set(-w + px, -h + py);
			B.set(w + px, -h + py);
			C.set(w + px, h + py);
			D.set(-w + px, h + py);
		}
		else if(type == CORNER){
			A.set(px, py);
			B.set(px + w, py);
			C.set(px + w, py + h);
			D.set(px, py + h);
		}
		p[0] = A;
		p[1] = B;
		p[2] = C;
		p[3] = D;
	}

	//-------------------------------OPERATORS------------------------------------
	friend ostream& operator<< (ostream& out, const Rectangle& rect){
//		out << "center: " << (rect.getCenter()) << "\ndimensions: " << (rect.getDimensions());
		Vector2 center = rect.getCenter();
		Vector2 dims = rect.getDimensions();
		out << "center: " << center << "\ndimensions: " << dims;

		return out;

	}

};

class ICircle {
	public:
	virtual Vector2 getCenter() = 0;
	virtual real getRadius() = 0;

};


class Circle : public ICircle {
	public:

	Vector2 center;
	real radius;

	Vector2 getCenter(){
		return center;
	}

	real getRadius(){
		return radius;
	}

};

/*
class Rectangle {
	public:
	Vector2 points[4];

	Rectangle(const Vector2 A,
						const Vector2 B,
						const Vector2 C,
						const Vector2 D)
	{
		points[0] = A;
		points[1] = B;
		points[2] = C;
		points[3] = D;

	}

	Vector2 minX(){
		Vector2 ret = points[0];
		for(size_t i = 0; i < 4; i++){

		}
	}

	Vector2& operator[](size_t i){
		return points[i];
	}

};
*/
#endif // CORE_HPP_INCLUDED
