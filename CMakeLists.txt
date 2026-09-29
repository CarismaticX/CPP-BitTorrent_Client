cmake_minimum_required(VERSION 3.20)

project(BitTorrentClient)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenSSL REQUIRED)

add_executable(BitTorrentClient
    src/main.cpp
    src/Bencode.cpp
    src/TorrentFile.cpp
    src/SHA1.cpp
)

target_include_directories(BitTorrentClient PRIVATE
    include
)

target_link_libraries(BitTorrentClient PRIVATE
    OpenSSL::Crypto
)