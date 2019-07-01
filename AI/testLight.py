from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier
from sklearn.metrics import accuracy_score
from scikitplot.metrics import plot_confusion_matrix
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

dataset = pd.read_json("./data.json")
#520

x = np.array([])
y = np.array([])

for value in enumerate(dataset["LIGHT_VALUE"]):
    x = np.append(x, int(value[1]))

for value in enumerate(dataset["NEED_LIGHT"]):
    y = np.append(y, int(value[1])) 

x = x.reshape(-1, 1)
y = y.reshape(-1, 1)

x_train, x_test, y_train, y_test = train_test_split(x,y)

model = DecisionTreeClassifier()
model.fit(x_train, y_train)

y_pred = model.predict(x_test)

print("Accuratezza test")
print(str(accuracy_score(y_test, y_pred)*100)+"%")

plot_confusion_matrix(y_test, y_pred)
plt.show()

y_pred = model.predict([[400]])
print(bool(y_pred[0]))