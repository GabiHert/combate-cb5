#include <iostream>
#include <string.h>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <iomanip>
using namespace std;

int CheckSumBuilder(string data)
{
    unsigned char dataLastIndex = data.length() - 1;
    int sum = 0;
    for (int i = 0; i <= dataLastIndex; i++)
    {
        sum += int(data[i]);
    };

    int CS = 256 - (sum % 256);

    return CS;
};

void printResponseToHexa(string test, int cs)
{
    std::ostringstream result;
    result << std::setw(2) << std::setfill('0') << std::hex << std::uppercase;
    std::copy(test.begin(), test.end(), std::ostream_iterator<unsigned int>(result, " "));

    std::cout << test << ":" << result.str() << cs << " " << 0x0d << " " << 0x0A << std::endl;
};

int main()
{
    std::cout << "Message generator has Started" << endl;

    std::cout << "Type alarm status [0 (off) or 1 (on) ] : ";
    string alarm;
    std::cin >> alarm;

    std::cout << "Type dose status [ N (no) or 0...9 (number of doses)]: ";
    string dose;
    std::cin >> dose;

    std::cout << "Type clear wheel bolts counter status [ N (no) or C (clear)]: ";
    string clearWheelBoltsCounter;
    std::cin >> clearWheelBoltsCounter;

    string inf = "INF";
    string extra = "xxxxxxx";

    string response = inf + alarm + dose + clearWheelBoltsCounter + extra;

    int cs = CheckSumBuilder(response);
    //    std::string csstring = std::to_string(cs);

    printResponseToHexa(response, cs);

    std::cout << response << endl;
    return 0;
}
