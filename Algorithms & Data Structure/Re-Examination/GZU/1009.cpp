# include <iostream>
# include <time.h>

using namespace std;

int main(){
    srand((unsigned)time(NULL));

    for(int i = 0; i < 5; i ++)
        cout << rand() % 20 + 1 << " ";
    return 0;
}