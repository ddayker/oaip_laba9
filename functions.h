#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;

struct name
{
    char familia[100];
    char imya[100];
    char otchestvo[100];
};

struct date
{
    int day;
    int month;
    int year;
};

struct chitatel
{
    char nomer[10];
    char kniga[60];
    struct name person;
    struct date data;
};

int menu()
{
    int choice;
    printf( "Выберите операцию:\n");
    printf( "1) Добавление нового читателя в файл\n");
    printf( "2) Вывод информации о всех читателях\n");
    printf( "3) Поиск читателя\n");
    printf( "4) Изменение информации о читателе\n");
    printf( "5) Сортировка (по дате возврата) \n");
    printf( "6) Удаление информацию о читателе с файла\n");
    printf( "7) Сброс данных и отчистка файла\n");
    printf( "8) Бэкап файла\n");
    printf( "9) Откат к бэкапу\n");
    printf( "0) Выход.\n");
    scanf("%d", &choice);
    return choice;
}

void clean(FILE* fp){
    fclose(fp);
    fp= fopen("my_file.txt","w+b");
}

void rewrite(FILE* fp,chitatel p_chitatel[10], int num){
    int i = 0;
    while (i < num) {
        fwrite((p_chitatel+i), sizeof(*p_chitatel),1,fp);
        i++;
    }
}

void new_chitatel(FILE* fp,chitatel p_chitatel[10], int num)
{
    
    if (num<10){
    printf("Читатель №%d\n",num+1);
    cout << "Введите полное имя ( Фамилия, Имя, Отчество):" << endl;
    cout << "Фамилия: ";
    cin >> (p_chitatel + num)->person.familia;
    cout << "Имя: ";
    cin >> (p_chitatel+ num)->person.imya;
    cout << "Отчество: ";
    cin >> (p_chitatel+ num)->person.otchestvo;
        
       while (true){
    cout << "Введите номер билета: ";
    cin >> (p_chitatel + num)->nomer;
           int flag =0;
        for (int i = 0; i < num; i++) {
            if (strcmp((p_chitatel + i)->nomer, (p_chitatel + num)->nomer) == 0){
                cout << "Этот номер уже занят!" <<endl;flag++;}
         }
           if(flag==0)break;
       }
        
    cout << "Введите название книги: ";
    getchar();
    gets((p_chitatel + num)->kniga);
    cout << "Введите дату возврата (День,Месяц, Год):" << endl;
    while (true) {
        cout << "День: ";
        cin >> (p_chitatel + num)->data.day;
        if(p_chitatel[num].data.day>31 || p_chitatel[num].data.day<1)cout<<"Неверный ввод"<< endl;
        else break;
    }
    while (true) {
        cout << "Номер месяца: ";
        cin >> (p_chitatel + num)->data.month;
        if(p_chitatel[num].data.month>12 || p_chitatel[num].data.month<1)cout<<"Ошибка, повторите ввод!"<< endl;
        else break;
    }
    while (true) {
        cout << "Год: ";
        cin >> (p_chitatel + num)->data.year;
        if(p_chitatel[num].data.year>2032 || p_chitatel[num].data.year<2022)cout<<"Ошибка, повторите ввод!"<< endl;
        else break;
    }
    cout << endl;
    fwrite((p_chitatel+num), sizeof(*p_chitatel),1,fp);
    return;
    }
    else cout << "\nМАССИВ ПЕРЕПОЛНЕН!\n"<< endl;
}

void print(FILE* fp,chitatel* p_chitatel, int num)
{
    
    if (num == 0)
    {
        cout << "ДАННЫХ НЕТ! Введите данные." << endl;
        return;
    }
    

    for (int i = 0; i < num; i++)
    {
        cout << " Читатель №" << i + 1 << endl;
        cout << "Полное имя:" << (p_chitatel + i)->person.familia<<" "<<
        (p_chitatel+ i)->person.imya<<" "<<(p_chitatel+ i)->person.otchestvo <<endl;
        cout << "Номер билета: "<< (p_chitatel + i)->nomer << endl;
        cout << "Название книги: " << (p_chitatel + i)->kniga << endl;
        cout << "Дата возврата (День, Месяц, Год):" <<(p_chitatel + i)->data.day <<
        "/"<< (p_chitatel + i)->data.month << "/"<< (p_chitatel + i)->data.year <<endl;
        cout << "------------------------------------------------------------" << endl;
        cout << endl;
        
    }
}


void print1(chitatel* p_chitatel, int num)
{
        cout << "Полное имя:" << (p_chitatel + num)->person.familia<<" "<<
        (p_chitatel+ num)->person.imya<<" "<<(p_chitatel+ num)->person.otchestvo <<endl;
        cout << "Номер билета: "<< (p_chitatel + num)->nomer << endl;
        cout << "Название книги: " << (p_chitatel + num)->kniga << endl;
        cout << "Дата возврата (День, Месяц, Год):" <<(p_chitatel + num)->data.day <<
        "/"<< (p_chitatel + num)->data.month << "/"<< (p_chitatel + num)->data.year <<endl;
        cout << "------------------------------------------------------------"<< endl;
        cout << endl;

}

void research(chitatel* p_chitatel, int num)
{
    if (num == 0)
    {
        cout << "Введите данные!" << endl;
        return;
    }
    int choice;
    while (1) {
        cout << "Выберите параметр, по которому будет осуществлён поиск:" << endl;
        cout << "1) Номер билета;" << endl;
        cout << "2) ФИО;" << endl;
        cout << "3) Название книги;" << endl;
        cout << "4) Выход." << endl;
        cin >> choice;
        char str[60];
        char str2[60];
        char str3[60];
        int flag = 0;
        switch (choice)
        {
        case 1:
            cout << "Введите номер : ";
            getchar();
            flag = 0;
            gets(str);

            for (int i = 0; i < num; i++) {
                if (strcmp((p_chitatel + i)->nomer, str) == 0) {
                    cout << "Параметр найден, это " << " Читатель №" << i + 1 << endl;
                    print1(p_chitatel, i);
                    flag++;
                }
            }
            if (flag == 0)
            {
                cout << "Читатель с такими параметрами не найден!" << endl;
            }
            break;
        
        case 2:
            cout << "Введите ФИО:" << endl;
            getchar();
            cout << "Фамилия: ";
            cin >> str;
            cout << "Имя: ";
            cin >> str2;
            cout << "Отчество: ";
            cin >> str3;
            flag = 0;
            for (int i = 0; i < num; i++)
            {
                if (strcmp((p_chitatel + i)->person.familia, str)==0 && strcmp((p_chitatel + i)->person.imya ,str2)==0 && strcmp((p_chitatel + i)->person.otchestvo,str3)==0)
                {
                    cout << "Параметр найден, это " << " Читатель №" << i + 1 << endl;
                    print1(p_chitatel, i);
                    flag++;
                }

            }
            if (flag == 0)
            {
                cout << "Читатель с такими параметрами не найден!" << endl;
            }
            break;
                
        case 3:
            cout << "Введите название книги: ";
            getchar();
            gets(str);
            flag = 0;
            for (int i = 0; i < num; i++) {
                if (strcmp((p_chitatel + i)->kniga, str)==0) {
                    cout << "Параметр найден, это " << " Читатель №" << i + 1 << endl;
                    print1(p_chitatel, i);
                    flag++;
                }
            }
            if (flag == 0)
            {
                cout << "Читатель с такими параметрами не найден!" << endl;
            }
            break;
        case 4:
            cout << "Поиск окончен!" << endl;
            return;
            break;
        default:
            cout << "Неверное действие!" << endl;
            break;
        }
    }

}
void change(chitatel* p_chitatel, int num)
{
    if (num == 0)
    {
        cout << "Введите данные!" << endl;
        return;
    }
    int choice, numb=-1;
    while (numb> num  || numb <= 0){
    cout << "Читатель(по порядку), для которого необходимо изменить информацию: ";
        cin >> numb;
    }
    numb--;
    
    while (1) {
        cout << "Выберите параметр, который хотите изменить:" << endl;
        cout << "1) Номер билета;" << endl;
        cout << "2) ФИО;" << endl;
        cout << "3) Название книги;" << endl;
        cout << "4) Дата возврата;" << endl;
        cout << "5) Выход." << endl;
        cin >> choice;
        if (choice == 5)
        {
            cout << "Операция завершена!" << endl;
            return;
        }
       
        char str[60];
        char str2[60];
        char str3[60];
        switch (choice)
        {
        case 1:
                 while (true){
                 cout << "Введите новый номер билета: ";
                 getchar();
                 cin>> str;
                     int flag =0;
                  for (int i = 0; i < num; i++) {
                      if (strcmp((p_chitatel + i)->nomer, str) == 0){
                          cout << "Этот номер уже занят!" <<endl;flag++;}
                   }
                     if(flag==0)break;
                 }
            strcpy((p_chitatel + numb)->nomer, str);
            break;
        case 2:
            cout << "ФИО:" << endl;
            getchar();
            cout << "Фамилия: ";
            gets(str);
            cout << "Имя: ";
            gets(str2);
            cout << "Отчество: ";
            gets(str3);
            strcpy((p_chitatel + numb)->person.familia, str);
            strcpy((p_chitatel + numb)->person.imya, str2);
            strcpy((p_chitatel + numb)->person.otchestvo, str3);
            break;
            case 3:
                cout << "Введите название книги: ";
                getchar();
                gets(str);
                strcpy((p_chitatel + numb)->kniga, str);
                break;
            case 4:
                cout << "Введите дату возврата (День,Месяц, Год):" << endl;
                while (true) {
                    cout << "День: ";
                    cin >> (p_chitatel + numb)->data.day;
                    if(p_chitatel[numb].data.day>31 || p_chitatel[numb].data.day<1)cout<<"Неверный ввод"<< endl;
                    else break;
                }
                while (true) {
                    cout << "Номер месяца: ";
                    cin >> (p_chitatel + numb)->data.month;
                    if(p_chitatel[numb].data.month>12 || p_chitatel[numb].data.month<1)cout<<"Ошибка, повторите ввод!"<< endl;
                    else break;
                }
                while (true) {
                    cout << "Год: ";
                    cin >> (p_chitatel + numb)->data.year;
                    if(p_chitatel[numb].data.year>2032 || p_chitatel[numb].data.year<2022)cout<<"Ошибка, повторите ввод!"<< endl;
                    else break;
                }
                cout << endl;
                break;
        default:
            cout << "Неверная операция!" << endl;
            break;
        }

    }
    
}
void delet(chitatel* p_chitatel, int num)
{
    int choice=-1;
    while (choice > num  || choice <= 0){
        cout << "Введите поярдковый номер читателя, которого хотите удалить: ";
            cin >> choice;
        if(choice > num || choice <= 0)cout << "Такого читателя не существует"<< endl;
        }
        choice--;
        for (int i = choice; i <= num; i++) {
            p_chitatel[i] = p_chitatel[i + 1];
        }
        cout << "Опрерация завершена!" << endl;
    }

void sort(chitatel* p_chitatel, int num)
{
    if (num == 0)
    {
        cout << "Введите данные!" << endl;
        return;
    }
chitatel tmp;
for (int j = 0; j < num - 1; j++) {
            for (int i = 0; i < num - 1; i++) {
if( p_chitatel[i].data.day+p_chitatel[i].data.month*31+p_chitatel[i].data.year*365>
p_chitatel[i+1].data.day+p_chitatel[i+1].data.month*31+p_chitatel[i+1].data.year*365){
tmp = p_chitatel[i];
p_chitatel[i] = p_chitatel[i+1];
p_chitatel[i+1] = tmp;
}
}
}
cout << "\nСортировка завершена!\n" << endl;
}

void backup(chitatel p_chitatel[10],int num)
{
    if (num == 0 ){
        cout << "Файл пуст...Бэкап не был выполнен!"<<endl;
    }
    else {
        FILE* bfp;
        bfp= fopen("backup.txt","w+b");
        int i = 0;
        while (i < num) {
            fwrite((p_chitatel+i), sizeof(*p_chitatel),1,bfp);
            i++;
        }
        fclose(bfp);
        cout<<"\nБэкап был выполнен\n"<<endl;
    }
}
