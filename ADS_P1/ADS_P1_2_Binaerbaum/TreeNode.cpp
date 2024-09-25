/*************************************************
 * ADS Praktikum 1.2
 * TreeNode.cpp
 * Erweiterung um Hilfsfunktionen gestattet.
 *************************************************/

#include "TreeNode.h"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

////////////////////////////////////
// Ihr Code hier:
TreeNode::TreeNode() {
	this->m_left = nullptr;
	this->m_right = nullptr;
}

TreeNode::TreeNode(int NodeOrderID, int NodeChronologicalID, string Name, int Age, double Income, int PostCode) {
	this->m_NodeOrderID = NodeOrderID;
	this->m_NodeChronologicalID = NodeChronologicalID;
	this->m_Name = Name;
	this->m_Age = Age;
	this->m_Income = Income;
	this->m_PostCode = PostCode;
	this->m_left = nullptr;
	this->m_right = nullptr;
}

int TreeNode::getNodeOrderID() {
	return this->m_NodeOrderID;
}

int TreeNode::getNodeChronologicalID() {
	return this->m_NodeChronologicalID;
}

string TreeNode::getName() {
	return this->m_Name;
}

void TreeNode::setName(string pName) {
	this->m_Name = pName;
}

int TreeNode::getAge() {
	return this->m_Age;
}

void TreeNode::setAge(int pAlter) {
	this->m_Age = pAlter;
}

double TreeNode::getIncome() {
	return this->m_Income;
}

void TreeNode::setIncome(double pEinkommen) {
	this->m_Income = pEinkommen;
}

int TreeNode::getPostCode() {
	return this->m_PostCode;
}

void TreeNode::setPostCode(int pPLZ) {
	this->m_PostCode = pPLZ;
}

TreeNode* TreeNode::getLeft() {
	return this->m_left;
}

TreeNode* TreeNode::getRight() {
	return this->m_right;
}

void TreeNode::setLeft(TreeNode* pLeft) {
	this->m_left = pLeft;
}

void TreeNode::setRight(TreeNode* pRight) {
	this->m_right = pRight;
}

void TreeNode::print() {
	cout << setfill(' ');
	cout << setw(3) << getNodeChronologicalID() << "|";
	cout << setw(19) << getName() << "|";
	cout << setw(5) << getAge() << "|";
	cout << setw(11) <<getIncome() << "|";
	cout << setw(9) <<getPostCode() << "|";
	cout << setw(11) << getNodeOrderID() << "|";
	cout << endl;
}
