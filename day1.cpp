#include <iostream>
#include <ostream>
#include <array>

enum class Dir
{
    R,
    L
};

struct Spin
{
    Dir dir;
    unsigned int num;
};

#include "input/day1.hpp"

// const std::array<Spin, 10> spinArray = {
//     Spin{Dir::L, 68},
//     Spin{Dir::L, 30},
//     Spin{Dir::R, 48},
//     Spin{Dir::L, 5},
//     Spin{Dir::R, 60},
//     Spin{Dir::L, 55},
//     Spin{Dir::L, 1},
//     Spin{Dir::L, 99},
//     Spin{Dir::R, 14},
//     Spin{Dir::L, 82}
// };

int mathMod(int a, int b)
{
    int res = a % b;
    if(res < 0)
    {
        res += b;
    }
    return res;
}

int main()
{
    int zeroCount = 0;
    int currentPos = 50;

    for(const Spin &spin: spinArray)
    {
        if(spin.dir == Dir::R)
        {
            currentPos += spin.num;
            // if(currentPos >= 100)
            //     zeroCount+= (int)(currentPos/100);

            currentPos = mathMod(currentPos, 100);
        } else
        {
            currentPos -= spin.num;
            // if(currentPos <= 0)
            //     zeroCount += (int)(-currentPos/100) + 1;

            currentPos = mathMod(currentPos, 100);
        }
        if(currentPos == 0)
            zeroCount += 1;

        std::cout << currentPos << " " << zeroCount << std::endl;
    }

    std::cout << zeroCount << std::endl;
}
