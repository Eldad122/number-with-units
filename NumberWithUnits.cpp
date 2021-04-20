#include <iostream>
#include <fstream>
#include <map>
#include "NumberWithUnits.hpp"
using namespace std;

namespace ariel {

    static map<string, map<string, double> > table;

    /**
     * @brief convert val of unit1 to unit2
     *        For Example:
     *              convert from 3[km] to 3000[m],
     *              convert from 30[sec] to 0.5[min],
     *              convert from 3.7[ton] to 3700[kg]. etc.
     * 
     * @param val   A given value of unit1 to be converted to unit2.
     * @param from  source unit
     * @param to    destination unit
     * @return      double The converted value
     */
    double convertFromTo(double val, const string from, const string to){
        if(from == to) {return val;}
        try {
            return val * table.at(from).at(to);
        }
        catch(const exception& e) {
            throw invalid_argument{"Units do not match - ["+from+"] cannot be converted to ["+to+"]"};
        }
    }

    void foo(const string unit1, const string unit2){
        for(auto [key, value] : table[unit2]){
            double w = table[unit1][unit2] * value;
            table[unit1][key] = w;
            table[key][unit1] = 1/w;
        }
    }
    /**
     * @brief Read a text file with each line in the format:
     *          "1 <unit1> = <ratio> <unit2>"nit
     *        For example:
     *          "1 km = 1000 m"
     *        And build a table of units ratios.
     * 
     * @param units_file A file stream contains the units as described above.
     */
    void NumberWithUnits::read_units(ifstream& units_file){
        string buff, unit1, unit2;
        double n1, n2;
        while(units_file >> n1 >> unit1 >> buff >> n2 >> unit2){
            table[unit1][unit2] = n2;
            table[unit2][unit1] = 1/n2;
            foo(unit1, unit2);
            foo(unit2, unit1);
        }
    }

    //=============================================================================================
    /* Overloading the in\out stream operators: {<<, >>} */
    //=============================================================================================
    ostream& operator<<(ostream& out, const NumberWithUnits& t){
        out << t.amount << "[" << t.unit << "]";
        return out;
    }
    istream& operator>>(istream& in, NumberWithUnits& t){
        string s;
        in >> t.amount >> s >> t.unit;
        return in;
    }
    //=============================================================================================
    /* Overloading the arithmetic operators: {+, +=, -, -=} */
    //=============================================================================================
    NumberWithUnits operator+(const NumberWithUnits& n1, const NumberWithUnits& n2) {
        double converted = convertFromTo(n2.amount, n2.unit, n1.unit);
        return NumberWithUnits(n1.amount+converted, n1.unit);
    }
    NumberWithUnits operator+(const NumberWithUnits& n, double a) {
        return NumberWithUnits(n.amount+a, n.unit);
    }
    NumberWithUnits operator+=(NumberWithUnits& n1, const NumberWithUnits& n2) {
        n1.amount += convertFromTo(n2.amount, n2.unit, n1.unit);
        return n1;
    }
    NumberWithUnits operator-(const NumberWithUnits& n1, const NumberWithUnits& n2) {
        double converted = convertFromTo(n2.amount, n2.unit, n1.unit);
        return NumberWithUnits(n1.amount-converted, n1.unit);
    }
    NumberWithUnits operator-(const NumberWithUnits& n) {
        return NumberWithUnits(-n.amount, n.unit);
    }
    NumberWithUnits operator-=(NumberWithUnits& n1, const NumberWithUnits& n2) {
        double converted = convertFromTo(n2.amount, n2.unit, n1.unit);
        return NumberWithUnits(n1.amount-=converted, n1.unit);
    }

    // Overloading the Increament\Decreament operators: {++x, x++, --x, x--}
    NumberWithUnits operator++(NumberWithUnits& n) {
        return NumberWithUnits(++n.amount, n.unit);
    }
    NumberWithUnits operator++(NumberWithUnits& n, int) {
        return NumberWithUnits(n.amount++, n.unit);
    }
    NumberWithUnits operator--(NumberWithUnits& n) {
        return NumberWithUnits(--n.amount, n.unit);
    }
    NumberWithUnits operator--(NumberWithUnits& n, int) {
        return NumberWithUnits(n.amount--, n.unit);
    }

    // Overloading the Multiplication operator: {number*x, x*number, x*=number, number*=x}
    NumberWithUnits operator*(NumberWithUnits& n, double num) {
        return NumberWithUnits(n.amount*num, n.unit);
    }
    NumberWithUnits operator*(double num, NumberWithUnits& n) {
        return NumberWithUnits(n.amount*num, n.unit);
    }
    NumberWithUnits operator*=(NumberWithUnits& n, double num) {
        return NumberWithUnits(n.amount*=num, n.unit);
    }
    NumberWithUnits operator*=(double num, NumberWithUnits& n) {
        return NumberWithUnits(num*=n.amount, n.unit);
    }

    // Overloading the comparison operators: {>, >=, <, <=, ==, !=}

    int compare(const NumberWithUnits& n1, const NumberWithUnits& n2){
        double eps = 0.00001;
        double x = n1.amount - convertFromTo(n2.amount, n2.unit, n1.unit);
        double y = convertFromTo(n2.amount, n2.unit, n1.unit) - n1.amount;
        if(x > eps){
            return 1;
        }
        else if(y > eps){
            return -1;
        }
        else{
            return 0;
        }
    }

    bool operator>(const NumberWithUnits& n1, const NumberWithUnits& n2){
        return compare(n1, n2) > 0;
    }
    bool operator>=(const NumberWithUnits& n1, const NumberWithUnits& n2){
        return compare(n1, n2) >= 0;
    }
    bool operator<(const NumberWithUnits& n1, const NumberWithUnits& n2){
        return compare(n1, n2) < 0;
    }
    bool operator<=(const NumberWithUnits& n1, const NumberWithUnits& n2){
        return compare(n1, n2) <= 0;
    }
    bool operator==(const NumberWithUnits& n1, const NumberWithUnits& n2){
        return compare(n1, n2) == 0;
    }
    bool operator!=(const NumberWithUnits& n1, const NumberWithUnits& n2){
        return compare(n1, n2) != 0;
    }
}