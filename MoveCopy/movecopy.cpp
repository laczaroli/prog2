#include <iostream>
#include <cstring>

using namespace std;

class Character {
private:
  char* desc;
  char* name;
  int desc_length, name_length;
public:
  Character(const char* name, const char* desc)
  {
    name_length = sizeof(name)+1;
    this->name = new char[name_length+1];
    memcpy(this->name,name,name_length);

    desc_length = sizeof(desc)+1;
    this->desc = new char[desc_length+1];
    memcpy(this->desc, desc, desc_length);


      //Alapértelmezett konstruktor.
  }

  Character(const Character& kari) {
    desc_length = kari.desc_length;
    name_length = kari.name_length;
    name = new char[name_length];
    desc = new char[desc_length];
    memcpy(desc,kari.desc,desc_length);
    memcpy(name,kari.name,name_length);
    cout << "Copy" << endl;
  }

  Character(Character&& kari) {
    desc_length = kari.desc_length;
    name_length = kari.name_length;
    name = new char[name_length];
    desc = new char[desc_length];
    memcpy(desc,kari.desc,desc_length);
    memcpy(name,kari.name,name_length);

    kari.name = nullptr;
    kari.desc = nullptr;
    cout << "Move" << endl;
  }

  ~Character() {
    delete[] desc;
    delete[] name;
  }

  const char* getName() {
    return name;
  }

  friend std::ostream& operator<< (std::ostream& stream, const Character& str);
};

std::ostream& operator<< (std::ostream& stream, const Character& str)
{
  stream << str.name << str.desc;
  return stream;
}

void movebeindito(Character kari)
{
  cout << kari << endl;
}

int main() {
  Character Roli("Roli","Kiraly");

  //Mivel itt ugyanazon a memóriacímen vannak, és kétszer akarjuk törölni a destruktorban
  //ugyan azon memóriacímet.
  Character RoliKetto = Roli;
  //Ha pedig megírjuk rá a deep copy constructort, akkor telejsen más memóriacímre kerül a "RoliKetto" karakter

  cout << &Roli << endl;
  cout << &RoliKetto << endl;

  movebeindito(move(Roli));
  return 0;
}
