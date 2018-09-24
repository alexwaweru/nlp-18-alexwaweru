#include "main.hpp"

// Reads a text file and counts the number of lines present in the file.
//
// Parameters:
//      string filename : The file name of the text file from which to count the lines.
// 
// Returns:
//      An integer representing the number of lines present in the text file.
int countDocs(std::string filename);


int countDocs(std::string filename)
{
    int count = 0;
    std::string line;
    std::ifstream file(filename);

    if (file.is_open())
    {
        while(!file.eof())
        {
            while(std::getline(file, line))
            {
                count++;
            }
        }
        file.close();
    }else {
        std::cout << "Unable to open file\n";
    }

    return count;
}