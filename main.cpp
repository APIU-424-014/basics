#include <iostream>
#include <string>
using namespace std;

class Auto
{
public:
  int geschwindigkeit;
  double preis;
  std::string farbe;
};

int main()
{
  Auto porsche;
  porsche.geschwindigkeit = 200;
  cout << "Der Ferrari erreicht " <<  porsche.geschwindigkeit << " Sachen" << std::endl;
}
