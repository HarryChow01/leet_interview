
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
#include <map>

using namespace std;

inline void printIntArray(vector<int>& array) {
    for (auto& item : array) {
        cout << item << " ";
    }
    cout << endl;
}

// 二维行列递增数组中的查找
class Solution1 {
public:
    bool findIn2DArray(int target, vector<vector<int>>& array) {
        size_t rows = array.size();
        size_t cols = array[0].size();
        if (array.empty() || rows == 0 || cols == 0) {
            return false;
        }
        int row = 0;
        int col = cols - 1;
        while (row < rows && col >= 0) {
            if (array[row][col] == target) {
                return true;
            } else if (array[row][col] > target) {
                --col;
            } else {
                ++row;
            }
        }
        return false;
    }
};

// 旋转数组，最小数字
class Solution2 {
public:
    int minNumberInRotateArray(std::vector<int>& rotateArray) {
        size_t size = rotateArray.size();							//数组长度
        if(rotateArray.empty()){
            return 0;
        }
        size_t left = 0;											//左指针
        size_t right = size - 1;									//右指针
        size_t mid = 0;											//中间指针
        while(rotateArray[left] >= rotateArray[right]) {			//确保旋转
            if(right - left == 1) {								//左右指针相邻
                mid = right;
                return rotateArray[mid];
            }
            mid = (left + right) / 2;					//计算中间指针位置
            //特殊情况：如果无法确定中间元素是属于前面还是后面的递增子数组，只能顺序查找
            if(rotateArray[left] == rotateArray[right] && rotateArray[mid] == rotateArray[left]){
                return MinInOrder(rotateArray, left, right);
            }
            //中间元素位于前面的递增子数组，此时最小元素位于中间元素的后面
            if(rotateArray[mid] >= rotateArray[left]){
                left = mid;
            } else {    //中间元素位于后面的递增子数组，此时最小元素位于中间元素的前面
                right = mid;
            }
        } // end while
        return rotateArray[mid];
    }
private:
    //顺序寻找最小值
    int MinInOrder(vector<int> &num, int left, int right){
        int result = num[left];
        for(int i = left + 1; i < right; i++){
            if(num[i] < result){
                result = num[i];
            }
        }
        return result;
    }
};

// 给定一个整形数组，要求调整元素顺序，使得奇数在前偶数在后，
// 并保证奇数之间，偶数之间的相对位置不变
// 如果要保证奇数和奇数，偶数和偶数之间的相对位置不变，那么需要开辟新的空间来保存奇数和偶数，方法有两种：
// 1、开辟一个新数组，遍历第一遍原数组，将奇数依次写入新数组，遍历第二遍原数组，将偶数依次写入新数组，返回新数组；
// 2、开辟两个数组，遍历一遍原数组，分别将奇数和偶数存入两个新数组，再将奇数数组和偶数数组分别写入原数组，返回原数组；
// 如果无需保证奇数和奇数，偶数和偶数之间的相对位置不变，那么可以通过前后遍历，奇偶对换的方法来实现：

class Solution3 { // 用一个数组实现
public:
    static void reOrderArray1(vector<int>& array) { // 开辟一个新数组
        if (array.empty())
            return;
        vector<int> tmpArray;
        tmpArray.reserve(array.size());
        //cout << "tmpArray.size(): " << tmpArray.size() << endl;
        for (size_t i = 0; i < array.size(); ++i) {
            if (array[i] % 2 == 1) {
                tmpArray.emplace_back(array[i]);
            }
        }
        for (size_t i = 0; i < array.size(); ++i) {
            if (array[i] % 2 == 0) {
                tmpArray.emplace_back(array[i]);
            }
        }
        std::swap(array, tmpArray);
    }

    static void reOrderArray2(vector<int>& array) { // 开辟两个新数组
        if (array.empty())
            return;
        vector<int> oddArray;
        vector<int> evenArray;
        for (size_t i = 0; i < array.size(); ++i) {
            if (array[i] % 2 == 1) {
                oddArray.emplace_back(array[i]);
            } else {
                evenArray.emplace_back(array[i]);
            }
        }
        array.assign(oddArray.begin(), oddArray.end());
        array.insert(array.end(), evenArray.begin(), evenArray.end());
    }

    static void reOrderArray3(vector<int>& array) { // 去掉约束条件，奇数和奇数，偶数和偶数之间的相对位置不变
        if (array.empty())
            return;
        size_t left = 0;
        size_t right = array.size() - 1;
        while (left != right) {
            while ((left != right) && (array[left] % 2 == 1))
                ++left;
            while ((left != right) && (array[right] % 2 == 0))
                --right;
            if (left != right)
                std::swap(array[left], array[right]);
        }
    }

    // 类似冒泡排序
    static void reOrderArray4(vector<int>& array) {
        bool flag = true;  //是否退出while的标志
        while(flag) {
            //每一趟
            flag = false;
            for(int i = 0; i <= array.size() - 2; i++) {
                if(array[i] % 2 == 0 && array[i+1] % 2 != 0) {
                    //前偶，后奇
                    std::swap(array[i], array[i+1]);
                    flag = true;
                }
            }
        }
    }

    void reOrderArray5(vector<int>& array) {
        //类似插入排序
        for(int i = 1; i < array.size(); i++) {
            int target = array[i];
            //如果target是奇数，需要调整
            if(target % 2 != 0) {
                int j;
                for(j = i-1; j >= 0; j--) {
                    if(array[j] % 2 == 0) {
                        //偶数后移
                        array[j+1] = array[j];
                    } else {
                        //碰到第一个奇数，退出
                        break;
                    }
                }
                array[j+1] = target;
            }
        }
    }

};

void testReorderArray() {
    vector<int> array = {0,1,2,3,4,5,6,7,8,9,};
    cout << "before reorder:"  << endl;
    printIntArray(array);
    Solution3::reOrderArray1(array);
    cout << "after reorder3:"  << endl;
    printIntArray(array);
}

// 统计数组中出现次数超过一半的数字
class Solution4 { //
public:
    // 先排序，取最中间一个numbers[numbers.size()/2]
    static int findOneNumber1(vector<int>& numbers) {
        // 时间复杂度O(nlogn)，不需要统计次数；
        if (numbers.empty())
            return 0;
        std::sort(numbers.begin(), numbers.end());
        return numbers[numbers.size()/2];
    }

    // 用hashmap统计次数，然后取最大的一个，空间复杂度O(n)，时间复杂度O(n)
    static int findOneNumber2(vector<int>& numbers) {
        if (numbers.empty())
            return 0;
        std::map<int, int> map_count;
        for (auto& item : numbers) {
            ++map_count[item];
        }

        int max_num = 0;
        int max_count = 0;
        for (auto& item : map_count) {
            if (item.second > max_count) {
                max_num = item.first;
                max_count = item.second;
            }
        }
        return max_num;
    }

    // 每次删除两个不同的数，最后保留的就是
    static int findOneNumber3(vector<int>& numbers);

    /*我们可以在遍历数组的时候保存两个值：一个candidate，用来保存数组中遍历到的某个数字；一个nTimes，
     * 表示当前数字的出现次数，其中，nTimes初始化为1。当我们遍历到数组中下一个数字的时候：
        如果下一个数字与之前candidate保存的数字相同，则nTimes加1；
        如果下一个数字与之前candidate保存的数字不同，则nTimes减1；
        每当出现次数nTimes变为0后，用candidate保存下一个数字，并把nTimes重新设为1。 直到遍历完数组中的所有数字为止。*/
    static int findOneNumber4(vector<int>& numbers) {
        if (numbers.empty())
            return 0;
        int number = numbers[0];
        size_t count = 1;
        for (size_t i = 1; i < numbers.size(); ++i) {
            if (count == 0) {
                number = numbers[i];
                count = 1;
            } else {
                if (number == numbers[i]) {
                    ++count;
                } else {
                    --count;
                }
            }
        } // end for
        return number;
    }

};

int moreThanHalfNum(vector<int>& numbers) {
    if(numbers.empty()){
        return 0;
    }
    // 遍历每个元素，并记录次数；若与前一个元素相同，则次数加1，否则次数减1
    int result = numbers[0];
    int times = 1;
    for (int i = 1; i < numbers.size(); ++i) {
        if(times == 0){
            // 更新result的值为当前元素，并置次数为1
            result = numbers[i];
            times = 1;
        } else if(numbers[i] == result) {
            times++;
        } else {
            times--;
        }
    }
    // 判断result是否符合条件，即出现次数大于数组长度的一半
    times = 0;
    for(int i = 0; i < numbers.size(); ++i)
    {
        if(numbers[i] == result){
            times++;
        }
    }
    return (times > (numbers.size() >> 1)) ? result : 0;
}

void testFindOneNumber() {
    vector<int> array = {0,1,2,1,1,};
    cout << "before:"  << endl;
    printIntArray(array);
    int num = Solution4::findOneNumber4(array);
    cout << "num: "  << num << endl;
    printIntArray(array);
}

// 返回旋转数组的最小值，无重复数字
int findMinRotatedArray1(vector<int> &nums) {
    if (nums.empty()) {
        return INT32_MIN;
    }
    size_t start = 0, end = nums.size() - 1;
    while (start < end) {
        if (nums[start] < nums[end])
            return nums[start];
        size_t mid = (start + end) / 2;
        if (nums[mid] >= nums[start])
            start = mid + 1;
        else
            end = mid;
    }
    return nums[start];
}

// 返回旋转数组的最小值，有重复数字
int findMinRotatedArray2(vector<int> &nums) {
    if (nums.empty()) {
        return INT32_MIN;
    }
    size_t start = 0, end = nums.size() - 1;
    while(start < end){
        if (nums[start] < nums[end])
            return nums[start];
        size_t mid = (start + end) / 2;
        if (nums[mid] > nums[start]) {
            start = mid + 1;
        } else if (nums[mid] < nums[start]) {
            end = mid;
        } else {
            if (start == mid) { // 总共还有两个元素，mid和start下标同时指向前一个元素
                if (nums[start] == nums[end]) {
                    return nums[start];
                } else { // if (nums[start] > nums[end])
                    return nums[end];
                }
            } else {
                start = start + 1;  // 舍弃一个相同的
            }
        }
    }
    return nums[start];
}

void testRotatedArray() {
    //vector<int> nums = {2,3,4,5,1,};
    //vector<int> nums = {10,3,10,10,10};
    vector<int> nums = {2,2,2,0,2}; // error
    cout << "min: " << findMinRotatedArray2(nums) << endl;
}

// 返回旋转数组大于等于target的最小值，有重复数字
int findMinRotatedArrayTarget(vector<int> &nums, int target) {
    if (nums.empty()) {
        return INT32_MIN;
    }
    size_t start = 0, end = nums.size() - 1;
    while(start < end){
        size_t mid = (start + end) / 2;
        if (target == nums[mid]) {
            return nums[mid];
        }
        if (nums[start] < nums[end]) {
            if (target > nums[end]) { // target大于最大的数
                return INT32_MIN;
            }
            if (nums[mid] >= target) {
                end = mid;
            } else {
                start = mid + 1;
            }
            continue;
        }
        if (nums[mid] > nums[start]) {
            if (target > nums[end] && target < nums[mid]) {
                end = mid;
            } else { // if (target > nums[mid] || target <= nums[end]) {
                start = mid + 1;
            }
        } else if (nums[mid] < nums[start]) {
            if (target < nums[mid] || target > nums[end]) {
                end = mid;
            } else { // if (target > nums[mid] && target <= nums[end]) {
                start = mid + 1;
            }
        } else {
            if (start == mid) { // 总共还有两个元素，mid和start下标同时指向前一个元素
                if (nums[end] >= target) {
                    return nums[end];
                } else { // if (nums[end] < target)
                    end = start;
                }
            } else {
                start = start + 1;  // 舍弃一个相同的
            }
        }
    }
    if (nums[start] >= target) {
        return nums[start];
    } else {
        return INT32_MIN;
    }
}

void testFindMinRotatedArrayTarget() {
    vector<int> nums1 = {3,4,5,8,1,};
    vector<int> nums2 = {10,3,10,10,10};
    vector<int> nums3 = {2,2,2,0,2}; // error
    cout << "min: " << findMinRotatedArrayTarget(nums1, -1) << endl;
    cout << "min: " << findMinRotatedArrayTarget(nums1, 0) << endl;
    cout << "min: " << findMinRotatedArrayTarget(nums1, 1) << endl;
    cout << "min: " << findMinRotatedArrayTarget(nums1, 2) << endl;
    cout << "min: " << findMinRotatedArrayTarget(nums1, 3) << endl;
    cout << "min: " << findMinRotatedArrayTarget(nums1, 4) << endl;
    cout << "min: " << findMinRotatedArrayTarget(nums1, 5) << endl;
    cout << "min: " << findMinRotatedArrayTarget(nums1, 6) << endl;
    cout << "min: " << findMinRotatedArrayTarget(nums1, 7) << endl;
    cout << "min: " << findMinRotatedArrayTarget(nums1, 8) << endl;
    cout << "min: " << findMinRotatedArrayTarget(nums1, 9) << endl;
    cout << "min: " << findMinRotatedArrayTarget(nums1, 10) << endl;

    cout << endl;
    cout << "min: " << findMinRotatedArrayTarget(nums2, 2) << endl;
    cout << "min: " << findMinRotatedArrayTarget(nums2, 3) << endl;
    cout << "min: " << findMinRotatedArrayTarget(nums2, 4) << endl;
}

// 在旋转数组中查找目标数字target的下标，数字不重复
int findTargetPos1(vector<int> &nums, int target) {
    if (nums.empty()){
        return -1;
    }
    int start = 0;
    int end = nums.size() - 1;

    while (start <= end) {
        int mid = (end + start) / 2;
        if (target == nums[mid]){
            return mid;
        } else if (nums[mid] >= nums[start] ){
            if (target >= nums[start] && target < nums[mid]) {
                end = mid - 1;
            } else { // if (target > nums[mid] || target <= nums[end])
                start = mid + 1;
            }
        } else { // if(nums[mid] < nums[start])
            if (target > nums[mid] && target <= nums[end]) {
                start = mid + 1;
            } else { // if (target < nums[mid] || target >= nums[start])
                end = mid - 1;
            }
        }
    }
    return -1;
}

// 在旋转数组中查找目标数字target的下标，数字可能重复
bool findTargetPos2(vector<int> &nums, int target) {
    if (nums.empty()){
        return false;
    }
    int start = 0;
    int end = nums.size() - 1;

    while (start <= end) {
        int mid = (end + start) / 2;
        if (target == nums[mid]){
            return true;
        } else if (nums[mid] > nums[start] ){
            if (target >= nums[start] && target < nums[mid]) {
                end = mid - 1;
            } else { // if (target > nums[mid] || target <= nums[end])
                start = mid + 1;
            }
        } else if(nums[mid] < nums[start]) {
            if (target > nums[mid] && target <= nums[end]) {
                start = mid + 1;
            } else { // if (target < nums[mid] || target >= nums[start])
                end = mid - 1;
            }
        } else { // if (nums[mid] == nums[start]) {
            start = start + 1;  // 舍弃一个相同的
        }
    }
    return false;
}

void testFindTargetPos() {
    vector<int> nums1 = {30,40,50,10,20};
    vector<int> nums2 = {2,5,6,0,0,1,2};

    //cout << "pos: " << findTargetPos1(nums, 20) << endl;
    //cout << "pos: " << findTargetPos1(nums, 15) << endl;
    cout << "found: " << findTargetPos2(nums2, 0) << endl;
    cout << "found: " << findTargetPos2(nums2, 3) << endl;
}

// 求逆序对的数目
long inversePairsCore(vector<int> &data, vector<int> &copy, int begin, int end){
    // 如果指向相同位置，则没有逆序对。
    if(begin == end){
        copy[begin] = data[end];
        return 0;
    }
    // 求中点
    int mid = (end + begin) >> 1;
    // 使data左半段有序，并返回左半段逆序对的数目
    long leftCount = inversePairsCore(copy, data, begin, mid);
    // 使data右半段有序，并返回右半段逆序对的数目
    long rightCount = inversePairsCore(copy, data, mid + 1, end);

    int i = mid; // i初始化为前半段最后一个数字的下标
    int j = end; // j初始化为后半段最后一个数字的下标
    int indexcopy = end; // 辅助数组复制的数组的最后一个数字的下标
    long count = 0; // 计数，逆序对的个数，注意类型

    while(i >= begin && j >= mid + 1){
        if(data[i] > data[j]){
            copy[indexcopy--] = data[i--];
            // 后一半的data[mid + 1, j],相对于data[i]都是逆序对
            count += j - mid;
        } else{
            copy[indexcopy--] = data[j--];
        }
    }
    for(;i >= begin; --i){
        copy[indexcopy--] = data[i];
    }
    for(;j >= mid + 1; --j){
        copy[indexcopy--] = data[j];
    }
    return leftCount + rightCount + count;
}
int InversePairs(vector<int> data) {
    if(data.size() == 0){
        return 0;
    }
    // 排序的辅助数组
    vector<int> copy;
    for(int i = 0; i < data.size(); ++i){
        copy.push_back(data[i]);
    }
    return inversePairsCore(data, copy, 0, data.size() - 1) % 1000000007;
}

// 求有序数组中多个相邻的K的数目；
// 迭代实现找到第一个K
int getFirstK(vector<int> &data, int k, int begin, int end){
    if(begin > end){
        return -1;
    }
    int middleIndex = (begin + end) >> 1;
    int middleData = data[middleIndex];

    if(middleData == k){
        if((middleIndex > 0 && data[middleIndex - 1] != k) || middleIndex == 0){
            return middleIndex;
        }
        else{
            end = middleIndex - 1;
        }
    }
    else if (middleData > k){
        end = middleIndex - 1;
    }
    else{
        begin = middleIndex + 1;
    }
    return getFirstK(data, k, begin, end);
}

// 循环实现找到最后一个K
int getLastK(vector<int> data, int k, int begin, int end){
    int length = data.size();
    int middleIndex = (begin + end) >> 1;
    int middleData = data[middleIndex];

    while(begin <= end){
        if(middleData == k){
            if((middleIndex < length - 1 && data[middleIndex + 1] != k) || middleIndex == length - 1){
                return middleIndex;
            }
            else{
                begin = middleIndex + 1;
            }
        }
        else if(middleData > k){
            end = middleIndex - 1;
        }
        else{
            begin = middleIndex + 1;
        }
        middleIndex = (begin + end) >> 1;
        middleData = data[middleIndex];
    }
    return -1;
}
int getNumberOfK(vector<int> data ,int k) {
    int length = data.size();
    if(length == 0){
        return 0;
    }
    int first = getFirstK(data, k, 0, length - 1);
    int last = getLastK(data, k, 0, length - 1);
    if(first != -1 && last != -1){
        return last - first + 1;
    }
    return 0;
}

vector<int> arrayMultiply(const vector<int>& A) {
    int length = A.size();
    vector<int> B(length);
    if(length <= 0){
        return B;
    }
    B[0] = 1;
    for(int i = 1; i < length; i++){
        B[i] = B[i - 1] * A[i - 1];
    }
    int temp = 1;
    for(int i = length - 2; i >= 0; i--){
        temp *= A[i + 1];
        B[i] *= temp;
    }
    return B;
}

void permutex_ationCore(string &str, int begin, vector<string> &result){
    //递归结束的条件：第一位和最后一位交换完成
    if(begin == str.length()){
        result.push_back(str);
        return;
    }
    for(int i = begin; i < str.length(); i++){
        //如果字符串相同，则不交换
        if(i != begin && str[i] == str[begin]){
            continue;
        }
        //位置交换
        swap(str[begin], str[i]);
        //递归调用，前面begin+1的位置不变，后面的字符串全排列
        permutex_ationCore(str, begin + 1, result);
        swap(str[begin], str[i]);
    }
}
vector<string> permutex_ation(string &str) {
    vector<string> result;
    //判断输入
    if(str.length() == 0){
        return result;
    }
    permutex_ationCore(str, 0, result);
    //对结果进行排序
    sort(result.begin(), result.end());
    return result;
}

vector<vector<int>> findContinuousSequence(int sum) {
    vector<vector<int>> result;
    // 高位指针和低位指针
    int plow = 1, phigh = 2;

    // 终止条件是phigh等于sum
    while (phigh > plow) {
        // 当前和，使用求和公式s = (a+b) * n / 2
        int curSum = (plow + phigh) * (phigh - plow + 1) >> 1;
        if (curSum == sum) {
            vector<int> temp;
            for(int i = plow; i <= phigh; i++){
                temp.push_back(i);
            }
            result.push_back(temp);
            plow++;
        } else if (curSum < sum) {
            phigh++;
        } if(curSum > sum) {
            plow++;
        }
    }
    return result;
}

vector<int> findNumbersWithSum1(vector<int> &array,int sum) {
    vector<int> result;
    int length = array.size();
    if(length < 1){
        return result;
    }
    int pright = length - 1;
    int pleft = 0;

    while(pright > pleft){
        int curSum = array[pleft] + array[pright];
        if(curSum == sum){
            result.push_back(array[pleft]);
            result.push_back(array[pright]);
            break;
        } else if(curSum < sum) {
            pleft++;
        } else {
            pright--;
        }
    }
    return result;
}

vector<int> findNumbersWithSum2(vector<int>& nums, int target) {
    map<int, int> myMap;
    vector<int> result;
    for (int i = 0; i < nums.size(); ++i) {
        if (myMap.find(target - nums[i]) == myMap.end()) {
            myMap[nums[i]] = i;
        } else {
            result = {target - nums[i], nums[i]};
            break;
        }
    }
    return result;
}


int f() {
    return 0;
    // or reurn 1;
}

int g() {
    while(true) {
        int a = f();
        int b = f();

        if ((a == 0) && (b == 1)) {
            return 0;
        }
        if ((a == 1) && (b == 0)) {
            return 1;
        }
    }
}


int main(int argc, char* argv[]) {
    //testReorderArray();
    //testFindOneNumber();
    //testRotatedArray();
    //testFindTargetPos();
    testFindMinRotatedArrayTarget();

}










