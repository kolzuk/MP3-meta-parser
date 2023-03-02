#include <lib/MP3parser.h>

#include <iostream>
#include <filesystem>

int main(int argc, char** argv) {
    std::filesystem::path path = argv[1];
    CParserMP3 parser;
    parser.ReadFile(path);
    parser.ReadFlags();
    parser.ReadSize();
    parser.ReadFrames();
    std::cout << "-----------META_INFORMATION-----------" << '\n';
    parser.ShowFrames();
    return 0;
}
