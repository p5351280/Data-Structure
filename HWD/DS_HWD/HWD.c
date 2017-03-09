#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 10000
#define ID 0
#define FIRSTNAME 1
#define LASTNAME 2
#define GENDER 3
#define AGE 4
#define PHONENUM 5

typedef struct{
    int id;
    char FirstName[15], LastName[15], Gender;
    int Age;
    char PhoneNum[15];
}Data;

Data data[MAX];
int count;
char item[6][10] = {"id","FirstName","LastName","Gender","Age","PhoneNum"};
bool ChooseItem[6];
int ChooseSort[6];
/*
 Choose Sort for make sure which kind of sorting algorithms it need
 1 for sel_sort, ASC
 -1 for DESC
 2 for ins_sort, ASC
 -2 for DESC
*/
bool CheckForSelect, CheckForFrom, CheckForOrder, CheckForBy;
bool Error;
int First;
int Second;
char command[MAX];
char FileName[MAX];

/*
 init global value
*/
void init(){
    for(int i=0; i<6; i++)
        ChooseItem[i] = ChooseSort[i] = 0;
    CheckForSelect = CheckForFrom = CheckForOrder = CheckForBy = false;
    Error = false;
    memset(FileName, 0, sizeof(FileName));
    First = Second = -1;
    count = 0;
}

void swap(void *a, void *b) {
    Data* temp = malloc(sizeof(Data));
    memcpy(temp, a, sizeof(Data));
    memcpy(a, b, sizeof(Data));
    memcpy(b, temp, sizeof(Data));
    free(temp);
}

/*
 if a>b, it will return the value bigger then 0
*/
int Item_cmp(Data* a, Data* b, int n){
    switch (n) {
        case ID:
            return a->id - b->id;
            break;
        case FIRSTNAME:
            return strcmp(a->FirstName,b->FirstName);
            break;
        case LASTNAME:
            return strcmp(a->LastName,b->LastName);
            break;
        case GENDER:
            return a->Gender - b->Gender;
            break;
        case AGE:
            return a->Age - b->Age;
            break;
        case PHONENUM:
            return strcmp(a->PhoneNum,b->PhoneNum);
            break;
    }
    return 0;
}

/*
 if return value bigger then 0, means it need to swap (because default ASC)
*/
int First_cmp(Data* a, Data* b){
    int temp;
    temp = Item_cmp(a, b, First);
    if(ChooseSort[First]<0) //if user choose DESC
        return -temp;
    else
        return temp;
}

/*
 if there need to do second compare, it will use this function
*/
int Second_cmp(Data* a, Data* b){
    int temp;
    temp = Item_cmp(a, b, Second);
    if(First_cmp(a, b)!=0)  //first sort final isn't the same, so they can't swap
        temp = 0;
    if(ChooseSort[Second]<0)
        return -temp;
    else
        return temp;
}

void Sel_sort(Data* a, int (*cmp)(Data* a, Data* b)){
    int min;
    for(int i=0; i<count-1; i++){
        min = i;
        for(int j=i+1; j<count; j++){
            if(cmp(a+min, a+j)>0){   //a[min] > a[j]
                min = j; //min = j
            }
        }
        swap(a+i, a+min);
    }
    /*
     for (int i = 0, minIndex; i < length - 1; ++i){
        minIndex = i;
        for (int j = i + 1; j < length; ++j)
            if (array[j] < array[minIndex])
                minIndex = j;
        swap(array[minIndex], array[i]);
     }
    */
}

void Ins_sort(Data* a, int (*cmp)(Data* a, Data* b)){
    Data *temp;
    temp = malloc(sizeof(Data));
    int i, j;
    for(i=1; i<count; i++){
        memcpy(temp, a+i, sizeof(Data));
        for(j=i-1; j>=0 && cmp(a+j, temp)>0; j--) //for (j=i-1; j >= 0 && a[j] > temp; j--)
            memcpy(a+(j+1), a+j, sizeof(Data));
        memcpy(a+(j+1), temp, sizeof(Data));
    }
    /*
     for (int i = 1, temp; i < length; ++i){
        temp = array[i];
        int j;
        for (j = i - 1; j >= 0 && array[j] > temp; --j)
            array[j + 1] = array[j];
        array[j + 1] = temp;
     }
    */
}

/*
 read the data from the file
*/
int Get_file(){
    FILE* fin = fopen(FileName, "r");
    if(fin == NULL)
        return 1;
    char temp[MAX];
    while(fgets(temp, MAX, fin)!=NULL){
        int len = (int)strlen(temp);
        if(temp[len-1] == '\n')
            temp[--len] = '\0';
        for(int i=0; i<len; i++){   // change all " and , to space in order for scanf to work
            if(temp[i]=='\"' || temp[i]==',')
                temp[i] = ' ';
        }
        //use sscanf to read data from temp
        sscanf(temp, "%d %s %s %c %d %s", &data[count].id, data[count].FirstName,
               data[count].LastName, &data[count].Gender, &data[count].Age,
               data[count].PhoneNum);
        memset(temp, '\0', sizeof(temp));
        count++;    //store how many data are there
    }
    fclose(fin);
    return 0;
}

int CheckForSortOption(char* temp){
    if(strcmp(temp, "-1")==0)
        return 1;
    if(strcmp(temp, "-2")==0)
        return 2;
    if(strcmp(temp, "DESC")==0)
        return 3;
    if(strcmp(temp, "ASC")==0)
        return 4;
    return -1;
}

//check the user input
int CheckWhatGet(char* temp){
    if(strcmp(temp, "id")==0)   //case-sensitive
        return 0;
    if(strcmp(temp, "FirstName")==0)
        return 1;
    if(strcmp(temp, "LastName")==0)
        return 2;
    if(strcmp(temp, "Gender")==0)
        return 3;
    if(strcmp(temp, "Age")==0)
        return 4;
    if(strcmp(temp, "PhoneNum")==0)
        return 5;
    if(strcasecmp(temp, "SELECT")==0)   //case-insensitive
        return 6;
    if(strcasecmp(temp, "FROM")==0)
        return 7;
    if(strcasecmp(temp, "ORDER")==0)
        return 8;
    if(strcasecmp(temp, "BY")==0)
        return 9;
    if(strcmp(temp, "*")==0)
        return 10;
    return -1;
}

/*
 Get syntax from the input
 And also identify if there is error in syntax
*/
int Get_syntax(){
    char* temp = strtok(command, " ,\n\r");
    int mode = 0;
    /*
     mode 0 start
     mode 1 select
     mode 2 from
     mode 3 Sort Option
     mode 4 More than one file
    */
    int item = 0;
    while(temp!=NULL) {
        if(strcmp(temp, "quit")==0)  return 1;
        int input = CheckWhatGet(temp);
        if(input == 6)  //SELECT
            mode = 1;
        else if(input==7 && mode==1)    //FROM
            mode = 2;
        else if(input == 8) //ORDER
            CheckForOrder = true;
        else if(input == 9){    //BY
            CheckForBy = true;
            mode = 3;
        }
        else if(mode == 1){ //choose the item need to show
            if(input == 10) //all need to show
                for(int i=0; i<6; i++)
                    ChooseItem[i] = true;
            else if(input == ID)
                ChooseItem[ID] = true;
            else if(input == FIRSTNAME)
                ChooseItem[FIRSTNAME] = true;
            else if(input == LASTNAME)
                ChooseItem[LASTNAME] = true;
            else if(input == GENDER)
                ChooseItem[GENDER] = true;
            else if(input == AGE)
                ChooseItem[AGE] = true;
            else if(input == PHONENUM)
                ChooseItem[PHONENUM] = true;
            else    //other item that is illegal
                Error = true;
            CheckForSelect = true;
        }
        else if(mode == 2){ //file part
            strcpy(FileName, temp);
            CheckForFrom = true;
            mode = 4;
        }
        else if(mode == 3){ //sorting part
            if(input == -1){    //sorting option
                input = CheckForSortOption(temp);
                if(input == 2)  //second sorting algorithms
                    ChooseSort[item] *= 2;
                if(input == 3)  //DESC
                    ChooseSort[item] *= -1;
                if(input == -1){
                    Error = true;
                    break;
                }
            }
            else{   //sorting item
                item = input;
                if(First<0)
                    First = item;
                else
                    Second = item;
                ChooseSort[item] = 1;   //default first sorting algorithms with ASC
            }
        }
        else{
            Error = true;
            break;
        }
        temp = strtok(NULL," ,\n\r");
    }
    return 0;
}

void sort(){
    if(Second<0 && First>=0){    //only one item need to sort
        if(abs(ChooseSort[First]) == 1)
            Sel_sort(data, First_cmp);
        if(abs(ChooseSort[First]) == 2)
            Ins_sort(data, First_cmp);
    }
    else if(Second>=0 && First>=0){   //two item need to sort
        if(abs(ChooseSort[First]) == 1) //sort the first item
            Sel_sort(data, First_cmp);
        else if(abs(ChooseSort[First]) == 2)
            Ins_sort(data, First_cmp);
        if(abs(ChooseSort[Second]) == 1)    //sort the second item
            Sel_sort(data, Second_cmp);
        else if(abs(ChooseSort[Second]) == 2)
            Ins_sort(data, Second_cmp);
    }
}

void Check_Error(){
    if(!(CheckForSelect && CheckForFrom))
        Error = true;
    if(CheckForOrder ^ CheckForBy)  //if the is only order or only by
        Error = true;
}

void print(){
    if(ChooseItem[ID])
        printf("%s\t", item[0]);
    if(ChooseItem[FIRSTNAME])
        printf("%10s", item[1]);
    if(ChooseItem[LASTNAME])
        printf("%13s", item[2]);
    if(ChooseItem[GENDER])
        printf("%7s", item[3]);
    if(ChooseItem[AGE])
        printf("%5s", item[4]);
    if(ChooseItem[PHONENUM])
        printf("%12s", item[5]);
    printf("\n");
    for(int i=0; i<count; i++){
        if(ChooseItem[ID])
            printf("%d\t", data[i].id);
        if(ChooseItem[FIRSTNAME])
            printf("%10s", data[i].FirstName);
        if(ChooseItem[LASTNAME])
            printf("%13s", data[i].LastName);
        if(ChooseItem[GENDER])
            printf("%4c", data[i].Gender);
        if(ChooseItem[AGE])
            printf("%7d", data[i].Age);
        if(ChooseItem[PHONENUM])
            printf("%14s", data[i].PhoneNum);
        printf("\n");
    }
}

int main(){
    while(fgets(command, MAX, stdin) != NULL){
        init();
        int len = (int)strlen(command);
        if(command[len-1] == '\n')
            command[--len] = '\0';
        if(Get_syntax())
            return 0;
        Check_Error();
        if(Error){
            printf("You have an error in your SQL syntax.\n");
            continue;
        }
        if(Get_file()) {
            printf("This file does not exist!\n");
            continue;
        }
        sort();
        print();
    }
    return 0;
}

//select Age, FirstName from /Users/Shuo-En/Downloads/DS_HWD/Contacts.csv order by Age -1, FirstName -2
//select * from /Users/Shuo-En/Downloads/DS_HWD/Contacts.csv order by Age DESC -2, FirstName -2
