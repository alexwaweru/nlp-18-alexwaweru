#include "main.hpp"

// Counts how many times a word appears in the concatenated file of a class.
//
// Parameters:
//      string filename    : The file name of the text file.
//      string text     : The word whose frequency we need.
// 
// Returns:
//      An integer that represents the number of times a word appears in a text file.
int countTokensOfTerm(std::string filename, std::string text);


int countTokensOfTerm(std::string filename, std::string text)
{   
    int count = 0;
    std::string line;
    std::ifstream file(filename);

    if(file.is_open())
    {
        while(!file.eof())
        {
            std::getline(file, line);
            std::transform(line.begin(), line.end(), line.begin(), ::tolower);
            std::stringstream ss(line);

            // Create a vector to hold tokens of a line temporarily
            std::vector<std::string> tokens;
            copy(std::istream_iterator<std::string>(ss),
                 std::istream_iterator<std::string>(),
                 back_inserter(tokens));

            // Punctuation and numbers to remove from words before doing comparison
            char punctuations [] = {'.', ',', '!', '?', ';', ':', '/', '(', ')', '0',
                                     '1', '2', '3', '4', '5', '6', '7', '8','9'};

            // Iterate through the vector to search for matching word
            for (std::string token : tokens)
            {
                // Remove punctuations from tokens
                for (char punctuation : punctuations)
                {
                    token.erase(std::remove(token.begin(), token.end(), punctuation), token.end());
                }
                
                if(token == text)
                {
                    count++;
                }
            }
        }
        file.close();
    }
    return count;
}

