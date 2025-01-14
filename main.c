#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structure for a node in the linked list
struct Node {
    int data;
    struct Node* next;
};

// Forward declaration of printList function
void printList(struct Node* head);

//function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

//function to insert a new node at the beginning of the list
void push(struct  Node** head, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
    printf("Node inserted successfully\n");
    printList(*head);
}

//function to delete a node from the beginning of the list
void pop(struct Node** head) {
    if (*head == NULL) {
        printf("list is empty\n");
        return;
    }
    struct Node* temp = *head;
    *head = (*head)->next;
    free(temp);
    printf("Node deleted successfully\n");
    printList(*head);
}

//function to delete a node from the end of the list
void deleteFromEnd(struct Node** head) {
    if (*head == NULL) {
        printf("list is empty\n");
        return;
    }
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        printf("Node deleted successfully\n");
        printList(*head);
        return;
    }
    struct Node* temp = *head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    free(temp->next);
    temp->next = NULL;
    printf("Node deleted successfully\n");
    printList(*head);
}

//function to delete a node by index
void deleteByIndex(struct Node** head, int index) {
    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }
    if (index == 0) {
        pop(head);
        return;
    }
    struct Node* temp = *head;
    for (int i = 0; temp != NULL && i < index - 1; i++) {
        temp = temp->next;
    }
    if (temp == NULL || temp->next == NULL) {
        printf("Index out of bounds\n");
        return;
    }
    struct Node* to_delete = temp->next;
    temp->next = temp->next->next;
    free(to_delete);
    printf("Node deleted successfully\n");
    printList(*head);
}

//function to delete a node by value
void deleteByValue(struct Node** head, int value) {
    if (*head == NULL) {
        printf("List is empty.\n");
        return;
    }
    if ((*head)->data == value) {
        pop(head);
        return;
    }
    struct Node* temp = *head;
    while (temp->next != NULL && temp->next->data != value) {
        temp = temp->next;
    }
    if (temp->next == NULL) {
        printf("Value not found in the list.\n");
        return;
    }
    struct Node* to_delete = temp->next;
    temp->next = temp->next->next;
    free(to_delete);
    printf("Node deleted successfully\n");
    printList(*head);
}

//function to search for a value in the list
int search(struct Node* head, int value) {
    int index = 0;
    struct Node* temp = head;
    while (temp != NULL) {
        if (temp->data == value) {
            return index;
        }
        temp = temp->next;
        index++;
    }
    return -1; //value not found
}

//function to print the list
void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

//function to read values from a file
void readFromFile(struct Node** head, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }
    int data;
    while (fscanf(file, "%d", &data) != EOF) {
        push(head, data);
    }
    fclose(file);
    printf("Data read from file successfully\n");
    printList(*head);
}

//function to write values to a file
void writeToFile(struct Node* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    struct Node* temp = head;
    while (temp != NULL) {
        fprintf(file, "%d ", temp->data);
        temp = temp->next;
    }
    fprintf(file, "\n");
    fclose(file);
    printf("Data written to file successfully\n");
    printList(head);
}

int main() {
    struct Node* head = NULL;
    int choice, data, index, value;
    char filename[100];

    while (1) {
        printf("\n1. Push\n");
        printf("2. Pop\n");
        printf("3. Delete from end\n");
        printf("4. Delete by index\n");
        printf("5. Delete by value\n");
        printf("6. Search\n");
        printf("7. Print list\n");
        printf("8. Write to file\n");
        printf("9. Read from file\n");
        printf("10. Exit\n");
        printf("Enter your selection: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to push: ");
                scanf("%d", &data);
                push(&head, data);
                break;
            case 2:
                pop(&head);
                break;
            case 3:
                deleteFromEnd(&head);
                break;
            case 4:
                printf("Enter index to delete: ");
                scanf("%d", &index);
                deleteByIndex(&head, index);
                break;
            case 5:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                deleteByValue(&head, value);
                break;
            case 6:
                printf("Enter value to search: ");
                scanf("%d", &value);
                index = search(head, value);
                if (index == -1) {
                    printf("Value not found in the list.\n");
                } else {
                    printf("Value found at index %d\n", index);
                }
                break;
            case 7:
                printList(head);
                break;
            case 8:
                printf("Enter filename: ");
                scanf("%s", filename);
                writeToFile(head, filename);
                break;
            case 9:
                printf("Enter filename to read from: ");
                scanf("%s", filename);
                readFromFile(&head, filename);
                break;
            case 10:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}