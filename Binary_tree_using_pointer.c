#include <stdio.h>
#include <stdlib.h>

// Structure of tree node
struct Node
{
    int data;
    struct Node *left, *right;
};

// Create new node
struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

//////////////////// RECURSIVE TRAVERSALS ////////////////////

void preorder(struct Node *root)
{
    if (root == NULL)
        return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void inorder(struct Node *root)
{
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void postorder(struct Node *root)
{
    if (root == NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

//////////////////// STACK IMPLEMENTATION ////////////////////

#define MAX 100

struct Stack
{
    struct Node *items[MAX];
    int top;
};

void initStack(struct Stack *s)
{
    s->top = -1;
}

int isEmpty(struct Stack *s)
{
    return s->top == -1;
}

void push(struct Stack *s, struct Node *node)
{
    if (s->top == MAX - 1)
        return;
    s->items[++(s->top)] = node;
}

struct Node *pop(struct Stack *s)
{
    if (isEmpty(s))
        return NULL;
    return s->items[(s->top)--];
}

struct Node *peek(struct Stack *s)
{
    if (isEmpty(s))
        return NULL;
    return s->items[s->top];
}

//////////////////// NON-RECURSIVE TRAVERSALS ////////////////////

// Non-recursive Preorder
void preorderNR(struct Node *root)
{
    if (root == NULL)
        return;

    struct Stack s;
    initStack(&s);

    push(&s, root);

    while (!isEmpty(&s))
    {
        struct Node *temp = pop(&s);
        printf("%d ", temp->data);

        if (temp->right)
            push(&s, temp->right);
        if (temp->left)
            push(&s, temp->left);
    }
}

// Non-recursive Inorder
void inorderNR(struct Node *root)
{
    struct Stack s;
    initStack(&s);

    struct Node *current = root;

    while (current != NULL || !isEmpty(&s))
    {
        while (current != NULL)
        {
            push(&s, current);
            current = current->left;
        }

        current = pop(&s);
        printf("%d ", current->data);

        current = current->right;
    }
}

// Non-recursive Postorder (using two stacks)
void postorderNR(struct Node *root)
{
    if (root == NULL)
        return;

    struct Stack s1, s2;
    initStack(&s1);
    initStack(&s2);

    push(&s1, root);

    while (!isEmpty(&s1))
    {
        struct Node *temp = pop(&s1);
        push(&s2, temp);

        if (temp->left)
            push(&s1, temp->left);
        if (temp->right)
            push(&s1, temp->right);
    }

    while (!isEmpty(&s2))
    {
        printf("%d ", pop(&s2)->data);
    }
}

//////////////////// MAIN FUNCTION ////////////////////

int main()
{
    // Creating tree manually
    /*
            1
           / \
          2   3
         / \
        4   5
    */

    struct Node *root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);

    printf("Recursive Traversals:\n");

    printf("Preorder: ");
    preorder(root);

    printf("\nInorder: ");
    inorder(root);

    printf("\nPostorder: ");
    postorder(root);

    printf("\n\nNon-Recursive Traversals:\n");

    printf("Preorder: ");
    preorderNR(root);

    printf("\nInorder: ");
    inorderNR(root);

    printf("\nPostorder: ");
    postorderNR(root);

    return 0;
}