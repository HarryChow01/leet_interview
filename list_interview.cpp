#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <map>
#include <iostream>

using namespace std;

struct ListNode {
    int val;
    struct ListNode* next;

    explicit ListNode(int x = 0) :
            val(x), next(nullptr) {
    }
};

struct RandomListNode {
    int label;
    struct RandomListNode* next, * random;

    explicit RandomListNode(int x = 0) :
            label(x), next(nullptr), random(nullptr) {
    }
};

ListNode* createList(const size_t kLen) {
    if (kLen == 0) {
        return nullptr;
    }
    auto* dumb = new ListNode(-1);
    auto* tail = dumb;

    for (int i = 0; i < kLen; i++) {
        tail->next = new ListNode(1 + i);
        tail = tail->next;
    }
    auto* pHead = dumb->next;
    delete dumb;
    dumb = nullptr;
    return pHead;
}

void printList(ListNode* head) {
    if (!head) {
        return;
    }
    ListNode* p = head;
    printf("List:\n");
    while (p) {
        printf("%d ", p->val);
        p = p->next;
    }
    printf("\n");
}

void deleteList(ListNode* head) {
    ListNode* p = nullptr;
    while (head) {
        p = head;
        head = head->next;
        delete (p);
    }
    p = nullptr;
}

// 倒序打印链表
void printListReverse(ListNode* head) {
    std::stack<int> nodes;
    ListNode* node = head;
    while (node) {
        nodes.push(node->val);
        node = node->next;
    }
    while (!nodes.empty()) {
        cout << "element in stack: " << nodes.top() << endl;
        nodes.pop();
    }
}

// https://blog.csdn.net/ljyljyok/article/details/77996029
ListNode* reverseList(ListNode* head) {
    // head每次指向当前拿下来的一个节点；
    ListNode* next; // 指向待合并的链表
    ListNode* prev = nullptr;   // 指向待返回的链表
    while (head != nullptr) {
        next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    return prev;
}

// 递归逆序单链表
// https://blog.csdn.net/ljyljyok/article/details/77996029
ListNode* reverseList2(ListNode* head) {
    if (!head || !head->next) {
        return head;
    }
    ListNode* newHead = reverseList2(head->next);
    head->next->next = head;
    head->next = nullptr;
    return newHead;
}

ListNode* reverseListByNStep(ListNode* head, const size_t kStep) {
    if (!head || kStep < 1) {
        return head;
    }
    auto* dumb = new ListNode(-1);
    dumb->next = head;
    size_t len = 0;
    auto* prev = dumb;
    ListNode* partHead = nullptr;
    auto* tail = dumb;

    while (head) {
        if (0 == len) {
            partHead = head;
        }
        while (head && len < kStep) {
            head = head->next;
            prev = prev->next;
            ++len;
        }
        if (kStep == len) {
            prev->next = nullptr;
            tail->next = reverseList(partHead);
            tail = partHead;
            tail->next = head;
            prev = tail;
            len = 0;
        }
    }
    auto* pHead = dumb->next;
    delete dumb;
    return pHead;
}

// 单链表首尾交替相连（快手面试题）
ListNode* reOrderList(ListNode* head) {
    if (!head || !head->next) {
        return head;
    }
    // 快慢指针将链表分成前后两个部分，后一部分进行逆序；
    auto* pSlow = head;
    auto* pFast = head->next;
    while (pFast && pFast->next) {
        pFast = pFast->next->next;
        pSlow = pSlow->next;
    }

    pFast = pSlow->next;
    pSlow->next = nullptr;
    pSlow = head;
    pFast = reverseList(pFast);

    ListNode* p = nullptr;
    while (pFast) {
        p = pFast;
        pFast = pFast->next;
        p->next = pSlow->next;
        pSlow->next = p;
        pSlow = pSlow->next->next;
    }
    return head;
}


/*
 * 单链表分段倒置:
任何一个单链表都可以分成若干个单调递增的区间, 例如:
1->4->6->2->8->6 可以分成 [1, 4, 6], [2, 8] 和[6] 三个区间.
现在要求对每个区间进行倒置, 例如刚才的例子就变成:
6->4->1->8->2->6.
要求返回链表的头指针, 语言不限.
 */
ListNode* reverseSeg(ListNode* head) {
    if (!head || !head->next) {
        return head;
    }
    ListNode* newHead = new ListNode(-1);
    ListNode* newTail = newHead;

    ListNode* next = nullptr;

    ListNode* segHead = nullptr;
    ListNode* segTail = nullptr;

    while (head) {
        segTail = head;
        segHead = nullptr;
        next = head->next;
        while (next && head->val <= next->val) {
            head->next = segHead;
            segHead = head;
            head = next;
            next = head->next;
        }

        head->next = segHead;
        segHead = head;
        newTail->next = segHead;
        newTail = segTail;
        head = next;
    }

    auto* pHead = newHead->next;
    delete newHead;
    return pHead;
}

ListNode* createSegList() {
    auto* head = new ListNode(1);
    ListNode* help = head;
    help->next = new ListNode(4);
    help = help->next;
    help->next = new ListNode(6);
    help = help->next;
    help->next = new ListNode(2);
    help = help->next;
    help->next = new ListNode(8);
    help = help->next;
    help->next = new ListNode(6);

    return head;
}

void testReverseList() {
    ListNode* head = createList(7);
    printList(head);
    //head = reverseList(head);
    head = reverseListByNStep(head, 3);
    //head = reOrderList(head);
    printList(head);

    //head = createSegList();
    //printList(head);
    //head = reverseSeg(head);
    //printList(head);

    deleteList(head);
}

#if 1
int main() {
    printf("Into main\n\n");

    testReverseList();

    printf("\n\nreturn from main\n");
}
#endif

ListNode* getLastKListNode(ListNode* head, const size_t k) {
    if (!head || k < 1)
        return nullptr;

    ListNode* q = head;
    ListNode* p = head;
    int pos = 0;

    while (p && (pos < k)) {
        pos++;
        p = p->next;
    }

    if (pos != k)
        return nullptr;

    while (p) {
        p = p->next;
        q = q->next;
    }
    return q;
}

void testGetLastKListNode() {
    ListNode* head = createList(10);
    printList(head);

    ListNode* pLastKNode = getLastKListNode(head, 8);
    if (pLastKNode) {
        printf("last 8 : %d\n", pLastKNode->val);
    }

    pLastKNode = getLastKListNode(head, 1);
    if (pLastKNode) {
        printf("last 1 : %d\n", pLastKNode->val);
    }

    pLastKNode = getLastKListNode(head, 10);
    if (pLastKNode) {
        printf("last 10 : %d\n", pLastKNode->val);
    }

    deleteList(head);
}

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode* dumb = new ListNode(-1);
    ListNode* cur = dumb;
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
    if (l1) {
        cur->next = l1;
    } else {
        cur->next = l2;
    }
    auto* pHead = dumb->next;
    delete dumb;
    return pHead;
}

ListNode* mergeKLists(vector<ListNode*> &lists) {
    if (lists.size() == 0) return nullptr;
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


// 两个链表合并，递归实现
ListNode* mergeLists(ListNode* pHead1, ListNode* pHead2) {
    //判断指针是否为空
    if (!pHead1) {
        return pHead2;
    } else if (!pHead2) {
        return pHead1;
    }
    ListNode* pMergedHead = nullptr;
    if (pHead1->val < pHead2->val) {
        pMergedHead = pHead1;
        pMergedHead->next = mergeLists(pHead1->next, pHead2);
    } else {
        pMergedHead = pHead2;
        pMergedHead->next = mergeLists(pHead1, pHead2->next);
    }
    return pMergedHead;
}

void testMergeLists() {
    ListNode* pHead1 = createList(5);
    ListNode* pHead2 = createList(3);
    printList(pHead1);
    printList(pHead2);
    pHead1 = mergeTwoLists(pHead1, pHead2);
    printList(pHead1);
}

// 带有随机指针的链表复制
RandomListNode* randomListClone1(RandomListNode* pHead) {
    if (!pHead)
        return nullptr;
    RandomListNode* p = pHead, * ret = pHead;
    for (; p != nullptr; p = p->next->next) {
        auto* now = new RandomListNode(p->label);
        now->next = p->next;
        p->next = now;
    }
    for (p = pHead; p != nullptr; p = p->next->next)
        if (p->random != nullptr)
            p->next->random = p->random->next;
    for (p = pHead, ret = p->next; p->next != nullptr;
         pHead = p->next, p->next = p->next->next, p = pHead);

    return ret;
}

RandomListNode* copyList(RandomListNode* pHead, map<RandomListNode*, RandomListNode*> &mp) {
    if (!pHead)
        return nullptr;
    auto* ret = new RandomListNode(pHead->label);
    mp[pHead] = ret;
    ret->next = copyList(pHead->next, mp);
    return ret;
}

RandomListNode* randomListClone2(RandomListNode* pHead) {
    map<RandomListNode*, RandomListNode*> mp;
    auto* ret = copyList(pHead, mp);
    for (RandomListNode* p = pHead, * q = ret; p != nullptr; p = p->next, q = q->next)
        q->random = mp[p->random];
    return ret;
}

RandomListNode* randomListClone3(RandomListNode* pHead) {
    if (!pHead)
        return nullptr;
    map<RandomListNode*, RandomListNode*> mp;
    RandomListNode* ret = new RandomListNode(pHead->label), * q = ret;
    mp[pHead] = ret;
    for (auto p = pHead->next; p != nullptr; p = p->next, q = q->next) {
        q->next = new RandomListNode(p->label);
        mp[p] = q->next;
    }
    q->next = nullptr;

    for (RandomListNode* p = pHead, * q = ret; p != nullptr; p = p->next, q = q->next)
        q->random = mp[p->random];
    return ret;
}


// Intersection of Two Linked Lists, O(1) Storage, so can not use map or set.
int getLength(ListNode* head) {
    int cnt = 0;
    while (head) {
        ++cnt;
        head = head->next;
    }
    return cnt;
}

ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
    if (!headA || !headB) return nullptr;
    int lenA = getLength(headA), lenB = getLength(headB);
    if (lenA < lenB) {
        for (int i = 0; i < lenB - lenA; ++i) headB = headB->next;
    } else {
        for (int i = 0; i < lenA - lenB; ++i) headA = headA->next;
    }
    while (headA && headB && headA != headB) {
        headA = headA->next;
        headB = headB->next;
    }
    return headA;
}


unsigned int getListLength(ListNode* pHead) {
    size_t length = 0;
    while (pHead != nullptr) {
        pHead = pHead->next;
        length++;
    }
    return length;
}

// 获取两个链表的第一个公共节点
ListNode* FindFirstCommonNode(ListNode* pHead1, ListNode* pHead2) {
    // 如果有一个链表为空，则返回结果为空
    if (!pHead1 || !pHead2) {
        return nullptr;
    }
    // 获得两个链表的长度
    unsigned int len1 = getListLength(pHead1);
    unsigned int len2 = getListLength(pHead2);
    // 默认 pHead1 长， pHead2短，如果不是，再更改
    ListNode* pHeadLong = pHead1;
    ListNode* pHeadShort = pHead2;
    int lengthDif = len1 - len2;
    // 如果 pHead1 比 pHead2 小
    if (len1 < len2) {
        ListNode* pHeadLong = pHead2;
        ListNode* pHeadShort = pHead1;
        lengthDif = len2 - len1;
    }
    // 将长链表的前面部分去掉，使两个链表等长
    for (int i = 0; i < lengthDif; i++) {
        pHeadLong = pHeadLong->next;
    }

    while (pHeadLong != nullptr && pHeadShort != nullptr && pHeadLong != pHeadShort) {
        pHeadLong = pHeadLong->next;
        pHeadShort = pHeadShort->next;
    }
    return pHeadLong;
}

// 使用快慢指针，找到任意的一个环中结点
ListNode* meetingNode(ListNode* pHead) {
    if (!pHead || !pHead->next) {
        return nullptr;
    }
    ListNode* pSlow = pHead->next;
    ListNode* pFast = pSlow->next;
    while (pFast != nullptr && pSlow != nullptr) {
        if (pFast == pSlow) {
            return pFast;
        }
        pSlow = pSlow->next;
        pFast = pFast->next;
        if (pFast != nullptr) {
            pFast = pFast->next;
        }
    }
    return nullptr;
}

// 3 steps: (1)find fast and slow pointer meet (2)find the length of circle
//          (3)let p1(from head) go length of circle, the p1 and p2 go on same step, when meet then stop
ListNode* entryNodeOfLoop(ListNode* pHead) {
    if (!pHead) {
        return nullptr;
    }
    ListNode* meetingnode = meetingNode(pHead);
    if (!meetingnode) {
        return nullptr;
    }
    // 回环链表结点个数
    int nodesloop = 1;
    // 找到环中结点个数
    ListNode* pNode1 = meetingnode;
    while (pNode1->next != meetingnode) {
        pNode1 = pNode1->next;
        nodesloop++;
    }
    pNode1 = pHead;
    // 第一个指针向前移动nodesloop步
    for (int i = 0; i < nodesloop; i++) {
        pNode1 = pNode1->next;
    }
    // 两个指针同时移动，找到环入口
    ListNode* pNode2 = pHead;
    while (pNode1 != pNode2) {
        pNode1 = pNode1->next;
        pNode2 = pNode2->next;
    }
    return pNode1;
}

void deleteDuplicates(ListNode* head) {
    if (!head)
        return;
    ListNode* prev = head;
    ListNode* cur = head->next;
    while (cur) {
        if (prev->val == cur->val) {
            prev->next = cur->next;
            delete cur;
        } else {
            prev = cur;
        }
        cur = prev->next;
    }
}

void recurRemove(ListNode* prev, ListNode* cur) {
    if (!prev || !cur)
        return;
    if (prev->val == cur->val) {
        prev->next = cur->next;
        delete cur;
        recurRemove(prev, prev->next);
    } else {
        recurRemove(prev->next, cur->next);
    }
}

ListNode* deleteDuplicatesRecur(ListNode* head) {
    if (!head)
        return nullptr;
    ListNode dummy;
    dummy.next = head;
    recurRemove(&dummy, head);
    return dummy.next;
}

ListNode* createDuplicatesList() {
    vector<int> values = {1, 2, 2, 3, 4, 4};
    if (values.empty())
        return nullptr;
    ListNode* head = new ListNode(values[0]);
    ListNode* p = head;
    for (size_t i = 1; i < values.size(); ++i) {
        p->next = new ListNode(values[i]);
        p = p->next;
    }
    return head;
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
    ListNode* help = head;
    help->next = new ListNode(1);
    help = help->next;
    help->next = new ListNode(6);
    help = help->next;
    help->next = new ListNode(2);
    help = help->next;
    help->next = new ListNode(3);
    help = help->next;
    help->next = new ListNode(7);
    help = help->next;
    help->next = new ListNode(5);
    help = help->next;

    return head;
}

#if 0
int main(int argc, char* argv[]) {
    printf("Into main\n\n");

    testReverseList();
    //testGetLastKListNode();
    //testMergeLists();
    //ListNode *head = createList(8);
    //printListReverse(head);

    //ListNode *head = createDuplicatesList();
    //printList(head);
    //deleteDuplicates(head);
    //deleteDuplicatesRecur(head);

    // list sort
    //ListNode* head = createListSort();
    //printList(head);
    //listQuickSort(head, nullptr);
    //head = listMergeSort(head);
    //printList(head);
    //deleteList(head);

    printf("\n\nreturn from main\n");
}

#endif








