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
#include <dirent.h>
#include <errno.h>
#include <fstream>
#include <iostream>
#include <queue>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

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
// [fileName], returning the number of chunks found.
int getChunks(string fileName, int chunkSize)
{
    ifstream file;
    file.open(fileName);
    queue<string> words;

    // Populate the queue with the first [chunkSize] words in the
    // file.  If there are less than that many words in the file,
    // do nothing and return.
    string nextWord;
    for (int i = 0; i < chunkSize; i++) {
        if (file.eof()) return 0;
        else {
            file >> nextWord;
            words.push(nextWord);
        }
    }

    int count = 0;
    while (1) {
        count++;

        string concat = "";
        for (int i = 0; i < words.size(); i++) {
            concat += words[i];
        }

        // For testing
        cout << concat << endl;

        // Get the next chunk by adding the next word from the file to
        // the end of the queue and removing the word at the front of
        // the queue.
        file >> nextWord;

        // If the end of file has been reached, we are done.
        if (nextWord == EOF) return count;

        words.push(nextWord);
        words.pop();
    }
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
    vector<string> files = vector<string>();

    getdir(dir,files);

/*
    for (unsigned int i = 0;i < files.size();i++) {
        cout << i << files[i] << endl;
    }
*/

    cout << getChunks("abf0704.txt", chunkSize);
    return 0;
}

