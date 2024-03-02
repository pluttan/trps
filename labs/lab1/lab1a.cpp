#include "iostream"
#include "unordered_map"
#include "list"
#include "string"

using std::cin, std::cout, std::unordered_map, std::list, std::string, std::vector;

struct norm {
    unsigned int detailCode;
    unsigned int materialCode;
    std::string measure;
    unsigned int workshopNum;
    unsigned int consumptionNorm;

    unsigned int& get(int index) {
        switch (index) {
            case 0: return detailCode;
            case 1: return materialCode;
            case 3: return workshopNum;
            case 4: return consumptionNorm;
            default: throw std::out_of_range("Invalid index");
        }
    }
};

typedef unordered_map<unsigned int, list<int> > uimap;
typedef unordered_map<string, list<int> > smap; 
typedef unordered_map<unsigned int, norm > tytbl; 

#include "lab1exa.cpp"

tytbl tbl;
vector<int> stbl;
uimap maps[4] = {{},{},{},{}};
smap  measureMap = {};
int k = 0;
bool quit = 0;

int getTableLength();
void getTable();
void getdata();

void mainMenu();

void adressSearchMenu();
list<int> adressSearch(string icol, bool wo);
template<typename tmap, typename t> void putmap(tmap &map, t key, int value);

void qSortMenu();
void qSortUi(int nocol);
void qSortStr();
void qSortI();

void removeMarkMenu();
void removeMarkIndex(unsigned int index, bool wo);
void removeMarkArray(list<int> indexes);

void printTable();
void printTableArr(list<int> arr, bool wo);


void clear() {
    std::cout << "\x1B[2J\x1B[H";
}


int getTableLength(){
    int res;
    cout << "Введите количество записей.....";
    cin  >> res;
    return res;
}

void getdata(){
    for (int i = 0; i < 40; i++) cout << "\n";
    clear();
    cout << "Лабораторная работа 1 (Альтернативное решение)\n"
         << "Ввод данных\n"
         << "[1] Ввести вручную\n"
         << "[2] Использовать пример\n"
         << "[x] Выйти\n";
    string text;
    cin >> text;
    if (text == "x") {
        quit = true;
        return;
    }
    if (text == "1") {
        k = getTableLength();
        getTable();
        return;
    };
    k = 300;
    lab1exa(tbl, &stbl);

    for (int i = 0; i < k; i++){
        putmap(maps[0],    tbl[i].detailCode,      i);
        putmap(maps[1],    tbl[i].materialCode,    i);
        putmap(measureMap, tbl[i].measure,         i);
        putmap(maps[2],    tbl[i].workshopNum,     i);
        putmap(maps[3],    tbl[i].consumptionNorm, i);
    }
 
    return;
}

void mainMenu(){
    clear();
    cout << "Лабораторная работа 1 (Альтернативное решение)\n"
         << "[1] Адресный поиск\n"
         << "[2] Быстрая сортировка\n"
         << "[3] Удаление маркировкой\n"
         << "[p] Вывести таблицу\n"
         << "[x] Выйти\n";
    string val;
    cin >> val;
    if (val == "1"){
        adressSearchMenu();
    }
    if (val == "2"){
        qSortMenu();
    }
    if (val == "3"){
        removeMarkMenu();
    }
    if (val == "p"){
        printTable();
    }
    if (val== "x"){
        quit = true;
    }
    return;
}

void adressSearchMenu(){
    clear();
    cout << "Лабораторная работа 1 (Альтернативное решение)\n"
         << "Адресный поиск\n"
         << "Выберите столбец, по которому необходимо искать:\n"
         << "[1] Код детали\n"
         << "[2] Код материала\n"
         << "[3] Единица измерения\n"
         << "[4] Номер цеха\n"
         << "[5] Норма расхода\n"
         << "[x] В главное меню\n";
    string icol;
    cin >> icol;
    if (icol == "x") return; 
    adressSearch(icol, true);
}

list<int> adressSearch(string icol, bool wo){
    cout << "Введите текст/число для поиска: ";
    if (icol == "3"){
        string text;
        cin >> text;
        if (measureMap[text].size() == 0) {
            cout << "-------------------------------\n"
                 << "Ничего не найдено\n";
        };
        printTableArr(measureMap[text], wo);
        return measureMap[text];
    }
    int i = std::stoi(icol)-1;
    if (i > 2) i--;
    int text;
    cin >> text;
    if (maps[i][text].size() == 0) {
        cout << "-------------------------------\n"
             << "Ничего не найдено\n";
    };
    printTableArr(maps[i][text], wo);
    return maps[i][text];
}


void qSortMenu(){
    clear();
    cout << "Лабораторная работа 1 (Альтернативное решение)\n"
         << "Быстрая сортировка\n"
         << "Выберите столбец, по которому необходимо сортировать:\n"
         << "[1] Код детали\n"
         << "[2] Код материала\n"
         << "[3] Единица измерения\n"
         << "[4] Номер цеха\n"
         << "[5] Норма расхода\n"
         << "[i] Номер записи\n"
         << "[x] В главное меню\n";
    string icol;
    cin >> icol;
    if (icol == "x") return;
    if (icol != "3" && icol != "i"){
        int nocol = stoi(icol);
        nocol--;
        qSortUi(nocol);
    } else if(icol == ""3) {
        qSortStr();
    } else {
        qSortI();
    }
    cout << "Отсортировано!\n"
         << "[x] В главное меню\n";
    cin >> icol;
    return;
}

void removeMarkMenu(){
    clear();
    cout << "Лабораторная работа 1 (Альтернативное решение)\n"
         << "Удаление маркировкой\n"
         << "Выберите столбец, по которому необходимо искать данные для удаления записей:\n"
         << "[i] Удалить по номеру записи\n"
         << "[1] Код детали\n"
         << "[2] Код материала\n"
         << "[3] Единица измерения\n"
         << "[4] Номер цеха\n"
         << "[5] Норма расхода\n"
         << "[x] В главное меню\n";
    string icol;
    cin >> icol;
    if (icol == "x") return;
    if (icol == "i") {
        cout << "Введите номер записи: ";
        cin  >> icol;
        removeMarkIndex(stoi(icol), true);
        return;
    }
    removeMarkArray(adressSearch(icol, false));
}

list<int>::const_iterator whereList(const list<int>& l, int a) {
    auto current = l.begin();
    while (*current != a && current != l.end()) 
        current++;
    return current;
}

void removeMarkIndex(unsigned int index, bool wo){
    int j = 0;
    for(int i = 0; i < 5 && j < 4; i++){
        if (i==2)i++;
        auto d = maps[j].find(tbl[index].get(i));
        if (d != maps[j].end()) {
            d->second.erase(whereList(d->second, index));
        }
        j++;
    }
    tbl[index] = {};
    cout << "Строка " << index << " успешно удалена\n";
    k--;
    if (wo){
        cout << "[x] В главное меню\n";
        string outi;
        cin  >> outi;
    }
}

void removeMarkArray(list<int> indexes){
    list<int> tmp(indexes);
    for (auto i: tmp){
        removeMarkIndex(i, false);
    }
    cout << "[x] В главное меню\n";
    string outi;
    cin  >> outi;
} 

void qSortUi(int nocol) {
    int i = 0, j = N;
    T temp, p;
    p = a [N>>1];

    do {
        while ( a[i] < p ) i++;
        while ( a[j] > p ) j--;
        if (i <= j){
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i++;
            j--;
        }
    } while (i <= j);

    if ( j > 0 ) quickSortR(a, j);
    if ( N > i ) quickSortR(a+i, N-i);
}

void qSortStr(){
}

void qSortI(){
}

template<typename tmap, typename t> void putmap(tmap &map, t key, int value){
    if (map.find(key) == map.end()){
        list<int> res = {};
        res.push_back(value);
        map[key] = res;
    } else {
        map[key].push_back(value);  
    }
}

void getTable(){
    for (int i = 0; i < k; i++){
        cout << "-------------------------------\n";
        cout << "Запись.............." << i <<"\n";
        cout << "Код детали..........";
        cin  >> tbl[i].detailCode;
        cout << "Код материала......."; 
        cin  >> tbl[i].materialCode;
        cout << "Единица измерения...";
        cin  >> tbl[i].measure;
        cout << "Номер цеха.........."; 
        cin  >> tbl[i].workshopNum;
        cout << "Норма расхода.......";
        cin  >> tbl[i].consumptionNorm;
        putmap(maps[0],    tbl[i].detailCode,      i);
        putmap(maps[1],    tbl[i].materialCode,    i);
        putmap(measureMap, tbl[i].measure,         i);
        putmap(maps[2],    tbl[i].workshopNum,     i);
        putmap(maps[3],    tbl[i].consumptionNorm, i);
    };  
    cout << "-------------------------------\n";
}

void printTableArr(list<int> arr, bool wo){
    int it = 0;
    for (auto i: arr){
        if (tbl.find(i) != tbl.end()){
            cout << "-------------------------------\n"
                 << "Запись.............." << it                       << "\n"
                 << "Код детали.........." << tbl[i].detailCode      << "\n"
                 << "Код материала......." << tbl[i].materialCode    << "\n"
                 << "Единица измерения..." << tbl[i].measure         << "\n"
                 << "Номер цеха.........." << tbl[i].workshopNum     << "\n"
                 << "Норма расхода......." << tbl[i].consumptionNorm << "\n";
        }
        it++;
    }; 
    cout << "-------------------------------\n";
    if (wo){
        cout << "[x] Назад\n";
        string text;
        cin >> text;
    }
    return;
}

void printTable(){
    for (auto i :stbl){
        cout << "-------------------------------\n"
             << "Запись.............." << i                      << "\n"
             << "Код детали.........." << tbl[i].detailCode      << "\n"
             << "Код материала......." << tbl[i].materialCode    << "\n"
             << "Единица измерения..." << tbl[i].measure         << "\n"
             << "Номер цеха.........." << tbl[i].workshopNum     << "\n"
             << "Норма расхода......." << tbl[i].consumptionNorm << "\n";
    };  
    cout << "-------------------------------\n";
    cout << "[x] Назад\n";
    string text;
    cin >> text;
    return;
}



int main(){
   getdata();
   while (!quit) mainMenu();
   return 0;
}
