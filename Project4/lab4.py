import sys
from logistic_regression import LogisticRegression as lg
from naive_bayes import NaiveBayes as nb

def main(classifier_type, version, testfile):
    if (classifier_type == "nb"):
        nb(version, testfile, "training_set.txt")
    elif(classifier_type == "lr"):
        lg(version, testfile,"training_set.txt")
    else:
        print("classifier type not supported!!!")


if __name__ == "__main__":
    inputs = len(sys.argv)
    if ( inputs == 4 ):
        # Get the terminal parameters
        classifier_type = sys.argv[1]
        version = sys.argv[2]
        testfile = sys.argv[3]

        # Call the main functionnlp-18
        main(classifier_type, version, testfile)
    else:
        inputs = inputs - 1
        print("3 inputs required %d given" % inputs)