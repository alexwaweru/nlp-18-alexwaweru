#include "main.hpp"
#include "functions.hpp"

void train(std::string filename);


int main(int argc, char** argv)
{
    train(argv[1]);
    return 0;
}


void train(std::string filename)
{
    // Initialize prior probability, condional probability, vocabulary, number of docs and classes
    std::ofstream prior("priors.txt");
    std::ofstream cond("conds.txt");
    std::set <std::string> vocabulary = extractVocabulary(filename);
    int N = 0;

    N = countDocs(filename);
    int classes [2] = {0, 1};

    // Concatenate positive and negative docs in same files
    std::string positive_docs = concatenateTextOfAllDocsInAClass(filename, 1, "positive_docs.txt");
    std::string negative_docs = concatenateTextOfAllDocsInAClass(filename, 0, "negative_docs.txt");

    for (auto c : classes)
    {
        // Count docs in a class
        std::string class_file_name;

        if (c==1)
        {
            class_file_name = positive_docs;
        }
        else {
            class_file_name = negative_docs;
        }

        // Calculate class priors
        int Nc = 0;
        Nc = countDocs(class_file_name);
        prior << c << "\t" << (double)Nc/N << "\n";

        double total_Tct;
        for (auto text : vocabulary)
        {
            double Tct;
            Tct = countTokensOfTerm(class_file_name, text);

            total_Tct = total_Tct + (Tct + 1);
        }

        for (auto text : vocabulary)
        {
            double prob;
            double Tct;
            Tct = countTokensOfTerm(class_file_name, text);
            prob = (Tct + 1)/ (total_Tct) ;
            cond << text << c <<"\t" << prob << "\n";
        }
    }
}