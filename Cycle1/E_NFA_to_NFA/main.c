#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

int nStates, nSymbols;
char symbols[MAX];

// Arrays for transitions
int epsilon[MAX][MAX], epCount[MAX];
int nfa[MAX][MAX][MAX], nfaCount[MAX][MAX];
int closure[MAX][MAX], closureSize[MAX];
int result[MAX][MAX][MAX], resultCount[MAX][MAX];

// Function to find the index of a symbol
int symbolIndex(char c) {
    for (int i = 0; i < nSymbols; i++)
        if (symbols[i] == c)
            return i;
    return -1;
}

// DFS to compute epsilon closure
void dfs(int state, int origin) {
    if (!closure[origin][state]) {
        closure[origin][state] = 1;
        closureSize[origin]++;
        for (int i = 0; i < epCount[state]; i++) {
            dfs(epsilon[state][i], origin);
        }
    }
}

// Compute epsilon closure for all states
void computeClosures() {
    for (int i = 0; i < nStates; i++) {
        for (int j = 0; j < nStates; j++)
            closure[i][j] = 0;
        closureSize[i] = 0;
        dfs(i, i);
    }
}

int main() {
    // Initialize all counts to 0
    memset(epCount, 0, sizeof(epCount));
    memset(nfaCount, 0, sizeof(nfaCount));
    memset(resultCount, 0, sizeof(resultCount));

    printf("Enter number of states: ");
    scanf("%d", &nStates);

    printf("Enter number of symbols (excluding ε): ");
    scanf("%d", &nSymbols);

    printf("Enter the symbols: ");
    for (int i = 0; i < nSymbols; i++)
        scanf(" %c", &symbols[i]);

    // Input epsilon transitions
    int numEpsTransitions;
    printf("Enter number of ε-transitions: ");
    scanf("%d", &numEpsTransitions);

    printf("Enter each ε-transition as: from_state to_state\n");
    for (int i = 0; i < numEpsTransitions; i++) {
        int from, to;
        scanf("%d %d", &from, &to);
        epsilon[from][epCount[from]++] = to;
    }

    // Input regular transitions
    int numTransitions;
    printf("Enter number of regular transitions (excluding ε): ");
    scanf("%d", &numTransitions);

    printf("Enter each transition as: from_state symbol to_state\n");
    for (int i = 0; i < numTransitions; i++) {
        int from, to;
        char sym;
        scanf("%d %c %d", &from, &sym, &to);

        int idx = symbolIndex(sym);
        if (idx == -1) {
            printf("Invalid symbol '%c'\n", sym);
            return 1;
        }
        nfa[from][idx][nfaCount[from][idx]++] = to;
    }

    // Compute epsilon closures
    computeClosures();

    // Build new NFA transitions
    for (int s = 0; s < nStates; s++) {
        for (int i = 0; i < nStates; i++) {
            if (closure[s][i]) {
                for (int j = 0; j < nSymbols; j++) {
                    for (int k = 0; k < nfaCount[i][j]; k++) {
                        int dest = nfa[i][j][k];
                        for (int m = 0; m < nStates; m++) {
                            if (closure[dest][m]) {
                                // Add to result if not already present
                                int exists = 0;
                                for (int x = 0; x < resultCount[s][j]; x++) {
                                    if (result[s][j][x] == m) {
                                        exists = 1;
                                        break;
                                    }
                                }
                                if (!exists)
                                    result[s][j][resultCount[s][j]++] = m;
                            }
                        }
                    }
                }
            }
        }
    }

    // Display the equivalent NFA (without ε-transitions)
    printf("\nEquivalent NFA (without ε-transitions):\n");
    for (int s = 0; s < nStates; s++) {
        for (int j = 0; j < nSymbols; j++) {
            printf("q%d --%c--> ", s, symbols[j]);
            if (resultCount[s][j] == 0) {
                printf("∅");
            } else {
                for (int k = 0; k < resultCount[s][j]; k++)
                    printf("q%d ", result[s][j][k]);
            }
            printf("\n");
        }
    }

    return 0;
}


/* Enter number of states: 4
Enter number of symbols (excluding ε): 2
Enter the symbols: a b

Enter number of ε-transitions: 3
Enter each ε-transition as: from_state to_state
0 1
0 2
1 3

Enter number of regular transitions (excluding ε): 4
Enter each transition as: from_state symbol to_state
1 a 1
2 b 2
3 a 2
3 b 1
*/
