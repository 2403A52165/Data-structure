#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100000

typedef struct Node {
    char data[1000];
    struct Node *next;
} Node;

/* Push a value onto the stack */
void push(Node **top, const char *value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    strcpy(newNode->data, value);
    newNode->next = *top;
    *top = newNode;
}

/* Pop and RETURN the node (caller must free) */
Node* pop(Node **top) {
    if (*top == NULL)
        return NULL;
    Node *temp = *top;
    *top = (*top)->next;
    temp->next = NULL;
    return temp;
}

/* Count nodes in stack */
int stackSize(Node *top) {
    int count = 0;
    while (top) {
        count++;
        top = top->next;
    }
    return count;
}

/* Remove the BOTTOM (oldest) node */
void removeBottom(Node **top) {
    if (*top == NULL)
        return;
    if ((*top)->next == NULL) {
        free(*top);
        *top = NULL;
        return;
    }
    Node *cur = *top;
    while (cur->next->next != NULL)
        cur = cur->next;
    free(cur->next);
    cur->next = NULL;
}

/* Free all nodes in stack */
void clearStack(Node **top) {
    while (*top != NULL) {
        Node *temp = *top;
        *top = (*top)->next;
        free(temp);
    }
}

/* Remove the last `len` characters from design string */
void removeLast(char *design, int len) {
    int cur = (int)strlen(design);
    if (len > cur) len = cur;   // safety clamp
    design[cur - len] = '\0';
}

int main() {
    int K, n;

    if (scanf("%d", &K) != 1 || scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    Node *undo = NULL;
    Node *redo = NULL;

    char *design = (char*)calloc(MAX, sizeof(char));
    if (!design) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    int discarded = 0;
    char command[20];
    char value[1000];

    for (int i = 0; i < n; i++) {
        if (scanf("%19s", command) != 1) break;

        if (strcmp(command, "MODIFY") == 0) {
            if (scanf("%999s", value) != 1) break;

            /* If undo stack is at capacity, drop oldest entry */
            if (stackSize(undo) >= K) {
                removeBottom(&undo);
                discarded++;
            }

            push(&undo, value);
            clearStack(&redo);          /* New modification wipes redo history */
            strcat(design, value);

        } else if (strcmp(command, "UNDO") == 0) {
            Node *node = pop(&undo);
            if (node) {
                removeLast(design, (int)strlen(node->data));
                push(&redo, node->data);    /* Save for possible REDO */
                free(node);
            }
            /* If nothing to undo, silently skip */

        } else if (strcmp(command, "REDO") == 0) {
            Node *node = pop(&redo);
            if (node) {
                strcat(design, node->data);
                push(&undo, node->data);    /* Re-add to undo stack */
                free(node);
            }
            /* If nothing to redo, silently skip */
        }
    }

    printf("Final Design State: %s\n", design);
    printf("Discarded Operations: %d\n", discarded);

    clearStack(&undo);
    clearStack(&redo);
    free(design);

    return 0;
}
