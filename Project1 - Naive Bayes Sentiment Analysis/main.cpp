#include "main.hpp"
#include "mainFunctions.cpp"

int main(int argc, char** argv )
{
    std::cout << "Train data file: "<< argv[1]<< "\n";
    std::cout << "Test data file: "<<argv[2]<<"\n\n";

    std::cout << "start...\n";

    std::vector<int> classes = {0,1};
    std::cout <<"\nThe classes are: \n";
    for (auto &c : classes){
        std::cout << c << "\n";
    }
    std::cout<<"\n";
    LearntParameters learntParameters = trainNB(classes, argv[1]);
    std::cout << "Finished training...\n";
    applyNB(classes, learntParameters, argv[2]);
    std::cout << "Everything done...\n";

    return 0;
}

