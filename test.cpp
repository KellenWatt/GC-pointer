#include <iostream>
#include "gcpointer.h"
using std::cout;
using std::endl;

struct complex {
    int real;
    int i;
    friend std::ostream& operator<<(std::ostream& out, complex c) {
        out << c.real << " + " << c.i << "i";
        return out;
    }
};

int main() {
    auto p = gnew<int>(25);
    auto q = p;
    auto r = gnew<const char*>("hello world");

    // doesn't even remotely work. Need to do a specialization for this.
    auto a = gnew<int[5]>();
    for(int i=0; i<5; i++) {
        a[i] = i+1;
    }

    auto c = gnew<complex>();
    c->real = 2;
    c->i = 12;

    cout << "value p: " << *p << endl;
    cout << "value q: " << *q << endl;
    cout << "value r: " << *r << endl;
    cout << "refcount p: " << *p.refcount << endl;
    cout << "refcount q: " << *q.refcount << endl;
    cout << "refcount r: " << *r.refcount << endl;

    cout << "value c: " << *c << endl;

    for(int i=0; i<5; i++) {
        cout << "value a[" << i << "]: " << *(a+i) << endl;
    }

}


