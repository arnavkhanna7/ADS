
/*************************************************
 * ADS Praktikum 1.2
 * Tree.cpp
 * Erweiterung um Hilfsfunktionen gestattet.
 *************************************************/
#include "Tree.h"
#include "TreeNode.h"
#include <iomanip>
#include <iostream>

using namespace std;

////////////////////////////////////
// Ihr Code hier:

Tree::Tree()
{
    this->m_currentNodeChronologicalID = 0;
}

Tree::~Tree() {}


bool Tree::searchNode(string Name)
{
    std::cout << "+Fundstellen:" << std::endl;
    TreeNode* k = m_anker;
    bool found = false;
    searchNodeHelper(k, Name, found);
    return found;
}

void Tree::searchNodeHelper(TreeNode* k, string Name, bool& found)
{
    if (k != nullptr) //Solange weiter machen bis der gesamte Baum durchgangen wurde, nicht abbrechen wenn etwas gefunden wurde
    {
        if (k->getName() == Name)
        {
            found = true;
            std::cout << "NodeID: " << k->getNodeChronologicalID() << ", "
                << "Name: " << k->getName() << ", "
                << "Alter: " << k->getAge() << ", "
                << "Einkommen: " << k->getIncome() << ", "
                << "PLZ: " << k->getPostCode() << ", "
                << "PosID: " << k->getPostCode() << std::endl;
        }
        searchNodeHelper(k->getRight(), Name, found);
        searchNodeHelper(k->getLeft(), Name, found);
    }
}
//Ausgabe in Tabellenform:
void Tree::printAll()
{
    //Tabletop:
    std::cout << std::setw(4) << "ID"
        << "|"
        << std::setw(18) << "Name"
        << "|"
        << std::setw(7) << "Age"
        << "|"
        << std::setw(11) << "Income"
        << "|"
        << std::setw(10) << "PostCode"
        << "|"
        << std::setw(8) << "Pos"
        << "|"
        << std::setw(8) << "Red" << std::endl;

    std::cout << std::setfill('-') << std::setw(5) << "+"
        << std::setw(19) << "+"
        << std::setw(8) << "+"
        << std::setw(12) << "+"
        << std::setw(11) << "+"
        << std::setw(9) << "+"
        << std::setw(9) << "+" << std::setfill(' ') << std::endl;

    std::queue<TreeNode*> blackNodes;
    std::queue<int> levelBlackNodes;
    int currentLevel = -1;
    TreeNode* tmp = m_anker;

    if (tmp == nullptr) {
        cout << "Leere Liste." << endl;
        return;
    }
    blackNodes.push(tmp);    //aufruf mit anker

    while (!blackNodes.empty()) {
        tmp = blackNodes.front();
        blackNodes.pop();
        printHelper(tmp);;
        //leftChild rot? => gucken ob es schwarzen Nachfolger hat
        if (tmp->getLeft() != nullptr) {
            if (tmp->getLeft()->getRed()) {
                printHelper(tmp->getLeft());
                //Nachfolger von rot müssen schwarz sein
                if (tmp->getLeft()->getLeft() != nullptr) {
                    blackNodes.push(tmp->getLeft()->getLeft());
                }
                if (tmp->getLeft()->getRight() != nullptr) {
                    blackNodes.push(tmp->getLeft()->getRight());
                }
            }
            //leftChild black => push
            else {
                blackNodes.push(tmp->getLeft());
            }
        }
        //rightChild rot? => gucken ob es schwarzen Nachfolger hat
        if (tmp->getRight() != nullptr) {
            //Nachfolger von rot müssen schwarz sein
            if (tmp->getRight()->getRed()) {
                printHelper(tmp->getRight());
                if (tmp->getRight()->getLeft() != nullptr) {
                    blackNodes.push(tmp->getRight()->getLeft());
                }
                if (tmp->getRight()->getRight() != nullptr) {
                    blackNodes.push(tmp->getRight()->getRight());
                }
            }
            //rightChild black => push
            else {
                blackNodes.push(tmp->getRight());
            }
        }
    }
}

void Tree::printHelper(TreeNode* k)
{
    std::cout << std::setw(4) << k->getNodeChronologicalID() << "|"
        << std::setw(18) << k->getName() << "|"
        << std::setw(7) << k->getAge() << "|"
        << std::setw(11) << k->getIncome() << "|"
        << std::setw(10) << k->getPostCode() << "|"
        << std::setw(8) << k->getNodeOrderID() << "|"
        << std::setw(8) << int(k->getRed()) << std::endl;
}
//p3:

//Ausgabe alle Levels:
void Tree::printLevelOrder() {
    std::queue<TreeNode*> blackNodes;
    std::queue<int> levelBlackNodes;
    int prevLevel = -1; //Damit auch am Anfang (preLevel != level )
    int level = 0;
    bool requestedLevel = false;
    TreeNode* tmp = m_anker;
    if (tmp == nullptr) {
        std::cout << "Der Baum ist leer." << std::endl;
        return;
    }
    //push(anker)
    blackNodes.push(tmp);
    levelBlackNodes.push(0);

    //
    while (!blackNodes.empty()) {
        tmp = blackNodes.front();
        blackNodes.pop();

        level = levelBlackNodes.front();
        levelBlackNodes.pop();

        if (prevLevel != level)    //Levelwechsel?
        {
            std::cout << std::endl << "Level " << level << ": ";
        }
        prevLevel = level;

        std::cout << "(";
        //leftChild
        if (tmp->getLeft() != nullptr)
        {
            if (tmp->getLeft()->getRed())
            {
                //leftChild == red => print
                std::cout << tmp->getLeft()->getNodeOrderID() << ",";
                //Nachfolger müssen schwarz sein -> push & und level erhöhen
                if (tmp->getLeft()->getLeft() != nullptr)
                {
                    blackNodes.push(tmp->getLeft()->getLeft());
                    levelBlackNodes.push(level + 1);
                }
                if (tmp->getLeft()->getRight() != nullptr)
                {
                    blackNodes.push(tmp->getLeft()->getRight());
                    levelBlackNodes.push(level + 1);
                }
            }
            else //leftChild == black->push
            {
                blackNodes.push(tmp->getLeft());
                levelBlackNodes.push(level + 1);
            }
        }
        //tmp == black
        std::cout << tmp->getNodeOrderID();
        //rightChild
        if (tmp->getRight() != nullptr)
        {
            if (tmp->getRight()->getRed())
            {
                //rightChild == red => print
                std::cout << "," << tmp->getRight()->getNodeOrderID();
                //Nachfolger müssen schwarz sein -> push und level erhöhen
                if (tmp->getRight()->getLeft() != nullptr) {
                    blackNodes.push(tmp->getRight()->getLeft());
                    levelBlackNodes.push(level + 1);
                }
                if (tmp->getRight()->getRight() != nullptr) {
                    blackNodes.push(tmp->getRight()->getRight());
                    levelBlackNodes.push(level + 1);
                }
            }
            else { //rightChild == black -> push
                blackNodes.push(tmp->getRight());
                levelBlackNodes.push(level + 1);
            }
        }
        std::cout << ") ";
    }
}

void Tree::printLevelOrder(int levelToPrint) {
    std::queue<TreeNode*> blackNodes;
    std::queue<int> levelBlackNodes;
    int currentLevel = -1;
    int level = 0;
    bool requestedLevel = false; //boolean für gesuchtes Element?
    TreeNode* tmp = m_anker;
    if (tmp == nullptr) {
        std::cout << "Der Baum ist leer." << std::endl;
        return;
    }
    blackNodes.push(tmp);
    levelBlackNodes.push(0);

    while (!blackNodes.empty()) {
        tmp = blackNodes.front();
        blackNodes.pop();

        level = levelBlackNodes.front();
        levelBlackNodes.pop();

        if (level == levelToPrint) {
            requestedLevel = true;
        }
        else if (level > requestedLevel)
        {
            cout << "+Level konnte nicht gefunden werden. Gesuchtes Level ueberschreitet maximales Level des Rot-Schwarzbaums." << endl;
            return;
        }
        if (level != currentLevel) {
            if (requestedLevel) {
                std::cout << std::endl << "Level " << level << ": ";
            }
            currentLevel = level;
        }
        if (requestedLevel) {
            std::cout << "(";
        }
        if (tmp->getLeft() != nullptr) {
            if (tmp->getLeft()->getRed()) {
                if (requestedLevel) {
                    std::cout << tmp->getLeft()->getNodeOrderID() << ",";
                }
                if (tmp->getLeft()->getLeft() != nullptr) {
                    blackNodes.push(tmp->getLeft()->getLeft());
                    levelBlackNodes.push(level + 1);
                }
                if (tmp->getLeft()->getRight() != nullptr) {
                    blackNodes.push(tmp->getLeft()->getRight());
                    levelBlackNodes.push(level + 1);
                }
            }
            else {
                blackNodes.push(tmp->getLeft());
                levelBlackNodes.push(level + 1);
            }
        }
        if (requestedLevel) {
            std::cout << tmp->getNodeOrderID();
        }
        if (tmp->getRight() != nullptr) {
            if (tmp->getRight()->getRed()) {
                if (requestedLevel) {
                    std::cout << "," << tmp->getRight()->getNodeOrderID();
                }
                if (tmp->getRight()->getLeft() != nullptr) {
                    blackNodes.push(tmp->getRight()->getLeft());
                    levelBlackNodes.push(level + 1);
                }
                if (tmp->getRight()->getRight() != nullptr) {
                    blackNodes.push(tmp->getRight()->getRight());
                    levelBlackNodes.push(level + 1);
                }
            }
            else {
                blackNodes.push(tmp->getRight());
                levelBlackNodes.push(level + 1);
            }
        }
        if (requestedLevel) {
            std::cout << ") ";
        }
        requestedLevel = false;
    }

}


bool Tree::addNode(string Name, int Age, double Income, int PostCode)
{
    int NodeOrderID = Age + PostCode + Income;
    TreeNode* newEle = new TreeNode(NodeOrderID, m_currentNodeChronologicalID, Name, Age, Income, PostCode);
    this->m_currentNodeChronologicalID++;

    newEle->setRed(true);  // new nodes are leaf nodes and always red 

    if (this->m_anker == nullptr) //if tree is empty directy add new node 
    {
        this->m_anker = newEle;
        m_anker->setLeft(nullptr);
        m_anker->setRight(nullptr);
        m_anker->setParent(nullptr);
        newEle->setRed(false); //Root node is always black
        return true;
    }

    //Suchen mit Suchpfad tracking(queue)
    TreeNode* tmp = m_anker;
    TreeNode* prev = nullptr; //Verweis auf den Node davor so dass man die Pointer richtig legen kann
    while (tmp != nullptr)
    {
        prev = tmp;

        if (tmp->getRed() == false && (tmp->getLeft() != nullptr && tmp->getRight() != nullptr)) //Check whether it is a 4er Node and split it
        {
            split4Node(tmp);
        }

        if (NodeOrderID < tmp->getNodeOrderID()) //depending on wether nodeOrderID bigger or smaller , tmp(ptr) needs to go left or right
        {
            tmp = tmp->getLeft();
        }
        else if (NodeOrderID > tmp->getNodeOrderID())
        {
            tmp = tmp->getRight();
        }
    }
    //Einfuegen:
    if (prev->getNodeOrderID() > NodeOrderID)
    {
        prev->setLeft(newEle);
    }
    else if (prev->getNodeOrderID() <= NodeOrderID)
    {
        prev->setRight(newEle);
    }

    newEle->setParent(prev);

    //Traverse the tree Bottom Up and search for 2 simultaneous red nodes 

    TreeNode* ptr = newEle;
    while (ptr != nullptr && ptr->getParent() != nullptr)
    {
        if (ptr->getRed() && ptr->getParent()->getRed())
        {
            balance(ptr);
        }
        if (ptr->getParent() == nullptr) {
            break;
        }
        ptr = ptr->getParent();
    }
    return true;
}


void Tree::balance(TreeNode* p_lowest)
{
    //links->links
    TreeNode* pp = p_lowest->getParent()->getParent();
    if (pp->getLeft() != nullptr && pp->getLeft()->getLeft() != nullptr) {
        if (pp->getLeft()->getRed() == true && pp->getLeft()->getLeft()->getRed() == true) //
        {
            rotateTreeRight(p_lowest->getParent());
            if (!pp->getRed()) {
                pp->setRed(true);
                p_lowest->getParent()->setRed(false);
            }
        }
    }

    // links->rechts
    if (pp->getLeft() != nullptr && pp->getLeft()->getRight() != nullptr) {
        if (pp->getLeft()->getRed() == true && pp->getLeft()->getRight()->getRed() == true)
        {
            rotateTreeLeft(p_lowest);
            rotateTreeRight(p_lowest);
            if (!pp->getRed()) {
                pp->setRed(true);
                p_lowest->setRed(false);
            }
        }
    }

    //rechts->links
    if (pp->getRight() != nullptr && pp->getRight()->getLeft() != nullptr) {
        if (pp->getRight()->getRed() == true && pp->getRight()->getLeft()->getRed() == true)
        {
            rotateTreeRight(p_lowest);
            rotateTreeLeft(p_lowest);
            if (!pp->getRed()) {
                pp->setRed(true);
                p_lowest->setRed(false);
            }
        }
    }

    //rechts->rechts
    if (pp->getRight() != nullptr && pp->getRight()->getRight() != nullptr) {
        if (pp->getRight()->getRed() == true && pp->getRight()->getRight()->getRed() == true)
        {
            rotateTreeLeft(p_lowest->getParent());
            if (!pp->getRed()) {
                pp->setRed(true);
                p_lowest->getParent()->setRed(false);
            }
        }
    }

}
bool Tree::split4Node(TreeNode* parent)
{
    if (parent->getLeft()->getRed() == true && parent->getRight()->getRed() == true) //4er Knoten erkannt
    {
        //Umfärben: parent == rot, children == schwarz
        if (parent != m_anker)
        {
            parent->setRed(true);
        }
        parent->getLeft()->setRed(false);
        parent->getRight()->setRed(false);
        return true;
    }
    return false;
}

bool Tree::rotateTreeRight(TreeNode* p2)
{
    //Es wird immer der unterste rote Knoten übergeben (p2)
    TreeNode* p1 = p2->getParent(); 
    TreeNode* pp = p1->getParent(); 

    if (p1 == m_anker) {
        p1->setLeft(p2->getRight());
        if (p2->getRight() != nullptr) {
            p2->getRight()->setParent(p1);
        }
        p2->setRight(p1);
        p2->setParent(p1->getParent());
        p1->setParent(p2);
        m_anker = p2;
        return true;
    }
    

    if (pp->getNodeOrderID() > p2->getNodeOrderID()) {
        pp->setLeft(p2);
    }
    else {
        pp->setRight(p2);
    }
    if (p2->getRight() != nullptr) {
        p2->getRight()->setParent(p1);
    }

    p1->setLeft(p2->getRight());
    p1->setParent(p2);
    p2->setParent(pp);
    p2->setRight(p1);

    cout << "RR(" << p2->getNodeOrderID() << "," << p1->getNodeOrderID() << ")\n";

    return true;
}
bool Tree::rotateTreeLeft(TreeNode* p2)
{
    //Es wird immer der unterste rote Knoten übergeben (p2)
    TreeNode* p1 = p2->getParent();
    TreeNode* pp = p1->getParent();

    if (p1 == m_anker) {
        p1->setRight(p2->getLeft());
        if (p2->getLeft() != nullptr) {
            p2->getLeft()->setParent(p1);
        }
        p2->setLeft(p1);
        p2->setParent(p1->getParent());
        p1->setParent(p2);
        m_anker = p2;
        return true;
    }

    if (pp->getNodeOrderID() > p2->getNodeOrderID()) {
        pp->setLeft(p2);
    }
    else {
        pp->setRight(p2);
    }
    if (p2->getLeft() != nullptr) {
        p2->getLeft()->setParent(p1);
    }
    p1->setRight(p2->getLeft());
    p1->setParent(p2);
    p2->setParent(pp);
    p2->setLeft(p1);

    cout << "LR(" << p2->getNodeOrderID() << "," << p1->getNodeOrderID() << ")\n";
    return true;
}


int Tree::proofRBCriterion(TreeNode* start)
{
    int height = this->proofRBCriterionRec(start);
    return height;
}

int Tree::proofRBCriterionRec(TreeNode* node) {

    if (node != nullptr) {
        int heightLeft = proofRBCriterionRec(node->getLeft());
        int heightRight = proofRBCriterionRec(node->getRight());


        // Blattknoten
        if (node->getLeft() == nullptr && node->getRight() == nullptr) {
            return 0;
        }

        //1 Nachfolger (rot oder schwarz)
        if ((node->getLeft() == nullptr) || (node->getRight() == nullptr)) {
            if (node->getLeft() == nullptr) {
                if (node->getRight()->getRed()) {
                    return heightRight;
                }
                else {
                    return heightRight + 1;
                }
            }
            if (node->getRight() == nullptr) {
                if (node->getLeft()->getRed()) {
                    return heightLeft;
                }
                else {
                    return heightLeft + 1;
                }
            }
        }

        //both children are red
        if (node->getLeft()->getRed() && node->getRight()->getRed()) {
            if (heightLeft == heightRight) {
                return heightLeft;
            }
        }

        //1 child is black && 1 child is red
        if ((node->getLeft()->getRed() && !node->getRight()->getRed()) || (node->getRight()->getRed() && !node->getLeft()->getRed())) {
            int redChildHeight = node->getLeft()->getRed() ? heightLeft : heightRight;
            int blackChildHeight = !node->getLeft()->getRed() ? heightLeft : heightRight;

            if ((redChildHeight + 1) == blackChildHeight) {
                return redChildHeight;
            }
        }

        //both children are black
        if (!node->getLeft()->getRed() && !node->getRight()->getRed()) {
            if (heightLeft == heightRight) {
                return heightLeft + 1;          //increase height due to black node
            }
        }

        return -1; //wenn Fehler auftritt
    }

    return 0; //Fall wenn der Node == nullptr;
}

//
////////////////////////////////////
