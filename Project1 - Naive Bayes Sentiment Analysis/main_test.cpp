#include "main.hpp"
#include "functions.hpp"
#include "test.cpp"

int main(int argc, char** argv)
{
   std::cout << "Started training";
    test("priors.txt", "conds.txt", argv[1]);
    return 1;
}
