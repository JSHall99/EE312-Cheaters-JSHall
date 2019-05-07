// File:   hashTable.h
// Author: Jackson S. Hall
// Date:   5/4/19
// The HashTable class 

#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H

#include <string>

using namespace std;

class HashTable
{
public:
   HashTable(int numFiles);

   HashTable();

   // Need to deallocate all table nodes and the collision table
   ~HashTable();

   // Function: addEntry
   // Hashes the string [words] and adds it to the table.  [fileNo]
   // identifies the file that the chunk came from.
   void addEntry(string words, int fileNo);

   // Function: collisions
   // Returns the number of collisions between the files with indexes
   // [fileNo1] and [fileNo2].
   int collisions(int fileNo1, int fileNo2);
   
private:
   // Hash table indices from 0 to (tableSize-1)
   int tableSize;

   // Used for dimensions of collisionsTable.
   int numFiles;

   // Each entry of the table consists of a linked list of tableNodes.
   typedef struct tableNode {
      int fileNo;
      struct tableNode *next;
   } tableNode;

   // Hash table
   tableNode **table;

   // Table counting number of collisions between each file.
   // collisionsTable[i][j] = # collisions b/w files No. i and j
   // Must be dynamically allocated to have dimensions equal to the
   // number of files.
   int **collisionsTable;

   // Function: hashFn
   // Converts a string into a numerical hash value.
   int hashFn(string words);

   // Returns true if the file identified by [fileNo] is contained in the
   // list pointed to by [head], false otherwise.  Detects if any chunk
   // in that file was mapped to that hash table entry.
   bool listContains(int fileNo, tableNode *head);

   // Deletes the linked list pointed to by [node].
   void deleteList(tableNode *node);
};

#endif
