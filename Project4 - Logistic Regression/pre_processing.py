import csv
import logging
from collections import Counter


def create_unique_set_of_words(training_data_filename):
    """
    Args:
        training_data_filename (str): The txt file containing the sentiment data 
    Returns:
        one_hot_encoding_titles (set): A set of unique words extracted from the training data 
    Raises:
        IOError: Unable to read file
    """
    
    try:
        # Initialize the input and output files as well as the Bag_of_words
        training_y_file = open('training_y.csv', 'w')
        training_y_file.write('class\n')
        inputfile = open(training_data_filename, 'r')
        bag_of_words = []

        # Read each line in the input file and split it by the space delimiter
        punctuations = " '\"+-*@#$%&^.,!?;:/()<>|[]0123456789"
        for row in (inputfile.readlines()):
            row = row.strip().lower()
            row = row.split(' ')

            # Store the class of the each line in the training_y file
            temp1 = row[-1].split('\t')
            temp = temp1[-1] + '\n'
            training_y_file.write(temp)
            del row[-1]
            for word in row:
                for mark in punctuations:
                    word = word.replace(mark,'')
                bag_of_words.append(word)

        # Convert the list of words into a set of words so as to get the unique words
        one_hot_encoding_titles = list(set(bag_of_words))

        inputfile.close()

        return one_hot_encoding_titles
    except IOError:
        logging.exception('') 


def one_hot_encode_features(training_data_filename):
    """
    Args:
        inputfilename (str): The name of the txt file containing the sentiment data 
    Returns:
        outputfile.name (str): The filename of the new csv file containing one_hot_encoded features
    Raises:
        IOError: Unable to read file
    """

    try:
        # Initialize the input and output files and the one hot encoding titles
        one_hot_encoded_titles = create_unique_set_of_words(training_data_filename)
        inputfile = open(training_data_filename, 'r')
        outputfile =open('one_hot_encoded_features.csv', 'w')

        # Write column headers i.e. the unique words at the top of the output file
        column_headers = ''
        last_index = len(one_hot_encoded_titles) - 1
        for  i in range(0, last_index):
            header = one_hot_encoded_titles[i]
            if i != last_index:
                column_headers = column_headers + header + ', '
            else: 
                column_headers = column_headers + header
        column_headers = column_headers + '\n'
        outputfile.write(column_headers)

        # Read each line in the training data file and split it by the space delimiter
        punctuations = " \"+*@#$%&^.,!?;:/()<>|[]0123456789"
        for row in (inputfile.readlines()):
            row = row.strip().lower()
            row = row.split(' ')
            words = Counter(row)
            for word in words:
                for mark in punctuations:
                    word = word.replace(mark,'')

            # For each document, map out and write its encoding on the output file
            line = ''
            for  i in range(0, last_index):
                word = one_hot_encoded_titles[i]
                if i != last_index:
                    if word in words:
                        line = line + str(words[word]) + ', '
                    else:
                        line = line + '0' + ', '
                else: 
                    if word in words:
                        line = line + words[word]
                    else:
                        line = line + '0'
            line = line + '\n'
            outputfile.write(line)

        inputfile.close()
        outputfile.close()

        return outputfile.name
    except IOError:
        logging.exception('')


one_hot_encode_features("training_set.txt")
