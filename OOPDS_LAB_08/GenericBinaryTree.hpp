#ifndef GENERIC_BINARY_TREE_HPP
#define GENERIC_BINARY_TREE_HPP

#include <iostream>
#include <list>
#include <algorithm>

#include "GenericTreeNode.hpp"

using namespace std;

template<typename E>
class BinaryTree
{
public:
	class Position {
	private:
		TreeNode<E>* pTN;
	public:
		Position(TreeNode<E>* _v = NULL) : pTN(_v) {} // default constructor
		void setpTN(TreeNode<E>* pV) { pTN = pV; }
		TreeNode<E>* getpTN() { return pTN; }
		E& operator*() { return pTN->getElement(); }
		Position& left() const { return Position(pTN->getpLeft()); }
		Position& right() const { return Position(pTN->getpRight()); }
		Position& parent() const { return Position(pTN->getpParent()); }
		void setLeft(Position& pos) { pTN->setpLeft(pos.pTN); }
		void setRight(Position& pos) { pTN->setpRight(pos.pTN); }
		void setParent(Position& pos) { pTN->setpParent(pos.pTN); }
		bool isNULL() { return (pTN == NULL); } // check if position is null
		bool isRoot() const { return (pTN->getpParent() == NULL); }
		bool isExternal() const { return ((pTN->getpLeft() == NULL) && (pTN->getpRight() == NULL)); }
	}; // end of class BinaryTree::Position
	typedef std::list<Position> PositionList; // list of positions
public:
	BinaryTree() : _root(NULL), n(0) { } // constructor
	int size() const { return n; }
	bool empty() const { return size == 0; }
	Position root() const { return Position(_root); }
	TreeNode<E>** getRootAddr() { return &_root; }
	void addRoot() { _root = new TreeNode<E>; n = 1; } // add root to empty tree
	Position& addElementInOrder(Position& pos, Position& parenPos, E* pE)
	{
		BinaryTree<E>::Position newPos, childPos, nullPos;
		TreeNode<E>* pTN;
		if (pos.isNULL())
		{
			pTN = new TreeNode<E>(pE);
			pos.setpTN(pTN);
			if (parenPos.isNULL()) { // if root node
				_root = pos.getpTN();
			}
			pos.setParent(parenPos);
			n++; // increment the number of elements
			newPos = BinaryTree::Position(pTN);
			return newPos;
		}
		else if (*pE < *pos) {
			childPos = pos.left();
			newPos = addElementInOrder(childPos, pos, pE);
			if (!newPos.isNULL())
				pos.setLeft(newPos);
			return nullPos; // only the leaf child is set correctly, while the intermediate node is skipped
		}
		else if (*pE > *pos)
		{
			childPos = pos.right();
			newPos = addElementInOrder(childPos, pos, pE);
			if (!newPos.isNULL())
				pos.setRight(newPos);
			return nullPos; // only the leaf child is set correctly, while the intermediate node is skipped
		}
		else
		{
			cout << "Duplicated element in addElementInOrder !!" << endl;
		}
	}
	TreeNode<E>* insertAndRebalance(TreeNode<E>** ppTN, E* pE)
	{
		TreeNode<E>* pTN;
		if (*ppTN == NULL) // attach a new tree node at the currently external node
		{
			pTN = new TreeNode<E>(pE);
			*ppTN = pTN;
			(*ppTN)->setpLeft(NULL);
			(*ppTN)->setpRight(NULL);
			n++;
		}
		else if ((*ppTN)->getElement() > *pE) {
			pTN = insertAndRebalance((*ppTN)->getppLeft(), pE);
			(*ppTN)->setpLeft(pTN);
			*ppTN = reBalance(ppTN);
		}
		else {
			pTN = insertAndRebalance((*ppTN)->getppRight(), pE);
			(*ppTN)->setpRight(pTN);
			*ppTN = reBalance(ppTN);
		}
		return *ppTN;
	}
	void printTreeInOrder(ostream& fout, Position p)
	{
		if (p.isNULL())
			return;
		printTreeInOrder(fout, p.left());
		cout << *p << " ";
		printTreeInOrder(fout, p.right());
	}
	void printTreeByLevel(ostream& fout, Position p, int level)
	{
		TreeNode<E>* pChild = NULL;
		Position childPos;
		if (!p.isNULL())
		{
			if (level == 0)
				cout << "\nRoot (data: ";
			cout << *p;
			cout << ")" << endl;
			childPos = p.left();
			for (int i = 0; i<level; i++)
				cout << " ";
			if (!childPos.isNULL()) {
				cout << "L (data: ";
				printTreeByLevel(fout, childPos, level + 1);
			}
			else {
				cout << "L (NULL)" << endl;
			}
			childPos = p.right();
			for (int i = 0; i<level; i++)
				cout << " ";
			if (!childPos.isNULL()) {
				cout << "R (data: ";
				printTreeByLevel(fout, childPos, level + 1);
			}
			else {
				cout << "R (NULL)" << endl;
			}
		}
	}
protected:
	TreeNode<E>* rotate_LL(TreeNode<E> *pParent)
	{
		TreeNode<E>* pChild;
		pChild = pParent->getpLeft();
		pParent->setpLeft(pChild->getpRight());
		pChild->setpRight(pParent);
		return pChild;
	}
	TreeNode<E>* rotate_RR(TreeNode<E> *pParent)
	{
		TreeNode<E>* pChild;
		pChild = pParent->getpRight();
		pParent->setpRight(pChild->getpLeft());
		pChild->setpLeft(pParent);
		return pChild;
	}
	TreeNode<E>* rotate_RL(TreeNode<E> *pParent)
	{
		TreeNode<E>* pChild;
		pChild = pParent->getpRight();
		pParent->setpRight(rotate_LL(pChild));
		return rotate_RR(pParent);
	}
	TreeNode<E>* rotate_LR(TreeNode<E> *pParent)
	{
		TreeNode<E>* pChild;
		pChild = pParent->getpLeft();
		pParent->setpLeft(rotate_RR(pChild));
		return rotate_LL(pParent);
	}
	int getHeight(TreeNode<E>* pTN)
	{
		int height = 0;
		if (pTN != NULL)
		{
			height = 1 + max(getHeight(pTN->getpLeft()), getHeight(pTN->getpRight()));
		}
		return height;
	}
	int getHeightDiff(TreeNode<E>* pTN)
	{
		int heightDiff = 0;
		if (pTN == NULL)
			return 0;
		heightDiff = getHeight(pTN->getpLeft()) - getHeight(pTN->getpRight());
		return heightDiff;
	}
	TreeNode<E>* reBalance(TreeNode<E>** ppTN)
	{
		int heightDiff = 0;
		heightDiff = getHeightDiff(*ppTN);
		if (heightDiff > 1) // left subtree is higher
		{
			if (getHeightDiff((*ppTN)->getpLeft()) > 0)
				*ppTN = rotate_LL(*ppTN);
			else
				*ppTN = rotate_LR(*ppTN);
		}
		else if (heightDiff < -1) // right subtree is higher
		{
			if (getHeightDiff((*ppTN)->getpRight()) < 0)
				*ppTN = rotate_RR(*ppTN);
			else
				*ppTN = rotate_RL(*ppTN);
		}
		return *ppTN;
	}
private:
	TreeNode<E>* _root; // pointer to the root
	int n; // number of tree nodes
};

#endif