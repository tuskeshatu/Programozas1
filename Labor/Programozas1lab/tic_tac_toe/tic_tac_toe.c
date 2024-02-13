
char check(char table[][3])
{
    if (table[1][1] == '.' && table[2][1] == 'X' && table[0][0] == 'X')
        return '\0';
    


    for (int i = 0; i < 3; i++)
        if (table[i][0] == 'X' && table[i][1] == 'X' && table[i][2] == 'X')
            return 'X';

    for (int i = 0; i < 3; i++)
        if (table[i][0] == 'O' && table[i][1] == 'O' && table[i][2] == 'O')
            return 'O';

    for (int i = 0; i < 3; i++)
        if (table[0][i] == 'X' && table[1][i] == 'X' && table[2][i] == 'X')
            return 'X';

    for (int i = 0; i < 3; i++)
        if (table[0][i] == 'O' && table[1][i] == 'O' && table[2][i] == 'O')
            return 'O';

    for (int i = 0; i < 3; i++)
        if (table[i][i] == 'X' && table[i][i] == 'X' && table[i][i] == 'X')
            return 'X';

    for (int i = 0; i < 3; i++)
        if (table[i][i] == 'O' && table[i][i] == 'O' && table[i][i] == 'O')
            return 'O';

    for (int i = 0; i < 3; i++)
        if (table[i][2 - i] == 'X' && table[i][2 - i] == 'X' && table[i][2 - i] == 'X')
            return 'X';

    for (int i = 0; i < 3; i++)
        if (table[i][i] == 'O' && table[i][2 - i] == 'O' && table[i][2 - i] == 'O')
            return 'O';

    return '\0';
}