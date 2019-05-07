// File:   plagiarismCatcher.cpp
// Author: Jackson S. Hall / jsh3647
// Date:   5/4/19
// This program checks a directory of files for plagiarism by checking
// how many instances there are of identical chunks of words.
//
// Call using the following form:
// 	./plagiarismCatcher [directory] [chunkSize] [threshold]
// [directory] is the location of files to check
// [chunkSize] is the number of consecutive words to compare
// [threshold] is the minimum number of matches to flag as plagiarism
//
// Example call:
// 	./plagiarismCatcher path/to/text/files 6 200

#include <sys/types.h>
#include <algorithm> // For sort()
#include <dirent.h>
#include <errno.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

#include "hashTable.h"

using namespace std;

// Contains a collision record for file1 and file2.
class Record
{
public:
    string file1, file2;
    int collisions;

    bool operator <(Record const &rhs) const
    {
        return (collisions < rhs.collisions);
    }
/*
    bool operator<=(Record const &rhs) {
        return collisions <= rhs.collisions;
    }
    bool operator>(Record const &rhs) {
        return collisions > rhs.collisions;
    }
    bool operator>=(Record const &rhs) {
        return collisions >= rhs.collisions;
    }
    bool operator==(Record const &rhs) {
        return collisions == rhs.collisions;
    }
    bool operator!=(Record const &rhs) {
        return collisions != rhs.collisions;
    }
*/
};

// Given a directory name [dir], this function creates a vector [files]
// of the file names in that directory.  (This function was provided as
// starter code.)
int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        string nextName = dirp->d_name;

        // Don't include "." and ".." in the list
        if (nextName != "." && nextName != "..") {
           files.push_back(string(dirp->d_name));
        }
    }

    closedir(dp);
    return 0;
}

// This function gets all sequences of [chunkSize] words in the file
// [fileName], returning the number of chunks found.  [fileNo] is the
// index of the current file, which is needed for hash table entries to
// count collisions.
int getChunks(string fileName, int fileNo, int chunkSize, HashTable &h)
{
    ifstream file;
    file.open(fileName.c_str());
    vector<string> wordQueue;

    int count = 0;
    bool done = false;

    // Populate the queue with the first [chunkSize] words in the
    // file.  If there are less than that many words in the file,
    // do nothing and return.
    string nextWord;
    for (int i = 0; i < chunkSize && !done; i++) {
        if (file.eof()) done = true;
        else {
            file >> nextWord;
            wordQueue.push_back(nextWord);
        }
    }

    while (!done) {
        count++;

        // Concatenate the words in the queue into one string for the input
        // to the hash function
        string key = "";        
        for (vector<string>::iterator i = wordQueue.begin();
            i < wordQueue.end(); i++) {

            key += *i;
        }
        
        // TESTING - Output the key
        // cout << count << " - " << key << endl;
        
        // Add this key to the hash table
        h.addEntry(key, fileNo);

        // Get the next chunk by adding the next word from the file to
        // the end of the queue and removing the word at the front of
        // the queue.
        file >> nextWord;
        if (file.eof()) done = true;
        else {
            wordQueue.push_back(nextWord);
            wordQueue.erase(wordQueue.begin());
        }
    }

    file.close();
    return count;
}

int main(int argc, char **argv)
{
    string dir;
    int chunkSize;
    int threshold;

    // By default, use "sm_doc_set" as the directory, 6 as the
    // chunk size, and 200 as the threshold.
    if (argc == 1) {
        dir = "sm_doc_set";
        chunkSize = 6;
        threshold = 200;
    }
    else if (argc == 4) {
        dir = string(argv[1]);
        chunkSize = atoi(argv[2]);
        threshold = atoi(argv[3]);
    }
    else { // Invalid call
        cout << "Error: Invalid input paramters" << endl;
        return 1;
    }

    //string dir = string("sm_doc_set");
    vector<string> files;
    getdir(dir,files);

/*
    for (unsigned int i = 0;i < files.size();i++) {
        cout << i << files[i] << endl;
    }
*/

    HashTable h;
    int totalChunks = 0;
    int fileNo = 0;
    for (vector<string>::iterator i = files.begin();
        i < files.end(); i++) {

        // Append directory to beginning of file name
        string nextFile = dir;
        if (nextFile[nextFile.length()-1] != '/') {
            nextFile += "/";
        }
        nextFile += *i;

        totalChunks += getChunks(nextFile, fileNo, chunkSize, h);
        fileNo++;
    }

/*
    cout << endl;
    cout << "TOTAL CHUNKS: " << totalChunks << endl;
*/

/*
    // TESTING - Output counts of all collisions
    cout << endl;
    cout << "COLLISIONS" << endl;
    for (int i = 0; i < files.size(); i++) {
        for (int j = i+1; j < files.size(); j++) {
            cout << "(" << files[i] << ", " << files[j] << ") - ";
            cout << h.collisions(i, j) << endl;
        }
    }
*/

    vector<Record> results;

    // Push all pairs of files that exceed collision threshold into
    // results vector
    for (int i = 0; i < files.size(); i++) {
        for (int j = i+1; j < files.size(); j++) {
            int count = h.collisions(i, j);
            if (count >= threshold) {
                Record nextRecord;
                nextRecord.file1 = files[i];
                nextRecord.file2 = files[j];
                nextRecord.collisions = count;

                results.push_back(nextRecord);
            }
        }
    }

    // Compare using operator<
    sort(results.begin(), results.end());

    // Output highest collision counts first
    for (vector<Record>::iterator i = results.end() - 1;
        i >= results.begin(); i--) {
        
        cout << i->collisions << ": ";
        cout << i->file1 << " " << i->file2 << endl;
    }

    return 0;
}

