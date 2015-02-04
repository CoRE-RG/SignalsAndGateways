//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include <Utility.h>

namespace UTLTY{
    static bool isnotalnum(char c){
        return !isalnum(c);
    }

    static int findFirstAlphaNum(const char *str){
        int pos = 0;
        for(pos = 0; !isalnum(*str);pos++){
            str++;
        }
        return pos;
    }

    void Utility::stripNonAlphaNum(std::string & str)
    {
        str.erase(remove_if(str.begin(),str.end(), isnotalnum), str.end());
    }

    std::string Utility::stripNonAlphaNum(const char *str)
    {
        std::string stringRepresentation = std::string(str, 0, 55);
        stripNonAlphaNum(stringRepresentation);
        return stringRepresentation;
    }

    std::string Utility::stripNonAlphaNum(const char *str, unsigned int maxLength){
        std::string stringRepresentation = std::string(str, findFirstAlphaNum(str), maxLength);
        stripNonAlphaNum(stringRepresentation);
        return stringRepresentation;
    }
}

