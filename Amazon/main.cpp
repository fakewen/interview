//
//  main.cpp
//  Amazon
//
//  Created by fakewen on 9/10/17.
//  Copyright © 2017 Koshr. All rights reserved.
//

#include <iostream>     // std::cout
#include <algorithm>    // std::inplace_merge, std::sort, std::copy
#include <vector>       // std::vector
#include <time.h>
#include <queue>          // std::priority_queue
#include <map>
#include <math.h>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>
using namespace std;

int _max,_start,_end;
void findPalindrome(string s, int l, int r){
    while(l-1>=0 && r+1<s.size() && s[l-1]==s[r+1]){
        l--;
        r++;
    }
    if( (r-l+1)>_max ){
        _max=r-l+1;
        _start=l;
        _end=r;
    }
}
string longestpalindrome(string s){
    _max=0;
    _start=0;
    _end=0;
    if(s.size()==0 || s.size()<2)return s;
    for(int i=0;i<s.size();i++){
        findPalindrome(s, i, i);
        if(i+1<s.size() && s[i]==s[i+1])findPalindrome(s, i, i+1);
    }
    return s.substr(_start,_max);
}


class Point{
public:
    int x;
    int y;
    Point(int a,int b){
        x=a;
        y=b;
    }
};
Point* org_;
//want Max heap , k size
class pComp{
public:
    int operator()(Point* a, Point* b){
        //a og_ < b og_
        return ( ( (a->x - org_->x)*(a->x - org_->x)+(a->y - org_->y)*(a->y - org_->y)  )<( (b->x - org_->x)*(b->x - org_->x)+(b->y - org_->y)*(b->y - org_->y)  ) );
    }
};

vector<Point*> kNearestPoint(vector<Point*> array, Point* org, int k){
    org_=org;
    vector<Point*> rvalue(k);
    if(k<=0 || k<array.size())return rvalue;
    int index=0;
    priority_queue<Point*, vector<Point*>, pComp> pq;
    for(int i=0;i<array.size();i++){
        pq.push(array[i]);
        if(pq.size() > k){
            pq.pop();
        }
    }
    while(!pq.empty()){
        rvalue[index++]=pq.top();
        pq.pop();
    }
    return rvalue;
}

class Node{
public:
    double _x;
    double _y;
    Node(double x,double y):_x(x),_y(y){}
};
Node* p;
class mycomp{
public:
    int operator()(Node* n1, Node* n2){//*?
        return (pow((n1->_x - p->_x),2) + pow((n1->_y - p->_y),2))<(pow((n2->_x - p->_x),2) + pow((n2->_y - p->_y),2));
    }
};

class ListNode{
public:
    int val;
    ListNode* next;
    ListNode(int x){
        val=x;
        next=NULL;
    }
};
ListNode* LinkedListInsert(ListNode* head, int val){
    if(head==NULL){
        ListNode* rvalue = new ListNode(val);
        rvalue->next = rvalue;
        return rvalue;
    }
    
    ListNode* cur =head;
    
    do{
        if(val<=cur->next->val && val>=cur->val)break;
        if(cur->val>cur->next->val && (val<cur->next->val || val>cur->val))break;
        cur = cur->next;
    }while(cur != head);
    
    ListNode* newNode = new ListNode(val);
    newNode->next = cur->next;
    cur->next = newNode;
    return newNode;
        
}

vector<vector<int>> dir={ {1,0},{-1,0},{0,1},{0,-1} };
int checkMaze(vector<vector<int>>& maze){
    if(maze.size()==0 || maze[0].size()==0 || maze[0][0]==0)return 0;
    if(maze[0][0]==9)return 1;
    int m=maze.size(), n=maze[0].size();
    queue<vector<int>> q;//[x][y]
    q.push({0,0});
    maze[0][0]=0;//BFS走過關門
    while(!q.empty()){
        auto p=q.front();
        q.pop();
        for(int k=0;k<4;k++){
            int x=p[0]+dir[k][0];
            int y=p[1]+dir[k][1];
            if(x>=0 && x<m && y>=0 &&y<n){
                if(maze[x][y]==0)return 1;
                else if(maze[x][y]==1){
                    q.push({x,y});
                    maze[x][y]=0;
                }
            }
        }
    }
    return 0;//BFS走到底還走不到９
}

class process{
public:
    int arrTime;
    int exeTime;
    process(int arr,int exe){
        arrTime=arr;
        exeTime=exe;
    }
};
float RR(vector<int> Atime,vector<int> Etime, int q){
    if(Atime.size()==0 || Etime.size()==0 || Atime.size()!=Etime.size())return 0;
    int length=Atime.size();
    queue<process*> que;
    int curTime=0, waitTime=0;//curTime每次節算waitTime時的curTime,+=exe OR q//waitTime==總等待時間
    int index=0;
    while(!que.empty() || index<length){
        if(!que.empty()){
            process* cur=que.front();
            que.pop();
            waitTime += (curTime - cur->arrTime);//現在時間-一開始得等待時間
            curTime+=min(cur->exeTime,q);//有些工作很短 不需要q時間
            for(;index<length && Atime[index]<=curTime;index++){//加新的進來
                que.push(new process(Atime[index],Etime[index]) );
            }
            if(cur->exeTime > q){
                que.push(new process(curTime,cur->exeTime - q));//這是沒跑完的，開始時間要換歐
            }
        }else{//一開始得時候//但之後要等que裡的pop玩心得才能進？第89行會家其他人，第93行會加還沒執行完的自己
            que.push(new process(Atime[index],Etime[index]));
            curTime = Atime[index++];
        }
    }
    return (float)waitTime/length;
}
class sjfComp{
public:
    int operator()(process* p1, process* p2){//*?
        return ( (p1->exeTime==p2->exeTime)?(p1->arrTime > p2->arrTime):(p1->exeTime>p2->exeTime) );
    }
};
float SJF(vector<int> req, vector<int> dur){
    if(req.size()==0 || dur.size()==0 || req.size()!=dur.size())return 0;
    int index=0, length=req.size();
    int waitTime=0, curTime=0;
    priority_queue<process*,vector<process*>,sjfComp> pq;
    
    while(!pq.empty() || index<length){
        if(!pq.empty()){
            process* cur = pq.top();
            pq.pop();
            waitTime += curTime - cur->arrTime;
            curTime +=cur->exeTime;
            while(index<length && curTime>=req[index]){
                pq.push(new process(req[index],dur[index++]));
            }
        }else{
            pq.push(new process(req[index],dur[index]));
            curTime = req[index++];
        }
    }
    
    return (float)waitTime/length;
}

vector<int> daysChange(vector<int> days, int n){
    if(days.size()==0 || n<=0)return days;
    int length = days.size();
    vector<int> rvalue=vector<int>(length+2);
    rvalue[0] = rvalue[length+1]=0;
    
    for(int i=1;i<=length;i++){
        rvalue[i] = days[i-1];
    }
    for(int i=0;i<n;i++){
        int pre =rvalue[0];//?????
        for(int j=1;j<=length;j++){
            int temp=rvalue[j];
            rvalue[j] =pre^rvalue[j+1];
            pre=temp;
        }
    }
    vector<int> ans(rvalue.begin()+1,rvalue.end()-1);
    //std::vector<int> third (second.begin(),second.end());
    return ans;
}

vector<int> fInt(int A,int B, int C, int D){
    vector<int> rvalue(4);
    rvalue[0]=A;
    rvalue[1]=B;
    rvalue[2]=C;
    rvalue[3]=D;
    sort(rvalue.begin(),rvalue.end());
    swap(rvalue[0],rvalue[1]);
    swap(rvalue[2],rvalue[3]);
    swap(rvalue[0],rvalue[3]);
    return rvalue;
}
class dlNode{
public:
    int val;
    dlNode* pre;
    dlNode* next;
    dlNode(int x){
        val=x;
        pre=NULL;
        next=NULL;
    }
};
int lru(vector<int> array, int size){
    if(array.size()==0)return 0;
    if(size==0)return array.size();
    //map & Double-linkedList
    unordered_map<int,dlNode*> mp;//val , ref=NULL
    dlNode* dummyHead=new dlNode(0);
    dlNode* dummyEnd=new dlNode(0);
    int count=0;
    for(int i=0;i<array.size();i++){
        if(mp.find(array[i])!=mp.end() ){
            //move it to head
            //update it to mp, no need?
            mp[array[i]]->pre->next=mp[array[i]]->next;
            mp[array[i]]->next->pre=mp[array[i]]->pre;
            
            mp[array[i]]->pre=dummyHead;
            mp[array[i]]->next=dummyHead->next;
            
            dummyHead->next->pre=mp[array[i]];
            dummyHead->next=mp[array[i]];
        }else{
            count++;
            if(size == mp.size()){
                //update LESS @ mp to NULL
                //remove the last
                dummyEnd->pre=dummyEnd->pre->pre;
                dummyEnd->pre->next=dummyEnd;
                
                mp.erase(array[i]);
            }
            //add to Head
            //add to mp
            dlNode* tmp=new dlNode(array[i]);
            tmp->pre=dummyHead;
            tmp->next=dummyHead->next;
            dummyHead->next->pre=tmp;
            dummyHead->next=tmp;
            mp[array[i]]=tmp;
            
        }
    }
    return 0;
}

class Order{
public:
    string orderName;
    Order(string x){
        orderName=x;
    }
};
class OrderDependency{
public:
    Order* order;
    Order* dependent;
    OrderDependency(Order* x,Order* y){
        order=x;
        dependent=y;
    }
};
vector<Order*> findOrder(vector<OrderDependency*> depenency){
    
    //用Ordered_map以免她需要字母排序
    map<string,int> inmp;//string, cnt[in輸入degree]
    map<string, vector<string>> outmp;
    for(OrderDependency* i: depenency){
        if(inmp.find(i->dependent->orderName)==inmp.end()) inmp[i->dependent->orderName]=0;
        if(inmp.find(i->order->orderName)==inmp.end()) inmp[i->order->orderName]=0;
        //inmp[i->order->orderName]=(inmp[i->order->orderName]+1);
        inmp[i->order->orderName]++;
        if(outmp.find(i->dependent->orderName)==outmp.end()){
            outmp[i->dependent->orderName]=vector<string>();
        }
        outmp[i->dependent->orderName].push_back(i->order->orderName);
    }
    vector<Order*> res;
    queue<string> que;
    for(auto it:inmp){
        if(inmp[it.first]==0)que.push(it.first);
    }
    while(!que.empty()){
        string s= que.front();
        que.pop();
        res.push_back(new Order(s));
        if(outmp.find(s)!=outmp.end()){
            for(string o:outmp[s]){
                //inmp[o]=(inmp[o]-1);
                inmp[o]--;
                if(inmp[o]==0)que.push(o);
            }
        }
        outmp.erase(s);
    }
    
    return res;
}

class Connection{
public:
    string node1;
    string node2;
    int cost;
    Connection(string a,string b,int c){
        node1=a;
        node2=b;
        cost =c;
    }
};
class DisjoinSet{
public:
    unordered_set<string> set;
    unordered_map<string,string> mp;
    int count;
    DisjoinSet(){
        count=0;
        //set&map
    }
    void MakeSet(string s){
        if(set.find(s)==set.end()){
            count++;
            set.insert(s);
            mp[s]=s;
        }
    }
    string Find(string s){
        if(set.find(s)==set.end())return NULL;
        if(mp[s] == s)return s;
        string root = Find(mp[s]);
        mp[s]=root;
        return root;
    }
    void Union(string s,string t){
        if(set.find(s)==set.end() || set.find(t)==set.end())return;
        if(s==t)return;
        count--;
        mp[s]=t;//阿不用反過來？mp[t]=s?
    }
};
class ConnectionComparator1{
public:
    int operator()(Connection a, Connection b){
        return a.cost < b.cost;
    }
};
class ConnectionComparator2{
public:
    int operator()(Connection a, Connection b){
        return ( (a.node1==b.node1)?(a.node2<b.node2):(a.node1<b.node1) );
    }
};
// Overlap Rectangle
/*
        AB,EF
                CD,GH
 */

// Rect 1: top-left(A, B), bottom-right(C, D)
// Rect 2: top-left(E, F), bottom-right(G, H)
int computeArea(int A,int B,int C,int D, int E, int F, int G, int H){
    int innerL=max(A,E);
    int innerR=max(min(C,G),innerL);
    int innerB=max(D,H);
    int innerT=max(min(B,F),innerB);
    return (C-A)*(B-D) - (innerR-innerL)*(innerT-innerB) + (G-E)*(F-H);
}

vector<int> GetSum(vector<int> A, int k){
    vector<int> result;
    if(A.size()==0 || k<=0)return result;
    vector<int> rvalue(max(1,(int)A.size()-k+1));
    for(int i=0;i<k;i++){
        rvalue[0] +=A[i];
    }
    for(int i=1;i<rvalue.size();i++){
        rvalue[i]=rvalue[i-1]-A[i-1]+A[i+k-1];
    }
    return rvalue;
}

int main(int argc, const char * argv[]) {
    //vector<vector<int>> maze={{1, 0, 0, 1}, {1, 1, 1, 1}, {1, 0, 0, 9}};
    //print
    //checkMaze
    //cout<<RR({0,1,3,9},{2,1,7,5},2)<<endl;
    //cout<<SJF({1, 3, 3, 6, 6, 6, 7},{2 ,2 ,3 ,2, 4, 4, 2})<<endl;
    /*
    vector<int> input = {1,0,0,0,0,1,0,0};
    vector<int> output = daysChange(input, 4);
    for(int i: output){
        cout<<i;
    }cout<<endl;
    */
    /*
    vector<int> nums = fInt(1, 3, 2, 4);
    for(int i: nums) cout<<i<<" ";
    cout<<endl;*/
    vector<OrderDependency*> input;
    input.push_back(new OrderDependency(new Order("A"),new Order("E")) );
    input.push_back(new OrderDependency(new Order("D"),new Order("E")) );
    input.push_back(new OrderDependency(new Order("A"),new Order("C")) );
    input.push_back(new OrderDependency(new Order("B"),new Order("D")) );
    
    vector<Order*> output = findOrder(input);
    for(Order* i: output)cout<<i->orderName <<" ";
    cout<<endl;

    return 0;
}



















