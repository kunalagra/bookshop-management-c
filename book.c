#include <stdio.h>
#include <stdlib.h>
#include <string.h>	
#include <time.h>

struct bookinfo{
	char name[30],author[20];
	float price;
	int id;
}book[1000];
	
int choiceCase(int choice){
	FILE *fcs;
	switch (choice){
		case 1: 
			system("cls");
			int bnum,i;
			fcs = fopen("data.csv","a+");
			printf("\nNumber Of Books to Add: ");
			scanf("%d",&bnum);
			for(i=0;i<bnum;i++){
				printf("Enter Book Id: ");
				scanf("%d",&book[i].id);
				getchar();
				printf("\nEnter Book name: ");
				gets(book[i].name);
				printf("\nEnter Book Author: ");
				gets(book[i].author);
				printf("\nEnter Book Price (in rupee): ");
				scanf("%d",&book[i].price);
				fprintf(fcs, "\n%d,%s,%s,%d", book[i].id,book[i].name,book[i].author,book[i].price);
			}
			fclose(fcs);
			printf("Started Writing.");
			
			printf("\nCompleted Writing");
			printf("\nGoing back to main menu..");
			sleep(3);
			break;



	}
}

int main(){
	START:system("cls");
	int opt;
	printf("\n\n\t\tWelcome To Bookshop Management System");
	printf("\n\nWhat Would like to Do?");
	printf("\n1. Add Book Record");
	printf("\n2. Edit A Book Record");
	printf("\n3. Show the Entire Book Record");
	printf("\n4. Delete A Book Record");
	printf("\n5. Search a Book Record");
	printf("\n0. For Exit");
	printf("\nPlease enter your Option: ");
	scanf("%d",&opt);
	checkopt: 
	if (opt==0){
		printf("Exiting..");
		goto END;
	}
	else if((opt<6)&&(opt>=1)){
		choiceCase(opt);
		goto START;
	}
	else{
		printf("Please Enter A Valid number or press 0 to exit. ");
		scanf("%d",opt);
		goto checkopt;
	}
	END:
	return 0;
}