/*************************************************
 * ADS Praktikum 1.2
 * Tree.h
 * Erweiterung um Hilfsattribute und -funktionen gestattet, wenn erforderlich.
 *************************************************/
#pragma once
#include <string>
#include "TreeNode.h"
#include "catch.h"

using namespace std;

class Tree {

private:
	///////////////////////////////////////
	// Ihr Code hier:	
	TreeNode* m_anker;
	int m_currentNodeChronologicalID;

	void printPreOrder(TreeNode* root) const {
        if (root != nullptr) {
            root->print();
            printPreOrder(root->getLeft());
            printPreOrder(root->getRight());
        }
    }

    void printPostOrder(TreeNode* root) const {
        if (root != nullptr) {
            printPostOrder(root->getLeft());
            printPostOrder(root->getRight());
            root->print();
        }
    }

    void printInOrder(TreeNode* root) const {
        if (root != nullptr) {
            printInOrder(root->getLeft());
            root->print();
            printInOrder(root->getRight());
        }
    }
	//
	////////////////////////////////////	

public:
	///////////////////////////////////////
	// Ihr Code hier:	
	Tree();
	~Tree();
	void deleteTree(TreeNode* node);

	void addNode(string Name, int Age, double Income, int PostCode);
	bool deleteNode(int NodeChronologicalID);

	//search functions
	bool searchNode(string Name);
	bool search_helper(TreeNode* ptr, std::string nm);

	void printAll() const;
	void levelOrder();
	void LOprint(TreeNode* ptr, int lvl,int ind);

	
	//
	
	////////////////////////////////////
	// friend-Funktionen sind fuer die Tests erforderlich und muessen unangetastet bleiben! 
	friend TreeNode * get_anker(Tree& TN);
};