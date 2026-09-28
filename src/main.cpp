#include <iostream>
#include "Bencode.hpp"

using namespace std;

int main() {

    // Test integer
    string integerData = "i12345e";
    int index1 = 0;

    int number = parseInteger(integerData, index1);

    cout << "Integer: " << number << endl;


    // Test string
    string stringData = "11:hello world";
    int index2 = 0;

    string result = parseString(stringData, index2);

    cout << "String: " << result << endl;

    return 0;
}