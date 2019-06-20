#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct BSTnode

  {
        char word[128], meaning[256];
        struct BSTnode *left, *right;
  };

struct BSTnode *root = NULL;

struct Node
  {
  	char sword[128];
  	struct Node *next;
  };

struct Node *str1;

struct Node *top = NULL;

struct Node *search_history(char* sword) /* To insert element in the stack Push function*/
{
  	struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
  	strcpy(temp->sword, sword);
  	temp -> next = top;
  	top = temp;
  	return top;
}

void display_search_history(struct Node *top) /* To display the elements that are present in stack*/
{
  	int i=0;
	if(top == NULL)
  	{
  		printf("You have not searched for any word yet!!\n");
		return;
	}
	printf("S.No \t Word\n");
	while(top != NULL)
	{
		i++;
		printf("%d \t %s\n" , i, top->sword);
		top = top -> next;
	}
}

struct Node *clear_history(struct Node *top) /* To empty the stack*/
{
  	str1 = NULL;
  	struct Node *temp;
  	if(top == NULL)
  	{
  		printf("No history entry found!!\n");
  		return str1;
	}
	while(top)
	{
		temp = top;
		top = top->next;
		printf("\nDeleted word is: %s\n" ,temp->sword);
		free(temp);
	}
	return top;
}

struct Node *remove_recent(struct Node *top) /*To remove the top element of the stack*/
{
  	str1 = NULL;
  	struct Node *temp;
  	if(top == NULL)
  	{
  		printf("No history entry found!!\n");
  		return str1;
	}
	if(top->next==NULL)
    {
        temp=top;
        printf("\nDeleted word is: %s\n",temp->sword);
        free(top);
        top=NULL;
        return str1;
    }
    temp = top;
    top = top -> next;
    printf("\nDeleted word is: %s\n" , temp->sword);
    free(temp);
    return (top);

}

struct BSTnode * createNode(char *word, char *meaning)
{
    	struct BSTnode *newnode;
        newnode = (struct BSTnode *)malloc(sizeof(struct BSTnode));
        strcpy(newnode->word, word);
        strcpy(newnode->meaning, meaning);
        newnode->left = newnode->right = NULL;
        return newnode;
}

void insert(char *word, char *meaning)
{
        struct BSTnode *parent = NULL, *current = NULL, *newnode = NULL;
        int res = 0 , res1 = 0;
        if (!root)
		{
                root = createNode(word, meaning);
                return;
        }
        for (current = root; current !=NULL; current = (res > 0) ? current->right : current->left)
		{
                res = strcasecmp(word, current->word);
                res1 = strcasecmp(meaning , current -> meaning);
                if (res == 0 && res1 == 0)
				{
                        printf("Duplicate entry!!\n");
                        return;
                }
                parent = current;
        }
        newnode = createNode(word, meaning);
        res > 0 ? (parent->right = newnode) : (parent->left = newnode);
        return;
}

void deleteNode(char *str)
  {
        struct BSTnode *parent = NULL, *current = NULL, *temp = NULL;
        int flag = 0, res = 0;
        if (!root)
		{
                printf("You have not updated your dictionary!!\n");
                return;
        }
        current = root;
        while (1)
		{
                res = strcasecmp(current->word, str);
                if (res == 0)
                        break;
                flag = res;
                parent = current;
                current = (res > 0) ? current->left : current->right;
                if (current == NULL)
                        return;
        }
        /* deleting leaf node */
        if (current->right == NULL)
		{
                if (current == root && current->left == NULL)
				{
                        free(current);
                        root = NULL;
                        return;
                }
				else if (current == root)
				{
                        root = current->left;
                        free (current);
                        return;
                }
                flag > 0 ? (parent->left = current->left) : (parent->right = current->left);
        }
		else
		{
                /* delete node with single child */
                temp = current->right;
                if (!temp->left)
				{
                        temp->left = current->left;
                        if (current == root)
						{
                                root = temp;
                                free(current);
                                return;
                        }
                        flag > 0 ? (parent->left = temp) : (parent->right = temp);
                }
				else
				{
                        /* delete node with two children */
                        struct BSTnode *successor = NULL;
                        while (1)
						{
                                successor = temp->left;
                                if (!successor->left)
                                        break;
                                temp = successor;
                        }
                        temp->left = successor->right;
                        successor->left = current->left;
                        successor->right = current->right;
                        if (current == root)
						{
                                root = successor;
                                free(current);
                                return;
                        }
                        (flag > 0) ? (parent->left = successor) : (parent->right = successor);
                }
        }
        free (current);
        return;
}

struct Node *findElement(char *str)
{
    struct BSTnode *temp = NULL;
    int flag = 0, res = 0;
    str1 = NULL;
    if (root == NULL)
    {

            printf("Binary Search Tree is out of station!!\n");
            return str1;
    }
    temp = root;
    while (temp)
    {
            if ((res = strcasecmp(temp->word, str)) == 0)
            {
                printf("Word   : %s", str);
                printf("Meaning: %s", temp->meaning);
                str1 = search_history(str);
                flag = 1;
                return str1;
            }
            temp = (res > 0) ? temp->left : temp->right;
    }
    if (!flag)
        printf("Search Element not found in Binary Search Tree\n");
    str1 = NULL;
    return str1;
}

void inorderTraversal(struct BSTnode *myNode)
{
    if (myNode)
    {
            inorderTraversal(myNode->left);
            printf("Word    : %s", myNode->word);
            printf("Meaning : %s", myNode->meaning);
            printf("\n");
            inorderTraversal(myNode->right);
    }
    return;
}

void dis_dict()
{
    printf("\n  ....   .....   .... ..... .....   ....   ..    .     ...     ....  .     .");
    printf("\n  .   .    .    .       .     .    .    .  . .   .    .   .    .   .  .   .");
    printf("\n  .    .   .   .        .     .   .      . .  .  .   .......   ....    ...");
    printf("\n  .   .    .    .       .     .    .    .  .   . .  .       .  .   .    .");
    printf("\n  ....   .....   ....   .   .....   ....   .    .. .         . .    .   .");
}

void main_menu()

{
    char s1 = 176;
    printf("\n\n\t\t\t****************************");
    printf("\n\t\t\t%c 1  | Insert a word in    %c" , s1 , s1);
    printf("\n\t\t\t%c    | dictionary          %c" , s1 , s1);
    printf("\n\t\t\t%c    |                     %c" , s1 , s1);
    printf("\n\t\t\t%c 2  | Remove a word       %c" , s1 , s1);
    printf("\n\t\t\t%c    | from dictionary     %c" , s1 , s1);
    printf("\n\t\t\t%c    |                     %c" , s1 , s1);
    printf("\n\t\t\t%c 3  | Search for a word   %c" , s1 , s1);
    printf("\n\t\t\t%c    |                     %c" , s1 , s1);
    printf("\n\t\t\t%c 4  | Show search history %c" , s1 , s1);
    printf("\n\t\t\t%c    |                     %c" , s1 , s1);
    printf("\n\t\t\t%c 5  | Remove last         %c" , s1 , s1);
    printf("\n\t\t\t%c    | searched element    %c" , s1 , s1);
    printf("\n\t\t\t%c    |                     %c" , s1 , s1);
    printf("\n\t\t\t%c 6  | Clear history       %c" , s1 , s1);
    printf("\n\t\t\t%c    |                     %c" , s1 , s1);
    printf("\n\t\t\t%c 7  | Display words       %c" , s1 , s1);
    printf("\n\t\t\t%c    |                     %c" , s1 , s1);
    printf("\n\t\t\t%c 8  | Exit                %c" , s1 , s1);
    printf("\n\t\t\t****************************\n");
}

int main()
{
    system("color 3");
    int ch;
    char str[128], meaning[256];
    void dis_dict();
    while(1)
    {
        main_menu();
        printf("Enter your choice: ");
        scanf("%d", &ch);
        printf("\n");
        getchar();
        switch (ch)
        {
            case 1:
                    printf("Word to insert:");
                    fgets(str, 100, stdin);
                    printf("Meaning:");
                    fgets(meaning, 256, stdin);
                    insert(str, meaning);
                    break;
            case 2:
                    printf("Enter the word to delete:");
                    fgets(str, 100, stdin);
                    deleteNode(str);
                    break;
            case 3:
                    printf("Enter the search word:");
                    fgets(str, 100, stdin);
                    findElement(str);
                    break;
            case 4:
                    display_search_history(str1);
                    break;
            case 5:
                    str1=remove_recent(str1);
                    break;
            case 6:
                    str1=clear_history(str1);
                    break;
            case 7:
                    inorderTraversal(root);
                    break;
            case 8:
                    exit(0);
                    break;
            default:
                    printf("You have entered a wrong option\n");
                    break;
        }
    }
    return 0;
}
