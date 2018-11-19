#include <iostream>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/program_options.hpp>
#include <boost/tokenizer.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;

int k = 0;

void getAmount(boost::filesystem::path path);

int main() {
  getAmount("/home/laczaroli/Letöltések/jdk-11.0.1/lib");
  cout << k << endl;
  return 0;
}


void getAmount(boost::filesystem::path path) {
  for(boost::filesystem::directory_entry & entry : boost::filesystem::directory_iterator(path))
  {
    string ext (".java");
    if(is_regular_file(entry.path()))
    {
      if(!ext.compare(boost::filesystem::extension(entry.path())))
        k++;
    } else getAmount(entry.path());
  }
}
