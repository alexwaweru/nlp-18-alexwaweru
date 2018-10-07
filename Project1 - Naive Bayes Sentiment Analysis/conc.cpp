#include "main.hpp"

void concatenate_files(std::string file1, std::string file2, std::string file3);


int main(int argc, char **argv)
{
    concatenate_files(argv[1], argv[2], argv[3]);
    return 0;
}

void concatenate_files(std::string file1, std::string file2, std::string file3)
{
    std::ifstream input_file1(file1);
    std::ifstream input_file2(file2);
    std::ifstream input_file3(file3);
    std::ofstream output("training_set.txt");

    std::string line;

    if (input_file1.is_open() && input_file2.is_open() && input_file3.is_open())
    {
        while(!input_file1.eof())
        {
            while(std::getline(input_file1, line))
            {
                output << line << "\n";
            }
        }
        input_file1.close();

        while(!input_file2.eof())
        {
            while(std::getline(input_file2, line))
            {
                output << line << "\n";
            }
        }
        input_file2.close();

        while(!input_file3.eof())
        {
            while(std::getline(input_file3, line))
            {
                output << line << "\n";
            }
        }
        input_file3.close();

        
    }else {
        std::cout << "Unable to open file\n";
    }
}