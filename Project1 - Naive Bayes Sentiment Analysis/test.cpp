
void test(std::string priors_filename, std::string cond_probs_filename, std::string test_file)
{
    // Create a list of priors
    std::ifstream priors_file(priors_filename);
    std::map<double, double> priors;   // Map of class and prior probabilities
    std::string priors_line;
    if (priors_file.is_open())
    {
        std::getline(priors_file, priors_line);
        std::string::size_type sz;    
        
        // Create a key(class) and value(prior prob) and insert into map
        double key = std::stod(priors_line,&sz);
        double value = std::stod (priors_line.substr(sz));
        priors.insert(std::pair<double, double>(key, value));
    }

    // Create a map of conditional probabilities
    std::ifstream conds_file(cond_probs_filename);
    std::map<std::string, double> conds;  // Map of conditional probabilities
    std::string conds_line;
    if (conds_file.is_open())
    {
        std::getline(conds_file, conds_line);
        std::stringstream ss(conds_line);

        // Create a vector to hold tokens of a line temporarily
        std::vector<std::string> tokens;
        copy(std::istream_iterator<std::string>(ss),
                std::istream_iterator<std::string>(),
                back_inserter(tokens));
        
        // Create key(word + class) and value (conditional probability) and add into map
        std::string key = tokens[0] + tokens[1];
        double value = std::stod(tokens[3]);
        conds.insert(std::pair <std::string, double> (key, value));
    }


    // Calculate the score for each class for each line and store max score in the results file
    std::string line;
    std::ifstream testfile(test_file);
    std::ofstream result("result.txt");
    if(testfile.is_open() && result.is_open())
    {
        while(!testfile.eof())
        {
            std::getline(testfile, line);
            std::stringstream ss(line);
            std::transform(line.begin(), line.end(), line.begin(), ::tolower);


            // Create a vector to hold words of a line temporarily
            std::vector<std::string> words;
            copy(std::istream_iterator<std::string>(ss),
                 std::istream_iterator<std::string>(),
                 back_inserter(words));
            
            // Punctuation and numbers to remove from words before inserting to set
            char punctuations [] = {' ','\'','"', '+', '-', '*', '@', '#', '$', '%', '&', '.', ',', '!', '?', ';', ':', '/', '(', ')', '0',
                                     '1', '2', '3', '4', '5', '6', '7', '8','9'};

            // Insert the cleaned up words to the documents vector
            std::vector<std::string> documents;
            for (std::string word : words)
            {
                // Remove punctuations from tokens
                for (char punctuation : punctuations)
                {
                    word.erase(std::remove(word.begin(), word.end(), punctuation), word.end());
                }
                documents.push_back(word);
            }

            double classes [2] = {0.0, 1.0};
            std::map <double, double> score;

            for (auto c : classes)
            {
                double score_c = 0.0;
                score_c = log(priors[c]);

                for (auto t : documents)
                {   
                    if (c==0.0)
                    {
                        t.push_back('0');
                    } else{
                        t.push_back('1');
                    }
                    score_c = score_c + conds[t];
                    std::cout << t << "\t"<<score_c<<"\t"<< conds[t]<<"\n";
                }
                score[c] = score_c;
            }

            //std::cout << std::endl;

            // Get the class with higher probability
            if (score[0.0] > score[1.0]){
                result <<0 << std::endl;
            }
            else if (score[1.0] > score[0.0]){
                result << 1 << std::endl;
            }
            else{
                result << "tie" <<std::endl;
            }
        }
    }
    else
    {
        testfile.close();
        result.close();
    }
}

int main(int argc, char** argv)
{
    test("priors.txt", "conds.txt", argv[1]);
}