#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

FILE *facc;
int cartCount = 0, amount = 0;
bool loginStatus = 0;
char uname[20];

struct ele
{
    int id;
    char name[100];
    char os[10];
    float display;
    char cam[100];
    char connectivity[10];
    int ram;
    char sim[10];
    int battery;
    int price;
} mob;

struct lapp
{
    int id;
    char name[100];
    int ram;
    int storage;
    float display;
    char os[10];
    char graphic[50];
    char processor[50];
    int price;
} lap;

struct tele
{
    int id;
    char name[100];
    int size;
    char color[10];
    char res[10];
    int price;
} tel;

struct pro
{
    int id;
    char name[100];
    int quantity;
    int price;
};
struct pro prod;

typedef struct node
{
    struct pro p;
    int totalPrice;
    struct node *next;
} product;

struct Address
{
    char city[20];
    char state[20];
    int homeno;
    char street[20];
};

struct account
{
    char name[100];
    char email[50];
    char uname[20];
    char pword[10];
    struct Address address;
} acc;

product *firstProduct = NULL, *orders = NULL;

void home();
void categories();
void mobiles();
void laptops();
void televisions();
product *addToCart(struct pro p);
void displayCart();
product *deleteItem(int id);
void account();
void login();
void signin();
void payment();
void debit();
void details(char name[]);
void MyOrder();
product *placeorder();

int main()
{
    printf("\t\t\t\t\t\t*****************************************************************************\n");
    printf("\t\t\t\t\t\t\t\t\tWelcome to DigiMart\n");
    printf("\t\t\t\t\t\t\t\t\t\t-one stop for your all your electronics needs\n");
    printf("\t\t\t\t\t\t*****************************************************************************\n");
    while (1)
    {
        home();
    }
    return 0;
}

void payment()
{
    printf("\n\n1:debit card\n2:credit card\n3:Go back to cart\n");
    printf("Choose payment method:");
    int m;
    scanf("%d", &m);
    switch (m)
    {
    case 1:
        debit();
        break;
    case 2:
        debit();
        break;
    case 3:
        displayCart();
        break;
    default:
        printf("\nenter valid value:");
        payment();
    }
}

void debit()
{
    int cnum, cvv, waste;

    if (firstProduct == NULL)
    {
        printf("\nCart is empty.Please select products\n");
    }
    else
    {
        printf("\nThe following items are present in your cart:\n");
        product *temp = firstProduct;
        while (temp != NULL)
        {
            printf("%d-----%s----%d\n", temp->p.id, temp->p.name, temp->totalPrice);
            temp = temp->next;
        }
        printf("\nTotal amount= Rs.%d\n", amount);
        printf("|||||||||||| PAYMENT DESK |||||||||||||\n");
        printf("Card no.: ");
        scanf("%d", &cnum);
        printf("CVV: ");
        scanf("%d", &cvv);
        printf("Total Amount: %d\n", amount);
        printf("OTP: ");
        scanf("%d", &waste);
        orders = placeorder();
        home();
    }
}
void details(char name[])
{
    struct account a2;
    facc = fopen("account.txt", "r");
    while (fscanf(facc, "%s%s%s%s%s%s%s%d\n", a2.name, a2.email, a2.uname, a2.pword, a2.address.state, a2.address.city, a2.address.street, &a2.address.homeno) != EOF)
    {
        if (strcmp(name, a2.uname) == 0)
        {
            printf("\nName: %s\n", a2.name);
            printf("\nAddress: #%d, %s, %s, %s. \n", a2.address.homeno, a2.address.street, a2.address.city, a2.address.state);
            fclose(facc);
            break;
        }
    }
}

void MyOrder()
{
    if (orders == NULL)
    {
        printf("\nYOU HAVEN'T PLACE ANY ORDER\n");
    }
    else
    {
        printf("\n-----------YOUR ORDER(S)------------\n");
        product *temp = orders;
        while (temp != NULL)
        {
            if (temp->p.id == 999)
            {
                printf("\n\n");
                details(temp->p.name);
                printf("Total Amount: %d\n", temp->totalPrice);
                printf("----------------------------------------\n");
            }
            else
                printf("%d-----%s----%d\n", temp->p.id, temp->p.name, temp->totalPrice);

            temp = temp->next;
        }
    }
}

product *placeorder()
{
    product *newproduct, *temp;
    newproduct = (product *)malloc(sizeof(product));
    newproduct->p.id = 999;
    strcpy(newproduct->p.name, uname);
    newproduct->totalPrice = amount;
    newproduct->next = firstProduct;
    if (orders == NULL)
        orders = newproduct;
    else
    {
        temp = orders;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newproduct;
    }
    amount = 0;
    cartCount = 0;
    printf("\nORDER SUCCESSFULLY PLACED!!! :)\n");
    firstProduct = NULL;
    return (orders);
}

void account()
{
    int c;
    printf("\n\n1:Signin\n2:Login\n3:My details\n4:Go back to home\n");
    printf("Enter your choice: ");
    scanf("%d", &c);
    switch (c)
    {
    case 1:
        if (loginStatus)
            printf("\nYour are already loged in\n");
        else
            signin();
        break;
    case 2:
        if (loginStatus)
            printf("\nYour are already loged in\n");
        else
            login();
        break;
    case 3:
        if (loginStatus == 0)
            printf("\nPlease login/signin first\n");
        else
        {
            details(uname);
        }
        break;
    case 4:
        home();
        break;
    default:
        printf("\nEnter valid value\n");
    }
}

void signin()
{
    printf("\t\t..........SIGNIN.............\n");
    printf("Name: ");
    scanf("%s", acc.name);
    printf("Email id: ");
    scanf("%s", acc.email);
    printf("Username: ");
    scanf("%s", acc.uname);

    struct account a1;
    facc = fopen("account.txt", "r");
    while ((fscanf(facc, "%s%s%s%s%s%s%s%d", a1.name, a1.email, a1.uname, a1.pword, a1.address.state, a1.address.city, a1.address.street, &a1.address.homeno)) != EOF)
    {
        if (strcmp(acc.name, a1.name) == 0)
        {
            printf("This Account already exists.Please login below:-\n");
            fclose(facc);
            login();
        }
    }
    int i;
    char ch;
    printf("Password: ");
    for (i = 0; i < 100; i++)
    {
        ch = getch();

        if (ch == 13)
            break;
        acc.pword[i] = ch;
        ch = '*';
        printf("%c", ch);
    }
    acc.pword[i] = '\0';
    printf("\n");
    printf("Address:......\nState: ");
    scanf("%s", acc.address.state);
    printf("City: ");
    scanf("%s", acc.address.city);
    printf("Street: ");
    scanf("%s", acc.address.street);
    printf("Home No.: ");
    scanf("%d", &acc.address.homeno);
    facc = fopen("account.txt", "a");
    fprintf(facc, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\n", acc.name, acc.email, acc.uname, acc.pword, acc.address.state, acc.address.city, acc.address.street, acc.address.homeno);
    strcpy(uname, acc.name);
    printf("SUCCESSFULLY SIGNED IN\n");
    loginStatus = 1;
    fclose(facc);
    home();
}

void login()
{
    if (loginStatus)
    {
        printf("You are already loged in");
        home();
    }
    struct account a1;
    char strtemp[100];
    facc = fopen("account.txt", "r");
    printf("USERNAME: ");
    scanf("%s", strtemp);
    while ((fscanf(facc, "%s%s%s%s%s%s%s%d", a1.name, a1.email, a1.uname, a1.pword, a1.address.state, a1.address.city, a1.address.street, &a1.address.homeno)) != EOF)
    {
        if (strcmp(strtemp, a1.name) == 0)
        {
            int i;
            char ch;
            printf("PASSWORD: ");
            for (i = 0; i < 100; i++)
            {
                ch = getch();
                if (ch == 13)
                    break;
                acc.pword[i] = ch;
                ch = '*';
                printf("%c", ch);
            }
            acc.pword[i] = '\0';
            printf("\n");
            if (strcmp(acc.pword, a1.pword) == 0)
            {
                strcpy(uname, a1.uname);
                printf("\nSUCCESSFULLY LOGED IN\n");
                loginStatus = 1;
            }
            else
            {
                printf("WRONG PASSWORD\n");
                login();
            }
            fclose(facc);
            home();
        }
    }
    printf("%s does not exist.Please sign in\n", strtemp);
    signin();
}

product *deleteItem(int id)
{
    product *temp, *prev = NULL;
    if (firstProduct == NULL)
    {
        printf("\nEmpty Cart\n");
        return NULL;
    }
    temp = firstProduct;
    while (temp != NULL && temp->p.id != id)
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
        printf("\nID % d is not found\n", id);
    else
    {
        if (prev == NULL)
            firstProduct = firstProduct->next;
        else
            prev->next = temp->next;
        cartCount--;
        amount = amount - temp->totalPrice;
        printf("\nProduct with ID %d is deleted\n", id);
        free(temp);
    }
    return (firstProduct);
}

void displayCart()
{
    if (firstProduct == NULL)
    {
        printf("\nCart is empty.Please select products\n");
    }
    else
    {
        printf("The following items are present in your cart:\n");
        printf("ID\t\tNAME\t\t\tPRICE\t\tQUANTITY\tTOTAL PRICE");
        printf("\n======================================================================================================\n");
        product *temp = firstProduct;
        while (temp != NULL)
        {
            printf("%d\t\t%s\t\t%d\t\t%d\t\t%d\n", temp->p.id, temp->p.name, temp->p.price, temp->p.quantity, temp->totalPrice);
            temp = temp->next;
        }
        printf("\nTotal amount= Rs.%d\n", amount);
        while (1)
        {
            int choice, num;
            printf("1:Proceed to payment\n2:Go to home\n3:go to categories\n4:Delete item\nEnter your choice: ");
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
                payment(amount);
                break;
            case 2:
                home();
                break;
            case 3:
                categories();
                break;
            case 4:
                printf("\nEnter product id to be deleted:");
                scanf("%d", &num);
                firstProduct = deleteItem(num);
                break;
            default:
                printf("\ninvalid choice!!!\n");
            }
        }
    }
}

product *addToCart(struct pro p1)
{
    product *temp = firstProduct;
    while (temp != NULL)
    {
        if (temp->p.id == p1.id)
        {
            char ch;
            printf("\nProduct already exists in cart. Do you want to update the quantity?(y/n):");
            scanf(" %c", &ch);
            if (ch == 'Y' || ch == 'y')
            {
                amount = amount - temp->totalPrice;
                printf("Enter the total quantity u need: ");
                scanf("%d", &temp->p.quantity);
                temp->totalPrice = temp->p.price * temp->p.quantity;
                amount = amount + temp->totalPrice;
                printf("\nChanged the quantity successfully!!!\n");
                return (firstProduct);
            }
            else
            {
                printf("\nNothing updated in the cart!!\n");
                return (firstProduct);
            }
        }
        temp = temp->next;
    }
    product *newproduct;
    newproduct = (product *)malloc(sizeof(product));
    newproduct->p = p1;
    newproduct->totalPrice = p1.price * p1.quantity;
    newproduct->next = firstProduct;
    amount = amount + newproduct->totalPrice;
    cartCount++;
    printf("\nProduct succesfully added to the cart!!!\n");
    return (newproduct);
}

void televisions()
{
    FILE *fp = fopen("televisions.txt", "r");
    int choice, quantity, id, flag = 0;
    printf("\nTV NAME\t\t|ID\t|DISPLAY SIZE\t|COLOR\t|RESOLUTION\t|PRICE\n");
    while (fscanf(fp, "%d %s %d %s %s %d\n", &tel.id, tel.name, &tel.size, tel.color, tel.res, &tel.price) != EOF)
    {
        printf("%s\t|%d\t|%d\t\t|%s\t|%s\t\t|%d\t\n", tel.name, tel.id, tel.size, tel.color, tel.res, tel.price);
    }
    printf("\n\t\t\t\t\t***End of Products***\n");
    while (1)
    {
        printf("\n\n1:Add to cart\n2:View cart\n3:Go back to categories\n4: Go back to home\n\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("\nEnter product id and required quantity: ");
            scanf("%d %d", &id, &quantity);
            rewind(fp);
            while (fscanf(fp, "%d %s %d %s %s %d\n", &tel.id, tel.name, &tel.size, tel.color, tel.res, &tel.price) != EOF)
            {
                if (tel.id == id)
                {
                    flag = 1;
                    strcpy(prod.name, tel.name);
                    prod.id = tel.id;
                    prod.price = tel.price;
                    prod.quantity = quantity;
                    firstProduct = addToCart(prod);
                    break;
                }
            }
            if (flag == 0)
                printf("\nProduct not found.Please enter a valid id.\n");
            break;
        case 2:
            displayCart();
            break;
        case 3:
            categories();
            break;
        case 4:
            home();
            break;
        default:
            printf("\ninvalid choice!!!\n");
        }
    }
}

void laptops()
{
    FILE *fp = fopen("laptops.txt", "r");
    int choice, quantity, id, flag = 0;
    printf("\nLAPTOP NAME\t|ID\t|RAM\t|STORAGE\t|DISPLAY\t|OS\t\t|GRAPHIC CARD\t|PROCESSOR\t|PRICE\n");
    while (fscanf(fp, "%d %s %d %d %f %s %s %s %d\n", &lap.id, lap.name, &lap.ram, &lap.storage, &lap.display, lap.os, lap.graphic, lap.processor, &lap.price) != EOF)
    {
        printf("%s\t|%d\t|%dGB\t|%dTB SSD\t|%0.2f inch\t|%s\t|%s\t|%s\t|%d\n", lap.name, lap.id, lap.ram, lap.storage, lap.display, lap.os, lap.graphic, lap.processor, lap.price);
    }
    printf("\n\t\t\t\t\t\t\t***End of Products***\n");
    while (1)
    {
        printf("\n\n1:Add to cart\n2:View cart\n3:Go back to categories\n4: Go back to home\n\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("\nEnter product id and required quantity: ");
            scanf("%d %d", &id, &quantity);
            rewind(fp);
            while (fscanf(fp, "%d %s %d %d %f %s %s %s %d\n", &lap.id, lap.name, &lap.ram, &lap.storage, &lap.display, lap.os, lap.graphic, lap.processor, &lap.price) != EOF)
            {
                if (lap.id == id)
                {
                    flag = 1;
                    strcpy(prod.name, lap.name);
                    prod.id = lap.id;
                    prod.price = lap.price;
                    prod.quantity = quantity;
                    firstProduct = addToCart(prod);
                    break;
                }
            }
            if (flag == 0)
                printf("\nProduct not found.Please enter a valid id.\n");
            break;
        case 2:
            displayCart();
            break;
        case 3:
            categories();
            break;
        case 4:
            home();
            break;
        default:
            printf("\ninvalid choice!!!\n");
        }
    }
}

void mobiles()
{
    FILE *fp = fopen("mobiles.txt", "r");
    int choice, quantity, id, flag = 0;
    printf("MOBILE NAME\t|ID\t|DISPLAY SIZE\t|OS\t\t|CAMERA\t\t\t|CONNECTIVITY\t|RAM\t|SIM\t|BATTERY\t|PRICE\t\n");
    while (fscanf(fp, "%d %s %s %f %s %s %d %s %d %d\n", &mob.id, mob.name, mob.os, &mob.display, mob.cam, mob.connectivity, &mob.ram, mob.sim, &mob.battery, &mob.price) != EOF)
    {
        printf("%s\t|%d\t|%0.2f\t\t|%s\t|%s\t|%s\t\t|%d\t|%s\t|%d\t\t|%d\t\n", mob.name, mob.id, mob.display, mob.os, mob.cam, mob.connectivity, mob.ram, mob.sim, mob.battery, mob.price);
    }
    printf("\n\t\t\t\t\t\t\t***End of Products***\n");
    while (1)
    {
        printf("\n\n1:Add to cart\n2:View cart\n3:Go back to categories\n4: Go back to home\n\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("\nEnter product id and required quantity: ");
            scanf("%d %d", &id, &quantity);
            rewind(fp);
            while (fscanf(fp, "%d %s %s %f %s %s %d %s %d %d\n", &mob.id, mob.name, mob.os, &mob.display, mob.cam, mob.connectivity, &mob.ram, mob.sim, &mob.battery, &mob.price) != EOF)
            {
                if (mob.id == id)
                {
                    flag = 1;
                    strcpy(prod.name, mob.name);
                    prod.id = mob.id;
                    prod.price = mob.price;
                    prod.quantity = quantity;
                    firstProduct = addToCart(prod);
                    break;
                }
            }
            if (flag == 0)
                printf("\nProduct not found.Please enter a valid id.\n");
            break;
        case 2:
            displayCart();
            break;
        case 3:
            categories();
            break;
        case 4:
            home();
            break;
        default:
            printf("\ninvalid choice!!!\n");
        }
    }
}

void categories()
{
    int catChoice;
    while (1)
    {
        printf("\n\n1:Mobiles\n2:Laptops\n3:Televisions\n4:Go back to home\nEnter your choice:");
        scanf("%d", &catChoice);
        switch (catChoice)
        {
        case 1:
            mobiles();
            break;
        case 2:
            laptops();
            break;
        case 3:
            televisions();
            break;
        case 4:
            home();
            break;
        default:
            printf("\ninvalid choice!!!\n");
        }
    }
}

void home()
{
    int choice;
    char ch;
    while (1)
    {
        printf("\n\n1:Shop by category\n2:My account\n3:My orders\n4:My cart[%d]\n5:Logout\n6:exit", cartCount);
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            if (loginStatus)
                categories();
            else
            {
                printf("\nPlease log in/sign in to proceed further\n");
                account();
            }
            break;
        case 2:
            account();
            break;
        case 3:
            if (loginStatus)
                MyOrder();
            else
            {
                printf("\nPlease log in/sign in to proceed further\n");
                account();
            }
            break;
        case 4:
            if (loginStatus)
                displayCart();
            else
            {
                printf("\nPlease log in/sign in to proceed further\n");
                account();
            }
            break;
        case 5:
            loginStatus = 0;
            strcpy(uname, "");
            printf("\nLoged out successfully\n");
            break;
        case 6:
            if (cartCount > 0)
            {
                printf("Looks like you have left something in cart.\nWould you really like to exit?(Y/N)");
                scanf(" %c", &ch);
                if (ch == 'Y' || ch == 'y')
                {
                    printf(":'(");
                    exit(0);
                }
                else
                    home();
            }
            else
                exit(0);
        default:
            printf("\ninvalid choice!!!\n");
        }
    }
}