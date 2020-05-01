# include <iostream>

using namespace std;

struct employee{
    char id[100];
    int h1, h2;
    int m1, m2;
    int s1, s2;
}E[1024];

int main(){

    int n;
    cin >> n;
    
    int time_early = 24 * 60 * 60, early_index = -1;
    int time_late = 0, late_index = -1;
    int time_long = 0, long_index = -1;

    for(int i = 0; i < n; i ++){
        scanf("%s %02d:%02d:%02d %02d:%02d:%02d", &E[i].id, &E[i].h1, &E[i].m1, &E[i].s1, &E[i].h2, &E[i].m2, &E[i].s2);
        int t1 = E[i].h1 * 60 * 60 + E[i].m1 * 60 + E[i].s1;
        int t2 = E[i].h2 * 60 * 60 + E[i].m2 * 60 + E[i].s2;

        if(t1 < time_early){
            time_early = t1;
            early_index = i;
        } 

        if(t2 > time_late){
            time_late = t2;
            late_index = i;
        }

        if(t2 - t1 > time_long){
            time_long = t2 - t1;
            long_index = i;
        }
    }

    printf("%s, %02d:%02d:%02d\n", E[early_index].id, E[early_index].h1, E[early_index].m1, E[early_index].s1);
    printf("%s, %02d:%02d:%02d\n", E[late_index].id, E[late_index].h1, E[late_index].m1, E[late_index].s1);
    printf("%s, %02d:%02d:%02d\n", E[long_index].id, E[long_index].h1, E[long_index].m1, E[long_index].s1);
    
    return 0;
}