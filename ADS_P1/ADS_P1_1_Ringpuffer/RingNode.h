/*************************************************
* ADS Praktikum 1.1
* RingNode.h
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
#pragma once
#include <string>

class RingNode{
	
private:
	
	int m_oldAge;
	std::string m_description;
	std::string m_symbolicData;
	RingNode* m_next = nullptr;


	
public:
	
	RingNode();
	RingNode(int new_age, std::string new_dsc, std::string neu_data);
	int getOldAge();
	void setOldAge(int alt);
	std::string getDescription();
	void setDescription(std::string dsc);
	std::string getSymbolicData();
	void setSymbolicData(std::string neu);
	RingNode* getNext();
	void setNext(RingNode* nxt);

	
};
