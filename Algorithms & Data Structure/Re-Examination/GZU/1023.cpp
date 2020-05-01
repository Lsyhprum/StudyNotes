# include <iostream>
# include <sstream>
# include <string>

using namespace std;

int main(){
	string s;
	getline(cin, s);
	
	string part;
	stringstream ss(s);
	
	int i = 0;
    int p[4];
	while(getline(ss, part, '.')){
        //cout << part << endl;
		if(++ i > 4){
            cout << "Error";
            return 0;
        }
		
        stringstream sst(part);
		if(!(sst >> p[i-1])){
            cout << "Error";
            return 0;
        }
	}

    if(i != 4 || s.back() == '.'){
        cout << "Error";
        return 0;
    }

    for(int i = 0; i < 4; i ++){
        if(p[i] > 255 || p[i] < 0){
            cout << "Error";
            return 0;
        }
    }

    printf("0x%02X%02X%02X%02X", p[0], p[1], p[2], p[3]);
	
	
	return 0;
}