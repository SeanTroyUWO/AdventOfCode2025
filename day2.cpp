#include <cassert>
#include <cmath>

#include <iostream>
#include <vector>

#include "input/day2.hpp"

// const char input[] = "11-22,95-115,998-1012,1188511880-1188511890,222220-222224,1698522-1698528,446443-446449,38593856-38593862,565653-565659,824824821-824824827,2121212118-212121212";

struct range
{
    range(uint64_t bot, uint64_t top)
        : bot(bot), top(top)
    {
        //
    }
    uint64_t bot;
    uint64_t top;
};

bool digitsMatch(uint64_t input, unsigned int digits)
{
    uint64_t modVal = std::pow(10, digits/2);
    return static_cast<uint64_t>(input/modVal) == input % modVal;
}

uint64_t howManyDigitsTwiceLoop(uint64_t bot, uint64_t top)
{
    uint64_t count = 0;
    for(uint64_t i = bot; i <= top; i++)
    {
        unsigned int digits = std::ceil(std::log10(static_cast<double>(i)+0.0001));
        std::string digitsString = std::to_string(i);
        assert(digitsString.length() == digits);
        if(digits % 2)
        {
            continue;
        }
        if(digitsMatch(i, digits))
        {
            std::cout << "next loop is: " << i << std::endl;
            count += i;
        }
    }

    return count;
}

uint64_t howManyDigitsTwice(uint64_t bot, uint64_t top)
{
    std::cout << "for bot: " << bot << " top: " << top << std::endl;
    uint64_t count = 0;
    double log10 = std::log10(static_cast<double>(bot)+0.0000001);
    uint64_t currentDivisor = std::pow(10, static_cast<int>(std::ceil(log10 / 2)))+1;
    uint64_t thisMin = std::pow(10, static_cast<int>(std::ceil(log10 / 2)-1)*2 + 1) + std::pow(10, static_cast<int>(std::floor(log10 / 2)));
    uint64_t next = std::max(bot + currentDivisor - (((bot-1) % currentDivisor)+1), thisMin);
    uint64_t nextGate = thisMin * 10;

    assert(bot <= next);
    assert(nextGate >= next);
    while(next <= top)
    {
        double log10_assert = std::log10(static_cast<double>(next));
        assert(static_cast<int>(std::ceil(log10_assert)) % 2 == 0);
        assert(digitsMatch(next, static_cast<int>(std::ceil(log10_assert))));
        count += next;
        std::cout << "next is: " << next << std::endl;
        next = next + currentDivisor;
        if(next >= nextGate)
        {
            std::cout << "hit gate" << std::endl;
            log10 = std::log10(next);
            currentDivisor = std::pow(10, static_cast<int>(std::ceil(log10 / 2)))+1;
            thisMin = std::pow(10, static_cast<int>(std::ceil(log10 / 2)-1)*2 + 1) + std::pow(10, static_cast<int>(std::floor(log10 / 2)));
            next = thisMin;
            nextGate = thisMin * 10;
        }
    }
    return count;
}

int main()
{
    std::vector<range> inputVec{};
    std::string_view inputStrView(input);

    size_t start = 0;
    size_t end = 0;
    while((end =  inputStrView.find(',', start)) != std::string_view::npos)
    {
        size_t dash = inputStrView.find('-', start);

        std::string botStr = std::string(inputStrView.substr(start, dash-start));
        std::string topStr = std::string(inputStrView.substr(dash+1, end-dash-1));
        uint64_t bot = std::stoll(botStr);
        uint64_t top = std::stoll(topStr);
        inputVec.emplace_back(bot, top);
        start = end+1;
    }

    size_t dash = inputStrView.find('-', start);
    inputVec.emplace_back(std::stol(std::string(inputStrView.substr(start, dash-start))),
        std::stol(std::string(inputStrView.substr(dash+1))));

    int commaCount = std::count(inputStrView.begin(), inputStrView.end(), ',');
    int dashCount = std::count(inputStrView.begin(), inputStrView.end(), '-');
    assert(commaCount+1 == inputVec.size());
    assert(dashCount == inputVec.size());

    uint64_t countLoop = 0;
    uint64_t count = 0;
    std::string checkStr{};
    for(const auto& input : inputVec)
    {
        count += howManyDigitsTwice(input.bot, input.top);
        countLoop += howManyDigitsTwiceLoop(input.bot, input.top);
        assert(count == countLoop);

        checkStr+=std::to_string(input.bot);
        checkStr+='-';
        checkStr+=std::to_string(input.top);
        checkStr+=',';
    }
    checkStr.pop_back();
    assert(checkStr == inputStrView);
    std::cout << "final count 1 is: " << count << std::endl;
    std::cout << "final count 2 is: " << countLoop << std::endl;
}