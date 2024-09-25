/*************************************************
* ADS Praktikum 1.1
* RingNode.cpp
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
#include "RingNode.h"

////////////////////////////////////
// Ihr Code hier:
RingNode::RingNode() {
	m_oldAge = 0;
	m_description = "";
	m_symbolicData = "";
    m_next = nullptr;
}
RingNode::RingNode(int new_age, std::string new_desc, std::string new_data) {
	m_oldAge = new_age;
	m_description = new_desc;
	m_symbolicData = new_data;
    m_next = nullptr;
}
int RingNode::getOldAge() {
	return m_oldAge;
}
void RingNode::setOldAge(int alt) {
	m_oldAge = alt;
}
std::string RingNode::getDescription() {
	return m_description;
}
void RingNode::setDescription(std::string new_desc) {
	m_description = new_desc;
}
std::string RingNode::getSymbolicData() {
	return m_symbolicData;
}
void RingNode::setSymbolicData(std::string new_data) {
	m_symbolicData = new_data;
}
RingNode* RingNode::getNext() {
	return m_next;
}
void RingNode::setNext(RingNode* nxt) {
	if (nxt != nullptr)
		m_next = nxt;                              
}

// 
////////////////////////////////////