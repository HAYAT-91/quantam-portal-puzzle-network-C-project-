#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

/* Array */
int portalID[MAX], totalPortal = 0;
char portalName[MAX][30];

/* Queue */
int playerQueue[MAX], front = -1, rear = -1;

/* BST Node */
struct Node
{
    int id;
    struct Node *left;
    struct Node *right;
};

struct Node *root = NULL;

/* Display Portals */
void displayPortals()
{
    int i;

    if (totalPortal == 0)
    {
        printf("No portals available.\n");
        return;
    }

    printf("\nPortal List\n");

    for (i = 0; i < totalPortal; i++)
        printf("%d %s\n", portalID[i], portalName[i]);
}

/* Insert Portal */
void insertPortal()
{
    int id, pos, i;
    char name[30];

    if (totalPortal == MAX)
    {
        printf("Storage full.\n");
        return;
    }

    printf("Portal ID: ");
    scanf("%d", &id);

    printf("Portal Name: ");
    scanf("%s", name);

    printf("Position (1-%d): ", totalPortal + 1);
    scanf("%d", &pos);

    if (pos < 1 || pos > totalPortal + 1)
    {
        printf("Invalid position.\n");
        return;
    }

    for (i = totalPortal; i >= pos; i--)
    {
        portalID[i] = portalID[i - 1];
        strcpy(portalName[i], portalName[i - 1]);
    }

    portalID[pos - 1] = id;
    strcpy(portalName[pos - 1], name);
    totalPortal++;

    printf("Portal inserted.\n");
}

/* Delete Portal */
void deletePortal()
{
    int pos, i;

    if (totalPortal == 0)
    {
        printf("No portal.\n");
        return;
    }

    printf("Position to delete: ");
    scanf("%d", &pos);

    if (pos < 1 || pos > totalPortal)
    {
        printf("Invalid position.\n");
        return;
    }

    for (i = pos - 1; i < totalPortal - 1; i++)
    {
        portalID[i] = portalID[i + 1];
        strcpy(portalName[i], portalName[i + 1]);
    }

    totalPortal--;

    printf("Portal deleted.\n");
}

/* Linear Search */
void linearSearchPortal()
{
    char name[30];
    int i;

    printf("Portal name: ");
    scanf("%s", name);

    for (i = 0; i < totalPortal; i++)
    {
        if (strcmp(portalName[i], name) == 0)
        {
            printf("Found ID: %d\n", portalID[i]);
            return;
        }
    }

    printf("Portal not found.\n");
}

/* Enqueue */
void enqueuePlayer()
{
    int id;

    if (rear == MAX - 1)
    {
        printf("Queue full.\n");
        return;
    }

    printf("Player ID: ");
    scanf("%d", &id);

    if (front == -1)
        front = 0;

    playerQueue[++rear] = id;

    printf("Player added to queue.\n");
}

/* Dequeue */
void dequeuePlayer()
{
    if (front == -1 || front > rear)
    {
        printf("Queue empty.\n");
        return;
    }

    printf("Player %d entered portal.\n", playerQueue[front++]);

    if (front > rear)
        front = rear = -1;
}

/* Create BST Node */
struct Node *createNode(int id)
{
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));

    temp->id = id;
    temp->left = NULL;
    temp->right = NULL;

    return temp;
}

/* BST Insert */
struct Node *insertNode(struct Node *node, int id)
{
    if (node == NULL)
        return createNode(id);

    if (id < node->id)
        node->left = insertNode(node->left, id);
    else if (id > node->id)
        node->right = insertNode(node->right, id);

    return node;
}

/* BST Search */
int searchNode(struct Node *node, int id)
{
    if (node == NULL)
        return 0;

    if (node->id == id)
        return 1;

    if (id < node->id)
        return searchNode(node->left, id);

    return searchNode(node->right, id);
}

/* Inorder Traversal */
void inorder(struct Node *node)
{
    if (node == NULL)
        return;

    inorder(node->left);
    printf("%d ", node->id);
    inorder(node->right);
}

int main()
{
    int choice = 0, id;

    while (choice != 9)
    {
        printf("\n==== Quantum Portal Puzzle Network ====\n");
        printf("1. Insert Portal\n");
        printf("2. Delete Portal\n");
        printf("3. Display Portals\n");
        printf("4. Linear Search Portal\n");
        printf("5. Enqueue Player\n");
        printf("6. Dequeue Player\n");
        printf("7. Insert Portal Node\n");
        printf("8. Search Portal Node\n");
        printf("9. Exit\n");

        printf("Choice: ");
        scanf("%d", &choice);

        if (choice == 1)
            insertPortal();
        else if (choice == 2)
            deletePortal();
        else if (choice == 3)
            displayPortals();
        else if (choice == 4)
            linearSearchPortal();
        else if (choice == 5)
            enqueuePlayer();
        else if (choice == 6)
            dequeuePlayer();
        else if (choice == 7)
        {
            printf("Portal node ID: ");
            scanf("%d", &id);

            root = insertNode(root, id);

            printf("Portal network (Inorder): ");
            inorder(root);
            printf("\n");
        }
        else if (choice == 8)
        {
            printf("Portal node ID: ");
            scanf("%d", &id);

            if (searchNode(root, id))
                printf("Portal node found.\n");
            else
                printf("Portal node not found.\n");
        }
        else if (choice == 9)
            printf("Program closed.\n");
        else
            printf("Invalid choice.\n");
    }

    return 0;
}
