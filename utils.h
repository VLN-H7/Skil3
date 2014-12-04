#ifndef UTILS_H
#define UTILS_H
#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>


namespace Utils {
    // Casually stolen from http://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance#C.2B.2B
    // (because i am too lazy to write from scratch)
    template<class T>
    unsigned int levenshtein_distance(const T &s1, const T & s2) {
        const size_t len1 = s1.size(), len2 = s2.size();
        std::vector<unsigned int> col(len2+1), prevCol(len2+1);

        for (unsigned int i = 0; i < prevCol.size(); i++)
            prevCol[i] = i;
        for (unsigned int i = 0; i < len1; i++) {
            col[0] = i+1;
            for (unsigned int j = 0; j < len2; j++)
                col[j+1] = std::min( std::min(prevCol[1 + j] + 1, col[j] + 1),
                                    prevCol[j] + (s1[i]==s2[j] ? 0 : 1) );
            col.swap(prevCol);
        }
        return prevCol[len2];
    }

    std::stringstream readline();

    // Credit to Evan Teran http://stackoverflow.com/questions/236129/split-a-string-in-c
    std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
    std::vector<std::string> split(const std::string &s, char delim);

    // Credit to same dude http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
    std::string& ltrim(std::string &s);
    std::string& rtrim(std::string &s);
    std::string& trim(std::string &s);

    void vtrim(std::vector<std::string>& strings);

}

#endif // UTILS_H
