#include <iostream>
#include "TorrentFile.hpp"
#include "Bencode.hpp"
#include "SHA1.hpp"

using namespace std;

int main() {

    // Read and parse the torrent file
    string data = readTorrentFile("torrents/test.torrent");

    cout << "Torrent file loaded successfully!" << endl;
    cout << "File size: " << data.size() << " bytes" << endl;

    int index = 0;
    BencodeValue torrent = parseAny(data, index);

    cout << "Torrent parsed successfully!" << endl;

    // Get the info dictionary
    BencodeValue info = torrent.dictionaryValue["info"];

    cout << "\nInfo dictionary keys:\n";

    for (auto entry : info.dictionaryValue) {
        cout << "- " << entry.first << endl;
    }

    // Get files
    BencodeValue files = info.dictionaryValue["files"];

    cout << "\nNumber of files: "
         << files.listValue.size()
         << endl;

    cout << "\nFiles:\n";

    for (int i = 0; i < files.listValue.size(); i++) {

        BencodeValue file = files.listValue[i];

        cout << "\nFile " << i + 1 << ":" << endl;

        cout << "- length: "
             << file.dictionaryValue["length"].intValue
             << " bytes" << endl;

        BencodeValue path = file.dictionaryValue["path"];

        cout << "- path: ";

        for (int j = 0; j < path.listValue.size(); j++) {

            cout << path.listValue[j].stringValue;

            if (j < path.listValue.size() - 1) {
                cout << "/";
            }
        }

        cout << endl;
    }

    BencodeValue name = info.dictionaryValue["name"];

    cout << "\nTorrent Name: "
         << name.stringValue
         << endl;

    BencodeValue pieceLength = info.dictionaryValue["piece length"];

    cout << "Piece Length: "
         << pieceLength.intValue
         << " bytes"
         << endl;

    // Each piece hash is 20 bytes (SHA-1)
    BencodeValue pieces = info.dictionaryValue["pieces"];

    cout << "\nPieces data size: "
         << pieces.stringValue.size()
         << " bytes"
         << endl;

    cout << "Number of pieces: "
         << pieces.stringValue.size() / 20
         << endl;

BencodeValue testDictionary;
testDictionary.type = DICTIONARY;

BencodeValue testName;
testName.type = STRING;
testName.stringValue = "test.txt";

BencodeValue testLength;
testLength.type = INTEGER;
testLength.intValue = 1000;

testDictionary.dictionaryValue["name"] = testName;
testDictionary.dictionaryValue["length"] = testLength;

cout << "\nEncoded dictionary: "
     << bencode(testDictionary)
     << endl;




     string encodedInfo = bencode(info);

cout << "\nEncoded info size: "
     << encodedInfo.size()
     << " bytes"
     << endl;




     string infoHash = calculateSHA1(encodedInfo);

     cout << "Info Hash: "
          << infoHash
          << endl;
          
    return 0;
}