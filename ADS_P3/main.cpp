/*************************************************
* ADS Praktikum 3
* main.cpp
*
*************************************************/
#define CATCH_CONFIG_RUNNER
#include <iostream>
#include "Tree.h"
#include "catch.h"

using namespace std;

void mainscreen_addTreeCSV(Tree*& ref)
{
	char j;
	cout << "+ Moechten Sie die Daten aus der Datei ExportZielanalyse.csv "
		"importieren(j / n) ? >";
	cin >> j;
	if (j == 'j')
	{
		ifstream csvread;
		csvread.open("ExportZielanalyse.csv", ios::in);
		if (!csvread.is_open())
		{
			cout << "Fehler beim Lesen!" << endl;
			return;
		}
		else
		{
			string name, age, postcode, income;

			while (!csvread.eof())
			{
				getline(csvread, name, ';');
				getline(csvread, age, ';');
				getline(csvread, income, ';');
				getline(csvread, postcode, '\n');
				if (name == "" || age == "" || income == "" || postcode == "") {
					continue;
				}
				ref->addNode(name, stoi(age), stod(income), stoi(postcode));
			}
			csvread.close();
		}
		cout << "+ Daten wurden dem Baum hinzugefuegt." << endl;
	}
}

int main() {

	int result = Catch::Session().run();

	///////////////////////////////////////
	// Ihr Code hier:
    Tree* Tr = new Tree();
    int wahl, Alter, plz, ID, Niv;
    char ant;
    string Name;
    double Income;
    do {
        cout << "========================================\n";
        cout << " ADS Rot-Schwarz-Baum Praktikum\n";
        cout << "========================================\n";
        cout << "1) Datensatz einfuegen, manuell\n"
            << "2) Datensatz einfuegen, CSV Datei\n"
            << "3) Suchen\n"
            << "4) Ausgabe in Levelorder\n"
            << "5) Ausgabe in Levelorder (mit Niveauauswahl)\n"
            << "6) Beenden\n"
            << "?> ";
        cin >> wahl;
        if (wahl == 1) {
            cin.ignore();
            cout << "+ Bitte geben Sie die den Datensatz ein:\n"
                << "Name ?> ";
            getline(cin, Name);
            cout << "Alter ?>";
            cin >> Alter;
            cout << "Einkommen ?>";
            cin >> Income;
            cout << "PLZ ? >";
            cin >> plz;
            Tr->addNode(Name, Alter, Income, plz);
            cout << "+ Ihr Datensatz wurde eingefuegt" << endl;
        }
        else if (wahl == 2) {
            mainscreen_addTreeCSV(Tr);
        }
        else if (wahl == 3) {
            cin.ignore();
            cout << "+ Bitte geben Sie den zu suchenden Datensatz an" << endl;
            cout << " Name ?> ";
            getline(cin, Name);
            Tr->searchNode(Name);
        }
        else if (wahl == 4) {
            cout << "Ausgabe in Levelorder als binärer Suchbaum :\n\n";
            Tr->printAll();
            cout << "Ausgabe in Level order als 234-Baum:\n";
            Tr->printLevelOrder();
        }
        else if (wahl == 5) {
            cin.ignore();
            cout << "+ Bitte geben Sie das auszudrückende Niveau an" << endl;
            cout << " Nieau ?>";
            cin >> Niv;
            Tr->printLevelOrder(Niv);
        }

    } while (wahl != 6);


	//
	///////////////////////////////////////
	system("PAUSE");

	return result;
}
