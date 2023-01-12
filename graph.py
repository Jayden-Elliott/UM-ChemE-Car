import os
from turtle import title
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

dfs = {}
times = {}
plt.figure(figsize=(6, 3))
#increase space below graph
plt.subplots_adjust(bottom=0.2)
for c in [0.1, 0.2, 0.3, 0.4]:
    dfs[c] = pd.read_csv(f"/Users/jayden/Documents/Code/ChemE_Car/data/10_31_2022_{c}gNaOH_0.03gKMnO4.csv", names=["t", "v"])
    dfs[c] = dfs[c].iloc[dfs[c]["v"].idxmax():]
    dfs[c]["t"] = dfs[c]["t"]/1000 - dfs[c]["t"].iloc[0]/1000
    plt.plot(dfs[c]["t"], dfs[c]["v"], label=f"{c}g")
    max_time = dfs[c]["v"].iloc[50:].idxmax()
    min_time = dfs[c]["v"].iloc[:500].idxmin()
    print(f"{c}g: {dfs[c]['t'][max_time]} - {dfs[c]['t'][min_time]}")
    times[c] = dfs[c]["t"][max_time] - dfs[c]["t"][min_time]    
    plt.plot([dfs[c]["t"][max_time], dfs[c]["t"][max_time]], [0, dfs[c]["v"][max_time]], color=plt.gca().lines[-1].get_color(), linestyle="--")
plt.legend(title="NaOH (g)")
plt.xlabel("Time (s)")
plt.ylabel("Transmitted Light Intensity")
plt.title("Light Transmission over Time for Differing NaOH Concentrations")
plt.xlim(0, 30)
plt.ylim(300, 1023)
plt.savefig("transmission.png")
plt.clf()

rooted_times = {}
for c, t in times.items():
    rooted_times[c] = t**(-0.5)
    print(f"{c}g: {rooted_times[c]}")
plt.plot(rooted_times.keys(), rooted_times.values(), "o")
m, b = np.polyfit(list(rooted_times.keys()), list(rooted_times.values()), 1)
plt.plot(np.arange(0.1, 0.5, 0.01), m*np.arange(0.1, 0.5, 0.01) + b)
plt.xlabel("NaOH Concentration (g)")
plt.ylabel(r"Inverse Square Root of Time to Peak (s$^{-0.5}$)")
plt.title("Inverse Square Root of Time to Peak by NaOH Concentration")
plt.savefig("trend.png")