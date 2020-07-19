#include "config.h"
#include <gmpxx.h>
#include <iostream>
#include <vector>
#include <set>
using namespace std;

mpz_class nperm(vector<int> pattern)
// nperm({4,3,3,3,2})=5!/1!3!1!=20.
{
  mpz_class ret=1;
  int i,j;
  for (i=0;i<pattern.size();i++)
  {
    if (i==0 || pattern[i]!=pattern[i-1])
      j=1;
    ret=ret*(i+1)/j;
  }
  return ret;
}

mpz_class nNotFull(int n,vector<int> pattern,set<int> sums)
{
  int i;
  set<int>::iterator j;
  mpz_class ret;
  if (sums.count(n))
    ret=0;
  else if (pattern.size()>=n)
    ret=nperm(pattern);
  else
  {
    ret=0;
    for (i=1;i<=(pattern.size()?pattern.back():n-1);i++)
    {
      set<int> newSums;
      for (j=sums.begin();j!=sums.end();j++)
      {
	newSums.insert(*j);
	newSums.insert(*j+i);
      }
      pattern.push_back(i);
      ret+=nNotFull(n,pattern,newSums);
      pattern.pop_back();
    }
  }
  return ret;
}

mpz_class nNotFull(int n)
{
  set<int> sums({0});
  vector<int> pattern;
  return nNotFull(n,pattern,sums);
}

int main(int argc, char *argv[])
{
  int i;
  for (i=0;i<11;i++)
    cout<<i<<' '<<nNotFull(i)<<endl;
  return 0;
}
