#include <iostream>
#include <ostream>
#include <string>
#include <vector>

// const char input[] =
// "987654321111111,"
// "811111111111119,"
// "234234234234278,"
// "818181911112111,";

#include "input/day3.hpp"

int main()
{
    std::vector<std::string> inputVec;
    std::string_view inputStringView(input);

    size_t start = 0;
    size_t end = 0;
    while((end = inputStringView.find(',', start)) != std::string::npos)
    {
        inputVec.emplace_back(inputStringView.substr(start, end - start));
        start = end + 1;
    }

    uint64_t count = 0;
    for(const auto bank : inputVec)
    {
        char max1 = bank[0];
        char max2 = bank[1];

        for(int i = 1; i < bank.size()-1; i++)
        {
            if(bank[i] > max1)
            {
                max1 = bank[i];
                max2 = bank[i+1];
            }
            else if(bank[i] > max2)
            {
                max2 = bank[i];
            }
        }
        max2 = std::max(max2, bank.back());

        int bankMax = ((max1-48)*10 + (max2-48));
        std::cout << bankMax << std::endl;
        count += bankMax;
    }

    std::cout << "final count is: " << count << std::endl;
}
