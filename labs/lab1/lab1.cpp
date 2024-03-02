#include "iostream"
#include "unordered_map"
#include "list"
#include "string"

#define max 300

using std::cin, std::cout, std::unordered_map, std::list, std::string;

typedef unordered_map<unsigned int, list<int> > uimap;
typedef unordered_map<string, list<int> > smap; 

struct norm {
    unsigned int detailCode;
    unsigned int materialCode;
    std::string measure;
    unsigned int workshopNum;
    unsigned int consumptionNorm;
    unsigned int no;

    unsigned int& get(int index) {
        switch (index) {
            case 0: return detailCode;
            case 1: return materialCode;
            case 3: return workshopNum;
            case 4: return consumptionNorm;
            case 5: return no;
            default: throw std::out_of_range("Invalid index");
        }
    }
};


#include "lab1ex.cpp"

norm tbl[max];
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

void bubbleSortMenu();
void bubbleSortUi(int nocol);
void bubbleSortStr();

void removeOffsetMenu();
void removeOffsetIndex(unsigned int index, bool wo);
void removeOffsetArray(list<int> indexes);

void printTable();
void printTableArr(list<int> arr, bool wo);


void clear() {
    std::cout << "\x1B[2J\x1B[H";
}


int getTableLength(){
    int res;
    cout << "Введите количество записей (min: 1, max: " << max << ").....";
    cin  >> res;
    return res;
}

void getdata(){
    for (int i = 0; i < 40; i++) cout << "\n";
    clear();
    cout << "Лабораторная работа 1\n"
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
    lab1ex(tbl);

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
    cout << "Лабораторная работа 1\n"
         << "[1] Адресный поиск\n"
         << "[2] Сортировка пузырьком\n"
         << "[3] Удаление сдвигом\n"
         << "[p] Вывести таблицу\n"
         << "[x] Выйти\n";
    string val;
    cin >> val;
    if (val == "1"){
        adressSearchMenu();
    }
    if (val == "2"){
        bubbleSortMenu();
    }
    if (val == "3"){
        removeOffsetMenu();
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
    cout << "Лаболаторная работа 1\n"
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


void bubbleSortMenu(){
    clear();
    cout << "Лаболаторная работа 1\n"
         << "Сортировка пузырьком\n"
         << "Выберите столбец, по которому необходимо сортировать:\n"
         << "[1] Код детали\n"
         << "[2] Код материала\n"
         << "[3] Единица измерения\n"
         << "[4] Номер цеха\n"
         << "[5] Норма расхода\n"
         << "[6] Номер записи\n"
         << "[x] В главное меню\n";
    string icol;
    cin >> icol;
    if (icol == "x") return;
    if (icol != "3"){
        int nocol = stoi(icol);
        nocol--;
        bubbleSortUi(nocol);
    } else {
        bubbleSortStr();
    }
    cout << "Отсортировано!\n"
         << "[x] В главное меню\n";
    cin >> icol;
    return;
}

void removeOffsetMenu(){
    clear();
    cout << "Лаболаторная работа 1\n"
         << "Удаление сдвигом\n"
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
        removeOffsetIndex(stoi(icol), true);
        return;
    }
    removeOffsetArray(adressSearch(icol, false));
}

list<int>::const_iterator whereList(const list<int>& l, int a) {
    auto current = l.begin();
    while (*current != a && current != l.end()) 
        current++;
    return current;
}

unsigned int idxSearch(unsigned int idx){
    for (int i = 0; i < k; i++){
        if (tbl[i].no == idx) return i;
    }
    return 0;
}

void removeOffsetIndex(unsigned int index, bool wo){
    unsigned int tmp = index;
    index = idxSearch(index);
    int j = 0;
    for(int i = 0; i < 5 && j < 4; i++){
        if (i==2)i++;
        auto d = maps[j].find(tbl[index].get(i));
        if (d != maps[j].end()) {
            d->second.erase(whereList(d->second, tmp));
        }
        j++;
    }
    for (int i = index; i < k; ++i)
        tbl[i] = tbl[i + 1];
    cout << "Строка " << tmp << " успешно удалена\n";
    k--;
    if (wo){
        cout << "[x] В главное меню\n";
        string outi;
        cin  >> outi;
    }
}

void removeOffsetArray(list<int> indexes){
    list<int> tmp(indexes);
    for (auto i: tmp){
        removeOffsetIndex(i, false);
    }
    cout << "[x] В главное меню\n";
    string outi;
    cin  >> outi;
}  

void bubbleSortUi(int nocol){
    for (int i = 0; i < k - 1; ++i) {
        for (int j = 0; j < k - i - 1; ++j) {
            if (tbl[j].get(nocol) > tbl[j + 1].get(nocol)) {
                norm temp = tbl[j];
                tbl[j] = tbl[j + 1];
                tbl[j + 1] = temp;
            }
        }
    }
}

void bubbleSortStr()
{
    string temp;
    for (int i = 0; i < k - 1; i++) {
        for (int j = 0; j < k - 1 - i; j++) {
            if (tbl[j].measure.compare(tbl[j + 1].measure) > 0) {
                norm temp = tbl[j];
                tbl[j] = tbl[j + 1];
                tbl[j + 1] = temp;
            }
        }
    }
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
        tbl[i].no = i;
        cout << "-------------------------------\n";
        cout << "Запись.............." << tbl[i].no <<"\n";
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
        putmap(maps[0],    tbl[i].detailCode,      tbl[i].no);
        putmap(maps[1],    tbl[i].materialCode,    tbl[i].no);
        putmap(measureMap, tbl[i].measure,         tbl[i].no);
        putmap(maps[2],    tbl[i].workshopNum,     tbl[i].no);
        putmap(maps[3],    tbl[i].consumptionNorm, tbl[i].no);
    };  
    cout << "-------------------------------\n";
}

void printTableArr(list<int> arr, bool wo){
    for (auto i: arr){
        unsigned int idx = idxSearch(i);
        cout << "-------------------------------\n"
             << "Запись.............." << tbl[idx].no              << "\n"
             << "Код детали.........." << tbl[idx].detailCode      << "\n"
             << "Код материала......." << tbl[idx].materialCode    << "\n"
             << "Единица измерения..." << tbl[idx].measure         << "\n"
             << "Номер цеха.........." << tbl[idx].workshopNum     << "\n"
             << "Норма расхода......." << tbl[idx].consumptionNorm << "\n";
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
    for (int i = 0; i < k; i++){
        cout << "-------------------------------\n"
             << "Запись.............." << tbl[i].no             << "\n"
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
