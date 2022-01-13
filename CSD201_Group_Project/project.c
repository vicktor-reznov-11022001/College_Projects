#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#define N 10


//function prototypes
void node_branch();
void create_Ar_ArT();
void create_conductance_matrix();
void create_matrices();
void cal_ArGArT();
float Determinant(float a[N][N],int n);
void cal_node_voltages();
void cal_branch_voltages();
void cal_branch_currents();
void menu();
void check(int n);

//global variables
    float A[N][N]; //Incidence matrix
    float Ar[N][N]; // Reduced incidence matrix
    float ArT[N][N]; //transpose of incidence matrix
    int R,C; // max rows & max columns
    float det;
    float Ib[N]; //branch current matrix
    float It[N]; //current matrix
    float Vn[N]; //node voltage matrix
    float Vb[N]; //branch voltage matrix
    float G[N][N]; //conductance matrix
    float ArG[N][N]; //matrix of product of [Ar][G]
    float ArGArT[N][N]; //matrix product of [ArG][ArT]
    float Crammer[N][N]; //matrix for using Crammer's rule
    int r,c,k,j; //variables for traversing the 2D arrays
    int ch;

int main(void)
{
    printf("*****| WELCOME TO CIRCUIT SOLVER |*****\n\n");
    printf("***THIS IS USED TO SOLVE CIRCUITS WITH INDEPENDENT SOURCES***\n\n");

    printf("\n\nStep 1. Creation of the Incidence Matrix:\n");
    create_Ar_ArT();
    Sleep(1);
    printf("\n.\n");
    sleep(1);
    printf(".\n");
    sleep(1);
    printf("DONE!\n");

    printf("\nStep 2. Creation of Conductance Matrix:\n");
    create_conductance_matrix();
    sleep(1);
    printf(".\n");
    sleep(1);
    printf(".\n");
    sleep(1);
    printf("DONE!\n");

    printf("\nStep 3. Creation of independent current matrix:\n");
    create_matrices();
    sleep(1);
    printf(".\n");
    sleep(1);
    printf(".\n");
    sleep(1);
    printf("DONE!\n");

    printf("\nStep 4. Calculation of node voltages:\n");
    cal_node_voltages();
    sleep(1);
    printf(".\n");
    sleep(1);
    printf(".\n");
    sleep(1);
    printf("DONE!\n");

    printf("\nStep 5. Calculation of branch voltages and currents:\n");
    cal_branch_voltages();
    cal_branch_currents();
    sleep(1);
    printf(".\n");
    sleep(1);
    printf(".\n");
    sleep(1);
    printf("DONE!\n");

    menu();
}

void check(int n)
{
    switch (n)
        {
        case 1:
            {
            printf("\nDisplaying node voltages\n");
            for(r=0;r<R-1;r++)
                printf("Node %d : %.3f   units\n",r+1,Vn[r]);
            menu();
            }
        break;
        case 2:
            {
            printf("\nDisplaying branch voltages\n");
            for(r=0;r<C;r++)
                printf("Branch %d : %.3f   units\n",r,Vb[r]);
            menu();
            }
        break;
        case 3:
            {
            printf("\nDisplaying branch currents\n");
            for(r=0;r<C;r++)
                printf("Branch %d : %.3f   units\n",r,Ib[r]);
            printf("\t\t\t ALERT\n If current value is negative then it simply means assumption of direction was wrong. No need to panic.\n");
            menu();
            }
        break;
        case 4:
            {
            printf("\n***CLEARING ALL MEMORY***\n");
            sleep(1);
            printf(".\n");
            sleep(1);
            printf(".\n");
            sleep(1);
            printf("Memory deallocated. Press any key to exit.");
            }
        break;
        default:
            {
            printf("\nERROR!!!!!\n***Enter a valid input***");
            menu();
            }
            // code to be executed if n doesn't match any cases
        }
}

void menu()
{
    printf("\n1. Display node voltages. \t  2. Display brnach voltages.\n");
    printf("3. Display branch currents. \t4. Exit.");
    printf("\nEnter your choice: ");
    scanf("%d",&ch);
    check(ch);
}


//max nodes will decide max number of rows (R)
//max branches will decide max number of columns (C)
void node_branch()
{
    printf("\nPlease Enter the number of nodes in the circuit: ");
    scanf("%d",&R);
    printf("Please Enter the number of branches in the circuit: ");
    scanf("%d",&C);
    printf("\nNumber of nodes:%d\nNumber of branches:%d\n",R,C);
}

//function to create the reduced incidence matrix [Ar] and its transpose [ArT]
void create_Ar_ArT()
{
    node_branch();

    printf("\n\t\t\tALERT\nPlease enter 1 if current is incident on the node\nPlease enter -1 if current is leaving the node\nPlease enter 0 if the branch and node have no connection\n");
//input from user
    for(r=0;r<R;r++)
        for(c=0;c<C;c++)
            {
            printf("Enter the value for [%d][%d] ([NODE][BRANCH]): ",r,c);
            scanf("%f",&A[r][c]);
            }

    sleep(1);
    printf(".\n");
    sleep(1);
    printf(".\n");
    sleep(1);
    printf("Incidence Matrix created.\n");
    printf("The Incidence Matrix:\n");
    for(int r=0;r<R;r++)
        {
        for(int c=0;c<C;c++)
            printf("%.2f  ",A[r][c]);
        printf("\n");
        }

//forming [Ar] and [ArT]
    for(r=0;r<R-1;r++)
        for(c=0;c<C;c++)
            {
            Ar[r][c]=A[r+1][c];
            ArT[c][r]=Ar[r][c];
            }
    sleep(1);
    printf(".\n");
    sleep(1);
    printf(".\n");
    sleep(1);
    printf("Reduced Incidence Matrix created.\nTranspose of Reduced Incidence Matrix created.\n");
}

//function to create the conductance matrix [G]
void create_conductance_matrix()
{

    for(r=0;r<C;r++)
        for(c=0;c<C;c++)
            {
            G[r][c] = 0;
            }

//input from user
    for(int i=0;i<C;i++)
    {


             printf("\nEnter the value of Resistance For branch number %d :\n",i);
            float q ;
            scanf("%f",&q);
            if (q != 0)
                G[i][i] = 1/q;
            else
            {
              printf("Please Review Graph Of Circuit for branch %d\n\n",i);
              exit(0);
            }

            printf("\n");

    }

    printf("The Conductance Matrix:\n");
    for(int i=0;i<C;i++)
        {
        for(int j=0;j<C;j++)
            {
            printf("%.4f   ",G[i][j]);
            }
        printf("\n");
        }
}

//function to create matrices [It]
void create_matrices()
{
    printf("Enter value of currents from external sources associated with the node numbers");
    printf("\n\t\t\t ALERT \nCurrent entering the node is considered POSITIVE. \nCurrent leaving the node is considered NEGATIVE.\n");
    for(c=0;c<R-1;c++)
        {
        printf("Enter the current associated with node %d: " ,c+1);
        scanf("%f",&It[c]);
        }
    printf("\nIndependent current matrix created.");
}

void cal_ArGArT()
 {
//PART 1: [Ar][G]=[ArG]

    for(r=0;r<R-1;r++)
        for(c=0;c<C;c++)
            ArG[r][c]=0;

    //matrix multiplication
	for(r = 0; r < R-1;r++)
		for(c= 0; c < C; c++)
			for(k=0; k<C;k++)
				ArG[r][c] += Ar[r][k] * G[k][c];

//PART 2: [ArG][ArT]=[ArGArT]
    for(r=0;r<R-1;r++)
        for(c=0;c<R-1;c++)
            ArGArT[r][c]=0;

   //matrix multiplication
	for(r = 0; r < R-1;r++)
		for(c= 0; c < R-1; c++)
			for(k=0; k<C;k++)
				ArGArT[r][c] += ArG[r][k] * ArT[k][c];

}

float Determinant(float a[N][N], int f)
{
  float s = 1, b[N][N];
  int i, j, m, n;
  if (f == 1)
    {
     return (a[0][0]);
    }
  else
    {
     det = 0;
     for (c = 0; c < f; c++)
       {
        m = 0;
        n = 0;
        for (i = 0;i < f; i++)
            {
            for (j = 0 ;j < f; j++)
                {
                b[i][j] = 0;
                if (i != 0 && j != c)
                    {
                    b[m][n] = a[i][j];
                    if (n < (f - 2))
                        n++;
                    else
                        {
                        n = 0;
                        m++;
                        }
                    }
                }
            }
        det = det + s * (a[0][c] * Determinant(b, f - 1));
        s = -1 * s;
        }
    }

    return (det);
}


//function to calculate node voltages
void cal_node_voltages()
{
    cal_ArGArT();
    for(k=0;k<R-1;k++)
        {
//assigning values
        for(r=0;r<R-1;r++)
            for(c=0;c<R-1;c++)
                {
                if(c==k)
                    Crammer[r][c]=It[r];
                else
                    Crammer[r][c]=ArGArT[r][c];
                }

//assigning values to node voltages
        Vn[k]=Determinant(Crammer,R-1)/Determinant(ArGArT,R-1);
        }
}

//function to calculate branch voltages
void cal_branch_voltages()
{
    for(r=0;r<C;r++)
        {
        Vb[r]=0;
        for(c=0;c<R-1;c++)
            Vb[r]+=ArT[r][c]*Vn[c];
        }
}

//function to calculate branch currents
void cal_branch_currents()
{
    for(r=0;r<C;r++)
        {
        Ib[r]=0;
        for(c=0;c<C;c++)
            Ib[r]+=G[r][c]*Vb[c];
        }
}
