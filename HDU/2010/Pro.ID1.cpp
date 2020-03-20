# include <iostream>
# include <cstdlib>
# include <ctime>

using namespace std;

int main(){
    srand((unsigned)time(NULL));
    int num = rand() % 900 + 100, cnt = 10;
    cout << num << endl;

    int left = 100, right = 999, mid;
    while(left <= right && cnt){
        mid = (left + right) / 2;

        cout << mid << endl;
        if(mid == num){
            printf("恭喜你，猜对了\n");
            return 0;
        }else if(mid < num){
            printf("猜小了，请继续\n");
            left = mid + 1;
        }else{
            printf("猜大了，请继续\n");
            right = mid - 1;
        }
        cnt --;
    }
    printf("Bye Bye\n");
    return 0;
}