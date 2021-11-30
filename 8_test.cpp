#include <iostream>

using namespace std;

int main(){
    cout << "200 100000 0\n";
    for(int i = 0; i < 200; i++)
        cout << i << " ";
    for(int i = 0; i < 200; i++)
        cout << "0 ";
    for(int i = 0; i < 200; i++)
        cout << "3 ";
    return 0;
}