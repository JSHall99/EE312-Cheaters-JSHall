Plagiarism Catcher
Author: Jackson S. Hall
Date:   5/7/19

This program checks a directory of files for plagiarism, returning the
number of consecutive n-word chunks that each of the files have in common
and flagging files with a score above a threshold value.

To compile the program, type "make" at the Linux command line.

Options for running the program:

	./plagiarismCatcher [directory] [chunkSize] [threshold]
	./plagiarismCatcher [directory]

The latter option uses default settings for the chunk size and threshold.
