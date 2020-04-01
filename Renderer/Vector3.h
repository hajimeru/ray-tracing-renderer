#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include <cmath>
#include <iostream>

class Vector3 {
public:
	Vector3() :x_(0), y_(0), z_(0) {}
	Vector3(double x, double y, double z) :x_(x), y_(y), z_(z) {}

	static Vector3 Zero;

	static Vector3 Xaxis;

	static Vector3 Yaxis;

	static Vector3 Zaxis;

	double Length() const {
		return std::sqrt(x_ * x_ + y_ * y_ + z_ * z_);
	}
	double SqrLength() const {
		return x_ * x_ + y_ * y_ + z_ * z_;
	}

	Vector3 Negative() {
		return Vector3(-x_, -y_, -z_);
	}

	Vector3 Normalize() const {
		double fac = 1 / Length();
		return Vector3(x_ * fac, y_ * fac, z_ * fac);
	}

	double x() const { return x_; }
	double y() const { return y_; }
	double z() const { return z_; }

	//add
	Vector3& operator += (const Vector3& rhs) {
		x_ += rhs.x_; y_ += rhs.y_; z_ += rhs.z_;
		return *this;
	}
	inline friend Vector3 operator +(const Vector3& lhs, const Vector3& rhs) {
		Vector3 ret(lhs);
		return ret += rhs;
	}
	
	//sub
	Vector3& operator -=(const Vector3& rhs) {
		x_ -= rhs.x_; y_ -= rhs.y_; z_ -= rhs.z_;
		return *this;
	}
	inline friend Vector3 operator -(const Vector3& lhs, const Vector3& rhs) {
		Vector3 ret(lhs);
		return ret -= rhs;
	}

	//mul
	Vector3& operator *=(double value) {
		x_ *= value; y_ *= value; z_ *= value;
		return *this;
	}
	inline friend Vector3 operator *(const Vector3& lhs, double value) {
		Vector3 ret(lhs);
		return ret *= value;
	}
	inline friend Vector3 operator *(double value, const Vector3& rhs) {
		return rhs * value;
	}

	//mul
	Vector3& operator /=(double value) {
		double fac = 1.0 / value;
		x_ *= fac; y_ *= fac; z_ *= fac;
		return *this;
	}
	inline friend Vector3 operator /(const Vector3& lhs, double value) {
		Vector3 ret(lhs);
		return ret /= value;
	}

	inline friend bool operator==(const Vector3& lhs, const Vector3& rhs) {
		return (lhs.x_ == rhs.x_) && (lhs.y_ == rhs.y_) && (lhs.z_ == rhs.z_);
	}

	//cross
	Vector3 Cross(const Vector3& rhs) const {
		double x = y_ * rhs.z_ - z_ * rhs.y_;
		double y = z_ * rhs.x_ - x_ * rhs.z_;
		double z = x_ * rhs.y_ - y_ * rhs.x_;
		return Vector3(x, y, z);
	}

	//dot
	double Dot(const Vector3& rhs) const {
		return x_ * rhs.x_ + y_ * rhs.y_ + z_ * rhs.z_;
	}

	//output
	friend std::ostream& operator << (std::ostream& os, const Vector3& rhs);

private:
	double x_, y_, z_;
};

Vector3 Vector3::Zero = Vector3(0, 0, 0);

Vector3 Vector3::Xaxis = Vector3(1, 0, 0);

Vector3 Vector3::Yaxis = Vector3(0, 1, 0);

Vector3 Vector3::Zaxis = Vector3(0, 0, 1);


std::ostream& operator<<(std::ostream& os, const Vector3& rhs) {
	 os << "[x,y,z]:" << rhs.x_ << " " << rhs.y_ << " " << rhs.z_ ;
	 return os;
}
#endif

