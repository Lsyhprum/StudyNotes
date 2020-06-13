# include <iostream>

using namespace std;

void prefix_table(string pattern, int prefix[], int n){
    prefix[0] = 0;
    int i = 1;
    int len = 0;
    while(i < n){
        if(pattern[i] == pattern[len]){
            len ++;
            prefix[i] = len;
            i ++;
        }else{
            if(len > 0){
                len = prefix[len - 1];
            }else{
                prefix[i] = len;
                i ++;
            }
        }
    }
}

void move_prefix_table(int prefix[], int n){
    for(int i = n - 1; i > 0; i --){
        prefix[i] = prefix[i-1];
    }
    prefix[0] = -1;
}

void kmp_search(string text, string pattern){
    int prefix[10];
    prefix_table(pattern, prefix, 10);
    move_prefix_table(prefix, 10);

    int i = 0, j = 0;
    int m = text.length(), n = pattern.length();

    while(i < m){
        if(j == n - 1 && text[i] == pattern[j]){
            cout << i << j << endl;
            cout << "find pattern:" << i - j << endl; 
            j = prefix[j];
        }

        if(text[i] == pattern[j]){
            i ++;
            j ++;
        }else{
            j = prefix[j];
            if(j == -1){
                i ++;
                j ++;
            }

        }
    }

}

int main(){
    string text = "ABABABABCABAAB";
    string pattern = "ABABCABAA";
    
    kmp_search(text, pattern);

    return 0;
}