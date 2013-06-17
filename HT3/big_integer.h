#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H
#include "my_vector.h"
#include <string>
#include <vector>

enum sign {
	PLUS, MINUS
};

class big_integer {
public:
	big_integer();
	big_integer(int);
	big_integer(const big_integer&);
	explicit big_integer(const std::string&);
	big_integer& operator = (const big_integer&);

	big_integer& operator %= (const big_integer&);
	big_integer& operator += (const big_integer&);
	big_integer& operator *= (const big_integer&);
	big_integer& operator -= (const big_integer&);
	big_integer& operator /= (const big_integer&);

	big_integer& operator ++ ();
	big_integer& operator -- ();

	big_integer operator ++ (int);
	big_integer operator -- (int);

	big_integer& operator &= (const big_integer&);
	big_integer& operator |= (const big_integer&);
	big_integer& operator ^= (const big_integer&);
	
	
	big_integer& operator >>= (int);
	big_integer& operator <<= (int);

	big_integer operator - ();
	big_integer operator + ();
	big_integer operator ~ ();


	friend bool operator == (const big_integer&, const big_integer&);
	friend bool operator != (const big_integer&, const big_integer&);
	friend bool operator < (const big_integer&, const big_integer&);
	friend bool operator > (const big_integer&, const big_integer&);
	friend bool operator <= (const big_integer&, const big_integer&);
	friend bool operator >= (const big_integer&, const big_integer&);

	friend big_integer operator % (const big_integer&, const big_integer&);
	friend big_integer operator + (const big_integer&, const big_integer&);
	friend big_integer operator - (const big_integer&, const big_integer&);
	friend big_integer operator * (const big_integer&, const big_integer&);
	friend big_integer operator / (const big_integer&, const big_integer&);

	friend big_integer operator & (const big_integer&, const big_integer&);
	friend big_integer operator | (const big_integer&, const big_integer&);
	friend big_integer operator ^ (const big_integer&, const big_integer&);

	friend big_integer operator << (const big_integer&, int);
	friend big_integer operator >> (const big_integer&, int);

	friend std::string to_string(big_integer const&);
	friend sign get_sign(const big_integer&);
private:
	mutable my_vector data;
};

sign get_sign(const big_integer& val);
bool operator == (const big_integer&, const big_integer&);
bool operator != (const big_integer&, const big_integer&);
bool operator < (const big_integer&, const big_integer&);
bool operator > (const big_integer&, const big_integer&);
bool operator <= (const big_integer&, const big_integer&);
bool operator >= (const big_integer&, const big_integer&);

big_integer operator % (const big_integer&, const big_integer&);
big_integer operator + (const big_integer&, const big_integer&);
big_integer operator - (const big_integer&, const big_integer&);
big_integer operator * (const big_integer&, const big_integer&);
big_integer operator / (const big_integer&, const big_integer&);

big_integer operator & (const big_integer&, const big_integer&);
big_integer operator | (const big_integer&, const big_integer&);
big_integer operator ^ (const big_integer&, const big_integer&);

big_integer operator << (const big_integer&, int);
big_integer operator >> (const big_integer&, int);

std::string to_string(big_integer const&);

#endif // BIG_INTEGER_H