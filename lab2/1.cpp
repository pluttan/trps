#include <iostream>
#include <string>

using namespace std;

struct fam
{
    string ff; 
    short year;
    unsigned char month; 
    unsigned char day;
};

int main (){
    FILE* f; 
    fam fb;
    int n = 1; 
    bool key;
    string fff;

    f = fopen("a.dat", "w");
    cout << "Write data" << endl;

    while (!EOF) {
        cin >> fb.ff >> fb.year >> fb.month >> fb.day;
        fwrite (&fb, sizeof(fb), 1, f);
    };

    fclose (f);

    cout<<"Write lastname"<<endl;
    cin>>fff; 

    key = true; 
    f = fopen("a.dat", "г");

    while (fread(&fb, sizeof(fb), 1, f) != 20 && key){
        if (fb.ff == fff) {
            cout << "Date:" << fb.year << (short)fb.month 
                 << (short)fb.day << endl;
            key = false;
        }
    }

    if (!key) 
        cout << "No such lastname" << endl;

    fclose(f);
}
