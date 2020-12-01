#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>


struct Dish
{
	char name[255];
	int price, quantity;
	Dish *prev, *next;
}*headDish, *tailDish, *currDish;

Dish *createDish(char *name, int price, int quantity)
{
  Dish *temp = (Dish*)malloc(sizeof(Dish));
  strcpy(temp->name, name);
  temp->price = price;
  temp->quantity = quantity;
  temp->next = temp->prev = NULL;
  return temp;
}

const int MAX_CUSTOMER = 26;

struct Customer
{
  char name[255];
  Customer *next;
} *headCust[MAX_CUSTOMER], *tailCust[MAX_CUSTOMER];

Customer *createCustomer(char *name)
{
  Customer *temp = (Customer*)malloc(sizeof(Customer));
  strcpy(temp->name, name);
  temp->next = NULL;
  return temp;
}

unsigned long DJB2(char *str)
{
  unsigned long hash = 5381;
  int c;
  while ((c = *str++))
    hash = ((hash << 5) + hash) + c;
  return hash % MAX_CUSTOMER;
}

//2
void pushTail(char *name, int price, int quantity)
{
  Dish *temp = createDish(name, price, quantity);

  if(!headDish)
  { 
    headDish = tailDish = temp;
  } else { 
    tailDish->next = temp; 
    temp->prev = tailDish; 
    tailDish = temp;  
  }
}

int search_Dish(char *name)
{
	currDish = headDish;
	while(currDish)
	{
		if(strcmp(currDish->name, name) == 0)
		{
			return 0;
		}
	}

	currDish = currDish->next;
	return 1;
}

void addDish()
{
	char dishName[255];
	int redo = 0;
	do
	{
		redo = 0;
		printf("Insert the name of the dish[Lowercase letters] ");
		scanf("%[^\n]", &dishName);
		getchar();
		int len = strlen(dishName);
		for(int i = 0; i < len; i++)
		{
			if(dishName[i] >= 'A' && dishName[i] <= 'Z')
			{
				redo = 1;
				break;
			}
		}
	}while(redo = 1);
	
	int price = 0;
	do
	{
		printf("Insert the price of the dish [1000..50000]: ");
		scanf("%d", &price);
		getchar();
	}while(price < 1000 || price > 50000);
	
	int qty = 0;
	do
	{
		printf("Insert the quantity of the dish[1..999]: ");
		scanf("%d", &qty);
		getchar();
		
	}while(qty < 1 || qty > 999);
	pushTail(dishName, price, qty);
	printf("The dish has been added!\n");
	printf("Press enter to continue...\n");
	getchar();
	getchar();
}

//3
void popHead_Dish()
{
  if(headDish && headDish == tailDish) {
    headDish = tailDish = NULL;
    free(headDish);
  } else { 
    Dish *newHead = headDish->next;
    headDish->next = newHead->prev = NULL;
    free(headDish);
    headDish = newHead;
  }
}

void popTail_Dish()
{
  if(headDish && headDish == tailDish) {
    headDish = tailDish = NULL;
    free(headDish);
  } else {
	Dish *newTail = tailDish->prev;
    tailDish->prev = newTail->next = NULL;
    free(tailDish);
    tailDish = newTail;
  }
}

void popMid_Dish(char *name)
{
  if(!headDish) {
    return;
  } else if(strcmp(headDish->name, name) == 0) {
    popHead_Dish();
  } else if(strcmp(tailDish->name, name) == 0) {
    popTail_Dish();
  } else { 
    currDish = headDish;

    while(currDish && currDish->name != name) {
      currDish = currDish->next;
    }
    currDish->prev->next = currDish->next;
    currDish->next->prev = currDish->prev;

    currDish->prev = currDish->next = NULL;
    free(currDish);
  }
}

void removeDish()
{
	char dishName[255];
	printf("           Bude's Menu\n");
	printf("==================================\n");
	printf("No.		Name	Quantity	Price\n");
	printf("1.	telur asin	040			Rp2500\n");
	printf("2.	tempe orek	030       	Rp13000\n");
	printf("3.	buncis		001        	Rp6000\n");
	printf("==================================\n");

int redo = 0;
	do
	{
		redo = 0;
		printf("Insert dish's name to be deleted: ");
		scanf("%[^\n]", &dishName);
		getchar();
		redo = search_Dish(dishName);
	}while(redo == 1);
	popMid_Dish(dishName);
	printf("The dish has been removed!\n");
	printf("Press enter to continue...\n");
	getchar();
	getchar();
}

//4

void insertCustomer(char *str)
{
  int index = DJB2(str);

  if(headCust[index]) { 
    Customer *temp = createCustomer(str);
    tailCust[index]->next = temp;
    tailCust[index] = temp;
  } else { 
    headCust[index] = tailCust[index] = createCustomer(str);
  }
}

void addCustomer()
{
	int redo = 0;
	char name[255];
	do
	{
		redo = 0;
		printf("Insert the customer's name[Without space]: ");
		scanf("%[^\n]", &name);
		getchar();
		int len = strlen(name);
		for(int i = 0; i < len; i++)
		{
			if(name[i] == ' ')
			{
				redo = 1;
				break;
			}
		}
	} while (redo == 1);
	printf("Customer has been added!\n");
	printf("Press enter to continue...\n");
	getchar();
	getchar();
}

//5
int searchHashCustomer(char *str)
{
	for(int i = 0; i < MAX_CUSTOMER; i++)
	{
		if(headCust[i])
		{
			if(strcmp(headCust[i]->name, str) == 0)
			{
				return 1;
			}
			else if(headCust[i]->next)
			{
				while(headCust[i]->next)
				{
					if(strcmp(headCust[i]->next->name, str) == 0)
					{
						return 1;
					}
				}
			}
			
		}
	}
	return 0;
}


void searchCustomer()
{
	int redo = 0;
	char name[255];
	do
	{
		redo = 0;
		printf("Insert the customer's name to be searched: ");
		scanf("%[^\n]", &name);
		getchar();
		int len = strlen(name);
		for(int i = 0; i < len; i++)
		{
			if(name[i] == ' ')
			{
				redo = 1;
				break;
			}
		}
	} while (redo == 1);
	int result = searchHashCustomer(name);
	if(result == 0)
	{
		printf("%s is not present.\n", name);
	}
	else if(result == 1)
	{
		printf("%s is present.\n", name);
	}
	printf("Press enter to continue...\n");
	getchar();
	getchar();
	
	
}
//6
void viewCustomer()
{
  for(int i = 0; i < MAX_CUSTOMER; i++) {
    printf("%d ", i);
    if(headCust[i]) {
      Customer *curr = headCust[i];
      while(curr) {
        printf("%s -> ", curr->name);
        curr = curr->next;
      }
    }
    puts("");
  }
}

void viewWarteg()
{
	printf("Customer's List\n");

	int redo = 0;
	do
	{
		redo = 0;
		viewCustomer();
	} while (redo == 1);
	printf("Customer has been added!\n");
	printf("Press enter to continue...\n");
	getchar();
	getchar();
}

//7
void order()
{
	int redo = 0;
	char name[255];
	int dishAmount;
	char dishName[255];
	int dishQty;
	do
	{
		redo = 0;
		printf("Insert the customer's name: ");
		scanf("%[^\n]", &name);
		getchar();
		printf("Insert the amount of dish: ");
		scanf("%d", &dishAmount);
		getchar();
		int len = strlen(name);
		for(int i = 0; i < len; i++)
		{
			if(name[i] == ' ')
			{
				redo = 1;
				break;
			}
		}
	} while (redo == 1);
	for(int i = 1; i <= dishAmount; i++)
	{
		printf("Insert the dish's name and quantity: ");
		scanf("%[^\n] x%d", &dishName, &dishQty);
	}
	printf("Order success!\n");
	printf("Press enter to continue...\n");
	getchar();
	getchar();
}

//8
void payment()
{

}

//9
void exitWarteg()
{
	printf("Please expand your terminal to full screen!\n");
	printf("Press enter to continue...\n");
	getchar();
	getchar();
}

const char* detectSystem()
{
  #ifdef _WIN32
  return "Windows 32-bit";
  #elif _WIN64
  return "Windows 64-bit";
  #elif __APPLE__ || __MACH__
  return "Mac OSX";
  #elif __linux__
  return "Linux";
  #elif __FreeBSD__
  return "FreeBSD";
  #elif __unix || __unix__
  return "Unix";
  #else
  return "Other";
  #endif
}
//1
void MainMenu()
{
	do
	{
		int mainmenu_select = 1;
	do
	{
		printf("1. Add Dish\n");
		printf("2. Remove Dish\n");
		printf("3. Add Customer\n");
		printf("4. Search Customer\n");
		printf("5. View Warteg\n");
		printf("6. Order\n");
		printf("7. Payment\n");
		printf("8. Exit Warteg\n");
		printf(">>\n");
		scanf("%d", &mainmenu_select);
		if(mainmenu_select = 0)
	{
		return;
	}
	}while(mainmenu_select < 1 || mainmenu_select > 0);
		if(mainmenu_select = 1)
		{
			addDish();
		}
		else if(mainmenu_select = 2)
		{
			removeDish();
		}
		else if(mainmenu_select = 3)
		{
			addCustomer();
		}
		else if(mainmenu_select = 4)
		{
			searchCustomer();
		}
		else if(mainmenu_select = 5)
		{
			viewWarteg();
		}
		else if(mainmenu_select = 6)
		{
			order();
		}
		else if(mainmenu_select = 7)
		{
			payment();
		}
		else if(mainmenu_select = 9)
		{
			exitWarteg();
		}
	}while(1);
}

//main
int main()
{
	printf("%s", detectSystem());

    time_t t;
    time(&t);
    printf("%s", ctime(&t));
    
	MainMenu();
	addDish();
	removeDish();
    return 0;
}
