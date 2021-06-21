#include <stdio.h>
#include <stdlib.h>
#include <string.h>	

struct bookinfo{
	char name[30],author[20];
	float price;
	int num;
};
int choiceCase(int choice){
	FILE *fcs;
	switch (choice){
		case 0: 
			printf("Exiting..");
			break;
		case 1: 
			fcs = fopen("data.csv",'a+');



	}
}

int main(){
	system("cls");
	int opt;
	START: printf("\n\n\t\tWelcome To Bookshop Management System");
	printf("\n\nWhat Would like to Do?");
	printf("\n1. Add Book Record");
	printf("\n2. Edit A Book Record");
	printf("\n3. Show the Entire Book Record");
	printf("\n4. Delete A Book Record");
	printf("\n5. Search a Book Record");
	printf("\n0. For Exit");
	printf("\nPlease enter your Option: ");
	scanf("%d",&opt);
	if((opt<6)&&(opt>=0))
		choiceCase(opt);
	else{
		printf("Please Enter A Valid number");
		goto START;
	}
	return 0;
}