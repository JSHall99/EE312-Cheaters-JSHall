// File:   hashTable.cpp
// Author: Jackson S. Hall
// Date:   5/4/19

#include <hashTable.h>

using namespace std;

int HashTable::hashFn(string words)
{
   // Format the string for processing.  Remove all characters besides
   // letters and numbers, and convert to all caps.
   for (int i = 0; i < words.length; i++) {
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
   for (int i = 0; i < words.length; i++) {
      result += 37*result + words[i];
      result %= tableSize;
   }

   return result;
}
