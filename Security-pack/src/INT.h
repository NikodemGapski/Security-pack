#pragma once
#include <iostream>

// numbers in this system are written backwarads and stored as a string (value)
class INT {
private:
	std::string value;
	bool isNegative;
public:
	// getter and setter
	std::string getValue() const;
	std::string getValueVisible() const; // visible means in the normal system (from the most to the least important digit)
	bool getIsNegative() const;
	void setValueVisible(std::string v); // slower than with integers, mainly for the purpose of debugging (the string reflects an actual number)
	void setValue(std::string v, bool n);
	void setValue(int v);
	void setValue(_int64 v);
	void setIsNegative(bool n);

	void addDigit(int x); // add digit x to value
	// functions
	void clear();
	INT add(INT x) const;
	INT subtract(INT x) const;
	INT multiply(INT x) const;
	INT divide(INT x) const;

	INT abs(INT x) const;
	// operators
	//		maths (const)
	INT operator+(INT x) const; 
	INT operator+(int x) const;
	INT operator+(_int64 x) const;
	INT operator-(INT x) const;
	INT operator-(int x) const;
	INT operator-(_int64 x) const;
	INT operator*(INT x) const;
	INT operator*(int x) const;
	INT operator*(_int64 x) const;
	INT operator/(INT x) const;
	INT operator/(int x) const;
	INT operator/(_int64 x) const;
	//		maths (change value)
	void operator+=(INT x);
	void operator+=(int x);
	void operator+=(_int64 x);
	void operator++();
	void operator-=(INT x);
	void operator-=(int x);
	void operator-=(_int64 x);
	void operator--();
	void operator*=(INT x);
	void operator*=(int x);
	void operator*=(_int64 x);
	void operator/=(INT x);
	void operator/=(int x);
	void operator/=(_int64 x);
	//		logic
	bool operator==(INT x) const;
	bool operator==(int x) const;
	bool operator==(_int64 x) const;
	bool operator!=(INT x) const;
	bool operator>(INT x) const;
	bool operator>=(INT x) const;
	bool operator<(INT x) const;
	bool operator<=(INT x) const;

	// initializers
	INT();
	INT(std::string v); // slower than with integers, mainly for the purpose of debugging (the string reflects an actual number)
	INT(int v);
	INT(_int64 v);
};

std::ostream& operator<<(std::ostream& stream, const INT& other);