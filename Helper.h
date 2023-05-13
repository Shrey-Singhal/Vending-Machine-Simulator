//
// Created by Artemis on 13/05/2023.
//

#ifndef PPD_HELPER_H
#define PPD_HELPER_H

#include <string>
#include <algorithm>


// trim from end
static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

#endif //PPD_HELPER_H
