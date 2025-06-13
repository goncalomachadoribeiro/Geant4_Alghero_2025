#!/usr/bin/env python
"""This Python script displays histogram as saved in CSV format.

How to run it:
  - python csv_histogram.py name_of_a_file.csv nbins minbin maxbin

Note: It does not open any other Geant4 output files.
"""

#from __future__ import division
import numpy as np
import matplotlib.pyplot as plt
import codecs
import sys
import os

def load_csv(path):
    """Load a histogram as output from Geant4 analysis tools in CSV format.
    
    Note: This method is useful for ANY Geant4 analysis tools histogram.

    Parameters
    ----------
    path: str
        Path to the CSV file
    """
    meta = {}
    data = []
    with codecs.open(path, encoding="ASCII") as in_file:
        for line in in_file:
            if line.startswith("#"):
                try:
                    key, value = line[1:].strip().split(" ", 1)
                    meta[key] = value
                except:
                    pass
            else:
                try:
                    data.append([float(frag) for frag in line.split(",")])
                except:
                    pass
    if "class" not in meta or (meta["class"] != "tools::histo::h1d"):
        raise RuntimeError("The file {0} is not an CSV export of a Geant4 histogram.".format(path))
    data = np.asarray(data)
    return data, meta


def plot_histogram(path):
    """Plot the detector histogram and saves it to histogram.png.
    
    Parameters
    ----------
    path: str
        The path to the file.
    """
    
    if not os.path.isfile(path):
        print("File {0} does not exist. Make sure you created it.".format(path))
        return
    
    data, meta = load_csv(path)
    fig, ax = plt.subplots()

    # This reads the infos from the meta data of the .csv
    nbin, minbin, maxbin = (int(z) for z in meta["axis"].split(" ")[1:])
    
    x = np.linspace(minbin, maxbin, nbin + 1)   
    bin_width = (maxbin - minbin) / (nbin * 1.0)
        
    # Display the histogram.
    ax.bar(x[:-1:1], data[1:-1:1,1], bin_width, color="red", label="NaI detector")
    ax.set_xlim(minbin, maxbin)
    
    ax.legend()
    ax.set_title(meta["title"])
    ax.set_xlabel("Energy [keV]")
    ax.set_ylabel("Counts")
    fig.savefig("histogram.png")
    plt.show()
    print("Histogram has been saved to histogram.png")

if __name__ == "__main__":
    if len(sys.argv) == 2:
        path = sys.argv[1]
    else:
        path = "task_h1_eDep.csv"
    plot_histogram(path)
