#pragma once
#include <string>
#include <iostream>

// numbers in this system are written backwarads and stored as a string (value)
class INT {
private:
	std::string value;
	bool isNegative;
public:
	// getter and setter
	std::string getValue() const;
	std::string getValueVisible() const;
	void setValue(std::string v); // slower than with integers, mainly for the purpose of debugging
	void setValue(int v);
	void setValue(_int64 v);
	// functions
	INT add(INT x) const;
	// operators
	//		maths
	INT operator+(INT x) const;
	//		logic
	bool operator==(INT x) const;
	bool operator!=(INT x) const;
	bool operator>(INT x) const;
	bool operator>=(INT x) const;
	bool operator<(INT x) const;
	bool operator<=(INT x) const;

	// initializers
	INT();
	INT(std::string v); // slower than with integers, mainly for the purpose of debugging
	INT(int v);
	INT(_int64 v);
};

std::ostream& operator<<(std::ostream& stream, const INT& other);