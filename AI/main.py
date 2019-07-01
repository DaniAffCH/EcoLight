from sklearn.tree import DecisionTreeClassifier
import numpy as np
import pandas as pd
import serial
import time

if __name__ == "__main__":
    serialPort = '/dev/ttyACM0'
    port = 9600
    dataset = pd.read_json("./data.json")

    x = np.array([])
    y = np.array([])

    for value in enumerate(dataset["LIGHT_VALUE"]):
        x = np.append(x, int(value[1]))

    for value in enumerate(dataset["NEED_LIGHT"]):
        y = np.append(y, int(value[1])) 

    x = x.reshape(-1, 1)
    y = y.reshape(-1, 1)

    model = DecisionTreeClassifier()
    model.fit(x, y)

    arduino = serial.Serial(serialPort, port)

    print("Running AI for ecoLight!")

    while True:

        msgStr = str(arduino.readline())
        protocol = msgStr[2:5]
        msgReduct = msgStr[5:]
        msg = np.array(msgReduct[:-5])

        if(protocol == "ard"):
            msg = msg.reshape(-1, 1)
            y_pred = model.predict(msg)
            out = "t" if y_pred == 1.0 else "f"
            arduino.write(out.encode('latin_1'))