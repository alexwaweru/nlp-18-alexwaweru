from sklearn.linear_model import LogisticRegression
import pandas as pd


df_x = pd.read_csv('one_hot_encoded_features.csv')
train_x = df_x[:int(df_x.shape[0]*0.7)]
test_x = df_x[int(df_x.shape[0]*0.7):]

df_y = pd.read_csv('training_y.csv')
train_y = df_y[:int(df_y.shape[0]*0.7)]
test_y = df_y[int(df_y.shape[0]*0.7):]



