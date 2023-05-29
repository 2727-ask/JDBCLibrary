#include <iostream>
#include <queue>
#include <omp.h>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void bfs(TreeNode* root) {
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        cout << node->val << " ";
        if (node->left) {
            q.push(node->left);
        }
        if (node->right) {
            q.push(node->right);
        }
    }
}

void parallel_bfs(TreeNode* root) {
    queue<TreeNode*> q;
    q.push(root);
    #pragma omp parallel
    {
        while (!q.empty()) {
            #pragma omp for nowait
            for (int i = 0; i < q.size(); i++) {
                TreeNode* node;
                #pragma omp critical
                {
                    node = q.front();
                    q.pop();
                }
                #pragma omp critical
                {
                    cout << node->val << " ";
                }
                if (node->left) {
                    #pragma omp critical
                    {
                        q.push(node->left);
                    }
                }
                if (node->right) {
                    #pragma omp critical
                    {
                        q.push(node->right);
                    }
                }
            }
        }
    }
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);

    cout << "Serial BFS traversal: ";
    double start = omp_get_wtime();
    bfs(root);
    double end = omp_get_wtime();
    cout << "\nSerial BFS took " << (end - start) * 1000 << " milliseconds." << endl;

    cout << "---------------------------------------" << endl;

    cout << "Parallel BFS traversal: ";
    start = omp_get_wtime();
    parallel_bfs(root);
    end = omp_get_wtime();
    cout << "\nParallel BFS took " << (end - start) * 1000 << " milliseconds." << endl;

    return 0;
}