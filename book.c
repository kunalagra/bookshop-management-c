#include <stdio.h>
#include <stdlib.h>
#include <string.h>	
#include <time.h>

struct bookinfo{
	char name[30],author[20];
	int id, price;
}book[1000];

int notfound(){
	printf("\nBook ID not found!");
	printf("\nReturning to Main Menu..");
	sleep(4);
	return 0;
}
	
int choiceCase(int choice){
	FILE *fcs;
	system("cls");
	fcs = fopen("data.csv","r");
	char line[1024];
	int j=0,inid,foundflag=0;
	char *bid,*bname,*bauth,*bprice;
	printf("\nReading Books Record..\n");
	while (fgets(line, 1024, fcs)!=NULL){
		bid = strtok(line,",");
		bname=strtok(NULL, ",");
		bauth=strtok(NULL, ",");
		bprice=strtok(NULL, ",");
		book[j].id = atoi(bid);
		strcpy(book[j].name,bname);
		strcpy(book[j].author,bauth);
		book[j].price = atoi(bprice);
		j++;
	}
	fclose(fcs);
	switch (choice){
		case 1: 
			fcs = fopen("data.csv","a+");
			printf("\nNumber Of Books to Add: ");
			scanf("%d",&inid);
			int i;
			for(i=0;i<inid;i++){
				printf("\nEnter Book Id: ");
				scanf("%d",&book[i].id);
				getchar();
				printf("Enter Book name: ");
				gets(book[i].name);
				printf("Enter Book Author: ");
				gets(book[i].author);
				printf("Enter Book Price (in rupee): ");
				scanf("%d",&book[i].price);
				fprintf(fcs, "%d,%s,%s,%d\n", book[i].id,book[i].name,book[i].author,book[i].price);
			}
			fclose(fcs);
			printf("\nNew Records have been added successfully");
			printf("\nReturning to main menu..");
			sleep(3);
			return 0;
		case 2:
			printf("\nEnter Book ID to Edit: ");
			scanf("%d",&inid);
			for(int s=0;s<j;s++){
				if(inid==book[s].id){
					foundflag++;
					printf("Editing Data for Book ID: %d & Book Name: %s",book[s].id,book[s].name);
					printf("\n\nEnter new Book Id: ");
					scanf("%d",&book[s].id);
					getchar();
					printf("Enter New Book name: ");
					gets(book[s].name);
					printf("Enter new Book Author: ");
					gets(book[s].author);
					printf("Enter new Book Price (in rupee): ");
					scanf("%d",&book[s].price);
					break;
				}
			}
			if (foundflag==1){
				printf("\nWriting Changes.. ");
				fcs = fopen("data.csv","w");
				for(int s=0;s<j;s++){
					fprintf(fcs, "%d,%s,%s,%d\n", book[s].id,book[s].name,book[s].author,book[s].price);
				}
				fclose(fcs);
				printf("\nReturning to Main Menu..");
				sleep(3);
				return 0;
			} 
			else {
				notfound();
				return 0;
			}

		case 3:
			printf("\n");
			for(int s=0;s<j;s++){
				printf("**************************");
				printf("\n\nBook ID: %d \nBook Name: %s \nBook Author: %s \nBook Price: %d\n",book[s].id,book[s].name,book[s].author,book[s].price);
				printf("\n**************************");
			
			}
			int exit1;
			wait:
			printf("\nPress 0 to return to main menu: ");
			scanf("%d",&exit1);
			if (exit1==0)
				return 0;
			else
				goto wait;

		case 4:
			printf("\nEnter the Book ID to delete: ");
			scanf("%d",&inid);
			int ss;
			for(ss=0;ss<=j;ss++){
				if(inid==book[ss].id){
					foundflag++;
					break;
				}
			}
			if (foundflag==1){
				printf("\nWriting Changes.. ");
				fcs = fopen("data.csv","w");
				for(int kk=0;kk<j;kk++){
					if(kk==ss){
						kk++;
						fprintf(fcs, "%d,%s,%s,%d\n", book[kk].id,book[kk].name,book[kk].author,book[kk].price);
					}
					else
						fprintf(fcs, "%d,%s,%s,%d\n", book[kk].id,book[kk].name,book[kk].author,book[kk].price);
				}
				fclose(fcs);
				printf("\nReturning to Main Menu..");
				sleep(3);
				return 0;
			} 
			else {
				notfound();
				return 0;
			}
		case 5:
			printf("Enter The Book ID to fetch Details: ");
			scanf("%d",&inid);
			for(ss=0;ss<=j;ss++){
				if(inid==book[ss].id){
					foundflag++;
					break;
				}
			}
			if (foundflag==1){
				printf("**************************");
				printf("\n\nBook ID: %d \nBook Name: %s \nBook Author: %s \nBook Price: %d\n",book[ss].id,book[ss].name,book[ss].author,book[ss].price);
				printf("\n**************************");
				printf("\nPress 0 to return to main menu: ");
				int exit2;
				scanf("%d",&exit2);
				if (exit1==0)
					return 0;
				else
					goto wait;
			}
			else
				notfound();
	}
}

int main(){
	START:system("cls");
	int opt;
	printf("\n\n\n\t\tWelcome To Bookshop Management System");
	printf("\n\n\nWhat Would like to Do?\n");
	printf("\n1. Add Book Record");
	printf("\n2. Edit A Book Record");
	printf("\n3. Show the Entire Book Record");
	printf("\n4. Delete A Book Record");
	printf("\n5. Search a Book Record");
	printf("\n0. For Exit");
	printf("\n\nPlease enter your Option: ");
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
		printf("\nPlease Enter A Valid number or press 0 to exit. ");
		scanf("%d",opt);
		goto checkopt;
	}
	END:
	return 0;
}