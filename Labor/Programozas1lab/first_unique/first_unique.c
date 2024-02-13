int first_unique(char str[])
{
    for (int i = 0; str[i] != '\0'; i++)
        for (int j = i + 1;; j++)
        {
            if (j == i)
                return i;
            if (str[j] == str[i])
                break;
            if (str[j] == '\0')
                j = -1;
        }
    return -1;
}

int main(void)
{
    char fasz[] = "alma";
    int kuksi = first_unique(fasz);
    return 0;
}