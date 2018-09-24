// Classifies a document into either positive sentiment or negative sentiment
//
// Parameters:
//      set Vocabulary
//      map prior probability
//      map conditional probability
//      string document - filename of the document
//
//  Returns:
//      int class {0,1}
void test(std::map<int, double> prior, std::map<std::string, double> cond, std::string document);


void test(std::map<int, double> prior, std::map<std::string, double> cond, std::string document)
{
    std::string line;
    std::ifstream testfile(document);
    std::ofstream result("result.txt");

    if(testfile.is_open() && result.is_open())
    {
        while(!testfile.eof())
        {
            std::getline(testfile, line);
            std::stringstream ss(line);

            //std::cout<<line<<"\n";

            // Create a vector to hold words of a line temporarily
            std::vector<std::string> words;
            copy(std::istream_iterator<std::string>(ss),
                 std::istream_iterator<std::string>(),
                 back_inserter(words));

            int classes [2] = {0, 1};
            std::map <int, double> score;

            for (auto& c : classes)
            {
                double score_c = prior[c];

                for (auto& t : words)
                {   

                    // Punctuation and numbers to remove from words before inserting to set
                    char punctuations [] = {'.', ',', '!', '?', ';', ':', '/', '(', ')', '0',
                                            '1', '2', '3', '4', '5', '6', '7', '8','9'};

                    std::string key = t;
                    // Remove punctuations from tokens
                    for (char punctuation : punctuations)
                    {
                        t.erase(std::remove(t.begin(), t.end(), punctuation), t.end());
                    }

                    if (c==0)
                    {
                        key.push_back('0');
                    } else{
                        key.push_back('1');
                    }

                    score_c = score_c + cond[key];
                    std::cout<< key << "\t" << cond[key]<<"\n";
                }
                score[c] = score_c;
                //std::cout << c << "\t" << score[c] << std::endl;
            }

            //std::cout << std::endl;

            // Get the class with higher probability
            int val = 1;
            if (score[0] > score[1])
            {
                val = 0;
            }
            result << val<< std::endl;
        }
    }
    else
    {
        testfile.close();
        result.close();
    }
}