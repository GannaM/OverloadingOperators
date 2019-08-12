#include <iostream>
#include "fraction.hpp"

using namespace std;

int main() {
    Fraction f1, f2, sum, diff, prod, quo;
    cout << "Enter num & den for first fraction: ";
    cin >> f1;
    cout << "Enter num & den for second fraction: ";
    cin >> f2;
    cout << "Fraction 1 is " << f1 << endl;
    cout << "Fraction 2 is " << f2 << endl;
    
    sum = f1 + f2;
    diff = f1 - f2;
    prod = f1 * f2;
    quo = f1 / f2;
    
    cout << "Sum is " << sum;
    cout << "Difference is " << diff;
    cout << "Product is " << prod;
    cout << "Quotient is " << quo;
    
    if (f1 == f2)
        cout << "Equal" << endl;
    if (f1 != f2)
        cout << "Not equal" << endl;
    
    cout << "Preincrements: " << ++f1 << " " << ++f2 << endl;
    cout << "Postincrements: " << f1++ << " " << f2++ << endl;
    
    cout << "After post increments: " << f1 << " " << f2 << endl;

    return 0;
}
