#ifndef _MYMATH_H_
#define _MYMATH_H_

class MyMath {
public:
	template<typename T>
	static inline T clip(const T& x, const T& low, const T& high) {
		return x < low ? low : (x > high ? high : x);
	}

	template<typename T>
	static inline T max3(const T& a, const T& b, const T& c) {
		return std::max(a, std::max(b, c));
	}
};



#endif // !_MYMATH_H_

