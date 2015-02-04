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

#ifndef UTILITY_H_
#define UTILITY_H_

#include <string>
#include <algorithm>
#include <functional>

namespace SignalsAndGateways {

/**
 * @brief Utility class to offer functions over module borders
 *
 * @author Sebastian Mueller
 */
class Utility {
    public:
        /**
         * @brief Strips all non alphanumeric characters from the string
         *
         * The operation is executed directly on the given string reference.
         *
         * @param str string to strip
         */
        static void stripNonAlphaNum(std::string & str);
        /**
         * @brief Strips all non alphanumeric characters from the char*.
         *
         * @param str const char* to strip
         * @return string representation with all alphanumeric characters of the char*.
         */
        static std::string stripNonAlphaNum(const char *str);
        /**
         * @brief Strips all non alphanumeric characters from the char*. MaxLength pretend the maximum length of the returning string.
         *
         * @param str const char* to strip
         * @param maxLength max length of str
         * @return string representation with alphanumeric characters of the char* with respect to the given maximum length.
         */
        static std::string stripNonAlphaNum(const char *str, unsigned int maxLength);
    };

}

#endif /* UTILITY_H_ */
