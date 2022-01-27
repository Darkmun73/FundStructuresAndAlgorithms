#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <intrin.h> 
#pragma intrinsic(__rdtsc)
using namespace std;

void generate_input(size_t n, string out_fyle) {
    setlocale(LC_ALL, "rus");
    string lane;
    string direct[] = { "Физика", "Психология", "Экономика", "Химия", "Геология",
        "География", "Биология", "Архитектура", "Машиностроение", "Инноватика" };

    string grp_num[] = { "Б9120-09.03.04прогин","Б9119-09.03.04прогин", "Б9120-09.03.03прогин",
        "М3121-26.04.02кто", "М3121-26.04.02ксо", "М4120-37.04.01пм", "С3120-08.05.01сгспо",
        "С3216-20.05.01птпп", "С3216-21.05.04мрд", "А8121-04.06.01фх", "А8121-04.06.01бох" };

    string FIO[] = { "Агеев Андрей Владиславович","Аксенова Алёна Егоровна","Анохин Марк Николаевич",
        "Безруков Иван Никитич","Ильина Варвара Львовна","Ильина Дарья Константиновна","Казанцев Григорий Михайлович",
        "Калугина Виктория Дмитриевна","Кириллова Алиса Демьяновна",
        "Киселева Арина Александровна","Ковалев Роман Александрович",
        "Ковалев Артём Егорович","Козина Василиса Марковна","Козырев Кирилл Иванович",
        "Лебедева Анна Львовна","Орлов Илья Русланович","Сорокина Валерия Тимуровна","Шестакова Таисия Павловна" };

    srand(time(0));
    ofstream output(out_fyle, 'w');
    output << n;
    for (int i = 0; i < n; i++) {
        output << "\n";
        lane = "";
        int phone1 = rand() % 900 + 100;
        int phone2 = rand() % 9000 + 1000;
        int month = rand() % 12 + 1;
        int day;
        if (month == 2) {
            day = rand() % 27 + 1;
        }
        else if (month % 2 == 1 or month == 8) {
            day = rand() % 31 + 1;
        }
        else  day = rand() % 30 + 1;
        int year = rand() % 4 + 2000;
        lane += FIO[rand() % 18] + ' ' + direct[rand() % 10] + ' ' + grp_num[rand() % 11];
        lane += ' ' + (day < 10 ? '0' + to_string(day) : to_string(day)) + '.'
            + (month < 10 ? '0' + to_string(month) : to_string(month)) + '.' + to_string(year) + " 8914" + to_string(phone1) + to_string(phone2);
            
        output << lane;
    }
    output.close();
}

void split(string s, char delim, vector<string>& data)
{
    while (!s.empty())
    {
        auto word_end = s.find(delim);
        if (word_end == -1)
        {
            data.push_back(s);
            s.clear();
        }
        else
        {
            data.push_back(s.substr(0, word_end));
            s.erase(0, word_end + 1);
        }
    }
}

struct FIO
{
    string f;
    string i;
    string o;
};

struct BirthDate
{
    int dd;
    int mm;
    int yy;
};

struct Student
{
    FIO fio;
    string direct;
    string group_num;
    BirthDate bdate;
    string phone_num;
};

bool operator <(Student& l, Student& r)
{
    string tempL = l.fio.f + " " + l.fio.i + " " + l.fio.o;
    string tempR = r.fio.f + " " + r.fio.i + " " + r.fio.o;

    if (l.bdate.yy < r.bdate.yy)
        return true;
    else if (l.bdate.yy > r.bdate.yy)
        return false;
    else if (l.bdate.yy == r.bdate.yy)
    {
        if (l.bdate.mm < r.bdate.mm)
            return true;
        else if (l.bdate.mm > r.bdate.mm)
            return false;
        else if (l.bdate.mm == r.bdate.mm)
        {
            if (l.bdate.dd < r.bdate.dd)
                return true;
            else if (l.bdate.dd > r.bdate.dd)
                return false;
            else if (l.bdate.dd == r.bdate.dd)
            {
                if (l.group_num < r.group_num)
                    return true;
                else if (l.group_num > r.group_num)
                    return false;
                else if (l.group_num == r.group_num)
                {
                    if (tempL < tempR)
                        return true;
                    else if (tempL >= tempR)
                        return false;
                }
            }
        }
    }
}

//вычисляет коэффициент седжвика с номером s
long calcSegvik(int s)
{
    if (s % 2)
        return 8 * pow(2.0, s) - 6 * pow(2.0, (s + 1) / 2) + 1;
    else
        return 9 * pow(2.0, s) - 9 * pow(2.0, s / 2) + 1;
}

//вычисляет последовательность длин подсписков
int  increment(long inc[], long size)
{
    int i = 0;

    do {
        inc[i] = calcSegvik(i);
    } while (3 * inc[i++] < size);

    return i - 1;
}

//сортировка вставками начиная с индекса start с шагом inc
//сортирует только элементы, которые входят в множество {a | a попадает в start + k * inc}
void insertSort(Student*& stud, int size, int start, int inc)
{
    int location;
    Student newelement;

    for (int i = start + inc; i < size; i += inc) {
        newelement = stud[i];
        location = i - inc;

        while (location >= start && stud[location] < newelement) {
            stud[location + inc] = stud[location];
            location -= inc;
        }

        stud[location + inc] = newelement;

    }
}

//сортировка Шелла
void ShellSort(int n, Student*& stud)
{
    long seq[40];

    //в s хранится последний элемент (его индекс) из массива коэф. седжвика seq
    for (int s = increment(seq, n); s >= 0; s--)
        for (int i = 0; i < seq[s]; i++)
            insertSort(stud, n, i, seq[s]);
}

//сортировка выбором
void ChoiceSort(int n, Student*& stud)
{
    // Перебираем каждый элемент массива (кроме последнего, он уже будет отсортирован к тому времени, когда мы до него доберемся)
    for (int startIndex = 0; startIndex < n - 1; ++startIndex)
    {
        // В переменной smallestIndex хранится индекс наименьшего значения, которое мы нашли в этой итерации.
        // Начинаем с того, что наименьший элемент в этой итерации - это первый элемент (индекс 0)
        int smallestIndex = startIndex;

        // Затем ищем элемент поменьше в остальной части массива
        for (int currentIndex = startIndex + 1; currentIndex < n; ++currentIndex)
        {
            // Если мы нашли элемент, который меньше нашего наименьшего элемента,
            if (stud[smallestIndex] < stud[currentIndex])
                // то запоминаем его
                smallestIndex = currentIndex;
        }

        // smallestIndex теперь наименьший элемент. 
        // Меняем местами наше начальное наименьшее число с тем, которое мы обнаружили
        std::swap(stud[startIndex], stud[smallestIndex]);
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    string temp;
    vector<string> record;
    vector<string> sub_record;
    /*generate_input(10, "DVFUStudents1.txt");
    generate_input(100, "DVFUStudents2.txt");
    generate_input(1000, "DVFUStudents3.txt");
    generate_input(10000, "DVFUStudents4.txt");
    generate_input(50000, "DVFUStudents5.txt");
    generate_input(1000000, "DVFUStudents6.txt");*/

    ifstream fi("DVFUStudents1.txt");
    ofstream fout1("DVFUStudentsOut1.txt");
    ofstream fout2("DVFUStudentsOut2.txt");

    getline(fi, temp);
    const int n = stoi(temp);
    Student* students = new Student[n];
    for (size_t i = 0; i < n; i++)
    {
        getline(fi, temp);
        split(temp, ' ', record);
        students[i].fio.f = record[0];
        students[i].fio.i = record[1];
        students[i].fio.o = record[2];
        students[i].direct = record[3];
        students[i].group_num = record[4];
        split(record[5], '.', sub_record);
        students[i].bdate.dd = stoi(sub_record[0]);
        students[i].bdate.mm = stoi(sub_record[1]);
        students[i].bdate.yy = stoi(sub_record[2]);
        students[i].phone_num = record[6];
        sub_record.clear();
        record.clear();
    }

    double begin = clock();
    ShellSort(n, students);
    double end = clock();
    double t1 = (end - begin);

    fout1 << t1;
    for (size_t i = 0; i < n; i++)
    {
        fout1 << "\n";
        //students[i].bdate.dd < 10 ? '0' + to_string(day) : to_string(day)
        fout1 << (students[i].bdate.dd < 10 ? '0' + to_string(students[i].bdate.dd) : to_string(students[i].bdate.dd)) << "." <<
                 (students[i].bdate.mm < 10 ? '0' + to_string(students[i].bdate.mm) : to_string(students[i].bdate.mm)) << "." <<
                  students[i].bdate.yy << " ";
        int l = 23 - students[i].group_num.size();
        fout1 << students[i].group_num;
        for (size_t i = 0; i < l; i++)
            fout1 << " ";
        string fio = students[i].fio.f + " " + students[i].fio.i + " " + students[i].fio.o;
        l = 31 - fio.size();
        fout1 << fio;
        for (size_t i = 0; i < l; i++)
            fout1 << " ";
        l = 17 - students[i].direct.size();
        fout1 << students[i].direct;
        for (size_t i = 0; i < l; i++)
            fout1 << " ";
        fout1 << students[i].phone_num;
    }

    //begin = clock();
    //ChoiceSort(n, students);
    //end = clock();
    //double t2 = (end - begin);

    //fout2 << t2;

    //for (size_t i = 0; i < n; i++)
    //{
    //    fout2 << "\n";
    //    //students[i].bdate.dd < 10 ? '0' + to_string(day) : to_string(day)
    //    fout2 << (students[i].bdate.dd < 10 ? '0' + to_string(students[i].bdate.dd) : to_string(students[i].bdate.dd)) << "." <<
    //        (students[i].bdate.mm < 10 ? '0' + to_string(students[i].bdate.mm) : to_string(students[i].bdate.mm)) << "." <<
    //        students[i].bdate.yy << " ";
    //    int l = 23 - students[i].group_num.size();
    //    fout2 << students[i].group_num;
    //    for (size_t i = 0; i < l; i++)
    //        fout2 << " ";
    //    string fio = students[i].fio.f + " " + students[i].fio.i + " " + students[i].fio.o;
    //    l = 31 - fio.size();
    //    fout2 << fio;
    //    for (size_t i = 0; i < l; i++)
    //        fout2 << " ";
    //    l = 17 - students[i].direct.size();
    //    fout2 << students[i].direct;
    //    for (size_t i = 0; i < l; i++)
    //        fout2 << " ";
    //    fout2 << students[i].phone_num;
    //}
    fi.close();
    fout1.close();
    fout2.close();
}
