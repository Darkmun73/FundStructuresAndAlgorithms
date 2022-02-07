#include <iostream>
using namespace std;

//Мультимножество 1 (с повторяющимися элементами), неупорядоченный список (добавление в конец списка) 

struct Elem //элемент списка
{
    int value;
    Elem* next; //след элемент списка
    Elem* prev; //пред элемент списка
};

struct Chain //список
{
    Elem* head;
};



void init(Chain &multi) //инициализация списка
{
    multi.head = NULL;
}

void add(Chain &multi, int v) //добавление в конец списка
{
    Elem* newElem = new Elem;
    newElem->value = v;
    if (multi.head == NULL)
    {
        multi.head = newElem;
        newElem->next = NULL;
    }
    else
    {
        Elem* cur = multi.head;
        while (cur->next != NULL)
        {
            cur = cur->next; 
        }
        cur->next = newElem;
        newElem->next = NULL;
        newElem->prev = cur;
    }
}

int found(Chain multi, int v) //поиск заданного элемента
{
    int count = 0;
    Elem* cur = multi.head;
    while (cur != NULL)
    {
        if (cur->value == v)
            count = count + 1;
        cur = cur->next;
    }
    /*if (count == 0)
        cout << "Заданный элемент не найден" << endl;
    else if (count == 1)
        cout << "Найден 1 элемент" << endl;
    else
        cout << "Найдено " << count << " элементов" << endl;*/
    return count;
}

void del(Chain &multi, int v) //удаление заданного элемента
{
    found(multi, v);
    Elem* cur = multi.head;
    Elem* cur1;
    int count = 0;
    while (cur != NULL)
    {
        
        if (cur->value == v)
        {
            count += 1;
            if (cur == multi.head)
            {
                cur1 = cur;
                multi.head = multi.head->next;
                cur = multi.head;
                delete(cur1);
            }
            else
            {
                cur1 = cur;
                cur = cur->prev;
                cur1->prev->next = cur1->next;
                if (cur1->next != NULL)
                cur1->next->prev = cur1->prev;
                delete(cur1);
                cur = cur->next;
            }
        }
        else
            cur = cur->next;
    }
    /*if (count == 0)
        cout << "Удаление не совершено" << endl;
    else
        cout << "Удаление завершено" << endl;*/
}

void print(Chain multi) //печать списка
{
    if (multi.head == NULL)
    {
        cout << "Empty" << endl;
    }
    else
    {
        Elem* cur = multi.head;
        cout << "Множество: {";
        while (cur != NULL)
        {
            cout << cur->value;
            cur = cur->next;
            if (cur == NULL)
                cout << "";
            else
                cout << ", ";
        }
        cout << "}" << endl;
    }
}

void free(Chain &multi) //освобождение памяти
{
    while (multi.head != NULL)
    {
        Elem* cur = multi.head;
        multi.head = multi.head->next;
        delete(cur);
    }
}

Chain multi_union(Chain multi1, Chain multi2) //объединение множеств
{
    Chain C;
    init(C);
    Elem* cur1 = multi1.head;
    while (cur1 != NULL)
    {
        add(C, cur1->value);
        cur1 = cur1->next;
    }
    Elem* cur2 = multi2.head;
    while (cur2 != NULL)
    {
        add(C, cur2->value);
        cur2 = cur2->next;
    }
    return C;
}

Chain multi_inter(Chain multi1, Chain multi2) //пересечение множеств
{
    Chain C;
    //Chain m1 = multi1;
    init(C);
    //Elem* C1 = C.head;
    Elem* cur1 = multi1.head;
    Elem* cur2 = multi2.head;
    Elem* cur1_new = multi1.head;
    Elem* cur2_new = multi2.head;
    Elem* mem = multi1.head;
    Elem* C1 = C.head;
    while (cur1 != NULL)
    {
        while ((C1 != NULL) && (cur1 != NULL))
        {
            if (cur1->value == C1->value)
            {
                cur1 = cur1->next;
                C1 = C.head;
            }
            else
                C1 = C1->next;
        }
        C1 = C.head;
        if (cur1 != NULL)
        {
            if ((found(multi1, cur1->value)) > (found(multi2, cur1->value)))
            {
                for (int i = 0; i < found(multi2, cur1->value); i++)
                {
                    add(C, cur1->value);
                }
            }
            else
            {
                for (int i = 0; i < found(multi1, cur1->value); i++)
                {
                    add(C, cur1->value);
                }
            }
            cur1 = cur1->next;
        }
        
    }
    /*while (cur1 != NULL)
    {
            while (cur2 != NULL)
            {
                if ((cur1->value == cur2->value))
                {
                    cur1_new = cur1;
                    cur2_new = cur2;
                    mem = cur1;
                    while ((cur1_new->value == cur2_new->value))
                    {
                        //while (cur1 !=)
                        add(C, cur1_new->value);
                        cur1_new = cur1_new->next;
                        //cur2 = cur2->next;
                        if ((cur1_new != NULL) && (cur2_new != NULL))
                        {
                            while (cur1_new->value != cur2_new->value)
                            {
                                cur1_new = cur1_new->next;
                                if (cur1_new == NULL)
                                    break;
                            }
                        }
                        if ((cur1_new != NULL) && (cur2_new != NULL))
                        {
                            cur2_new = cur2_new->next;
                            if (cur2_new != NULL)
                            {
                                while (cur2_new->value != cur1_new->value)
                                {
                                    cur2_new = cur2_new->next;
                                    if (cur2_new == NULL)
                                        break;
                                } 
                            }
                            
                            //add(C, cur1->value);

                        }
                        if ((cur1_new == NULL) || (cur2_new == NULL))
                            break;
                        cur2 = NULL;

                    }
                    
                }
                else
                    if (cur2 != NULL)
                        cur2 = cur2->next;
                del(multi1, mem->value);
                cur1 = multi1.head;
            }
            cur1 = cur1->next;
            //cur1 = multi1.head;
            cur2 = multi2.head;
            //C1 = C.head;
        //}
        
    }
    //multi1 = m1;*/
    return C;
}

Chain multi_compl(Chain multi1, Chain multi2) //разность множеств
{
    Chain C;
    //Chain m1 = multi1;
    init(C);
    //Elem* C1 = C.head;
    Elem* cur1 = multi1.head;
    Elem* cur2 = multi2.head;
    Elem* cur1_new = multi1.head;
    Elem* cur2_new = multi2.head;
    Elem* mem = multi1.head;
    Elem* C1 = C.head;
    while (cur1 != NULL)
    {
        while ((C1 != NULL) && (cur1 != NULL))
        {
            if (cur1->value == C1->value)
            {
                cur1 = cur1->next;
                C1 = C.head;
            }
            else
                C1 = C1->next;
        }
        C1 = C.head;
        if (cur1 != NULL)
        {
            if ((found(multi1, cur1->value)) > (found(multi2, cur1->value)))
            {
                for (int i = 0; i < (found(multi1, cur1->value) - found(multi2, cur1->value)); i++)
                {
                    add(C, cur1->value);
                }
            }
            cur1 = cur1->next;
        }

    }
    while (cur1 != NULL)
    {
        while (cur2 != NULL)
        {
            if (cur1->value == cur2->value)
            {
                add(C, cur1->value);
                cur2 = NULL;
            }
            if (cur2 != NULL)
                cur2 = cur2->next;
        }
        cur1 = cur1->next;
        cur2 = multi2.head;
    }
    return C;
}

int card(Chain multi) //мощность множества
{
    int count = 0;
    Elem* cur = multi.head;
    while (cur != NULL)
    {
        count = count + 1;
        cur = cur->next;
    }
    cout << "Мощность множества: " << count << endl;
    return count;
}

Chain H1, H2, C;
int main()
{
    setlocale(LC_ALL, "Russian");
    init(H1);
    add(H1, 4);
    add(H1, -2);
    add(H1, 5);
    print(H1);
    /*init(H1);
    init(H2);
    for (int i = 1; i < 10; i++)
    {
        add(H1,10- i);
       add(H2, i%6);
    }
    print(H1);
    print(H2);


    for (int i = 1; i < 10; i+=2)
    {
       del(H1, i);
       del(H2, i % 6);
    }
    print(H1);
    print(H2);

    for (int i = 1; i < 10; i++)
    {
        add(H1, 10 - i);
        add(H2, i % 6);
    }
    //print(H2);
    C = multi_inter(H2, H1);
    print(H1);
    print(H2);
    print(C);
    card(C);
    C = multi_compl(H2, H1);
    print(C);
    card(C);*/

    return 0;
}
