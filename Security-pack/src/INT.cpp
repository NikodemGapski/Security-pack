#include <string>
#include "Math.h"
#include "INT.h"


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


void INT::setValue(std::string v) {
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


INT INT::add(INT x) const {
	INT output;
	output.value = "";

	int remainder = 0;
	int size = x.getValue().size();
	int _size = getValue().size();

	bool isGreater = false; // is x greater than this value
	if (getValue().size() < size) {
		size = getValue().size();
		_size = x.getValue().size();
		isGreater = true;
	}
	for (int i = 0; i < size; i++) {
		int a = x.getValue()[i] - '0' + getValue()[i] - '0';
		output.value += (a + remainder) % 10 + '0';
		remainder = a / 10;
	}

	if (isGreater == true) {
		for (int i = size; i < _size; i++) {
			int a = x.getValue()[i] - '0';
			output.value += (a + remainder) % 10 + '0';
			remainder = a / 10;
		}
	}else {
		for (int i = size; i < _size; i++) {
			int a = getValue()[i] - '0';
			output.value += (a + remainder) % 10 + '0';
			remainder = a / 10;
		}
	}
	if (remainder > 0) {
		output.value += remainder + '0';
	}
	return output;
}


INT INT::operator+(INT x) const{
	return add(x);
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
	setValue(0);
}
INT::INT(std::string v) {
	setValue(v);
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