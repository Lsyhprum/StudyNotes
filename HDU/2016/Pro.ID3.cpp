# include <iostream>
# include <algorithm>
# include <fstream>

using namespace std;

const int maxn = 110;

struct stu{
    char name[20];
    int id;
    int chinese;
    int math;
    int english;
}STU[maxn];

bool cmp(stu a, stu b){
    if(a.chinese + a.math + a.english == b.chinese + b.math + b.english){
        return a.id < b.id;
    }
    return a.chinese + a.math + a.english > b.chinese + b.math + b.english;
}

int main(){
    ifstream in("h://stu.txt");

    int num = 0;
    int chinese_sum = 0;
    int math_sum = 0;
    int english_sum = 0;

    if(!in.is_open()){return 1;}

    while(in >> STU[num].name >> STU[num].id >> STU[num].chinese >> STU[num].math >> STU[num].english){
        chinese_sum += STU[num].chinese;
        math_sum += STU[num].math;
        english_sum += STU[num].english;
        num ++;
    }

    sort(STU, STU + num, cmp);

    // 输出课程总分和平均分

    for(int i = 0; i < num; i ++){
        cout << STU[i].name << " " << STU[i].id << endl;
    }


    return 0;
}