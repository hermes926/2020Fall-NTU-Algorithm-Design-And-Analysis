#include <iostream>

using namespace std;

int main(){
    int now = 33;
    for(int i = 0; i < 9;i ++){
        for(int j = 0; j < 9; j++){
            cout << (char)(now + i * 9 + j);
        }
        cout << "\n";
    }
    int ARR[81] = {
    2, 1, 5, 6, 4, 7, 3, 9, 8, 
    3, 6, 8, 9, 5, 2, 1, 7, 4,
    7,9,4,3,8,1,6,5,2,
    5,8,6,2,7,4,9,3,1,
    1,4,2,5,9,3,8,6,7,
    9,7,3,8,1,6,4,2,5,
    8,2,1,7,3,9,5,4,6,
    6,5,9,4,2,8,7,1,3,
    4,3,7,1,6,5,2,8,9};

    for(int i = 0; i < 81; i ++){
        cout << (char)(i + 33) << " " << ARR[i] << "\n";
    }


    return 0;
}