//
// Created by pmqtt on 20.11.19.
//

#ifndef PMQ_UTF8_HPP
#define PMQ_UTF8_HPP

#include <string>
namespace pmq::utf8{
    const std::size_t MAX_LENGTH=65536;

    namespace {
        bool is_null(const char chr){
            return chr == 0;
        }
        bool is_plain_ascii(const char chr){
            return chr <= 0x7f;
        }
    }

    bool validate_utf8(const std::string & buffer){

        const auto * buffer_c_str = (const unsigned char *)buffer.c_str();
        std::size_t len = buffer.length();
        if(len < 0 || len > MAX_LENGTH){
            return false;
        }

        for(std::size_t i = 0; i < len; i++){
            std::pair<int,unsigned char> utf8_code;
            if( is_null(buffer_c_str[i]) ){
                return false;
            }else if( is_plain_ascii(buffer_c_str[i]) ){
                utf8_code = std::make_tuple(1,buffer_c_str[i]);
            }else if((buffer_c_str[i] & static_cast<unsigned char>(0xE0)) == 0xC0){
                if(buffer_c_str[i] == 0xC0 || buffer_c_str[i] == 0xC1){
                    return false;
                }
                utf8_code = std::make_tuple(2,buffer_c_str[i] & static_cast<unsigned char>(0x1F));

            }else if((buffer_c_str[i] & static_cast<unsigned char>(0xF0)) == 0xE0){
                utf8_code = std::make_tuple(3,buffer_c_str[i] & static_cast<unsigned char>(0x0F));
            }else if((buffer_c_str[i] & static_cast<unsigned char>(0xF8)) == 0xF0){
                if(buffer_c_str[i] > 0xF4){
                    return false;
                }
                utf8_code = std::make_tuple(4,buffer_c_str[i] & static_cast<unsigned char>(0x07));
            }else{
                return false;
            }
            if(i == len - utf8_code.first +1){
                return false;
            }
            for(std::size_t j=0; j < utf8_code.first - 1; j++){
                if((buffer_c_str[++i] & static_cast<unsigned char>(0xC0)) != 0x80){
                    /* Not a continuation byte */
                    return false;
                }
                utf8_code.second = (utf8_code.second<<6) | (buffer_c_str[i] & static_cast<unsigned char>(0x3F));
            }

            /* Check for UTF-16 high/low surrogates */
            if(utf8_code.second >= 0xD800 && utf8_code.second <= 0xDFFF){
                return false;
            }

            if(utf8_code.first == 3 && utf8_code.second < 0x0800){
                return false;
            }else if(utf8_code.first == 4 && (utf8_code.second < 0x10000 || utf8_code.second > 0x10FFFF)){
                return false;
            }

            // Check for non characters
            if(utf8_code.second >= 0xFDD0 && utf8_code.second <= 0xFDEF){
                return false;
            }
            if((utf8_code.second & 0xFFFF) == 0xFFFE || (utf8_code.second & 0xFFFF) == 0xFFFF){
                return false;
            }
            // Check for control characters
            if(utf8_code.second <= 0x001F || (utf8_code.second >= 0x007F && utf8_code.second <= 0x009F)){
                return false;
            }
        }
        return true;
    }
}


#endif //PMQ_UTF8_HPP
