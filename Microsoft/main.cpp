//
//  main.cpp
//  Microsoft
//
//  Created by fakewen on 9/16/17.
//  Copyright © 2017 Koshr. All rights reserved.
//

#include <iostream>
#include <stdio.h>//
#include <stdlib.h>
#include <unordered_map>
#include <queue>
#include <vector>
using namespace std;
class Node{
public:
    int val;
    Node* next;
    Node(int x){
        val=x;
        next=NULL;
    }
    ~Node(){
        val=777;
    }
};

vector<string> getRes(string s){
    int n=s.size();
    vector<string> res;
    for(int i=0;i<n-1;i++){
        for(int j=i+1; j<n;j++){
            if(s[j]-s[j-1]!=1){
                break;
            }
            if(j-i+1>=2){
                res.push_back(s.substr(i,j+1-i));
            }
        }
    }
    return res;
}
float avg(priority_queue<float> pq){
    long long sum=0;
    int cnt=0;
    while(!pq.empty() && cnt<5){
        sum+=pq.top();
        pq.pop();
        cnt++;
    }
        return (cnt==0)?0:(sum/cnt);
}
/*
 movie1 87
 movie22 24
 movie3 88
 movie1 90
 movie1 91
 movie1 22.3
 movie1 79.2
 movie1 99
 movie1 88
 (87+90+91+99+88)/5
 */
int main(int argc, const char * argv[]) {
    // insert code here...
    //std::cout << sizeof(int)<<endl;//4 byte
    /*
    int someInt =INT_MIN;
    char str[12];
    int n=sprintf(str,"%d",someInt);
    cout<<str<<endl;
    cout<<"len="<<n<<endl;
     */
    
    Node* n= new Node(3);
    cout<<n->val<<endl;
    Node* n1=new Node(4);
    n->next=n1;
    cout<<n1->val<<endl;
    
    //delete n1;
    free(n1);
    cout<<(n->next == NULL)<<endl;
    
    /*
    int k=13;
    int len=3;
    k %= len;
    cout<<"k="<<k<<endl;
    cout<<"len="<<len<<endl;
     */
    /*
    string in = "BCCDEG";
    auto ans=getRes(in);
    for(auto it:ans){
        cout<<it<<endl;
    }*/
    

    
    /*
    fp = fopen("/tmp/test.txt", "r");
    fscanf(fp, "%s", buff);
    printf("1 : %s\n", buff );
    
    fgets(buff, 255, (FILE*)fp);
    printf("2: %s\n", buff );
    
    fgets(buff, 255, (FILE*)fp);
    printf("3: %s\n", buff );
     */
    /*
    FILE *fp;
    char buff[255];
    fp = fopen("/tmp/test.txt", "r");
    unordered_map<string,priority_queue<float>> mp;
    while(1){
        if(fscanf(fp,"%s",buff)<=0)break;
        cout<<buff<<",";
        float rate;
        if(fscanf(fp,"%f",&rate)<=0)break;
        cout<<rate<<endl;
        mp[buff].push(rate);
    }
    cout<<"MP"<<endl;
    for(auto it:mp){
        cout<<it.first<<" : "<<avg(it.second)<<endl;
    }
    fclose(fp);
    */
    return 0;
}
