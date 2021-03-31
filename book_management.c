/*This is a file for managing books, the acount.dat is for storing the name, username and password line by line. The book.dat is for storing the books 
in the library, with the detail copies, year, title, suthor and id.So all of these file should at least contuin one account(book) in it.*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "book_management.h"
#include "user_management.h"
#define BUF_LEN  128
void Searchforbooks(Book*head)
{
	int a;
	int check;
	char title[60], author[60];
	int year;
	BookArray *find;
	do
	{
		printf("Please choose your option:\n1) search by title\n2) search by author\n3) search by year\n4) Quit\n");
		int check = scanf("%1d", &a);
		getchar();
		if(check == 0)
		{
			printf("Sorry, the option you intered was invalid, please try again.\n");
		}
		else
		{
			int i = a;
			switch(i)
			{
				case 1: printf("Please inter the whole title you want to search: ");
					gets(title);
					find = find_book_by_title(title, head);
					if(find!= NULL)
					{
						printf("Here is your book.%d %s %s %d %d\n", find->array->id, find->array->title, find->array->authors, find->array->year, find->array->copies);
					}
					else
					{
						printf("Sorry, there is no seach book.\n");
					}
					break;
				case 2: printf("Please inter the whole author you want to search: ");
					gets(author);
					find = find_book_by_author(author, head);
					if(find!= NULL)
					{
						while(find->array->next)
						{
							find->array = find->array->next;
							printf("Here is your book.%d %s %s %d %d\n", find->array->id, find->array->title, find->array->authors, find->array->year, find->array->copies);
						}
					}
					else
					{
						printf("Sorry, there is no seach book.\n");
					}
					break;
				case 3: printf("Please inter the whole year you want to search: ");
					scanf("%d", &year);
					find = find_book_by_year(year, head);
					if(find!= NULL)
					{
						while(find->array->next)
						{
							find->array = find->array->next;
							printf("Here is your book.%d %s %s %d %d\n", find->array->id, find->array->title, find->array->authors, find->array->year, find->array->copies);
						}					
					}
					else
					{
						printf("Sorry, there is no seach book.\n");
					}
					break;
				default: break;
			}
			return;
		}
	}while(a != 4);
}


BookArray *find_book_by_title(const char* title, Book* head)
{
	Book* y = head;
		while(y->next)
		{
			y =y->next;
			if(strcmp(y->title, title) == 0)
			{
				BookArray* p = (BookArray*)malloc(sizeof(BookArray));
				p->array = y;
				p-> length = 1;
				return p;
			}
		}
	return NULL;
}

BookArray *find_book_by_author(const char* author, Book* head)
{
	int a = 0;
	Book* y = head;
	BookArray* point= (BookArray*)malloc(sizeof(BookArray));
	Book* newhead = (Book*)malloc(sizeof(Book));
	Book* temp = newhead;
		while(y->next)
		{
			y =y->next;
			if(strcmp(y->authors, author) == 0)
			{
				Book* c = (Book*)malloc(sizeof(Book*));
				c = y;
				c->next = NULL;
				temp->next =c;
				temp = c;
				point->array = newhead;
				a++;
				point->length = a;
			}
		}
		return point;
	
}

BookArray *find_book_by_year(unsigned int year, Book* head)
{
	int a = 0;
	Book* y = head;
	BookArray* point= (BookArray*)malloc(sizeof(BookArray));
	Book* newhead = (Book*)malloc(sizeof(Book));
	Book* temp = newhead;
		while(y->next)
		{
			y =y->next;
			if(y->year = year)
			{
				Book* c = (Book*)malloc(sizeof(Book*));
				c = y;
				c->next = NULL;
				temp->next =c;
				point->array = newhead;
				a++;
				point->length = a;
			}
		}
		return point;
}

int load_books(FILE* file, Book* head)
{
	char acf[BUF_LEN];
	if (!file)
	{
		return 1;
	}
	if (fgets(acf, BUF_LEN, file) == NULL)
	{
		return 1;
	}
	Book* temp = head;
	while(feof(file) == 0)
	{
		//Load book
		Book* c = (Book*)malloc(sizeof(Book));
		c-> title = (char*)malloc(sizeof(char));
		c-> authors = (char*)malloc(sizeof(char));
		sscanf(acf,"%d %s %s %d %d", &c-> id, c-> title, c-> authors, &c-> year, &c-> copies);
		c->next =NULL;
		temp->next = c;
		temp = c;
		fgets(acf, BUF_LEN, file);
	}
	return 0;
}
int store_books(FILE* file, Book* head) 
{
	file = fopen("book.dat", "w");
	if (!file) {
		return 1;
	}
	Book* temp = head;
	while(temp->next)
	{
		temp = temp->next;
		fprintf(file, "%d %s %s %d %d\n", temp->id, temp->title, temp->authors, temp->year, temp->copies);
	}
	fclose(file);
	return 0;
}

int add_book(Book* head, char* x)
{
	int id;
	char tyear[20];
	char tcopies[20];
	Book* temp = head;
	while(temp->next)
	{
		temp = temp->next;
		id = temp->id;
	}
	printf("add\n");
	Book* c = (Book*)malloc(sizeof(Book));
	c-> title = (char*)malloc(sizeof(char));
	c-> authors = (char*)malloc(sizeof(char));
	sscanf(x, "%s %s %s %s", c->title, c-> authors, tyear, tcopies);
	c->year = atoi(tyear);
	c->copies = atoi(tcopies);
	c->id = id+1;
	c->next = NULL;
	temp->next = c;
	return 0;
}

int remove_book(Book* head, char* title)
{
	Book* temp = head->next;
	Book* x = head;
	do
	{
		x = temp;
		temp = temp->next;
	}while(strcmp(temp->title, title) != 0);
	if(strcmp(temp->title, title) == 0)
	{
		x->next = temp->next;
	}
	free(temp);
	x = head->next;
	while(x!=NULL)
	{
		x  = x->next;
	}
	return 0;
}
void Borrow_book(Book* book, User* user)
{
	char acf[128];
	FILE *fp;
	fp = fopen("bbook.dat", "r");
	if (!fp)
	{
		fprintf(stderr, "Error when opening account.dat\n");
		return;
	}
	fclose(fp);
	fp = fopen("bbook.dat", "a");
	fprintf(fp, "%s %s\n",user-> username, book->title);
	fclose(fp);
	
}

void Return_book(BorrowUser* head, User*user)
{
	char acf[128];
	char username[128];
	char title[128];
	BorrowUser* temp = head->next;
	BorrowUser* check= head;
	BorrowUser* check1;
	while(temp!= NULL)
	{
		if(strcmp(user->username, temp->username) == 0)
		{
			check ->next= temp->next;
			check1 = temp;
			
		}
		check = check->next;
		temp=temp->next;
	}
	free(check1);
	FILE *fp;
	fp = fopen("bbook.dat", "w");
	BorrowUser* temp1 = head->next;
	while(temp1!= NULL)
	{
		
		fprintf(fp, "%s %s\n", temp1->username, temp1->title);
		temp1 = temp1->next;
		
	}
	fclose(fp);
	temp = head;
	temp1 = head;
	while(temp!=NULL)
	{
		temp1 = temp;
		temp = temp->next;
		free(temp1);
	}
}
