/*************************************************
* ADS Praktikum 1.1
* main.cpp
* 
*************************************************/
#define CATCH_CONFIG_RUNNER

#include <iostream>
#include <string>
#include "Ring.h"
#include "catch.h"

using namespace std;

void print_menu()
{
    cout << "====================================" << endl
        << " SuperBackUp-Organizer over 9000, by. Son Goku" << endl
        << "====================================" << endl
        << "1) Backup anlegen" << endl
        << "2) Backup suchen" << endl
        << "3) Alle Backups ausgeben" << endl
        << "4) Programm beenden" << endl
        << "?> ";
}

int main()
{
	int result = Catch::Session().run();
	// Ihr Code hier:
    string eingabe; 
	string desc;
	int wahl = 0;
	Ring Backup;

    do
    {
        print_menu();

        cin>> wahl;

        if(wahl == 1){
            cout << "+Neuen Datensatz anlegen\n";
			cout << "Beschreibung ?> ";
			cin.ignore();
			getline(cin, desc);
			cout << "Daten ?> ";
			getline(cin, eingabe);
			Backup.addNewNode(desc, eingabe);
			cout << "+Ihr Datensatz wurde hinzugefuegt.\n";
        }
        else if(wahl == 2){
            cout << "+Nach welchen Daten soll gesucht werden?\n";
			cout << "?> ";
			cin.ignore();
			getline(cin, eingabe);
			Backup.search(eingabe);
        }
        else if (wahl == 3) {
			Backup.print();
			cout << endl;
		}
        else if(wahl == 4){
            break;
        }
		else{
			cout << "falsche Eingabe\n";
		}



    } while (wahl);
	//
	///////////////////////////////////////
	system("Pause");
	return result;
}