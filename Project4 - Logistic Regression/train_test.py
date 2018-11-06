from sklearn.linear_model import LogisticRegression
import pandas as pd

# Split the X dataframe into 2: 70% for training and 30% for testing
df_x = pd.read_csv('one_hot_encoded_features.csv')
train_x = df_x[:int(df_x.shape[0]*0.7)]
test_x = df_x[int(df_x.shape[0]*0.7):]

# Split the Y dataframe into 2: 70% for training and 30% for testing
df_y = pd.read_csv('training_y.csv')
train_y = df_y[:int(df_y.shape[0]*0.7)]
test_y = df_y[int(df_y.shape[0]*0.7):]

# Train the model
clf = LogisticRegression(random_state=0, solver='lbfgs', multi_class='ovr').fit(train_x, train_y)

# Test the model
train_accuracy = clf.score(train_x, train_y) 
test_accuracy = clf.score(test_x, test_y)

# Print out the model's accuracy level
print("The model's accuracy based on the training data is: ", train_accuracy)
print("the model's accuracy based on data the model has not seen before is: ", test_accuracy)
