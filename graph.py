import pandas as pd
import matplotlib.pyplot as plt
import click

@click.command()
#required file argument
@click.argument('file', type=click.Path(exists=True))
def main(file):
    #set column names to time and value
    data = pd.read_csv(file, names=["time", "value"])
    data.time = data.time / 1000
    plt.scatter(data.time, data.value, s=2)
    plt.show()

if __name__ == "__main__":
    main()