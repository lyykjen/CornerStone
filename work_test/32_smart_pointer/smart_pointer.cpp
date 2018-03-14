#include <iostream>
#include <memory>
using  namespace std;

class Example
{
public:
    Example() : e(1) { cout << "Example Constructor..." << endl; }
    ~Example() { cout << "Example Destructor..." << endl;}

    int e;
};

int main() 
{

    std::shared_ptr<Example> pInt(new Example());
    cout << (*pInt).e << endl;
    cout << "pInt引用计数: " << pInt.use_count() << endl;

    shared_ptr<Example> pInt2 = pInt;
    cout << "pInt引用计数: " << pInt.use_count() << endl;
    cout << "pInt2引用计数: " << pInt2.use_count() << endl;

    return 0;
}