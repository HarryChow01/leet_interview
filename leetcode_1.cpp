
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <stack>
#include <unordered_map>
#include <algorithm>
#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

template<typename T>
ostream& operator<<(ostream& out, vector<T>& data) {
    for (auto& item : data) {
        out << " " << item;
    }
    out << endl;
    return out;
}

template<typename T>
ostream& operator<<(ostream& out, list<T>& data) {
    for (auto& item : data) {
        out << " " << item;
    }
    out << endl;
    return out;
}

vector<int> twoSum(vector<int>& nums, int target) {
    map<int, int> myMap;
    vector<int> result;
    for (int i = 0; i < nums.size(); ++i) {
        if (myMap.find(target - nums[i]) == myMap.end()) {
            myMap[nums[i]] = i;
        } else {
            result = {myMap[target - nums[i]], i};
            break;
        }
    }
    return result;
}

void testTwoSum() {
    vector<int> data = {2, 5, 8, 7};
    int target = 9;
    vector<int> result = twoSum(data, target);
    cout << "a1: " << result[0] << ", a2: " << result[1] << endl;
}

// c++ 中，如何判断一个int整数的逆序，比如说157，逆置751，是溢出的？
// 用int64_t类型记录，然后看看是不是大于int32_t的最大是否小于int32_t的最小。
int32_t reverseInt(int32_t x) {
    int64_t result = 0;
    int64_t curNum = std::abs((int64_t)x);
    while (curNum > 0) {
        result = result * 10 + curNum % 10;
        curNum /= 10;
    }
    result = (x >= 0) ? result : -result;
    //if (result != (int32_t) result) { // OK
    if (result > INT32_MAX || result < INT32_MIN) {
        return 0;
    } else {
        return (int32_t)result;
    }
}

int myAtoi(string str) {
    int64_t sum = 0;

    int i = 0;
    while ((i < str.size()) && (isspace(str[i]))) {
        ++i;
    }
    if (i == str.size()) {
        return 0;
    }

    //是否为负数
    bool negative = false;
    if (str[i] == '+') {
        ++i;
    } else if (str[i] == '-') {
        negative = true;
        ++i;
    }

    while ((i < str.size()) && isdigit(str[i])) {
        sum = sum * 10 + (str[i++] - '0');
        // 溢出
        if (negative && sum > int64_t(INT32_MAX) + 1) {
            return INT32_MIN;
        } else  if (!negative && sum > INT32_MAX) {
            return INT32_MAX;
        }
    }

    while (i < str.size() && isspace(str[i])) {
        ++i;
    }
    // 输入数据错误
    if (i < str.size()) {
        if (negative) {
            return INT32_MIN;
        } else {
            return INT32_MAX;
        }
    }

    return negative ? int(-sum) : int(sum);
}

ListNode* addTwoNumbers(ListNode *l1, ListNode *l2) {
    ListNode *res = new ListNode(-1);
    ListNode *cur = res;
    int carry = 0;
    while (l1 || l2) {
        int n1 = l1 ? l1->val : 0;
        int n2 = l2 ? l2->val : 0;
        int sum = n1 + n2 + carry;
        carry = sum / 10;
        cur->next = new ListNode(sum % 10);
        cur = cur->next;
        if (l1) l1 = l1->next;
        if (l2) l2 = l2->next;
    }
    if (carry) cur->next = new ListNode(1);
    return res->next;
}


bool isParenthesesValid(const string& s) {
    if (s.empty() || s.size() % 2 == 1) {
        return false;
    }
    map<char, char> myMap = {
        {'(', ')'},
        {'[', ']'},
        {'{', '}'},
    };

    //bool contain = myMap['a'] == 'b';
    //cout << contain << endl;
    set<char> mySet = {')',']','}'};
    stack<char> stack;
    for (auto ch : s) {
        if (myMap.count(ch) >= 1) {
            stack.push(ch);
        } else {
            if (mySet.count(ch) == 0) {
                return false;
            }
            if (!stack.empty() && myMap[stack.top()] == ch) {
                stack.pop();
            } else {
                return false;
            }
        }
    }
    return stack.empty();
}

vector<vector<int>> threeSum1(vector<int>& nums) {
    vector<vector<int>> res;
    sort(nums.begin(), nums.end());
    if (nums.empty() || nums.back() < 0 || nums.front() > 0) return {};
    for (int k = 0; k < nums.size(); ++k) {
        if (nums[k] > 0) break;
        if (k > 0 && nums[k] == nums[k - 1]) continue;
        int target = 0 - nums[k];
        int i = k + 1, j = nums.size() - 1;
        while (i < j) {
            if (nums[i] + nums[j] == target) {
                res.push_back({nums[k], nums[i], nums[j]});
                while (i < j && nums[i] == nums[i + 1]) ++i;
                while (i < j && nums[j] == nums[j - 1]) --j;
                ++i; --j;
            } else if (nums[i] + nums[j] < target) ++i;
            else --j;
        }
    }
    return res;
}

vector<vector<int>> threeSum2(vector<int>& nums) {
    set<vector<int>> res;
    sort(nums.begin(), nums.end());
    if (nums.empty() || nums.back() < 0 || nums.front() > 0) return {};
    for (int k = 0; k < nums.size(); ++k) {
        if (nums[k] > 0) break;
        int target = 0 - nums[k];
        int i = k + 1, j = nums.size() - 1;
        while (i < j) {
            if (nums[i] + nums[j] == target) {
                res.insert({nums[k], nums[i], nums[j]});
                while (i < j && nums[i] == nums[i + 1]) ++i;
                while (i < j && nums[j] == nums[j - 1]) --j;
                ++i; --j;
            } else if (nums[i] + nums[j] < target) ++i;
            else --j;
        }
    }
    return vector<vector<int>>(res.begin(), res.end());
}
void test3sum() {
    vector<int> data = {-1, 0, 1, 2, -1, -4};
    auto result = threeSum2(data);
    for (auto& item : result) {
        cout << item;
    }

}
int threeSumClosest(vector<int>& nums, int target) {
    int closest = nums[0] + nums[1] + nums[2];
    int diff = abs(closest - target);
    sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size() - 2; ++i) {
        int left = i + 1, right = nums.size() - 1;
        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            int newDiff = abs(sum - target);
            if (diff > newDiff) {
                diff = newDiff;
                closest = sum;
            }
            if (sum < target) ++left;
            else --right;
        }
    }
    return closest;
}
void test3SumClosest() {
    vector<int> data = {-1,2,1,-4};
    auto result = threeSumClosest(data, 1);
    cout << "test3SumClosest: " << result << endl;

}
vector<vector<int>> fourSum(vector<int> &nums, int target) {
    set<vector<int>> res;
    sort(nums.begin(), nums.end());
    for (int i = 0; i < int(nums.size() - 3); ++i) {
        for (int j = i + 1; j < int(nums.size() - 2); ++j) {
            if (j > i + 1 && nums[j] == nums[j - 1]) continue;
            int left = j + 1, right = nums.size() - 1;
            while (left < right) {
                int sum = nums[i] + nums[j] + nums[left] + nums[right];
                if (sum == target) {
                    vector<int> out{nums[i], nums[j], nums[left], nums[right]};
                    res.insert(out);
                    ++left; --right;
                } else if (sum < target) ++left;
                else --right;
            }
        }
    }
    return vector<vector<int>>(res.begin(), res.end());
}


int longestSubstring1(string s) {
    int res = 0, left = -1, n = s.size();
    map<int, int> m;
    for (int i = 0; i < n; ++i) {
        // 如果某个字符找到重复，则left赋值为，重复字符的上一个位置，最大长度从此位置的下一个开始计算
        if (m.count(s[i]) && m[s[i]] > left) {
            left = m[s[i]];
        }
        m[s[i]] = i;
        res = max(res, i - left);
    }
    return res;
}

int longestSubstring2(string s) {
    vector<int> m(128, -1);
    int res = 0, left = -1;
    for (int i = 0; i < s.size(); ++i) {
        left = max(left, m[s[i]]);
        m[s[i]] = i;
        res = max(res, i - left);
    }
    return res;
}

void testLongestSubstr() {
    string str("abcadefbcbb");
    cout << "longest substr: " << longestSubstring2(str) << endl;

}

int findKth2Array(vector<int>& nums1, int i, vector<int>& nums2, int j, int k) {
    if (i >= nums1.size()) return nums2[j + k - 1];
    if (j >= nums2.size()) return nums1[i + k - 1];
    if (k == 1) return min(nums1[i], nums2[j]);
    int midVal1 = (i + k / 2 - 1 < nums1.size()) ? nums1[i + k / 2 - 1] : INT32_MAX;
    int midVal2 = (j + k / 2 - 1 < nums2.size()) ? nums2[j + k / 2 - 1] : INT32_MAX;
    if (midVal1 < midVal2) {
        return findKth2Array(nums1, i + k / 2, nums2, j, k - k / 2);
    } else {
        return findKth2Array(nums1, i, nums2, j + k / 2, k - k / 2);
    }
}
double findMedian2Arrays(vector<int>& nums1, vector<int>& nums2) {
    int m = nums1.size(), n = nums2.size(), left = (m + n + 1) / 2, right = (m + n + 2) / 2;
    return (findKth2Array(nums1, 0, nums2, 0, left) + findKth2Array(nums1, 0, nums2, 0, right)) / 2.0;
}
void testMedian() {
    vector<int> nums1 = {1, 3};
    vector<int> nums2 = {2, 4};
    cout << "findMedian2Arrays:" << findMedian2Arrays(nums1, nums2) << endl;
}

ListNode* removeNthFromEnd(ListNode* head, size_t n) {
    if (!head || !head->next || n == 0) return nullptr;
    ListNode *pre = head, *cur = head;
    for (size_t i = 0; i < n && cur != nullptr; ++i) cur = cur->next;
    if (!cur) return head->next;
    while (cur->next) {
        cur = cur->next;
        pre = pre->next;
    }
    pre->next = pre->next->next;
    return head;
}

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode *dummy = new ListNode(-1), *cur = dummy;
    while (l1 && l2) {
        if (l1->val < l2->val) {
            cur->next = l1;
            l1 = l1->next;
        } else {
            cur->next = l2;
            l2 = l2->next;
        }
        cur = cur->next;
    }
    cur->next = l1 ? l1 : l2;
    return dummy->next;
}

void searchPalindrome(string s, int left, int right, int& start, int& maxLen) {
    while (left >= 0 && right < s.size() && s[left] == s[right]) {
        --left; ++right;
    }
    if (maxLen < right - left - 1) {
        start = left + 1;
        maxLen = right - left - 1;
    }
}
string longestPalindrome1(string s) {
    if (s.size() < 2) return s;
    int n = s.size(), maxLen = 0, start = 0;
    for (int i = 0; i < n - 1; ++i) {
        searchPalindrome(s, i, i, start, maxLen);
        searchPalindrome(s, i, i + 1, start, maxLen);
    }
    return s.substr(start, maxLen);
}
string longestPalindrome2(string s) {
    if (s.size() < 2) return s;
    int n = s.size(), maxLen = 0, start = 0;
    for (int i = 0; i < n;) {
        if (n - i <= maxLen / 2) break;
        int left = i, right = i;
        while (right < n - 1 && s[right + 1] == s[right]) ++right;
        i = right + 1;
        while (right < n - 1 && left > 0 && s[right + 1] == s[left - 1]) {
            ++right; --left;
        }
        if (maxLen < right - left + 1) {
            maxLen = right - left + 1;
            start = left;
        }
    }
    return s.substr(start, maxLen);
}
void testLongestPalindrome() {
    string s("aaalevelbbb");
    cout << "palindrome: " << longestPalindrome2(s) << endl;

}

string zigZagConvert(string s, int nRows) {
    if (nRows <= 1) return s;
    string res;
    int size = 2 * nRows - 2;
    for (int i = 0; i < nRows; ++i) {
        for (int j = i; j < s.size(); j += size) {
            res += s[j];
            int tmp = j + size - 2 * i;
            if (i != 0 && i != nRows - 1 && tmp < s.size()) res += s[tmp];
        }
    }
    return res;
}
void testZigZagConvert() {
    string str("0123456789ABCDEF");
    cout << "zigzag string: " << zigZagConvert(str, 4) << endl;

}

bool isPalindrome(int x) {
    if (x < 0) return false;
    int div = 1;
    while (x / div >= 10) div *= 10;
    while (x > 0) {
        int left = x / div;
        int right = x % 10;
        if (left != right) return false;
        x = (x % div) / 10;
        div /= 100;
    }
    return true;
}

bool isReMatch(string s, string p) {
    if (p.empty()) return s.empty();
    if (p.size() == 1) {
        return (s.size() == 1 && (s[0] == p[0] || p[0] == '.'));
    }
    if (p[1] != '*') {
        if (s.empty()) return false;
        return (s[0] == p[0] || p[0] == '.') && isReMatch(s.substr(1), p.substr(1));
    }
    while (!s.empty() && (s[0] == p[0] || p[0] == '.')) {
        if (isReMatch(s, p.substr(2))) return true;
        s = s.substr(1);
    }
}

// 容器装最多水，图示：https://zhuanlan.zhihu.com/p/29776216
int maxContain(vector<int>& height) {
    int res = 0, i = 0, j = height.size() - 1;
    while (i < j) {
        res = max(res, min(height[i], height[j]) * (j - i));
        height[i] < height[j] ? ++i : --j;
    }
    return res;
}
void testMaxContain() {
    vector<int> heights = {1,8,6,2,5,4,8,3,7};
    cout << "maxWater: " << maxContain(heights) << endl;
}

string intToRoman(int num) {
    string res = "";
    char roman[] = {'M', 'D', 'C', 'L', 'X', 'V', 'I'};
    int value[] = {1000, 500, 100, 50, 10, 5, 1};

    for (int n = 0; n < 7; n += 2) {
        int x = num / value[n];
        if (x < 4) {
            for (int i = 1; i <= x; ++i) res += roman[n];
        } else if (x == 4) res += roman[n] + roman[n - 1];
        else if (x > 4 && x < 9) {
            res += roman[n - 1];
            for (int i = 6; i <= x; ++i) res += roman[n];
        }
        else if (x == 9) res += roman[n] + roman[n - 2];
        num %= value[n];
    }
    return res;
}

int romanToInt(string s) {
    int res = 0;
    unordered_map<char, int> m{{'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}};
    for (int i = 0; i < s.size(); ++i) {
        int val = m[s[i]];
        if (i == s.size() - 1 || m[s[i+1]] <= m[s[i]]) res += val;
        else res -= val;
    }
    return res;
}

string longestCommonPrefix(vector<string>& strs) {
    if (strs.empty()) return "";
    string res = "";
    for (int j = 0; j < strs[0].size(); ++j) {
        char c = strs[0][j];
        for (int i = 1; i < strs.size(); ++i) {
            if (j >= strs[i].size() || strs[i][j] != c) {
                return res;
            }
        }
        res.push_back(c);
    }
    return res;
}
void testLongestCommonPrefix() {
    vector<string> strs = {"flower","flow","flight"};
    cout << "longestCommonPrefix: " << longestCommonPrefix(strs) << endl;
}

void letterCombinationsDFS(string digits, string dict[], int level, string out, vector<string> &res) {
    if (level == digits.size()) {res.push_back(out); return;}
    string str = dict[digits[level] - '0'];
    for (int i = 0; i < str.size(); ++i) {
        letterCombinationsDFS(digits, dict, level + 1, out + string(1, str[i]), res);
    }
}
vector<string> letterCombinations1(string digits) {
    if (digits.empty()) return {};
    vector<string> res{""}; // 不能是空
    string dict[] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    for (int i = 0; i < digits.size(); ++i) {
        vector<string> t;
        string str = dict[digits[i] - '0'];
        for (int j = 0; j < str.size(); ++j) {
            for (string s : res) t.push_back(s + str[j]);
        }
        res = t;
    }
    return res;
}
vector<string> letterCombinations2(string digits) {
    if (digits.empty()) return {};
    for (auto& ch : digits) {   // digits能有0或1，因为是空
        if (ch < '2') {
            return {};
        }
    }
    vector<string> res;
    string dict[] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    letterCombinationsDFS(digits, dict, 0, "", res);
    return res;
}
void testLetterCombinations() {
    string digits("356");
    auto strs = letterCombinations1(digits);
    cout << "strs: ";
    for (auto& str : strs) {
        cout << " " << str;
    }
    cout << endl;
}

void generateParenthesisDFS(int left, int right, string out, vector<string> &res) {
    if (left > right) return;
    if (left == 0 && right == 0) res.push_back(out);
    else {
        if (left > 0) generateParenthesisDFS(left - 1, right, out + '(', res);
        if (right > 0) generateParenthesisDFS(left, right - 1, out + ')', res);
    }
}
vector<string> generateParenthesis(int n) {
    vector<string> res;
    generateParenthesisDFS(n, n, "", res);
    return res;
}

ListNode *mergeKLists(vector<ListNode *> &lists) {
    if (lists.size() == 0) return NULL;
    int n = lists.size();
    while (n > 1) {
        int k = (n + 1) / 2;
        for (int i = 0; i < n / 2; ++i) {
            lists[i] = mergeTwoLists(lists[i], lists[i + k]);
        }
        n = k;
    }
    return lists[0];
}

ListNode* swapPairs(ListNode* head) {
    ListNode *dummy = new ListNode(-1), *pre = dummy;
    dummy->next = head;
    while (pre->next && pre->next->next) {
        ListNode *t = pre->next->next;
        pre->next->next = t->next;
        t->next = pre->next;
        pre->next = t;
        pre = t->next;
    }
    return dummy->next;
}


int main() {
    //testTwoSum();
    //cout << reverseInt(-123) <<endl;
    //cout << myAtoi("123") << endl;
    //cout << isParenthesesValid("{}[()]") << endl;
    //test3sum();
    //testLongestSubstr();
    //testMedian();
    //testLongestPalindrome();
    //testZigZagConvert();
    //cout << "isPalindrome: " << isPalindrome(1221) << endl;
    //testMaxContain();
    //cout << "intToRoman: " << intToRoman(1437) << endl; // "MCDXXXVII"
    //cout << "romanToInt: " << romanToInt("MCMXCIV") << endl;   //
    //testLongestCommonPrefix();
    //test3SumClosest();
    testLetterCombinations();



    return 0;
}

