#include <iostream>
#include <vector>
#define MAXN 100010

using namespace std;

int books1[MAXN], books2[MAXN];
long long int ans1 = 0, ans2 = 0;

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);    
    int n, flag, zero_c = 0, zero_p = -1;
    vector<int> ans1_seq, ans2_seq;

    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> books1[i];
        if(books1[i] != 0){
            zero_c ++;
            zero_p = i;
        }
        books2[i] = books1[i];
    }
    cin >> flag;
    if(zero_c == 1){
        cout << max(0, books1[zero_p] - 1) << endl;
        if(flag){
            if(zero_p == 0){            
                for(int i = 0; i < books1[zero_p] - 1; i++)
                    cout << "1 2 ";
                cout << "1\n";
            }else{
                for(int i = 0; i < books1[zero_p] - 1; i++)
                    cout << zero_p + 1 << " " << zero_p << " ";
                cout << zero_p + 1 << "\n";
            }
        }
        return 0;
    }


    for(int i = n - 1; i >= 0; i--){
        if(books1[i] == 0)
            n--;
        else
            break;
    }
    
    for(int i = 0; i < n - 2; i++){
        if(books1[i] == 0)
            continue;
        for(int j = 0; j < books1[i] && flag; j++){
            //cout << "hi\n";
            if(ans1_seq.size() == 0 || ans1_seq.back() != i + 1)
                ans1_seq.push_back(i + 1);
            ans1_seq.push_back(i + 2);
        }
        if(books1[i] > books1[i + 1]){
            ans1 += (books1[i] - books1[i + 1]);
            books1[i] = 1;
            books1[i + 1] = 1;
        }else if(books1[i] == books1[i + 1]){
            books1[i] = 1;
            books1[i + 1] = 1;
        }else{
            books1[i + 1] -= (books1[i] - 1);
            books1[i] = 1;
        }
        
    }
    if(books1[n - 2] <= books1[n - 1]){
        for(int j = 0; j < books1[n - 1]; j++){
            if(ans1_seq.size() == 0 || ans1_seq.back() != n - 1)
                ans1_seq.push_back(n - 1);
            ans1_seq.push_back(n);
        }
        ans1 += (books1[n - 1] - books1[n - 2]);
    }else{
        for(int j = 0; j < books1[n - 2] - 1; j++){
            //cout << "oh\n";
            if(ans1_seq.size() == 0 || ans1_seq.back() != n - 1)
                ans1_seq.push_back(n - 1);
            ans1_seq.push_back(n);
        }
        ans1_seq.push_back(n - 1);
        ans1 += max(0, books1[n - 2] - books1[n - 1] - 1);
    }
    
    
    
    
    int p_2 = 0;
    while(books2[p_2] == 0)
        p_2 ++;
    
    ans2_seq.push_back(p_2 + 2);
    if(books2[p_2 + 1] > 0){

        books2[p_2 + 1] -= 1;
        for(int i = p_2; i < n - 2; i++){
            if(books2[i] == 0)
                continue;
            for(int j = 0; j < books2[i] && flag; j++){
                if(ans2_seq.size() == 0 || ans2_seq.back() != i + 1)
                    ans2_seq.push_back(i + 1);
                ans2_seq.push_back(i + 2);
            }
            if(books2[i] > books2[i + 1]){
                ans2 += (books2[i] - books2[i + 1]);
                books2[i] = 1;
                books2[i + 1] = 1;
            }else if(books2[i] == books2[i + 1]){
                books2[i] = 1;
                books2[i + 1] = 1;
            }else{
                books2[i + 1] -= (books2[i] - 1);
                books2[i] = 1;
            }
        }
        if(books2[n - 2] <= books2[n - 1]){
            for(int j = 0; j < books2[n - 1]; j++){
                if(ans2_seq.size() == 0 || ans2_seq.back() != n - 1)
                    ans2_seq.push_back(n - 1);
                ans2_seq.push_back(n);
            }
            ans2 += (books2[n - 1] - books2[n - 2]);
        }else{
            for(int j = 0; j < books2[n - 2] - 1; j++){
                if(ans2_seq.size() == 0 || ans2_seq.back() != n - 1)
                    ans2_seq.push_back(n - 1);
                ans2_seq.push_back(n);
            }
            ans2_seq.push_back(n - 1);
            ans2 += max(0, books2[n - 2] - books2[n - 1] - 1);
        }
        

        if(ans1 < ans2){
            cout << ans1 << "\n";
            for(int i = 0; i < ans1_seq.size() && flag; i++)
                cout << ans1_seq[i] << " ";
            cout << endl;
        }else{
            cout << ans2 << "\n";
            for(int i = 0; i < ans2_seq.size() && flag; i++)
                cout << ans2_seq[i] << " ";
            cout << endl;            
        }
        
        //cout << min(ans1, ans2) << "\n";

    }else{
        cout << ans1 << "\n";
        for(int i = 0; i < ans1_seq.size() && flag; i++)
            cout << ans1_seq[i] << " ";
        cout << endl;
    }
    
    return 0;
}