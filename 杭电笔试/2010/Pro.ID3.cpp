# include <iostream>
# include <algorithm>
# include <fstream>
# include <string>

using namespace std;

const int maxn = 1024;

struct stu{
    char name[20];
    char id[20];
    int english;
    int chinese;
    int math;
    int science;
}STU[maxn];

bool cmp(stu a, stu b){
    return (a.english + a.chinese + a.math + a.science) > (b.english + b.chinese + b.math + b.science);
}

int main(){
    ifstream in("h://student.txt");

    //if(!in.is_open()){return 1;};

    int num = 0;

    while(in >> STU[num].name >> STU[num].id >> STU[num].english >> STU[num].chinese >> STU[num].math >> STU[num].science){
        num ++;
    }

    sort(STU, STU + num, cmp);


    for(int i = 0; i < num; i ++){
        cout << STU[i].name << " " 
             << STU[i].id << " " 
             << STU[i].english << " " 
             << STU[i].chinese << " " 
             << STU[i].math << " "
             << STU[i].science << endl;
    }
    return 0;
}