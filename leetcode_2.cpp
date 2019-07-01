
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

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct Interval {
    size_t start = 0;
    size_t end = 0;
};



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

template<typename T>
inline ostream& operator<<(ostream& out, vector<vector<T>>& data) {
    for (auto& row : data) {
        for (auto& item : row) {
            out << " " << item;
        }
        out << endl;
    }
    return out;
}

ListNode* createList(const size_t len) {

    ListNode* p = nullptr;
    ListNode* q = nullptr;

    ListNode* ret = new ListNode(1);
    q = ret;
    for(int i = 1; i < len; i++) {
        p = new ListNode(1 + i);
        q->next = p;
        q = p;
    }
    return ret;
}
ListNode* createList2(std::list<int>& datas) {
    auto* dummy = new ListNode(-1);
    ListNode* p = dummy;
    for(auto& item : datas) {
        p->next = new ListNode(item);
        p = p->next;
    }
    return dummy->next;
}
void printList(ListNode* head) {
    if (!head) {
        return;
    }
    ListNode* p = head;
    cout << "List:";
    while(p) {
        cout << " " << p->val;
        p = p->next;
    }
    cout << endl;
}
void deleteList(ListNode* head) {
    ListNode* p = head;
    while(p) {
        ListNode* q = p;
        p = p->next;
        delete(q);
    }
}

ListNode *reverseOneGroup(ListNode *pre, ListNode *next) {
    ListNode *last = pre->next;
    ListNode *cur = last->next;
    while(cur != next) {
        last->next = cur->next;
        cur->next = pre->next;
        pre->next = cur;
        cur = last->next;
    }
    return last;
}
ListNode *reverseKGroup(ListNode *head, int k) {
    if (!head || k == 1) return head;
    ListNode *dummy = new ListNode(-1);
    ListNode *pre = dummy, *cur = head;
    dummy->next = head;
    int i = 0;
    while (cur) {
        ++i;
        if (i % k == 0) {
            pre = reverseOneGroup(pre, cur->next);
            cur = pre->next;
        } else {
            cur = cur->next;
        }
    }
    return dummy->next;
}
void testReverseKGroup() {
    auto head = createList(8);
    printList(head);
    head = reverseKGroup(head, 3);
    printList(head);
}

int removeDuplicates(vector<int>& nums) {
    if (nums.empty()) return 0;
    int pre = 0, cur = 0, n = nums.size();
    while (cur < n) {
        if (nums[pre] == nums[cur]) ++cur;
        else nums[++pre] = nums[cur++];
    }
    return pre + 1;
}

int removeElement(vector<int>& nums, int val) {
    int res = 0;
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] != val) nums[res++] = nums[i];
    }
    return res;
}

int strStr(string haystack, string needle) {
    if (needle.empty()) return 0;
    int m = haystack.size(), n = needle.size();
    if (m < n) return -1;
    for (int i = 0; i <= m - n; ++i) {
        int j = 0;
        for (; j < n; ++j) {
            if (haystack[i + j] != needle[j]) break;
        }
        if (j == n) return i;
    }
    return -1;
}

int divide(int dividend, int divisor) {
    long long m = abs((long long)dividend), n = abs((long long)divisor), res = 0;
    if (m < n) return 0;
    while (m >= n) {
        long long t = n, p = 1;
        while (m > (t << 1)) {
            t <<= 1;
            p <<= 1;
        }
        res += p;
        m -= t;
    }
    if ((dividend < 0) ^ (divisor < 0)) res = -res;
    return res > INT32_MAX ? INT32_MAX : res;
}

vector<int> findSubstring(string s, vector<string>& words) {
    vector<int> res;
    if (s.empty() || words.empty()) return res;
    int n = words.size(), m = words[0].size();
    unordered_map<string, int> m1;
    for (auto &a : words) ++m1[a];
    for (int i = 0; i <= (int)s.size() - n * m; ++i) {
        unordered_map<string, int> m2;
        int j = 0;
        for (j = 0; j < n; ++j) {
            string t = s.substr(i + j * m, m);
            if (m1.find(t) == m1.end()) break;
            ++m2[t];
            if (m2[t] > m1[t]) break;
        }
        if (j == n) res.push_back(i);
    }
    return res;
}

void nextPermutex_ation(vector<int> &num) {
    int i, j, n = num.size();
    for (i = n - 2; i >= 0; --i) {
        if (num[i + 1] > num[i]) {
            for (j = n - 1; j > i; --j) {
                if (num[j] > num[i]) break;
            }
            swap(num[i], num[j]);
            reverse(num.begin() + i + 1, num.end());
            return;
        }
    }
    reverse(num.begin(), num.end());
}

int longestValidParentheses(string s) {
    int res = 0, start = 0;
    stack<int> m;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '(') m.push(i);
        else if (s[i] == ')') {
            if (m.empty()) start = i + 1;
            else {
                m.pop();
                res = m.empty() ? max(res, i - start + 1) : max(res, i - m.top());
            }
        }
    }
    return res;
}

int search(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) return mid;
        else if (nums[mid] < nums[right]) {
            if (nums[mid] < target && nums[right] >= target) left = mid + 1;
            else right = mid - 1;
        } else {
            if (nums[left] <= target && nums[mid] > target) right = mid - 1;
            else left = mid + 1;
        }
    }
    return -1;
}

int biSearch(vector<int>& nums, int left, int right, int target) {
    if (left > right) return -1;
    int mid = left + (right - left) / 2;
    if (nums[mid] == target) return mid;
    else if (nums[mid] < target) return biSearch(nums, mid + 1, right, target);
    else return biSearch(nums, left, mid - 1, target);
}
vector<int> biSearch(vector<int>& nums, int target) {
    int idx = biSearch(nums, 0, nums.size() - 1, target);
    if (idx == -1) return {-1, -1};
    int left = idx, right = idx;
    while (left > 0 && nums[left - 1] == nums[idx]) --left;
    while (right < nums.size() - 1 && nums[right + 1] == nums[idx]) ++right;
    return {left, right};
}

int searchInsert(vector<int>& nums, int target) {
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] >= target) return i;
    }
    return nums.size();
}

bool isValidSudoku(vector<vector<char> > &board) {
    const size_t kSquare = 9;
    if (board.size() != kSquare || board[0].size() != kSquare) return false;
    vector<vector<bool> > rowFlag(kSquare, vector<bool>(kSquare, false));
    vector<vector<bool> > colFlag(kSquare, vector<bool>(kSquare, false));
    vector<vector<bool> > cellFlag(kSquare, vector<bool>(kSquare, false));
    for (int i = 0; i < kSquare; ++i) {
        for (int j = 0; j < kSquare; ++j) {
            if (board[i][j] >= '1' && board[i][j] <= '9') {
                int c = board[i][j] - '1';
                if (rowFlag[i][c] || colFlag[c][j] || cellFlag[3 * (i / 3) + j / 3][c]) return false;
                rowFlag[i][c] = true;
                colFlag[c][j] = true;
                cellFlag[3 * (i / 3) + j / 3][c] = true;
            }
        }
    }
    return true;
}

bool isValid(vector<vector<char> > &board, int i, int j) {
    for (int col = 0; col < 9; ++col) {
        if (col != j && board[i][j] == board[i][col]) return false;
    }
    for (int row = 0; row < 9; ++row) {
        if (row != i && board[i][j] == board[row][j]) return false;
    }
    for (int row = i / 3 * 3; row < i / 3 * 3 + 3; ++row) {
        for (int col = j / 3 * 3; col < j / 3 * 3 + 3; ++col) {
            if ((row != i || col != j) && board[i][j] == board[row][col]) return false;
        }
    }
    return true;
}
bool solveSudokuDFS(vector<vector<char> > &board, int i, int j) {
    if (i == 9) return true;
    if (j >= 9) return solveSudokuDFS(board, i + 1, 0);
    if (board[i][j] == '.') {
        for (int k = 1; k <= 9; ++k) {
            board[i][j] = (char)(k + '0');
            if (isValid(board, i , j)) {
                if (solveSudokuDFS(board, i, j + 1)) return true;
            }
            board[i][j] = '.';
        }
    } else {
        return solveSudokuDFS(board, i, j + 1);
    }
    return false;
}
void solveSudoku(vector<vector<char> > &board) {
    if (board.empty() || board.size() != 9 || board[0].size() != 9) return;
    solveSudokuDFS(board, 0, 0);
}

string countAndSay(int n) {
    if (n <= 0) return "";
    string res = "1";
    while (--n) {
        string cur = "";
        for (int i = 0; i < res.size(); ++i) {
            int cnt = 1;
            while (i + 1 < res.size() && res[i] == res[i + 1]) {
                ++cnt;
                ++i;
            }
            cur += to_string(cnt) + res[i];
        }
        res = cur;
    }
    return res;
}

void combinationSumDFS(vector<int> &candidates, int target, int start, vector<int> out, vector<vector<int>> &res) {
    if (target < 0) return;
    else if (target == 0) {res.push_back(out); return;}
    for (int i = start; i < candidates.size(); ++i) {
        out.push_back(candidates[i]);
        combinationSumDFS(candidates, target - candidates[i], i, out, res);
        out.pop_back();
    }
}
vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
    vector<vector<int>> res;
    combinationSumDFS(candidates, target, 0, {}, res);
    return res;
}

void combinationSum2DFS(vector<int> &num, int target, int start, vector<int> &out, vector<vector<int> > &res) {
    if (target < 0) return;
    else if (target == 0) res.push_back(out);
    else {
        for (int i = start; i < num.size(); ++i) {
            if (i > start && num[i] == num[i - 1]) continue;
            out.push_back(num[i]);
            combinationSum2DFS(num, target - num[i], i + 1, out, res);
            out.pop_back();
        }
    }
}
vector<vector<int> > combinationSum2(vector<int> &num, int target) {
    vector<vector<int> > res;
    vector<int> out;
    sort(num.begin(), num.end());
    combinationSum2DFS(num, target, 0, out, res);
    return res;
}

int firstMissingPositive(vector<int>& nums) {
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
        while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
            swap(nums[i], nums[nums[i] - 1]);
        }
    }
    for (int i = 0; i < n; ++i) {
        if (nums[i] != i + 1) return i + 1;
    }
    return n + 1;
}

int trap1(vector<int>& height) {
    int res = 0, mx = 0, n = height.size();
    vector<int> dp(n, 0);
    for (int i = 0; i < n; ++i) {
        dp[i] = mx;
        mx = max(mx, height[i]);
    }
    mx = 0;
    for (int i = n - 1; i >= 0; --i) {
        dp[i] = min(dp[i], mx);
        mx = max(mx, height[i]);
        if (dp[i] > height[i]) res += dp[i] - height[i];
    }
    return res;
}

string multiply(string num1, string num2) {
    string res;
    int n1 = num1.size(), n2 = num2.size();
    int k = n1 + n2 - 2, carry = 0;
    vector<int> v(n1 + n2, 0);
    for (int i = 0; i < n1; ++i) {
        for (int j = 0; j < n2; ++j) {
            v[k - i - j] += (num1[i] - '0') * (num2[j] - '0');
        }
    }
    for (int i = 0; i < n1 + n2; ++i) {
        v[i] += carry;
        carry = v[i] / 10;
        v[i] %= 10;
    }
    int i = n1 + n2 - 1;
    while (v[i] == 0) --i;
    if (i < 0) return "0";
    while (i >= 0) res.push_back(v[i--] + '0');
    return res;
}

bool isWildcardMatch(char *s, char *p) {
    char *scur = s, *pcur = p, *sstar = nullptr, *pstar = nullptr;
    while (*scur) {
        if (*scur == *pcur || *pcur == '?') {
            ++scur;
            ++pcur;
        } else if (*pcur == '*') {
            pstar = pcur++;
            sstar = scur;
        } else if (pstar) {
            pcur = pstar + 1;
            scur = ++sstar;
        } else return false;
    }
    while (*pcur == '*') ++pcur;
    return !*pcur;
}

bool canJump(vector<int>& nums) {
    vector<int> dp(nums.size(), 0);
    for (int i = 1; i < nums.size(); ++i) {
        dp[i] = max(dp[i - 1], nums[i - 1]) - 1;
        if (dp[i] < 0) return false;
    }
    return true;
}

int canJump2(vector<int>& nums) {
    int res = 0, n = nums.size(), i = 0, cur = 0;
    while (cur < n - 1) {
        ++res;
        int pre = cur;
        for (; i <= pre; ++i) {
            cur = max(cur, i + nums[i]);
        }
        if (pre == cur) return -1; // May not need this
    }
    return res;
}

void permutex_eDFS(vector<int> &num, int start, vector<vector<int> > &res) {
    if (start >= num.size()) res.push_back(num);
    for (int i = start; i < num.size(); ++i) {
        swap(num[start], num[i]);
        permutex_eDFS(num, start + 1, res);
        swap(num[start], num[i]);
    }
}
vector<vector<int> > permutex_e1(vector<int> &num) {
    vector<vector<int> > res;
    permutex_eDFS(num, 0, res);
    return res;
}

// 非重复；
void permutex_eUniqueDFS(vector<int> &num, int level, vector<int> &visited, vector<int> &out, vector<vector<int> > &res) {
    if (level >= num.size()) res.push_back(out);
    else {
        for (int i = 0; i < num.size(); ++i) {
            if (visited[i] == 0) {
                if (i > 0 && num[i] == num[i - 1] && visited[i - 1] == 0) continue;
                visited[i] = 1;
                out.push_back(num[i]);
                permutex_eUniqueDFS(num, level + 1, visited, out, res);
                out.pop_back();
                visited[i] = 0;
            }
        }
    }
}
vector<vector<int> > permutex_eUnique1(vector<int> &num) {
    vector<vector<int> > res;
    vector<int> out;
    vector<int> visited(num.size(), 0);
    sort(num.begin(), num.end());
    permutex_eUniqueDFS(num, 0, visited, out, res);
    return res;
}

// 非重复；
void permutex_e2(vector<int> &nums, int start, set<vector<int>> &res) {
    if (start >= nums.size()) res.insert(nums);
    for (int i = start; i < nums.size(); ++i) {
        if (i != start && nums[i] == nums[start]) continue;
        swap(nums[i], nums[start]);
        permutex_e2(nums, start + 1, res);
        swap(nums[i], nums[start]);
    }
}
vector<vector<int>> permutex_eUnique2(vector<int>& nums) {
    set<vector<int>> res;
    permutex_e2(nums, 0, res);
    return vector<vector<int>> (res.begin(), res.end());
}

void rotate(vector<vector<int> > &matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            swap(matrix[i][j], matrix[j][i]);
        }
        reverse(matrix[i].begin(), matrix[i].end());
    }
}

vector<vector<string>> groupAnagrams(vector<string>& strs) {
    vector<vector<string>> res;
    unordered_map<string, vector<string>> m;
    for (string str : strs) {
        string t = str;
        sort(t.begin(), t.end());
        m[t].push_back(str);
    }
    for (auto a : m) {
        res.push_back(a.second);
    }
    return res;
}

double power1(double x, int n) {
    if (n == 0) return 1;
    double half = power1(x, n / 2);
    if (n % 2 == 0) return half * half;
    return x * half * half;
}
double myPow(double x, int n) {
    if (n < 0) return 1 / power1(x, -n);
    return power1(x, n);
}

bool isValid(vector<int> &pos, int row, int col) {
    for (int i = 0; i < row; ++i) {
        // abs(row - i) == abs(col - pos[i])表示在同一斜线上
        if (col == pos[i] || abs(row - i) == abs(col - pos[i])) {
            return false;
        }
    }
    return true;
}
void solveNQueensDFS(vector<int> &pos, int row, vector<vector<string> > &res, size_t& count) {
    int n = pos.size();
    if (row == n) {
        ++count;
        vector<string> out(n, string(n, '.'));
        for (int i = 0; i < n; ++i) {
            out[i][pos[i]] = 'Q';
        }
        res.push_back(out);
    } else {
        for (int col = 0; col < n; ++col) {
            if (isValid(pos, row ,col)) {
                pos[row] = col;
                solveNQueensDFS(pos, row + 1, res, count);
                pos[row] = -1;
            }
        }
    }
}
vector<vector<string> > solveNQueens(int n) {
    vector<vector<string> > res;
    vector<int> pos(n, -1);
    size_t count = 0;
    solveNQueensDFS(pos, 0, res, count);
    cout << "count: " << count << endl;
    return res;
}

vector<int> spiralOrder1(vector<vector<int> > &matrix) {
    if (matrix.empty() || matrix[0].empty()) return {};
    int m = matrix.size(), n = matrix[0].size();
    vector<int> res;
    int c = m > n ? (n + 1) / 2 : (m + 1) / 2;
    int p = m, q = n;
    for (int i = 0; i < c; ++i, p -= 2, q -= 2) {
        for (int col = i; col < i + q; ++col)
            res.push_back(matrix[i][col]);
        for (int row = i + 1; row < i + p; ++row)
            res.push_back(matrix[row][i + q - 1]);
        if (p == 1 || q == 1) break;
        for (int col = i + q - 2; col >= i; --col)
            res.push_back(matrix[i + p - 1][col]);
        for (int row = i + p - 2; row > i; --row)
            res.push_back(matrix[row][i]);
    }
    return res;
}
vector<int> spiralOrder2(vector<vector<int>>& matrix) {
    if (matrix.empty() || matrix[0].empty()) return {};
    int m = matrix.size(), n = matrix[0].size();
    vector<int> res;
    int up = 0, down = m - 1, left = 0, right = n - 1;
    while (true) {
        for (int j = left; j <= right; ++j) res.push_back(matrix[up][j]);
        if (++up > down) break;
        for (int i = up; i <= down; ++i) res.push_back(matrix[i][right]);
        if (--right < left) break;
        for (int j = right; j >= left; --j) res.push_back(matrix[down][j]);
        if (--down < up) break;
        for (int i = down; i >= up; --i) res.push_back(matrix[i][left]);
        if (++left > right) break;
    }
    return res;
}

vector<Interval> mergeIntervals(vector<Interval>& intervals) {
    if (intervals.empty()) return {};
    sort(intervals.begin(), intervals.end(), [](Interval &a, Interval &b) {return a.start < b.start;});
    vector<Interval> res{intervals[0]};
    for (int i = 1; i < intervals.size(); ++i) {
        if (res.back().end < intervals[i].start) {
            res.push_back(intervals[i]);
        } else {
            res.back().end = max(res.back().end, intervals[i].end);
        }
    }
    return res;
}

int lengthOfLastWord(string s) {
    int right = s.size() - 1, res = 0;
    while (right >= 0 && s[right] == ' ') --right;
    while (right >= 0 && s[right] != ' ' ) {
        --right;
        ++res;
    }
    return res;
}

vector<vector<int> > subsets(vector<int> &S) {
    vector<vector<int> > res(1);
    sort(S.begin(), S.end());
    for (int i = 0; i < S.size(); ++i) {
        int size = res.size();
        for (int j = 0; j < size; ++j) {
            res.push_back(res[j]);
            res.back().push_back(S[i]);
        }
    }
    return res;
}

int removeDuplicates2(vector<int>& nums) {
    if (nums.size() <= 2) return nums.size();
    int index = 2;
    for (int i = 2; i < nums.size(); i++){
        if (nums[i] != nums[index - 2])
            nums[index++] = nums[i];
    }
    return index;
}

ListNode* removeDuplicatesList1(ListNode* head) {
    if (!head || !head->next) {
        return head;
    }
    ListNode* cur = head->next;
    ListNode* prev = head;
    while (cur) {
        if (prev->val == cur->val) {
            prev->next = cur->next;
            delete cur;
            cur = prev->next;
        } else {
            prev = cur;
            cur = cur->next;
        }
    }
    return head;
}
ListNode* removeDuplicatesList2(ListNode *head) {
    if (!head || !head->next) return head;

    ListNode* dummy = new ListNode(-1);
    dummy->next = head;
    ListNode* prev = dummy;
    while (prev->next) {
        ListNode* cur = prev->next;
        while (cur->next && cur->next->val == cur->val){
            auto* p = cur;
            cur = cur->next;
            delete p;
        }
        if (cur != prev->next) {
            prev->next = cur->next;
            delete cur;
        } else {
            prev = prev->next;  // after this line, prev != nullptr
            // or prev = cur;
        }
    }
    return dummy->next;
}

void testRemoveDuplicates() {
    std::list<int> datas = {1,1,2,3,3,};
    auto* head = createList2(datas);
    head = removeDuplicatesList2(head);
    printList(head);
}

ListNode* reverseBetween(ListNode* head, int m, int n) {
    if (!head || !head->next) {
        return head;
    }
    if (m < 1 || m >= n) {
        return head;
    }
    auto* cur = head;
    int count = 1;
    while (cur->next && count < m - 1) {
        cur = cur->next;
        count += 1;
    }
    if (!cur->next) { // length of list < m
        return head;
    }
    ListNode* prev = cur;
    ListNode* next;
    ListNode* last = cur->next;
    cur = cur->next;
    while (cur && count < n) {
        next = cur->next;
        cur->next = prev->next;
        prev->next = cur;
        cur = next;
        ++count;
    }
    last->next = next;
    return head;
}

void testReverseBetween() {
    std::list<int> datas = {1,2,3,4,5,};
    auto* head = createList2(datas);
    head = reverseBetween(head, 2, 8);
    printList(head);
}

ListNode *partitionList1(ListNode *head, int x) {
    if (!head || !head->next) {
        return head;
    }
    ListNode *dummy1 = new ListNode(-1);
    ListNode *dummy2 = new ListNode(-1);

    ListNode *last1 = dummy1;
    ListNode *last2 = dummy2;
    ListNode *cur = head;
    while (cur) {
        if (cur->val < x) {
            last1->next = cur;
            last1 = last1->next;
        } else {
            last2->next = cur;
            last2 = last2->next;
        }
        cur = cur->next;
    }
    last2->next = nullptr;
    last1->next = dummy2->next;
    return dummy1->next;
}


void testPartionList() {
    std::list<int> datas = {1,2,4,2,3,5,};
    auto* head = createList2(datas);
    head = partitionList1(head, 3);
    printList(head);
}

void setMatrixZeros1(vector<vector<int>>& data) {
    if (data.empty() || data[0].empty()) return;
    size_t m = data.size();
    size_t n = data[0].size();
    vector<size_t> rowZeros(m);
    vector<size_t> columnZeros(n);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (data[i][j] == 0) {
                rowZeros[i] = 1;
                columnZeros[j] = 1;
            }
        }
    }
    for (int i = 0; i < m; ++i) {
        if (rowZeros[i] == 1) {
            for (int j = 0; j < n; ++j) {
                data[i][j] = 0;
            }
        }
    }
    for (int j = 0; j < n; ++j) {
        if (columnZeros[j] == 1) {
            for (int i = 0; i < m; ++i) {
                data[i][j] = 0;
            }
        }
    }
}
void setMatrixZeros2(vector<vector<int>> &matrix) {
    if (matrix.empty() || matrix[0].empty()) return;
    int m = matrix.size(), n = matrix[0].size();
    bool rowZero = false, colZero = false;
    for (int i = 0; i < m; ++i) {
        if (matrix[i][0] == 0) colZero = true;
    }
    for (int i = 0; i < n; ++i) {
        if (matrix[0][i] == 0) rowZero = true;
    }
    for (int i = 1; i < m; ++i) {
        for (int j = 1; j < n; ++j) {
            if (matrix[i][j] == 0) {
                matrix[0][j] = 0;
                matrix[i][0] = 0;
            }
        }
    }
    for (int i = 1; i < m; ++i) {
        for (int j = 1; j < n; ++j) {
            if (matrix[0][j] == 0 || matrix[i][0] == 0) {
                matrix[i][j] = 0;
            }
        }
    }
    if (rowZero) {
        for (int i = 0; i < n; ++i) matrix[0][i] = 0;
    }
    if (colZero) {
        for (int i = 0; i < m; ++i) matrix[i][0] = 0;
    }
}

void testZeroMatrix() {
    vector<vector<int>> data = {
            {0,1,2,0},
            {3,4,5,2},
            {1,3,1,5},
    };
    setMatrixZeros2(data);
    cout << data << endl;
}

int largestRectangleArea(vector<int> &height) {
    int res = 0;
    stack<int> s;
    height.push_back(0);
    for (int i = 0; i < height.size(); ++i) {
        if (s.empty() || height[s.top()] <= height[i]) s.push(i);
        else {
            int tmp = s.top();
            s.pop();
            res = max(res, height[tmp] * (s.empty() ? i : (i - s.top() - 1)));
            --i;
        }
    }
    return res;
}
int maximalRectangle1(vector<vector<int>> &matrix) {
    int res = 0;
    vector<int> height;
    for (int i = 0; i < matrix.size(); ++i) {
        height.resize(matrix[i].size());
        for (int j = 0; j < matrix[i].size(); ++j) {
            height[j] = (matrix[i][j] == 0 ? 0 : (1 + height[j]));
        }
        res = max(res, largestRectangleArea(height));
    }
    return res;
}
int maximalRectangle2(vector<vector<int>> &matrix) {
    if (matrix.empty() || matrix[0].empty()) return 0;
    int res = 0, m = matrix.size(), n = matrix[0].size();
    // 必须多一列，否则最后一列有效数据不会被计算
    vector<int> h(n + 1, 0);
    for (int i = 0; i < m; ++i) {
        stack<int> s;
        for (int j = 0; j < n + 1; ++j) {
            if (j < n) {
                if (matrix[i][j]) ++h[j];
                else h[j] = 0;
            }
            while (!s.empty() && h[s.top()] >= h[j]) {
                // while循环一次都不执行的情况下，只积累栈，栈顶元素对应的高度逐步增加
                // 每次遇到h[j]<=栈中元素时，则计算栈中保存的大于当前h[j]的所有元素的面积
                int cur = s.top(); s.pop();
                res = max(res, h[cur] * (s.empty() ? j : (j - s.top() - 1)));
                // 此时s.top()保存的是j的上一个元素的上一个元素，即j - s.top()==2
                // 因为j的上一个元素已经出栈给cur
            }
            s.push(j);
        }
    }
    return res;
}
void testMaximalRectangle() {
    vector<vector<int>> data = {
            {1, 1, 0, 0, 1},
            {0, 1, 0, 0, 1},
            {0, 0, 1, 1, 1},
            {0, 0, 1, 1, 1},
            {0, 0, 0, 0, 1}
    };
    cout << "maximalRectangle: " << maximalRectangle1(data) << endl;


}

string minWindow(string s, string t) {
    string res = "";
    unordered_map<char, int> letterCnt;
    int left = 0, cnt = 0, minLen = INT32_MAX;
    for (char c : t) ++letterCnt[c];
    for (int i = 0; i < s.size(); ++i) {
        if (--letterCnt[s[i]] >= 0) ++cnt;
        while (cnt == t.size()) {
            // 窗口内的有效字符数已经足够，可以右移left边缘
            if (minLen > i - left + 1) {
                minLen = i - left + 1;
                res = s.substr(left, minLen);
            }
            if (++letterCnt[s[left]] > 0) --cnt;
            // 窗口内的有效字符数目已经不足，窗口left边缘不能继续右移运算，跳出while循环
            ++left;
        }
    }
    return res;
}

int largestRectangleArea1(vector<int> &height) {
    int res = 0;
    for (int i = 0; i < height.size(); ++i) {
        if (i + 1 < height.size() && height[i] <= height[i + 1]) {
            // 找一段连续上升的区间
            continue;
        }
        int minH = height[i];
        for (int j = i; j >= 0; --j) {
            // 从最高点连续计算，最高1块，最高2块，最高3块的可能面积；
            minH = min(minH, height[j]);
            int area = minH * (i - j + 1);
            res = max(res, area);
        }
    }
    return res;
}

// A的长度是m + n
void mergeArrays(int A[], int m, int B[], int n) {
    int count = m + n - 1;
    --m; --n;
    while (m >= 0 && n >= 0) A[count--] = A[m] > B[n] ? A[m--] : B[n--];
    while (n >= 0) A[count--] = B[n--];
    // 不需考虑m>=0的情况，因为本身就要放在A中
}



int main() {
    //testReverseKGroup();
    //solveNQueens(4);
    //testRemoveDuplicates();
    //testZeroMatrix();
    //testReverseBetween();
    //testPartionList();
    //testMaximalRectangle();




    return 0;
}



