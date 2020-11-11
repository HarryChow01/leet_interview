
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <ctime>

#include <vector>
#include <iostream>
#include <stack>

using namespace std;

struct ListNode {
    int val;
    struct ListNode* next;

    explicit ListNode(int x = 0) :
            val(x), next(nullptr) {
    }
};

template<typename T>
void printContainer(const T &container) {
    for (auto &item : container) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

/*
 * 二分查找
 */
int biSearch(const int data[], int start, int end, const int value) {
    if (start < 0 || start > end) {
        return -1;
    }
    int low = start;
    int high = end;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (value == data[mid]) {
            return mid;
        } else if (value < data[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1;  //没找到
}

void testBisearch() {
    int data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int pos = biSearch(data, 0, 9, 9);
    cout << "pos = " << pos << endl;
}


template<typename T>
int partition(T data[], int start, int end) {
    assert ((start >= 0) && (start <= end));
    T pivot = data[start];
    while (start < end) {
        while ((start < end) && (data[end] >= pivot)) --end;
        data[start] = data[end];
        while ((start < end) && (data[start] <= pivot)) ++start;
        data[end] = data[start];
    }
    data[start] = pivot;
    return start;
}

template<typename T>
void quickSort1(T data[], int start, int end) {
    if (start < 0 || start >= end) {
        return;
    }
    int pivot = partition(data, start, end);
    quickSort1(data, start, pivot - 1);
    quickSort1(data, pivot + 1, end);
}

/*
 * 非递归快排用栈保存划分的首尾index
 * https://blog.csdn.net/Scythe666/article/details/50951938
 */
template<typename T>
void quickSort2(T data[], int low, int high) {
    std::stack<int> stack;
    if (low < 0 || low >= high) {
        return;
    }
    int mid = partition(data, low, high);
    if (low < mid - 1) {
        stack.push(low);
        stack.push(mid - 1);
    }
    if (mid + 1 < high) {
        stack.push(mid + 1);
        stack.push(high);
    }
    while (!stack.empty()) {
        high = stack.top();
        stack.pop();
        low = stack.top();
        stack.pop();
        mid = partition(data, low, high);
        if (low < mid - 1) {
            stack.push(low);
            stack.push(mid - 1);
        }
        if (mid + 1 < high) {
            stack.push(mid + 1);
            stack.push(high);
        }
    }
}

void testQuickSort() {
    vector<int> data = {3, 1, 6, 9, 3, 2, 7, 8, 4, 5};

    printf("Before sort:");
    printContainer(data);

    //quickSort1(data.data(), 0, data.size() - 1);
    quickSort2(data.data(), 0, data.size() - 1);

    printf("after sort:");
    printContainer(data);
}

template<typename T>
void heapAdjust(T data[], int s, int m) {
    T record = data[s];
    for (int j = 2 * s + 1; j <= m; j = 2 * s + 1) {
        if ((j < m) && (data[j] < data[j + 1])) ++j;
        if (record >= data[j]) {
            break;
        }
        data[s] = data[j];
        s = j;
    }
    data[s] = record;
}

template<typename T>
void heapSort(std::vector<T>& data) {
    int length = data.size();
    if (length <= 1) return;
    for (int i = length / 2; i >= 0; --i) {
        heapAdjust(data.data(), i, length - 1);
    }
    for (int i = length - 1; i > 0; --i) {
        std::swap(data[0], data[i]);
        heapAdjust(data.data(), 0, i - 1);
    }
}

void testHeapSort() {
    vector<int> data = {3, 1, 6, 9, 3, 2, 7, 8, 4, 5};
    std::cout << "before sort: ";
    printContainer(data);

    heapSort(data);

    std::cout << "after sort: ";
    printContainer(data);
}

// 桶排序重要参考：https://blog.csdn.net/misayaaaaa/article/details/66969486
// 适用范围是：待排序数组是整数，且值在一个范围内[m, n]
// 时间复杂度：O(n)，空间复杂度要一个额外数组
void bucketSort(uint32_t data[], int length, uint32_t startValue, uint32_t endValue) {
    const size_t kSize = endValue - startValue + 1;
    std::vector<uint32_t> temp(kSize);
    for (int i = 0; i < length; ++i) {
        size_t pos = (data[i] - startValue) % kSize;
        temp[pos]++;
    }
    int pos = 0;
    for (int i = 0; i < kSize; ++i) {
        for (int j = 0; j < temp[i]; ++j) {
            data[pos++] = startValue + i;
        }
    }
}


// 无序数组的中位数
// 快排的思想：注意数据量是奇数还是偶数的情况
int median1(vector<int> &data) {
    if (data.empty()) return INT32_MIN;
    int largeIndex = int(data.size() / 2);

    int left = 0;
    int right = int(data.size()) - 1;

    int index = -1;
    while (index != largeIndex) {
        index = partition(data.data(), left, right);
        if (index < largeIndex) left = index + 1;
        else if (index > largeIndex) right = index - 1;
        else break;
    }

    if (data.size() % 2 == 0) return data[index];

    int smallIndex = largeIndex - 1;
    left = 0;
    right = int(data.size()) - 1;
    index = -1;
    while (index != smallIndex) {
        index = partition(data.data(), left, right);
        if (index < smallIndex) left = index + 1;
        else if (index > smallIndex) right = index - 1;
        else break;
    }
    return (data[smallIndex] + data[largeIndex]) / 2;
}

// 最大堆
int median2(vector<int> &data) {
    if (data.empty()) return INT32_MIN;
    const int kPos = int(data.size()) / 2;

    for (int i = kPos / 2; i >= 0; --i) {
        heapAdjust(data.data(), i, kPos);
    }
    for (int i = kPos + 1; i < data.size(); ++i) {
        if (data[i] < data[kPos]) {
            std::swap(data[i], data[kPos]);
            heapAdjust(data.data(), 0, kPos);
        }
    }

    if (data.size() % 2 == 1) { // 奇数个元素
        return data[0];
    } else {                    // 偶数个元素
        int temp = data[0];
        if (kPos == 1) {
            temp += data[1];
        } else {
            temp += std::max(data[1], data[2]);
        }
        return temp / 2;
    }
}


/*
 * 分治法：归并排序
 */
template<typename T>
void merge(T data[], T leftData[], size_t leftCount, T rightData[], size_t rightCount) {
    int i = 0;
    int j = 0;
    int k = 0;

    while (i < leftCount && j < rightCount) {
        if (leftData[i] < rightData[j])
            data[k++] = leftData[i++];
        else
            data[k++] = rightData[j++];
    }
    while (i < leftCount) data[k++] = leftData[i++];
    while (j < rightCount) data[k++] = rightData[j++];
}

template<typename T>
void mergeSort(T data[], size_t len) {
    if (len < 2) return;
    size_t mid = len / 2;

    vector<T> leftData(data, data + mid);
    vector<T> rightData(data + mid, data + len);

    //std::copy(data, data + mid, leftData.begin());
    //std::copy(data + mid, data + len, rightData.begin());

    mergeSort(leftData.data(), mid);
    mergeSort(rightData.data(), len - mid);
    merge(data, leftData.data(), mid, rightData.data(), len - mid);
}

void testMergeSort() {
    vector<size_t> data = {6, 2, 3, 1, 9, 10, 15, 13, 12, 17};
    mergeSort(data.data(), data.size());

    cout << "after sort:\n";
    for (auto &item : data)
        cout << item << " ";
    cout << endl;
}

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode* head = new ListNode(-1);
    ListNode* cur = head;
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
    if (l1) cur->next = l1;
    if (l2) cur->next = l2;
    return head->next;
}

// list sort quick Time: n*log(n)-n^2  storage: log(n)-n
ListNode* listPartition(ListNode* head, ListNode* tail) {
    if (!head) {
        return nullptr;
    }
    int pivot = head->val;
    ListNode* p = head;
    ListNode* q = head->next;
    while (q != tail) {
        if (q->val < pivot) {
            p = p->next;
            if (p->val >= pivot) {
                swap(p->val, q->val);
            }
        }
        q = q->next;
    }
    swap(p->val, head->val);
    return p;
}

void listQuickSort(ListNode* head, ListNode* tail) {
    if (!head) {
        return;
    }
    if (head != tail) {
        ListNode* p = listPartition(head, tail);
        listQuickSort(head, p);
        listQuickSort(p->next, tail);
    }
}

ListNode* listMergeSort(ListNode* head) {
    if (!head || !head->next)
        return head;
    /* 找到链表中间的节点，prev代表中间节点的前一个节点 */
    ListNode* slow = head;
    ListNode* fast = head->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    fast = slow;
    slow = slow->next;
    fast->next = nullptr;
    /* 对左右两部分分别进行切分和排序　*/
    ListNode* lhs = listMergeSort(head);
    ListNode* rhs = listMergeSort(slow);
    /* 返回的lhs和rhs是已经排好序的链表，接下来将这两个有序链表合并成一个 */
    return mergeTwoLists(lhs, rhs);
}


ListNode* createListSort() {
    auto* head = new ListNode(4);
    ListNode* cur = head;
    cur->next = new ListNode(1);
    cur = cur->next;
    cur->next = new ListNode(6);
    cur = cur->next;
    cur->next = new ListNode(2);
    cur = cur->next;
    cur->next = new ListNode(3);
    cur = cur->next;
    cur->next = new ListNode(7);
    cur = cur->next;
    cur->next = new ListNode(5);

    return head;
}

int main() {
    //testBisearch();
    //testQuickSort();
    //testHeapSort();
    testMergeSort();

    return 0;
}
