#include "utils/utils.h"

vector<string> splitStringBy(const string str, char separator)
{
    std::vector<std::string> result;
    std::istringstream stream(str);
    std::string token;

    while (std::getline(stream, token, separator))
    {
        result.push_back(token);
    }

    return result;
}
