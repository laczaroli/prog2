#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <boost/filesystem.hpp>
#include <sstream>
#include <math.h>
#include <algorithm>

/*int sumofVec(std::vector<int> losts)
{
  int sum = 0;
  for(int i : losts)
  {
    sum += i;
  }
  return sum;
}*/

std::vector<int> searchinFile(boost::filesystem::path file, std::string search) {
  boost::filesystem::ifstream brainb(file);
  std::vector<int> vec;
  std::string line;

  while (std::getline(brainb, line)) {
    if(line.find(search) != std::string::npos)
    {
      line = line.substr(search.length()+1);
      break;
    }
  }

  std::istringstream word (line);
  std::string k;
  while(word >> k)
  {
    vec.push_back(stoi(k));
  }
  return vec;
}

std::vector<int> merge (std::vector<int> a, std::vector<int> b)
{
  std::vector<int> merged;
  bool placed = false;
  for(int i = 0; i<a.size(); i++)
  {
    merged.push_back(a[i]);
    placed = false;
    for(int j = i; j<b.size(); j++)
    {
      if(!placed)
      {
        merged.push_back(b[j]);
        placed = true;
        break;
      }
    }
  }
  return merged;
}


std::vector<int> unique_avg(std::vector<std::vector<int>> vec)
{
  std::cout << "OSZTÓK: ";
  int sum = 0, oszto = 0;
  std::vector<int> avg;
  for(int i = 0; i < vec[0].size(); i++)
  {
    oszto = vec.size();
    for(int j = 0; j < vec.size(); j++)
    {
      if(vec[j][i] != -1)
        sum += vec[j][i];
      else { oszto --; }
    }
    if(oszto > 0)
    {
      avg.push_back(sum/oszto);
      std::cout << oszto << ",";
    }
    sum = 0;
  }
  std::cout << std::endl;
  return avg;
}

std::vector<std::vector<int>> osszes;
std::vector<std::vector<int>> fillVec(boost::filesystem::path path, std::string ext, std::string ext2, std::string outfile) {
  std::vector<int> l2f;
  std::vector<int> f2l;
  std::vector<int> temp;
  for(boost::filesystem::directory_entry & entry : boost::filesystem::directory_iterator(path))
  {
    if(is_regular_file(entry.path()))
    {
      if(!ext.compare(boost::filesystem::extension(entry.path())) || !ext2.compare(boost::filesystem::extension(entry.path())))
      {
        l2f = searchinFile(entry.path(),"lost2found:");
        f2l = searchinFile(entry.path(),"found2lost:");
        if(!l2f.empty() && !f2l.empty())
        {
          temp = merge(l2f,f2l);
          osszes.push_back(temp);
        }
        l2f.clear();
        f2l.clear();
        temp.clear();
      }
    } else fillVec(entry.path(), ext,ext2, outfile);
  }
  return osszes;
}


int main(int argc, char** argv)
{
  std::ifstream brainb(argv[1]);
  std::string buffer;
  std::ofstream total("total.txt");
  std::vector<std::vector<int>> tempVec = fillVec(argv[1], ".txt",".TXT", "merkee.txt");
  int rownum, max = 0;
  for(int i = 0; i < tempVec.size(); i++)
  {
    if(max < tempVec[i].size())
    {
      max = tempVec[i].size();
      rownum = i;
    }
  }

  for(int i = 0; i<tempVec.size(); i++)
  {
    while(max > tempVec[i].size())
    {
      tempVec[i].push_back(-1);
    }
  }

  std::vector<int> avg_vec = unique_avg(tempVec);
  std::cout << "Értékek: ";
  for(int j : avg_vec)
  {
    std::cout << j << ",";
  }
  std::cout << std::endl;
  //Itt kimentem egy fájlba, az egész 2d-s mátrixomat, mivel a függvénybe külön gyűjtöttem őket.
  //Nem tudom hogy szükséges-e mindkét lépés, de ha nem akkor kivesszük belőle.
  for(int i = 0; i<tempVec.size(); i++)
  {
    for(int j = 0; j<tempVec[i].size(); j++)
    {
      total << tempVec[i][j] << " ";
    }
    total << std::endl;
  }
  total.close();
  brainb.close();
  return 0;
}
