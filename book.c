#include <stdio.h>
#include <stdlib.h>
#include <string.h>	
#include <time.h>

struct bookinfo{
	char name[30],author[20];
	int id, price;
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
				fprintf(fcs, "%d,%s,%s,%d\n", book[i].id,book[i].name,book[i].author,book[i].price);
			}
			fclose(fcs);
			printf("Started Writing.");
			printf("\nCompleted Writing");
			printf("\nGoing back to main menu..");
			sleep(3);
			return 0;
		case 2:
			system("cls");
			fcs = fopen("data.csv","r");
			char line[1024];
			int j=0,recnum;
			char *bid,*bname,*bauth,*bprice;
			printf("\nReading Books Record..");
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
			record:
			printf("\nEnter Book ID to Edit: ");
			scanf("%d",&recnum);
			int foundflag=0;
			for(int s=0;s<j;s++){
				if(recnum==book[s].id){
					foundflag++;
					printf("Editing Data for Book ID: %d & Book Name: %s",book[s].id,book[s].name);
					printf("\n\nEnter new Book Id: ");
					scanf("%d",&book[s].id);
					getchar();
					printf("\nEnter New Book name: ");
					gets(book[s].name);
					printf("\nEnter new Book Author: ");
					gets(book[s].author);
					printf("\nEnter new Book Price (in rupee): ");
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
				printf("Returning to Main Menu..");
				sleep(3);
				return 0;
			} 
			else {
				printf("Book ID not found!");
				printf("Returning to Main Menu..");
				sleep(3);
				return 0;
			}

		case 3:
			system("cls");
			fcs = fopen("data.csv","r");
			printf("\nReading Books Record..\n");
			char line2[1024];
			char *bid2,*bname2,*bauth2,*bprice2;
			while (fgets(line2, 1024, fcs)!=NULL){
				bid2=strtok(line2, ",");
				bname2=strtok(NULL, ",");
				bauth2=strtok(NULL, ",");
				bprice2=strtok(NULL, ",");
				printf("**************************");
				printf("\n\nBook ID: %s \nBook Name: %s \nBook Author: %s \nBook Price: %s\n",bid2,bname2,bauth2,bprice2);
				printf("**************************");
			}
			fclose(fcs);
			int exit1;
			wait:
			printf("\nPress 0 to return to main menu: ");
			scanf("%d",&exit1);
			if (exit1==0)
				return 0;
			else
				goto wait;
		case 4:
			system("cls");
			fcs = fopen("data.csv","r");
			char line3[1024];
			int jj=0,delid;
			char *bid3,*bname3,*bauth3,*bprice3;
			printf("\nReading Books Record..");
			while (fgets(line3, 1024, fcs)!=NULL){
				bid3 = strtok(line3,",");
				bname3=strtok(NULL, ",");
				bauth3=strtok(NULL, ",");
				bprice3=strtok(NULL, ",");
				book[jj].id = atoi(bid3);
				strcpy(book[jj].name,bname3);
				strcpy(book[jj].author,bauth3);
				book[jj].price = atoi(bprice3);
				jj++;
			}
			fclose(fcs);
			printf("\nEnter the Book ID to delete: ");
			scanf("%d",&delid);
			int foundflag2=0;
			int ss;
			for(ss=0;ss<=jj;ss++){
				if(delid==book[ss].id){
					foundflag2++;
					break;
				}
			}
			if (foundflag2==1){
				printf("\nWriting Changes.. ");
				fcs = fopen("data.csv","w");
				for(int kk=0;kk<jj;kk++){
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
				printf("Book ID not found!");
				printf("\nReturning to Main Menu..");
				sleep(3);
				return 0;
			}

			 
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