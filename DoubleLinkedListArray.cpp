#include "DoubleLinkedListArray.h"

NTL_CLIENT

// first code for implementing DoublLinkedListArray class
DoubleLinkedListArray::DoubleLinkedListArray(long bound){
  // ListItem(i) points next = i+1, prev = i-1
  for(long i = 0; i < bound; i++){
    container.push_back( ListItem(i) );
  }
  // now the left endpoint correctly points to -1, but we need to change 
  // the right endpoint
  container.at(bound-1).setnext(-2);
}

long DoubleLinkedListArray::next(long x){
  return container.at(x).getnext();
}

long DoubleLinkedListArray::prev(long x){
  return container.at(x).getprev();
}

void DoubleLinkedListArray::remove(long x){
  // careful, next command copies the ListItem.
  // this works when we only want to getnext() and getprev(), but 
  // to turnoff it won't work
  ListItem current = container.at(x); // the item to be removed
 
  container.at(x).turnoff();  //make sure it is set as no longer there

  //now reset the items ahead and behind to point to each other 
  //note the checks that it is not an endpoint.  The other can proceed
  if(current.getnext() >= 0){ 
    container.at(current.getnext()).setprev(current.getprev());
  }
  if(current.getprev() >= 0){
    container.at(current.getprev()).setnext(current.getnext());
  }
  // if neither true, it is last element, and it is simply removed.
}

ListItem DoubleLinkedListArray::at(long x){
  return container.at(x);
}

// now all the code for implementing ListItem class

ListItem::ListItem(long n){
  prev = n-1;
  next = n+1;
  present = true;
}

ListItem::ListItem(long prev, long next){
  prev = prev;
  next = next;
  present = true;
}

long ListItem::getnext(){
  return next;
}

long ListItem::getprev(){
  return prev;
}

bool ListItem::ison(){
  return present;
}

void ListItem::turnoff(){
  present = false;
}

void ListItem::setnext(long n){
  next = n;
}

void ListItem::setprev(long n){
  prev = n;
}

