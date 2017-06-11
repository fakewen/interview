//Apr.4
// inplace_merge example
#include <iostream>     // std::cout
#include <algorithm>    // std::inplace_merge, std::sort, std::copy
#include <vector>       // std::vector
#include <time.h>
#include <queue>          // std::priority_queue
#include <map>
using namespace std;

//sort
//map
//priority_que
class Point{
public:
    int _a;
    int _b;
    Point(int a,int b):_a(a),_b(b){
    }
};
class mycomp{
public:
    int operator()(const Point& p1, const Point& p2)const{
        return (p1._a + p1._b)>(p2._a + p2._b);
    }
};
int main () {
    vector<Point> vp;
    vp.emplace_back(1, 2);
    vp.emplace_back(3, -222);
    vp.emplace_back(-1, 2);
    sort(vp.begin(),vp.end(),mycomp());
    for(auto it:vp){
        cout<<"[sort vector]"<<it._a<<" , "<<it._b<<endl;
    }
    
    map<Point,int,mycomp> mp;
    /*
    Point* p1=(new Point(1,2));
    Point p1o=*p1;
    mp[p1o]=3;*/
    mp.emplace(Point(1,2),1);
    mp.emplace(Point(3,-222),2);
    mp.emplace(Point(-1,2),3);
    for(auto it:mp){
        cout<<"[order map]"<<it.first._a<<" , "<<it.first._b<<" = "<<it.second<<endl;
    }
    //min_heap
    priority_queue<Point,vector<Point>,mycomp> pq;
    pq.emplace(Point(1,2));//???
    pq.emplace(Point(3,-222));
    pq.emplace(Point(-1,2));
    while(!pq.empty()){
        auto tmp = pq.top();
        pq.pop();
        cout<<"[minHeap]"<<tmp._a<<" , "<<tmp._b<<endl;
    }
    return 0;
}
