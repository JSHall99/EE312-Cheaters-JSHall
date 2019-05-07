final: plagiarismCatcher.o hashTable.o
	g++ -o catcher plagiarismCatcher.o hashTable.o -std=c++0x

plagiarismCatcher.o: plagiarismCatcher.cpp hashTable.h
	g++ -c plagiarismCatcher.cpp -std=c++0x

hashTable.o: hashTable.cpp hashTable.h
	g++ -c hashTable.cpp -std=c++0x
