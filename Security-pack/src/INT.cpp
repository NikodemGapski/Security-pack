#include <string>
#include "Math.h"
#include "INT.h"


static int Char2Int(char c) {
	return c - '0';
}
static std::string Inverse(std::string x) {
	std::string output = "";
	for (int i = 0; i < x.size(); i++) {
		output += x[x.size() - i - 1];
	}
	return output;
}

std::string INT::getValue() const {
	return value;
}
std::string INT::getValueVisible() const {
	if (isNegative == true) {
		return '-' + Inverse(value);
	}
	return Inverse(value);
}
bool INT::getIsNegative() const {
	return isNegative;
}

void INT::setValueVisible(std::string v) {
	isNegative = false;
	if (v[0] == '-') {
		isNegative = true;
		v = v.substr(1, v.size() - 1);
	}
	if (Math::IsNumber(v)) {
		value = Inverse(v);
		return;
	}
	value = "0";
	isNegative = false;
}
void INT::setValue(std::string v, bool n) {
	isNegative = n;
	value = v;
}
void INT::setValue(int v) {
	std::string s = std::to_string(v);
	isNegative = false;
	if (s[0] == '-') {
		isNegative = true;
		s = s.substr(1, s.size() - 1);
	}
	value = Inverse(s);
}
void INT::setValue(_int64 v) {
	std::string s = std::to_string(v);
	isNegative = false;
	if (s[0] == '-') {
		isNegative = true;
		s = s.substr(1, s.size() - 1);
	}
	value = Inverse(s);
}
void INT::setIsNegative(bool n) {
	isNegative = n;
}

void INT::addDigit(int x) {
	value += x + '0';
}
void INT::clear() {
	value = "";
	isNegative = false;
}

// ADDITION
// add y to x (when both are positive)
static INT XplusY(INT x, INT y) {
	INT output;
	output.clear();

	int remainder = 0;

	int min = x.getValue().size();
	bool isX = false; // is x maximum ?
	int max = y.getValue().size();
	if (min > max) {
		int k = min;
		min = max;
		max = k;
		isX = true;
	}
	
	for (int i = 0; i < min; i++) {
		int a = Char2Int(x.getValue()[i]) + Char2Int(y.getValue()[i]) + remainder;
		if (a > 9) {
			remainder = 1;
			a -= 10;
		}
		else {
			remainder = 0;
		}
		output.addDigit(a);
	}
	if (isX == true) {
		for (int i = min; i < max; i++) {
			int a = Char2Int(x.getValue()[i]) + remainder;
			if (a > 9) {
				remainder = 1;
				a -= 10;
			}
			else {
				remainder = 0;
			}
			output.addDigit(a);
		}
	}
	else {
		for (int i = min; i < max; i++) {
			int a = Char2Int(y.getValue()[i]) + remainder;
			if (a > 9) {
				remainder = 1;
				a -= 10;
			}
			else {
				remainder = 0;
			}
			output.addDigit(a);
		}
	}
	
	if (remainder > 0) {
		output.addDigit(remainder);
	}
	return output;
}
INT INT::add(INT x) const {
	if (isNegative == false && x.isNegative == false) {
		return XplusY(x, *this);
	}
	if (isNegative == true && x.isNegative == false) {
		INT y = *this;
		y.setIsNegative(false);
		return x.subtract(y);
	}
	// else : (isNegative == false && x.isNegative == true) || (isNegative == true && x.isNegative == true)
	x.setIsNegative(false);
	return subtract(x);
}
// SUBTRACTION
// subtract y from x (when abs(x) > abs(y)), and when their signs are the same (aka different in addition form)
static INT XminusY(INT x, INT y) {
	INT output;
	output.clear();
	int debt = 0;
	for (int i = 0; i < y.getValue().size(); i++) { // subtract all the digits of the smaller number
		int curr = x.getValue()[i] - y.getValue()[i] + debt;
		if (curr < 0) {
			debt = -1;
			curr += 10;
		}
		else {
			debt = 0;
		}
		output.addDigit(curr);
	}
	for (int i = y.getValue().size(); i < x.getValue().size(); i++) {
		int curr = Char2Int(x.getValue()[i]) + debt;
		if (curr < 0) {
			debt = -1;
			curr += 10;
		}
		else {
			debt = 0;
		}
		output.addDigit(curr);
	}
	// delete unused zeros and adjust signs
	for (int i = output.getValue().size() - 1; i >= 0; i--) {
		if (output.getValue()[i] != '0') {
			output.setValue(output.getValue().substr(0, i + 1), x.getIsNegative());
			i = -1;
		}else if (i == 0) { // everything is zeros
			output.setValue(0);
		}
	}
	return output;
}
INT INT::subtract(INT x) const {
	INT output;
	output.clear();
	if (x.isNegative != isNegative) { 
		// both have different signs (so after subtraction both have the same one),
		//so we can just add them and adjust the sign afterwards
		output = XplusY(x, *this);
		if (isNegative == true) { // the first number is negative (-) - (+) = (-) + (-) = (-) * ((+) + (+))
			output.isNegative = true;
		}
		return output;
	}
	// otherwise both have the same sign (so different in subtraction), so the next thing to do is to check which has a greater absolute value
	if (abs(x) > abs(*this)) {
		// subtract this from x (inverted, so we need to return different sign)
		output = XminusY(x, *this);
		output.setIsNegative(!output.getIsNegative());
		return output;
	}
	// otherwise subtract x from this
	return XminusY(*this, x);

}
// MULTIPLICATION
INT INT::multiply(INT x) const {
	// quick things: * 0; * 1; * -1
	{
		if (x == 0 || *this == 0) {
			return INT(0);
		}
		if (x == 1) {
			return *this;
		}
		if (*this == 1) {
			return x;
		}
		if (x == -1) {
			INT a;
			a.setValue(getValue(), !getIsNegative());
			return a;
		}
		if (*this == -1) {
			INT a;
			a.setValue(x.getValue(), !x.getIsNegative());
			return a;
		}
	}
	
	INT output;
	// multiply values
	for (int i = 0; i < getValue().size(); i++) { // for each digit of this->value...
		INT curr;
		curr.clear();
		int remainder = 0;
		for (int z = 0; z < i; z++) { // ...add zeros where needed...
			curr.addDigit(0);
		}
		for (int j = 0; j < x.getValue().size(); j++) { // ...and count multiplication of the whole x.value
			remainder = Char2Int(getValue()[i]) * Char2Int(x.getValue()[j]) + remainder;
			int v = remainder % 10;
			remainder /= 10;
			curr.addDigit(v);
		}
		if (remainder > 0) { // the last digit (aka the most important one)
			curr.addDigit(remainder);
		}
		output += curr;
	}


	// truth table for sign multiplication
	/*
	isNegative:
	a	b		output
	1	1		0
	0	1		1
	1	0		1
	0	0		0
	
	formula: output = (a - b)^2
	*/
	bool sign = (getIsNegative() - x.getIsNegative()) * (getIsNegative() - x.getIsNegative());
	output.setIsNegative(sign);
	return output;
}
// DIVISION
INT INT::divide(INT x) const {
	// truth table for sign multiplication (and division)
	/*
	isNegative:
	a	b		output
	1	1		0
	0	1		1
	1	0		1
	0	0		0

	formula: output = (a - b)^2
	*/
	bool sign = (getIsNegative() - x.getIsNegative()) * (getIsNegative() - x.getIsNegative());

	INT _this = *this;
	_this.setIsNegative(false);
	x.setIsNegative(false);
	INT output(0);
	if (x > _this) {
		return output;
	}
	while (x * (output + 1) <= _this) {
		INT curr(1);
		while (x * (output + curr * 2) <= _this) {
			curr *= 2;
		}
		output += curr;
	}

	output.setIsNegative(sign);
	return output;
}

INT INT::abs(INT x) const {
	x.isNegative = false;
	return x;
}

INT INT::operator+(INT x) const{
	return add(x);
}
INT INT::operator+(int x) const {
	INT out(x);
	return add(x);
}
INT INT::operator+(_int64 x) const {
	INT out(x);
	return add(x);
}
INT INT::operator-(INT x) const {
	return subtract(x);
}
INT INT::operator-(int x) const {
	INT out(x);
	return subtract(x);
}
INT INT::operator-(_int64 x) const {
	INT out(x);
	return subtract(x);
}
INT INT::operator*(INT x) const {
	return multiply(x);
}
INT INT::operator*(int x) const {
	INT out(x);
	return multiply(x);
}
INT INT::operator*(_int64 x) const {
	INT out(x);
	return multiply(x);
}
INT INT::operator/(INT x) const {
	return divide(x);
}
INT INT::operator/(int x) const {
	INT out(x);
	return divide(x);
}
INT INT::operator/(_int64 x) const {
	INT out(x);
	return divide(x);
}

void INT::operator+=(INT x) {
	*this = add(x);
}
void INT::operator+=(int x) {
	INT out(x);
	operator+=(out);
}
void INT::operator+=(_int64 x) {
	INT out(x);
	operator+=(out);
}
void INT::operator++() {
	operator+=(1);
}
void INT::operator-=(INT x) {
	*this = subtract(x);
}
void INT::operator-=(int x) {
	INT out(x);
	operator-=(out);
}
void INT::operator-=(_int64 x) {
	INT out(x);
	operator-=(out);
}
void INT::operator--() {
	operator-=(1);
}
void INT::operator*=(INT x) {
	*this = multiply(x);
}
void INT::operator*=(int x) {
	INT out(x);
	operator*=(out);
}
void INT::operator*=(_int64 x) {
	INT out(x);
	operator*=(out);
}
void INT::operator/=(INT x) {
	*this = divide(x);
}
void INT::operator/=(int x) {
	INT out(x);
	operator/=(out);
}
void INT::operator/=(_int64 x) {
	INT out(x);
	operator/=(out);
}



bool INT::operator==(INT x) const {
	if (x.isNegative == isNegative) {
		if (x.getValue().size() == getValue().size()) {
			int s = getValue().size();
			for (int i = 0; i < s; i++) {
				if (x.getValue()[s - 1 - i] != getValue()[s - 1 - i]) { // in ASCII larger digits have larger numbers, so we don't worry about converting to int
					return false;
				}
			}
			return true;
		}
	}
	return false;
}
bool INT::operator==(int x) const {
	INT _x(x);
	return operator==(_x);
}
bool INT::operator==(_int64 x) const {
	INT _x(x);
	return operator==(_x);
}
bool INT::operator!=(INT x) const {
	return !operator==(x);
}
bool INT::operator>(INT x) const {
	if (x.isNegative == true && isNegative == false) {
		return true;
	}
	if (x.isNegative == false && isNegative == true) {
		return false;
	}
	if (x.isNegative == false && isNegative == false) { // both are positive
		if (x.getValue().size() > getValue().size()) {
			return false;
		}
		if (x.getValue().size() < getValue().size()) {
			return true;
		}
		// both have the same sign and the same number of digits
		int s = getValue().size();
		for (int i = 0; i < s; i++) {
			if (x.getValue()[s - 1 - i] > getValue()[s - 1 - i]) { // in ASCII larger digits have larger numbers, so we don't worry about converting to int
				return false;
			}
			if (x.getValue()[s - 1 - i] < getValue()[s - 1 - i]) {
				return true;
			}
		}
		return false; // are equal
	}
	// both are negative
	if (x.getValue().size() > getValue().size()) {
		return true;
	}
	if (x.getValue().size() < getValue().size()) {
		return false;
	}
	// both have the same sign and the same number of digits
	int s = getValue().size();
	for (int i = 0; i < s; i++) {
		if (x.getValue()[s - 1 - i] > getValue()[s - 1 - i]) { // in ASCII larger digits have larger numbers, so we don't worry about converting to int
			return true;
		}
		if (x.getValue()[s - 1 - i] < getValue()[s - 1 - i]) {
			return false;
		}
	}
	return false; // are equal
}
bool INT::operator>=(INT x) const {
	return operator>(x) || operator==(x);
}
bool INT::operator<(INT x) const {
	return !operator>=(x);
}
bool INT::operator<=(INT x) const {
	return !operator>(x);
}

INT::INT() {
	value = "0";
	isNegative = false;
}
INT::INT(std::string v) {
	setValueVisible(v);
}
INT::INT(int v) {
	setValue(v);
}
INT::INT(_int64 v) {
	setValue(v);
}

std::ostream& operator<<(std::ostream& stream, const INT& other) {
	stream << other.getValueVisible();
	return stream;
}