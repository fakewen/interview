#include <iostream>
using namespace std;

class Foo1 {
public:
    virtual void show() { // 虛擬函式
        cout << "Foo1's show" << endl;
    }
};

class Foo2 : public Foo1 {
public:
    virtual void show() override{ // 虛擬函式
        cout << "Foo2's show" << endl;
    }
    void show2() {
        cout<<"[Foo2]show2"<<endl;
    }
};

void showFooByPtr(Foo1 *foo) {
    foo->show();
}

void showFooByRef(Foo1 &foo) {
    foo.show();
}

int main() {
    Foo1* f1;
    Foo2 f2;
    f1=&f2;
    f1->show();//有virtual 又有ptr/ref動態連結 Foo2's show
    /*
    // 動態繫結
    showFooByPtr(&f1);
    showFooByPtr(&f2);
    cout << endl;
    
    // 動態繫結
    showFooByRef(f1);
    showFooByRef(f2);
    cout << endl;
    
    // 靜態繫結
    f1.show();
    f2.show();
    */
    return 0;
}
