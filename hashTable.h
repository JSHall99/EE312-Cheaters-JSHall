// File:   hashTable.h
// Author: Jackson S. Hall
// Date:   5/4/19
// The HashTable class 

#include <string>

class HashTable
{
public:
   HashTable();

   ~HashTable();
   
private:
   // Hash table indices from 0 to (tableSize-1)
   const int tableSize = 53; // CHANGE THIS!

   // Function: hashFn
   // Converts a string into a numerical hash value.
   int hashFn(string words);

}
