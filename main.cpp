#include <locale.h>
#include "functions.h"

using namespace std;

/*Сформировать бинарный файл из элементов, заданной в варианте структуры, распечатать его содержимое, выполнить добавление элементов в соответствии со своим вариантом и поиск по одному из параметров (например, по фамилии, по государственному номеру, по году рождения и т.д.). Формирование, печать, добавление, поиск элементов оформить и выбор желаемого действия оформить в виде функций. Предусмотреть сообщения об ошибках при открытии файла и выполнении операций ввода/вывода.*/


int main()
{

    setlocale (LC_ALL, "Russian");
    struct chitatel new_name[10];
    bool flag = true;
    int num=0, a,v=0;
    FILE* fp, * bfp;
    
 fp= fopen("my_file.txt","rb");
    if(!(fp = fopen("my_file.txt","rb")))
    {
      printf("Невозможно открыть файл\n");
        while (v>3 || v<1){
      printf("1- Создать новый файл\n");
      printf("2- Загрузить данные с бэкапа\n");
      printf("3-Выход\n");
        scanf("%d",&v);
        switch (v) {
            case 1:
                fp= fopen("my_file.txt","w+b");
                fclose(fp);
                puts("ФАЙЛ СОЗДАН");
                break;
            case 2:
                
                bfp= fopen("backup.txt","rb");
                if(!(bfp = fopen("backup.txt","rb")))
                {
                    printf("Бэкап не найден\n");v=0;break;
                    }
                fread(new_name, sizeof(new_name),1,bfp);
                num =(int)(ftell(bfp))/382;
                fclose(bfp);
                fp= fopen("my_file.txt","w+b");
                rewrite(fp,new_name,num);
                break;
            case 3: puts("ПРОГРАММА ЗАВЕРШЕНА"); return 0;
            default: puts("Неверное действие, введите 1, 2 или 3.");
            break;}
        }
    }
    else {fread(new_name, sizeof(new_name),1,fp);
        num =(int)(ftell(fp))/382;
    }
    
    fp= fopen("my_file.txt","a+b");
    while (flag) {
        switch (menu())
        {
        case 1:
                cout << "Добавление читателя:" << endl;
                new_chitatel(fp,new_name, num);
                num++;
            break;
        case 2:
            print(new_name, num);
            break;
        case 3:
            research(new_name, num);
            break;
        case 4:
            change(new_name, num);
            clean(fp);
            rewrite(fp,new_name,num);
                break;
        case 5:
                sort(new_name, num);
                clean(fp);
                rewrite(fp,new_name,num);
                break;
        case 6:
            delet(new_name,num);
                num--;
            clean(fp);
            rewrite(fp,new_name,num);
            break;
        case 7:
                cout<<"Данные будут сброшены. Продолжить?"<<endl;
                cout<<"Нажмите 0, чтобы продолжить. Нажмите любую другую клавишу для выхода!"<<endl;
                cin>>a;
                switch (a) {
                    case 0:
                        clean(fp);
                            num=0;
                            cout<<"ВСЕ ДАННЫЕ БЫЛИ СБРОШЕНЫ!!!"<<endl;
                        break;
                    default:
                        break;
                }
                break;
            case 8:
                backup(new_name, num);
                break;
            case 9:
                cout<<"Данные файла будут обновлены. Продолжить?"<<endl;
                cout<<"Нажмите 0, чтобы продолжить. Нажмите любую другую клавишу для выхода!"<<endl;
                cin>>a;
                switch (a) {
               case 0:
                bfp= fopen("backup.txt","rb");
                if(!(bfp = fopen("backup.txt","rb")))
                {
                    printf("Бэкап не найден\n");break;
                    }
                fread(new_name, sizeof(new_name),1,bfp);
                        num =(int)(ftell(bfp))/382;
                fclose(bfp);
                fp= fopen("my_file.txt","w+b");
                rewrite(fp,new_name,num);
                printf("\nВ ФАЙЛ ЗАПИСАНЫ ДАННЫЕ БЭКАПА!\n");
                    break;
                default:
                        break;
                }
                break;
        case 0:
            flag = false;
                cout <<"ПРОГРАММА ЗАВЕРШЕНА"<< endl;
            break;
        default:
            printf("\nНеизвестная операция!\n");
            break;
        }
        
    }
    fclose(fp);
    return 0;
}



