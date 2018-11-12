import logging
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.cross_validation import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.preprocessing import Normalizer

def logistic_reg(version, testfile, trainfile):
    """
    Args:
        version (str): The version of the classifier to use
        testfile (str): The txt file containing the sentiment data 
        trainfile (str): The txt file containing the test set of sentiment data
    Raises:
        IOError: Unable to read file
    """

    try:
        data, data_labels = train_input_conversion(trainfile)
        vectorizer = CountVectorizer(analyzer = 'word',lowercase = False,)
        features = vectorizer.fit_transform(data)
        features_nd = features.toarray() # for easy usage
        X_train, X_test, y_train, y_test  = train_test_split(features_nd, data_labels,train_size=0.80, random_state=1234)

        if (version == "u"):
            file1 = open("results-lr-u.txt", "w")
            # Create and train the logistic regressor
            log_model = LogisticRegression()
            log_model = log_model.fit(X=X_train, y=y_train)

            # Extract the test data
            test_data = test_input_conversion(testfile)
            test_features = vectorizer.transform(test_data)
            test_features_nd = test_features.toarray() # for easy usage

            # Predict the test data and write in file
            y_pred = log_model.predict(test_features_nd)
            for i in y_pred:
                file1.write(str(i))
                file1.write('\n')
            file1.close()
            print(y_pred)

        elif (version == "n"):
            file2 = open("results-lr-n.txt", "w")
            # Create and train the logistic regressor
            log_model = LogisticRegression()
            log_model = log_model.fit(X=X_train, y=y_train)

            # Extract the test data
            test_data = test_input_conversion(testfile)
            test_features = vectorizer.transform(test_data)
            test_features_nd = test_features.toarray() # for easy usage
            
            # Normalize data
            scaler = Normalizer().fit(test_features_nd)
            normalizedX = scaler.transform(test_features_nd)

            # Predict the test data and write in file
            y_pred = log_model.predict(normalizedX)
            for i in y_pred:
                file2.write(str(i))
                file2.write('\n')
            file2.close()
            print(y_pred)

        else:
            print("Version not supported!!")
            return
    
    except IOError:
        logging.exception('') 
    


def test_input_conversion(testfile):
    """
    Args:
        testfile (str): The txt file containing the sentiment data 
    Returns:
        data (list): A list of documents extracted from the testfile
    Raises:
        IOError: Unable to read file
    """
    
    try:
        # Initialize the input file as well as the input_list
        inputfile = open(testfile,'r')
        data = []

        # Read each line in the input file and append it to the list
        for line in inputfile.readlines():
            data.append(line)
        inputfile.close()
        return data

    except IOError:
        logging.exception('') 


def train_input_conversion(trainfile):
    """
    Args:
        testfile (str): The txt file containing the sentiment data 
    Returns:
        data (list): A list of documents extracted from the testfile
        data_labels (list): A list of corresponding documents' classes
    Raises:
        IOError: Unable to read file
    """
    
    try:
        # Initialize the input file as well as the input_list
        inputfile = open(trainfile,'r')
        data = []
        data_labels = []

        # Read each line in the input file and append it to the list
        for line in inputfile.readlines():
            data.append(line)
            s = line.split('\t')
            data_labels.append(int(s[-1][0]))
        inputfile.close()
        return data, data_labels

    except IOError:
        logging.exception('') 
