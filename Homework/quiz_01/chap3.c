#include <stdio.h>
#include <math.h>
#include <stdbool.h>

void quiz4();
void quiz5();
void quiz6();
void quiz7();
void quiz8();
void quiz9();
void quiz10();
void quiz11();
void quiz12();

void main()
{
    bool isGameOver = false;
    int num;

    printf("���Ӽ���Ʈ�����а� - 5723717 - ��ȫ��\n\n");

    while (!isGameOver)
    {
        printf("������ ��ȣ(4 ~ 12)�� �Է��ϼ���(0�� �Է��ϸ� ����): ");
        scanf_s("%d", &num);

        switch (num)
        {
        case 0:
            printf("\n���α׷��� �����մϴ�.\n");
            printf("\n���Ӽ���Ʈ�����а� - 5723717 - ��ȫ��\n");
            isGameOver = true;
            break;

        case 4: quiz4();
            break;

        case 5: quiz5();
            break;

        case 6: quiz6();
            break;

        case 7: quiz7();
            break;

        case 8: quiz8();
            break;

        case 9: quiz9();
            break;

        case 10: quiz10();
            break;

        case 11: quiz11();
            break;

        case 12: quiz12();
            break;

        default:
            printf("���ڸ� �߸� �Է��Ͽ����ϴ�.\n");
        }
    }
}

void quiz4()
{
    printf("Quiz 4 : \n");

    int two[10];

    for (int i = 0; i < 10; i++)
    {
        two[i] = pow(2, i);
    }

    for (int i = 0; i < 10; i++)
    {
        printf("two[%d]�� ��: %d\n", i, two[i]);
    }
}

void quiz5()
{
    printf("Quiz 5 : \n");

    printf("struct Person\n");
    printf("{\n");
    printf("    char name[10];\n");
    printf("    int age;\n");
    printf("    float salary;\n");
    printf("};\n");

   struct Person
    {
        char name[10];
        int age;
        float salary;
    };
}

void quiz6()
{
    printf("Quiz 6 : \n");

    typedef struct Complex
    {
        float real;
        float imaginary;
    } Complex;

    Complex c1;
    Complex c2;

    printf("typedef struct Complex\n");
    printf("{\n");
    printf("    float real;\n");
    printf("    float imaginary;\n");
    printf("} Complex;\n");
    printf("\n");
    printf("Complex c1;\n");
    printf("Complex c2;\n");
}

void quiz7()
{
    
}

void quiz8()
{

}

void quiz9()
{

}

void quiz10()
{

}

void quiz11()
{

}

void quiz12()
{

}

