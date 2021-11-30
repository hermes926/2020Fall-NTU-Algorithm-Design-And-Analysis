#include <iostream>
#include <vector>

using namespace std;

int main(){
    vector<int> all_inc;
    all_inc.push_back(0);
    all_inc.push_back(1);
    all_inc.push_back(2);
    all_inc.push_back(3);
    all_inc.push_back(4);
    all_inc.push_back(5);
    int l = 0, m = 2, r = 5;
    vector<int> left(all_inc.begin() + l, all_inc.begin() + m + 1);
    vector<int> right(all_inc.begin() + m + 1, all_inc.begin() + r + 1); 
    for(int i = 0; i < left.size(); i++){
        cout << left[i] << endl;
    }
    cout << endl;
    for(int i = 0; i < right.size(); i++){
        cout << right[i] << endl;
    }
    cout << endl;

}