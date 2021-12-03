#include "utils.h"

ArrayList<std::string> split(std::string str, std::string delimiter)
{
    auto list = ArrayList<std::string>();

    size_t last = 0;
    size_t next;
    while ((next = str.find(delimiter, last)) != std::string::npos)
    {
        if (last != next) list.insert(str.substr(last, next-last));
        last = next + 1;
    }

    list.insert(str.substr(last));
    return list;
}

void trim_in_place(std::string& str)
{
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
        return !isspace(ch);
    }));

    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
        return !isspace(ch);
    }).base(), str.end());
}