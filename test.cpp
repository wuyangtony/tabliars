/*
#include <ctime>
#include <time.h>
#include <vector>
#include "formulas.h"
#include "tab_carmichael.h"
#include "tab_liars.h"
#include "first_liar.h"
#include <NTL/ZZ.h>
#include <list>
#include <NTL/RR.h>  
#include "sievepractice.h"
#include "lowestprimesieve.h"
#include "tab_psp.h"
#include "DoubleLinkedListArray.h"
*/
#include <unordered_map>
#include <iostream>

//NTL_CLIENT
using namespace std;

int main() {

  unordered_map<long,long> mymap;
  mymap.emplace(1,2);


  pair<long,long> example(3,4);
  mymap.insert(example);
  
  cout << "hash table contains\n";
  for(auto& x: mymap) cout << x.first << " : " << x.second << "\n";

return 0;
}
