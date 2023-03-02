#include "MP3parser.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <filesystem>

const uint8_t FRAME_HEADER_SIZE = 10;
const uint8_t FRAME_SIZE_BYTES = 4;

void CParserMP3::ReadFile(const std::filesystem::path& path) {
    std::ifstream file(path);

    assert(file.is_open());

    char byte;
    while (file.get(byte)) {
        bytes.push_back(byte);
    }
}

void CParserMP3::ReadFlags() {
    unsigned char byte = bytes[5]; // Flags field (%abcd0000)
    unsynchronisation = (byte >> 7) & 1; //a
    extended_header = (byte >> 6) & 1; //b
    experimental_indicator = (byte >> 5) & 1; //c
    footer_present = (byte >> 4) & 1; //d
}

void CParserMP3::ReadSize() { // reading a tag size
    unsigned char first_byte = bytes[6];
    unsigned char second_byte = bytes[7];
    unsigned char third_byte = bytes[8];
    unsigned char fourth_byte = bytes[9];
    tag_size = (static_cast<uint32_t> (fourth_byte)) +
               (static_cast<uint32_t> (third_byte) << 7) +
               (static_cast<uint32_t> (second_byte) << 14) +
               (static_cast<uint32_t> (first_byte) << 21); // with a garbage front zero
}

void CParserMP3::ReadFrames() {
    if (!frames.empty()) {
        return;
    }
    uint64_t current_position = FRAME_HEADER_SIZE;
    uint64_t frame_size;
    uint64_t frame_position;
    while (current_position < tag_size) {
        std::string frame_id;
        std::string frame_value;
        for (int i = 0; i < FRAME_SIZE_BYTES; ++i) {
            frame_id += bytes[current_position + i];
            if (bytes[current_position + i] == '\0') {
                return;
            }
        }
        frame_size = (static_cast<uint64_t> (bytes[current_position + 4]) << 21) +
                     (static_cast<uint32_t> (bytes[current_position + 5]) << 14) +
                     (static_cast<uint32_t> (bytes[current_position + 6]) << 7) +
                     (static_cast<uint32_t> (bytes[current_position + 7]));

        frame_position = current_position + FRAME_HEADER_SIZE;
        uint64_t frame_end = current_position + FRAME_HEADER_SIZE + frame_size;
        while (frame_position < frame_end) {
            frame_value += bytes[frame_position];
            frame_position++;
        }
        frames.push_back(MakeUnique(frame_id, frame_value));
        current_position = frame_position;
    }
}

void CParserMP3::ShowFrames() {
    for (int i = 0; i < frames.size(); ++i) {
        frames[i]->ReadInformation();
        std::cout << *frames[i];
        std::cout << '\n';
    }
}

std::unique_ptr<CFrame> CParserMP3::MakeUnique(const std::string& frame_id, const std::string& frame_value) {
    if (frame_id[0] == 'T' && frame_id[1] != 'X') {
        return (std::make_unique<CTextFrame>(frame_value, frame_id));
    } else if (frame_id == "TXXX") {
        return (std::make_unique<CFrameTXXX>(frame_value, frame_id));
    } else if (frame_id[0] == 'W' && frame_id[1] != 'X') {
        return (std::make_unique<CLinkFrame>(frame_value, frame_id));
    } else if (frame_id == "WXXX") {
        return (std::make_unique<CFrameWXXX>(frame_value, frame_id));
    } else if (frame_id == "USLT") {
        return (std::make_unique<CFrameUSLT>(frame_value, frame_id));
    } else if (frame_id == "COMM") {
        return (std::make_unique<CFrameCOMM>(frame_value, frame_id));
    } else if (frame_id == "PCNT") {
        return (std::make_unique<CFramePCNT>(frame_value, frame_id));
    } else if (frame_id == "POPM") {
        return (std::make_unique<CFramePOPM>(frame_value, frame_id));
    } else if (frame_id == "RBUF") {
        return (std::make_unique<CFrameRBUF>(frame_value, frame_id));
    } else if (frame_id == "LINK") {
        return (std::make_unique<CFrameLINK>(frame_value, frame_id));
    } else if (frame_id == "USER") {
        return (std::make_unique<CFrameUSER>(frame_value, frame_id));
    } else if (frame_id == "OWNE") {
        return (std::make_unique<CFrameOWNE>(frame_value, frame_id));
    } else if (frame_id == "COMR") {
        return (std::make_unique<CFrameCOMR>(frame_value, frame_id));
    } else if (frame_id == "ENCR") {
        return (std::make_unique<CFrameENCR>(frame_value, frame_id));
    } else if (frame_id == "GRID") {
        return (std::make_unique<CFrameGRID>(frame_value, frame_id));
    } else if (frame_id == "SIGN") {
        return (std::make_unique<CFrameSIGN>(frame_value, frame_id));
    } else if (frame_id == "SEEK") {
        return (std::make_unique<CFrameSEEK>(frame_value, frame_id));
    } else if (frame_id == "PRIV") {
        return (std::make_unique<CFramePRIV>(frame_value, frame_id));
    }
}
