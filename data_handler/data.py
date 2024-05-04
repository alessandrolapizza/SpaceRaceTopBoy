"""
Script that generates a graph of the raw altitude and filtered altitude in function of time (ms) from a .csv file given.
"""

import matplotlib.pyplot as plt
import pandas as pd
import sys

def plot_altitude(file_path):
    """
    Plot the raw altitude and filtered altitude in function of time (ms) from a .csv file given.

    Args:
    file_path (str): The path to the .csv file.
    """
    df = pd.read_csv(file_path)

    plt.plot(df['Time [ms]'], df[' Raw Altitude [m]'], label='Raw altitude')
    plt.plot(df['Time [ms]'], df[' Filtered Altitude [m]'], label='Filtered altitude')
    plt.xlabel('Time (ms)')
    plt.ylabel('Altitude (m)')
    plt.legend()
    plt.show()

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('Usage: python3 plot_altitude.py <file_path>')
        sys.exit(1)

    plot_altitude(sys.argv[1])