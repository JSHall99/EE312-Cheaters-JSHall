// File:   hashTable.cpp
// Author: Jackson S. Hall
// Date:   5/4/19

#include "hashTable.h"
#include <iostream>

using namespace std;

HashTable::HashTable(int numFiles)
{
   // Allocate hash table
   tableSize = 1608433;
   table = new tableNode* [tableSize];
   for (int i = 0; i < tableSize; i++) {
      table[i] = NULL;
   }

   // Allocate collisions table
   this->numFiles = numFiles;
   collisionsTable = new int* [numFiles];
   for (int i = 0; i < numFiles; i++) {
      collisionsTable[i] = new int[numFiles];
      for (int j = 0; j < numFiles; j++) {
         collisionsTable[i][j] = 0;
      }
   }
}

HashTable::HashTable()
{
   // Default - 
   HashTable(1000);
   cout << "WARNING: HashTable default constructor called" << endl;
}

HashTable::~HashTable()
{
   // Deallocate hash table
   for (int i = 0; i < tableSize; i++) {
      // Delete each node of the linked list
      deleteList(table[i]);
   }
   delete[] table;

   // Deallocate collision table
   for (int i = 0; i < numFiles; i++) {
      delete[] collisionsTable[i];
   }
   delete[] collisionsTable;
}

void HashTable::deleteList(tableNode *node)
{
   if (node == NULL) return;
   else deleteList(node->next);
   delete node;
   node = NULL;
}

void HashTable::addEntry(string words, int fileNo)
{
   int hashIndex = hashFn(words);

   // Add to front of linked list at hashIndex
   tableNode *nextNode = new tableNode;
   nextNode->fileNo = fileNo;
   nextNode->next = table[hashIndex];
   table[hashIndex] = nextNode;  

   // Update collision table
   nextNode = nextNode->next;
   while (nextNode != NULL) {
      collisionsTable[nextNode->fileNo][fileNo]++;
      collisionsTable[fileNo][nextNode->fileNo]++;
      nextNode = nextNode->next;
   }
   
}

int HashTable::collisions(int fileNo1, int fileNo2)
{
/*
   int count = 0;
   for (int i = 0; i < tableSize; i++) {
      
      // Increment the collision count if both files had a chunk that
      // hashed to this index.
      if (listContains(fileNo1, table[i]) &&
         listContains(fileNo2, table[i])) {

         count++;
      }
   }

   return count;
*/

   return collisionsTable[fileNo1][fileNo2];
}

bool HashTable::listContains(int fileNo, tableNode *head)
{
   if (head == NULL) return false;
   else if (head->fileNo == fileNo) return true;
   else return (listContains(fileNo, head->next));
}


int HashTable::hashFn(string words)
{
   // Format the string for processing.  Remove all characters besides
   // letters and numbers, and convert to all caps.
   for (int i = 0; i < words.length(); i++) {
      bool validChar = false;
      if (words[i] >= 'a' && words[i] <= 'z') {
         validChar = true;
         words[i] += 'A' - 'a'; // Convert to caps
      }
      if (words[i] >= 'A' && words[i] <= 'Z') validChar = true;
      if (words[i] >= '0' && words[i] <= '9') validChar = true;
      
      // If the character is not valid, remove it from the string.
      if (validChar == false) {
         words.erase(words.begin() + i);

         // Check the new character at index i during the next iteration
         // of the loop.
         i--;
      }
   }

   // Calculate the hash of the standardized string by calculating its
   // decimal value as if it were a base-36 number (since there are 36
   // possible characters in the string).  Take the reuslt mod tableSize. 
   int result = 0;
   for (int i = 0; i < words.length(); i++) {
      result += 37*result + words[i];
      result %= tableSize;
   }

   return result;
}
