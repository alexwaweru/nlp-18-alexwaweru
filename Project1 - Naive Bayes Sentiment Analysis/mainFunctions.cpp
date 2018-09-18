#include "main.hpp"


// Used to hold all variables returned by the trainNB function. 
// It is also an input for the applyNB function.
struct LearntParameters
{
    std::vector<std::string> Vocabulary;
    float prior[2];
    std::vector< std::vector<float> > conditionalProbability;
};

// Reads a text file and extracts all words present in the file and places them in an array.
//
// Parameters:
//      string fname -> The file name of the text file to extract the vocabulary from.
//      
// Returns:
//      The a vector.
//
// Note:
//      The text files and the program files should be in the same folder.
std::vector<std::string> extractBOW(std::string fname);


// Extracts unique words present an array.
//
// Parameters:
//      vector BOG -> The vector from which to get unique words.
//      
// Returns:
//      A vector of unique words.
//
std::vector<std::string> extractVocabulary(std::vector<std::string>& BOW);


// Reads a text file and counts the number of lines present in the file.
//
// Parameters:
//      string fname : The file name of the text file from which to count the lines.
// 
// Returns:
//      An integer representing the number of lines present in the text file.
int countDocs(std::string fname);


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


// Counts how many times a word appears in the concatenated file of a class.
//
// Parameters:
//      string fname    : The file name of the concatenated text file.
//      string text     : The word who frequency of appearance we are searching.
// 
// Returns:
//      An integer that represents the number of times a word appears in a text file.
int countTokensOfTermInClass(std::string fname, std::string text);


// Trains the Naive Bayes Sentiment Analysis model
// 
// Parameters:
//      int* classes : An array of classes
//      string fname : The text file contaidning the training data.
// 
//Returns:
//      Learnt Parameters: A struct containing:
//                  std::string Vocabulary[]            : An array containing each word in the training data
//                  float prior[]                       : An array containing the prior probabilities for the classes
//                  float conditionalProbability[][]    : An 2*2 array containing the conditional probability of each [word][class]
LearntParameters trainNB(std::vector<int>& classes, std::string fname);


// It creates an array of words from the test file.
//
// Parameters:
//      string fname : A text file on which to perform the sentiment analysis
//
// Returns:
//      An vector of all extracted Tokens from the document
std::vector<std::vector<std::string>> extractTokensFromDoc( std::string fname);


// Tests the Naive Bayes Sentiment Analysis Model
//
// Parameters:
//      string* classes   : The classes 
//      Learnt Parameters : A struct containing -> (prior probability, conditional probability, Vocabulary)
//      string document   : The string on which to perform the sentiment analysis
//
// Returns: 
//      The class in which the string is classified into.
float applyNB(std::vector<std::string> classes, LearntParameters P, std::string fname);


std::vector<std::string> extractBOW(std::string fname)
{   
    std::cout << "Creation of Bag of Word started... \n";
    std::vector<std::string> BOW;
    std::string line;
    std::ifstream file(fname);

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
            
            // Add the tokens to the main vector
            for (std::string token : tokens)
            {
                BOW.push_back(token);
            }
        }
        file.close();
    } else {
        std::cout << "Unable to open file\n";
    }

    return BOW;
}


std::vector<std::string> extractVocabulary(std::vector<std::string>& BOW)
{   
    std::vector<std::string> vocabulary;

    for (auto &word : BOW)
    {
        if (!std::binary_search(vocabulary.begin(), vocabulary.end(), word))
        {
            vocabulary.push_back(word);
        }
    }

    return vocabulary;
}


int countDocs(std::string fname)
{
    int count;
    std::ifstream file(fname);

    if (file.is_open())
    {
        while(!file.eof())
        {
            count++;
        }
        file.close();
    }else {
        std::cout << "Unable to open file\n";
    }

    return count;
}


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
            if(tokens.back()==std::to_string(c))
            {
                output << line <<"\n";
            }
        }
        file.close();
        output.close();
    }
    return fnameOut;
}


int countTokensOfTermInClass(std::string fname, std::string text)
{   
    int count;
    std::string line;
    std::ifstream file(fname);

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

            // iterate through the vector to search for words
            for( auto &token : tokens)
            {
                if(token==text)
                {
                    count++;
                }
            }
        }
        file.close();
    }
    return count;
}


LearntParameters trainNB(std::vector<int>& classes, std::string fname)
{
    std::cout << "Start training... \n";

    // Get the BOG and vocabulary
    std::cout << "Creating Bag of words... \n";
    std::vector<std::string> BOW = extractBOW("training_data.txt");
    std::cout << "Created a Bag of Words.";
    std::vector<std::string> vocabulary = extractVocabulary(BOW);
    int N = countDocs("training_data.txt");

    //Initialize learnt parameters struct
    LearntParameters params;

    for( int index = 0; index < classes.size(); index++)
    {
        std::string filename;
        if (classes[index]==1)
        {
            filename = "positive_docs.txt";
        }
        else{
            filename = "negative_docs.txt";
        }

        std::cout<<"start concatenating docs for class "<< classes[index] <<"\n";
        std::cout<<filename<<" generated";
        std::string textc = concatenateTextOfAllDocsInAClass("training_data.txt", classes[index], filename);
        std::cout << "concatenated docs in class "<< classes[index]  << "\n";

        int sizec = extractBOW(filename).size();
        int Nc = countDocs(textc);
        params.prior[classes[index]] = Nc/N;
        std::cout << params.prior[classes[index]] << "\n";

        float den = 0;
        for(int index = 0; index < vocabulary.size(); index++)
        {
            int Tct = countTokensOfTermInClass(textc, vocabulary[index]);
            den = den + Tct + 1;
        }

        for(int index = 0; index < vocabulary.size(); index++)
        {
            int Tct = countTokensOfTermInClass(textc, vocabulary[index]);
            params.conditionalProbability[index][classes[index]] = (Tct + 1 )/(den);
        }
    }
    return params;
}


std::vector<std::vector<std::string>> extractTokensFromDoc(std::string fname)
{
    std::string line;
    std::vector<std::vector<std::string>> W;
    std::ifstream file(fname);

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
            
            // Add the tokens vector to the main vector
            W.push_back(tokens);
        }
        file.close();
    } else {
        std::cout << "Unable to open file\n";
    }

    return W;
}


float applyNB(std::vector<int> classes, LearntParameters P, std::string fname)
{
    std::vector<std::vector<std::string>> W = extractTokensFromDoc(fname);
    std::ofstream output("results.txt");

    for (auto &doc : W)
    {
        if (output.is_open())
        {
            if (output.eof())
            {
                double score[2];
                for (auto &c : classes)
                {
                    score[c] = log(P.prior[c]);
                    for ( int index = 0; index < doc.size(); index++)
                    {
                        score[c] = score[c] + P.conditionalProbability[index][c];
                    }
                }
                if (score[0] > score[1])
                {
                    output << 0;
                } else {
                    output << 1;
                }
            }
        }
    }
}


