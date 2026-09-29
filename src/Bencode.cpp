#include "Bencode.hpp"
#include <stdexcept>

using namespace std;


// Bencode integer format:
// i42e
// i100e
// i-25e

BencodeValue parseInteger(string data, int &index) {

    if (data[index] != 'i') {
        throw runtime_error("Expected integer");
    }

    index++;

    string number = "";

    while (data[index] != 'e') {
        number += data[index];
        index++;
    }

    index++;

    BencodeValue value;

    value.type = INTEGER;
    value.intValue = stoi(number);

    return value;
}


// Bencode string format:
// 5:hello
// 4:name
// 11:hello world

BencodeValue parseString(string data, int &index) {

    string lengthString = "";

    while (data[index] != ':') {
        lengthString += data[index];
        index++;
    }

    int length = stoi(lengthString);

    index++;

    string result = "";

    for (int i = 0; i < length; i++) {
        result += data[index];
        index++;
    }

    BencodeValue value;

    value.type = STRING;
    value.stringValue = result;

    return value;
}


// Decide what type of Bencode data we are looking at

BencodeValue parseAny(string data, int &index) {

    if (data[index] == 'i') {
        return parseInteger(data, index);
    }

    if (data[index] == 'l') {
        return parseList(data, index);
    }

    if (data[index] >= '0' && data[index] <= '9') {
        return parseString(data, index);
    }
    if (data[index] == 'd') {
    return parseDictionary(data, index);
    }

    throw runtime_error("Unknown Bencode type");
}


// Bencode list format:
// l5:helloi42ee
//
// Means:
// ["hello", 42]

BencodeValue parseList(string data, int &index) {

    // Current character should be 'l'
    if (data[index] != 'l') {
        throw runtime_error("Expected list");
    }

    // Move past 'l'
    index++;

    BencodeValue value;

    value.type = LIST;

    // Keep parsing until we reach 'e'
    while (data[index] != 'e') {

        BencodeValue element = parseAny(data, index);

        value.listValue.push_back(element);
    }

    // Move past 'e'
    index++;

    return value;
}



BencodeValue parseDictionary(string data, int &index) {

    // Current character should be 'd'
    if (data[index] != 'd') {
        throw runtime_error("Expected dictionary");
    }

    // Move past 'd'
    index++;

    BencodeValue value;

    value.type = DICTIONARY;

    // Keep reading key-value pairs until 'e'
    while (data[index] != 'e') {

        // Dictionary key
        BencodeValue key = parseString(data, index);

        // Dictionary value
        BencodeValue dictionaryValue = parseAny(data, index);

        // Store key -> value
        value.dictionaryValue[key.stringValue] = dictionaryValue;
    }

    // Move past 'e'
    index++;

    return value;
}


string bencode(const BencodeValue& value) {

    if (value.type == INTEGER) {

        return "i" + to_string(value.intValue) + "e";
    }

    if (value.type == STRING) {

        return to_string(value.stringValue.size())
             + ":"
             + value.stringValue;
    }

    if (value.type == LIST) {

        string result = "l";

        for (auto item : value.listValue) {
            result += bencode(item);
        }

        result += "e";

        return result;
    }

    if (value.type == DICTIONARY) {

        string result = "d";

        for (auto entry : value.dictionaryValue) {

            result += to_string(entry.first.size());
            result += ":";
            result += entry.first;

            result += bencode(entry.second);
        }

        result += "e";

        return result;
    }

    throw runtime_error("Unknown Bencode type");
}