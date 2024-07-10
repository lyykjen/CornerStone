#include <iostream>
#include <memory>
#include <vector>
using namespace std;
int main()
{
    vector<shared_ptr<int>> intPtr;
    vector<shared_ptr<int>> intPtr2;
    for (int i = 0; i < 10; ++i) {
        intPtr.emplace_back(make_shared<int>(i));
    }
    for (int i = 0; i < 10; ++i) {
        cout << "intPtr " << i << " = " << *intPtr.at(i) << endl;        
    }

    intPtr2 = intPtr;
    /*
    cout << "2:  intPtr[0].use_count() = " << intPtr[0].use_count() << endl;
    cout << "2:  intPtr2[0].use_count() = " << intPtr2[0].use_count() << endl;
    */

    cout << "intPtr[0]  = " << intPtr[0] << endl;
    cout << "intPtr2[0] = " << intPtr2[0] << endl;

    intPtr[0] = make_shared<int>(50);

    cout << "3:  intPtr[0].use_count()  = " << intPtr[0].use_count() << endl;
    cout << "3:  intPtr2[0].use_count() = " << intPtr2[0].use_count() << endl;

    cout << "intPtr[0]  = " << intPtr[0] << endl;
    cout << "intPtr2[0] = " << intPtr2[0] << endl;

    cout << "intPtr[0]  = " << *intPtr[0] << endl;
    cout << "intPtr2[0] = " << *intPtr2[0] << endl;


    return 0;
}
