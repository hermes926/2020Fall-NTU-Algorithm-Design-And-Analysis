#include <iostream>

using namespace std;

int main(){
    int n = 1000, k = 25;
    cout << n << " " << k << " 2 5\n";
    for(int i = 0; i < n ; i ++){
        if(i % 2 == 0)
            cout << - i  << " ";
        else
            cout << i << " ";
    }   
    cout << endl;



    return 0;
}