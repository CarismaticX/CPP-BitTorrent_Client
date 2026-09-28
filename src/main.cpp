#include <iostream>
#include "Bencode.hpp"

using namespace std;

int main() {

    string data = "ll5:helloei42ee";

    int index = 0;

    BencodeValue result = parseAny(data, index);

    cout << "List parsed successfully!" << endl;

    cout << "First element: "
         << result.listValue[0].stringValue << endl;

    cout << "Second element: "
         << result.listValue[1].intValue << endl;


    if (result.type == LIST) {
    cout << "Correctly identified as a list!" << endl;
     }     

    return 0;
}