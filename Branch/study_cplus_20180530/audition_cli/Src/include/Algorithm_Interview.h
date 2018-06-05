//
//  Algorithm_Interview.h
//  my_Account
//
//  Created by hubao on 2018/5/6.
//  Copyright © 2018年 cltx. All rights reserved.
//
#ifndef Algorithm_Interview_h
#define Algorithm_Interview_h

#include <assert.h>

template<typename T>
void swap(T* a, T* b){
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

/*
 *冒泡排序
 */

void buddle_sort(int *a, int size){
    assert(a != NULL);
    
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size - i; j++){
            if (a[j] < a[j+1]){
                a[j] = a[j] ^ a[j+1];
                a[j+1] = a[j] ^ a[j+1];
                a[j] = a[j] ^ a[j+1];
            }
        }
    }
}
/*
 *快速排序
 */
void qk_sort(int *a, int begin, int end)
{
    int i = begin, j = end;
    int temp = a[i];

    if(i < j){
        while(i < j){
            while(a[j] > temp && i < j) j--;
            while (a[i] < temp && i < j) i++;

            if(i < j) swap(a[i],a[j]);
        }

        swap(a[i], a[begin]);
        qk_sort(a, begin, i - 1);
        qk_sort(a, j+1, end);
    }
}

/*
 *归并排序
 */
void merge(int *a, int begin, int mid, int end, int* ret){
    int i=begin, j=mid;
    int m=mid+1, n=end;
    
    while(i <= j && m <= n){
        if(a[i] < a[m]) *ret++ = a[i++];
        if(a[i] > a[m]) *ret++ = a[m++];
    }
    
    while(i<=j) *ret++ = a[i++];
    while(m<=n) *ret++ = a[m++];
}

void merge_sort(int *a, int begin, int end, int* ret){
    
    if(begin < end){
        int mid = (begin + end) / 2;
        merge_sort(a, begin, mid, ret);
        merge_sort(a, mid + 1, end, ret);
        merge(a, begin, mid, end, ret);
    }
}

/*
 *堆排序
 */
void heap(int *a, int node,int size){
    int lch = 2*node+1;
    int rch = 2*node+2;
    
    cout << "lch="<< a[lch]<<"("<<lch<<")"
        <<" rch="<< a[rch]<<"("<<rch<<")"
        << endl;
    
    // 检查必须要加，因为当右子节点被swap之后，如果不检查，则会拿过来重新比较
    if(lch <= size-1){
        if(a[lch] > a[node]) swap(a[node], a[lch]);
    }
    // 检查必须要加，因为当右子节点被swap之后，如果不检查，则会拿过来重新比较
    if(rch <= size-1){
        if(a[rch] > a[node]) swap(a[node], a[rch]);
    }
    cout << "out: " << a[node]<< " " << a[lch]<< " " << a[rch] << endl;
}

void heap_buid(int *a, int size){
    cout << "#########" << size<< endl;
    for(int i=size/2-1;i>=0;i--){
        heap(a, i, size);
    }
    cout<<"max=" << a[0]<< endl;
}

void heap_sort(int *a, int size){
    heap_buid(a, size);
    for(int i= size-1; i >0;i--){
        swap(a[i], a[0]);
        heap_buid(a, i);
    }
}

/*
 *二叉树
 */
struct _node{
    int data;
    _node* lch;
    _node* rch;
};
struct _ListNode{
    int data;
    _ListNode* next;
};
//前序或中序遍历
void pre_order(_node* p){
    if(NULL == p){
        return;
    }else{
        std::stack<_node*> sNode;
        while(p || !sNode.empty()){
            while(p){
                sNode.push(p);
                p = p->lch;
            }
            
            p = sNode.top();
            sNode.pop();
            
            p = p->rch;
        }
    }
}
//层级遍历
void lev_order(_node* p){
    if(NULL == p){
        return;
    }else{
        std::queue<_node*> qNode;
        qNode.push(p);
        
        while(!qNode.empty()){
            cout << p->data << endl;
            
            if(p->lch) qNode.push(p->lch);
            if(p->rch) qNode.push(p->rch);
        }
    }
}
//后序遍历
void last_order(_node* p){
    if(!p) return;
    
    last_order(p->lch);
    last_order(p->rch);
    cout << p->data << endl;
}

/*
 *单链表反转
 */
void reverse(_ListNode* head){
    if(NULL == head){
        cout << "####" << endl;
        return;
    }
    
    _ListNode *p = head;
    _ListNode *q = p->next;
    _ListNode *r = NULL;
    
    p->next = NULL;
    
    while(q != NULL){
        r = q->next;
        q->next = p;
        p = q;
        q =r;
        cout << "####q" << endl;
    }
    
    head = p;
}



/*
 *查找
 */
//二分查找 - 递归
int binary_search(int *a, int begin, int end, int data)
{
    if(begin >= end) return -1;
    
    int mid = (end + begin)/2;
    int ret = -1;
    
    if(a[mid] == data) return mid;
    
    if(a[mid] > data)
        ret = binary_search(a, begin, mid, data);
    
    if(a[mid] < data)
        ret = binary_search(a, mid+1, end, data);
    
    return ret;
}
//二分查找 - 非递归
int binary_search(int *a, int value, int size){
    int begin = 0, end = size - 1, mid = size / 2;
    if(a[mid] == value) return mid;
    while(end > begin){
        mid = end - begin / 2;
        if(a[mid] == value) return mid;
        if(a[mid] > value) end = mid;
        if(a[mid] < value) begin = mid;
    }
    return -1;
}


#endif /* Algorithm_Interview_h */
