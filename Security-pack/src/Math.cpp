#include <iostream>
#include <ctime>
#include <algorithm>
#include <string>
#include "Math.h"

namespace Math {
	int Power(int base, int power) {
        int output = 1;
        int curOutput = base;
        int curPower = 1;
        int powers = 0;
        while (powers != power) {
            while (powers + curPower * 2 < power) {
                curPower *= 2;
                curOutput *= curOutput;
            }
            output *= curOutput;
            powers += curPower;
            curPower = 1;
            curOutput = base;
        }
        return output;
	}
	int Power(int base, int power, int modulo) {
        _int64 output = 1;
        _int64 curOutput = base;
        _int64 curPower = 1;
        _int64 powers = 0;
        while (powers != power) {
            while (powers + curPower * 2 < power) {
                curPower *= 2;
                curOutput *= curOutput;
                curOutput %= modulo;
            }
            output *= curOutput;
            output %= modulo;
            powers += curPower;
            curPower = 1;
            curOutput = base;
        }
        return (int)output;
	}
    _int64 Power(_int64 base, _int64 power, _int64 modulo) {
        _int64 output = 1;
        _int64 curOutput = base;
        _int64 curPower = 1;
        _int64 powers = 0;
        while (powers != power) {
            while (powers + curPower * 2 < power) {
                curPower *= 2;
                curOutput *= curOutput;
                curOutput %= modulo;
            }
            output *= curOutput;
            output %= modulo;
            powers += curPower;
            curPower = 1;
            curOutput = base;
        }
        return output;
    }

	_int64 InverseModulo(int _a, _int64 modulo) { // source: https://www.geeksforgeeks.org/multiplicative-inverse-under-modulo-m/
        _int64 m0 = modulo;
        _int64 y = 0, x = 1;
        _int64 a = _a;

        if (modulo == 1) {
            return 0;
        }

        while (a > 1)
        {
            // q is quotient 
            _int64 q = a / modulo;
            _int64 t = modulo;

            // m is remainder now, process same as 
            // Euclid's algo 
            modulo = a % modulo, a = t;
            t = y;

            // Update y and x 
            y = x - q * y;
            x = t;
        }

        // Make x positive 
        if (x < 0) {
            x += m0;
        }

        return x;
	}

    bool IsPrime(_int64 p) {
        if (p % 2 == 0 && p != 2) {
            return false;
        }
        for (_int64 i = 3; i < sqrt(p); i += 2) {
            if (p % i == 0) {
                return false;
            }
        }
        return true;
    }
    _int64 FindBigPrime(_int64 modulo) {
        _int64 p = 0;
        for (int i = 0; i < 1; i++) {
            p = rand() % modulo;
        }
        
        if (p % 2 == 0) {
            p++;
        }

        for (_int64 i = p; i < modulo; i += 2) {
            if (IsPrime(i)) {
                return i;
            }
        }
        for (_int64 i = p; i > 1; i -= 2) {
            if (IsPrime(i)) {
                return i;
            }
        }
        return 2;
    }
    int GCD(_int64 a, _int64 b) {
        while (a != b && a != 0 && b != 0) {
            if (a > b) {
                a = a % b;
            }
            else {
                b = b % a;
            }
        }
        if (a == 0) {
            return (int)b;
        }
        return (int)a;
    }
    int FindCoprime(_int64 a, int min, int modulo) {
        _int64 start = min;
        start += rand() % modulo;
        while (true) {
            if (GCD(a, start) == 1) {
                return (int)start;
            }
            start++;
        }
    }

    void InitRSA(_int64 &n, _int64 &publicKey, _int64 &privateKey, _int64 modulo, int min) {
        _int64 p, q;
        p = FindBigPrime(modulo);
        q = FindBigPrime(modulo);
        n = p * q;
        _int64 phi = (p - 1) * (q - 1);

        publicKey = FindCoprime(phi, min, modulo);
        privateKey = InverseModulo(publicKey, phi);
    }

    int characterBase = 127 + 9 + 1; // base of number system in which characters are defined (ASCII + Polish characters + 1)
    int Repair(char c) {
        if (c == '\245') { // ¹
            return 128;
        }
        if (c == '\206') { // æ
            return 129;
        }
        if (c == '\251') { // ê
            return 130;
        }
        if (c == '\210') { // ³
            return 131;
        }
        if (c == '\344') { // ñ
            return 132;
        }
        if (c == '\242') { // ó
            return 133;
        }
        if (c == '\230') { // œ
            return 134;
        }
        if (c == '\253') { // Ÿ
            return 135;
        }
        if (c == '\276') { // ¿
            return 136;
        }

        if (c < 0 || c > 136) {
            return '?';
        }
        return c;
    }
    char ReadCharacter(int character) {
        if (character == 128) { // ¹
            return '\245';
        }
        if (character == 129) { // æ
            return '\206';
        }
        if (character == 130) { // ê
            return '\251';
        }
        if (character == 131) { // ³
            return '\210';
        }
        if (character == 132) { // ñ
            return '\344';
        }
        if (character == 133) { // ó
            return '\242';
        }
        if (character == 134) { // œ
            return '\230';
        }
        if (character == 135) { // Ÿ
            return '\253';
        }
        if (character == 136) { // ¿
            return '\276';
        }

        if (character < 0 || character > 136) {
            return '?';
        }
        return character;
    }
    std::string ReadChunk(int number) {
        std::string output = "";
        while (number > 0) {
            int character = number % characterBase;
            char c = ReadCharacter(character);
            output += c;
            number /= characterBase;
        }
        return output;
    }

    std::string StringToData(std::string text) {
        // we store data in numbers in base system based on variable base (first character is the smallest)
        int curOutput = 0;
        int curPower = 1;
        std::string output = "-";
        int i = 0;
        while (i < text.size()) {
            int character = Repair(text[i]);
            curOutput += curPower * character;
            curPower *= characterBase;
            i++;
            if (i % 3 == 0) { // end of chunk
                output += std::to_string(curOutput);
                output += '-';
                curOutput = 0;
                curPower = 1;
            }
        }
        if (curOutput > 0) {
            output += std::to_string(curOutput);
            output += '-';
        }
        return output;
    }
    std::string DataToString(std::string data) {
        std::string output = "";
        int i = 0;
        while (i < data.size()) {
            if (data[i] == '-') { // a new chunk begins
                i++;
                std::string chunk = "";
                if (i < data.size()) { // if the last '-' wasn't the end of the message
                    while (data[i] != '-' && i < data.size() - 1) { // until the next chunk starts or the index gets out of range
                        chunk += data[i];
                        i++;
                    }
                    int number = std::stoi(chunk);
                    output += ReadChunk(number);
                }
            }
            else {
                i++; // ignore unseparated values
            }
        }
        return output;
    }

    std::string PerformRSA(std::string message, _int64 key, _int64 modulo) {
        std::string output = "-";
        _int64 number = 0;
        for (int i = 1; i < message.size(); i++) {
            if (message[i] != '-') {
                std::string piece = "";
                piece += message[i];
                number += std::stoi(piece);
                number *= 10;
            }
            else {
                number /= 10; // one time more in the if statement (at the end)
                _int64 _number = Power(number, key, modulo);
                std::string piece = std::to_string(_number);
                output += piece;
                output += '-';
                number = 0;
            }
        }
        return output;
    }

    bool IsNumber(std::string n) {
        for (int i = 0; i < n.size(); i++) {
            if (n[i] < 48 || n[i] > 57) {
                return false;
            }
        }
        return true;
    }
}
