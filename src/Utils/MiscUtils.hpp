#pragma once
#include <array>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <string>
#include <string_view>
#include <enet/enet.h>
#include <Packet/GameUpdatePacket.hpp>
#include <Packet/VariantList.hpp>
#include <Packet/PacketFactory.hpp>

namespace Utils {
    inline std::vector<std::string> Split(std::string data, std::string delimiter) {
        std::size_t startPos = 0, endPos, delimiterLength = delimiter.length();
        std::string token{};
        std::vector<std::string> ret{};

        while ((endPos = data.find(delimiter, startPos)) != std::string::npos) {
            token = data.substr(startPos, endPos - startPos);
            startPos = endPos + delimiterLength;
            ret.push_back(token);
        }

        ret.push_back (data.substr(startPos));
        return ret;
    }
    inline bool IsValidUsername(std::string username) {
        if (username.empty()) 
            return false;

        for (auto ch : username) {
            if (!(ch >= '0' && ch <= '9') && !((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')))
                return false;
        }
        return true;
    }
    inline bool ToLowerCase(std::string& data, const bool& underscore = false) {
        if (data.empty()) 
            return false;

        for (auto& ch : data) {
            if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
                ch = std::tolower(ch);
            else if (!(ch >= '0' && ch <= '9') && !(underscore && ch == '_'))
                return false;
        }
        return true;
    }
    inline std::string GetLowerCase(const std::string& data) {
        std::string result = data;
        std::transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }
    inline uint32_t GetProtonHash(const void* data, std::size_t data_len) {
        if (!data) return 0;
        uint32_t hash = 0x55555555;

        for (std::size_t i = 0; i < data_len; ++i)
            hash = (hash >> 27) + (hash << 5) + static_cast<const uint8_t*>(data)[i];

        return hash;
    }
}

namespace Hash {
    constexpr std::size_t Fnv1A(const std::string_view& data) {
        std::size_t prime = 1099511628211ULL;
        std::size_t hash{ 14695981039346656037ULL };
        for (auto& c : data)
            hash ^= c, hash *= prime;
        return hash;
    }
}

constexpr std::size_t operator ""_fnv(const char* str, std::size_t len) {
    return Hash::Fnv1A(std::string_view{ str, len });
}