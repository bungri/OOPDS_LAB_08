/** main.cpp */
#include <iostream>
#include <fstream>

#include "GenericBinaryTree.hpp"

using namespace std;
#define NUM_DATA 20
void main()
{
	ofstream fout;
	BinaryTree<int> *pInt_BT, *pInt_BT_Bal;
	TreeNode<int>* pRoot;
	//int data[NUM_DATA] = {4, 3, 7, 2, 0, 9, 8, 5, 1, 6};
	int data[NUM_DATA] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
	fout.open("Output.txt");
	if (fout.fail())
	{
		cout << "Fail to open Output.txt !!" << endl;
		exit(1);
	}
	pInt_BT = new BinaryTree<int>;
	BinaryTree<int>::Position intBTpos_root = pInt_BT->root();
	BinaryTree<int>::Position intBTpos_Null(NULL);
	for (int i = 0; i< NUM_DATA; i++)
	{
		fout << "\nAdding " << data[i] << " into BinaryTree without Rebalancing";
		pInt_BT->addElementInOrder(intBTpos_root, intBTpos_Null, &data[i]);
	}
	fout << endl;
	fout << "\nElements in BinaryTree, in order : " << endl;
	pInt_BT->printTreeInOrder(fout, intBTpos_root);
	fout << endl;
	fout << "\nPrint BinaryTree by Level : ";
	pInt_BT->printTreeByLevel(fout, intBTpos_root, 0);
	fout << endl;
	pInt_BT_Bal = new BinaryTree<int>;
	BinaryTree<int>::Position intBTBal_pos_root = pInt_BT_Bal->root();
	BinaryTree<int>::Position intBTBal_pos_Null(NULL);
	for (int i = 0; i< NUM_DATA; i++)
	{
		fout << "\nAdding " << data[i] << " into BinaryTree with Rebalancing";
		pRoot = pInt_BT_Bal->insertAndRebalance(pInt_BT_Bal->getRootAddr(), &data[i]);
		pInt_BT_Bal->printTreeByLevel(fout, BinaryTree<int>::Position(pRoot), 0);
		fout << endl;
	}
	fout << endl;
	fout << "\nElements in BinaryTree, in order : " << endl;
	pInt_BT_Bal->printTreeInOrder(fout, BinaryTree<int>::Position(pRoot));
	fout << endl;
	delete pInt_BT_Bal;
	fout.close();
}