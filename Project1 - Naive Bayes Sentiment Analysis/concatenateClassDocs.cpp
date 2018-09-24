#include "main.hpp"

// Reads a text file and places all the lines that belong to a certain class c in a new document.
//
// Parameters:
//      string fname    : The file name of the text file.
//      int c           : The class whose documents to concatenate i.e. 1 or 0.
//      string fnameOut : The file name of the new text file where to put all documents belonging to c.
// 
// Returns:
//      A file name of the new text file where all documents of c have been concatenated to.
std::string concatenateTextOfAllDocsInAClass(std::string fnameIn, int c, std::string fnameOut);


std::string concatenateTextOfAllDocsInAClass(std::string fnameIn, int c, std::string fnameOut)
{
    std::string line;
    std::ifstream file(fnameIn);
    std::ofstream output(fnameOut);

    if(file.is_open() && output.is_open())
    {
        while(!file.eof())
        {
            std::getline(file, line);
            std::stringstream ss(line);

            // Create a vector to hold tokens of a line temporarily
            std::vector<std::string> tokens;
            copy(std::istream_iterator<std::string>(ss),
                 std::istream_iterator<std::string>(),
                 back_inserter(tokens));

            // Check the last item of the vector
            if(!tokens.empty())
            {
                if(tokens.back()==std::to_string(c))
                {
                    output << line <<"\n";
                }
            }
        }
    }
    else
    {
        file.close();
        output.close();
    }
    return fnameOut;
}