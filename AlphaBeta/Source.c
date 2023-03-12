#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>

typedef struct Move
{
    int row, col;
}Move;

char computer = 'X', om = '0';
int tura = 0;
char board[3][3] =
{
    { '_', '_', '_' },
    { '_', '_', '_' },
    { '_', '_', '_' }
};
#define inf 999;
#define maximizing 1
#define minimising 0
bool isMovesLeft(char board[3][3])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == '_')
                return true;
    return false;
}

int evaluate(char b[3][3])
{
    for (int row = 0; row < 3; row++)
    {
        if (b[row][0] == b[row][1] &&
            b[row][1] == b[row][2])
        {
            if (b[row][0] == computer)
                return 2;
            else if (b[row][0] == om)
                return 1;
        }
    }

    // Checking for Columns for X or O victory.
    for (int col = 0; col < 3; col++)
    {
        if (b[0][col] == b[1][col] &&
            b[1][col] == b[2][col])
        {
            if (b[0][col] == computer)
                return 2;

            else if (b[0][col] == om)
                return 1;
        }
    }

    if (b[0][0] == b[1][1] && b[1][1] == b[2][2])
    {
        if (b[0][0] == computer)
            return 2;
        else if (b[0][0] == om)
            return 1;
    }

    if (b[0][2] == b[1][1] && b[1][1] == b[2][0])
    {
        if (b[0][2] == computer)
            return 2;
        else if (b[0][2] == om)
            return 1;
    }

    return 0;
}

int min(int a, int b)
{
    if (a <= b)
        return a;
    else return b;
}
int max(int a, int b)
{
    if (a > b)
        return a;
    else return b;
}
int alphaBeta(int level,int alpha,int beta)
{
    int scor = evaluate(board);
    if (scor == 2)
        return 1;
    if (scor == 1)
        return -1;
    if (!isMovesLeft(board))
        return 0;
    if (level%2==minimising) {
        int value = inf;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '_') {
                    board[i][j] = computer;
                    value = min(value, alphaBeta(level+1, alpha, beta));
                    board[i][j] = '_';
                }
            }
                beta = min(value, beta);
                if (alpha >= beta)
                    break;
        }
        return value;
    }
    else {
        int value = -inf;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '_') {
                    board[i][j] = om;
                    value = max(value, alphaBeta(level+1,alpha,beta));
                    board[i][j] = '_';
                }
            alpha = max(alpha, value);
            if (alpha >= beta)
                break;
            }
        return value;
    }
}
Move findBestMove(char board[3][3])
{
    int bestVal = -1000;
    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == '_')
            {
                board[i][j] = computer;
                int alpha = 0;
                int beta = inf;
                int moveVal = alphaBeta(0,alpha, beta);
                board[i][j] = '_';
                if (moveVal > bestVal)
                {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    return bestMove;
}

void printTabela()
{
    printf(" \t0 1 2\n");
    for (int i = 0; i < 3; i++)
    {
        printf("%d\t", i);
        for (int j = 0; j < 3; j++)
        {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
void play_game()
{
    Move bestMove;
    int c1, c2;
    while (!evaluate(board) && isMovesLeft(board))
    {
        if (tura % 2 == 0)
        {
            bestMove = findBestMove(board);
            board[bestMove.row][bestMove.col] = computer;
            printTabela();
        }
        if (tura % 2 == 1)
        {
            printf("Introduceti linia si coloana:");
            scanf("%d %d", &c1, &c2);
            while (board[c1][c2] != '_')
            {
                printf("Introduceti linia si coloana:");
                scanf("%d %d", &c1, &c2);
            }
            board[c1][c2] = om;
            printTabela();
        }
        tura++;
    }
}
int main()
{
    printTabela();
    play_game();
    if (evaluate(board) == 2)
        printf("Computerul a castigat !");
    else if (evaluate(board) == 1)
        printf("Jucatorul a castigat !");
    else printf("Este REMIZA!");
}