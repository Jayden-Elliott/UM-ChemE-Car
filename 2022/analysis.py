import os
import pandas as pd

data_dir = "/Users/jayden/Documents/Code/ChemE_Car/data"
for file in os.listdir(data_dir):
    if not file.startswith("10_24") and not file.startswith("10_27") and not file.startswith("10_31"):
        continue
    df = pd.read_csv(os.path.join(data_dir, file))

    last_10 = [0 for i in range(10)]
    rolling_index = 0
    start_time = 0
    highest = 0
    lowest = 1023
    peaked = False
    bottomed = False

    print(file)
    for i in range(len(df)):
        val = df.iloc[i, 1]
        last_10[rolling_index] = val
        rolling_index = (rolling_index + 1) % 10
        avg = sum(last_10) / len(last_10)
        
        if not peaked:
            if avg > highest:
                highest = avg
            elif avg < highest - 150 and highest > 800:
                peaked = True
                print(f"Peak time: {start_time}, Peak avg: {val}, Highest value: {highest}")

        elif not bottomed:
            if avg < lowest:
                lowest = avg
            elif avg > lowest + 10:
                bottomed = True
                highest = 0
                start_time = df.iloc[i, 0]
                print("Bottom time: " + str(df.iloc[i, 0]), ", Bottom value: " + str(val))
        
        else:
            if df.iloc[i, 0] - start_time < 500:
                continue
            if avg > highest and avg > lowest + 10:
                highest = avg
            elif avg < highest - 5:
                print("End time: " + str(df.iloc[i, 0]), ", End value: " + str(val))
                print("Time to Peak: ", df.iloc[i, 0] - start_time, end="\n\n")
                break