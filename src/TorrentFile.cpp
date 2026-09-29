#include "TorrentFile.hpp"
#include <fstream>
#include <stdexcept>

using namespace std;

string readTorrentFile(string filePath) {

    ifstream file(filePath, ios::binary);

    if (!file) {
        throw runtime_error("Could not open torrent file");
    }

    string data(
        (istreambuf_iterator<char>(file)),
        istreambuf_iterator<char>()
    );

    return data;
}