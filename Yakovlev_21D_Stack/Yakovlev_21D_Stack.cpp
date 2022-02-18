// Yakovlev_21D_Stack
// В созданном спискеопределить количество и удалить все элементы, находящиеся между минимальным и максимальнымэлементами.
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <ctime>


using namespace std;

struct List
{
    int info;
    List* pred, * next;
};

// Функция вставляет элемент р в список ПОСЛЕ элемента last
// И возвращает указатель на вставленный в список элемент
List* InsertElementIntoList(List* last, List* p)
{
    if (last && p)
    {
        p->pred = last;
        p->next = last->next;
        last->next = p;
        p->next->pred = p;
        return p;
    }
    else
        return NULL;
}

// Функция создает двусвязный список из n элементов
// Возвращает через head и tail адреса головы и хвоста списка
void CreateRandomList(List*& head, List*& tail, int n)
{
    head = new List;
    tail = new List;
    head->next = tail;
    tail->pred = head;

    List* last = head; // последний вставленный в список элемент
    for (int i = 0; i < n; i++)
    {
        List* p = new List;
        p->info = rand() % 200 - 100; // от -100 до 100
        last = InsertElementIntoList(last, p);
    }
}


// Вывод списка на консоль
void PrintList(List* head, List* tail)
{
    List* p = head->next;
    while (p != tail)
    {
        cout << setw(6) << p->info;
        p = p->next;
    }
    cout << endl;
    return;
}

// Функция исключает из списка элемент p, и возвращает адрес элемента, следававшего ПОСЛЕ удаленного
List* RemoveElement(List* p)
{
    if (p)
    {
        List* p1 = p->pred;
        List* p2 = p->next;
        p1->next = p2;
        p2->pred = p1;
        p->next = p->pred = NULL;
        return p2;
    }
    else
        return NULL;
}

//Функция удаляет из списка все элементы с отрицательной информационной частью
void DeleteNegativeElements(List* head, List* tail)
{
    List* p = head->next;
    while (p != tail)
    {
        if (p->info < 0)
        {
            List* q;
            q = RemoveElement(p);
            delete p;
            p = q;
        }
        else
            p = p->next;
    }
    return;
}

//Функция поиска минимума, возвращает указатель на минимум
List* Minimum(List* head, List* tail)
{
    List* p = head->next;
    List* min = head->next;
    while (p != tail)
    {
        if (p->info < min->info)
        {
            min = p;
            p = p->next;
        }
        else
            p = p->next;
    }
    return min;
}

//Функция поиска максимума, возвращает указатель на максимум
List* Maximum(List* head, List* tail)
{
    List* p = head->next;
    List* max = head->next;
    while (p != tail)
    {
        if (p->info > max->info)
        {
            max = p;
            p = p->next;
        }
        else
            p = p->next;
    }
    return max;
}

//Функция удаляет из списка все элементы между минимальным и максимумальным
void DeleteBetweenMinMax(List* head, List* tail)
{
    List* buf;

    if (head > tail)
    {
        buf = tail;
        tail = head;
        head = buf;
    }

    List* p = head->next;
    while (p != tail)
    {
        List* q;
        q = RemoveElement(p);
        delete p;
        p = q;
    }
    return;
}

//Функция перемещает в голову списка последовательно все элементы с нечетной информационной частью
void MoveOddElementsToHead(List* head, List* tail)
{
    List* p = head->next;
    while (p != tail)
    {
        if (p->info % 2 == 1)
        {
            List* q = RemoveElement(p);
            InsertElementIntoList(head, p);
            p = q;
        }
        else
            p = p->next;
    }
    return;
}


int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    List* head = NULL, * tail = NULL;
    CreateRandomList(head, tail, 10);
    cout << "Исходный список" << endl;
    PrintList(head, tail);

    cout << "Первый минимум" << endl;
    cout << Minimum(head, tail)->info << endl;
    cout << "Последний максимум" << endl;
    cout << Maximum(head, tail)->info << endl;

    DeleteBetweenMinMax(Minimum(head, tail), Maximum(head, tail));
    cout << "Новый список" << endl;
    PrintList(head, tail);

    system("pause");
    return 0;
}