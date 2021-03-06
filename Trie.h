#pragma once
#include <iostream>
#include <string>
#include "TrieNode.h"
using namespace std;

class Trie {
private:
	TrieNode* root;
public:
	Trie() { this->setRoot(new TrieNode); };
	~Trie() { delete this; }
	void setRoot(TrieNode* newRoot) { root = newRoot; }
	TrieNode* getRoot() { return this->root; }
	void insert(string newWord);
	bool searchWord(string s);
	bool searchWord2(string s);
	bool setDef(string word, string definition, string type);
};

bool Trie::setDef(string word, string definition, string type)
{
	TrieNode* rover = root;

	while (rover != NULL)
	{
		for (size_t i = 0; i < word.length(); i++)
		{
			TrieNode* temp = rover->findChild(word[i]);
			if (temp == NULL)
				return false;
			rover = temp;
		}

		if (rover->wordMarker())
		{
			rover->setDef(definition);
			rover->setType(type);
			return true;
		}
		else
			return false;
	}
	return false;
}

void Trie::insert(string newWord)
{
	TrieNode* rover = getRoot();

	if (newWord.length() == 0)
	{
		rover->setWordMarker();
		return;
	}

	for (size_t i = 0; i < newWord.length(); i++)
	{
		TrieNode* child = rover->findChild(newWord[i]);
		if (child != NULL)
		{
			rover = child;
		}
		else
		{
			TrieNode* temp = new TrieNode();
			temp->setChar(newWord[i]);
			rover->appendChild(temp);
			rover = temp;
		}
		if (i == newWord.length() - 1)
		{
			rover->incOccurrences();
			rover->setWordMarker();
		}
	}
}


bool Trie::searchWord2(string search)
{
	TrieNode* rover = root;

	while (rover != NULL)
	{
		for (size_t i = 0; i < search.length(); i++)
		{
			TrieNode* temp = rover->findChild(search[i]);
			if (temp == NULL)
				return false;
			rover = temp;
		}

		if (rover->wordMarker())
		{
			return true;
		}
		else
			return false;
	}
	return false;
}

bool Trie::searchWord(string s)
{
	TrieNode* rover = root;

	while (rover != NULL)
	{
		for (size_t i = 0; i < s.length(); i++)
		{
			TrieNode* temp = rover->findChild(s[i]);
			if (temp == NULL)
				return false;
			rover = temp;
		}

		if (rover->wordMarker())
		{
			std::cout << "\n~\tWord Found!" << std::endl;
			std::cout << "~\tOccurrences: " << rover->getOccurrences() << std::endl;
			cout << "~\t" << s;
			if (rover->defExists() && rover->getTypeExist())
			{
				cout << " (" << rover->getType() << ".): " << rover->getDef() << ".";
			}
			else if (rover->defExists())
			{
				cout << ": " << rover->getDef() << "." << endl;
			}
			cout << "\n~\t";
			for (size_t i = 0; i < s.length(); i++)
				cout << "^";
			return true;
		}
		else
			return false;
	}

	return false;
}