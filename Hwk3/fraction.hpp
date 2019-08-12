#include <stdio.h>
#include <iostream>
#include <cmath>
using namespace std;


class Fraction {
    
    // Overloaded operators:
    friend ostream &operator << (ostream &, const Fraction &);
    friend istream &operator >> (istream&, Fraction &);
    
public:
    Fraction(int = 1, int = 1);
    
    // Overloaded Operators:
    Fraction operator + (const Fraction &rhs) const;
    Fraction operator - (const Fraction &rhs) const;
    Fraction operator * (const Fraction &rhs) const;
    Fraction operator / (const Fraction &rhs) const;
    Fraction &operator ++ (); // preincrement operator
    Fraction &operator ++ (int); // postincrement operator
    bool operator == (const Fraction &rhs) const;
    bool operator != (const Fraction &rhs) const;
    
    
private:
    int numerator, denominator;
    
    int gcd(int, int) const;
    void reduce(Fraction) const;
    void reciprocal();
    
    Fraction sum(Fraction) const;
    Fraction subtract(Fraction) const;
    Fraction multiply(Fraction) const;
    Fraction divide(Fraction) const;

};

//-----------------------------------------------------------------------
//OVERLOADED OPERATORS: begin
//-----------------------------------------------------------------------

// OUTPUT
ostream &operator << (ostream &output, const Fraction &f) {
    if (f.numerator == 0) {
        output << "0" << endl;
    }
    else {
        output << f.numerator << "/" << f.denominator << endl;
    }
    return output;
}

// INPUT
istream &operator >> (istream &input, Fraction &f) {
    input >> f.numerator >> f.denominator;
    return input;
}

// SUM
Fraction Fraction::operator + (const Fraction &rhs) const {
    return sum(rhs);
}

// SUBTRACTION
Fraction Fraction::operator - (const Fraction &rhs) const {
    return subtract(rhs);
}

// MULTIPLICATION
Fraction Fraction::operator * (const Fraction &rhs) const {
    return multiply(rhs);
}

// DIVISION
Fraction Fraction::operator / (const Fraction &rhs) const {
    return divide(rhs);
}

// PREincrement
// returns a reciprocal
Fraction &Fraction::operator ++ () {
    reciprocal();
    return *this;
}

// POSTincrement
// returns fraction and then does a reciprocal
Fraction &Fraction::operator ++ (int) {
    Fraction temp = *this;
    reciprocal();
    return temp;
}

// EQUALITY
bool Fraction::operator == (const Fraction &rhs) const {
    return (numerator == rhs.numerator && denominator == rhs.denominator);
}

// NON-EQUALITY
bool Fraction::operator != (const Fraction &rhs) const {
    return (numerator != rhs.numerator || denominator != rhs.denominator);
}

//-----------------------------------------------------------------------
//OVERLOADED OPERATORS: end
//-----------------------------------------------------------------------


// Reduces Fraction to its simplest form
void Fraction::reduce(Fraction f) const {
    int gcd_r = gcd(numerator, denominator);
    f.numerator /= gcd_r;
    f.denominator /= gcd_r;
}

// Constructor
Fraction::Fraction(int num, int den) {
    // If numerator or denominator are equal to zero, exit program with Error code 1.
    if (num == 0 || den <= 0) {
        cout << "Invalid fraction declaration" << endl;
        exit(1);
    }
    numerator = num;
    denominator = den;
    reduce(*this);
}

// Returns the greatest common divisor of two numbers: numerator and denominator
int Fraction::gcd(int num, int den) const {
    // Everything divides 0
    if (num == 0 || den == 0)
        return 0;
    
    // base case
    if (abs(num) == den)
        return num;
    
    // a is greater
    if (abs(num) > den)
        return gcd(abs(num)-den, den);
    return gcd(abs(num), den-abs(num));
}

// Swaps values of numerator and denominator
void Fraction::reciprocal() {
    int temp = numerator;
    numerator = denominator;
    denominator = temp;
    
    // Make sure only numerator retains a negative value if any
    if (denominator < 0) {
        denominator = abs(denominator);
        numerator = 0 - numerator;
    }
}

// Returns sum of two fractions
Fraction Fraction::sum(Fraction f) const {
    
    // Check if either Fraction is equal to 0
    if ((denominator == 0 && f.denominator == 0) || (f.denominator == 0)) {
        return *this;
    }
    if (denominator == 0) {
        return f;
    }

    // If both Fractions are non-zero, proceed with summing them
    Fraction result;
    int sum_of_numerators;
    int common_denominator;
    
    // If the denominators are equal just sum the numerators
    if (denominator == f.denominator) {
        sum_of_numerators = numerator + f.numerator;
        common_denominator = denominator;
    }
    
    // If denominators are not equal
    else {
        // Find common denominator
        common_denominator = denominator * f.denominator;
        // Multiply each numerators by the opposite denominator and then sum
        sum_of_numerators = numerator * f.denominator + f.numerator * denominator;
    }
    
    result.numerator = sum_of_numerators;
    result.denominator = common_denominator;
    reduce(result);
    
    return result;
}

// Returns subtraction of two fractions
Fraction Fraction::subtract(Fraction f) const {
    
    //If Fraction f is zero, there is nothing to subtract
    if (f.denominator == 0) {
        return *this;
    }
    
    Fraction subtraction;
    int subtraction_of_numerators;
    int common_denominator;
    
    // If the denominators are equal just subtract the numerators
    if (denominator == f.denominator) {
        subtraction_of_numerators = numerator - f.numerator;
        common_denominator = denominator;
    }
    
    // If denominators are not equal
    else {
        // Find common denominator
        common_denominator = denominator * f.denominator;
        // Multiply each numerators by the opposite denomintar and then subtract
        subtraction_of_numerators = numerator * f.denominator - f.numerator * denominator;
    }
    
    // Find gcd for the resulted denominator and numerator to reduce the fraction

    if (subtraction_of_numerators == 0) {
        subtraction.numerator = 0;
        subtraction.denominator = 0;
    }
    else {
        subtraction.numerator = subtraction_of_numerators;
        subtraction.denominator = common_denominator;
        reduce(subtraction);
    }

    
    return subtraction;
}

Fraction Fraction::multiply(Fraction f) const {
    
    //Check is f is zero, then the result of multiplication is also 0
    if (f.denominator == 0) {
        return f;
    }
    
    Fraction product;
    
    int num = numerator * f.numerator;
    int den = denominator * f.denominator;
    int gcd = this->gcd(num, den);
    
    product.numerator = num / gcd;
    product.denominator = den / gcd;
    
    return product;
}

Fraction Fraction::divide(Fraction f) const {
    // Dividing two fractions is the same as multiplying it by a reciprocal
    f.reciprocal();
    return this->multiply(f);
}
