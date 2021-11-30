#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct cord{
    long long int x, y;
};

long long int dis_sqr(cord a, cord b){
    return ((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool compx(cord a, cord b){ 
    return  (a.x > b.x);
} 

bool compy(cord a, cord b){ 
    return  (a.y < b.y);
}

long long int finddirect(vector<cord> allcord){
    long long int min_dis = dis_sqr(allcord[0], allcord[1]);
    for(int i = 1; i < allcord.size(); i++){
        for(int j = 0; j < i; j ++){
            if(dis_sqr(allcord[i], allcord[j]) < min_dis)
                min_dis = dis_sqr(allcord[i], allcord[j]);
        }
    }
    return min_dis;

}

long long int findcover(vector<cord> cover, long long int now_min){
    //cout << "cover : " << cover.size() << endl;
    sort(cover.begin(), cover.end(), compy);
    if(cover.size() <= 1)
        return now_min;
    for(int i = 0; i < cover.size() - 1; i++){
        for(int j = i + 1; j < cover.size() && ((cover[i].y - cover[j].y) * (cover[i].y - cover[j].y)) < now_min; j++){
            if(now_min > dis_sqr(cover[i], cover[j]))
                now_min = dis_sqr(cover[i], cover[j]);
        }
    }
    return now_min;
}

long long int findmindis(vector<cord> allcord){
    if(allcord.size() <= 3){
        return finddirect(allcord);
    }
    vector<cord> left(allcord.begin(), allcord.begin() + (allcord.size() / 2));
    vector<cord> right(allcord.begin() + (allcord.size() / 2), allcord.end());
    /*cout << "left: ";
    for(int i = 0; i < left.size(); i ++)
        cout << left[i].x << " ";
    cout << endl << "right: ";
    for(int i = 0; i < right.size(); i ++)
        cout << right[i].x << " ";
    cout << endl;*/
    long long int l_dis = findmindis(left);
    long long int r_dis = findmindis(right);
    long long int min_dis = ((l_dis > r_dis) ? r_dis : l_dis); 

    vector<cord> cover;
    //cout << min_dis << endl;
    for(int i = 0; i < allcord.size(); i++){
        if((allcord[i].x - allcord[(allcord.size()/2)].x) * (allcord[i].x - allcord[(allcord.size()/2)].x) < min_dis)
            cover.push_back(allcord[i]);
        //cout << "hi\n";
    }
    //cout << cover.size() << endl;
    return findcover(cover, min_dis);
}


/*int comp(const void* a, const void* b){  
    cord *p1 = (cord *)a, cord *p2 = (cord *)b;  
    if(p1 -> x > p2 -> x || (p1 -> x == p2 -> x && p1 -> y > p2 -> y))
        return 1;
    else 
        return 1;  
}  
*/
int main(){
    int n;
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    //I think for about 2 hours and find out it's same as a min-distance finding problem
    cin >> n;
    vector<cord> allcord;
    for(int i = 0; i < n; i++){
        cord temp;
        cin >> temp.x >> temp.y;
        allcord.push_back(temp);
    }
    //random_shuffle(allcord.begin(), allcord.end());
    sort(allcord.begin(), allcord.end(), compx);
    long long int ans = findmindis(allcord);
    cout << -ans << endl;
    return 0;
}