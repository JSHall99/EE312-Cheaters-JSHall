// File:   hashTable.h
// Author: Jackson S. Hall
// Date:   5/4/19
// The HashTable class 

#include <string>

using namespace std;

class HashTable
{
public:
   HashTable();

   HashTable(int numFiles);

   // Need to deallocate all table nodes, collision array.
   ~HashTable();

   // Function: addEntry
   // Hashes the string [words] and adds it to the table.  [fileNo]
   // identifies the file that the chunk came from.
   void addEntry(string words, int fileNo);

   typedef struct record {
      int files[2];
      int count; // Number of collisions between files[0] and files[1]
   } record;

   vector<record> collisions();
   
private:
   // Hash table indices from 0 to (tableSize-1)
   // I chose 1608433 because it is a prime number, and the program counted
   // 1608418 six-letter chunks in the large file set.
   const int tableSize = 1608433;

   // Each entry of the table consists of a linked list of tableNodes.
   typedef struct tableNode {
      int fileNo;
      struct tableNode *next;
   } tableNode;

   tableNode *table[tableSize];

   // 2D array counting the number of collisions between each pair of files.
   int **collisions;

   // Function: hashFn
   // Converts a string into a numerical hash value.
   int hashFn(string words);

}
