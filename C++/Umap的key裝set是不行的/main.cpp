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
#include <unordered_set>//unordered_set
#include <unordered_map>
#include <set>
#include <map>

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

#include <thread>         // std::thread
#include <mutex>          // std::mutex
#include <stdio.h>

#include <iostream>
#include <sstream>

#include <thread>
#include <fstream>

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
/*
 class mycomp{
 public:
 int operator()(Node* n1, Node* n2){//*?
 return (pow((n1->_x - p->_x),2) + pow((n1->_y - p->_y),2))<(pow((n2->_x - p->_x),2) + pow((n2->_y - p->_y),2));
 }
 };
 */
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
void unint(){
    int i;
    cout<<"fun"<<i<<endl;
}
int gint;
/*
 void cfunc(const dlNode* in){
 in->val=711;
 cout<<in->val;
 }*/
double ifd(int i){
    cout<<"int"<<endl;
    return i;
}
double ifd(float i){
    cout<<"float"<<endl;
    return i;
}
double ifd(double i){
    cout<<"double"<<endl;
    return i;
}
struct str{
    int aP;
};

struct mycomp{
    
    int operator()(vector<int>& a,vector<int>& b){
        if(a[0]!=b[0]){
            return a[0]<b[0];
        }else if(a[1]!=b[1]){
            return a[1]<b[1];
        }else{
            if(a[1]==0){
                return a[2]>b[2];
            }else{
                return a[2]<b[2];
            }
        }
    }
};


void foo()
{
    cout<<"Foo"<<endl;
    // do stuff...
}

void bar(int x)
{
    cout<<"Bar"<<endl;
    // do stuff...
}
std::mutex mtx;           // mutex for critical section

void print_thread_id (int id,string in) {
    // critical section (exclusive access to std::cout signaled by locking mtx):
    mtx.lock();
    std::cout << "thread #" << id <<"[stri]"<<in<< '\n';
    mtx.unlock();
}
int ncom(int in){
    int ans=0;
    string bs="";
    while(in){
        bs=( (in%2==1)? "1":"0" )+bs;
        in/=2;
    }
    auto found= bs.find_first_of("1");
    found= bs.find_first_of("0",found+1);
    while(found<bs.size()){
        ans=ans*2+( (bs[found++]=='1')? 0:1);
    }
    return ans;
}


int nColorS(vector<int>& in){
    int len=in.size();
    int i=0,j=len-1;
    int ans=0;
    while(i<=j){
        if(in[i]%2==0){
            i++;
        }else if( in[j]%2==1){
            j--;
        }else{
            swap(in[i++], in[j--]);
            ans++;
        }
    }
    
    return ans;
}

void test_func()
{
    // do something
    double dSum = 0;
    for( int i = 0; i < 10000; ++ i )
        for( int j = 0; j < 10000; ++ j )
            dSum += i*j;
    
    cout << "Thread: " << dSum << endl;
}

class TrieNode{
public:
    map<char,TrieNode*> next;//unordered_
    bool is_word;
    string word;
    //init
};
TrieNode* root;
void add(string s){
    TrieNode* r=root;
    for(int i=0;i<s.size();i++){
        if(r->next.find( s[i] ) ==r->next.end() ){
            r->next[s[i]]=new TrieNode();
        }
        r=r->next[s[i]];
    }
    r->is_word=true;
    r->word=s;
}
void buildTrie(vector<string> in){
    root=new TrieNode();
    for(auto& it:in){
        add(it);
    }
}
void findEach(TrieNode* r,vector<string>& ans){
    if(!r)return;
    //cout<<"hi"<<endl;
    if(r->is_word){
        //cout<<"is_woRD="<<r->word<<endl;
        ans.push_back(r->word);
    }
    for(auto& it: r->next){
        findEach(it.second , ans);
    }
}
void findSucc(TrieNode* r, char p,vector<string>& ans){
    
    for(auto& it=(++r->next.find(p)) ;it!=r->next.end() ;it++ ){
        findEach(it->second,ans);
    }
}
void find3(string pre){
    TrieNode* r=root;
    int i=0;
    vector<TrieNode*> path;
    path.push_back(r);
    for(;i<pre.size() && r->next.find(pre[i])!=r->next.end() ;i++){
        r=r->next[ pre[i] ];
        path.push_back(r);
    }
    if(i!=pre.size() ){
        cout<<"[]not3 with exactly with PRE"<<endl;
        return;//
    }else{
        //print cur 3
        vector<string> ans;
        findEach(r,ans);
        cout<<"[]exactly with PRE SIZE="<<ans.size()<<endl;
        int need=3;
        
        //if <3 match the lase pre[i]
        int l=pre.size()-1;//pre[0,len-1]
        //path[0,len-1]
        while(l>=0 && ans.size() <need){
            cout<<"[]Need More"<<endl;
            path.pop_back();
            //cout<<"[findSucc@para]"<<
            findSucc(path.back(), pre[l],ans);//root....r[len-1] pre[len-1]>>>從r[len-2]開始找
            l--;
        }
        for(int i=0;i<ans.size() && i<need ;i++){
            cout<<"[ans]"<<ans[i]<<endl;
        }
    }
    //if no pre,cout NOthing
    
    //if pre has enough 3, print the, all
    
    //if not enough, print 1. and trace back List, and find pre[r--]
}
void npq(int n, int p, int q){
    for(int i=0;i<=n;i++){
        cout<<i<<":";
        if(i%p==0 && i%q==0){
            cout<<"OUTTHINK";
        }else if(i%p==0){
            cout<<"OUT";
        }else if(i%q==0){
            cout<<"THINK";
        }
        cout<<endl;
    }
}

void npq2(int n, int p, int q){
    for(int i=0;i<=n;i++){
        cout<<i<<":";
        //strin 2 int
        //stoi(string)
        //int 2 string
        //to_string(int)
        //const char* ip=strstr( to_string(i).c_str() , to_string(p).c_str() );
        //const char* iq=strstr( to_string(i).c_str() , to_string(q).c_str() );
        bool iq= ( strstr( to_string(i).c_str() , to_string(q).c_str() )!=NULL );
        if(i%p==0 && iq){
            cout<<"OUTTHINK";
        }else if(i%p==0){
            cout<<"OUT";
        }else if(iq){
            cout<<"THINK";
        }
        cout<<endl;
    }
}

vector<string> sold(vector<string> input){
    vector<string> ans;
    
    if(input.size()==0)return ans;
    map<string, int> quantity ;
    unordered_map<string, unordered_set<string>> fruit;
    
    for(string curr:input){
        stringstream iss(curr);
        vector<string> temp(3); int i=0;
        while(i<3 && getline(iss,temp[i++],',')){
            
        }
        quantity[ temp[0] ] += stoi(temp[1]);
        fruit[ temp[0] ].insert(temp[2]);
    }
    for(auto& curr:quantity){
        string tmpAns="";
        string date = curr.first;
        int sold=curr.second;
        int type=fruit[ date ].size();
        double avg = (double) sold/type;
        tmpAns=date+","+to_string(sold)+","+to_string(avg)+","+to_string(type);
        ans.push_back(tmpAns);
    }
    
    
    return ans;
}
void find(int a){
    cout<<"hi Find"<<endl;
}
class ttt{
public:
    int a=3351;
    vector<int> vi;//(26);
    ttt(){
        a=666;
        vi=vector<int>(26,7);
    }
};
void DoC(char cc[]){
    cout<<cc<<"[]"<<endl;
    cout<<sizeof(cc)<<endl;
    //*cc='k';
    //cout<<cc<<endl;
}
fstream infile("/Users/fakewen/Documents/找工作/FB/asdg");
string line="";
int il=0;
int read4(char* buf4){
    int i=0;
    while(i<4){
        if(il >= line.size()){
            while(getline(infile,line) ){
                if(line.size()!=0)break;
            }
            il=0;
            if(line.size()==0)return i;
        }
        buf4[i++]=line[il++];
    }
    return i;
}
class DL{
public:
    int key;
    int val;
    DL* pre;
    DL* next;
    DL(int a,int b){
        key=a;
        val=b;
    }
};
vector<vector<int>> twoSum(vector<int>& nums, int tar ,int block){
    vector<vector<int>> ans;
    int len= nums.size();
    if(len<2)return ans;
    
    unordered_set<int> s;
    unordered_map<int,int> mp;//val,cnt
    
    for(int i=0;i<len;i++){
        if(i==block)continue;
        int key1=nums[i], key2=tar-nums[i];
        if(mp.count(key2)  && mp[key2]>0 ){//這樣還是沒distinct啊........
            int m=min(key1,key2), M=max(key1,key2);
            
            if(!s.count(m) && !s.count(M)){
                s.insert(m);
                s.insert(M);
                ans.push_back({m,M});
            }
            mp[key2]--;
            //ans.push_back({m,M});//後面每個都去找 1st 的1
        }else{
            mp[key1]++;
        }
    }
    return ans;
}

vector<vector<int>> threeSum(vector<int>& nums, int tar){
    vector<vector<int>> ans;
 
    unordered_map<int, unordered_set<int> > mp;//1st val , set<2nd val>
    //unordered_set<int> s;
    for(int i=0;i<nums.size() ; i++){
        if( mp.count(nums[i]) )continue;
//        s.insert(nums[i]);
        vector<vector<int>> tmp2Ans=twoSum(nums,tar-nums[i],i);
        for(vector<int> it: tmp2Ans){
            //it = 2nd,3rd
            vector<int> tmpAns={nums[i] , it[0] , it[1]};
            //sort(tmpAns.begin() , tmpAns.end());
            if(nums[i]>=it[1]){
                tmpAns={ it[0] , it[1] , nums[i]};
            }else if( nums[i]>=it[0] ){
                tmpAns={ it[0] , nums[i] , it[1] };
            }
            if(mp[ tmpAns[0] ].count( tmpAns[1] ) ){
                continue;
            }else{
                mp[ tmpAns[0] ].insert( tmpAns[1] );
                ans.push_back(tmpAns);
            }
        }
        //s.insert
    }

    return ans;
}
//http://www.1point3acres.com/bbs/thread-201860-1-1.html
int main(int argc, const char * argv[]) {
    unordered_map<string,set<string>> mp;//ok
    unordered_map<string,unordered_set<string>> mp2;//ok
    map<string,set<string>> mp3;//ok
    map<string,unordered_set<string>> mp4;//ok
    
    //unordered_map<unordered_set<string>,string> mp11;//no
    //unordered_map<set<string>,string> mp12;//no
    map<unordered_set<string>,string> mp21;//ok
    map<set<string>,string> mp22;//ok
    /*
    vector<int> v={1,3,2};
    queue<long int, std::deque<long int>> q(  deque<long int>(v.begin(), v.end())  );
    cout<<"q_size="<<q.size();
    while(!q.empty()){
        cout<<"[front]"<<q.front()<<endl;
        q.pop();
    }*/
    /*
    vector<int> in={-4,-2,1,-5,-4,-4,4,-2,0,4,0,-2,3,1,-5,0};
    vector<vector<int>> ans=threeSum(in, 0);
    for(auto& it:ans){
        cout<<"[]"<<it[0]<<"\t,"<<it[1]<<"\t,"<<it[2]<<endl;
    }
     */
    /*
    vector<int> in={1,1,1,2,2};//{-4,-2,1,-5,-4,-4,4,-2,0,4,0,-2,3,1,-5,0}
    //[1, 4, -5]
    vector<vector<int>> ans=twoSum(in, 3,-1);
    //vector<vector<int>> ans=twoSum(in, 2 , -1);
    for(auto& it:ans){
        cout<<"k1="<<it[0]<<"k2="<<it[1]<<endl;
    }
    */
    
    //DL* dl1=new DL(1,2),dl2=new DL(2,2);
    /*
    string s="abc";
    char d='d';
    s+=d;
    cout<<s<<"[]"<<endl;
    */
    /*
    stringstream ss("ab cd");
    for(int i=0;i<6;i++){
        string tmp;
        ss>>tmp;
        cout<<"[]"<<tmp<<"[]"<<endl;
    }*/
    /*
    vector<int> a={-1,3,3,3,-4};
    unordered_set<int> set(a.begin(),a.end());
    for(auto& it:set){
        cout<<"[]"<<it<<endl;
    }*/
    /*
    string s="654376531";
    int c=s.find("3");
    cout<<"c="<<c<<endl;
    int a=stoi(s);
    cout<<a<<endl;
    */
    
    /*
    char buf4[4];
    int len=0;
    while( ( len=read4(buf4) )!=0 ){
        for(int i=0;i<len;i++){
            cout<<buf4[i];
        }cout<<"[]"<<endl;
    }*/
    /*
    char c;
    while(infile>>c){//這樣會跳過Space
        cout<<"inFile"<<endl;
        cout<<c<<endl;
    }*/
    /*
    string line;
    while(getline(infile,line)){
        cout<<line<<"-"<<endl;
    }*/
    
    /*
    char* cc="cccc";
    DoC(buf4);
     */
    //char cc[]="cccc";
    /*
    cc[3]='g';
    cout<<*(cc+3)<<endl;
    */
    //DoC(cc);
    
    /*
    ttt t;
    cout<<t.a<<endl;
    cout<<t.vi[13]<<endl;
    ttt* t1=new ttt();
    cout<<t1->a<<endl;
    cout<<t1->vi[13]<<endl;
     */
    /*
    stringstream ss;
    ss<<"in,,2,,,,3,,,4";
    string tmpAns;
    while( getline(ss,tmpAns,',') ){
        cout<<tmpAns<<endl;
    }
     */
    /*
    std::stringstream stringStream(" in,   , 2  ;g; ,  ,,,3,,,4");
    std::string line;
    vector<string> ans;
    while(std::getline(stringStream, line))//getline沒第三參數，只是隔開\n
    {
        size_t pre=0, pos;
        while( ( pos=line.find_first_of(" ,:;|",pre) ) !=string::npos  ){
            if(pre<pos){
                ans.push_back( line.substr(pre,pos-pre) );
            }
            pre=pos+1;
        }
        if(pre<line.size()){
            ans.push_back( line.substr(pre) );
        }
    }
    for(auto& it:ans){
        cout<<"[]"<<it<<"[]"<<endl;
    }
    */
    /*
    try{
        int a=stoi("abd");
        //int a=stoi("123");
        cout<<a<<endl;
    }catch(exception& a){
        cout<<"catch"<<endl;
    }
    vector<string> vs={"gcd","g","a","ac","ab","abc","aa"};
    sort(vs.begin(), vs.end());
    for(auto& it:vs){
        cout<<it<<endl;
    }
    cout<<"@@@";
    find(3);
    */
    /*
    std::vector<int> myvector;
    
    // set some values:
    for (int i=1; i<10; ++i) myvector.push_back(i);   // 1 2 3 4 5 6 7 8 9
    
    std::reverse(myvector.begin(),myvector.begin()+3);    // 9 8 7 6 5 4 3 2 1
    
    // print out content:
    std::cout << "myvector contains:";
    for (std::vector<int>::iterator it=myvector.begin(); it!=myvector.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
    
    map<int,string> mp;
    mp[1]="11";
    mp[3]="33";
    cout<<"mp22="<<mp[2]<<"[]"<<endl;
     */
//FB
    /*
    std::thread first (foo);     // spawn new thread that calls foo()
    std::thread second (bar,0);  // spawn new thread that calls bar(0)
    
    std::cout << "main, foo and bar now execute concurrently...\n";
    
    std::cout << "foo and bar completed.\n";
    
    // synchronize threads:
    first.join();                // pauses until first finishes
    second.join();               // pauses until second finishes
    */
    /*
    std::thread threads[10];
    // spawn 10 threads:
    for (int i=0; i<10; ++i)
        threads[i] = std::thread(print_thread_id,i+1,"affs");
    
    for (auto& th : threads) th.join();
*/
    /*
    std::string input = "abc def  ghi";
    std::istringstream ss(input);
    std::string token;
    
    string tmp;
    while(ss>>tmp) {
        std::cout << tmp << '\n';
    }
     */
    //find();
    /*
    stringstream iss("a bc d ");
    string tmp;
    while(iss>>tmp){
        cout<<"[]"<<tmp<<endl;
    }
    */
    //cout<<ncom(50)<<endl;
    //cout<<ncom(100)<<endl;
    /*
    vector<int> in={13,10,21,20};
    cout<< nColorS(in) <<endl;
     */
    /*
    string s;
    //if(s != NULL){
    cout<<"[og s]"<<s<<"[end]"<<endl;
    //}
    s="hi FB";
    cout<<"[fb s]"<<s<<endl;
    return 0;
     */
    
    /*
    // execute thread
    thread mThread( test_func );
    
    // do somthing
    cout << "main thread" << endl;
    
    // wait the thread stop
    mThread.join();
     */
    /*
    string ss="a";
    ss=ss+'c'+"d";
    cout<<ss<<endl;
    //int stop=-1;
    enum Action{stop = 1, sit, stand = 3, walk, run};
    
    Action a=stop;
    Action b= walk;
    cout<<a<<endl;
    cout<<b<<endl;
      */
    
    /*
    string OGin="ACETA ASPERGEL ATAVAN BUPROPION";// AV
    stringstream iss(OGin);
    vector<string> in;
    string tmp;
    while(iss>>tmp){
        in.push_back(tmp);
    }
    for(auto& it:in){
        cout<<it<<endl;
    }
    cout<<"##Cin Above###"<<endl;
    //
    buildTrie(in);
    //find3("A");
    find3("AS");
     */
    //cout<<
    //npq(10,2,5);
    //npq2(50,2,5);
    /*
    string a="abcdabc";
    string b="cd";
    auto ans=strstr(a.c_str(),b.c_str());
    if(ans!=NULL){
        cout<<"[Idx@]"<<(  ans - a.c_str())<<endl;
    }
     */
    /*
    std::string str = "10,29,3,4,5,6";
    std::vector<int> vect;
    
    std::stringstream ss(str);
    
    int i;
    
    while (ss >> i)
    {
        vect.push_back(i);
        
        if (ss.peek() == ',')
            ss.ignore();
    }
    
    for (i=0; i< vect.size(); i++)
        std::cout << vect.at(i)<<std::endl;
     */
    /*
    stringstream ss( "1,4sdg9,1,1, or something else ,88" );
    vector<string> result(10);

    string tmpAns;
    int i=0;
    while(getline(ss,result[i++],',')){
        //result.push_back(tmpAns);
    }
    for(auto& it: result){
        cout<<it<<endl;
    }*/
    /*
    vector<string> input={"d1,11,f1" ,"d1,22,f2","d2,33,f2"};
    vector<string> ans=sold(input);
    for(auto& it:ans){
        cout<<"sold:"<<it<<endl;
    }*/
    return 0;
}



















