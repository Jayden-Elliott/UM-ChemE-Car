import os
import sys
import pandas as pd

def main():
    df = pd.read_csv("/Users/jayden/Documents/Code/ChemE_Car/data/10_03_2022_1gNaOH.csv")
    with open("/Users/jayden/Documents/Code/ChemE_Car/fixed.csv", "w") as f:
        i = 0
        for index, row in df.iterrows():
            f.write(f"{i},{row['reading']}\n")
            i += 1
            for j in range(9):
                #interpolate between points
                if index == len(df)-1:
                    f.write(f"{i},{row['reading']}\n")
                    break
                f.write(f"{i},{df.iloc[index]['reading'] + (df.iloc[index+1]['reading'] - df.iloc[index]['reading'])/10 * (j+1)}\n")
                i += 1


if __name__ == "__main__":
    main()