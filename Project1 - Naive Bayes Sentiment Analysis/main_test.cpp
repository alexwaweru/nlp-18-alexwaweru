#include "main.hpp"
#include "functions.hpp"
#include "test.cpp"

int main(int argc, char** argv)
{
    std::cout<<"Started!!";
    test("priors.txt", "conds.txt", argv[1]);
}
