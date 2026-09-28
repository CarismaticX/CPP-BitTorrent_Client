#include "Bencode.hpp"
#include <stdexcept>

using namespace std;


// Bencode integer format:
// i42e
// i100e
// i-25e

int parseInteger(string data, int &index) {

    // Integer must start with 'i'
    if (data[index] != 'i') {
        throw runtime_error("Expected integer");
    }

    // Move past 'i'
    index++;

    string number = "";

    // Store all characters until 'e'
    while (data[index] != 'e') {
        number += data[index];
        index++;
    }

    // Move past 'e'
    index++;

    // Convert string to integer
    return stoi(number);
}


// Bencode string format:
// 5:hello
// 4:name
// 11:hello world

string parseString(string data, int &index) {

    // Store the length of the string
    string lengthString = "";

    // Read the length until ':'
    while (data[index] != ':') {
        lengthString += data[index];
        index++;
    }

    // Convert length from string to integer
    int length = stoi(lengthString);

    // Move past ':'
    index++;

    // Store the actual string
    string result = "";

    // Read exactly 'length' characters
    for (int i = 0; i < length; i++) {
        result += data[index];
        index++;
    }

    return result;
}