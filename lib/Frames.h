#pragma once

#include <cstdint>
#include <map>
#include <string>
#include <ostream>
#include <iostream>

class CFrame {
protected:
    std::string frame_value;
    std::string frame_id;
    uint64_t frame_size;
public:
    CFrame(const std::string& frame_value_, const std::string& frame_id_);
    virtual void ReadInformation();
    virtual void Print(std::ostream& stream);
};

std::ostream& operator<<(std::ostream& stream, CFrame& frame);

class CTextFrame : public CFrame {
private:
    std::string information;
public:
    CTextFrame(const std::string& _frame_value, const std::string& _frame_id);
    void ReadInformation() override;
    void Print(std::ostream& stream) override;
};

class CFrameTXXX : public CFrame {
private:
    std::string description;
    std::string value;
public:
    CFrameTXXX(const std::string& _frame_value, const std::string& _frame_id);
    void ReadInformation() override;
    void Print(std::ostream& stream) override;
};

class CLinkFrame : public CFrame {
private:
    std::string URL;
public:
    CLinkFrame(const std::string& _frame_value, const std::string& _frame_id);
    void ReadInformation() override;
    void Print(std::ostream& stream) override;
};

class CFrameWXXX : public CFrame {
private:
    std::string description;
    std::string value;
public:
    CFrameWXXX(const std::string& _frame_value, const std::string& _frame_id);
    void ReadInformation() override;
    void Print(std::ostream& stream) override;
};

class CFrameUSLT : public CFrame {
private:
    std::string language;
    std::string content_descriptor;
    std::string lyrics;
public:
    CFrameUSLT(const std::string& _frame_value, const std::string& _frame_id);
    void ReadInformation() override;
    void Print(std::ostream& stream) override;
};

class CFrameCOMM : public CFrame {
private:
    std::string language;
    std::string short_content_descriptor;
    std::string text_of_comm;
public:
    CFrameCOMM(const std::string& _frame_value, const std::string& _frame_id);
    void ReadInformation() override;
    void Print(std::ostream& stream) override;
};

class CFramePCNT : public CFrame {
private:
    uint64_t counter;
public:
    CFramePCNT(const std::string& _frame_value, const std::string& _frame_id);
    void ReadInformation() override;
    void Print(std::ostream& stream) override;
};

class CFramePOPM : public CFrame {
private:
    std::string email_to_user;
    uint8_t rating;
    uint64_t counter;
public:
    CFramePOPM(const std::string& _frame_value, const std::string& _frame_id);
    void ReadInformation() override;
    void Print(std::ostream& stream) override;
};

class CFrameRBUF : public CFrame {
private:
    uint32_t buffer_size;
    bool embedded_into_flag;
    uint64_t offset_to_next_flag;
public:
    CFrameRBUF(const std::string& _frame_value, const std::string& _frame_id);
    void ReadInformation() override;
    void Print(std::ostream& stream) override;
};

class CFrameLINK : public CFrame {
private:
    std::string frame_identifier;
    std::string URL;
    std::string ID_and_additional_data;
public:
    CFrameLINK(const std::string& _frame_value, const std::string& _frame_id);
    void ReadInformation() override;
    void Print(std::ostream& stream) override;
};

class CFrameUSER : public CFrame {
private:
    std::string language;
    std::string actual_information;
public:
    CFrameUSER(const std::string& _frame_value, const std::string& _frame_id);
    void ReadInformation() override;
    void Print(std::ostream& stream) override;
};

class CFrameOWNE : public CFrame {
private:
    std::string price_paid;
    std::string year_of_paid;
    std::string month_of_paid;
    std::string day_of_paid;
    std::string seller;
public:
    CFrameOWNE(const std::string& _frame_value, const std::string& _frame_id);
    void ReadInformation() override;
    void Print(std::ostream& stream) override;
};

class CFrameCOMR : public CFrame {
private:
    std::string price_string;
    std::string year_of_valid;
    std::string month_of_valid;
    std::string day_of_valid;
    std::string contact_URL;
    std::string received_as;
    std::string name_of_seller;
    std::string description;
    std::string picture_MIME_type;
    std::string seller_logo;
public:
    CFrameCOMR(const std::string& _frame_value, const std::string& _frame_id);
    void ReadInformation() override;
    void Print(std::ostream& stream) override;
};

class CFrameENCR : public CFrame {
private:
    std::string owner_identifier;
    std::string method_symbol;
    std::string encryption_data;
public:
    CFrameENCR(const std::string& _frame_value, const std::string& _frame_id);
    void ReadInformation() override;
    void Print(std::ostream& stream) override;
};

class CFrameGRID : public CFrame {
private:
    std::string owner_identifier;
    std::string group_symbol;
    std::string group_dependent_data;
public:
    CFrameGRID(const std::string& _frame_value, const std::string& _frame_id);
    void ReadInformation() override;
    void Print(std::ostream& stream) override;
};

class CFrameSIGN : public CFrame {
private:
    char group_symbol;
    std::string signature;
public:
    CFrameSIGN(const std::string& _frame_value, const std::string& _frame_id);
    void ReadInformation() override;
    void Print(std::ostream& stream) override;
};

class CFrameSEEK : public CFrame {
private:
    uint64_t minimum_offset_to_next_tag;
public:
    CFrameSEEK(const std::string& _frame_value, const std::string& _frame_id);
    void ReadInformation() override;
    void Print(std::ostream& stream) override;
};

class CFramePRIV : public CFrame {
private:
    std::string owner_identifier;
    std::string private_data;
public:
    CFramePRIV(const std::string& _frame_value, const std::string& _frame_id);
    void ReadInformation() override;
    void Print(std::ostream& stream) override;
};