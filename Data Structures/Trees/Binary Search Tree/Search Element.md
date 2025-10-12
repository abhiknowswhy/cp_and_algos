## Searching for an Element in a Binary Search Tree (BST)

### Algorithm

1. Start at the root node.
2. If the current node is `null`, the element is not found.
3. If the current node's value equals the target, return true (found).
4. If the target is less than the current node's value, move to the left child.
5. If the target is greater, move to the right child.
6. Repeat steps 2-5 until the node is found or you reach a null node.

### C++ Code

```cpp
// filepath: c:\Users\abondada\source\repos\abhiram_personal\cp_and_algos\temp\Data Structures\Trees\Binary Search Tree\Search element.md
#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

bool searchBST(TreeNode* root, int target) {
    while (root) {
        if (root->val == target) return true;
        else if (target < root->val) root = root->left;
        else root = root->right;
    }
    return false;
}

// Example usage
int main() {
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(3);
    root->right = new TreeNode(7);
    root->left->left = new TreeNode(2);
    root->left->right = new TreeNode(4);

    int target = 4;
    cout << (searchBST(root, target) ? "Found" : "Not Found") << endl;
    return 0;
}
```

#### LeetCode Reference

- [LeetCode 700. Search in a Binary Search Tree](https://leetcode.com/problems/search-in-a-binary-search-tree/)

---

## Searching for the Nearest Element in a BST (Closest Value)

### Algorithm

1. Initialize a variable to store the closest value (e.g., root's value).
2. Traverse the tree:
    - At each node, if the current node's value is closer to the target than the stored closest value, update the closest value.
    - If the target is less than the current node's value, move to the left child.
    - If the target is greater, move to the right child.
3. Continue until you reach a null node.
4. Return the closest value found.

### C++ Code

```cpp
// filepath: c:\Users\abondada\source\repos\abhiram_personal\cp_and_algos\temp\Data Structures\Trees\Binary Search Tree\Search element.md
#include <iostream>
#include <cmath>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

int closestValue(TreeNode* root, double target) {
    int closest = root->val;
    while (root) {
        if (abs(root->val - target) < abs(closest - target)) {
            closest = root->val;
        }
        if (target < root->val) root = root->left;
        else if (target > root->val) root = root->right;
        else break;
    }
    return closest;
}

// Example usage
int main() {
    TreeNode* root = new TreeNode(8);
    root->left = new TreeNode(3);
    root->right = new TreeNode(10);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(6);

    double target = 5.7;
    cout << "Closest value: " << closestValue(root, target) << endl;
    return 0;
}
```

#### LeetCode Reference

- [LeetCode 270. Closest Binary Search Tree Value](https://leetcode.com/problems/closest-binary-search-tree-value/)
