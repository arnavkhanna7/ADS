/*************************************************
 * ADS Praktikum 1.2
 * TreeNode.h
 * Erweiterung um Hilfsattribute und -funktionen gestattet, wenn erforderlich.
 *************************************************/

#pragma once
#include <string>

using namespace std;

class TreeNode {

private:
	///////////////////////////////////////
	// Ihr Code hier:	
	int m_NodeOrderID;
	int m_NodeChronologicalID;
	string m_Name;
	int m_Age;
	double m_Income;
	int m_PostCode;
	TreeNode* m_left;
	TreeNode* m_right;
	//
	////////////////////////////////////

public:
	///////////////////////////////////////
	// Ihr Code hier:
	TreeNode();
	TreeNode(int NodeOrderID, int NodeChronologicalID, string Name, int Age, double Income, int PostCode);

	//getter und setter fuer alle atttribute
	int getNodeOrderID();
	int getNodeChronologicalID();
	string getName();
	void setName(string pName);
	int getAge();
	void setAge(int pAlter);
	double getIncome();
	void setIncome(double pEinkommen);
	int getPostCode();
	void setPostCode(int pPLZ);
	TreeNode* getLeft();
	TreeNode* getRight();
	void setLeft(TreeNode* pLeft);
	void setRight(TreeNode* pRight);

	//print function
	void print();
	//
	////////////////////////////////////
};