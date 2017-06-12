/* DoubleLinkedListArray - a container class for linear sieves
Author - Andrew Shallue
Date - July 2015

Closely follows Jon Sorenson, "An introduction to Prime number sieves" 1990
A computer science technical report written while he was at Wisconsin

Implementation is of an array of records, connected sequentially with pointers 
a la a doubly-linked list.  Thus we have random access (like vectors or arrays),
as well as constant time insertion and deletion (like list container).

Dealing with the endpoints is a sticky special case.  I've decided not to 
create special endnodes.  Rather, for the left endpoint x we have 
x.prev = -1, and for the right endpoint x we have x.next = -2.
Then these are checked when removing.
*/

#ifndef DOUBLELINKEDLISTARRAY_H
#define DOUBLELINKEDLISTARRAY_H

#include<vector>
#include<NTL/ZZ.h>

NTL_CLIENT


// The individual items of the container.  It contains integers as 
// the next and previous elements, as well as a boolean recording if the item
// is currently part of the container or not
class ListItem{
   public:
      ListItem(long n);  //next = n+1, prev = n-1
      ListItem(long prev, long next); //sets prev and next

      long getnext(); // returns next integer
      long getprev(); // returns prev integer
      bool ison(); // returns true if present is flipped on
      void turnoff(); // flips item from on to off
      void setnext(long n); // sets next to n
      void setprev(long n); // sets prev to n

   private:
      long prev;
      long next;
      bool present;
};

class DoubleLinkedListArray{
   public:
      // initialize array to all integers < bound, linked sequentially
      DoubleLinkedListArray(long bound);

      long next(long x); //returns next integer after x
      long prev(long x); //returns prev integer before x
      void remove(long x); //removes x from array, meaning pointers go around it
      ListItem at(long x); //returns ListItem at index x

   private:
      vector<ListItem> container;
};

#endif //DOUBLELINKEDLISTARRAY_H
