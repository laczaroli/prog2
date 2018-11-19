#include <iostream>
#include <vector>
#include <map>
#include <algorithm>


using namespace std;

int main() {
  vector<char> karakterek = {'A', 'E', 'I', 'O','C'};
  vector<int> szamok = {5, 2, 1, 9, 4};
  map<char,int> mep;
  for(int i = 0; i<karakterek.size(); i++)
  {
    mep[karakterek[i]] = szamok[i];
  }

  sort(mep.begin()->second, mep.end()->second);
  return 0;
}
