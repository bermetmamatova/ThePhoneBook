#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef  struct {
    char name[30];
    char number[30];
}phone_book ;

typedef struct {
    int size;
    int inserted_size;
    phone_book *pb;

}phone;


void init(phone *pbook,int size){

    pbook->size=size;
    pbook->inserted_size=0;
    pbook->pb= malloc(sizeof(phone_book)*size);

}

bool insert(phone *phone,char name[],char number[]){

    bool isFul=false;
    bool isExist=false;


    for(int i=0;i<phone->inserted_size;i++){

        if(strcmp(name,phone->pb[i].name)==0){
            strcpy(phone->pb[i].number,number);
            isExist=true;
        }
    }
    if(phone->inserted_size>=phone->size && isExist==false){
        isFul=true;
        printf("Phone Book is Full:\n");
    }

    if(isExist==false && isFul==false){
        phone_book pbook;
        strcpy(pbook.name,name);
        strcpy(pbook.number,number);
        phone->pb[phone->inserted_size++] = pbook;
    }

    return isFul;
}

char *get(phone *phone,char name[]){

    for(int i=0;i<phone->inserted_size;i++){
        if(strcmp(name,phone->pb[i].name)==0){
            return phone->pb[i].number;
        }
    }
    return NULL;

}

void print(phone *phone){
    for(int i=0;i<phone->inserted_size;i++){
        printf("%s : %s \n",phone->pb[i].name,phone->pb[i].number);
    }
}

void dump(phone *phone ,char fileName[]){
    FILE *output;
    output= fopen(fileName,"w+");

    for(int i=0;i<phone->inserted_size;i++){
        fprintf(output, "%s : %s\n", phone->pb[i].name, phone->pb[i].number);
        fseek(output, 0, SEEK_CUR);
    }
    fclose(output);
}

void destroy(phone *phone){
    free(phone);
}

int main(){

    phone phonebook;

    init(&phonebook,10);


    insert(&phonebook,"Monika","+3619990147");
    insert(&phonebook,"Joey","+3615507903");
    insert(&phonebook,"Chandler","+3618001724");


    printf("%s\n",get(&phonebook,"Monika"));


    print(&phonebook);


    dump(&phonebook,"PhoneBook.txt");
    destroy(&phonebook);


    return 0;
}
