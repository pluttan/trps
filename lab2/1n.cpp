#include <iostream>
#include <string>
#include <cstdio>
#include <sstream>

using namespace std;

struct fam {
    string ff; 
    short year;
    short month; 
    short day;
};

int main() {
    FILE* f; 
    fam fb;
    bool key;
    string fff;

    f = fopen("a.dat", "wb");
    if (f == nullptr) {
        cerr << "Error opening file for writing" << endl;
        return 1;
    }
    cout << "Write data (enter an empty string to stop):" << endl;

    while (true) {
        string input;
        getline(cin, input);
        if (input.empty()) {
            break;
        }
        istringstream iss(input);
        iss >> fb.ff >> fb.year >> fb.month >> fb.day;
        fwrite(&fb, sizeof(fb), 1, f);
    }

    fclose(f);
    cout << "Write lastname:" << endl;
    cin >> fff; 
    key = true; 
    f = fopen("a.dat", "rb");
    if (f == nullptr) {
        cerr << "Error opening file for reading" << endl;
        return 1;
    }
    while (fread(&fb, sizeof(fb), 1, f) == 1 && key) {
        if (fb.ff == fff) {
            cout << "Date: " << fb.year << " " 
                 << fb.month << " " 
                 << fb.day << endl;
            key = false;
        }
    }
    if (key) {
        cout << "No such lastname" << endl;
    }
    fclose(f);
    return 0;
}
