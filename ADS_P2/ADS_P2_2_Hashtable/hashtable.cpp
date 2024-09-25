#include "hashtable.h"
#include <iostream>

using namespace std;

HashTable::HashTable(int size, double threshold, int methode) 
{
	collisionCount = 0;
	m_sondierMethode = methode;
	elements = 0;
	hashTable = new vector<int>;
	hashTable->resize(size, -1);
	this->size = size;
	this->threshold_rehashing = threshold;
}

HashTable::~HashTable()
{
	delete hashTable;
}

int get_next_prime(int x)
{
	x = x + 1;
	bool found = true;
	while (true)
	{
		found = true;
		for (int i = 2; i <= sqrt(x); i++)
		{
			if (x % i == 0)
			{
				found = false;
				break;
			}
		}
		if (found)
		{
			return x;
		}
		x += 1;
	}
}

int get_last_prime(int x)
{
	x = x - 1;
	bool found = true;
	while (true)
	{
		found = true;
		for (int i = 2; i <= sqrt(x); i++)
		{
			if (x % i == 0)
			{
				found = false;
				break;
			}
		}
		if (found)
		{
			return x;
		}
		x -= 1;
	}
}

// Berechnung des Hashwertes
int HashTable::hashValue(int item) 
{	
	int index = 0;
	int i = 0;

	switch (m_sondierMethode)
	{
	case (1):
		// Lineares Sondieren
		while(hashTable->at((item + i ) % size) != -1){
			i++;
			collisionCount++;
		}
		index = (item+i) % size;
		break;
	case (2):
		// Quadr. Sondieren
		
		while(hashTable->at((item + i*i)%size) != -1){
			i++;
			collisionCount++;
		}
		index = (item + i*i)%size;
		break;
	case (3):
		{
		// Doppeltes Hashing
		int R = get_last_prime(size);
		while(hashTable->at((item + i*(R - (item % R))) % size) != -1){
			i++;
			collisionCount++;

		}
		index = (item + i*(R - (item % R))) % size;
		break;
		}
	default:
		break;
	}
	return index;
}
	

void HashTable::rehashing()
{
	int M_new = get_next_prime(2*size), oldsize = size;
	size = M_new;
	collisionCount=0;
	elements=0;
	vector<int> tmp(oldsize,-1);
	for(int i=0; i<oldsize; i++){
		tmp.at(i) = hashTable->at(i);
	}
	delete hashTable;

	hashTable = new vector<int>;
	hashTable->resize(M_new,-1);

	for(int i=0; i<oldsize; i++){
		if(tmp.at(i) != -1){
			insert(tmp.at(i));
		}
	}
}

int HashTable::insert(int item) 
{
	if(double(elements+1)/double(size) >= threshold_rehashing){
		rehashing();
	}


	hashTable->at(hashValue(item)) = item;
	elements++;

	
	return 0;
}


int HashTable::at(int i) 
{
	return hashTable->at(i);
}

int HashTable::getCollisionCount() 
{
	return this->collisionCount;
}

int HashTable::getSize() 
{
	return this->size;
}

int HashTable::getElements() 
{
	return this->elements;
}



