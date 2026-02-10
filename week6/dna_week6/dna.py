import argparse
import sys
import csv
import os

def main():
    """
    Pulling in command line arguments, included the usage and also default values in case there are no arguments passed
    """
    parser = argparse.ArgumentParser("Usage: python3 <program> <database> <file_name>.")
    parser.add_argument("-str", help="Enter the CSV file name", default='dna/databases/small.csv')
    parser.add_argument("-sequence", help="Enter the CSV file name", default='dna/sequences/1.txt')
    args = parser.parse_args()

    """
    Assigning files to their right file names
    Checking if these files are actually present in the right os path
    
    Opening and reading both the csv and txt file in read mode
    Intentionally opening the csv file in a manual way and closing towards the end
    """
    csvFile = args.str
    sequenceFile = args.sequence

    csvExists = os.path.exists(csvFile)
    fileExists = os.path.exists(sequenceFile)

    csvfile = open(csvFile, "r", newline="")
    reader = csv.DictReader(csvfile, delimiter=',')
    if not csvExists or os.path.getsize(csvFile) == 0:
        return "Invalid CSV"
    if reader.fieldnames:
        subsequences = reader.fieldnames
    
    with open(sequenceFile, "r") as filename:
        content = filename.read()
        if not fileExists or os.path.getsize(sequenceFile) == 0:
            return "Invalid File"

    """
    Assigning the STR values against their index from the sequence
    """
    strCounts = {}
    for i in subsequences:
            strCounts[i] = str(longestSequence(content, i))
    
    """
    Checking which of the rows in the csv matches with the STR values from the sequence
    Using count and match as flags to compare these values against each row i.e., person in the csv and returning the name of the person who is a match
    """
    match = False
    for row in reader:
        count = 0
        for i in subsequences:
            if not i == 'name':
                if row[i] == strCounts[i]:
                    count += 1
                else:
                    break
        
        if count == len(strCounts)-1:
            match = True
            print(row['name'])
            break
        else:
            continue
        
    if match == False:
        print("No match")
    
    # Closing the opened csv file
    csvfile.close()
    
"""
Calculating the longest number of consecutive repetitions for each STR index
"""
def longestSequence(sequence, subsequence):
    sequenceLength = len(sequence)
    subsequenceLength = len(subsequence)

    longestMatch = 0

    for i in range(sequenceLength):
        counter = 0
        while True:
            start = i + (subsequenceLength * counter)
            end = start + subsequenceLength

            if sequence[start:end] == subsequence:
                counter += 1
            else:
                break

            longestMatch = max(longestMatch, counter)

    return longestMatch


if __name__ == "__main__":
    main()