



int main()
{
    int first = 0;
    int second = 0;
    char op = 0;

    printf("Please Enter the first number : ");
    scanf("%d", &first);

    printf("Please Enter the operation : ");
    scanf(" %c", &op);

    

    printf("Please Enter the second number : ");
    scanf("%d", &second);


    

    

    int res = 0;
    
    switch (op)
    {
    case '+':
        res = first + second;
        break;
    case '-':
        res = first - second;
        break;
    case '*':
        res = first * second;
        break;
    case '/':
        res = first / second;
        break;
    
    default:
        break;
    }

    printf("%d", res);
    printf("\n");
}