/*************************************************
* ADS Praktikum 1.1
* Ring.cpp
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
// Ring .cpp
#include "Ring.h"
#include <iostream>

// Ihr Code hier:
Ring::Ring() {
	m_anker = nullptr;
	m_anker->setNext(m_anker);
	m_countNodes = 0;
}

void Ring::addNewNode(std::string new_desc, std::string new_data) {
	RingNode* n_Node = new RingNode(0, new_desc,new_data);    //new node is formed with age = 0
	if (m_anker == nullptr) {
		m_countNodes = 1;
		m_anker = n_Node;		//anker is pointed to new node
		m_anker->setNext(m_anker);
	}
	else {
		if (m_countNodes < 6) {  //if count nodes less than 6 then add new 
			n_Node->setNext(m_anker->getNext());
			m_anker->setNext(n_Node);
			m_anker = n_Node;
			m_countNodes++;
		}
		else {
			RingNode* ptr = m_anker->getNext();
			n_Node->setNext(ptr->getNext());
			m_anker->setNext(n_Node);
			m_anker = n_Node;
			delete ptr;
		}
		RingNode* ptr = m_anker->getNext();
		for (int i = 1; i < m_countNodes; i++) {
			ptr->setOldAge(ptr->getOldAge()+1);                  //set new age as old age + 1 with a loop
			ptr = ptr->getNext();
		}
	}
}

bool Ring::search(std::string txt) {
	if (m_anker != nullptr) {
		RingNode* ptr = m_anker;
		for (int i = 0; i < m_countNodes; i++) {
			if (ptr->getSymbolicData() == txt) {
				std::cout << "Gefunden in Backup: Alter " << ptr->getOldAge()
					<< ", Beschreibung: " << ptr->getDescription() << ", Daten: " << ptr->getSymbolicData() << "\n\n";
				return 1;
			}
			else {
				ptr = ptr->getNext();
			}
		}
	}
	std::cout << "Datensatz konnte nicht gefunden werden.\n";
	return 0;
}

int Ring::print_helper(RingNode* ptr) {                //helper method for recursive print command 
	int i = 0;
	if(ptr != m_anker){
		i = print_helper(ptr->getNext())+1;
	}
	std::cout << "Alter: " << ptr->getOldAge() << ", Beschreibung: " << ptr->getDescription()
		<< ", Daten: " << ptr->getSymbolicData() << " i: " << i << "\n";
	if(i<5)
		std::cout << "--------------------------\n";
	return i;
} 

void Ring::print() {
	if (m_anker != 0) {
		print_helper(m_anker->getNext());
	}
	else
		std::cout << "Backup ist Leer";
}




//
////////////////////////////////////