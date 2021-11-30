#include <iostream>
#include <vector>
#include <queue> 
#include <algorithm>
#include <bitset>
#define MAXN 100000
#define MAXS 50
#define ll long long


using namespace std;

typedef struct Operation{
    int slice, duration, dep, rank, time, id;
    vector<int> slices;
    vector<int> depends;
};

typedef struct Job{
    double weight;
    int oper_cnt, id;
    ll total_d;
    int max_rank;
    vector<Operation> oper;
};

bool cp_com(Job &a, Job &b){
    return (double)(a.weight) > (double)(b.weight);  
}

bool id_com(Job &a, Job &b){
    return (a.id < b.id) ;
}

Job jobs[MAXN];
ll ttime = 0;
int slice, job;
bitset<MAXN> puzzle[MAXS]; 

int fit_oper(Operation &in, int start_time){
    int end_time = start_time;
    bool find = false;
    while(!find){
        for(int i = 1; i <= slice; i++){
            if(i + in.slice > slice + 1)
                break;
            find = true;
            for(int j = i; j < i + in.slice; j++){
                for(int k = start_time; k < start_time + in.duration; k++){
                    if(puzzle[j][k]){
                        find = false;
                        break;
                    }
                }
                if(!find)
                    break;
            }
            if(find){
                for(int j = i; j < i + in.slice; j++){
                    for(int k = start_time; k < start_time + in.duration; k++)
                        puzzle[j].set(k);
                }  
                            in.time = start_time;
                for(int j = i; j < i + in.slice; j++)
                    in.slices.push_back(j);
                end_time = start_time + in.duration;
                //cout << in.id << " " << start_time << " " << i << endl ;
                break;              
            }

        }
        start_time++;
    }

    return end_time;
}

void fit_job(Job &in){
    int start_time = 0, now_rank = 1, arr_cnt = 0;
    while(now_rank <= in.max_rank){
        int max_end_time = start_time;
        while(arr_cnt < in.oper_cnt && in.oper[arr_cnt].rank == now_rank){
            int end_time = fit_oper(in.oper[arr_cnt], start_time);
            if(max_end_time < end_time)
                max_end_time = end_time;
            arr_cnt++;
        }
        //cout << now_rank << "\n";
        start_time = max_end_time;
        now_rank++;
    }
}

bool alltrue(int n, bool check[]){
    for(int i = 0; i < n; i++)
        if(!check[i])
            return false;
    return true;
}

bool in_sort(Operation &a, Operation &b){
    return (a.rank < b.rank);
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
        vector<int> turn_true;
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
                //now_rank++;
                turn_true.push_back(i);
                //check[i] = true;
            }
        }
        for(int i = 0; i < turn_true.size(); i++)
            check[turn_true[i]] = true;
        now_rank++;
    }
    in.max_rank = now_rank - 1;
    Job test = in;
    sort(in.oper.begin(), in.oper.end(), in_sort);
    fit_job(in);
    /*for(int i = 0; i < in.oper_cnt; i++){
        in.oper[i].time = ttime;
        ttime += in.oper[i].duration; 
    }*/
    sort(in.oper.begin(), in.oper.end(), out_sort);
    return ;
}



int main(){
    //int slice, job;
    cin >> slice >> job;   
    for(int i = 0; i < job; i ++){
        cin >> jobs[i].oper_cnt >> jobs[i].weight;
        jobs[i].total_d = 0;
        jobs[i].id = i;
        jobs[i].max_rank = -1;
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
            for(int k = 0; k < jobs[i].oper[j].slices.size(); k++)
                cout << jobs[i].oper[j].slices[k] << " ";
            cout << "\n";
        }
    }

    return 0;
}