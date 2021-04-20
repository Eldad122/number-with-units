#include <iostream>
#include <map>
#include <string>
using namespace std;

namespace ariel {
    class NumberWithUnits{

    private:
        double amount;
        string unit;

    public:
        NumberWithUnits(double amount, string unit){
            this->amount = amount;
            this->unit = unit;
        }
        ~NumberWithUnits(){}
        static void read_units(ifstream& units_file);
        friend int compare(const NumberWithUnits& n1, const NumberWithUnits& n2);

        /* Overloading the in/out stream operators - Declerations */
        friend ostream& operator<<(ostream& out, const NumberWithUnits& t);
        friend istream& operator>>(istream& in, NumberWithUnits& t);

        /* Overloading the arithmetic operators */
        friend NumberWithUnits operator+(const NumberWithUnits& n1, const NumberWithUnits& n2);
        friend NumberWithUnits operator+(const NumberWithUnits& n, double a);
        friend NumberWithUnits operator+=(NumberWithUnits& n1, const NumberWithUnits& n2);
        friend NumberWithUnits operator-(const NumberWithUnits& n1, const NumberWithUnits& n2);
        friend NumberWithUnits operator-(const NumberWithUnits& n);
        friend NumberWithUnits operator-=(NumberWithUnits& n1, const NumberWithUnits& n2);

        /* Increment operations overiding */
        friend NumberWithUnits operator++(NumberWithUnits& n);
        friend NumberWithUnits operator++(NumberWithUnits& n, int);
        friend NumberWithUnits operator--(NumberWithUnits& n);
        friend NumberWithUnits operator--(NumberWithUnits& n, int);

        /* Multiplication operations overiding */
        friend NumberWithUnits operator*(NumberWithUnits& n, double num);
        friend NumberWithUnits operator*(double num, NumberWithUnits& n);
        friend NumberWithUnits operator*=(NumberWithUnits& n, double num);
        friend NumberWithUnits operator*=(double num, NumberWithUnits& n);

        /* Overloading the comparison operators - Declerations */
        friend bool operator>(const NumberWithUnits& n1, const NumberWithUnits& n2);
        friend bool operator>=(const NumberWithUnits& n1, const NumberWithUnits& n2);
        friend bool operator<(const NumberWithUnits& n1, const NumberWithUnits& n2);
        friend bool operator<=(const NumberWithUnits& n1, const NumberWithUnits& n2);
        friend bool operator==(const NumberWithUnits& n1, const NumberWithUnits& n2);
        friend bool operator!=(const NumberWithUnits& n1, const NumberWithUnits& n2);
    };
}