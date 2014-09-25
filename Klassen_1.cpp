#include <iostream>
#include <string>
using namespace std;

class Auto  //Die Klasse wird definiert

{
public: //Elementliste wie var int double string usw
  int geschwindigkeit;
  double preis;
  string farbe;
}; //nach der Definition der Elementliste 

int main()

{
  Auto porsche;
  porsche.geschwindigkeit = 200;
  cout << "Der Ferrari erreicht " <<  porsche.geschwindigkeit << " Sachen" <<endl;
}
