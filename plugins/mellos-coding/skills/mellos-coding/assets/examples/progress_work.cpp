#include "progress_work.hpp"

#include <iostream>

using namespace mellos::example;

int main()
{
    const Begin Request{100};
    Running Work(Request);
    bool HalfReported = false;

    while (!CompletedEnd::GetResult(Work))
    {
        Work.Advance();
        if (!HalfReported && HalfEnd::GetResult(Work))
        {
            std::cout << "Half completed!\n";
            HalfReported = true;
        }
    }

    std::cout << "Completed!\n";
}
