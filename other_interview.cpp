
#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>

using namespace std;

//优化方法http://blog.csdn.net/xiaobo620/article/details/7488827


/*
 * 数值问题：全是0和全是1的问题：https://blog.csdn.net/fuhuixin7497/article/details/78037265
 * x |= (x + 1);    一次去掉一个0
 */


//斐波那契数列
// F(1)=1，F(2)=1, F(n)=F(n-1)+F(n-2)
const int32_t kSize = 1024;
int fibTable[kSize] = {};
// 循环法，O(n)
int32_t fib1(const int32_t n) {
    if (n == 0) return 0;
    if (n == 1 || n == 2) return 1;
    int32_t a = 1;
    int32_t b = 1;
    for (int32_t i = 3; i <= n; ++i) {
        int32_t f2 = a + b;
        a = b;
        b = f2;
    }
    return b;
}
// 查表法
int32_t fib2(const int32_t n) {
    if (n == 0) return 0;
    if (n == 1 || n == 2) {
        fibTable[n] = 1;
        return 1;
    }
    if (fibTable[n] > 0) {
        return fibTable[n];
    } else {
        fibTable[n] = fib2(n - 1) + fib2(n - 2);
        return fibTable[n];
    }
}

void count_0_1() {

    // 统计二进制位0的个数
    int x0 = 0xfffafff0; // x0（1111 1111 1111 1010 1111 1111 1111 0000）
    int count0 = 0;
    while (x0 + 1) {
        count0++;
        x0 |= (x0 + 1);
    }
    cout << "count0: " << count0 << endl;

    // 统计二进制位1的个数
    int x1 = 0xfffafff0; // x1（1111 1111 1111 1010 1111 1111 1111 0000）
    int count1 = 0;
    while (x1) {
        count1++;
        x1 &= (x1 - 1);
    }
    cout << "count1: " << count1 << endl;
}
void DeleteSpace(char* str);
void TestDeleteSpace();
void DeleteSpace(char* src) {
    const int len = strlen(src);
    int i = 0;
    if(!src)
        return;

    while(i < len && src[i]!= ' ') {
        i++;
    }
    int j = i;

    while(i < len) {
        if(src[i]!= ' ') {
            src[j++] = src[i];
        }
        i++;
    }
    src[j] = '\0';
}

void TestDeleteSpace() {
    char src[] = "a b c d ";
    printf("%d\n",strlen(src));
    DeleteSpace(src);
    printf("%d\n",strlen(src));
    printf("%s\n",src);
}


void * memcpy(void *dest, const void *src, size_t count)
{
    if (dest == NULL || src == NULL)
          return NULL;
    char *pdest = static_cast <char*>(dest);
    const char *psrc  = static_cast <const char*>(src);
    
    if (pdest > psrc && pdest < psrc + count)
    {
        for (size_t i = count -1; i != -1; --i)
        {
                pdest[i] = psrc[i];
        }
    }
    else
    {
        for (size_t i= 0; i < count; i++)
        {
                pdest[i] = psrc[i];
        }
    }
    
    return dest;
}

#if 0
int main()
{
    char data[] = "aaabbb";
    cout << "data : " <<  data << endl;
    memcpy(data, data + 3, 3);

    cout << "data : " <<  data << endl;
}

#endif

char * DelSpace(char * data)
{
    if (!data || *data == '\0')
    {
        return nullptr;
    }
    char *p = data;
    char *q = data;
    while(*q != '\0')
    {
        if (*q != ' ')
        {
            *p++ = *q;
        }
        q++;
    }
    *p = '\0';
    return data;
}

#if 0
int main()
{
    char data[] = "  a a abbb ";
    DelSpace(data);
    cout << "data : " <<  data << endl;
}

#endif

//不使用加减乘除实现两个数相加
int add(int a, int b){
    if (b == 0) return a;
    else
        return add(a ^ b, (a & b) << 1);
    //本语句，第一个参数是a和b和的进位，表示前面的初始调用参数a和b有几位是需要进位的且进位的位置已固定，
    //因为只有两位同为1的位才会产生进位，第二参数a^b，是前面的a,b两个数的按位异或作为和。
    //如果一次相加有进位，则把进位加上，如果相加后仍有进位，则递归调用，直到进位为0（没有进位）。
}

bool isMatch1(string s, string p) {
    if (p.empty()) return s.empty();
    if (p.size() == 1) {
        return (s.size() == 1 && (s[0] == p[0] || p[0] == '.'));
    }
    if (p[1] != '*') {
        if (s.empty()) return false;
        return (s[0] == p[0] || p[0] == '.') && isMatch1(s.substr(1), p.substr(1));
    }
    while (!s.empty() && (s[0] == p[0] || p[0] == '.')) {
        // 如果p[2]后和当前s能匹配，则p[1]的*号不用吃掉s[0]位置，可以直接返回true
        if (isMatch1(s, p.substr(2))) return true;

        // 否则需要吃掉s[0]，用后续s字符串和p进行匹配
        s = s.substr(1);
    }

    // p[0]p[1] = p[0]*，吃掉了所有的s[0]和p[0]的匹配字符后，s[0]已经和p[0]不再匹配，
    // 然后用余下的p[2]后和当前s进行匹配
    return isMatch1(s, p.substr(2));
}

int main() {
    count_0_1();
    return 0;
}
