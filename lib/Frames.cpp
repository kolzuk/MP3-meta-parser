#include "Frames.h"
#include "FramesID.h"

CFrame::CFrame(const std::string& frame_value_, const std::string& frame_id_) {
    frame_value = frame_value_;
    frame_id = frame_id_;
    frame_size = frame_value_.size();
}

void CFrame::ReadInformation() {
    std::cout << frame_id << ' ' << frame_value << '\n';
}

void CFrame::Print(std::ostream& stream) {
    stream << "Frame ID: " << frame_id << '\n';
    stream << "Frame Value: " << frame_value << '\n';
}

std::ostream& operator<<(std::ostream& stream, CFrame& frame) {
    frame.Print(stream);
    return stream;
}

CTextFrame::CTextFrame(
        const std::string& _frame_value,
        const std::string& _frame_id)
        : CFrame(_frame_value, _frame_id) {
}

void CTextFrame::ReadInformation() {
    for (uint64_t i = 1; i < frame_size; ++i) {
        information += frame_value[i];
    }
}

void CTextFrame::Print(std::ostream& stream) {
    stream << "Frame ID: " << frame_id << '\n';
    stream << "Frame Information: " << kFrameIdDescription.at(frame_id) << '\n';
    stream << information << '\n';
}

CFrameTXXX::CFrameTXXX(
        const std::string& _frame_value,
        const std::string& _frame_id)
        : CFrame(_frame_value, _frame_id) {
}

void CFrameTXXX::ReadInformation() {
    uint64_t current_position = 1;
    while (frame_value[current_position] != '\0') {
        description += frame_value[current_position];
        current_position++;
    }
    current_position++;
    for (uint64_t i = current_position; i < frame_size; ++i) {
        value += frame_value[i];
    }
}

void CFrameTXXX::Print(std::ostream& stream) {
    stream << "FrameID: " << frame_id << '\n';
    stream << "Frame Description: " << description << '\n';
    stream << "Frame Value: " << value << '\n';
}

CLinkFrame::CLinkFrame(
        const std::string& _frame_value,
        const std::string& _frame_id)
        : CFrame(_frame_value, _frame_id) {
}

void CLinkFrame::ReadInformation() {
    for (uint64_t i = 0; i < frame_size; ++i) {
        URL += frame_value[i];
    }
}

void CLinkFrame::Print(std::ostream& stream) {
    stream << "FrameID: " << frame_id << '\n';
    stream << "Frame Value: " << kFrameIdDescription.at(frame_id) << '\n';
    stream << URL << '\n';
}

CFrameWXXX::CFrameWXXX(
        const std::string& _frame_value,
        const std::string& _frame_id)
        : CFrame(_frame_value, _frame_id) {
}

void CFrameWXXX::ReadInformation() {
    uint64_t current_position = 1;
    while (frame_value[current_position] != '\0') {
        description += frame_value[current_position];
        current_position++;
    }
    current_position++;
    for (uint64_t i = current_position; i < frame_size; ++i) {
        value += frame_value[i];
    }
}

void CFrameWXXX::Print(std::ostream& stream) {
    stream << "FrameID: " << frame_id << '\n';
    stream << "Frame Description: " << description << '\n';
    stream << "Frame Value: " << value << '\n';
}

CFrameUSLT::CFrameUSLT(
        const std::string& _frame_value,
        const std::string& _frame_id) :
        CFrame(_frame_value, _frame_id) {
}

void CFrameUSLT::ReadInformation() {
    uint64_t current_index = 1;
    while (current_index < 4) {
        language += frame_value[current_index];
        current_index++;
    }
    while (frame_value[current_index] != '\0') {
        content_descriptor += frame_value[current_index];
        current_index++;
    }
    current_index++;
    while (current_index < frame_size) {
        lyrics += frame_value[current_index];
        current_index++;
    }
}

void CFrameUSLT::Print(std::ostream& stream) {
    stream << "Frame ID: " << frame_id << '\n';
    stream << "Frame: " << language << '\n';
    stream << "Content Descriptor: " << content_descriptor << '\n';
}

CFrameCOMM::CFrameCOMM(
        const std::string& _frame_value,
        const std::string& _frame_id)
        : CFrame(_frame_value, _frame_id) {
}

void CFrameCOMM::ReadInformation() {
    uint64_t current_index = 1;
    while (current_index < 4) {
        language += frame_value[current_index];
        current_index++;
    }
    while (frame_value[current_index] != '\0') {
        short_content_descriptor += frame_value[current_index];
        current_index++;
    }
    current_index++;
    while (current_index < frame_size) {
        text_of_comm += frame_value[current_index];
        current_index++;
    }
}

void CFrameCOMM::Print(std::ostream& stream) {
    stream << "Frame ID: "<< frame_id << '\n';
    stream << "Language: " << language << '\n';
    stream << "Short Content Descriptor: " << short_content_descriptor << '\n';
    stream << "Text Of Comm: " << text_of_comm << '\n';
}

CFramePCNT::CFramePCNT(
        const std::string& _frame_value,
        const std::string& _frame_id)
        : CFrame(_frame_value, _frame_id) {
}

void CFramePCNT::ReadInformation() {
    uint64_t sum = 0;
    for (int64_t i = frame_size - 1; i >= 0; --i) {
        sum += (static_cast<uint64_t> (frame_value[i]) >> (frame_size - i - 1));
    }
    counter = sum;
}

void CFramePCNT::Print(std::ostream& stream) {
    stream << "Frame ID: " << frame_id << '\n';
    stream << "Counter: " << counter << '\n';
}

CFramePOPM::CFramePOPM(const std::string& _frame_value,
                       const std::string& _frame_id)
                       : CFrame(_frame_value, _frame_id) {
}

void CFramePOPM::ReadInformation() {
    uint64_t current_index = 0;
    while (frame_value[current_index] != '\0') {
        email_to_user += frame_value[current_index];
        current_index++;
    }
    current_index++;
    rating = static_cast<uint8_t> (frame_value[current_index]);
    uint64_t sum = 0;
    for (uint32_t i = frame_size - 1; i > current_index; --i) {
        sum += (static_cast<uint32_t> (frame_value[i]) >> (frame_size - i - 1));
    }
    counter = sum;
}

void CFramePOPM::Print(std::ostream& stream) {
    stream << "Frame ID: " << frame_id << '\n';
    stream << "Email To User: " << email_to_user << '\n';
    stream << "Counter: " << counter << '\n';
    stream << "Rating: " << rating << '\n';
}

CFrameRBUF::CFrameRBUF(
        const std::string& _frame_value,
        const std::string& _frame_id)
        : CFrame(_frame_value, _frame_id) {
}

void CFrameRBUF::ReadInformation() {
   buffer_size =  (static_cast<uint32_t> (frame_value[0]) >> 16) +
                  (static_cast<uint32_t> (frame_value[1]) >> 8) +
                  (static_cast<uint32_t> (frame_value[2]));
   embedded_into_flag = ((uint64_t) frame_value[3] >> 7);
   offset_to_next_flag =  (static_cast<uint32_t> (frame_value[4]) >> 24) +
                          (static_cast<uint32_t> (frame_value[5]) >> 16) +
                          (static_cast<uint32_t> (frame_value[6]) >> 8) +
                          (static_cast<uint32_t> (frame_value[7]));
}
void CFrameRBUF::Print(std::ostream& stream) {
    stream << "Frame ID: " << frame_id << '\n';
    stream << "Buffer Size: " << buffer_size << '\n';
    stream << "Embedded Into Flag: " << embedded_into_flag << '\n';
    stream << "Offset To Next Flag: " << offset_to_next_flag << '\n';
}

CFrameLINK::CFrameLINK(
        const std::string& _frame_value,
        const std::string& _frame_id) :
        CFrame(_frame_value, _frame_id) {
}

void CFrameLINK::ReadInformation() {
    for (int i = 0; i < 4; ++i) {
        frame_identifier += frame_value[i];
    }
    uint64_t current_index = 4;
    while (frame_value[current_index] != '\0') {
        URL += frame_value[current_index];
        current_index++;
    }
    current_index++;
    while (current_index < frame_size) {
        ID_and_additional_data += frame_value[current_index];
        current_index++;
    }
}

void CFrameLINK::Print(std::ostream& stream) {
    stream << "Frame ID: " << frame_id << '\n';
    stream << "Frame Identifier: " << frame_identifier << '\n';
    stream << "URL: \n" << URL << '\n';
    stream << "ID And Additional Data" << ID_and_additional_data << '\n';
}

CFrameUSER::CFrameUSER(
        const std::string& _frame_value,
        const std::string& _frame_id)
        : CFrame(_frame_value, _frame_id) {
}

void CFrameUSER::ReadInformation() {
    for (int i = 1; i < 4; ++i) {
        language += frame_value[i];
    }
    uint64_t current_index = 4;
    while (current_index < frame_size) {
        actual_information += frame_value[current_index];
    }
}
void CFrameUSER::Print(std::ostream& stream) {
    stream << "Frame ID: " << frame_id << '\n';
    stream << "Language: " << language << '\n';
    stream << "Actual Information: " << actual_information << '\n';
}

CFrameOWNE::CFrameOWNE(const std::string& _frame_value,
                       const std::string& _frame_id)
                       : CFrame(_frame_value, _frame_id) {
}

void CFrameOWNE::ReadInformation() {
    for (int i = 1; i < 4; ++i) {
        price_paid += frame_value[i];
    }
    for (int i = 5; i < 9; ++i) {
        year_of_paid += frame_value[i];
    }
    for (int i = 9; i < 11; ++i) {
        month_of_paid += frame_value[i];
    }
    for (int i = 11; i < 13; ++i) {
        day_of_paid += frame_value[i];
    }
    for (int i = 13; i < frame_size; ++i) {
        seller += frame_value[i];
    }
}
void CFrameOWNE::Print(std::ostream& stream) {
    stream << "Frame ID: " << frame_id << '\n';
    stream << "Price Paid: " << price_paid << '\n';
    stream << "Year Of Paid: " << year_of_paid << '\n';
    stream << "Month Of Paid: " << month_of_paid << '\n';
    stream << "Day Of Paid: " << day_of_paid << '\n';
    stream << "Seller: " << seller << '\n';
}

CFrameCOMR::CFrameCOMR(
        const std::string& _frame_value,
        const std::string &_frame_id)
        : CFrame(_frame_value, _frame_id) {
}

void CFrameCOMR::ReadInformation() {
    for (int i = 0; i < 3; ++i) {
        price_string += frame_value[i];
    }
    for (int i = 4; i < 8; ++i) {
        year_of_valid += frame_value[i];
    }
    for (int i = 8; i < 10; ++i) {
        month_of_valid += frame_value[i];
    }
    for (int i = 10; i < 12; ++i) {
        day_of_valid += frame_value[i];
    }
    uint64_t current_index = 12;
    while (frame_value[current_index] != '\0') {
        contact_URL += frame_value[current_index];
        current_index++;
    }
    current_index++;
    received_as = frame_value[current_index];
    while (frame_value[current_index] != '\0') {
        name_of_seller += frame_value[current_index];
        current_index++;
    }
    current_index++;
    while (frame_value[current_index] != '\0') {
        description += frame_value[current_index];
        current_index++;
    }
    current_index++;
    while (frame_value[current_index] != '\0') {
        picture_MIME_type += frame_value[current_index];
        current_index++;
    }
    current_index++;
    while (current_index < frame_size) {
        for (int i = 7; i >= 0; --i) {
            seller_logo += std::to_string((frame_value[current_index] >> i) & 1);
        }
        current_index++;
    }
}
void CFrameCOMR::Print(std::ostream& stream) {
    stream << "Frame ID: " << frame_id << '\n';
    stream << "Price String: " << price_string << '\n';
    stream << "Year Of Valid: " << year_of_valid << '\n';
    stream << "Month Of Valid: " << month_of_valid << '\n';
    stream << "Day Of Valid: " << day_of_valid << '\n';
    stream << "Contact URL: " << contact_URL << '\n';
    stream << "Received As: " << received_as << '\n';
    stream << "Name of seller: " << name_of_seller << '\n';
    stream << "Description: " << description << '\n';
    stream << "Picture MIME Type: " << picture_MIME_type << '\n';
    stream << "Seller Logo: " << seller_logo << '\n';
}

CFrameENCR::CFrameENCR(
        const std::string& _frame_value,
        const std::string& _frame_id)
        : CFrame(_frame_value, _frame_id) {
}

void CFrameENCR::ReadInformation() {
    uint64_t current_index = 0;
    while (frame_value[current_index] != '\0') {
        owner_identifier += frame_value[current_index];
        current_index++;
    }
    current_index++;
    method_symbol += frame_value[current_index];
    current_index++;
    while (current_index < frame_size) {
        for (int i = 7; i >= 0; --i) {
            encryption_data += std::to_string((frame_value[current_index] >> i) & 1);
        }
        current_index++;
    }
}
void CFrameENCR::Print(std::ostream& stream) {
    stream << "Frame ID: " << frame_id << '\n';
    stream << "Owner Identifier: " << owner_identifier << '\n';
    stream << "Method Symbol: " << method_symbol << '\n';
    stream << "Encryption Data: " << encryption_data << '\n';
}

CFrameGRID::CFrameGRID(
        const std::string& _frame_value,
        const std::string& _frame_id)
        : CFrame(_frame_value, _frame_id) {
}

void CFrameGRID::ReadInformation() {
    uint64_t current_index = 0;
    while (frame_value[current_index] != '\0') {
        owner_identifier += frame_value[current_index];
        current_index++;
    }
    current_index++;
    group_symbol = frame_value[current_index];
    while (current_index < frame_size) {
        for (int i = 7; i >= 0; --i) {
            group_dependent_data = std::to_string((frame_value[current_index] >> i) & 1);
        }
        current_index++;
    }
}
void CFrameGRID::Print(std::ostream& stream) {
    stream << "Frame ID: " << frame_id << '\n';
    stream << "Owner Identifier: " << owner_identifier << '\n';
    stream << "Group Symbol: " << group_symbol << '\n';
    stream << "Group Dependent Data: " << group_dependent_data << '\n';
}

CFrameSIGN::CFrameSIGN(
        const std::string& _frame_value,
        const std::string& _frame_id)
        : CFrame(_frame_value, _frame_id) {
}

void CFrameSIGN::ReadInformation() {
    group_symbol = frame_value[0];
    uint64_t current_index = 1;
    while (current_index < frame_size) {
        for (int i = 7; i >= 0; --i) {
            signature += std::to_string((frame_value[current_index] >> i) & 1);
        }
        current_index++;
    }
}
void CFrameSIGN::Print(std::ostream& stream) {
    stream << "Frame ID: " << frame_id << '\n';
    stream << "Group Symbol: " << group_symbol << '\n';
    stream << "Signature: " << signature << '\n';
}

CFrameSEEK::CFrameSEEK(
        const std::string& _frame_value,
        const std::string& _frame_id)
        : CFrame(_frame_value, _frame_id) {
}

void CFrameSEEK::ReadInformation() {
    minimum_offset_to_next_tag = (static_cast<uint64_t> (frame_value[0]) >> 24) +
                                 (static_cast<uint64_t> (frame_value[1]) >> 16) +
                                 (static_cast<uint64_t> (frame_value[2]) >> 8) +
                                 (static_cast<uint64_t> (frame_value[3]));
}
void CFrameSEEK::Print(std::ostream& stream) {
    stream << "Frame ID: " << frame_id << '\n';
    stream << "Minimum Offset To Next Tag" << minimum_offset_to_next_tag << '\n';
}

CFramePRIV::CFramePRIV(
        const std::string& _frame_value,
        const std::string& _frame_id)
        : CFrame(_frame_value, _frame_id) {
}

void CFramePRIV::ReadInformation() {
    uint64_t current_index = 0;
    while (frame_value[current_index] != '\0') {
        owner_identifier += frame_value[current_index];
    }
    current_index++;
    while (current_index < frame_size) {
        private_data += frame_value[current_index];
    }
}

void CFramePRIV::Print(std::ostream& stream) {
    stream << "Frame ID: " << frame_id << '\n';
    stream << "Owner Identifier" << owner_identifier << '\n';
    stream << "Private Data" << private_data << '\n';
}
