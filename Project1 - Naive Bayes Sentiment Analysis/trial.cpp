#include <iostream>
#include "test.cpp"

int main(int argc, char** argv)
{
    std::cout << argv[1];
    std::cout << "Started training";
    test::test("priors.txt", "conds.txt", argv[1]);
    return 0;
}