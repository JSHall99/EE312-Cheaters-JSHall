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
   HashTable();

   // Need to deallocate all table nodes
   ~HashTable();

   // Function: addEntry
   // Hashes the string [words] and adds it to the table.  [fileNo]
   // identifies the file that the chunk came from.
   void addEntry(string words, int fileNo);

   // Function: collisions
   // Returns the number of collisions between the files with indexes
   // [fileNo1] and [fileNo2].  This is the number of hash values that both
   // files had in common; in other words, if both of files hashed to the
   // same value multiple times, that would still only add 1 to the total.
   int collisions(int fileNo1, int fileNo2);
   
private:
   // Hash table indices from 0 to (tableSize-1)
   int tableSize;

   // Each entry of the table consists of a linked list of tableNodes.
   typedef struct tableNode {
      int fileNo;
      struct tableNode *next;
   } tableNode;

   tableNode **table;

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
