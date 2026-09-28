#pragma once

#include <string>
#include <vector>
#include <map>

using namespace std;

const int INTEGER = 1;
const int STRING = 2;
const int LIST = 3;
const int DICTIONARY = 4;

struct BencodeValue {

    int type;

    int intValue;
    string stringValue;

    vector<BencodeValue> listValue;

    map<string, BencodeValue> dictionaryValue;
};

BencodeValue parseInteger(string data, int &index);
BencodeValue parseString(string data, int &index);
BencodeValue parseAny(string data, int &index);
BencodeValue parseList(string data, int &index);
BencodeValue parseDictionary(string data, int &index);