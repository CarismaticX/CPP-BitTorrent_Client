#pragma once

#include <string>
#include <vector>

using namespace std;

const int INTEGER = 1;
const int STRING = 2;
const int LIST = 3;

struct BencodeValue {

    int type;

    int intValue;
    string stringValue;
    vector<BencodeValue> listValue;
};

BencodeValue parseInteger(string data, int &index);
BencodeValue parseString(string data, int &index);
BencodeValue parseAny(string data, int &index);
BencodeValue parseList(string data, int &index);