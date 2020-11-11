#include "../header/helper.h"

//! function that transforms attributes bytes into text
void get_attribute(const int* attr, std::string* res){
    std::vector<std::string> names = {"WRITE_PROTECT ", "HIDDEN ", "SYSTEM ",
                                      "VOLUME_NAME ", "SUBDIR ", "ARCHIVE ", "RESERVED "};
    for (auto i = 1; i < names.size() + 1; i++){
        if ((*attr & static_cast<int>((1*pow(10, i)))) != 0){
            *res += names[i];
        }
    }
}

//! function that transforms date&time bytes into text
void dt_converter(const unsigned short* time, const unsigned short* date, std::string* res){
    char buf[100];
    sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d", 1980 + (*date >> 9), (*date >> 5) & 0xF,
            *date & 0x1F, (*time >> 11), (*time >> 5) & 0x3F, *time & 0x1F);
    *res = buf;
}

//! function that transforms name&extension bytes into text
void get_file_name(unsigned char* name, unsigned char* ext, std::string* f_name){
    for(auto i = 0; i < filename_size; i++){
        unsigned char a = *name;
        if (a == 32 || a == 0){
            break;
        }
        f_name->push_back(a);
        name++;
    }
    if (*ext != 32 && *ext != 0){
        f_name->push_back('.');
    }
    for(auto i = 0; i < ext_size; i++){
        unsigned char a = *ext;
        if (a == 32 || a == 0){
            break;
        }
        f_name->push_back(a);
        ext++;
    }
}

//https://stackoverflow.com/questions/874134/find-out-if-string-ends-with-another-string-in-c
//! function that checks if a string ends with another string
bool ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}
