#include <string>

using namespace std;

struct douNode {
	string left, right;
	douNode(string left, string right) {
		this->left = left;
		this->right = right;
	}
	bool operator< (const douNode& rhs) const {
		if (left != rhs.left)
			return left < rhs.left;
		return right < rhs.right;
	}
};

struct triNode {
	string left, current, right;
	triNode(string left, string current, string right) {
		this->left = left;
		this->current = current;
		this->right = right;
	}
	bool operator< (const triNode& rhs) const {
		if (left != rhs.left)
			return left < rhs.left;
		if (current != rhs.current)
			return current < rhs.current;
		return right < rhs.right;
	}
};