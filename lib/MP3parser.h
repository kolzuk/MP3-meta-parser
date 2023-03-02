#pragma once

#include "Frames.h"

#include <memory>
#include <map>
#include <string>
#include <vector>
#include <filesystem>

class CParserMP3 {
private:
    std::vector<unsigned char> bytes;
    bool unsynchronisation;
    bool extended_header;
    bool experimental_indicator;
    bool footer_present;
    uint32_t tag_size;
    std::vector<std::unique_ptr<CFrame>> frames;
public:
    void ReadFile(const std::filesystem::path& path);
    void ReadFlags();
    void ReadSize();
    void ReadFrames();
    void ShowFrames();
    std::unique_ptr<CFrame> MakeUnique(const std::string& frame_id, const std::string& frame_value);
};
