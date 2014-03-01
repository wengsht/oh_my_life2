#include <iostream>
#include <string>
using namespace std;


int main() {
    string x = "123456789";
    x.erase(0, 3);
    cout << x << endl;
    return 0;
}

