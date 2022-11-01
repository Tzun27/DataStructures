#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10000

void initHeap(int h[], int *elements)
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        h[i] = 0;
    }

    *elements = -1;
}

void bubbleUp(int h[], int index)
{
    if (index == 0)
    {
        return;
    }

    if (h[index] < h[(index - 1) / 2])
    {
        int temp;
        temp = h[index];
        h[index] = h[(index - 1) / 2];
        h[(index - 1) / 2] = temp;

        bubbleUp(h, (index - 1) / 2);
    }
}

void bubbleDown(int h[], int index, int *elements)
{
    int child;
    int min_index;

    child = 2 * index + 1;
    min_index = index;

    for (int i = 0; i < 2; i++)
    {
        if (child + i <= *elements)
        {
            if (h[min_index] > h[child + i])
            {
                min_index = child + i;
            }
        }
    }

    if (min_index != index)
    {
        int temp;
        temp = h[index];
        h[index] = h[min_index];
        h[min_index] = temp;
        bubbleDown(h, min_index, elements);
    }
}

void insert(int h[], int *elements, int n)
{
    if (*elements >= MAX_SIZE)
    {
        printf("Heap Overflow\n");
        exit(1);
    }
    else
    {
        *elements += 1;
        h[*elements] = n;
        bubbleUp(h, *elements);
    }
}

void removeMin(int h[], int *elements)
{
    int min;
    if (*elements == -1)
    {
        printf("empty\n");
    }
    else
    {
        min = h[0];
        printf("%d\n", min);
        h[0] = h[*elements];
        h[*elements] = 0;
        *elements -= 1;
        bubbleDown(h, 0, elements);
    }

}

void change(int h[], int *elements, int index, int replacement)
{
    if (index > *elements || index < 0)
    {
        printf("out of range\n");
    }
    else
    {
        h[index] = replacement;
        bubbleDown(h, index, elements);
        bubbleUp(h, index);
    }
}

int main()
{
    char input[10000], command[100];
    int index, value;

    int minHeap[MAX_SIZE];
    int *elements = (int *)malloc(sizeof(int));

    initHeap(minHeap, elements);

    while (1)
    {
        fgets(input, sizeof(input) / sizeof(char), stdin);
        char *t = strtok(input, " ");
        strcpy(command, t);
        

        if (strcmp(t, "insert") == 0)
        {
            char* ptr;
            t = strtok(NULL, " ");
            value = strtol(t, &ptr, 10);
        }
        else if (strcmp(t, "change") == 0)
        {
            char* ptr;
            t = strtok(NULL, " ");
            t = strtok(t, ",");
            index = strtol(t, &ptr, 10);
            t = strtok(NULL, ",");
            value = strtol(t, &ptr, 10);
        }
        else
        {
            command[strlen(command) - 1] = '\0';
        }

        if (strcmp(command, "insert") == 0)
        {
            insert(minHeap, elements, value);
        }
        else if (strcmp(command, "remove") == 0)
        {
            removeMin(minHeap, elements);
        }
        else if (strcmp(command, "change") == 0)
        {
            change(minHeap, elements, index, value);
        }
        else if (strcmp(command, "quit") == 0)
        {
            exit(0);
        }
        else
        {
            printf("Invalid command\n");
        }
    }

    return 0;
}