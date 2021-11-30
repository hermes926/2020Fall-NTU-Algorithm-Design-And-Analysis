#include <iostream>
#include <stdlib.h>
#include <vector>


using namespace std;

int main(){
    int n = 100, m = 5;
    vector<int> nums;
    for(int i = 1; i <= n; i++){
        nums.push_back(i);
    }
    cout << n << " " << m << endl;
    for(int i = n - 1; i >= 0; i--){
        if(i % 2 == 0)
            cout << n - i << " ";
        else
            cout << i << " ";
    } 
    cout << endl;
}