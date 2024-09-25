#define CATCH_CONFIG_RUNNER
#include "catch.h"
#include <iostream>
#include"hashtable.h"

int main() {
    Catch::Session().run();

    int eingabe;
    double belegungsfaktor;
    do {
	  cout << "Waehlen Sie die Kollisionsstrategie an :" << endl;
	  cout << "1. Lineares Sondieren" << endl << "2. Quadratisches Sondieren" << endl << "3. Doppeltes Hashing" << endl;
	  cout << "eingabe :";
	  cin >> eingabe;
        } while (eingabe < 1 || eingabe>3);


    cout << "Waehlen Sie die Belegungsfaktor an (standard = 0.6) :";
    cin >> belegungsfaktor;
    if (belegungsfaktor > 1 || belegungsfaktor < 0)
	  belegungsfaktor = 0.6;
      
    HashTable table(1000, belegungsfaktor, eingabe);
    int anzahl = 200;
    int Ugrenz = 1000;
    for (int i = 0; i < anzahl; i++) {
	  int element = Ugrenz + rand() % 501;
	  table.insert(element);
  }
  cout << "Anzahl der Kollisionen : " << table.getCollisionCount() << endl;
  

    system("pause");
    return 0;
}