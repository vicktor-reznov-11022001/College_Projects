#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ARR_SIZE 5

//Circular Array for Queue
int queue_array[ARR_SIZE] ;
int front = -1, rear = -1 ;

//Check whether queue is full or not
int Check_Queue_Full_Func(){
  if ((front == rear + 1) || (front == 0 && rear == ARR_SIZE - 1))
    return 1;
  return 0;
}

//Check whether queue is empty or not
int Check_Queue_Empty_Func() {
  if (front == -1)
    return 1;
  return 0;
}

//Adding element to queue
void Insert(int element) {
  if (Check_Queue_Full_Func())
    printf("Queue is full !\n") ;
  else {
    if (front == -1)
        front = 0;
    rear = (rear + 1) % ARR_SIZE ;
    queue_array[rear] = element ;
    printf("Inserting %d", element) ;
  }
}

// Removing element to queue
int Remove() {
  int element;
  if (Check_Queue_Empty_Func())
    {
    printf("Remove FAILED due to queue empty.\n");
    return (-1);
  }
  else {
    element = queue_array[front];
    if (front == rear)
        {
      front = -1;
      rear = -1;
    }
    else {
      front = (front + 1) % ARR_SIZE;
    }
    printf("Remove returned %d \n", element);
    return (element);
  }
}

//Displaying the queue
void display() {
  int x = 0 ;
  if (Check_Queue_Empty_Func())
    printf("Remove FAILED due to queue empty.\n");
  else {
    printf("\nQueue is : ");
    for (x = front ; x != rear; x = (x + 1) % ARR_SIZE)
        {
      printf("%d ", queue_array[x]);
    }
    printf("%d \n", queue_array[x]);
  }
}

int main()
{
    //String for storing file name
    char file_name[50];
    scanf("%s",&file_name);
  FILE *filePointer = fopen(file_name,"r");

  //Read the function and value
  char read_function[50] ;
  int read_value ;

  fscanf(filePointer, "%s", &read_function);
  if(!strcmp(&read_function, "Insert"))
    fscanf(filePointer,"%d", &read_value);

    Insert(read_value);
    display();

  fscanf(filePointer, "%s", &read_function);
  if(!strcmp(&read_function, "Insert"))
    fscanf(filePointer,"%d", &read_value);

    Insert(read_value);
    display();

    Remove();
    Remove();
    Remove();

  fclose(filePointer);

  return 0;
}
