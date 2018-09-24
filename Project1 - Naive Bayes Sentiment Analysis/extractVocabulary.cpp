#include "main.hpp"

// Extracts all unique words present a file.
//
// Parameters:
//      file -> The vector from which to get unique words.
//      
// Returns:
//      A vector of unique words.
//
std::set<std::string> extractVocabulary(std::string filename);


std::set<std::string> extractVocabulary(std::string filename)
{
    std::set<std::string> vocabulary;
    std::string line;
    std::ifstream file(filename);

    if(file.is_open())
    {
        // Read each line before end of file
        while(!file.eof())
        {
            std::getline(file, line);

            // Convert all words to lowercase
            std::transform(line.begin(), line.end(), line.begin(), ::tolower);
            std::stringstream ss(line);

            // Create a vector to hold tokens of a line temporarily
            std::vector<std::string> tokens;
            copy(std::istream_iterator<std::string>(ss),
                 std::istream_iterator<std::string>(),
                 back_inserter(tokens));
            
            // Punctuation and numbers to remove from words before inserting to set
            char punctuations [] = {'.', ',', '!', '?', ';', ':', '/', '(', ')', '0',
                                     '1', '2', '3', '4', '5', '6', '7', '8','9'};

            // Insert the tokens to the main vector
            for (std::string token : tokens)
            {
                // Remove punctuations from tokens
                for (char punctuation : punctuations)
                {
                    token.erase(std::remove(token.begin(), token.end(), punctuation), token.end());
                }
                vocabulary.insert(token);
            }
        }
        file.close();
    } else {
        std::cout << "Unable to open file\n";
     }

    return vocabulary;
}


