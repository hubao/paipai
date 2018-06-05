
#include <stack>
#include <queue>
#include <unistd.h>

//#include "../Include/Cha15.9_TextQuery.h"
//#include "../Include/Cha16.4.7_CTStatic.h"
//#include "../Include/RpcConnectPool.h"
//#include "../Include/Cha13.4_MsgHandler.h"
//#include "../Include/MergeSort.h"
//#include "../Include/Algorithm_Interview.h"
//#include "../Include/DesignPattern-Create.h"


#include "server.h"
//#include "../thrift/Src/client.h"
//#define DEF_ORDER_DLR 0x0
//#define DEF_ORDER_LDR 0x1
//#define DEF_ORDER_LRD 0x2
//
//class TSales_item{
//public:
//    TSales_item(Item_base* ap) : p(ap), use(new int(1)){}
//    TSales_item(const TSales_item& rhs) : p(rhs.p), use(rhs.use){
//        ++*use;
//    }
//    TSales_item& operator=(const TSales_item& rhs){
//        ++*rhs.use;
//        if(--*use == 0) delete p;delete use;
//
//        use =  rhs.use;
//        p = rhs.p;
//        return *this;
//    }
//private:
//    Item_base* p;
//    int *use;
//};
//
//
//
//class IU_Ptr{
//private:
//    friend class IHasPtr;
//    IU_Ptr(int* ap=NULL) : p(ap) , use(1){}
//    ~IU_Ptr(){ delete p;}
//
//    int *p;
//    int use;
//};
//
//class IHasPtr{
//    IHasPtr(int *data) : p(new IU_Ptr(data)){}
//    ~IHasPtr(){delete p;}
//    IHasPtr(const IHasPtr& rhs) : p(rhs.p){ ++p->use;}
//    IHasPtr& operator=(const IHasPtr& rhs){
//        ++rhs.p->use;
//        if(--p->use == 0){
//            delete p;
//        }
//        p = rhs.p;
//        return *this;
//    }
//
//private:
//    IU_Ptr *p;
//};
//
//
//
//
//class node{
//public:
//    int data;
//    struct node* lch;
//    struct node* rch;
//
//
//    void dump(){
//        cout << " l=" << lch
//            << " r=" << rch
//            << " data=" << data
//            << endl;
//    }
//};
//
//struct ListNode {
//    int data;
//    ListNode* next;
//    };
//
//ostream& operator<<(ostream& os, const node& apNode)
//{
//    os << "l=" << apNode.lch << " r=" << apNode.rch << " d=" << apNode.data << endl;
//    return os;
//}
//
//ListNode* reverse_dev(ListNode* apNode){
//    ListNode *p,*q,*r;
//
//    if(NULL == apNode || NULL == apNode->next){
//        return apNode;
//    }
//
//    p = apNode;
//    q = apNode->next;
//
//    while ( q->next != NULL) {
//        r = q->next;
//        q->next = p;
//        p = q;
//        q = r;
//    }
//
//    return p;
//}
//
//void Order(int aiType, node* apNode){
//    if(DEF_ORDER_DLR == aiType)
//        cout << "(前）"<< (char)apNode->data << endl;
//
//    if(NULL != apNode->lch)
//        Order(aiType, apNode->lch);
//    if(DEF_ORDER_LDR == aiType)
//        cout << "(中）"<< (char)apNode->data << endl;
//
//    if(NULL != apNode->rch)
//        Order(aiType, apNode->rch);
//    if(DEF_ORDER_LRD == aiType)
//        cout << "(后）"<< (char)apNode->data << endl;
//
//}
//
//void preorder_dev(node* apNode){
//    stack<node*> s;
//
//    if(apNode){
//        while(apNode || !s.empty()){
//            while (apNode) {
//                //cout << "(前）"<< (char)apNode->data << endl;
//                s.push(apNode);
//                apNode = apNode->lch;
//            }
//
//            apNode = s.top();
//            s.pop();
//            cout << "(中）"<< (char)apNode->data << endl;
//            apNode = apNode->rch;
//        }
//    }
//}
//
//void levorder_dev(node* apNode){
//    queue<node*> q;
//    q.push(apNode);
//
//    while (!q.empty()) {
//        apNode = q.front();
//        q.pop();
//        cout << "(层）" << (char)apNode->data << endl;
//
//        if(apNode->lch) q.push(apNode->lch);
//        if(apNode->rch) q.push(apNode->rch);
//    }
//}
//
//node* search_dev(node* apNode, int aiData){
//    if(!apNode){
//        return NULL;
//    }
//    if(apNode->data == aiData){
//        return apNode;
//    }else{
//        if(!search_dev(apNode->lch,aiData)){
//            return search_dev(apNode->rch,aiData);
//        }
//        return apNode;
//    }
//
////    if(!apNode) return NULL;
////    if(aiData == apNode->data) return apNode;
////
////    return search_dev(apNode, aiData);
//}
////class TestRpc{
////public:
////    void say(){ cout << "hello." << endl;}
////};
////
////
////
////class TBase{
////public:
////    TBase(int t=0) : type(t){}
////
////    TBase(const TBase& rhs){
////        type = rhs.type;
////    }
////
////    virtual void display(int i)
////    {
////        cout << "TBase: " << type << " defalut:" << i << endl;
////    }
////
////    virtual void display(){
////        cout << "TBase: " << type << endl;
////    }
////
////private:
////    int type;
////};
////
////class Test : private TBase{
////public:
////    using TBase::display;
////
////    Test(const Test& rhs) : TBase(rhs){}
////
////    Test(const char* aName) {
////        name = std::string(aName);
////        cout << "直接构造函数" << endl;
////    }
////
//////    virtual void display(int i=101)
//////    {
//////        TBase::display();
//////        cout << "name: "<< name << " count:" << count <<" defalut:" << i << endl;
//////    }
////
////    void dis(){
////        TBase::display();
////    }
////public:
////
//////    Test(const Test& rhs){
//////        count = rhs.count;
//////        name = rhs.name;
//////
//////        cout << "复制构造函数" << endl;
//////    }
////private:
////    int count;
////    std::string name;
////};
////
////int main(int argc, const char * argv[]) {
////    int* ap = new int(100);
////    HasPtr hp(ap,10);
////    HasPtr hp1 = hp;
////
////    *(hp1.operator->()->ip) = 99;
////    cout << *(hp1.operator->()->ip) << " " << *(hp.operator->()->ip) << endl;
////    return 0;
////}
////p为树的根节点（已开辟动态内存）,str为二叉树的顺序存储数组ABCD##E或其他顺序存储数组，r当前结点所在顺序存储数组位置
//void creat(node* p, string str, int r)
//{
//    p->data = str[r];
//    if (str[r * 2 + 1] == '#' || r * 2 + 1 > str.size() - 1)p->lch = NULL;
//    else
//    {
//        p->lch = new node;
//        creat(p->lch, str, r * 2 + 1);
//    }
//    if (str[r * 2 + 2] == '#' || r * 2 + 2 > str.size() - 1)p->rch = NULL;
//    else
//    {
//        p->rch = new node;
//        creat(p->rch, str, r * 2 + 2);
//    }
//}
//
//vector<int> twoSum(vector<int>& nums, int target) {
//    map<int,int> loObjs;
//    vector<int> loRet;
//    map<int,int>::iterator liIter;
//
//    for(int index = 0; index<nums.size(); index++){
//        liIter = loObjs.find(target-nums[index]);
//        if(liIter != loObjs.end()){
//            loRet.push_back(index);
//            loRet.push_back(liIter->first);
//        }else{
//            loObjs.insert(map<int,int>::value_type(index,nums[index]));
//        }
//    }
//    return loRet;
//}
//
//ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
//    ListNode* ret = NULL;
//
//    std::stack<ListNode*> sList1;
//    std::stack<ListNode*> sList2;
//
//    while (l1 != NULL) {
//        sList1.push(l1++);
//    }
//
//    while (l2 != NULL) {
//        sList2.push(l2++);
//    }
//
//    ListNode *obj = new ListNode;
//    obj->data = 0;
//    obj->next = NULL;
//
//    while (!sList1.empty() || !sList2.empty()) {
//        int liData;
//        if(!sList1.empty()) {
//            liData = sList1.top()->data;
//            sList1.pop();
//        }
//        if (!sList2.empty()) {
//            liData += sList2.top()->data;
//            sList2.pop();
//        }
//
//        ListNode* tmp = new ListNode;
//        tmp->data = liData;
//        tmp->next = obj;
//
//        ret = obj = tmp;
//    }
//
//    return ret;
//}
//
//int maxProfit(vector<int>& prices) {
//    std::stack<int> st_min;
//    std::stack<int> st_max;
//    int max = 0;
//
//    st_min.push(prices[0]);
//    st_max.push(prices[0]);
//
//    for(int i = 1; i< prices.size(); i++){
//
//        if(prices[i] < st_min.top()){
//            st_min.push(prices[i]);
//            st_max.push(0);
//        }else if(prices[i] > st_max.top()){
//            st_max.pop();
//            st_max.push(prices[i]);
//        }
//    }
//
//    while(!st_min.empty()){
//        max = st_max.top() - st_min.top() > max ? st_max.top() - st_min.top() : max;
//        st_min.pop();
//        st_max.pop();
//    }
//
//    return max;
//}


//p为树的根节点（已开辟动态内存）,str为二叉树的顺序存储数组ABCD##E或其他顺序存储数组，r当前结点所在顺序存储数组位置
int main()
{
/*
 *二叉树排序
 */

//    node* p = new node;
//    //node* p = head;
//    //head = p;
//    string str;
//    cout << "please input:\n" << endl;
//    cin >> str;
//    creat(p, str, 0);//默认根节点在str下标0的位置
//
//    //Order(DEF_ORDER_DLR,p);
//    //Order(DEF_ORDER_LDR,p);
//    //Order(DEF_ORDER_LRD,p);
//    //levorder_dev(p);
//    node* t = search_dev(p, 'h');
//
//    char buff[30] = {0};
//    snprintf(buff, 10, "hello wor!");
//
//    cout << buff << endl;
//    if(t) cout << "找到了: " << *t << endl;
//
//    int arr[11] = {1,4,5,6,8,46,67,100,101,102,177};
//    int arr1[11] = {1,14,6,8,9,67,10,11,102,17,192};
//    //buddle_sort(arr, 7);
//    //quickSort(arr, 0, 6);
//    cout << binary_search(arr, 0, 10, 100) << endl;
//    qk_sort(arr, 0, 10);
//    for(int i=0;i<10;i++){
//        cout << arr[i] << endl;
//    }
//
//
//    vector<int> v_nums;
//    v_nums.push_back(4);
//    v_nums.push_back(7);
//    v_nums.push_back(1);
//    v_nums.push_back(2);
//    v_nums.push_back(8);
//    v_nums.push_back(5);
//    v_nums.push_back(0);
//    v_nums.push_back(1);
//    v_nums.push_back(2);
//    v_nums.push_back(8);
//    v_nums.push_back(5);
//
//    maxProfit(v_nums);
////
//    vector<int> ret = twoSum(v_nums, 10);
//    for(vector<int>::iterator liIter = ret.begin();
//        liIter != ret.end(); ++liIter){
//        cout << "#####" << *liIter << endl;
//    }
    //merge(arr, 0, 5, 10, ret);
    //heap_sort(arr1, 11);
//    _ListNode *a = new _ListNode;
//    _ListNode *b = new _ListNode;
//    _ListNode *c = new _ListNode;
//    _ListNode *d = new _ListNode;
//    _ListNode *e = new _ListNode;
//    _ListNode *f = new _ListNode;
//    _ListNode *g = new _ListNode;
//
//    a->data = 1;a->next = NULL;
//    b->data = 4;b->next=a;
//    c->data = 5;c->next=b;
//    d->data = 6;d->next=c;
//    e->data = 8;e->next=d;
//    f->data = 46;f->next=e;
//    g->data = 67;g->next=f;
//
//    reverse(g);
//    while(g){
//        cout << g->data <<endl;
//        g = g->next;
//    }
    
    
    return 0;
}

