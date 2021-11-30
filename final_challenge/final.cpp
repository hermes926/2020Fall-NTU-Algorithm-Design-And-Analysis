#include <iostream>
#include <vector>
#include <queue> 
#include <algorithm>
#define MAXN 100000
#define ll long long


using namespace std;

typedef struct Operation{
    int slice, duration, dep, rank, time, id;
    vector<int> depends;
};

typedef struct Job{
    double weight;
    int oper_cnt, id;
    ll total_d;
    vector<Operation> oper;
};

bool cp_com(Job &a, Job &b){
    return ((a.weight / (double)a.total_d) > (b.weight / (double)b.total_d));  
}

bool id_com(Job &a, Job &b){
    return (a.id < b.id) ;
}

Job jobs[MAXN];
ll time = 0;

bool alltrue(int n, bool check[]){
    for(int i = 0; i < n; i++)
        if(!check[i])
            return false;
    return true;
}

bool in_sort(Operation &a, Operation &b){
    return (double)(a.rank / a.slice) < (double)(b.rank / b.slice);
}

bool out_sort(Operation &a, Operation &b){
    return (a.id < b.id);
}

void processjob(Job &in){
    /*if(in.oper_cnt == 1 || in.oper_cnt == 0)
        return ;*/
    bool check[MAXN] = {0};
    int now_rank = 1;
    while(!alltrue(in.oper_cnt, check)){
        
        for(int i = 0; i < in.oper_cnt; i++){
            bool wow = true;
            for(int j = 0; j < in.oper[i].dep; j++){
                if(!check[in.oper[i].depends[j] - 1])
                    wow = false;
            }    
            if(in.oper[i].dep == 0)
                wow = true;
            if(wow && !check[i]){
                in.oper[i].rank = now_rank;
                now_rank++;
                check[i] = true;
            }
        }
    }
    Job test = in;
    sort(in.oper.begin(), in.oper.end(), in_sort);
    for(int i = 0; i < in.oper_cnt; i++){
        in.oper[i].time = time;
        time += in.oper[i].duration; 
    }
    sort(in.oper.begin(), in.oper.end(), out_sort);
    return ;
}



int main(){
    int slice, job;
    cin >> slice >> job;   
    for(int i = 0; i < job; i ++){
        cin >> jobs[i].oper_cnt >> jobs[i].weight;
        jobs[i].total_d = 0;
        jobs[i].id = i;
        for(int j = 0; j < jobs[i].oper_cnt; j++){
            Operation tmp;
            cin >> tmp.slice >> tmp.duration >> tmp.dep;
            jobs[i].total_d += tmp.duration;
            //cout << jobs[i].total_d << endl;
            tmp.rank = -1;
            tmp.time = -1;
            tmp.id = j;
            for(int i = 0; i < tmp.dep; i++){
                int tmp_num;
                cin >> tmp_num;
                tmp.depends.push_back(tmp_num);
            }
            jobs[i].oper.push_back(tmp);
        }
        
        //processjob(jobs[i]);
    }
    sort(jobs, jobs + job, cp_com);
    for(int i = 0; i < job; i++)
        processjob(jobs[i]);
    
    sort(jobs, jobs + job, id_com);
    //ll nowt = 0;
    for(int i = 0; i < job; i++){
        //cout << jobs[i].id << " " << jobs[i].total_d << endl;
        for(int j = 0; j < jobs[i].oper_cnt; j++){
            cout << jobs[i].oper[j].time << " ";
            //nowt += jobs[i].oper[j].duration;
            for(int k = 1; k <= jobs[i].oper[j].slice; k++)
                cout << k << " ";
            cout << "\n";
        }
    }

    return 0;
}