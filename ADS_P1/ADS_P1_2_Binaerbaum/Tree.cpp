/*************************************************
 * ADS Praktikum 1.2
 * Tree.cpp
 * Erweiterung um Hilfsfunktionen gestattet.
 *************************************************/
#include "Tree.h"
#include "TreeNode.h"
#include <iostream>
#include <iomanip>
#include <queue>
#include <stack>


using namespace std;

////////////////////////////////////
// Ihr Code hier:
Tree::Tree() {
	this->m_anker = nullptr;
	this->m_currentNodeChronologicalID = 0;
}


Tree::~Tree(){
	deleteTree(m_anker);
}

void Tree::deleteTree(TreeNode* node){
	if(node != nullptr){
		deleteTree(node->getLeft());
		deleteTree(node->getRight());
		delete node;
	}
}

void Tree::addNode(string N, int age, double income, int PLZ){
	TreeNode* new_node = new TreeNode(age+income+PLZ, m_currentNodeChronologicalID, N, age, income, PLZ);

	if(m_anker==0){							//if the tree is empty
		m_anker = new_node;
		m_currentNodeChronologicalID++;
	}
	else{									//if tree is not empty
		m_currentNodeChronologicalID++;		//increasing chronologicalID
		TreeNode* ptr = m_anker;			//make pointers for anker and parent node
		TreeNode* prnt = nullptr;

		do{
			prnt = ptr;
			if(new_node->getNodeOrderID() >= ptr->getNodeOrderID()){
				ptr = ptr->getRight();			//search for position where node has to be added 
			}
			else{
				ptr=ptr->getLeft(); 
			}
		}while(ptr!= 0);

		//compare values of current parent node and new node 
		if(new_node->getNodeOrderID() < prnt->getNodeOrderID()){
			prnt->setLeft(new_node);			//set new child node of parent accordingly
		}else{
			prnt->setRight(new_node);
		}

		}

}
// Method to delete a node from the tree based on NodeOrderID
bool Tree::deleteNode(int NodeOrderID) {
    TreeNode* current = m_anker;
    TreeNode* parent = nullptr;

    bool isLeftChild = false;				//check if current is a left child or right child

    // Search for the node to be deleted
    while (current != nullptr && current->getNodeOrderID() != NodeOrderID) {
        parent = current;
        if (NodeOrderID < current->getNodeOrderID()) {
            current = current->getLeft();
            isLeftChild = true;
        } else {
            current = current->getRight();
            isLeftChild = false;
        }
    }

    // Node not found
    if (current == nullptr) {
        std::cout << "Node with NodeOrderID " << NodeOrderID << " not found." << std::endl;
        return false;
    }

    // Case 1: Node to be deleted has no children (leaf node)
    if (current->getLeft() == nullptr && current->getRight() == nullptr) {
        if (current == m_anker) {
            m_anker = nullptr; 					// Tree becomes empty
        } else {
            if (isLeftChild) {
                parent->setLeft(nullptr);			//set child node pointer of parent to nullptr 
            } else {
                parent->setRight(nullptr);
            }
        }
        delete current;							//delete the node with current ptr 
    }
    // Case 2: Node to be deleted has one child
    else if (current->getRight() == nullptr) {			//check wether child node of current is on the left
        if (current == m_anker) {						//if root node then make the left child the new root of tree
            m_anker = current->getLeft();				
        } else if (isLeftChild) {						//if current is left child then set new left child of parent
            parent->setLeft(current->getLeft());		//to the left child of current node 
        } else {
            parent->setRight(current->getLeft());		//else set right child of parent to left of current
        }
        delete current;
    } else if (current->getLeft() == nullptr) {			
        if (current == m_anker) {
            m_anker = current->getRight();
        } else if (isLeftChild) {
            parent->setLeft(current->getRight());
        } else {
            parent->setRight(current->getRight());
        }
        delete current;
    }
    // Case 3: Node to be deleted has two children
    else {
        TreeNode* successor = current->getRight();		//introduce succesor ptr and succesor parent to replace the deleted node 
        TreeNode* successorParent = current;			//succesor is current->getright to replace with min. of right subtree
        
		while (successor->getLeft() != nullptr) {		
            successorParent = successor;				//find the min. in right subtree
            successor = successor->getLeft();
        }

        if (current == m_anker) {					
            m_anker = successor;
        } else if (isLeftChild) {
            parent->setLeft(successor);					//if current node is leftchild set left of parent node
        } else {
            parent->setRight(successor);				//if current node is right child set the right of parent node 
        }

        successor->setLeft(current->getLeft());			//set left subtree of current as left subtree of successor


        if (successor != current->getRight()) {
            successorParent->setLeft(successor->getRight());		//if succesor is left child somehow then put right subtree of current as 
            successor->setRight(current->getRight());				//right subtree of successor
        }
        delete current;
    }
    return true;
}



bool Tree::searchNode(string Nm){
	cout << "+ fundstellen: \n";
	if(search_helper(m_anker,Nm)){		//if head is the required node return true
		return 1;
	}
	else{
		cout << "Koennte nicht gefunden werden. \n";
	}

	return 0;
}

bool Tree::search_helper(TreeNode* head,std::string nm) {
	if (head == 0)						//if tree is empty return false
		return 0;
	if (head->getName() == nm){
		head->print();
		return true;					//if node is found print it and return true
	}
	return search_helper(head->getLeft(), nm) || search_helper(head->getRight(), nm);  //return true for either left or right subtree

}



void Tree::printAll() const {
	string order;
	std::cout << "Ausgabereihenfolge ?>";
	cin>>order;

	cout << left << setw(3) << " ID";
	cout << left << setw(20) << "| Name";
	cout << left << setw(6) << "| Age";
	cout << left << setw(12) << "| Income";
	cout << left << setw(10) << "| PostCode";
	cout << left << setw(12) << "| OrderID";
	cout << endl;

	

	cout <<right << setfill('-');
	cout << setw(4) << "+";
	cout << setw(20) << "+";
	cout << setw(6) << "+";
	cout << setw(12) << "+";
	cout << setw(10) << "+";
	cout << setw(12) << "+";
	cout << endl;

	if (order == "pre") {
    	std::cout << "Preorder traversal:" << std::endl;
        printPreOrder(m_anker);
    } else if (order == "post") {
        std::cout << "Postorder traversal:" << std::endl;
        printPostOrder(m_anker);
    } else if (order == "in") {
        std::cout << "Inorder traversal:" << std::endl;
        printInOrder(m_anker);
    } else {
    	std::cerr << "Invalid traversal order specified!" << std::endl;
    }
        std::cout << std::endl;
}
	

void Tree::levelOrder() {
	int maxtief = 10;
	cout << left << setw(4) << " ID";
	cout << left << setw(19) << "| Name";
	cout << left << setw(8) << "| Age";
	cout << left << setw(12) << "| Income";
	cout << left << setw(11) << "| PostCode";
	cout << left << setw(7) << "| OrderID";
	cout << left << setw(6) << "| Level\n";

	cout <<right << setfill('-');
	cout << setw(5) << "+";
	cout << setw(19) << "+";
	cout << setw(8) << "+";
	cout << setw(12) << "+";
	cout << setw(11) << "+";
	cout << setw(9) << "+";
	cout << setw(6) <<"-"<< endl;

	for (int i = 0; i <= maxtief; i++) {
		LOprint(m_anker, i, i);
	}
}

void Tree::LOprint(TreeNode* ptr,int lvl, int ind) {
	if (ptr == 0) {
		cout << "Leerer Baum." << endl;
		return;
	}
	else {
		if (ind == 0) {
			cout << setfill(' ');
			cout << setw(4) << ptr->getNodeChronologicalID() << "|";
			cout << setw(18) << ptr->getName() << "|";
			cout << setw(7) << ptr->getAge() << "|";
			cout << setw(11) << ptr->getIncome() << "|";
			cout << setw(10) << ptr->getPostCode() << "|";
			cout << setw(8) << ptr->getNodeOrderID() << "|";
			cout << setw(5) << lvl << endl;
		}
		else if (ind > 0) {
			if (ptr->getLeft() != 0)
				LOprint(ptr->getLeft(), lvl, ind - 1);
			if (ptr->getRight() != 0)
				LOprint(ptr->getRight(), lvl, ind - 1);
		}
	}
}



