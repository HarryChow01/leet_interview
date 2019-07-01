
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <iostream>

using namespace std;


template<typename T>
inline ostream& operator<<(ostream& out, vector<T>& data) {
    for (auto& item : data) {
        out << " " << item;
    }
    //out << endl;
    return out;
}

template<typename T>
inline ostream& operator<<(ostream& out, list<T>& data) {
    for (auto& item : data) {
        out << " " << item;
    }
    //out << endl;
    return out;
}

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
struct TreeLinkNode {
    int val;
    struct TreeLinkNode *left;
    struct TreeLinkNode *right;
    struct TreeLinkNode *next;
    TreeLinkNode(int x) :val(x), left(nullptr), right(nullptr), next(nullptr) {
    }
};
//vector<int> preOrderTree = {1,2,3,4,5,6,7,8};
//vector<int> inOrderTree = {3,2,5,6,4,7,1,8};
//vector<int> postOrderTree = {3,6,5,7,4,2,8,1};
/*
           1
        /     \
       2        8
     /    \
   3       4
         /    \
        5       7
          \
            6
 */
TreeNode *preInBuildTree(vector<int> &preorder, int pLeft, int pRight, vector<int> &inorder, int iLeft, int iRight) {
    if (pLeft > pRight || iLeft > iRight) return nullptr;
    int i = 0;
    for (i = iLeft; i <= iRight; ++i) {
        if (preorder[pLeft] == inorder[i]) break;
    }
    auto *cur = new TreeNode(preorder[pLeft]);
    cur->left = preInBuildTree(preorder, pLeft + 1, pLeft + i - iLeft, inorder, iLeft, i - 1);
    cur->right = preInBuildTree(preorder, pLeft + i - iLeft + 1, pRight, inorder, i + 1, iRight);
    return cur;
}
TreeNode *preInBuildTree(vector<int> &preorder, vector<int> &inorder) {
    return preInBuildTree(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
}

TreeNode *inPostBuildTree(vector<int> &inorder, int iLeft, int iRight, vector<int> &postorder, int pLeft, int pRight) {
    if (iLeft > iRight || pLeft > pRight) return nullptr;
    auto *cur = new TreeNode(postorder[pRight]);
    int i = 0;
    for (i = iLeft; i < inorder.size(); ++i) {
        if (inorder[i] == postorder[pRight]) break;
    }
    cur->left = inPostBuildTree(inorder, iLeft, i - 1, postorder, pLeft, pLeft + i - iLeft - 1);
    cur->right = inPostBuildTree(inorder, i + 1, iRight, postorder, pLeft + i - iLeft, pRight - 1);
    return cur;
}
TreeNode *inPostBuildTree(vector<int> &inorder, vector<int> &postorder) {
    return inPostBuildTree(inorder, 0, inorder.size() - 1, postorder, 0, postorder.size() - 1);
}

void bstToLinkCore(TreeNode* pNode, TreeNode** pLastNode, TreeNode** pHead){
    //叶结点直接返回
    if(pNode == nullptr){
        return;
    }
    TreeNode* pCurrent = pNode;
    //递归左子树
    if(pCurrent->left)
        bstToLinkCore(pCurrent->left, pLastNode, pHead);

    //左指针
    pCurrent->left = *pLastNode;
    //右指针
    if(*pLastNode){
        (*pLastNode)->right = pCurrent;
    } else {
        *pHead = pCurrent;
    }
    //更新双向链表尾结点
    *pLastNode = pCurrent;
    //递归右子树
    if(pCurrent->right){
        bstToLinkCore(pCurrent->right, pLastNode, pHead);
    }
}
TreeNode* bstToLink(TreeNode* pRoot) {
    //用于记录双向链表尾结点
    TreeNode* pLastNode = nullptr;
    TreeNode* pHead = nullptr;
    //开始转换结点
    bstToLinkCore(pRoot, &pLastNode, &pHead);
    return pHead;
}

TreeNode* kthNodeCore(TreeNode* pRoot, int &k){
    TreeNode* target = nullptr;
    // 先遍历左结点
    if (pRoot->left) {
        target = kthNodeCore(pRoot->left, k);
    }
    // 如果没有找到target，则继续减小k，如果k等于1，说明到了第k大的数
    if (!target) {
        if(k == 1){
            target = pRoot;
            return target;
        }
        k--;
    }
    // 如果没有找到target，继续找右结点
    if(pRoot->right && !target){
        target = kthNodeCore(pRoot->right, k);
    }
    return target;
}
TreeNode* kthNode(TreeNode* pRoot, int k)
{
    if(!pRoot || k < 1){
        return nullptr;
    }
    return kthNodeCore(pRoot, k);
}


void destroyBiTree(TreeNode *root) {
    if(!root)
        return;
    if(root->left)
        destroyBiTree(root->left);
    if(root->right)
        destroyBiTree(root->right);
    delete root;
}

void preorderTraversal(TreeNode *root, vector<int> &res) {
    if (!root) {
        return;
    }
    res.emplace_back(root->val);
    preorderTraversal(root->left, res);
    preorderTraversal(root->right, res);
}
void inorderTraversal(TreeNode *root, vector<int> &res) {
    if (!root) {
        return;
    }
    inorderTraversal(root->left, res);
    res.emplace_back(root->val);
    inorderTraversal(root->right, res);
}
void postorderTraversal(TreeNode *root, vector<int> &res) {
    if (!root) {
        return;
    }
    postorderTraversal(root->left, res);
    postorderTraversal(root->right, res);
    res.emplace_back(root->val);
}

// http://www.cnblogs.com/grandyang/p/4146981.html
void preorderTraversal2(TreeNode* root, vector<int> &res) {
    stack<TreeNode*> s;
    TreeNode *p = root;
    while (!s.empty() || p) {
        if (p) {
            s.push(p);
            res.push_back(p->val);
            p = p->left;
        } else {
            auto *t = s.top(); s.pop();
            p = t->right;
        }
    }
}
void preorderTraversal3(TreeNode* root, vector<int> &res) {
    stack<TreeNode*> s;
    TreeNode *p = root;
    while (!s.empty() || p) {
        while (p) {
            s.push(p);
            res.push_back(p->val);
            p = p->left;
        }
        auto *t = s.top(); s.pop();
        p = t->right;
    }
}
void preorderTraversal4(TreeNode* root, vector<int> &res) {
    if (!root) return;
    stack<TreeNode*> s;
    s.push(root);
    while (!s.empty()) {
        TreeNode *t = s.top(); s.pop();
        res.push_back(t->val);
        if (t->right) s.push(t->right);
        if (t->left) s.push(t->left);
    }
}

// http://www.cnblogs.com/grandyang/p/4297300.html
void inorderTraversal2(TreeNode *root, vector<int> &res) {
    stack<TreeNode*> s;
    auto *p = root;
    while (p || !s.empty()) {
        while (p) {
            s.push(p);
            p = p->left;
        }
        p = s.top(); s.pop();
        res.push_back(p->val);
        p = p->right;
    }
}
void inorderTraversal3(TreeNode* root, vector<int> &res) {
    stack<TreeNode*> s;
    auto *p = root;
    while (!s.empty() || p) {
        if (p) {
            s.push(p);
            p = p->left;
        } else {
            p = s.top(); s.pop();
            res.push_back(p->val);
            p = p->right;
        }
    }
}
void inorderTraversal4(TreeNode *root, vector<int> &res) {
    if (!root) return;
    TreeNode *cur, *pre;
    cur = root;
    while (cur) {
        if (!cur->left) {
            res.push_back(cur->val);
            cur = cur->right;
        } else {
            pre = cur->left;
            while (pre->right && pre->right != cur) pre = pre->right;
            if (!pre->right) {
                pre->right = cur;
                cur = cur->left;
            } else {
                // pre->right point to next inorder node, now it's that node's turn
                // so pre->right must renew to nullptr
                pre->right = nullptr;
                res.push_back(cur->val);
                cur = cur->right; // all cur->right 's been set with cur,not null
            }
        }
    }
}

// http://www.cnblogs.com/grandyang/p/4251757.html
void postorderTraversal2(TreeNode* root, vector<int> &res) {
    stack<TreeNode*> s;
    TreeNode *p = root;
    while (!s.empty() || p) {
        if (p) {
            s.push(p);
            res.insert(res.begin(), p->val);
            p = p->right;
        } else {
            TreeNode *t = s.top(); s.pop();
            p = t->left;
        }
    }
}
void postorderTraversal3(TreeNode* root, vector<int> &res) {
    if (!root) return;
    stack<TreeNode*> s;
    s.push(root);
    while (!s.empty()) {
        TreeNode *t = s.top(); s.pop();
        res.insert(res.begin(), t->val);
        if (t->left) s.push(t->left);
        if (t->right) s.push(t->right);
    }

}
void postorderTraversal4(TreeNode* root, vector<int> &res) {
    if (!root) return;
    stack<TreeNode*> s{{root}};
    TreeNode *head = root;  // head不能初始化为空，否则出错；
    while (!s.empty()) {
        TreeNode *t = s.top();
        if ((!t->left && !t->right) || t->left == head || t->right == head) {
            res.push_back(t->val);
            s.pop();
            head = t;
        } else {
            if (t->right) s.push(t->right);
            if (t->left) s.push(t->left);
        }
    }
}

void postorderTraversal5(TreeNode* root, vector<int> &res) {
    if (!root) return;
    stack<TreeNode*> s1, s2;
    s1.push(root);
    while (!s1.empty()) {
        TreeNode *t = s1.top(); s1.pop();
        s2.push(t);
        if (t->left) s1.push(t->left);
        if (t->right) s1.push(t->right);
    }
    while (!s2.empty()) {
        res.push_back(s2.top()->val); s2.pop();
    }
}

vector<vector<int>> levelOrder1(TreeNode* root) {
    if (!root) return {};
    vector<vector<int>> res;
    queue<TreeNode*> q{{root}};
    while (!q.empty()) {
        vector<int> oneLevel;
        const size_t queueSize = q.size();
        //for (size_t i = 0; i < queueSize; ++i) {
        for (int i = q.size(); i > 0; --i) {
            TreeNode *t = q.front(); q.pop();
            oneLevel.push_back(t->val);
            if (t->left) q.push(t->left);
            if (t->right) q.push(t->right);
        }
        res.push_back(oneLevel);
    }
    return res;
}
void levelorder(TreeNode* node, int level, vector<vector<int>>& res) {
    if (!node) return;
    if (res.size() == level) res.push_back({});
    res[level].push_back(node->val);
    if (node->left) levelorder(node->left, level + 1, res);
    if (node->right) levelorder(node->right, level + 1, res);
}
vector<vector<int>> levelOrder2(TreeNode* root) {
    vector<vector<int>> res;
    levelorder(root, 0, res);
    return res;
}

vector<int> rightSideView(TreeNode *root) {
    vector<int> res;
    if (!root) {
        return res;
    }

    std::queue<TreeNode *> queue;
    queue.push(root);
    while (!queue.empty()) {
        int levelSize = queue.size();
        for (int i = levelSize; i > 1; --i) {
            auto *p = queue.front();
            queue.pop();
            if (p->left) queue.push(p->left);
            if (p->right) queue.push(p->right);
        }
        auto *p = queue.front();
        res.push_back(p->val);
        queue.pop();
        if (p->left) queue.push(p->left);
        if (p->right) queue.push(p->right);
    }
}

TreeLinkNode* getNextTreeNode(TreeLinkNode* pNode)
{
    if(pNode == nullptr){
        return nullptr;
    }
    TreeLinkNode* pNext = nullptr;
    // 当前结点有右子树，那么它的下一个结点就是它的右子树中最左子结点
    if(pNode->right != nullptr){
        TreeLinkNode* pRight = pNode->right;
        while(pRight->left != nullptr){
            pRight = pRight-> left;
        }
        pNext = pRight;
    }
    // 当前结点无右子树，则需要找到这样一个结点：本节点在该祖先节点的左子树上，或者一个空指针
    else if(pNode->next != nullptr){
        // 当前结点
        TreeLinkNode* pCur = pNode;
        // 父节点
        TreeLinkNode* pPar = pNode->next;
        while(pPar != nullptr && pCur == pPar->right){
            pCur = pPar;
            pPar = pCur->next;
        }
        pNext = pPar;
    }
    return pNext;
}

bool isSymmetriacalCore(TreeNode* pRoot1, TreeNode* pRoot2){
    if(pRoot1 == nullptr && pRoot2 == nullptr){
        return true;
    }
    if(pRoot1 == nullptr || pRoot2 == nullptr){
        return false;
    }
    if(pRoot1->val != pRoot2->val){
        return false;
    }
    return isSymmetriacalCore(pRoot1->left, pRoot2->right) && isSymmetriacalCore(pRoot1->right, pRoot2->left);
}
bool isSymmetrical(TreeNode* pRoot) {
    if(pRoot == nullptr){
        return true;
    }
    return isSymmetriacalCore(pRoot, pRoot);
}

void printSwapTree(TreeNode* pRoot) {
    vector<vector<int> > result;
    if(pRoot == nullptr){
        return;
    }
    stack<TreeNode* > s[2];
    s[0].push(pRoot);
    while(!s[0].empty() || !s[1].empty()){
        vector<int> v[2];
        // 偶数行
        while(!s[0].empty()){
            TreeNode* p = s[0].top();
            v[0].push_back(p->val);
            if(p->left != nullptr){
                s[1].push(p->left);
            }
            if(p->right != nullptr){
                s[1].push(p->right);
            }
            s[0].pop();
        }
        if(!v[0].empty()){
            result.push_back(v[0]);
        }
        // 奇数行
        while(!s[1].empty()){
            TreeNode* p = s[1].top();
            v[1].push_back(p->val);
            if(p->right != nullptr){
                s[0].push(p->right);
            }
            if(p->left != nullptr){
                s[0].push(p->left);
            }
            s[1].pop();
        }
        if(!v[1].empty()){
            result.push_back(v[1]);
        }
    }
    for (auto &level : result) {
        cout << level << endl;
    }
}

void serializeCore(TreeNode* root, string& str){
    // 如果指针为空，表示左子节点或右子节点为空，则在序列中用#表示
    if(!root){
        str += '#';
        return;
    }
    string tmp = to_string(root->val);
    str += tmp;
    // 加逗号，用于区分每个结点
    str += ',';
    serializeCore(root->left, str);
    serializeCore(root->right, str);
}
char* serialize(TreeNode *root) {
    if(!root){
        return nullptr;
    }
    string str;
    serializeCore(root, str);
    // 把str流中转换为字符串返回
    int length = str.length();
    char* res = new char[length+1];
    // 把str流中转换为字符串返回
    for(int i = 0; i < length; i++){
        res[i] = str[i];
    }
    res[length] = '\0';
    return res;
}
// 递归时改变了str值使其指向后面的序列，因此要声明为char**
TreeNode* deserializeCore(char** str){
    // 到达叶节点时，调用两次，都返回null，所以构建完毕，返回父节点的构建
    if(**str == '#'){
        (*str)++;
        return nullptr;
    }
    // 因为整数是用字符串表示，一个字符表示一位，先进行转换
    int num = 0;
    while(**str != ',' && **str != '\0'){
        num = num * 10 + ((**str) - '0');
        (*str)++;
    }
    TreeNode* root = new TreeNode(num);
    if(**str == '\0'){
        return root;
    }
    else{
        (*str)++;
    }
    root->left = deserializeCore(str);
    root->right = deserializeCore(str);
    return root;
}
TreeNode* deserialize(char *str) {
    if(!str){
        return nullptr;
    }
    TreeNode* res = deserializeCore(&str);
    return res;
}

bool verifySequenceBSTCore(vector<int> seq, int begin, int end){
    if(seq.empty() || begin > end){
        return false;
    }

    //根结点
    int root = seq[end];

    //在二叉搜索树中左子树的结点小于根结点
    int i = begin;
    for(; i < end; ++i){
        if(seq[i] > root){
            break;
        }
    }
    //在二叉搜索书中右子树的结点大于根结点
    for(int j = i; j < end; ++j){
        if(seq[j] < root){
            return false;
        }
    }

    //判断左子树是不是二叉搜索树
    bool left = true;
    if (i > begin) {
        left = verifySequenceBSTCore(seq, begin, i - 1);
    }
    //判断右子树是不是二叉搜索树
    bool right = true;
    if (i < end - 1) {
        right = verifySequenceBSTCore(seq, i , end - 1);
    }
    return left && right;
}
bool verifySequenceOfBST(vector<int>& sequence) {
    return verifySequenceBSTCore(sequence, 0, sequence.size() - 1);
}

size_t countLeaf(TreeNode *root) {
    if (!root) {
        return 0;
    }
    if (!root->left && !root->right) {
        return 1;
    } else {
        return countLeaf(root->left) + countLeaf(root->right);
    }
}

size_t countNode(TreeNode *root) {
    if (!root) {
        return 0;
    }
    return countNode(root->left) + countNode(root->right) + 1;
}

size_t countNoLeafNode(TreeNode *root) {
    if (!root) {
        return 0;
    }
    if (!root->left && !root->right) {
        return 0;
    } else {
        return countNoLeafNode(root->left) + countNoLeafNode(root->right) + 1;
    }
}

int treeDepth1(TreeNode* root) {
    if (!root) return 0;
    return 1 + std::max(treeDepth1(root->left), treeDepth1(root->right));
}
int treeDepth2(TreeNode* root) {
    if (!root) return 0;
    int res = 0;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        ++res;
        int n = q.size();
        for (int i = 0; i < n; ++i) {
            TreeNode *t = q.front(); q.pop();
            if (t->left) q.push(t->left);
            if (t->right) q.push(t->right);
        }
    }
    return res;
}
bool isBalancedTree1(TreeNode* pRoot) {
    if(pRoot == nullptr){
        return true;
    }
    int left = treeDepth1(pRoot->left);
    int right = treeDepth1(pRoot->right);
    if (std::abs(left - right) > 1){
        return false;
    }
    return isBalancedTree1(pRoot->left) && isBalancedTree1(pRoot->right);
}
int checkDepth(TreeNode *root) {
    if (!root) return 0;
    int left = checkDepth(root->left);
    if (left == -1) return -1;
    int right = checkDepth(root->right);
    if (right == -1) return -1;
    int diff = abs(left - right);
    if (diff > 1) return -1;
    else return 1 + max(left, right);
}
bool isBalancedTree2(TreeNode *root) {
    if (checkDepth(root) == -1) return false;
    else return true;
}


bool areLikeTrees(TreeNode *p, TreeNode *q) {
    if (!p && !q) return true;
    if ((p && !q) || (!p && q)) return false;
    return areLikeTrees(p->left, q->left) && areLikeTrees(p->right, q->right);
}

bool areSameTrees1(TreeNode *p, TreeNode *q) {
    if (!p && !q) return true;
    if ((p && !q) || (!p && q) || (p->val != q->val)) return false;
    return areSameTrees1(p->left, q->left) && areSameTrees1(p->right, q->right);
}
bool areSameTrees2(TreeNode* p, TreeNode* q) {
    stack<TreeNode*> s1, s2;
    if (p) s1.push(p);
    if (q) s2.push(q);
    while (!s1.empty() && !s2.empty()) {
        TreeNode *t1 = s1.top(); s1.pop();
        TreeNode *t2 = s2.top(); s2.pop();
        if (t1->val != t2->val) return false;
        if (t1->left) s1.push(t1->left);
        if (t2->left) s2.push(t2->left);
        if (s1.size() != s2.size()) return false;
        if (t1->right) s1.push(t1->right);
        if (t2->right) s2.push(t2->right);
        if (s1.size() != s2.size()) return false;
    }
    return s1.size() == s2.size();
}

bool isSubtree1(TreeNode* s, TreeNode* t) {
    if (!t) return true;
    if (!s) return false;
    if (areSameTrees1(s, t)) return true;
    return isSubtree1(s->left, t) || isSubtree1(s->right, t);
}

TreeNode *copyBiTree(TreeNode *t) {
    if (!t)
        return t;
    auto *p = new TreeNode(t->val);
    p->left = copyBiTree(t->left);
    p->right = copyBiTree(t->right);
    return p;
}

void makeMirrorTree(TreeNode *pRoot) {
    if (!pRoot){
        return;
    }
    //交换根节点的左右结点
    std::swap(pRoot->left, pRoot->right);
    //递归左子树
    if (pRoot->left) {
        makeMirrorTree(pRoot->left);
    }
    //递归右子树
    if (pRoot->right) {
        makeMirrorTree(pRoot->right);
    }
}

// https://blog.csdn.net/stockholm_sun/article/details/75647259
TreeNode* lowestCommonAncestor1(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || p == root || q == root) return root;
    TreeNode *left = lowestCommonAncestor1(root->left, p, q);
    TreeNode *right = lowestCommonAncestor1(root->right, p , q);
    if (left && right) return root;
    return left ? left : right;
}

TreeNode* lowestCommonAncestor2(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || p == root || q == root) return root;
    TreeNode *left = lowestCommonAncestor2(root->left, p, q);
    if (left && left != p && left != q) return left;
    TreeNode *right = lowestCommonAncestor2(root->right, p , q);
    if (left && right) return root;
    return left ? left : right;
}

void findNodePath(TreeNode *t, TreeNode *q, vector<TreeNode *>& path) {
    vector<bool> tag;
    TreeNode *p = t;

    while (p || !path.empty()) {
        if (p) {
            path.push_back(p);
            tag.push_back(false);
            if (p == q) {
                break;
            }
            p = p->left;
        } else {
            if (!tag.back()) {
                tag.back() = true;
                p = path.back()->right;
            } else {
                path.pop_back();
                tag.pop_back();
            }
        }
    }//end while
}

inline ostream& operator<<(ostream& out, vector<TreeNode *>& data) {
    for (auto& item : data) {
        out << " " << item->val;
    }
    //out << endl;
    return out;
}

void findShortLongPath(TreeNode *t, vector<TreeNode *>& shortPath, vector<TreeNode *>& longPath) {
    vector<TreeNode *> path;
    vector<bool> tag;

    TreeNode *p = t;
    bool shortSet = false;
    while (p || !path.empty()) {
        if (p) {
            path.push_back(p);
            tag.push_back(false);
            if (!p->left && !p->right) {
                if (!shortSet || path.size() < shortPath.size() ) {
                    shortPath = path;
                    shortSet = true;
                }
                if (path.size() > longPath.size()) {
                    longPath = path;
                }
            }

            p = p->left;
        } else {
            if (!tag.back()) {
                tag.back() = true;
                p = path.back()->right;
            } else {
                path.pop_back();
                tag.pop_back();
            }
        }
    }//end while

}

TreeNode *treeLCA1(TreeNode *t, TreeNode *q1, TreeNode *q2) {
    vector<TreeNode *> path;
    vector<TreeNode *> path1;
    vector<TreeNode *> path2;
    vector<bool> tag;

    TreeNode *p = t;

    while (p || !path.empty()) {
        if (p) {
            path.push_back(p);
            tag.push_back(false);
            if (p == q1) {
                for(auto &item : path) {
                    path1.push_back(item);
                }
            }
            if (p == q2) {
                for(auto &item : path) {
                    path2.push_back(item);
                }
            }
            p = p->left;
        } else {
            if (!tag.back()) {
                tag.back() = true;
                p = path.back()->right;
            } else {
                path.pop_back();
                tag.pop_back();
            }
        }
    }//end while

    size_t minLen = std::min(path1.size(), path2.size());
    size_t i = 1;
    for(; i < minLen; ++i)
        if(path1[i] != path2[i])
            break;
    return path1[i - 1];
}

TreeNode *treeLCA2(TreeNode *t, TreeNode *q1, TreeNode *q2) {
    vector<TreeNode *> path;
    vector<TreeNode *> path1;
    vector<TreeNode *> path2;
    vector<bool> tag;

    bool q1Found = false;
    bool q2Found = false;
    TreeNode *p = t;

    while (p || !path.empty()) {
        if (p) {
            path.push_back(p);
            tag.push_back(false);
            if (!q1Found && p == q1) {
                for(auto &item : path) {
                    path1.push_back(item);
                }
                q1Found = true;
                if (q2Found) {
                    break;
                }
            }
            if (!q2Found && p == q2) {
                for(auto &item : path) {
                    path2.push_back(item);
                }
                q2Found = true;
                if (q1Found) {
                    break;
                }
            }
            p = p->left;
        } else {
            if (!tag.back()) {
                tag.back() = true;
                p = path.back()->right;
            } else {
                path.pop_back();
                tag.pop_back();
            }
        }
    }//end while

    size_t minLen = std::min(path1.size(), path2.size());
    size_t i = 1;
    for(; i < minLen; ++i)
        if(path1[i] != path2[i])
            break;
    return path1[i - 1];
}

/*
           1
        /     \
       2        8
     /    \
   3       4
         /    \
        5      7
          \
           6
 */

void findTargetSumPath(TreeNode* root, int expectNumber,
        vector<int>& path, vector<vector<int>>& result) {

    if (!root) return;
    expectNumber -= root->val;
    path.push_back(root->val);
    if (expectNumber == 0 && !root->left && !root->right){
        result.push_back(path);
        return;
    }
    //遍历左子树
    findTargetSumPath(root->left, expectNumber, path, result);
    //遍历右子树
    findTargetSumPath(root->right, expectNumber, path, result);
    path.pop_back();
}

TreeNode *findTreeNode(TreeNode *root, int nodeValue) {
    stack<TreeNode*> s;
    auto *p = root;
    while (p || !s.empty()) {
        while (p) {
            if (p->val == nodeValue) {
                return p;
            }
            s.push(p);
            p = p->left;
        }
        p = s.top(); s.pop();
        p = p->right;
    }
    return nullptr;
}
void testLACTree() {
    // Lowest Common Ancestor
    vector<int> preOrderTree = {1, 2, 3, 4, 5, 6, 7, 8};
    vector<int> inOrderTree = {3, 2, 5, 6, 4, 7, 1, 8};
    TreeNode *root = preInBuildTree(preOrderTree, inOrderTree);
    vector<int> res;

    auto *q1 = findTreeNode(root, 4);
    auto *q2 = findTreeNode(root, 4);
    vector<TreeNode *> path;
    findNodePath(root, q1, path);
    cout << "path:" << path << endl;

    vector<TreeNode *> shortPath;
    vector<TreeNode *> longPath;
    findShortLongPath(root, shortPath, longPath);
    cout << "shortPath:" << shortPath << endl;
    cout << "longPath:" << longPath << endl;

    auto *ancestor = treeLCA1(root, q1, q2);
    cout << "lca ancestor: " << ancestor->val << endl;

}

/*
           1
        /     \
       2        8
     /    \
   3       4
         /    \
        5      7
          \
           6
 */
void testTraversalTree() {
    vector<int> preOrderTree = {1,2,3,4,5,6,7,8};
    vector<int> inOrderTree = {3,2,5,6,4,7,1,8};
    vector<int> postOrderTree = {3,6,5,7,4,2,8,1};
    TreeNode *root = preInBuildTree(preOrderTree, inOrderTree);
    //TreeNode *root = inPostBuildTree(inOrderTree, postOrderTree);
    vector<int> res;
    //preorderTraversal2(root, res);
    //inorderTraversal2(root, res);
    //postorderTraversal5(root, res);
    //cout << res << endl;
    //cout << "leaf number: " << countLeaf(root) << endl;
    //cout << "noLeafNode number: " << countNoLeafNode(root) << endl;
    //cout << "node number: " << countNode(root) << endl;

    //auto *p = copyBiTree(root);
    //preorderTraversal2(p, res);
    //cout << res << endl;
    //cout << "areLikeTrees: " << areLikeTrees(root, p) << endl;
    //cout << "areSameTrees: " << areSameTrees2(root, p) << endl;

    //res = rightSideView(root);
    //cout << res << endl;

}

vector<vector<int>> zigzagLevelOrder(TreeNode *root) {
    vector<vector<int>> res;
    if (!root) return res;
    stack<TreeNode *> s1;
    stack<TreeNode *> s2;
    if (root) {
        s1.push(root);
    }
    while (!s1.empty() || !s2.empty()) {
        vector<int> v1;
        vector<int> v2;
        while (!s1.empty()) {
            auto *p = s1.top();
            s1.pop();
            v1.push_back(p->val);
            if (p->left) {
                s2.push(p->left);
            }
            if (p->right) {
                s2.push(p->right);
            }
        }
        if (!v1.empty()) {
            res.push_back(v1);
        }
        while (!s2.empty()) {
            auto *p = s2.top();
            s2.pop();
            v2.push_back(p->val);
            if (p->right) {
                s1.push(p->right);
            }
            if (p->left) {
                s1.push(p->left);
            }
        }
        if (!v2.empty()) {
            res.push_back(v2);
        }
    }

    return res;
}

int minDepth(TreeNode* root) {
    if (!root) return 0;
    int res = 0;
    queue<TreeNode*> q{{root}};
    while (!q.empty()) {
        ++res;
        for (int i = q.size(); i > 0; --i) {
            auto t = q.front(); q.pop();
            if (!t->left && !t->right) return res;
            if (t->left) q.push(t->left);
            if (t->right) q.push(t->right);
        }
    }
    return -1;
}

// http://www.cnblogs.com/grandyang/p/4042156.html
vector<vector<int> > pathSum2(TreeNode *root, int sum) {
    vector<vector<int>> res;
    vector<TreeNode*> s;
    TreeNode *cur = root, *pre = nullptr;
    // pre用于右子树处理完毕后的回溯
    int val = 0;
    while (cur || !s.empty()) {
        while (cur) {
            s.push_back(cur);
            val += cur->val;
            cur = cur->left;
        }
        cur = s.back();
        if (!cur->left && !cur->right && val == sum) {
            vector<int> v;
            for (auto it : s) {
                v.push_back(it->val);
            }
            res.push_back(v);
        }
        if (cur->right && cur->right != pre) cur = cur->right; // 右子树第一次入vector
        else {
            pre = cur; // 用于右子树处理完毕后的回溯
            val -= cur->val;
            s.pop_back();
            cur = nullptr;
        }
    }
    return res;
}

int main() {
    //testTraversalTree();
    testLACTree();

    return 0;
}










