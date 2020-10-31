
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <array>
#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

// 替换空格为%20
void replaceSpace1(char* str) {
    if (!str) {
        return;
    }

    int original_length = 0;            //原始长度
    int number_blank = 0;                //空格数
    while (str[original_length++] != '\0') {                //遍历字符串
        if (str[original_length] == ' ') {
            ++number_blank;                //遇到空格+1
        }
    }
    /*new_length为把空格替换成'%20'之后的长度*/
    int new_length = original_length + 2 * number_blank;

    int index_original = original_length;    //原始字符串末尾索引值
    int index_new = new_length;                //计算长度后的字符串末尾索引值

    /*index_original指针开始向前移动，如果遇到空格，替换成'%20'，否则进行复制操作*/
    while (index_original >= 0) {
        if (str[index_original] == ' ') {
            str[index_new--] = '0';
            str[index_new--] = '2';
            str[index_new--] = '%';
        } else {
            str[index_new--] = str[index_original];
        }
        --index_original;
    }
}

char* delSubStr(char* str, const char* subStr) {
    if (!str || !subStr) {
        return nullptr;
    }
    size_t prev = 0;
    size_t pos = 0;
    char* start = str;
    while (*start) {
        while (start[pos] && subStr[pos] && (start[pos] == subStr[pos])) {
            ++pos;
        }
        if (!subStr[pos]) {
            start += pos;
            pos = 0;
        } else {
            str[prev++] = *start++;
            pos = 0;
        }
    }
    str[prev++] = '\0';

    return str;
}

void testReplaceSpace() {
    char str[256] = "a b c";

    replaceSpace1(str);
    cout << "str: " << str << endl;

    char str2[64] = "cdabcdeab";
    char subStr[] = "abc";
    char* strEnd = delSubStr(str2, subStr);
    cout << "str2: " << strEnd << std::endl;

}

// 求子串
const char* strstr2(const char* str, const char* substr) {
    if (!str || !substr) {
        return nullptr;
    }
    int i = 0;
    while (str[i] != '\0') {
        int k = i;
        int j = 0;
        while (str[k] && substr[j] && (str[k] == substr[j])) {
            // (str[k++] == substr[j++])这种方式有问题，尽量少用++;
            ++k;
            ++j;
        }
        if (!substr[j]) {
            return str + i;
        }
        if (!str[i]) {
            return nullptr;
        }
        ++i;
    }
    return nullptr;
}

void testStrstr2() {
    //char str[] = "abcabcdabcd";
    //char str[] = "abcabcabcd";
    char str[] = "abcdabcabcd";
    char substr[] = "abcd";
    const char* p = strstr2(str, substr);
    cout << "substr: " << p << endl;
}

// 字符串的全排列
class Solution2 {
public:
    /* 递归实现字符串全排列
     * 每次调用处理len - k个字符的全排列
     * 每次调用这个函数，k（不含k）之前的字符原样输出
     * 递归的实现是深度优先
     * */
    static void permutex_ation1(char data[], const size_t k, size_t last) {//非字典序
        if (k == last) {
            for (size_t i = 0; i <= last; ++i)
                cout << data[i] << ' ';
            cout << endl;
        } else {
            for (size_t i = k; i <= last; i++) {
                std::swap(data[k], data[i]);   //交换
                permutex_ation1(data, k + 1, last);
                std::swap(data[k], data[i]);
            }
        }
    }

    static void permutex_ation2(char data[], const size_t k, size_t last) {//字典序

        if (k == last) {
            for (size_t i = 0; i <= last; ++i)
                cout << data[i] << ' ';
            cout << endl;
        } else {
            for (size_t i = k; i <= last; ++i) {
                size_t tmp = data[i];
                for (size_t j = i; j > k; --j) {
                    data[j] = data[j - 1];
                }
                data[k] = tmp;
                permutex_ation2(data, k + 1, last);
                tmp = data[k];
                for (size_t j = k; j < i; ++j) {
                    data[j] = data[j + 1];
                }
                data[i] = tmp;
            }
        }
    }


    static void permutex_ation3(string str, vector<string> &result) {
        //判断输入
        if (str.length() == 0) {
            return;
        }
        permutex_ationCore(str, 0, result);
        //对结果进行排序
        sort(result.begin(), result.end());
    }

private:
    static void permutex_ationCore(string str, int begin, vector<string> &result) {
        //递归结束的条件：第一位和最后一位交换完成
        if (begin == str.length()) {
            result.push_back(str);
            return;
        }
        for (int i = begin; i < str.length(); ++i) {
            //如果字符串相同，则不交换
            if (i != begin && str[i] == str[begin]) {
                continue;
            }
            //位置交换
            swap(str[begin], str[i]);
            //递归调用，前面begin+1的位置不变，后面的字符串全排列
            permutex_ationCore(str, begin + 1, result);
        }
    }
};

void testPermutex_ation() {
    const size_t kSize = 3;
    char data[kSize];
    for (size_t i = 0; i < kSize; ++i) {
        data[i] = 'a' + i;
    }
    Solution2::permutex_ation1(data, 0, kSize - 1);
    cout << "\n\nnow data:\n";
    for (size_t i = 0; i < kSize; ++i)
        cout << data[i] << ' ';
    cout << endl;
}


/* Reverse Words in a String
 * Given s = "the sky is blue",
 * return "blue is sky the".
 * delete leading and trailing spaces
 * Reduce multiple spaces to a single space
 *
 * "   the sky is blue    "
 */

void reverse(string &s, size_t begin, size_t end) {
    assert(begin <= end && end <= s.size());
    while (begin < end) {
        std::swap(s[begin++], s[--end]);
    }
}

void reverseWords1(string &s) {
    size_t idx = 0, n = s.size();
    reverse(s, 0, s.size());
    for (int i = 0; i < n; ++i) {
        if (s[i] != ' ') {
            if (idx != 0) s[idx++] = ' ';
            int j = i;
            while (i < n && s[i] != ' ') s[idx++] = s[i++];
            reverse(s, idx - (i - j), idx);
        }
    }
    s.resize(idx);
}

void testReverseWords1() {
    //string s = "the sky is blue";
    string s = "   the   sky is   blue  ";
    cout << "Before reverseWords: " << s << endl;
    reverseWords1(s);
    cout << "After reverseWords: " << s << endl;
}

// abb s
// bba t
string shortestPalindrome1(string s) {
    string t = s;
    reverse(t.begin(), t.end());
    int n = s.size(), i = 0;
    for (i = n; i > 0; --i) {
        if (s.substr(0, i) == t.substr(n - i)) {
            break;
        }
    }
    return t.substr(0, n - i) + s;
}

// bacca
string longestPalindrome1(string s) {
    if (s.empty()) return "";
    vector<vector<int>> dp(s.size(), vector<int>(s.size(), 0));
    int left = 0, right = 0, len = 0;

    //右上角，行号小于列号
    for (int i = 0; i < s.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            dp[j][i] = (s[i] == s[j] && (i - j < 2 || dp[j + 1][i - 1]));
            if (dp[j][i] && len < i - j + 1) {
                len = i - j + 1;
                left = j;
                right = i;
            }
        }
        dp[i][i] = 1;
    }
    return s.substr(left, right - left + 1);
}


void leftRotateString(string &str, const size_t kSize) {
    if (str.empty() || kSize == 0) {
        return;
    }
    const size_t leftSize = kSize % str.size();
    if (leftSize == 0) return;
    std::reverse(str.begin(), str.begin() + leftSize);
    std::reverse(str.begin() + leftSize, str.end());
    std::reverse(str.begin(), str.end());
}

void rightRotateString(string &str, const size_t kSize) {
    if (str.empty() || kSize == 0) {
        return;
    }
    const size_t leftSize = str.size() - kSize % str.size();
    if (leftSize == 0) return;
    std::reverse(str.begin(), str.begin() + leftSize);
    std::reverse(str.begin() + leftSize, str.end());
    std::reverse(str.begin(), str.end());
}

void testRotateString() {
    string str("abcdefg");
    rightRotateString(str, 2);
    cout << "leftRotateString: " << str << endl;
}

string Manacher(string s) {
    // Insert '#'
    string t = "$#";
    for (int i = 0; i < s.size(); ++i) {
        t += s[i];
        t += "#";
    }
    // Process t
    vector<int> p(t.size(), 0);
    int mx = 0; // 最长回文串的下一个位置index
    int id = 0; // 最长回文串的中心index
    int resLen = 0, resCenter = 0;
    //string s1 = "abbab";
    //string t = "$#a#b#b#a#b#";
    //   i 0 1 2 3 4 5....
    //p[i] 0 1 2 1 2 5....
    for (int i = 1; i < t.size(); ++i) {
        p[i] = mx > i ? min(p[2 * id - i], mx - i) : 1;
        // 当前i的映像j=2 * id - i，以i为中心和以j为中心的p[i]和p[j]
        // 一定相等（不考虑mx-i），因为二者关于id对称，
        // i为中心的p[i]的字母数目和j为中心的p[j]的字母数目相等；
        // 如果mx-i < p[j]，说明以i为中心的p[i]达不到p[j]那么大，因为右侧已经到头；
        while (t[i + p[i]] == t[i - p[i]]) ++p[i];
        if (mx < i + p[i]) {
            mx = i + p[i];
            id = i;
        }
        if (resLen < p[i]) {
            resLen = p[i];
            resCenter = i;
        }
        cout << "i: " << i << ", p[i]: " << p[i] << ", mx: " << mx << ", id: " << id << endl;
    }
    cout << "resLen: " << resLen << ", resCenter: " << resCenter << endl;
    return s.substr((resCenter - resLen) / 2, resLen - 1);
}

char* getStr1() {
    int a = 1;
    printf("getStr1: &a: %p\n", &a); // 0xffffcbcc

    static char str[128];
    strcpy(str, "Hello");
    printf("getStr1: str: %p\n", str);
    //printf("getStr1: str: %p\n", &str); // 同上
    printf("getStr1: str: %s\n", str);

    return str;
}

char* getStr2() {
    static char* str = (char*) malloc(128 * sizeof(char));
    strcpy(str, "Hello");
    printf("getStr2: str: %p\n", str);
    printf("getStr2: str: %s\n", str);
    printf("getStr2: &str: %p\n", &str);
    return str;
}

void test() {
    char* str1 = getStr1();
    char* str2 = getStr2();

    printf("str1: %p\n", str1);
    printf("str2: %p\n", str2);

    printf("str1: %s\n", str1);
    printf("str2: %s\n", str2);

}

int main() {
    testReplaceSpace();
    //testPermutex_ation();
    //cout << "shortestPalindrome: " << shortestPalindrome1("abb") << endl;
    // testReverseWords1();
    //testStrstr2();

    //string s1 = "abbab";
    //cout << Manacher(s1) << endl;
    //string s2 = "abbabb";
    //cout << Manacher(s2) << endl;
    //string s = "waabwswfd";
    //cout << Manacher(s) << endl;

    //test();

}










