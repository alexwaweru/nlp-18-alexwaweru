#include "main.hpp"
#include "functions.hpp"
#include "train.cpp"
#include "test.cpp"

int main(int argc, char** argv)
{
    //std::map<int, double> prior;
    //std::map<std::string, double> cond;
    //train(argv[1]);

    test("priors.txt", "conds.txt", argv[1]);
}
