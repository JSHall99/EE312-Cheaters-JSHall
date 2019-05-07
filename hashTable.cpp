// File:   hashTable.cpp
// Author: Jackson S. Hall
// Date:   5/4/19

#include "hashTable.h"

using namespace std;

HashTable::HashTable()
{
   // I chose 1608433 because it is a prime number, and the program counted
   // 1608418 six-letter chunks in the large file set.
   tableSize = 100003;
   table = new tableNode* [tableSize];
   for (int i = 0; i < tableSize; i++) {
      table[i] = NULL;
   }
}

HashTable::~HashTable()
{
   for (int i = 0; i < tableSize; i++) {
      // Delete each node of the linked list
      deleteList(table[i]);
   }
   delete[] table;
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
}

int HashTable::collisions(int fileNo1, int fileNo2)
{
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
