#ifndef GENERIC_TREE_NODE_HPP
#define GENERIC_TREE_NODE_HPP

template<typename E>
class TreeNode { // a node of the tree
public:
	TreeNode() : pE(NULL), pParent(NULL), pLeft(NULL), pRight(NULL) { } // default constructor
	TreeNode(E* pElem) : pE(pElem), pParent(NULL), pLeft(NULL), pRight(NULL) { } // constructor
	E& getElement() const { return *pE; }
	E* getpE() const { return pE; }
	void setpE(const E* pElem) { pE = pElem; }
	TreeNode* getpParent() { return pParent; }
	TreeNode* getpLeft() { return pLeft; }
	TreeNode* getpRight() { return pRight; }
	TreeNode** getppParent() { return &pParent; }
	TreeNode** getppLeft() { return &pLeft; }
	TreeNode** getppRight() { return &pRight; }
	void setpParent(TreeNode* pTN) { pParent = pTN; }
	void setpLeft(TreeNode* pTN) { pLeft = pTN; }
	void setpRight(TreeNode* pTN) { pRight = pTN; }
private:
	E* pE; // element value
	TreeNode* pParent; // parent
	TreeNode* pLeft; // left child
	TreeNode* pRight; // right child
};

#endif