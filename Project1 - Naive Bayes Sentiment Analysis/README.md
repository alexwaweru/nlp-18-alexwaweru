#This is an implementation of Naive Bayes Model for Sentiment Analysis

##Prediction
To predict or test using my pretrained model :

1. Go to your bash shell
2. Navigate to where the cloned project is
3. Run the commands below:
```console
./test piors.txt conds.txt [test file]
```

Note: The output is stored in file result.txt

##Training
To train the model:
1. run the commands below 
```console
./train [training file]
```

The output will be
1. A priors.txt file that stores prior probabilities of the classes
2. A conds.txt file that stores conditional probabilities of the each [word, class] combination


Go to both files and delete the last line which should be empty.
IF YOU DO NOT DO THIS YOU WILL GET A SEGMENTATION FAULT ERROR IF YOU RUN YOUR test