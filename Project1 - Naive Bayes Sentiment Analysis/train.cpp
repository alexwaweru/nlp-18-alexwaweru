// Trains a Naive Bayes Sentiment Classifier
//
// Returns:
//      set vocabulary
//      map prior_probabilities for each class
//      map conditional_probabilities for each text+class e.g the1
std::tuple < std::map<int,double>, std::map <std::string, double> > train(std::string filename);


std::tuple < std::map<int,double>, std::map <std::string, double> > train(std::string filename)
{
    // Initialize prior probability, condional probability, vocabulary, number of docs and classes
    std::map <int, double> prior;
    std::map <std::string, double> condprob;
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
        prior[c] = (double)Nc/N;

        double den;
        for (auto &text : vocabulary)
        {
            int Tct = countTokensOfTerm(class_file_name, text);

            den = den + Tct + 1;


            // Add class to the text 
            std::string key = text;
            if (c==0)
            {
                key.push_back('0');
            } else{
                key.push_back('1');
            }

            condprob[key] = (Tct+1);
        }

        for (auto& p : condprob)
        {
            p.second = p.second/den;
        }
    }

    return std::make_tuple(prior, condprob);
}