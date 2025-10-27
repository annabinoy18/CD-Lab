#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

int numStates, numSymbols;
int dfa[MAX][MAX];
int finalStates[MAX], numFinal;
int isFinalState[MAX];
int distinguishable[MAX][MAX];
int stateGroup[MAX];
char symbols[MAX];

int isFinal(int state) {
    return isFinalState[state];
}

void minimizeDFA() {
    // Step 1: Mark distinguishable pairs (final vs non-final)
    for (int i = 0; i < numStates; i++) {
        for (int j = 0; j < i; j++) {
            if (isFinal(i) != isFinal(j))
                distinguishable[i][j] = 1;
            else
                distinguishable[i][j] = 0;
        }
    }

    // Step 2: Iteratively mark pairs distinguishable based on transitions
    int changed;
    do {
        changed = 0;
        for (int i = 0; i < numStates; i++) {
            for (int j = 0; j < i; j++) {
                if (distinguishable[i][j]) continue;
                for (int k = 0; k < numSymbols; k++) {
                    int a = dfa[i][k];
                    int b = dfa[j][k];
                    if (a == b) continue;

                    // Order them correctly
                    if (a < b) {
                        int temp = a;
                        a = b;
                        b = temp;
                    }

                    if (distinguishable[a][b]) {
                        distinguishable[i][j] = 1;
                        changed = 1;
                        break;
                    }
                }
            }
        }
    } while (changed);

    // Step 3: Group equivalent states
    int groupNum = 0;
    for (int i = 0; i < numStates; i++)
        stateGroup[i] = -1;

    for (int i = 0; i < numStates; i++) {
        if (stateGroup[i] == -1) {
            stateGroup[i] = groupNum;
            for (int j = i + 1; j < numStates; j++) {
                int a = i > j ? i : j;
                int b = i > j ? j : i;
                if (!distinguishable[a][b])
                    stateGroup[j] = groupNum;
            }
            groupNum++;
        }
    }

    // Step 4: Print minimized DFA
    printf("\nMinimized DFA Groups:\n");
    for (int g = 0; g < groupNum; g++) {
        printf("Group %d: ", g);
        for (int s = 0; s < numStates; s++) {
            if (stateGroup[s] == g)
                printf("q%d ", s);
        }
        printf("\n");
    }

    printf("\nTransitions:\n");
    for (int g = 0; g < groupNum; g++) {
        int rep = -1;
        for (int i = 0; i < numStates; i++) {
            if (stateGroup[i] == g) {
                rep = i;
                break;
            }
        }

        printf("Group %d: ", g);
        for (int k = 0; k < numSymbols; k++) {
            int next = dfa[rep][k];
            printf("--%c--> Group %d ", symbols[k], stateGroup[next]);
        }
        printf("\n");
    }

    printf("\nFinal states of minimized DFA: ");
    for (int g = 0; g < groupNum; g++) {
        for (int i = 0; i < numStates; i++) {
            if (stateGroup[i] == g && isFinal(i)) {
                printf("Group %d ", g);
                break;
            }
        }
    }
    printf("\n");
}

int main() {
    // Initialize arrays
    memset(isFinalState, 0, sizeof(isFinalState));
    memset(distinguishable, 0, sizeof(distinguishable));

    printf("Enter number of DFA states: ");
    scanf("%d", &numStates);

    printf("Enter number of input symbols: ");
    scanf("%d", &numSymbols);

    printf("Enter the input symbols (e.g. a b): ");
    for (int i = 0; i < numSymbols; i++)
        scanf(" %c", &symbols[i]);

    printf("\nEnter DFA transitions (state symbol_index → to_state):\n");
    printf("Example: For symbol %c use 0, for %c use 1, etc.\n", symbols[0], symbols[1]);
    for (int i = 0; i < numStates; i++) {
        for (int j = 0; j < numSymbols; j++) {
            printf("From q%d on %c → ", i, symbols[j]);
            scanf("%d", &dfa[i][j]);
        }
    }

    printf("\nEnter number of final states: ");
    scanf("%d", &numFinal);

    printf("Enter final states: ");
    for (int i = 0; i < numFinal; i++) {
        scanf("%d", &finalStates[i]);
        isFinalState[finalStates[i]] = 1;
    }

    minimizeDFA();
    return 0;
}

/*
Enter number of DFA states: 4
Enter number of input symbols: 2
Enter the input symbols (e.g. a b): a b

Enter DFA transitions (state symbol_index → to_state):
Example: For symbol a use 0, for b use 1, etc.
From q0 on a → 1
From q0 on b → 2
From q1 on a → 0
From q1 on b → 3
From q2 on a → 3
From q2 on b → 0
From q3 on a → 2
From q3 on b → 1

Enter number of final states: 2
Enter final states: 2 3

Minimized DFA Groups:
Group 0: q0 q1 
Group 1: q2 q3 

Transitions:
Group 0: --a--> Group 0 --b--> Group 1 
Group 1: --a--> Group 1 --b--> Group 0 

Final states of minimized DFA: Group 1 
*/
