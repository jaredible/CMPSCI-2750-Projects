#ifndef _STACK_H_
#define _STACK_H_ 

struct Stack;

struct Stack *createStack(unsigned capacity);

int isFull(struct Stack *stack);

int isEmpty(struct Stack *stack);

int isDuplicate(struct Stack *stack, int item);

void push(struct Stack *stack, int item);

int pop(struct Stack *stack);

#endif
