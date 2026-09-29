#include "SHA1.hpp"

#include <openssl/evp.h>
#include <sstream>
#include <iomanip>
#include <stdexcept>

using namespace std;

string calculateSHA1(const string& data) {

    EVP_MD_CTX* context = EVP_MD_CTX_new();

    if (context == nullptr) {
        throw runtime_error("Failed to create SHA-1 context");
    }

    if (EVP_DigestInit_ex(context, EVP_sha1(), nullptr) != 1) {
        EVP_MD_CTX_free(context);
        throw runtime_error("Failed to initialize SHA-1");
    }

    if (EVP_DigestUpdate(context, data.data(), data.size()) != 1) {
        EVP_MD_CTX_free(context);
        throw runtime_error("Failed to update SHA-1");
    }

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hashLength = 0;

    if (EVP_DigestFinal_ex(context, hash, &hashLength) != 1) {
        EVP_MD_CTX_free(context);
        throw runtime_error("Failed to calculate SHA-1");
    }

    EVP_MD_CTX_free(context);

    stringstream result;

    for (unsigned int i = 0; i < hashLength; i++) {
        result << hex
               << setw(2)
               << setfill('0')
               << static_cast<int>(hash[i]);
    }

    return result.str();
}