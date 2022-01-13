#include<stdlib.h>
#include<stdio.h>

#define MAX_SIZE_ARR 10

struct node
{
    int key;
    struct node *left ;
    struct node *right;
};

void level_order(struct node* root)
{
    int level = height(root) ;
    for (int i = 1; i <= level ; i = i + 1)
        print_current_level(root, i);
}

void print_current_level(struct node* root, int level)
{
    if (root == NULL)
        return ;
    if (level == 1)
        printf("%d ", root->key);
    else if (level > 1)
    {
        print_current_level(root->left, level-1);
        print_current_level(root->right, level-1);
    }
}

struct node* find_func(struct node* root, int key)
{
    if (root == NULL || root->key == key)
       return root;

    if (root->key < key)
      {
          find_func(root->right, key);
          printf("%d ",root->key);
      }

    else
    {
        find_func(root->left, key);
        printf("%d ",root->key);
    }
}

struct node * least_value(struct node* node)
{
    struct node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

int depth_calc(struct node *node, int data, int level)
{
    if (node == NULL)
        return 0;

    if (node->key == data)
        return level ;

    int next_level_left = depth_calc(node->left, data, level+1);
    if (next_level_left != 0)
        return next_level_left ;

    next_level_left = depth_calc(node->right, data, level+1);
    return next_level_left;
}

int depth(struct node *node, int data)
{
    return depth_calc(node,data,1);
}

int height(struct node* node)
{
    if (node == NULL)
        return 0;
    else
    {
        int left_height = height(node->left);
        int right_height = height(node->right);

        if (left_height > right_height)
            return(left_height+1);
        else
            return(right_height+1);
    }
}

struct node *new_Node(int key)
{
    struct node *temp =  (struct node *)malloc(sizeof(struct node));
    temp->key = key;
    temp->left = temp->right = NULL;
    return temp;
}

struct node* build_tree(int arr[], int start, int end)
{
    if (start > end)
      return NULL;

    int root_array = (start + end)/2;
    struct node *root = new_Node(arr[root_array]);

    root->left =  build_tree(arr, start, root_array-1);

    root->right = build_tree(arr, root_array+1, end);

    return root;
}

struct node* rebalance(int arr[], int start, int end)
{
    if (start > end)
      return NULL;

    int root_array = (start + end)/2;
    struct node *root = new_Node(arr[root_array]);

    root->left =  build_tree(arr, start, root_array-1);

    root->right = build_tree(arr, root_array+1, end);

    return root;
}

struct node* unbalanced(int arr[], int start, int end)
{
    if (start > end)
      return NULL;

    int mid = (start + end)/2;
    struct node *root = new_Node(arr[mid]);

    root->left =  build_tree(arr, start, mid-1);

    return root;
}

struct node* insert_func(struct node* node, int key)
{
    if (node == NULL)
        return new_Node(key);

    if (key < node->key)
        node->left  = insert_func(node->left, key);
    else if (key > node->key)
        node->right = insert_func(node->right, key);

    return node;
}

void postorder(struct node* root)
{
     if (root == NULL)
        return ;
     postorder(root->left);
     postorder(root->right);
     printf("%d ", root->key);
}

void inorder(struct node *root)
{
    if (root == NULL)
        return ;
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
}

void preorder(struct node *root)
{
    if (root == NULL)
        return ;
    printf("%d ",root->key);
    preorder(root->left);
    preorder(root->right);
}

int Balanced(struct node* root)
{
    if (root == NULL)
        return 1;

    int lh = height(root->left);
    int rh = height(root->right);

    if (abs(lh - rh) <= 1 && Balanced(root->left) && Balanced(root->right))
        return 1;

    return 0;
}

struct node* delete_func(struct node* root, int key)
{
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = delete_func(root->left, key);

    else if (key > root->key)
        root->right = delete_func(root->right, key);

    else
    {
        if (root->left == NULL)
        {
            struct node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }

        struct node* temp = least_value(root->right);
        root->key = temp->key;
        root->right = delete_func(root->right, temp->key);
    }
    return root;
}

int Tree(arr,n)
{
    int rand_arr = arr ;
    int arr_size  = n ;
    struct node *root = build_tree(rand_arr,0,arr_size-11);
}

void main()
{
    printf("\nThe driver script being executed for the following tasks.\n");
    printf("1. Create a binary search tree from an array of random numbers (make use of rand() function).\n");
    printf("2. Confirm that the tree is balanced by calling ‘balanced’.\n");
    printf("3. Print out all elements in level, pre, post, and in order.\n");
    printf("4. Try to unbalance the tree by adding several numbers > 100.\n");
    printf("5. Confirm that the tree is unbalanced by calling ‘balanced’.\n");
    printf("6. Balance the tree by calling ‘rebalance’.\n");
    printf("7. Confirm that the tree is balanced by calling ‘balanced’.\n");
    printf("8. Print out all elements in level, pre, post, and in order.\n\n");

        int arr[MAX_SIZE_ARR+10] ;
    for(int i = 0 ; i < MAX_SIZE_ARR ; i = i + 1)
            arr[i] = (rand()%89)+10 ;
        int n = sizeof(arr)/sizeof(arr[0]);
       int Tree(arr,n);
       struct node *root = build_tree(arr,0,n-11);

        printf("Create Binary search tree from array of random numbers using random function.\n\n");

        int Balanced(struct node* root);
        if (Balanced(root))
        printf("Tree is balanced\n");
        else
        printf("Tree is not balanced\n");

        printf("\n");

        printf("preorder : ");
        preorder(root);
        printf("\n");
        printf("Inorder : ");
        inorder(root);
        printf("\n");
        printf("Postorder : ");
        postorder(root);
        printf("\n\n");

        for(int i = 10 ; i < MAX_SIZE_ARR+10 ; i = i + 1)
            arr[i] = (rand()%990)+100 ;
        struct node *root1 = unbalanced(arr, 0, n-1);

        printf("Unbalanced the tree by adding several numbers > 100.\n");

        printf("\n");
        int Balanced(struct node* root1);
        if (Balanced(root1))
        printf("Tree is balanced\n");
        else
        printf("Tree is not balanced\n");

        struct node *root2 = rebalance(arr, 0, n-1);

        printf("\n");
        int Balanced(struct node* root2);
        if (Balanced(root2))
        printf("Tree is balanced\n");
        else
        printf("Tree is not balanced\n");

        printf("\n");

        printf("preorder : ");
        preorder(root2);
        printf("\n");
        printf("Inorder : ");
        inorder(root2);
        printf("\n");
        printf("Postorder : ");
        postorder(root2);
        printf("\n\n");

        int choice = 0, data = 0 ;

    while(1)
    {
        printf("\n1 Insert an element ");
        printf("\n2 Delete an element ");
        printf("\n3 Search for an element ");
        printf("\n4 Level Order ");
        printf("\n5 Inorder ");
        printf("\n6 Preorder ");
        printf("\n7 Postorder ");
        printf("\n8 Height ");
        printf("\n9 Depth of node ");
        printf("\n10 Exit ");
        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
                {
        int data ;
        printf("\nEnter your element that you want to insert :\n");
        scanf("%d",&data);
        insert_func(root2,data);
        break;
                }
            case 2:
                {
        int data ;
        printf("\nEnter your element that you want to delete :\n");
        scanf("%d",&data);
        delete_func(root2,data);
        break ;
        }
            case 3:
                {
        int data ;
        printf("Enter element you want to find :\n");
        scanf("%d",&data);
        printf("Element exist after transversal from root node (Last number) : ");
        (find_func(root2,data));
        printf("\n\n");
        break;
                }
            case 10:
                {
                printf("\nExiting...\n");
                return;
		}
            case 8 :
                {
                    printf("\Height of tree : %d\n",height(root2));
                    break ;
                }
            case 5 :
                {
                    printf("Inorder : ");
        inorder(root2);
        printf("\n");
        break ;
                }
            case 6 :
                {
                     printf("Preorder : ");
        preorder(root2);
        printf("\n");
        break ;
                }
            case 7 :
                {
                     printf("Postorder : ");
        postorder(root2);
        printf("\n");
        break ;
                }
            case 4 :
                {
                    printf("Level Order : ");
                    level_order(root2);
        printf("\n");
        break ;
                }
            case 9 :
                {
                    int data ;
                    printf("\nEnter depth of element you want :\n");
                    scanf("%d",&data);
                    printf("\nDepth of element %d : %d\n",data,depth(root2, data));
                    break ;
                }
            default:
                printf("\nEnter a valid choice.\n");

        }
    }

    return 0;
}
