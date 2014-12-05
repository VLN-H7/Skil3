#include "utils.h"

std::stringstream Utils::readline(){
    std::string s;
    std::getline(std::cin, s);

    std::stringstream ss(s);
    return ss;
}

// Credit to Evan Teran http://stackoverflow.com/questions/236129/split-a-string-in-c
std::vector<std::string>& Utils::split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> Utils::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}
// Credit to same dude http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string& Utils::ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

// trim from end
std::string& Utils::rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}

// trim from both ends
std::string& Utils::trim(std::string &s) {
        return ltrim(rtrim(s));
}

// partial credit to: http://www.java2s.com/Code/Cpp/STL-Algorithms-Modifying-sequence-operations/removeemptystring.htm
void Utils::vtrim(std::vector<std::string>& strings)
{
    std::for_each(strings.begin(), strings.end(), Utils::trim);
    auto it = std::remove_if(strings.begin(), strings.end(), [](std::string& a){ return a.empty(); });
    // erase the removed elements
    strings.erase(it, strings.end());
}


