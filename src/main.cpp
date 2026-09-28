#include <iostream>
#include "Bencode.hpp"

using namespace std;

int main() {

    string data =
    "d"
    "8:announce"
    "10:http://abc"
    "4:info"
        "d"
        "4:name"
        "8:test.txt"
        "6:length"
        "i1000e"
        "12:piece length"
        "i256e"
        "e"
    "e";

    int index = 0;

    BencodeValue result = parseAny(data, index);

    if (result.type == DICTIONARY) {

        cout << "Outer dictionary parsed successfully!" << endl;

        BencodeValue info = result.dictionaryValue["info"];

        if (info.type == DICTIONARY) {

            cout << "Inner dictionary parsed successfully!" << endl;

            cout << "name: "
                 << info.dictionaryValue["name"].stringValue
                 << endl;

            cout << "name: "
                 << info.dictionaryValue["name"].stringValue
                 << endl;

            cout << "length: "
                 << info.dictionaryValue["length"].intValue
                 << endl;

            cout << "piece length: "
                 << info.dictionaryValue["piece length"].intValue
                 << endl;     
        }
    }

    return 0;
}