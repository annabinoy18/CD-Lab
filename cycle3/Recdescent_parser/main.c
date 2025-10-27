#include <stdio.h>
#include <string.h>

char inp[100];
int len = 0;
int curr = 0;

// Function prototypes for the new grammar structure
int E();
int E_prime(); // E' for '+', '-'
int T();
int T_prime(); // T' for '*', '/'
int F();       // F for 'i' or '(E)'

int main()
{
    printf("Enter input (using i, +, *, /, ()): \n");
    if (scanf("%s", inp) != 1) return 1;

    len = strlen(inp); // Use strlen for simplicity
    
    int res = E();
    
    if (res == 1 && curr == len)
        printf("Input has been accepted (Valid Expression).\n");
    else
        printf("Input has been rejected (Invalid Expression).\n");
    
    return 0;
}

// E -> T E'  (Highest Level: Handles +, -)
int E()
{
    // E must start with a T
    if (T() == 1) {
        // Then continue with E'
        return E_prime();
    }
    return -1;
}

// E' -> + T E' | - T E' | epsilon
int E_prime()
{
    // Try to match '+' or '-'
    if (inp[curr] == '+' || inp[curr] == '-')
    {
        curr++; // Consume the operator (+ or -)
        
        // E' must be followed by a T
        if (T() == 1) {
            // Then recursively call E' to handle more operations
            return E_prime();
        }
        return -1; // Failed to match T after the operator
    }
    
    // E' -> epsilon (Empty String)
    // If we don't find '+' or '-', it's a successful match of the empty production.
    return 1;
}

// T -> F T' (Intermediate Level: Handles *, /)
int T()
{
    // T must start with an F
    if (F() == 1) {
        // Then continue with T'
        return T_prime();
    }
    return -1;
}

// T' -> * F T' | / F T' | epsilon
int T_prime()
{
    // Try to match '*' or '/'
    if (inp[curr] == '*' || inp[curr] == '/')
    {
        curr++; // Consume the operator (* or /)
        
        // T' must be followed by an F
        if (F() == 1) {
            // Then recursively call T' to handle more operations
            return T_prime();
        }
        return -1; // Failed to match F after the operator
    }
    
    // T' -> epsilon (Empty String)
    // If we don't find '*' or '/', it's a successful match of the empty production.
    return 1;
}

// F -> i | (E) (Base Level: Operands)
int F()
{
    // F -> i (identifier)
    if (inp[curr] == 'i')
    {
        curr++; // Consume 'i'
        return 1;
    }
    
    // F -> (E) (parenthesized expression)
    if (inp[curr] == '(')
    {
        curr++; // Consume '('
        
        if (E() == 1) { // Parse the expression inside the parentheses
            if (inp[curr] == ')') {
                curr++; // Consume ')'
                return 1;
            }
            // Mismatch: '(' was opened but ')' is missing
        }
    }
    
    return -1;
}

/*
Enter input (using i, +, *, /, ()): 
i+(i*i)-i
Input has been accepted (Valid Expression).
*/
