

def naive_b(version, testfile):
    """
    Args:
        version (str): The version of the classifier to use
        testfile (str): The txt file containing the sentiment data 
    Raises:
        IOError: Unable to read file
    """

    try:
        print("Classifier: nb")
        if (version == "u"):
            print("Version: %s" % version)
                
            # Code for unnormalized this thing will go here

        elif (version == "n"):
            print("Version: %s" % version)

            # Code for normalized this thing will go here

        else:
            print("Version not supported!!")
            return 

    except IOError:
        logging.exception('')


def input_conversion(testfile):
    """
    Args:
        testfile (str): The txt file containing the sentiment data 
    Returns:
        input_list (list): A list of documents extracted from the testfile
    Raises:
        IOError: Unable to read file
    """
    
    try:
        # Initialize the input file as well as the input_list
        inputfile = open(training_data_filename, 'r')
        input_list = []

        # Read each line in the input file and append it to the list
        for line in fo.readlines():
            input_list.append(line)
        inputfile.close()
        return input_list

    except IOError:
        logging.exception('') 


