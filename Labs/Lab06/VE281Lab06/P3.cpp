/*#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
using namespace std;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void inorder(TreeNode* root, TreeNode*& pre, TreeNode*& first, TreeNode*& second) {
	if (!root) return;
	inorder(root->left, pre, first, second);
	if (!pre) pre = root;
	else {
		if (pre->val > root->val) {
			if (!first) first = pre;
			second = root;
		}
		pre = root;
	}
	inorder(root->right, pre, first, second);
}

void recoverTree(TreeNode* root) {
	TreeNode* pre = NULL, * first = NULL, * second = NULL;
	int temp;
	inorder(root, pre, first, second);
	temp = first->val;
	first->val = second->val;
	second->val = temp;
}

int main() {
	TreeNode* root=new TreeNode(4);
	TreeNode* left = new TreeNode(2);
	TreeNode* right = new TreeNode(6);
	TreeNode* leftleft = new TreeNode(5);
	TreeNode* leftright = new TreeNode(3);
	TreeNode* rightleft = new TreeNode(1);
	TreeNode* rightright = new TreeNode(7);
	root->left = left;
	root->right = right;
	left->left = leftleft;
	left->right = leftright;
	right->left = rightleft;
	right->right = rightright;
	cout << root->left->left->val << root->left->val << root->left->right->val << root->val << root->right->left->val << root->right->val << root->right->right->val << endl;
	recoverTree(root);
	cout << root->left->left->val << root->left->val << root->left->right->val << root->val << root->right->left->val << root->right->val << root->right->right->val;
}*/