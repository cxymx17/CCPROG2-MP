/*********************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts learned. I
have constructed the functions and their respective algorithms and corresponding code by myself. The program was run, tested,
and debugged by my own efforts. I further certify that I have not copied in part or whole or otherwise plagiarized the work of other
students and/or persons.
CYMBELINE ANNE B. LIGNES, DLSU ID# 12107892
RALPH CHRISTIAN A. TUANGCO, DLSU ID# 12044008
*********************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef char str10[10]; 
typedef char str20[20];
typedef char str15[15];
typedef char str30[30];

struct userTag {
		int userID;
		str10 password;
		str20 name;
		str30 address;
		int contact;       
	};

typedef struct userTag userTag;
	
struct itemTag {
	int productID;
	str20 itemName;
	str15 category;
	str30 description;
	int quantity;
	int price;  
	int sellerID;        
};

typedef struct itemTag itemTag;

struct transactionTag {
	str10 date;
	itemTag setItem[5];
	int buyerID;
	int tranSellerID;
	int total;     
};

typedef struct transactionTag transactionTag;

/*
	Purpose: display the welcome banner
*/
	void intro(){
	printf("\n");
	printf("_________________________________\n\n");
	printf("|   WELCOME TO SHOPPING APP     |\n");
	printf("_________________________________\n\n");
	}

/*
	Purpose: display the main menu
*/
	void mainMenu(){
	printf("\t     MAIN MENU\n\n");
	printf("     1 - Register as a User\n     2 - User Menu\n     3 - Admin Menu\n     4 - Exit\n\n");
	}

/*
	Purpose: append user text file to add the newly registered user
	@param : nMenu the condition of the selected menu
	@param : users is the structure that will contain the data of the users
	@param : ft is the flag when appending a new user
	@param : *fpUser is the User and file name that will be read, appended, and closed once nMenu is set to terminate
	@param : *fpItem is the Item and file name that will be read and closed once nMenu is set to terminate
	Pre-condition: the parameter is a valid structure, string, file pointer, and integer.
*/
	void writeTxt(int nMenu, userTag users, int ft, FILE *fpUser , FILE *fpItem){
	//scans the "Users.txt" file
	if (ft == 1){
		fclose(fpUser);
		fpUser = fopen("Users.txt", "a");
		fprintf(fpUser, "%d %s \n%s\n%s\n%d\n\n", users.userID, users.password, users.name, users.address, users.contact);
		ft = 0;
	}
	//closes "Users.txt" and "Items.txt" files	
		if (nMenu == 4){
			fclose(fpUser);
			fclose(fpItem);
		}
	}
	
/*
	Purpose: checks if the userID already exists in the users data
	Returns: either the (a) userID is invalid and will return a negative boolean value or
	         (b) the userID is valid and will return a positive boolean value
	@param : tempUserID is the integer that stores the desired userID to be added if valid
	@param : users is the structure array that will contain the data of the users
	@param : userCnt monitors the count of users added in the array
	Pre-condition: the parameter is a valid structure array and integer.
*/
	int checkUserID(int tempUserID, userTag users[], int userCnt){
		int nDup = 0;
		
		//scans all users and checks any duplicate userID
		for (int i = 0; i < 100; i++){
			if (tempUserID == users[i].userID)
			nDup++;
			}
			
			
			if (nDup){	//if nDup is true(positive int) then the program will keep asking for a userID
			printf("\n\tuserID already registered...\n\n");
				return 1;
			}
			else	//if nDup is false(nonpositive int) then the program will store the given userID
			users[userCnt].userID = tempUserID;
				return 0;
	}

/*
	Purpose: checks if the userID is registered in the users data and if it does it will then check if the given password matches
	Returns: either the (a) userID is not registered and will return a negative boolean value or
	         (b) will return a positive boolean value when the userID is registered and password matches
	@param : users is the structure array that will contain the data of the users
	@param : tempUserID is the string that holds the userID that is given by the user.
	@param : tempPass is the string that holds the password that is given by the user.
	Pre-condition: the parameter is a valid structure array and string.
*/
	int logIn(userTag users[],int tempUserID, str10 tempPass){
		int nCon = 0;
		
		//returns a positive int if the given tempUserID and tempPass is stored in users[]
		for (int i = 0; i < 100; i++){
			if (tempUserID == users[i].userID)
					if (!(strcmp(tempPass, users[i].password)))
					nCon = 1;
			}
			
		return nCon;
	}

/*
	Purpose: collects information to be added in the user array
	@param : nMenu the condition of the selected menu
	@param : users is the structure array that will contain the data of the users
	@param : userCnt monitors the count of users added in the array
	@param : *fpUser is the User and file name that will be essential when calling the writeTxt function
	@param : *fpItem is the Item and file name that will be essential when calling the writeTxt function
	Pre-condition: the parameters contain valid values
*/	
	void regUser(int *nMenu, userTag users[], int *userCnt, FILE *fpUser , FILE *fpItem){
		*nMenu = 0;
		int tempUserID, ft = 1;
		
		printf("\n\n\t     REGISTER USER MENU\n\n");
		
		do {	//asks for userID then calls checkUserID() to verify if the given userID is valid
			printf("Enter your userID: ");
			scanf("%d", &tempUserID);
		}while(checkUserID(tempUserID, users, *userCnt));
				//proceeds to ask for the users' information then stores it in the users[]
		printf("Enter your password: ");
		scanf("%s", users[*userCnt].password);
		printf("Enter your name: ");
		scanf(" %[^\n]s", users[*userCnt].name);
		printf("Enter your address: ");
		scanf(" %[^\n]s", users[*userCnt].address);
		printf("Enter your contact: ");
		scanf("%d", &users[*userCnt].contact);
		
		//adds the new users' information to the "Users.txt" file
		writeTxt(*nMenu, users[*userCnt], ft, fpUser, fpItem);
		
		printf("\n\tRedirecting back to Main Menu...\n\n");
	}

/*
	Purpose: checks if the productID is registered in the items data
	Returns: either the (a) productID is not found and will return a negative boolean value or
	         (b) the productID is registered and will return a positive boolean value
	@param : tempProductID is the string that holds the productID that is given by the user.
	@param : *fpItem is the Item and file name that will be scanned
	Pre-condition: the parameters contain valid values
*/	
	int checkProductID(int tempProductID,  FILE *fpItem){
		itemTag tempItem;
		int nFlag = 0;
		
		fclose(fpItem);
		fpItem = fopen("Items.txt", "r");
		
		// scans "Items.txt" file and checks if tempProductID is already stored
		while(fscanf(fpItem, "%d %d", &tempItem.productID, &tempItem.sellerID) == 2){
			fscanf(fpItem, " %[^\n]s", tempItem.itemName);
			fscanf(fpItem, " %[^\n]s", tempItem.category);
			fscanf(fpItem, " %[^\n]s", tempItem.description);
			fscanf(fpItem, "%d %d", &tempItem.quantity, &tempItem.price);
			if(tempProductID == tempItem.productID) //if tempProductID exist then nFlag is set to true
				nFlag = 1;	
		}
			
			if (nFlag)
				printf("\n\tproductID already registered...\n\n");
			
			return nFlag;
	}

/*
	Purpose: collects information to be added in the item array
	@param : items is the structure array that will contain the data of the items
	@param : *fpItem is the Item and file name that will be appended
	@param : sellerID stores the sellerID for the item
	@param : *itemCnt monitors the count of users added in the array
	Pre-condition: the parameters contain valid values
*/		
	void newItem(itemTag items[], FILE *fpItem, int sellerID, int *itemCnt){
		int tempProductID;
		
		printf("\n\n\t     ADD NEW ITEM\n\n");
		do {	//asks for productID then calls checkProductID() to verify if the given productID is valid
			printf("Enter the ProductID: ");
			scanf("%d", &tempProductID);
		} while(checkProductID(tempProductID, fpItem));
				//proceeds to ask for the item information then stores it in the items[]
		items[*itemCnt].productID = tempProductID;
		printf("Enter the Item Name: ");
		scanf(" %[^\n]s", items[*itemCnt].itemName);
		printf("Enter the Item Category: ");
		scanf(" %[^\n]s", items[*itemCnt].category);
		printf("Enter Item Description: ");
		scanf(" %[^\n]s", items[*itemCnt].description);
		printf("Enter Item Quantity: ");
		scanf("%d", &items[*itemCnt].quantity);
		printf("Enter Item Price: ");
		scanf("%d", &items[*itemCnt].price);
		
		//adds the item information to the "Items.txt" file
		fclose(fpItem);
		fpItem = fopen("Items.txt", "a");
		fprintf(fpItem, "%d %d\n%s\n%s\n%s\n%d %d\n\n", items[*itemCnt].productID, sellerID, items[*itemCnt].itemName, items[*itemCnt].category, items[*itemCnt].description, items[*itemCnt].quantity, items[*itemCnt].price);
		
		printf("\n\tRedirecting back to Main Menu...\n\n");
	}

/*
	Purpose: displays the products of the seller
	@param : *fpItem is the Item and file name that will be scanned
	@param : sellerID stores the sellerID for the item
	Pre-condition: the parameters contain valid values
*/
	void myProducts(itemTag items[], int sellerID, int max){
	itemTag nSet, tempOrder[max];
	int j = 0;	
		
		printf("\n\n\t\t\t\t\t     MY PRODUCTS\n\n");
		printf("  Product ID  ||      Item Name      ||  Item Category  ||  Unit Price  || Unit Quantity\n\n");
		
		//copies all items to tempOrder[]
		for (int i = 0; i < max; i++){
			tempOrder[j] = items[i];
			j++;
		}
		
		//sort the productID to increasing order
		for (int i = 0; i < j; ++i) {
            for (int l = i + 1; l < j; ++l) 
                if (tempOrder[i].productID > tempOrder[l].productID) 
                {
                    nSet =  tempOrder[i];
                    tempOrder[i] = tempOrder[l];
                    tempOrder[l] = nSet;
                }
		}

		//prints products in increasing order
		for (int i = 0; i < j; i++)
			printf("%14d  %-21s  %-17s  %14d  %14d\n",  tempOrder[i].productID, tempOrder[i].itemName, tempOrder[i].category, tempOrder[i].price, tempOrder[i].quantity);
			
	}

/*
	Purpose: menu to edit the products of the seller
	@param : items contains the item structure
	Pre-condition: the parameters contain valid values
*/	
	void editMenu(itemTag *items){
		int nOpt;
		itemTag tempItem;
		
		do{	
			printf("\n\n\t     EDIT MENU\n\n");	
			printf("\n\n     1 - Replenish\n     2 - Change Price\n     3 - Change Item Name\n     4 - Change Category\n     5 - Change Description\n     6 - Finish Editing\n\n");
			printf("Select Option: ");
			scanf("%d", &nOpt);
		
			switch(nOpt){
			case 1: {	//asks for the desired quantity to be added then updates the item quantity
					printf("Enter the quantity that will be added: ");
					scanf("%d", &tempItem.quantity);
					items->quantity = items->quantity + tempItem.quantity;
					}; break;
			case 2: {	//asks for the desired price to be changed then updates the item price
					printf("Enter the New Unit Price: ");
					scanf("%d", &tempItem.price);
					items->price = tempItem.price;
					}; break;
			case 3: {	//asks for the desired name to be changed then updates the item name
					printf("Enter the New Unit Name: ");
					scanf(" %[^\n]s", tempItem.itemName);
					strcpy(items->itemName, tempItem.itemName);
					}; break;
			case 4: {	//asks for the desired category to be changed then updates the item category
					printf("Enter the New Unit Category: ");
					scanf("  %[^\n]s", tempItem.category);
					strcpy(items->category, tempItem.category);
					}; break;
			case 5: {	//asks for the desired description to be changed then updates the item description
					printf("Enter the New Unit Description: ");
					scanf("  %[^\n]s", tempItem.description);
					strcpy(items->description, tempItem.description);
					}; break;
            case 6: printf("\n"); break;
			default: printf("\nINVALID INPUT\n\n"); break;
			}
		
		}while(nOpt != 6);
	}

/*
	Purpose: checks if the productID exists in the items array
	Returns: either the (a) productID is not registered and will return a negative boolean value or
	         (b) will return a positive boolean value when the productID is found
	@param : items contains the item structure array
	@param : tempProdID contains the productID that is given by the user
	Pre-condition: the parameters contain valid values
*/	
	int checkProductIDarray(itemTag items[], int tempProdID, int *index){
		int nFlag;

		//scans all items and checks any duplicate productID
		for(int i = 0; i < 21; i++){
			if(tempProdID == items[i].productID){
				nFlag = 1;
				*index = i;}
		}
		
		if(!(nFlag))	//if nFlag is NOT true(positive int) then the program redirects back to main menu
			printf("\n\tINVALID PRODUCTID\n\tRedirecting back to Main Menu...\n\n");
		
		return nFlag;
	}

/*
	Purpose: menu that decides if the given productID will proceed to editMenu() or not
	@param : items contains the item structure array
	@param : *fpItem is the Item and file name that will be essential when calling the checkProductIDarray()
	@param : sellerID stores the sellerID for the item
	@param : *itemCnt monitors the count of users added in the array
	Pre-condition: the parameters contain valid values
*/		
	void editStock(itemTag items[], FILE *fpItem, int sellerID, int *itemCnt){
		int tempProdID, nCon = 0, index;
		
		printf("\n\n\t     EDIT STOCK\n\n");
		printf("\n\n\t     MY PRODUCTS\n\n");
		
		myProducts(items, sellerID, *itemCnt);
		
		printf("Enter ProductID: ");
		scanf("%d", &tempProdID);
		
			//checks if product exist in the items[]
		nCon = checkProductIDarray(items, tempProdID, &index);

		if (nCon) //if product exist, it proceeds to the editMenu()
			editMenu(&items[index]);
			
		fclose(fpItem);
		fpItem = fopen("Items.txt", "w");
		
		for(int i = 0; i < *itemCnt; i++)	//updates the "Items.txt" file
		fprintf(fpItem, "%d %d\n%s\n%s\n%s\n%d %d\n\n", items[i].productID, sellerID, items[i].itemName, items[i].category, items[i].description, items[i].quantity, items[i].price);
	}

/*
	Purpose: prints items array to "Items.txt" file
	@param : *fpItem is the Item and file name that will be read and closed once nMenu is set to terminate
	@param : max is the count of items added in the array
	@param : items contains the item structure array
	@param : sellerID stores the sellerID for the item
	Pre-condition: the parameters contain valid values
*/
	void printItems(FILE *fpItem, int max, itemTag items[],int sellerID){
	
		fclose(fpItem);
		fpItem = fopen("Items.txt", "w");

		for (int i = 0; i < max; i++)	//prints items[] to "Items.txt" file
		fprintf(fpItem, "%d %d\n%s\n%s\n%s\n%d %d\n\n", items[i].productID, sellerID, items[i].itemName, items[i].category, items[i].description, items[i].quantity, items[i].price);
}
	
/*
	Purpose: displays the low stock products of the seller
	@param : *fpItem is the Item and file name that will be scanned
	@param : sellerID stores the sellerID for the item
	Pre-condition: the parameters contain valid values
*/	
	void lowStock(FILE *fpItem, itemTag items[], int sellerID, int max){
		itemTag tempItem;
		char cCon = 'N';
		
		printItems(fpItem, max, items, sellerID);

		printf("\n\n\t     LOW STOCK\n\n");
		
		fclose(fpItem);
		fpItem = fopen("Items.txt", "r");
		
		//scans "Items.txt" file then checks for items with stocks lower than 5 to display
		while(fscanf(fpItem, "%d %d", &tempItem.productID, &tempItem.sellerID) == 2){
		fscanf(fpItem, " %[^\n]s", tempItem.itemName);
		fscanf(fpItem, " %[^\n]s", tempItem.category);
		fscanf(fpItem, " %[^\n]s", tempItem.description);
		fscanf(fpItem, "%d %d", &tempItem.quantity, &tempItem.price);
			if(sellerID == tempItem.sellerID)
				if(tempItem.quantity < 5 && cCon == 'N'){
					printf("\nProduct ID: %d\t Item Name: %s\t  Item Category: %s\t Unit Price: %d\t Unit Quantity: %d\n",  tempItem.productID, tempItem.itemName, tempItem.category, tempItem.price, tempItem.quantity);
					printf("\n\nPress [N] to see next product \nPress [X] to exit: ");
					scanf(" %c", &cCon);
					}
		}

	}
	
/*
	Purpose: scans the items text file
	@param : *fpItem is the Item and file name that will be scanned
	@param : items is the structure array that stores all items
	@param : sellerID stores the sellerID for the item
	@param : *itemCnt monitors the count of users added in the array
	Pre-condition: the parameters contain valid values
*/		
	void scanItems( FILE *fpItem, itemTag items[],int sellerID, int *itemCnt){
		itemTag tempItem;
		*itemCnt = 0;
		int nLimit;
		
		fclose(fpItem);
		fpItem = fopen("Items.txt", "r");
		
		//scans "Items.txt" file and checks for the sellers items then stores it to items[]
		while(fscanf(fpItem, "%d %d", &tempItem.productID, &tempItem.sellerID) == 2){
			fscanf(fpItem, " %[^\n]s", tempItem.itemName);
			fscanf(fpItem, " %[^\n]s", tempItem.category);
			fscanf(fpItem, " %[^\n]s", tempItem.description);
			fscanf(fpItem, "%d %d", &tempItem.quantity, &tempItem.price);
			if(sellerID == tempItem.sellerID){
				items[*itemCnt].productID =  tempItem.productID;
				items[*itemCnt].sellerID = tempItem.sellerID;
				strcpy(items[*itemCnt].itemName, tempItem.itemName);
				strcpy(items[*itemCnt].category, tempItem.category);
				strcpy(items[*itemCnt].description, tempItem.description);
				items[*itemCnt].quantity =  tempItem.quantity;
				items[*itemCnt].price = tempItem.price;
				*itemCnt = *itemCnt + 1;
				}
		}

		nLimit = *itemCnt;
		
		// if the scanned items is less than 20, the following productID's are set to 0 to prevent garbage values
		while(nLimit < 21){
			items[nLimit].productID = 0;
			nLimit++;
		}
	}

/*
	Purpose: counts the sellers items in the "Items.txt" file
	@param : items contains the item structure array
	@param : sellerID stores the sellerID for the item
	@param : max is the count of items added in the array
	Pre-condition: the parameters contain valid values
*/
	int checkItems(itemTag items[], int sellerID, int max){
		int nCnt = 0;
		
			//counts the sellers items in the "Items.txt" file
		for(int i = 0; i < max; i++)
			if(sellerID == items[i].sellerID)
				nCnt++;
		
			//if sellers' items is less than 20 then it returns a positive boolean value
		if (nCnt < 20)
			return 1;
		else
			return 0;
	}

/*
	Purpose: displays the sell menu
	@param : *nMenu the condition of the selected menu
	@param : sellerID stores the sellerID for the item
	@param : transactions[] contains all the transaction data
	@param : *fpUser is the User and file name that will be essential when calling functions
	@param : *fpItem is the Item and file name that will be essential when calling functions
	Pre-condition: the parameters contain valid values
*/	
	void sellMenu(int *nMenu, int sellerID, transactionTag transactions[], FILE *fpUser , FILE *fpItem, int *itemCnt){
		itemTag items[21];
		int nOpt;
		
		*nMenu = 0;
		do{
			scanItems( fpItem, items, sellerID, itemCnt);
			printf("\n\n\t     SELL MENU\n\n");	
			printf("\n\n     1 - Add New Item\n     2 - Edit Stock\n     3 - Show My Products\n     4 - Show My Low Stock Products\n     5 - Exit Sell Menu\n\n");
			printf("Select Option: ");
			scanf("%d", &nOpt);
			switch(nOpt){
							//case 1: calls checkItems() to check if maximum sell limit is reached
				case 1: if(checkItems(items, sellerID, *itemCnt))
							newItem(items, fpItem, sellerID, itemCnt);	//newItem() is called when sellers items is less than the limit
						else
							printf("\n\tMaximum Sell Item Limit Reached\n\n");
						; 
						break;
				case 2: editStock(items, fpItem, sellerID, itemCnt); break;
				case 3: myProducts(items, sellerID, *itemCnt); break;
				case 4: lowStock(fpItem, items, sellerID, *itemCnt); break;
				case 5: printf ("\n"); break;
				default: printf("\nINVALID INPUT\n\n"); break;
			}
		}while(nOpt != 5);	
	}

/*
	Purpose: scans all items in the Items.txt
	@param : itemArray[] is the array that contains all items available to be bought
	@param : *fpItem is the Item and file name that will be scanned
	@param : max monitors the count of items added in the cart
	Pre-condition: the parameters contain valid values
*/	
	void scanBuyItems(itemTag itemArray[],FILE *fpItem, int max){
		int i = 0;
		itemTag tempItem;
		fclose(fpItem);
		fpItem = fopen("Items.txt", "r");
	
		//scans "Items.txt" file and checks for the sellers items then stores it to items[]
		while(fscanf(fpItem, "%d %d", &tempItem.productID, &tempItem.sellerID) == 2){
		fscanf(fpItem, " %[^\n]s", tempItem.itemName);
		fscanf(fpItem, " %[^\n]s", tempItem.category);
		fscanf(fpItem, " %[^\n]s", tempItem.description);
		fscanf(fpItem, "%d %d", &tempItem.quantity, &tempItem.price);
			itemArray[i].productID = tempItem.productID;
			itemArray[i].sellerID = tempItem.sellerID;
			strcpy(itemArray[i].itemName, tempItem.itemName);
			strcpy(itemArray[i].category, tempItem.category);
			strcpy(itemArray[i].description, tempItem.description);
			itemArray[i].quantity = tempItem.quantity;
			itemArray[i].price = tempItem.price;
			i = i + 1;
		}
	
	}

/*
	Purpose: display all products
	@param : items[] is the array that contains all items available to be bought
	@param : max is the count of items added in the array
	@param : userCnt is the count of users registered in the array
	Pre-condition: the parameters contain valid values
*/		
	void allProducts(itemTag items[], int max, int userCnt){
		int nSet, tempMax, arrayID[max];
		FILE *fpItem;
        char cCon = 'N';
		
		fpItem = fopen("Items.txt", "r");
		
		scanBuyItems(items, fpItem, max);
		
		fclose(fpItem);
		
		tempMax = max;
		
		printf("\n\n\t\t\t     SHOW PRODUCTS\n\n");
		
		//stores all items.sellerID
		for(int i = 0; i < max; i++)
			arrayID[i] = items[i].sellerID;
		
		//remove duplicates in arrayID[]
		for(int i = 0; i < max; i++)
      		for(int j = i + 1; j < max; j++)
         		if(arrayID[i] == arrayID[j]){
            		for(int k = j; k < max; k++){
               			arrayID[k] = arrayID[k+1];
            		}
            		j--;
            		max--;
        		}
		
		//set arrayID[] in increasing order
		for (int i = 0; i < max; ++i) {
            for (int l = i + 1; l < max; ++l)
                if (arrayID[i] > arrayID[l]) 
                {
                    nSet =  arrayID[i];
                    arrayID[i] = arrayID[l];
                    arrayID[l] = nSet;
                }
		}

		
		for(int i = 0; i < max; i++)
			if(cCon !='X'){		//display products by sellers items
				printf("\n\n\t\t\tSELLER %d PRODUCT/S\n", arrayID[i]);
				printf("  Product ID  ||      Item Name      ||  Item Category  ||  Unit Price  || Unit Quantity\n\n");
				for(int l = 0; l < tempMax; l++)
					if(arrayID[i] == items[l].sellerID)
						printf("%14d  %-21s  %-17s  %14d  %14d\n",  items[l].productID, items[l].itemName, items[l].category, items[l].price, items[l].quantity);
				printf("\n\nPress [N] to see the next seller's product/s \nPress [X] to exit: ");
				scanf(" %c", &cCon);
			}
	}

/*
	Purpose: display all products by a specifAic seller
	@param : items[] is the array that contains all items available to be bought
	@param : max is the count of items added in the array
	Pre-condition: the parameters contain valid values
*/			
	void specificSeller(itemTag items[], int max){
		int tempSeller;
		FILE *fpItem;
		
		fpItem = fopen("Items.txt", "r");
		
		scanBuyItems(items, fpItem, max);
		
		fclose(fpItem);
		
		printf("Enter Specific Seller: ");
		scanf("%d", &tempSeller);
		
		printf("\n\n\t\t\t\t\t     SELLER %d PRODUCTS\n\n", tempSeller);
		printf("  Product ID  ||      Item Name      ||  Item Category  ||  Unit Price  || Unit Quantity\n\n");
		
		for(int i = 0; i < max; i++)
			if (tempSeller == items[i].sellerID)	//display products by the given sellerID
				printf("%14d  %-21s  %-17s  %14d  %14d\n",  items[i].productID, items[i].itemName, items[i].category, items[i].price, items[i].quantity);	
	}

/*
	Purpose: display all products by a specific category
	@param : items[] is the array that contains all items available to be bought
	@param : max is the count of items added in the array
	Pre-condition: the parameters contain valid values
*/		
	void specificCategory(itemTag items[], int max){
		str15 tempCat;
		char cCon = 'N';
		FILE *fpItem;
		
		fpItem = fopen("Items.txt", "r");
		
		scanBuyItems(items, fpItem, max);
		
		fclose(fpItem);
		
		printf("Enter Specific Category: ");
		scanf("%s", tempCat);
		
		printf("\n\n\t     %s PRODUCTS\n\n", tempCat);
		
		for(int i = 0; i < max; i++)
			if(!(strcmp(tempCat, items[i].category)) && cCon == 'N'){	//display products by the given category
				printf("Product ID: %d\t Item Name: %s\t  Item Category: %s\t Unit Price: %d\t Unit Quantity: %d\n",  items[i].productID, items[i].itemName, items[i].category, items[i].price, items[i].quantity);
				printf("\n\nPress [N] to see next product \nPress [X] to exit: ");
				scanf(" %c", &cCon);
				}
	}

/*
	Purpose: display all products by a specific name	
	@param : items[] is the array that contains all items available to be bought
	@param : max is the count of items added in the array
	Pre-condition: the parameters contain valid values
*/	
	void specificName(itemTag items[], int max){
		str20 tempName;
		char cCon = 'N';
		FILE *fpItem;
		
		fpItem = fopen("Items.txt", "r");
		
		scanBuyItems(items, fpItem, max);
		
		fclose(fpItem);
		
		
		printf("Enter Specific Name: ");
		scanf("%s", tempName);
		
		printf("\n\n\t     %s PRODUCT/s\n\n", tempName);
		
		for(int i = 0; i < max; i++)
			if(strstr(items[i].itemName, tempName) != NULL && cCon == 'N'){	//display products by the given name
				printf("Product ID: %d\t Item Name: %s\t  Item Category: %s\t Unit Price: %d\t Unit Quantity: %d\n",  items[i].productID, items[i].itemName, items[i].category, items[i].price, items[i].quantity);
				printf("\n\nPress [N] to see next product \nPress [X] to exit: ");
				scanf(" %c", &cCon);
				}
	
	}

/*
	Purpose: checks if the given sellerID is stored in the cart[] and removes it from the array
	@param : cart[] is the structure array that contains items
	@param : max is the count of items stored in the array to avoid garbage values
	@param : tempSellerID contains the productID that is given by the user
	Pre-condition: the parameters contain valid values
*/	
	void checkCart(itemTag cart[],int *max, int tempSellerID){
		int indexCnt = 0, nIndexArr[*max], nIndex, nCon = 0;

		for(int i = 0; i < *max; i++)	//stores index where the given sellerID is found in the cart[]
			if (cart[i].sellerID == tempSellerID){
				nIndexArr[indexCnt] = i;
				indexCnt++;
				nCon++;
			}
		
		if(nCon){	//removes the sellers items from the cart[]
			for(int i = 0; i < indexCnt; i++){
				if( i > 0)
					nIndex = nIndexArr[i] - 1;
				else
					nIndex = nIndexArr[i];
				for(int j = nIndex; j < *max; j++){
					cart[j] =  cart[j+1];	
				}
			}
			*max = *max - indexCnt;
		}
		
	}

/*
	Purpose: removes specific product stored in the cart[]
	@param : cart[] is the structure array that contains items
	@param : max is the count of items stored in the cart
	@param : tempProductID contains the productID that is given by the user
	Pre-condition: the parameters contain valid values
*/	
	void removeProductID(itemTag cart[],int *max, int tempProductID){
		int nCon = 0, nIndex;
		
		for(int i = 0; i < *max; i++)	//stores index where the given productID is found in the cart[]
			if (cart[i].productID == tempProductID){
				nIndex = i;
				nCon = 1;
				}
		
		if(nCon){	//removes the product from the cart[]
			for(int i = nIndex; i < *max; i++){
				cart[i] =  cart[i+1];
		}
		
			*max = *max - 1;
		}
	}

/*
	Purpose: display all items stored in the cart[]
	@param : cart[] is the structure array that contains items
	@param : max is the count of items stored in the cart
	Pre-condition: the parameters contain valid values
*/	
	void displayCart(itemTag cart[],int max){

		printf("\n\n\t\t\t\t\t\t     CART ITEM/s\n\n");
		printf("  Product ID  ||      Item Name      ||  Item Category  ||  Unit Price  || Unit Quantity\n\n");
		
		for(int i = 0; i < max; i++)
			printf("%14d  %21s  %17s  %14d  %14d\n",  cart[i].productID, cart[i].itemName, cart[i].category, cart[i].price, cart[i].quantity);	
		
	}

/*
	Purpose: displays the edit cart menu and manages the cart
	@param : cart[] is the structure array that contains items
	@param : max is the count of items stored in the cart
	Pre-condition: the parameters contain valid values
*/		
	void editCart(itemTag cart[], int *max){
		int tempProductID, tempSellerID, nOpt, nQuan;
		
		do{
			displayCart(cart, *max);
			printf("\n\n\t     EDIT CART MENU\n\n");	
			printf("\n\n     1 - Remove All Items from Seller\n     2 - Remove Specific Item\n     3 - Edit Quantity\n     4 - Finish Edit Cart\n\n");
			printf("Select Option: ");
			scanf("%d", &nOpt);
			
			switch(nOpt){
				case 1: { 	printf("Enter SellerID: ");
							scanf("%d", &tempSellerID);
							checkCart(cart, max, tempSellerID);
							printf("\nCart is updated\n");
						}; break;
				case 2: { 	printf("Enter ProductID: ");
							scanf("%d", &tempProductID);
							removeProductID(cart, max, tempProductID);
							printf("\nCart is updated\n");
						}; break;
				case 3: {	printf("Enter ProductID: ");
							scanf("%d", &tempProductID);
							printf("Enter New Quantity: ");
							scanf("%d", &nQuan);
							
							for(int i = 0; i < *max; i++)
								if(tempProductID == cart[i].productID)
									cart[i].quantity = nQuan;
						}; break;
				case 4: printf ("\n"); break;
				default: printf("\nINVALID INPUT\n\n"); break;
			}
		
		}while(nOpt != 4);	
	}

/*
	Purpose: returns the count of items in the "Items.txt" file
	@param : *fpItem is the Item and file name that will be read and closed once nMenu is set to terminate
	Pre-condition: the parameters contain valid values
*/		
	int countBuyItems(FILE *fpItem){
		int nCnt = 0;
		itemTag tempItem;
		fclose(fpItem);
		fpItem = fopen("Items.txt", "r");
		
			// scans "Items.txt" and increments the count of the items
		while(fscanf(fpItem, "%d %d", &tempItem.productID, &tempItem.sellerID) == 2){
			fscanf(fpItem, " %[^\n]s", tempItem.itemName);
			fscanf(fpItem, " %[^\n]s", tempItem.category);
			fscanf(fpItem, " %[^\n]s", tempItem.description);
			fscanf(fpItem, "%d %d", &tempItem.quantity, &tempItem.price);
			nCnt++;
		}
		
		return nCnt;
	}
	

/*
	Purpose: checks out all items in the cart and displays transaction receipt/s
	@param : cart[] is the structure array that contains items
	@param : *max is the count of items stored in the cart
	@param : transaction[] is the structure array that contains transactions
	@param : buyerID stores the buyerID
	@param : strDate stores the date of the transaction
	@param : userCnt monitors the count of users added in the array
	@param : users[] is the structure array that contains users
	Pre-condition: the parameters contain valid values
*/		
	void checkOutAll(itemTag cart[],int  *max, transactionTag transaction[], int buyerID, str10 strDate, int userCnt, userTag users[]){
		int tempArrayID[*max], arrayID[*max], tempMax, l = 0, tCtr = 0, m = 0, nFlag = 0, nCon = 1, nLimit = 0, nIndex = 0, limitSeller, nTotal = 0, itemCnt;
		str20 sellerName;
		FILE *fpTransaction, *fpItem;
		
		fpItem = fopen("Items.txt", "r");
		
		itemCnt = countBuyItems(fpItem);
		
		itemTag items[itemCnt];

		scanBuyItems(items,	fpItem, itemCnt);
		
		
		tempMax = *max;
		
			//stores all cart.sellerID to arrayID[] and tempArrayID[]
		for(int i = 0; i < tempMax; i++){
			arrayID[i] = cart[i].sellerID;
			tempArrayID[i] = cart[i].sellerID;
		}
				
			//remove duplicates in arrayID[]
		for(int i = 0; i < tempMax; i++)
      		for(int j = i + 1; j < tempMax; j++)
         		if(arrayID[i] == arrayID[j]){
            		for(int k = j; k < tempMax; k++){
               			arrayID[k] = arrayID[k+1];
            		}
            		j--;
            		tempMax--;
        		}
        		
	
			//counts if cart has items greater than 5 with the same sellerID
        for(int i = 0; i < tempMax; i++){
        	nLimit = 0;
        	for(int k = 0; k < *max; k++){
        		if (arrayID[i] == tempArrayID[k]){
					nLimit++;
				}
	        	if (nLimit > 4){
			        nFlag = 1;
			        nIndex = i;
			        nLimit = 0;
		        }
        	}
        }
        
        	//assigns sellerID to limitSeller
        limitSeller = arrayID[nIndex];

        if(nFlag){
       		for(int k = 0; k < *max; k++){
       			if (limitSeller == cart[k].sellerID){ //first 5 items of the seller is stored in the first transaction
					if(l >= 5){
						strcpy(transaction[1].date, strDate);
						transaction[1].setItem[m] = cart[k];
						transaction[1].buyerID = buyerID;
						transaction[1].tranSellerID = cart[k].sellerID;
						m++;
						tCtr++;
					}
					else{	//succeeding items is stored in the second transaction
						strcpy(transaction[0].date, strDate);
						transaction[0].setItem[l] = cart[k];
						transaction[0].buyerID = buyerID;
						transaction[0].tranSellerID = cart[k].sellerID;
					}
					l++;
				}
			}
				
			tCtr++;

			for(int i = 0; i < tempMax; i++)	//takes limitSeller index in the arrayID[]
				if (arrayID[i] == limitSeller){
					nIndex = i;
					nCon = 1;
				}

			if(nCon){	//removes limitSeller in the arrayID[]
				for(int i = nIndex; i < tempMax; i++){
					arrayID[i] =  arrayID[i+1];
				}
			}
		
			tempMax = tempMax - 1;
			
			while (m < 5){	//if not all slots of transaction.items is filled, productID's and prices are set to 0 to avoid garbage values
				transaction[1].setItem[m].quantity = 0;
				transaction[tCtr].setItem[l].price = 0;
				m++;
				}
		}
			l = 0;
		

			//succeeding items from the cart with items of the same seller is less than 5 are stored with their own transaction structures
		for(int i = 0; i < tempMax; i++){
			for(int k = 0; k < *max; k++)
				if (arrayID[i] == cart[k].sellerID){
					strcpy(transaction[tCtr].date, strDate);
					transaction[tCtr].setItem[l] = cart[k];
					transaction[tCtr].buyerID = buyerID;
					transaction[tCtr].tranSellerID = cart[k].sellerID;
					l++;
				}	
			while (l < 5){
				transaction[tCtr].setItem[l].quantity = 0;
				transaction[tCtr].setItem[l].price = 0;
				l++;
			}
			l = 0;
			tCtr++;
		}
	
		for (int i = 0; i < tCtr; i++){	//display transactions
			printf("\n\n\t\t\t\t     %d TRANSACTION RECEIPT \n\n", transaction[i].setItem[0].sellerID);
			printf("\tUnit Quantity ||  Product ID  ||      Item Name      ||  Unit Price  ||  Total Price \n\n");
			for (int k = 0; k < 5; k++){
				if(transaction[i].setItem[k].quantity != 0)
					printf("\t%14d  %14d  %-21s  %14d  %14d  \n",   transaction[i].setItem[k].quantity, transaction[i].setItem[k].productID, transaction[i].setItem[k].itemName,  transaction[i].setItem[k].price, transaction[i].setItem[k].quantity*transaction[i].setItem[k].price);
				nTotal = nTotal + transaction[i].setItem[k].quantity * transaction[i].setItem[k].price;
				for(int l = 0; l < *max; l++){
					if(transaction[i].setItem[k].productID == cart[l].productID){
						if((cart[l].quantity - transaction[i].setItem[k].quantity) < 1)
							removeProductID( cart, max, cart[l].productID);
						else
							cart[l].quantity = cart[l].quantity - transaction[i].setItem[k].quantity;
					}
				}
				for(int l = 0; l < itemCnt; l++){
					if(transaction[i].setItem[k].productID == items[l].productID){
						if((items[l].quantity - transaction[i].setItem[k].quantity) < 1)
							removeProductID( items, &itemCnt, items[l].productID);
						else
							items[l].quantity = items[l].quantity - transaction[i].setItem[k].quantity;
					}
				}
				
			}
			transaction[i].total = nTotal;
			printf("\n\n\t       TOTAL AMOUNT: %d", transaction[i].total);
			printf("\n\tPayable To SellerID: %d", transaction[i].setItem[0].sellerID);
			for(int m = 0; m < userCnt; m++){
				if(users[m].userID == transaction[i].setItem[0].sellerID)
					strcpy( sellerName, users[m].name);
			}
			printf("\n\t        Seller Name: %s", sellerName);
			printf("\n");
			nTotal = 0;
		}
		
			//updates "Transactions.dat"
		fpTransaction = fopen("Transactions.dat", "rb+");
		
		fseek(fpTransaction, 0, SEEK_END);
		
		
		for(int i = 0; i < tCtr; i++)
			fwrite(&transaction[i], sizeof(transactionTag), 1, fpTransaction);
		
			//updates "Items.txt" file
		fpItem = fopen("Items.txt", "w");
		
		for(int i = 0; i < itemCnt; i++)
			fprintf(fpItem, "%d %d\n%s\n%s\n%s\n%d %d\n\n", items[i].productID, items[i].sellerID, items[i].itemName, items[i].category, items[i].description, items[i].quantity, items[i].price);
	
		
		fclose(fpItem);
		fclose(fpTransaction);
	}
	
/*
	Purpose: checks out all the given seller's items in the cart and displays transaction receipt/s
	@param : cart[] is the structure array that contains items
	@param : *max is the count of items stored in the cart
	@param : transaction[] is the structure array that contains transactions
	@param : buyerID stores the buyerID
	@param : strDate stores the date of the transaction
	@param : userCnt monitors the count of users added in the array
	@param : users[] is the structure array that contains users
	Pre-condition: the parameters contain valid values
*/		
	void checkOutSeller(itemTag cart[],int  *max, transactionTag transaction[], int buyerID,str10 strDate, int userCnt, userTag users[]){
		int tempSeller, nLimit = 0, l = 0, tCtr = 0, nTotal = 0, itemCnt;
		str20 sellerName;
		FILE *fpTransaction, *fpItem;
		
		fpItem = fopen("Items.txt", "r");
		
		itemCnt = countBuyItems(fpItem);
		
		itemTag items[itemCnt];
		
		scanBuyItems(items,	fpItem, itemCnt);
		
		printf("Enter Specific Seller: ");
		scanf("%d", &tempSeller);
		
			//counts how many items tempSeller has in the cart
		for(int i = 0;  i < *max; i++)
			if(cart[i].sellerID == tempSeller){
				nLimit++;
			}
		
			//stores items with the corresponding sellerID to transaction structure
		for(int i = 0;  i < *max; i++){
			if(cart[i].sellerID == tempSeller){
				if(l > 4){
					tCtr++;
					l = 0;
				}
				strcpy(transaction[tCtr].date, strDate);
				transaction[tCtr].setItem[l] = cart[i];
				transaction[tCtr].buyerID = buyerID;
				transaction[tCtr].tranSellerID = cart[i].sellerID;
				l++;
			}
		}
		
		if(nLimit < 5)
		nLimit = 0;

		tCtr++;
		
		while(l < 5){	//if not all slots of transaction.items is filled, productID's and prices are set to 0 to avoid garbage values
			transaction[tCtr].setItem[l].productID = 0;
			transaction[tCtr].setItem[l].price = 0;
			l++;
		}
		
		for(int i = 0; i < tCtr; i++){	//display transactions
			printf("\n\n\t\t\t\t     %d TRANSACTION RECEIPT \n\n", transaction[i].setItem[0].sellerID);
			printf("\tUnit Quantity ||  Product ID  ||      Item Name      ||  Unit Price  ||  Total Price \n\n");
			for(int k = 0; k < 5; k++){
				if(transaction[i].setItem[k].productID != 0){
					printf("\t%14d  %14d  %-21s  %14d  %14d  \n",   transaction[i].setItem[k].quantity, transaction[i].setItem[k].productID, transaction[i].setItem[k].itemName,  transaction[i].setItem[k].price, transaction[i].setItem[k].quantity*transaction[i].setItem[k].price);
					nTotal = nTotal + transaction[i].setItem[k].quantity * transaction[i].setItem[k].price;
					for(int l = 0; l < *max; l++){
						if(transaction[i].setItem[k].productID == cart[l].productID){
							if((cart[l].quantity - transaction[i].setItem[k].quantity) < 1)
								removeProductID( cart, max, cart[l].productID);
							else
								cart[l].quantity = cart[l].quantity - transaction[i].setItem[k].quantity;
						}
					}
					for(int l = 0; l < itemCnt; l++){
						if(transaction[i].setItem[k].productID == items[l].productID){
							if((items[l].quantity - transaction[i].setItem[k].quantity) < 1)
								removeProductID( items, &itemCnt, items[l].productID);
							else
								items[l].quantity = items[l].quantity - transaction[i].setItem[k].quantity;
						}
					}
				}
			}
			transaction[i].total = nTotal;
			printf("\n\n\t       TOTAL AMOUNT: %d", transaction[i].total);
			printf("\n\tPayable To SellerID: %d", transaction[i].setItem[0].sellerID);
			for(int m = 0; m < userCnt; m++){
				if(users[m].userID == transaction[i].setItem[0].sellerID)
					strcpy( sellerName, users[m].name);
			}
			printf("\n\t        Seller Name: %s", sellerName);
			printf("\n");
			nTotal = 0;
		}
		
			//updates "Transactions.dat"
		fpTransaction = fopen("Transactions.dat", "rb+");
		
		fseek(fpTransaction, 0, SEEK_END);
		
		for(int i = 0; i < tCtr; i++)
			fwrite(&transaction[i], sizeof(transactionTag), 1, fpTransaction);
			
			//updates "Items.txt" file
		fpItem = fopen("Items.txt", "w");
		
		for(int i = 0; i < itemCnt; i++)
			fprintf(fpItem, "%d %d\n%s\n%s\n%s\n%d %d\n\n", items[i].productID, items[i].sellerID, items[i].itemName, items[i].category, items[i].description, items[i].quantity, items[i].price);
	
		
		fclose(fpItem);
		fclose(fpTransaction);
	}

/*
	Purpose: checks out the given item in the cart and displays the transaction receipt
	@param : cart[] is the structure array that contains items
	@param : *max is the count of items stored in the cart
	@param : transaction[] is the structure array that contains transactions
	@param : buyerID stores the buyerID
	@param : strDate stores the date of the transaction
	@param : userCnt monitors the count of users added in the array
	@param : users[] is the structure array that contains users
	Pre-condition: the parameters contain valid values
*/		
	void checkOutItem(itemTag cart[],int  *max, transactionTag transaction[], int buyerID, str10 strDate, int userCnt, userTag users[]){
		int tempID, nTotal = 0, l = 0, itemCnt;
		str20 sellerName;
		FILE *fpTransaction, *fpItem;
		
		fpItem = fopen("Items.txt", "r");
		
		itemCnt = countBuyItems(fpItem);
		
		itemTag items[itemCnt];
		
		scanBuyItems(items,	fpItem, itemCnt);
		
		printf("Enter Specific Product ID: ");
		scanf("%d", &tempID);
		
		for(int i = 0;  i < *max; i++){	//stores items with the corresponding productID to transaction structure
			if(cart[i].productID == tempID){
				strcpy(transaction[0].date, strDate);
				transaction[0].setItem[0] = cart[i];
				transaction[0].buyerID = buyerID;
				transaction[0].tranSellerID = cart[i].sellerID;
				l++;
			}
		}
		
		while(l < 5){	//if not all slots of transaction.items is filled, productID's and prices are set to 0 to avoid garbage values
			transaction[0].setItem[l].productID = 0;
			transaction[0].setItem[l].price = 0;
			l++;
		}
		
		printf("\n\n\t\t\t\t     %d TRANSACTION RECEIPT \n\n", transaction[0].setItem[0].sellerID);
		printf("\tUnit Quantity ||  Product ID  ||      Item Name      ||  Unit Price  ||  Total Price \n\n");
		
		if(transaction[0].setItem[0].productID != 0){	//display transactions
			printf("\t%14d  %14d  %-21s  %14d  %14d  \n",   transaction[0].setItem[0].quantity, transaction[0].setItem[0].productID, transaction[0].setItem[0].itemName,  transaction[0].setItem[0].price, transaction[0].setItem[0].quantity*transaction[0].setItem[0].price);
			nTotal = nTotal + transaction[0].setItem[0].quantity * transaction[0].setItem[0].price;
			for(int l = 0; l < *max; l++){
				if(transaction[0].setItem[0].productID == cart[l].productID){
					if((cart[l].quantity - transaction[0].setItem[0].quantity) < 1)
						removeProductID( cart, max, cart[l].productID);
					else
						cart[l].quantity = cart[l].quantity - transaction[0].setItem[0].quantity;
				}
			}
			for(int l = 0; l < itemCnt; l++){
				if(transaction[0].setItem[0].productID == items[l].productID){
					if((items[l].quantity - transaction[0].setItem[0].quantity) < 1)
						removeProductID( items, &itemCnt, items[l].productID);
					else
						items[l].quantity = items[l].quantity - transaction[0].setItem[0].quantity;
				}
			}
		}
			
		transaction[0].total = nTotal;
		
		printf("\n\n\t       TOTAL AMOUNT: %d", transaction[0].total);
		printf("\n\tPayable To SellerID: %d", transaction[0].setItem[0].sellerID);
		
		for(int m = 0; m < userCnt; m++){
			if(users[m].userID == transaction[0].setItem[0].sellerID)
				strcpy( sellerName, users[m].name);
		}
		
		printf("\n\t        Seller Name: %s", sellerName);
		printf("\n");
		
			//updates "Transactions.dat"
		fpTransaction = fopen("Transactions.dat", "rb+");
		
		fseek(fpTransaction, 0, SEEK_END);
		
		fwrite(&transaction[0], sizeof(transactionTag), 1, fpTransaction);
			//updates "Items.txt" file
		fpItem = fopen("Items.txt", "w");
		
		for(int i = 0; i < itemCnt; i++)
			fprintf(fpItem, "%d %d\n%s\n%s\n%s\n%d %d\n\n", items[i].productID, items[i].sellerID, items[i].itemName, items[i].category, items[i].description, items[i].quantity, items[i].price);
	
		
		fclose(fpItem);
		fclose(fpTransaction);
	}

/*
	Purpose: checks and updates any product changes in the cart
	@param : itemArray[] is the structure array that contains items
	@param : itemMax is the count of items stored in the cart
	@param : cart[] is the structure array that contains items
	@param : cartMax is the count of items stored in the cart
	Pre-condition: the parameters contain valid values
*/	
	void checkUpdateCart(itemTag itemArray[],int itemMax, itemTag cart[], int cartMax){
	int nFlag = 0;
		
		for(int i = 0; i < cartMax; i++)
			for (int k = 0; k < itemMax; k++)
				if(cart[i].productID == itemArray[k].productID) //checks if product is found in the cart
					if(cart[i].quantity > itemArray[k].quantity || cart[i].price != itemArray[k].price){ //checks if the product information from itemArray[] is different from the cart[]
						printf("\n\n\tChange has been applied to Product %s", cart[i].itemName);
						if (cart[i].price != itemArray[k].price){
							printf("\n\nOld Price: %d \nNew Price: %d", cart[i].price, itemArray[k].price);
							cart[i].price = itemArray[k].price;
							nFlag++;
						}
						if (cart[i].quantity > itemArray[k].quantity){
							printf("\n\nCart Quantity: %d \nProduct Quantity: %d", cart[i].quantity, itemArray[k].quantity);	
							cart[i].quantity = itemArray[k].quantity;
							nFlag++;
						}
					}
		
		if (nFlag)
		printf("\n\n\t The Cart has been updated!\n To modify the Cart return to Edit Cart Menu");
	}

/*
	Purpose: displays the check out menu and calls the function that the user requires
	@param : itemArray[] is the structure array that contains items
	@param : itemMax is the count of items stored in the cart
	@param : cart[] is the structure array that contains items
	@param : *cartMax is the count of items stored in the cart
	@param : buyerID stores the buyerID
	@param : userCnt monitors the count of users added in the array
	@param : users[] is the structure array that contains users
	Pre-condition: the parameters contain valid values
*/		
	void checkOutMenu(itemTag itemArray[],int itemMax, itemTag cart[], int *cartMax, int buyerID, int userCnt, userTag users[]){
		transactionTag transaction[11];
		str10 tempDate;
		int nOpt;
		
		printf("Input Date [MM/DD/YYYY]: ");
		scanf("%s", tempDate);
		
		checkUpdateCart(itemArray, itemMax, cart, *cartMax);
		displayCart(cart, *cartMax);
		
		do{
			printf("\n\n\t     CHECK OUT MENU\n\n");	
			printf("\n\n     1 - All\n     2 - By a Specific Seller\n     3 - Specific Item\n     4 - Exit Check Out\n\n");
			printf("Select Option: ");
			scanf("%d", &nOpt);
			
			switch(nOpt){
				case 1: checkOutAll(cart, cartMax, transaction, buyerID, tempDate, userCnt, users); break;
				case 2: checkOutSeller(cart, cartMax, transaction, buyerID, tempDate, userCnt, users); break;
				case 3: checkOutItem(cart, cartMax, transaction, buyerID, tempDate, userCnt, users); break;
				case 4: printf ("\n"); break;
				default: printf("\nINVALID INPUT\n\n"); break;
			}
		}while(nOpt != 4);
	}
	
/*
	Purpose: add items to cart[]
	@param : itemArray[] contains all stored items
	@param : cart[] is the structure array that contains items
	@param : max is the count of items stored in the array
	@param : *cartCtr monitors the count of items added in the cart
	@param : sellerID stores the sellerID
	Pre-condition: the parameters contain valid values
*/	
	void addCart(itemTag itemArray[],itemTag cart[], int max, int *cartCtr, int sellerID){
		int tempProductID, tempQnty, nReq = 0, nOpt = 0;
		
		if(*cartCtr < 10){
			printf("Enter your productID: ");
			scanf("%d", &tempProductID);
			printf("Enter Quantity: ");
			scanf("%d", &tempQnty);
			
			for (int i = 0; i < max; i++){	
				if(tempProductID == itemArray[i].productID && sellerID != itemArray[i].sellerID){	//checks if item is owned by the buyer
					if(tempQnty <= itemArray[i].quantity && tempQnty != 0){		//adds item to the cart
						cart[*cartCtr] = itemArray[i];
						cart[*cartCtr].quantity = tempQnty;
						*cartCtr = *cartCtr + 1;
						nReq = 1;
						printf("\nProduct %d has been added to the Cart!\n\n", tempProductID);
						printf("\n\tRedirecting back to Main Menu...");
					}
					else if (tempQnty <= itemArray[i].quantity && tempQnty == 0)
						nReq = 0;
					else
						nReq = 17;
				}
			}
		
			if (nReq == 17)
				printf("\n\n\tProduct Quantity Insufficient\n\nRedirecting back to Main Menu...");
			else if (!(nReq))
				printf("\n\n\tRequest Denied\n\nRedirecting back to Main Menu..."); //not sureeee
		}
		else{
			do{
				printf("\n\n\tCART FULL");	
				printf("\n\n Proceed To Edit Cart or Check Out\n     1 - Back to Buy Menu\n\n");
				printf("Select Option: ");
				scanf("%d", &nOpt);
				
				switch(nOpt){
					case 1: printf ("\n"); break;
					default: printf("\nINVALID INPUT\n\n"); break;
			}
				
			}while(nOpt != 1);	
		}
		
	}




/*
	Purpose: add items from user.bag to cart[]
	@param : cart[] is the structure array that contains items
	@param : *cartCtr monitors the count of items added in the cart
	@param : sellerID stores the sellerID
	Pre-condition: the parameters contain valid values
*/
	void scanBag(itemTag cart[], int *cartCnt, int sellerID){
		str20 strID, strExt = ".bag";
		FILE *fpBag;
		
		if(*cartCnt == 0){
			sprintf(strID, "%d", sellerID);		//convert int to string
			
			strcat(strID, strExt);		//adds ".bag" to string
			
			fpBag = fopen(strID, "rb");		//opens "user.bag"
			
			while (fread(&cart[*cartCnt], sizeof(itemTag), 1, fpBag))	//scans "user.bag content"
				*cartCnt = *cartCnt + 1;
			
			fclose(fpBag);
		}
	}

/*
	Purpose: displays the buy menu and calls the function that the user requires
	@param : *fpItem is the Item and file name that will be scanned
	@param : *itemCnt is the count of items stored in the cart
	@param : userCnt monitors the count of users added in the array
	@param : buyerID stores the buyerID
	@param : users[] is the structure array that contains users
	@param : cart[] is the structure array that contains items
	@param : *cartCtr is the count of items stored in the cart
	Pre-condition: the parameters contain valid values
*/	
	void buyMenu(FILE *fpItem, int *itemCnt, int userCnt, int buyerID, userTag users[], itemTag cart[], int *cartCtr){
		int nOpt;
		
		*itemCnt = countBuyItems(fpItem);
		
		itemTag itemArray[*itemCnt];
		
		scanBuyItems(itemArray, fpItem, *itemCnt);
		
		scanBag(cart, cartCtr, buyerID);
		
		do{
			printf("\n\n\t     BUY MENU\n\n");	
			printf("\n\n     1 - View All Products\n     2 - Show All Products by a Specific Seller\n     3 - Search Products by Category\n     4 - Show Products by Name\n     5 - Add to cart\n     6 - Edit Cart\n     7 - Check Out Menu\n     8 - Exit Buy Menu\n\n");
			printf("Select Option: ");
			scanf("%d", &nOpt);
			
			switch(nOpt){
				case 1: allProducts(itemArray, *itemCnt, userCnt); break;
				case 2: specificSeller(itemArray, *itemCnt); break;
				case 3: specificCategory(itemArray, *itemCnt); break;
				case 4: specificName(itemArray, *itemCnt); break;
				case 5: addCart(itemArray, cart, *itemCnt, cartCtr, buyerID); break;
				case 6: editCart(cart, cartCtr); break;
				case 7: checkOutMenu(itemArray, *itemCnt, cart, cartCtr, buyerID, userCnt, users); break;
				case 8: printf ("\n"); break;
				default: printf("\nINVALID INPUT\n\n"); break;
			}
		}while(nOpt != 8);
	}

/*
	Purpose: displays the buy menu and calls the function that the user requires
	@param : cart[] is the structure array that contains items
	@param : *cartCnt is the count of items stored in the cart
	@param : sellerID stores the sellerID
	Pre-condition: the parameters contain valid values
*/	
	void userBag(itemTag cart[], int *cartCnt, int sellerID){
		str20 strID, strExt = ".bag";
		FILE *fpBag;
		
		sprintf(strID, "%d", sellerID);		//convert int to string
		
		strcat(strID, strExt);		//adds ".bag" to string
		
		fpBag = fopen(strID, "wb");		//creates "user.bag"
		
		for(int i = 0; i < *cartCnt; i++)
			fwrite(&cart[i], sizeof(itemTag), 1, fpBag);
		
		fclose(fpBag);
	}
	
/*
	Purpose: displays the user menu and calls the function that the user requires
	@param : sellerID stores the sellerID	
	@param : transaction[] is the structure array that contains transactions
	@param : *fpUser is the Item and file name that will be scanned
	@param : *fpItem is the Item and file name that will be scanned
	@param : *itemCnt is the count of items stored in the cart
	@param : userCnt monitors the count of users added in the array
	@param : users[] is the structure array that contains users
	Pre-condition: the parameters contain valid values
*/		
	void userMenu(int sellerID, transactionTag transactions[], FILE *fpUser , FILE *fpItem, int *itemCnt, int userCnt, userTag users[]){
		int nMenu, cartCtr = 0;
		itemTag cart[10];
		
		do{	
			printf("\n\n\t     USER MENU\n\n");
			printf("\n\n     1 - Sell Menu\n     2 - Buy Menu\n     3 - Exit User Menu\n\n");
			printf("Select Menu: ");
			scanf("%d", &nMenu);
			
			switch(nMenu){
				case 1: sellMenu(&nMenu, sellerID, transactions, fpUser, fpItem, itemCnt); break;
				case 2: buyMenu(fpItem, itemCnt, userCnt, sellerID, users, cart, &cartCtr); break;
				case 3: { if(cartCtr > 0)
							userBag(cart, &cartCtr, sellerID);
						  printf ("\n");} break;
				default: printf("\nINVALID INPUT\n\n"); break;
			}
		}while(nMenu != 3);
	}

/*
	Purpose: checks if the given login details are valid
	@param : *nMenu the condition of the selected menu
	@param : users is the structure array that will contain the data of the users
	@param : transactions[] contains all the transaction data
	@param : *fpUser is the User and file name that will be essential when calling functions
	@param : *fpItem is the Item and file name that will be essential when calling functions
	@param : *itemCnt is the count of items stored in the cart
	@param : userCnt monitors the count of users added in the array
	Pre-condition: the parameters contain valid values
*/		
	void logInUserMenu(int *nMenu, userTag users[], transactionTag transactions[], FILE *fpUser , FILE *fpItem, int *itemCnt, int userCnt){
		int tempUserID;
		str10 tempPass;
		
		printf("\nUserID:");
		scanf("%d", &tempUserID);
		
		printf("Password:");
		scanf("%s", tempPass);

		if (!(logIn(users, tempUserID ,tempPass))){		//checks if the login credentials are valid
			printf("\nInvalid UserID or Password\n");
			printf("\n\tRedirecting back to Main Menu...\n\n");
		}
		else
			userMenu(tempUserID,transactions, fpUser, fpItem, itemCnt, userCnt, users);
	}

/*
	Purpose: scans "Users.txt" data to users[]
	@param : users[] is the structure array that contains the data of the users
	@param : userCnt monitors the count of users added in the array
	@param : *fpUser is the User and file name that will be essential when calling functions
	Pre-condition: the parameters contain valid values
*/	
	void scanUsers(userTag users[], int *userCnt, FILE *fpUser){
		userTag tempUser;
		int  nLimit;
		
		*userCnt = 0;
		
		fclose(fpUser);
		fpUser = fopen("Users.txt", "r");
		
			//scans "Users.txt" and stores to the user[]
		while(fscanf(fpUser, "%d", &tempUser.userID) == 1){
			fscanf(fpUser, "%s", tempUser.password);
			fscanf(fpUser, " %[^\n]s", tempUser.name);
			fscanf(fpUser, " %[^\n]s", tempUser.address);
			fscanf(fpUser, "%d", &tempUser.contact);
			users[*userCnt].userID = tempUser.userID;
			strcpy(users[*userCnt].password, tempUser.password);
			strcpy(users[*userCnt].name, tempUser.name);
			strcpy(users[*userCnt].address, tempUser.address);
			users[*userCnt].contact = tempUser.contact;
			*userCnt = *userCnt + 1;
		}
		
		nLimit = *userCnt;
		
		while(nLimit < 100){	// if the scanned users is less than 100, the following userID's are set to 0 to prevent garbage values
			users[nLimit].userID = 0;
			nLimit++;
		}
	}

/*
	Purpose: displays all users
	@param : *fpUser is the User and file name that will be scanned
	Pre-condition: the parameters contain valid values
*/	
	void showAllUsers(FILE *fpUser){
		userTag users[100];
		userTag nSet;
		int userMax;
		
		scanUsers(users, &userMax, fpUser);
			
		for (int i = 0; i < userMax; ++i) {	//set users in increasing order
            for (int l = i + 1; l < userMax; ++l)
                if (users[i].userID > users[l].userID) {
                    nSet =  users[i];
                    users[i] = users[l];
                    users[l] = nSet;
             	}
		}
		printf("    User ID    ||     Password     ||       Name      ||        Address        ||   Phone Number\n\n");
		
		for(int i = 0; i < userMax; i++)
			printf("%15d  %18s  %17s  %23s  %15d\n", users[i].userID, users[i].password, users[i].name, users[i].address, users[i].contact);
	}

/*
	Purpose: returns the count of the given users' items
	@param : items[] is the structure array that contains the data of the items
	@param : itemCnt is the count of items stored in the cart
	@param : userID stores the userID	
	Pre-condition: the parameters contain valid values
*/		
	int countItems(itemTag items[],int itemCnt, int userID){
		int nCount = 0;
		
			for(int k = 0; k < itemCnt; k++){	//count items of the given userID
				if(userID == items[k].sellerID){
					nCount++;
					}
				}
		
		return nCount;
	}

/*
	Purpose: displays all sellers
	@param : *fpItem is the User and file name that will be scanned
	@param : *fpUser is the User and file name that will be scanned
	@param : itemMax is the count of items stored in the cart
	@param : userMax monitors the count of users added in the array
	Pre-condition: the parameters contain valid values
*/		
	void showAllSellers(FILE *fpItem, FILE *fpUser,  int itemMax, int userMax){
		userTag users[100], nSet;
		itemTag items[100];
		itemTag tempItem;
		int itemCnt, nCount;
		
		fclose(fpItem);
		fclose(fpUser);
		fpUser = fopen("Users.txt", "r");
		fpItem = fopen("Items.txt", "r");
		
		//scans "Items.txt" and stores to the user[]
		while(fscanf(fpItem, "%d %d", &tempItem.productID, &tempItem.sellerID) == 2){
			fscanf(fpItem, " %[^\n]s", tempItem.itemName);
			fscanf(fpItem, " %[^\n]s", tempItem.category);
			fscanf(fpItem, " %[^\n]s", tempItem.description);
			fscanf(fpItem, "%d %d", &tempItem.quantity, &tempItem.price);
				items[itemCnt].productID =  tempItem.productID;
				items[itemCnt].sellerID = tempItem.sellerID;
				strcpy(items[itemCnt].itemName, tempItem.itemName);
				strcpy(items[itemCnt].category, tempItem.category);
				strcpy(items[itemCnt].description, tempItem.description);
				items[itemCnt].quantity =  tempItem.quantity;
				items[itemCnt].price = tempItem.price;
				itemCnt = itemCnt + 1;
		}
	
		scanUsers(users, &userMax, fpUser);
		
		for (int i = 0; i < userMax; ++i) { 	//set users[] to increasing order
            for (int l = i + 1; l < userMax; ++l)
                if (users[i].userID > users[l].userID){
                    nSet =  users[i];
                    users[i] = users[l];
                    users[l] = nSet;
             	}
		}
			//prints all sellers
		printf("\n    User ID    ||     Password     ||       Name      ||        Address        ||  Phone Number || No. of Items ||\n\n");
		
		for(int i = 0; i < userMax; i++){
			nCount = 0;
			for(int k = 0; k < itemCnt; k++){
				if(users[i].userID == items[k].sellerID){
					nCount = countItems(items, itemCnt, users[i].userID);
				}
			}
			if(nCount)
			printf("%15d  %18s  %17s  %23s  %15d  %14d\n", users[i].userID, users[i].password, users[i].name, users[i].address, users[i].contact, nCount);
		}
	}

/*
	Purpose: convert date to int, e.g. (String: 01/02/2023 to Int: 20230102)
	@param : strDate is the given date to be converted
	Pre-condition: the parameters contain valid values
*/		
	int extractDate(str10 strDate){
		int day, month, year;     
		char tempStr[11];      
		int i = 0, cnt = 0;
	
	   strcpy(tempStr, strDate);

	   while (tempStr[i] != '/') {	//use '/' as a divider
	       i++;
	       cnt++;
	   }       
	   
	   tempStr[i] = '\0';   
	   
	   month = atol(tempStr);	//convert string to int

	   cnt++;
	   
	   strcpy(tempStr, strDate + cnt);
	   
	   i = 0;
	   
	   while (tempStr[i] != '/'){ 	//use '/' as a divider
	      i++;
	      cnt++;
	   }  
	   
	   tempStr[i] = '\0';
	   
	   day = atol(tempStr);      	//convert string to int
	       
	   cnt++; 
	   
	   strcpy(tempStr, strDate + cnt);  
	   
	   year = atol(tempStr);    	//convert string to int
	
	   return year * 10000 + month * 100 + day;   
	}

/*
	Purpose: displays total sales within the given dates
*/	
	void showTotalSales(){
		FILE *fpTransaction;
		str20 startDate, endDate;
		int sDate, eDate, nDayCnt, nIndex, m = 0, nTotal = 0;
		transactionTag tempTran;
		
		printf("Input Start Date [MM/DD/YYYY]: ");
		scanf("%s", startDate);
		printf("Input End Date [MM/DD/YYYY]: ");	
		scanf("%s", endDate);
		
		sDate = extractDate(startDate);
		eDate = extractDate(endDate);
	
		nDayCnt = (eDate-sDate) + 1;
		
		int arrIndex[nDayCnt];
		
		fpTransaction = fopen("Transactions.dat", "rb");
		
		nIndex = 0;
		
			//counts all transactions in the "Transaction.dat"
		while(fread(&tempTran, sizeof(transactionTag), 1, fpTransaction))
			nIndex++;
		
		transactionTag transaction[nIndex];
		int arrDate[nIndex];
		
		fseek (fpTransaction, 0, SEEK_SET);
		
		for(int i = 0; i < nIndex; i++){	//stores all transactions
			fread(&transaction[i], sizeof(transactionTag), 1, fpTransaction);
			arrDate[i] = extractDate(transaction[i].date);	//stores converted date
		}
		
		for(int k = 0; k < nIndex; k++){
			if(arrDate[k] >=  sDate && arrDate[k] <= eDate){	//stores index's of the transactions that falls within the given duration
				arrIndex[m] = k;
				m++;
			}
		}
		
		fseek (fpTransaction, 0, SEEK_SET);
		
		for(int i = 0; i < nIndex; i++){	//stores all transactions
			fread(&transaction[i], sizeof(transactionTag), 1, fpTransaction);
		}
		
		for(int i = 0; i < m; i++)	//prints transactions
			printf("\nTransaction Date: %10s\t Transaction Total: %14d", transaction[arrIndex[i]].date, transaction[arrIndex[i]].total);
		
		for(int i = 0; i < m; i++){
			nTotal = nTotal + transaction[arrIndex[i]].total;
		}
			
		printf("\n\n\t\t\t   TOTAL AMOUNT OF ALL TRANSACTIONS = %d", nTotal);
		
		fclose(fpTransaction);
	}

/*
	Purpose: displays sellers sales within the given dates
	@param : *fpUser is the User and file name that will be scanned
	Pre-condition: the parameters contain valid values
*/	
	void showSellers(FILE *fpUser){
		FILE *fpTransaction;
		str20 startDate, endDate, strName;
		int sDate, eDate, nDayCnt, nIndex, m = 0, nTotal = 0, nSet, uMax, n = 0, nFlag = 0;
		transactionTag tempTran;
		userTag users[100];
		
		scanUsers(users, &uMax, fpUser);
		
		printf("Input Start Date [MM/DD/YYYY]: ");
		scanf("%s", startDate);
		printf("Input End Date [MM/DD/YYYY]: ");	
		scanf("%s", endDate);
			
		sDate = extractDate(startDate);
		eDate = extractDate(endDate);
		
		nDayCnt = (eDate-sDate) + 1;

		int arrIndex[nDayCnt];
	
		fpTransaction = fopen("Transactions.dat", "rb");
		
		nIndex = 0;
		
			//counts all transactions in the "Transaction.dat"
		while(fread(&tempTran, sizeof(transactionTag), 1, fpTransaction))
			nIndex++;
		
		transactionTag transaction[nIndex];
		int arrSeller[nIndex];
		int arrDate[nIndex];

		fseek (fpTransaction, 0, SEEK_SET);
		
		for(int i = 0; i < nIndex; i++){
			fread(&transaction[i], sizeof(transactionTag), 1, fpTransaction);	//stores all transactions
			arrDate[i] = extractDate(transaction[i].date);	//stores converted date
		}
		
		for(int k = 0; k < nIndex; k++){
			if(arrDate[k] >=  sDate && arrDate[k] <= eDate){	//stores index's of the transactions that falls within the given duration
				arrIndex[m] = k;
				m++;
			}
		}
		
		for(int i = 0; i < m; i++){
			arrSeller[n] = transaction[arrIndex[i]].tranSellerID;	//stores all transaction seller ID's
			n++;
		}
		
		for(int i = 0; i < n; i++)	//removes transactions with garbage value
      		for(int l = i + 1; l < m; l++)
         		if(arrSeller[i] == 0){
            		for(int k = l; k < m; k++){
               			arrSeller[k] = arrSeller[k+1];
            		}
            		l--;
            		m--;
        		}
		

		
		for (int i = 0; i < n; ++i){	//sort sellerID's in increasing order
            for (int l = i + 1; l < m; ++l)
                if (arrSeller[i] > arrSeller[l]){
                    nSet =  arrSeller[i];
                    arrSeller[i] = arrSeller[l];
                    arrSeller[l] = nSet;
             	}
		}

		for(int i = 0; i < n; i++)		//removes duplicate sellerID's
      		for(int l = i + 1; l < m; l++)
         		if(arrSeller[i] == arrSeller[l]){
            		for(int k = l; k < m; k++){
               			arrSeller[k] = arrSeller[k+1];
            		}
            		l--;
            		m--;
        		}
        		
		for (int i = 0; i < n; ++i){	//prints sellers' transactions
			for(int k = 0; k < nIndex; k++)
				if(arrSeller[i] == transaction[k].tranSellerID){
					nTotal = nTotal + 	transaction[k].total;
				}
			if(nTotal){
				for(int l = 0; l < uMax; l++)
					if(users[l].userID == arrSeller[i])
						strcpy(strName, users[l].name);
				nFlag++;
				if(nTotal && nFlag == 1)
					printf("\n  Seller ID   ||       Name      ||   Total Sales\n\n");
				printf("%14d  %17s  %14d\n", arrSeller[i], strName, nTotal);
			}
			nTotal = 0;	
		}
		
		fclose(fpTransaction);
	}

/*
	Purpose: displays buyers expenses within the given dates
	@param : *fpItem is the User and file name that will be scanned
	@param : *fpUser is the User and file name that will be scanned
	@param : itemMax is the count of items stored in the cart
	@param : userMax monitors the count of users added in the array
	Pre-condition: the parameters contain valid values
*/	
	void showShopaholics(FILE *fpUser){
		FILE *fpTransaction;
		str20 startDate, endDate, strName;
		int sDate, eDate, nDayCnt, nIndex, m = 0, nTotal = 0, nSet, uMax, n = 0, nFlag = 0;
		transactionTag tempTran;
		userTag users[100];
		
		scanUsers(users, &uMax, fpUser);
		
		printf("Input Start Date [MM/DD/YYYY]: ");
		scanf("%s", startDate);
		printf("Input End Date [MM/DD/YYYY]: ");	
		scanf("%s", endDate);
			
		sDate = extractDate(startDate);
		eDate = extractDate(endDate);
		
		nDayCnt = (eDate-sDate) + 1;

		int arrIndex[nDayCnt];
	
		fpTransaction = fopen("Transactions.dat", "rb");
		
		nIndex = 0;
		
			//counts all transactions in the "Transaction.dat"
		while(fread(&tempTran, sizeof(transactionTag), 1, fpTransaction))
			nIndex++;
		
		transactionTag transaction[nIndex];
		int arrBuyer[nIndex];
		int arrDate[nIndex];

		fseek (fpTransaction, 0, SEEK_SET);
		
		for(int i = 0; i < nIndex; i++){
			fread(&transaction[i], sizeof(transactionTag), 1, fpTransaction);	//stores all transactions
			arrDate[i] = extractDate(transaction[i].date);	//stores converted date
		}
		
		for(int k = 0; k < nIndex; k++){
			if(arrDate[k] >=  sDate && arrDate[k] <= eDate){	//stores index's of the transactions that falls within the given duration
				arrIndex[m] = k;
				m++;
			}
		}
		
		for(int i = 0; i < m; i++){
			arrBuyer[n] = transaction[arrIndex[i]].buyerID;		//stores all transaction buyerID's
			n++;
		}
		
		
		for(int i = 0; i < n; i++)		//removes transactions with garbage value
      		for(int l = i + 1; l < m; l++)
         		if(arrBuyer[i] == 0){
            		for(int k = l; k < m; k++){
               			arrBuyer[k] = arrBuyer[k+1];
            		}
            		l--;
            		m--;
        		}
		

		
		for (int i = 0; i < n; ++i){	//sort buyerID's in increasing order
            for (int l = i + 1; l < m; ++l)
                if (arrBuyer[i] > arrBuyer[l]){
                    nSet =  arrBuyer[i];
                    arrBuyer[i] = arrBuyer[l];
                    arrBuyer[l] = nSet;
             	}
		}

		for(int i = 0; i < n; i++)		//removes duplicate buyerID's
      		for(int l = i + 1; l < m; l++)
         		if(arrBuyer[i] == arrBuyer[l]){
            		for(int k = l; k < m; k++){
               			arrBuyer[k] = arrBuyer[k+1];
            		}
            		l--;
            		m--;
        		}
        		
		for (int i = 0; i < n; ++i){	//prints sellers' transactions
			for(int k = 0; k < nIndex; k++)
				if(arrBuyer[i] == transaction[k].buyerID){
					nTotal = nTotal + 	transaction[k].total;
				}
			if(nTotal){
				for(int l = 0; l < uMax; l++)
					if(users[l].userID == arrBuyer[i])
						strcpy(strName, users[l].name);
				nFlag++;
				if(nTotal && nFlag == 1)
					printf("\n  Seller ID   ||       Name      ||   Total Expenses\n\n");
				printf("%14d  %17s  %14d\n", arrBuyer[i], strName, nTotal);
			}
			nTotal = 0;	
		}
		
		fclose(fpTransaction);
}

/*
	Purpose: displays the admin menu and calls the function that the user requires
	@param : *nMenu the condition of the selected menu
	@param : *fpUser is the User and file name that will be essential when calling functions
	@param : *fpItem is the Item and file name that will be essential when calling functions
	Pre-condition: the parameters contain valid values
*/		
	void adminMenu(int *nMenu, FILE *fpUser, FILE *fpItem, int itemMax, int userMax){
		int nOpt;
		
		*nMenu = 0;
		
			do{
				printf("\n\n\t     ADMIN MENU\n\n");	
				printf("\n\n     1 - Show All Users\n     2 - Show All Sellers\n     3 - Show Total Sales in Given Duration\n     4 - Show Sellers Sales\n     5 - Show Shopaholics\n     6 - Back to Main Menu\n\n");
				printf("Select Option: ");
				scanf("%d", &nOpt);
				
				switch(nOpt){
					case 1: showAllUsers(fpUser); break;
					case 2: showAllSellers(fpItem, fpUser, itemMax, userMax); break;
					case 3: showTotalSales(); break;
					case 4: showSellers(fpUser); break;
					case 5: showShopaholics(fpUser); break;
					case 6: printf ("\n"); break;
					default: printf("\nINVALID INPUT\n\n"); break;
				}
			}while(nOpt != 6);
			
	}

/*
	Purpose: checks if the given password is valid
	@param : *nMenu the condition of the selected menu
	@param : users is the structure array that will contain the data of the users
	@param : transactions[] contains all the transaction data
	@param : *fpUser is the User and file name that will be essential when calling functions
	@param : *fpItem is the Item and file name that will be essential when calling functions
	@param : *itemCnt is the count of items stored in the cart
	@param : userCnt monitors the count of users added in the array
	Pre-condition: the parameters contain valid values
*/		
	void logInAdminMenu(int *nMenu, userTag users[], transactionTag transactions[], FILE *fpUser , FILE *fpItem, int *itemCnt, int userCnt){
		str10 tempPass;
		int nCon = 1;
		printf("Admin Password:");
		scanf("%s", tempPass);
		
		for (int i = 0; i < 100; i++){
			if (!(strcmp(tempPass, users[i].password)))		//checks if the password is valid
					nCon = 0;
			}

		if (nCon){
			printf("\n\t\tInvalid Password\n");
			printf("\n\tRedirecting back to Main Menu...\n\n");
		}
		else
			adminMenu(nMenu, fpUser, fpItem, *itemCnt, userCnt);
	}

/*
	Purpose: close all opened file pointers
	@param : *nMenu the condition of the selected menu
	@param : *fpUser is the User and file name that will be essential when calling functions
	@param : *fpItem is the Item and file name that will be essential when calling functions
	@param : *fpCart is the Cart and file name that will be essential when calling functions
	@param : *fpTransaction is the Transaction and file name that will be essential when calling functions
	Pre-condition: the parameters contain valid values
*/	
	void nExit(int *nMenu, FILE *fpUser, FILE *fpItem,  FILE *fpTransaction){
		fclose(fpUser);
		fclose(fpItem);;
		fclose(fpTransaction);
		*nMenu = 4;
	}

int main(){
	userTag users[100];
	transactionTag transactions[20];
	int nMenu, userCnt = 0, itemCnt= 0;;
	FILE *fpUser, *fpItem, *fpTransaction;
	
	fpUser = fopen("Users.txt", "r");
	fpItem = fopen("Users.txt", "r");
	
	fpTransaction = fopen("Transactions.dat", "wb");
	
	if (fpUser == NULL)
		fpUser = fopen("Users.txt", "w");
	if (fpItem == NULL)
		fpUser = fopen("Users.txt", "w");
	
	scanUsers(users, &userCnt, fpUser);
	intro();
	
	do{	
		mainMenu();
		printf("Select Menu: ");
		scanf("%d", &nMenu);	
		
		switch(nMenu){
			case 1: regUser(&nMenu, users, &userCnt, fpUser, fpItem); userCnt++; break;
			case 2: logInUserMenu(&nMenu, users, transactions, fpUser, fpItem, &itemCnt, userCnt); break;
			case 3: logInAdminMenu(&nMenu, users, transactions, fpUser, fpItem, &itemCnt, userCnt); break;
			case 4: nExit(&nMenu, fpUser, fpItem, fpTransaction); break;
			default: printf("\nINVALID INPUT\n\n"); break;
		}
	}while(nMenu != 4);
	
	return 0;
}
