#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#define M 50000
#define T 5000
#define B 1000
#define V 15
#define S 5
#define H 3

void dodawanie(int* num1, int* num2, int* sum, int* cout, int l1, int l2)
{
    int f = 0;
    int carry = 0;
    int fd1 = l1 - 1;
    int fd2 = l2 - 1;



    for (; fd1 >= 0 && fd2 >= 0; fd1--, fd2--, f++)
    {
        sum[f] = (num1[fd1] + num2[fd2] + carry) % 10;
        carry = (num1[fd1] + num2[fd2] + carry) / 10;
        if (fd1 == 0 && fd2 == 0 && carry != 0)
        {
            f++;
            sum[f] = carry;
        }
    }


    if (l1 > l2)
    {

        while (fd1 >= 0)
        {
            sum[f] = (num1[fd1] + carry) % 10;
            carry = (num1[fd1] + carry) / 10;
            f++;
            fd1--;

        }
        if (carry != 0)
        {
            f++;
            sum[f] = carry;
        }
    }
    else if (l2 > l1)
    {
        while (fd2 >= 0)
        {
            sum[f] = (num2[fd2] + carry) % 10;
            carry = (num2[fd2] + carry) / 10;
            f++;
            fd2--;
        }

        if (carry != 0)
        {
            f++;
            sum[f] = carry;
        }
    }

    cout[0] = f;
    if (sum[f] == 0) cout[0]--;
}

void shortpalindrom(int* cout, int* modified, int* nulled)
{
    int licz = 0;
    int e = cout[0];
    for (; e >= 0; e--, licz++)
    {
        modified[licz] = nulled[e];
        nulled[e] = 0;
    }
}

void iloczyn(int* num1, int* num2, int* suma, int* cout, int l1, int l2)
{
    int f = 0;
    int i = 0;
    int help = 0;
    int t = 0;
    int fd1 = l1 - 1;
    int fd2 = l2 - 1;



    for (; fd2 >= 0; fd2--, f++, i++)
    {
        for (; fd1 >= 0; fd1--, f++)
        {
            suma[f] += num1[fd1] * num2[fd2];
            t = f;

            for (; suma[t] >= 10; t++)
            {
                help = suma[t];
                suma[t] = suma[t] % 10;
                suma[t + 1] += help / 10;
            }

        }
        t = 0;
        cout[0] = f;
        f = 0 + i;
        fd1 = l1 - 1;

    }


    while (suma[cout[0]] <= 0)
    {
        cout[0]--;
    }


}

void power(int* num1, int* num2, int* suma, int* cout, int* arrpot, int l1, int l2, int lpow)
{
    int pow = 0;
    int b = 1;

    iloczyn(num1, num2, suma, cout, l1, l2);
    shortpalindrom(cout, num1, suma);

    lpow--;
    for (; lpow >= 0; lpow--)
    {
        pow += (arrpot[lpow] * b);
        b = b * 10;
    }

    for (; pow > 2; pow--)
    {
        iloczyn(num1, num2, suma, cout, cout[0] + 1, l2);
        shortpalindrom(cout, num1, suma);
    }
}

void isbigger(int* num1, int* num2, int* check, int l1, int l2)
{
    int a = 0;
    int fd1 = l1 - 1;

    while (a <= fd1)
    {
        if (fd1 > l2 - 1)
        {
            break;
        }
        else if (fd1 < l2 - 1)
        {
            check[0] = 1;
            break;
        }
        else if (fd1 == l2 - 1)
        {
            if (num1[a] > num2[a])
            {

                break;
            }

            else if (num1[a] == num2[a])
            {
                a++;
            }
            else if (num1[a] < num2[a])
            {
                check[0] = 1;
                break;
            }
        }

    }
}

void sub(int* num1, int* num2, int* suma, int* cout, int* check, int l1, int l2)
{
    int f = 0;
    int fd1 = l1 - 1;
    int fd2 = l2 - 1;
    int borrow = l1 - 2;

    isbigger(num1, num2, check, l1, l2);
    if (check[0] == 1)
    {
        for (; f <= fd1; f++, fd1--)
        {
            suma[f] = num1[fd1];
        }
        cout[0] = f;
        fd2 = -1;
    }

    for (; fd2 >= 0; fd1--, fd2--, f++)
    {

        while (num1[fd1] < num2[fd2])
        {
            while (num1[borrow] == 0) borrow--;
            if (num1[borrow] > 0)
            {
                num1[borrow] -= 1;
                num1[borrow + 1] += 10;
            }
            borrow = fd1 - 1;
        }
        suma[f] = num1[fd1] - num2[fd2];
        borrow--;
    }

    for (; fd1 >= 0; fd1--, f++)
    {
        suma[f] = num1[fd1];
    }

    while (suma[f] == 0)
    {
        f--;
        if (f == 0 && suma[f] == 0)
        {
            break;
        }
    }
    cout[0] = f;
}

void dzielenie(int* num1, int* num2, int* suma, int* wynik, int* cout, int* check, int l1, int l2)
{
    int x = 0;
    int help = 0;
    int help2 = l1;


    sub(num1, num2, suma, cout, check, l1, l2);
    shortpalindrom(cout, num1, suma);



    while (check[0] != 1)
    {
        sub(num1, num2, suma, cout, check, cout[0] + 1, l2);
        shortpalindrom(cout, num1, suma);


        wynik[x] += 1;

        for (; wynik[x] >= 10; x++)
        {
            help = wynik[x];
            wynik[x] = wynik[x] % 10;
            wynik[x + 1] += help / 10;

        }
        x = 0;
        help = 0;

    }

    while (wynik[help2] == 0) help2--;
    cout[1] = help2;
}

void division(int* num1, int* num2, int* temp, int* final, int* suma, int* wynik, int* check, int* cout, int l1, int l2)
{
    int len;
    int r = 0;
    int q;

    check[0] = 0;
    isbigger(num1, num2, check, l1, l2);
    if (check[0] == 1)
    {
        final[0] = 0;
        for (q = 0; q < l1; q++) temp[q] = num1[q];
        cout[0] = q - 1;
        cout[1] = 1;
        return;
    }

    for (len = 0; len < l2; len++) temp[len] = num1[len];


    isbigger(temp, num2, check, len, l2);
    if (check[0] == 1)
    {
        temp[len] = num1[len];
    }
    else
    {
        len--;
    }


    check[0] = 0;
    dzielenie(temp, num2, suma, wynik, cout, check, len + 1, l2);

    for (q = 0; q <= cout[1]; r++, q++)
    {
        final[r] = wynik[q];
        wynik[q] = 0;
    }

    while (num1[len + 1] == 0 && temp[0] == 0 && len < l1 - 1)
    {
        final[r] = 0;
        r++;
        len++;
    }

    if (temp[0] == 0 && (len < l1 - 1)) cout[0] -= 1;
    cout[0] += 1;
    len++;
    temp[cout[0]] = num1[len];

    check[0] = 0;
    isbigger(temp, num2, check, cout[0] + 1, l2);
    while (check[0] == 1 && len <= l1 - 1)
    {
        final[r] = 0;
        cout[0] += 1;
        r++;
        len++;
        temp[cout[0]] = num1[len];
        check[0] = 0;
        isbigger(temp, num2, check, cout[0] + 1, l2);
    }




    while (len <= l1 - 1)
    {
        check[0] = 0;
        dzielenie(temp, num2, suma, wynik, cout, check, cout[0] + 1, l2);


        for (q = 0; q <= cout[1]; r++, q++)
        {
            final[r] = wynik[q];
            wynik[q] = 0;
        }

        while (num1[len + 1] == 0 && temp[0] == 0 && len < l1 - 1)
        {
            final[r] = 0;
            r++;
            len++;
        }


        if (temp[0] == 0 && (len < l1 - 1)) cout[0] -= 1;
        cout[0] += 1;
        len++;
        temp[cout[0]] = num1[len];

        check[0] = 0;
        isbigger(temp, num2, check, cout[0] + 1, l2);
        while (check[0] == 1 && len <= l1 - 1)
        {
            final[r] = 0;
            cout[0] += 1;
            r++;
            len++;
            temp[cout[0]] = num1[len];
            check[0] = 0;
            isbigger(temp, num2, check, cout[0] + 1, l2);
        }

    }
    cout[1] = r - 1;
    cout[0]--;

}

void palindrom(int* cout, int* modified, int* nulled, int i)
{
    int licz = 0;
    int e = cout[i];
    for (; e >= 0; e--, licz++)
    {
        modified[licz] = nulled[e];
        nulled[e] = 0;
    }
}

void palindromone(int* cout, int* modified, int* nulled, int i)
{
    int licz = 0;
    int e = cout[i];
    for (; licz <= e; licz++)
    {
        modified[licz] = nulled[licz];
        nulled[licz] = 0;
    }
}

void inttochar(int index, int* arr)
{
    for (; index >= 0; index--)
    {
        if (arr[index] >= 10)
        {
            arr[index] += 55;
        }
        else if (arr[index] < 10)
        {
            arr[index] += 48;
        }
    }
}

void konwersja_na_n(int* num1, int* num2, int* temp, int* final, int* suma, int* wynik, int* cout, int* check, int* reszty, int l1, int l2)
{
    int index = 0;
    cout[1] = l1 - 1;
    check[1] = 0;
    int help = l1 - 1;
    int reszta1 = 0;
    int reszta2 = 0;
    int system1 = 0;
    int system2 = 0;

    if (l2 == 2) system1 = (num2[l2 - 2] * 10 + num2[l2 - 1]);
    if (l2 == 1) system1 = num2[l2 - 1];
    if (cout[1] == 1) system2 = (num1[cout[1]] + 10 * num1[cout[1] - 1]);
    if (cout[1] == 0) system2 = num1[cout[1]];
    if (cout[1] > 1) system2 = 99;



    if ((l2 == 2 && system1 == 10) || (system1 > system2))
    {
        for (; index <= l1 - 1; help--, index++) reszty[index] = num1[help];
        index--;
        cout[2] = index;
    }
    else
    {

        while (check[0] != 1)
        {
            division(num1, num2, temp, final, suma, wynik, check, cout, cout[1] + 1, l2);

            if (cout[0] == 1)reszty[index] = (temp[cout[0]] + 10 * temp[cout[0] - 1]);
            if (cout[0] == 0)reszty[index] = temp[cout[0]];
            palindromone(cout, num1, final, 1);
            check[0] = 0;
            index++;
            isbigger(num1, num2, check, cout[1] + 1, l2);

        }



        if (cout[1] == 1) reszta1 = (num1[cout[1]] + 10 * num1[cout[1] - 1]);
        if (cout[1] == 0) reszta1 = num1[cout[1]];

        if (l2 == 2) reszta2 = (num2[l2 - 2] + 10 * num2[l2 - 1]);
        if (l2 == 1) reszta2 = num2[l2 - 1];

        reszty[index] = reszta1 % reszta2;

    }
    cout[2] = index;
}

void konwersja_na_dec(int* num1, int* num2, int* num3, int* wynik, int* swap, int* suma, int* cout, int l1, int l2)
{
    int ind = 0;
    int system1 = 0;
    int index = 0;
    int help = l1 - 1;

    if (l2 == 2) system1 = (num2[l2 - 2] * 10 + num2[l2 - 1]);
    if (l2 == 1) system1 = num2[l2 - 1];





    if ((l2 == 2 && system1 == 10) || l1 == 1)
    {
        for (; index <= l1 - 1; help--, index++) wynik[index] = num1[help];
        index--;
        cout[0] = index;
    }
    else
    {
        num3[0] = num1[ind];
        iloczyn(num2, num3, suma, cout, l2, 1);
        shortpalindrom(cout, swap, suma);

        ind = 1;
        for (; ind <= l1 - 1; ind++)
        {
            num3[0] = num1[ind];
            dodawanie(swap, num3, wynik, cout, cout[0] + 1, 1);
            if (ind == l1 - 1) break;
            shortpalindrom(cout, suma, wynik);
            iloczyn(suma, num2, wynik, cout, cout[0] + 1, l2);
            shortpalindrom(cout, swap, wynik);
        }
    }

}

void zerowanie(int* arr, int len)
{
    int a;
    for (a = 0; a < len; a++)
    {
        arr[a] = 0;
    }

}

int dane(char arr[],char sys[])
{
    int i;
    int value = 1;
    for (i = 0; arr[i] != '\0'; i++)
    {
        if (arr[i] < '0' || arr[i]>'Z')
        {
            value = 0;
            return value;
        }
        else if (arr[i] > '9' && arr[i] < 'A')
        {
            value = 0;
            return value;
        }
        else if (sys[1] != '\0')
        {
            if (arr[i] >= sys[1] + 17)
            {
                value = 0;
                return value;
            }
        }
    }
    return value;
}

//dzialania

void multiply(char* s1, char* s2, char* s4, FILE* ptr)
{
    int l1, l2, l4; // l1-arg1 l2-system l4-arg2
    int cout[H];
    int check[H];
    int num3[H]; // pomocnicza do sytemu
    int e;
    int larg1, larg4;
    check[0] = 0;

    for (l1 = 0; s1[l1] != '\0'; l1++);
    for (l2 = 0; s2[l2] != '\0'; l2++);
    for (l4 = 0; s4[l4] != '\0'; l4++);


    int* num1 = (int*)calloc(l1 * B, sizeof(int));
    if (num1 == NULL)
        printf("Couldn't allocate memory");

    int* num2 = (int*)calloc(l2*2, sizeof(int));
    if (num2 == NULL)
        printf("Couldn't allocate memory");

    int* num4 = (int*)calloc(l4 * B, sizeof(int));
    if (num4 == NULL)
        printf("Couldn't allocate memory");

    int* suma = (int*)calloc(l1 * l4 * B, sizeof(int));
    if (suma == NULL)
        printf("Couldn't allocate memory");

    int* wynik = (int*)calloc(l1 * l4 * B, sizeof(int));
    if (wynik == NULL)
        printf("Couldn't allocate memory");

    int* swap = (int*)calloc(l1 * l4 * B, sizeof(int));
    if (swap == NULL)
        printf("Couldn't allocate memory");

    int* reszty = (int*)calloc(l1 * l4 * B, sizeof(int));
    if (reszty == NULL)
        printf("Couldn't allocate memory");
    int* temp = (int*)calloc(l1 * l4 * B, sizeof(int));
    if (temp == NULL)
        printf("Couldn't allocate memory");

    int* final = (int*)calloc(l1 * l4 * B, sizeof(int));
    if (final == NULL)
        printf("Couldn't allocate memory");



    for (l1 = 0; s1[l1] != '\0'; l1++)
    {
        if (s1[l1] >= '0' && s1[l1] <= '9')
        {
            num1[l1] = s1[l1] - '0';
        }
        else
        {
            num1[l1] = s1[l1] - 55;
        }
    }

    for (l2 = 0; s2[l2] != '\0'; l2++)
        num2[l2] = s2[l2] - '0';

    for (l4 = 0; s4[l4] != '\0'; l4++)
    {
        if (s4[l4] >= '0' && s4[l4] <= '9')
        {
            num4[l4] = s4[l4] - '0';
        }
        else
        {
            num4[l4] = s4[l4] - 55;
        }
    }



    konwersja_na_dec(num1, num2, num3, wynik, swap, suma, cout, l1, l2);
    palindrom(cout, num1, wynik, 0);
    larg1 = cout[0];
    cout[0] = 0;
    num3[0] = 0;
    zerowanie(suma, l1 * l4 * B);
    zerowanie(swap, l1 * l4 * B);

    konwersja_na_dec(num4, num2, num3, wynik, swap, suma, cout, l4, l2);
    palindrom(cout, num4, wynik, 0);
    larg4 = cout[0];
    cout[0] = 0;
    num3[0] = 0;
    zerowanie(suma, l1 * l4 * B);
    zerowanie(swap, l1 * l4 * B);

    iloczyn(num1, num4, suma, cout, larg1 + 1, larg4 + 1);
    palindrom(cout, num1, suma, 0);
    zerowanie(wynik, l1 * l4 * B);


    konwersja_na_n(num1, num2, temp, final, suma, wynik, cout, check, reszty, cout[0] + 1, l2);
    inttochar(cout[2], reszty);
    e = cout[2];



    for (; e >= 0; e--) fputc(reszty[e], ptr);
    fprintf(ptr, "\n");
    fprintf(ptr, "\n");
    fprintf(ptr, "\n");
    fprintf(ptr, "\n");



    free(num1);
    free(num2);
    free(suma);
    free(swap);
    free(wynik);
    free(num4);
    free(reszty);
    free(final);
    free(temp);

}

void plus(char* s1, char* s2, char* s4, FILE* ptr)
{
    int l1, l2, l4;// l1-arg1 l2-system l4-arg2
    int larg1, larg4;
    int cout[H];
    int check[H];
    int num3[H]; // pomocnicza do sytemu
    int e = 0;
    check[0] = 0;



    for (l1 = 0; s1[l1] != '\0'; l1++);
    for (l2 = 0; s2[l2] != '\0'; l2++);
    for (l4 = 0; s4[l4] != '\0'; l4++);


    int* num1 = (int*)calloc(l1 * l1 * B, sizeof(int));
    if (num1 == NULL)
        printf("Couldn't allocate memory");

    int* num2 = (int*)calloc(l2*2, sizeof(int));
    if (num2 == NULL)
        printf("Couldn't allocate memory");

    int* num4 = (int*)calloc(l4 * l4 * B, sizeof(int));
    if (num4 == NULL)
        printf("Couldn't allocate memory");

    int* suma = (int*)calloc(l1 * l4 * B, sizeof(int));
    if (suma == NULL)
        printf("Couldn't allocate memory");

    int* wynik = (int*)calloc(l1 * l4 * B, sizeof(int));
    if (wynik == NULL)
        printf("Couldn't allocate memory");

    int* swap = (int*)calloc(l1 * l4 * B, sizeof(int));
    if (swap == NULL)
        printf("Couldn't allocate memory");

    int* reszty = (int*)calloc(l1 * l4 * B, sizeof(int));
    if (reszty == NULL)
        printf("Couldn't allocate memory");
    int* temp = (int*)calloc(l1 * l4 * B, sizeof(int));
    if (temp == NULL)
        printf("Couldn't allocate memory");

    int* final = (int*)calloc(l1 * l4 * B, sizeof(int));
    if (final == NULL)
        printf("Couldn't allocate memory");



    for (l1 = 0; s1[l1] != '\0'; l1++)
    {
        if (s1[l1] >= '0' && s1[l1] <= '9')
        {
            num1[l1] = s1[l1] - '0';
        }
        else
        {
            num1[l1] = s1[l1] - 55;
        }
    }

    for (l2 = 0; s2[l2] != '\0'; l2++)
        num2[l2] = s2[l2] - '0';

    for (l4 = 0; s4[l4] != '\0'; l4++)
    {
        if (s4[l4] >= '0' && s4[l4] <= '9')
        {
            num4[l4] = s4[l4] - '0';
        }
        else
        {
            num4[l4] = s4[l4] - 55;
        }
    }




    konwersja_na_dec(num1, num2, num3, wynik, swap, suma, cout, l1, l2);
    palindrom(cout, num1, wynik, 0);
    larg1 = cout[0];
    cout[0] = 0;
    num3[0] = 0;
    zerowanie(suma, l1 * l4 * B);
    zerowanie(swap, l1 * l4 * B);

    konwersja_na_dec(num4, num2, num3, wynik, swap, suma, cout, l4, l2);
    palindrom(cout, num4, wynik, 0);
    larg4 = cout[0];
    cout[0] = 0;
    num3[0] = 0;
    zerowanie(suma, l1 * l4 * B);
    zerowanie(swap, l1 * l4 * B);

    dodawanie(num1, num4, suma, cout, larg1 + 1, larg4 + 1);
    palindrom(cout, num1, suma, 0);
    zerowanie(wynik, l1 * l4 * B);


    konwersja_na_n(num1, num2, temp, final, suma, wynik, cout, check, reszty, cout[0] + 1, l2);
    inttochar(cout[2], reszty);
    e = cout[2];



    for (; e >= 0; e--) fputc(reszty[e], ptr);
    fprintf(ptr, "\n");
    fprintf(ptr, "\n");
    fprintf(ptr, "\n");
    fprintf(ptr, "\n");




    free(num1);
    free(num2);
    free(suma);
    free(swap);
    free(wynik);
    free(num4);
    free(reszty);
    free(final);
    free(temp);

}

void iloraz(char* s1, char* s2, char* s4, FILE* ptr)
{
    int l1, l2, l4;// l1-arg1 l2-system l4-arg2
    int larg1, larg4;
    int cout[H];
    int check[H];
    int num3[H]; // pomocnicza do sytemu
    int e = 0;
    check[0] = 0;

    for (l1 = 0; s1[l1] != '\0'; l1++);
    for (l2 = 0; s2[l2] != '\0'; l2++);
    for (l4 = 0; s4[l4] != '\0'; l4++);


    int* num1 = (int*)calloc(l1 * l1 * B, sizeof(int));
    if (num1 == NULL)
        printf("Couldn't allocate memory");

    int* num2 = (int*)calloc(l2*2, sizeof(int));
    if (num2 == NULL)
        printf("Couldn't allocate memory");

    int* num4 = (int*)calloc(l4 * l4 * B, sizeof(int));
    if (num4 == NULL)
        printf("Couldn't allocate memory");

    int* suma = (int*)calloc(l1 * l4 * B, sizeof(int));
    if (suma == NULL)
        printf("Couldn't allocate memory");

    int* wynik = (int*)calloc(l1 * l4 * B, sizeof(int));
    if (wynik == NULL)
        printf("Couldn't allocate memory");

    int* swap = (int*)calloc(l1 * l4 * B, sizeof(int));
    if (swap == NULL)
        printf("Couldn't allocate memory");

    int* reszty = (int*)calloc(l1 * l4 * B, sizeof(int));
    if (reszty == NULL)
        printf("Couldn't allocate memory");
    int* temp = (int*)calloc(l1 * l4 * B, sizeof(int));
    if (temp == NULL)
        printf("Couldn't allocate memory");

    int* final = (int*)calloc(l1 * l4 * B, sizeof(int));
    if (final == NULL)
        printf("Couldn't allocate memory");



    for (l1 = 0; s1[l1] != '\0'; l1++)
    {
        if (s1[l1] >= '0' && s1[l1] <= '9')
        {
            num1[l1] = s1[l1] - '0';
        }
        else
        {
            num1[l1] = s1[l1] - 55;
        }
    }

    for (l2 = 0; s2[l2] != '\0'; l2++)
        num2[l2] = s2[l2] - '0';

    for (l4 = 0; s4[l4] != '\0'; l4++)
    {
        if (s4[l4] >= '0' && s4[l4] <= '9')
        {
            num4[l4] = s4[l4] - '0';
        }
        else
        {
            num4[l4] = s4[l4] - 55;
        }
    }



    konwersja_na_dec(num1, num2, num3, wynik, swap, suma, cout, l1, l2);
    palindrom(cout, num1, wynik, 0);
    larg1 = cout[0];
    cout[0] = 0;
    num3[0] = 0;
    zerowanie(suma, l1 * l4 * B);
    zerowanie(swap, l1 * l4 * B);

    konwersja_na_dec(num4, num2, num3, wynik, swap, suma, cout, l4, l2);
    palindrom(cout, num4, wynik, 0);
    larg4 = cout[0];
    cout[0] = 0;
    num3[0] = 0;
    zerowanie(suma, l1 * l4 * B);
    zerowanie(swap, l1 * l4 * B);

    division(num1, num4, temp, final, suma, wynik, check, cout, larg1 + 1, larg4 + 1);
    palindromone(cout, num1, final, 1);
    zerowanie(wynik, l1 * l4 * B);
    zerowanie(temp, l1 * l4 * B);

    check[0] = 0;
    konwersja_na_n(num1, num2, temp, final, suma, wynik, cout, check, reszty, cout[1] + 1, l2);
    inttochar(cout[2], reszty);
    e = cout[2];


    for (; e >= 0; e--) fputc(reszty[e], ptr);
    fprintf(ptr, "\n");
    fprintf(ptr, "\n");
    fprintf(ptr, "\n");
    fprintf(ptr, "\n");


    free(num1);
    free(num2);
    free(suma);
    free(swap);
    free(wynik);
    free(num4);
    free(reszty);
    free(final);
    free(temp);
}

void modulo(char* s1, char* s2, char* s4, FILE* ptr)
{
    int l1, l2, l4;// l1-arg1 l2-system l4-arg2
    int larg1, larg4;
    int cout[H];
    int check[H];
    int num3[H]; // pomocnicza do sytemu
    int e = 0;
    check[0] = 0;

    for (l1 = 0; s1[l1] != '\0'; l1++);
    for (l2 = 0; s2[l2] != '\0'; l2++);
    for (l4 = 0; s4[l4] != '\0'; l4++);


    int* num1 = (int*)calloc(l1 * l1 * B, sizeof(int));
    if (num1 == NULL)
        printf("Couldn't allocate memory");

    int* num2 = (int*)calloc(l2*2, sizeof(int));
    if (num2 == NULL)
        printf("Couldn't allocate memory");

    int* num4 = (int*)calloc(l4 * l4 * B, sizeof(int));
    if (num4 == NULL)
        printf("Couldn't allocate memory");

    int* suma = (int*)calloc(l1 * l4 * B, sizeof(int));
    if (suma == NULL)
        printf("Couldn't allocate memory");

    int* wynik = (int*)calloc(l1 * l4 * B, sizeof(int));
    if (wynik == NULL)
        printf("Couldn't allocate memory");

    int* swap = (int*)calloc(l1 * l4 * B, sizeof(int));
    if (swap == NULL)
        printf("Couldn't allocate memory");

    int* reszty = (int*)calloc(l1 * l4 * B, sizeof(int));
    if (reszty == NULL)
        printf("Couldn't allocate memory");
    int* temp = (int*)calloc(l1 * l4 * B, sizeof(int));
    if (temp == NULL)
        printf("Couldn't allocate memory");

    int* final = (int*)calloc(l1 * l4 * B, sizeof(int));
    if (final == NULL)
        printf("Couldn't allocate memory");



    for (l1 = 0; s1[l1] != '\0'; l1++)
    {
        if (s1[l1] >= '0' && s1[l1] <= '9')
        {
            num1[l1] = s1[l1] - '0';
        }
        else
        {
            num1[l1] = s1[l1] - 55;
        }
    }

    for (l2 = 0; s2[l2] != '\0'; l2++)
        num2[l2] = s2[l2] - '0';

    for (l4 = 0; s4[l4] != '\0'; l4++)
    {
        if (s4[l4] >= '0' && s4[l4] <= '9')
        {
            num4[l4] = s4[l4] - '0';
        }
        else
        {
            num4[l4] = s4[l4] - 55;
        }
    }



    konwersja_na_dec(num1, num2, num3, wynik, swap, suma, cout, l1, l2);
    palindrom(cout, num1, wynik, 0);
    larg1 = cout[0];
    cout[0] = 0;
    num3[0] = 0;
    zerowanie(suma, l1 * l4 * B);
    zerowanie(swap, l1 * l4 * B);

    konwersja_na_dec(num4, num2, num3, wynik, swap, suma, cout, l4, l2);
    palindrom(cout, num4, wynik, 0);
    larg4 = cout[0];
    cout[0] = 0;
    num3[0] = 0;
    zerowanie(suma, l1 * l4 * B);
    zerowanie(swap, l1 * l4 * B);

    division(num1, num4, temp, final, suma, wynik, check, cout, larg1 + 1, larg4 + 1);
    zerowanie(num1, l1 * l4 * B);
    zerowanie(wynik, l1 * l4 * B);
    zerowanie(final, l1 * l4 * B);

    check[0] = 0;
    konwersja_na_n(temp, num2, num1, final, suma, wynik, cout, check, reszty, cout[0] + 1, l2);
    inttochar(cout[2], reszty);
    e = cout[2];


    for (; e >= 0; e--) fputc(reszty[e], ptr);
    fprintf(ptr, "\n");
    fprintf(ptr, "\n");
    fprintf(ptr, "\n");
    fprintf(ptr, "\n");


    free(num1);
    free(num2);
    free(suma);
    free(swap);
    free(wynik);
    free(num4);
    free(reszty);
    free(final);
    free(temp);
}

void konwersja(char* s1, char* s2, char* s4, FILE* ptr)
{
    int l1, l2, l4;// l1-arg1 l2-system l4-arg2
    int larg1;
    int cout[H];
    int check[H];
    int num3[H]; // pomocnicza do sytemu
    int e = 0;
    check[0] = 0;

    for (l1 = 0; s1[l1] != '\0'; l1++);
    for (l2 = 0; s2[l2] != '\0'; l2++);
    for (l4 = 0; s4[l4] != '\0'; l4++);


    int* num1 = (int*)calloc(l1 * l1 * B, sizeof(int));
    if (num1 == NULL)
        printf("Couldn't allocate memory");

    int* num2 = (int*)calloc(l2*2, sizeof(int));
    if (num2 == NULL)
        printf("Couldn't allocate memory");

    int* num4 = (int*)calloc(l4 * l4 * B, sizeof(int));
    if (num4 == NULL)
        printf("Couldn't allocate memory");

    int* suma = (int*)calloc(l1 * l4 * B, sizeof(int));
    if (suma == NULL)
        printf("Couldn't allocate memory");

    int* wynik = (int*)calloc(l1 * l4 * B, sizeof(int));
    if (wynik == NULL)
        printf("Couldn't allocate memory");

    int* swap = (int*)calloc(l1 * l4 * B, sizeof(int));
    if (swap == NULL)
        printf("Couldn't allocate memory");

    int* reszty = (int*)calloc(l1 * l4 * B, sizeof(int));
    if (reszty == NULL)
        printf("Couldn't allocate memory");

    int* temp = (int*)calloc(l1 * l4 * B, sizeof(int));
    if (temp == NULL)
        printf("Couldn't allocate memory");

    int* final = (int*)calloc(l1 * l4 * B, sizeof(int));
    if (final == NULL)
        printf("Couldn't allocate memory");



    for (l1 = 0; s1[l1] != '\0'; l1++)
    {
        if (s1[l1] >= '0' && s1[l1] <= '9')
        {
            num1[l1] = s1[l1] - '0';
        }
        else
        {
            num1[l1] = s1[l1] - 55;
        }
    }

    for (l2 = 0; s2[l2] != '\0'; l2++)
        num2[l2] = s2[l2] - '0';

    for (l4 = 0; s4[l4] != '\0'; l4++)
    {
        if (s4[l4] >= '0' && s4[l4] <= '9')
        {
            num4[l4] = s4[l4] - '0';
        }
        else
        {
            num4[l4] = s4[l4] - 55;
        }
    }



    konwersja_na_dec(num1, num2, num3, wynik, swap, suma, cout, l1, l2);
    palindrom(cout, num1, wynik, 0);
    larg1 = cout[0];
    cout[0] = 0;
    num3[0] = 0;
    zerowanie(suma, l1 * l4 * B);
    zerowanie(swap, l1 * l4 * B);

    konwersja_na_n(num1, num4, temp, final, suma, wynik, cout, check, reszty, larg1 + 1, l4);
    inttochar(cout[2], reszty);
    e = cout[2];


    for (; e >= 0; e--) fputc(reszty[e], ptr);
    fprintf(ptr, "\n");
    fprintf(ptr, "\n");
    fprintf(ptr, "\n");
    fprintf(ptr, "\n");


    free(num1);
    free(num2);
    free(suma);
    free(swap);
    free(wynik);
    free(num4);
    free(reszty);
    free(final);
    free(temp);
}

void potega(char* s1, char* s2, char* s4, FILE* ptr)
{
    int l1, l2, l4, lpow;// l1-arg1 l2-system l4-arg2
    int larg1, larg4, largpow;
    int cout[H];
    int check[H];
    int num3[H]; // pomocnicza do sytemu
    int e = 0;
    check[0] = 0;

    for (l1 = 0; s1[l1] != '\0'; l1++);
    for (l2 = 0; s2[l2] != '\0'; l2++);
    l4 = l1;
    for (lpow = 0; s4[lpow] != '\0'; lpow++);


    int* num1 = (int*)calloc(l1 * l1 * M, sizeof(int));
    if (num1 == NULL)
        printf("Couldn't allocate memory");

    int* arrpow = (int*)calloc(l1 * l1 * B, sizeof(int)); //zmniejszone z M do B
    if (arrpow == NULL)
        printf("Couldn't allocate memory");

    int* num2 = (int*)calloc(l2*2, sizeof(int));
    if (num2 == NULL)
        printf("Couldn't allocate memory");

    int* num4 = (int*)calloc(l4 * l4 * M, sizeof(int));
    if (num4 == NULL)
        printf("Couldn't allocate memory");

    int* suma = (int*)calloc(l1 * l4 * M, sizeof(int));
    if (suma == NULL)
        printf("Couldn't allocate memory");

    int* wynik = (int*)calloc(l1 * l4 * M, sizeof(int));
    if (wynik == NULL)
        printf("Couldn't allocate memory");

    int* swap = (int*)calloc(l1 * l4 * M, sizeof(int));
    if (swap == NULL)
        printf("Couldn't allocate memory");

    int* reszty = (int*)calloc(l1 * l4 * M, sizeof(int));
    if (reszty == NULL)
        printf("Couldn't allocate memory");
    int* temp = (int*)calloc(l1 * l4 * M, sizeof(int));
    if (temp == NULL)
        printf("Couldn't allocate memory");

    int* final = (int*)calloc(l1 * l4 * M, sizeof(int));
    if (final == NULL)
        printf("Couldn't allocate memory");



    for (l1 = 0; s1[l1] != '\0'; l1++)
    {
        if (s1[l1] >= '0' && s1[l1] <= '9')
        {
            num1[l1] = s1[l1] - '0';
            num4[l1] = s1[l1] - '0';
        }
        else
        {
            num1[l1] = s1[l1] - 55;
            num4[l1] = s1[l1] - 55;
        }
    }

    for (l2 = 0; s2[l2] != '\0'; l2++)
        num2[l2] = s2[l2] - '0';

    for (lpow = 0; s4[lpow] != '\0'; lpow++)
    {
        if (s4[lpow] >= '0' && s4[lpow] <= '9')
        {
            arrpow[lpow] = s4[lpow] - '0';
        }
        else
        {
            arrpow[lpow] = s4[lpow] - 55;
        }
    }



    konwersja_na_dec(num1, num2, num3, wynik, swap, suma, cout, l1, l2);
    palindrom(cout, num1, wynik, 0);
    larg1 = cout[0];
    larg4 = cout[0];
    cout[0] = 0;
    num3[0] = 0;
    zerowanie(suma, l1 * l4 * B);
    zerowanie(swap, l1 * l4 * B);

    konwersja_na_dec(num4, num2, num3, wynik, swap, suma, cout, l4, l2);
    palindrom(cout, num4, wynik, 0);
    larg4 = cout[0];
    cout[0] = 0;
    num3[0] = 0;
    zerowanie(suma, l1 * l4 * B);
    zerowanie(swap, l1 * l4 * B);

    konwersja_na_dec(arrpow, num2, num3, wynik, swap, suma, cout, lpow, l2);
    palindrom(cout, arrpow, wynik, 0);
    largpow = cout[0];
    cout[0] = 0;
    num3[0] = 0;
    zerowanie(suma, l1 * l4 * B);
    zerowanie(swap, l1 * l4 * B);

    power(num1, num4, suma, cout, arrpow, larg1 + 1, larg4 + 1, largpow + 1);
    zerowanie(wynik, l1 * l4 * B);


    konwersja_na_n(num1, num2, temp, final, suma, wynik, cout, check, reszty, cout[0] + 1, l2);
    inttochar(cout[2], reszty);
    e = cout[2];


    for (; e >= 0; e--) fputc(reszty[e], ptr);
    fprintf(ptr, "\n");
    fprintf(ptr, "\n");
    fprintf(ptr, "\n");
    fprintf(ptr, "\n");


    free(num1);
    free(num2);
    free(suma);
    free(swap);
    free(wynik);
    free(num4);
    free(reszty);
    free(arrpow);
    free(final);
    free(temp);
}


int main()
{
    char s1[T] = { 0 };
    char s2[S] = { 0 };
    char s4[T] = { 0 };
    char help1[S] = { 0 };
    char help2[S] = { 0 };
    char various[V];
    int a = 1;
    int i = 1;
    int choice;



    FILE* input, * output[B];

    input = fopen("in.txt", "r");
    if (!input) return 1;


    printf("For results in multiple files enter 1 / for results in a single file enter 0: ");
    scanf("%d", &choice);


    sprintf(various, "out%d.txt", i);
    output[i] = fopen(various, "w+");
    if (!output[i]) return 1;


    while (!feof(input))
    {
        if (choice == 1 && i >= 2)
        {
            sprintf(various, "out%d.txt", i);
            output[i] = fopen(various, "w+");
            if (!output[i]) return 1;
        }
        printf("%s %d %s", "Operation nr:", a, "in progress: ");
        //printf("\n");
        a++;

        fscanf(input, "%s", help1);
        fputs(help1, output[i]);
        fscanf(input, "%s", s2);
        fprintf(output[i], " ");
        fputs(s2, output[i]);
        fprintf(output[i], "\n");
        fprintf(output[i], "\n");

        if (help1[0] >= '0' && help1[0] <= '9')
        {


            fscanf(input, "%s", s1);
            fputs(s1, output[i]);
            fprintf(output[i], "\n");
            fprintf(output[i], "\n");
            konwersja(s1, help1, s2, output[i]);
            printf("(finished)");
            printf("\n");
        }
        else
        {

            fscanf(input, "%s", s1);
            fputs(s1, output[i]);
            fprintf(output[i], "\n");
            fprintf(output[i], "\n");
            fscanf(input, "%s", s4);
            fputs(s4, output[i]);
            fprintf(output[i], "\n");
            fprintf(output[i], "\n");

            switch (help1[0])
            {
            case '+':
                if (dane(s1,s2) == 0 || dane(s4,s2) == 0)
                {
                    fprintf(output[i], "Invalid arguments ERROR");
                    fprintf(output[i], "\n");
                    fprintf(output[i], "\n");
                    fprintf(output[i], "\n");
                    fprintf(output[i], "\n");
                }
                else
                {
                    plus(s1, s2, s4, output[i]);
                }

                break;
            case '*':
                if (dane(s1,s2) == 0 || dane(s4,s2) == 0)
                {
                    fprintf(output[i], "Invalid arguments ERROR");
                    fprintf(output[i], "\n");
                    fprintf(output[i], "\n");
                    fprintf(output[i], "\n");
                    fprintf(output[i], "\n");
                }
                else
                {
                    multiply(s1, s2, s4, output[i]);
                }

                break;
            case '^':
                if (dane(s1,s2) == 0 || dane(s4,s2) == 0)
                {
                    fprintf(output[i], "Invalid arguments ERROR");
                    fprintf(output[i], "\n");
                    fprintf(output[i], "\n");
                    fprintf(output[i], "\n");
                    fprintf(output[i], "\n");
                }
                else
                {
                    potega(s1, s2, s4, output[i]);
                }

                break;
            case '/':
                if (s4[0] == '0')
                {
                    fprintf(output[i], "Division by 0 ERROR");
                    fprintf(output[i], "\n");
                    fprintf(output[i], "\n");
                    fprintf(output[i], "\n");
                    fprintf(output[i], "\n");

                    break;
                }
                else if (dane(s1,s2) == 0 || dane(s4,s2) == 0)
                {
                    fprintf(output[i], "Invalid arguments ERROR");
                    fprintf(output[i], "\n");
                    fprintf(output[i], "\n");
                    fprintf(output[i], "\n");
                    fprintf(output[i], "\n");
                }
                else
                {
                    iloraz(s1, s2, s4, output[i]);
                    break;
                }

            case '%':
                if (s4[0] == '0')
                {
                    fprintf(output[i], "Division by 0 ERROR");
                    fprintf(output[i], "\n");
                    fprintf(output[i], "\n");
                    fprintf(output[i], "\n");
                    fprintf(output[i], "\n");
                    break;
                }
                else if (dane(s1,s2) == 0 || dane(s4,s2) == 0)
                {
                    fprintf(output[i], "Invalid arguments ERROR");
                    fprintf(output[i], "\n");
                    fprintf(output[i], "\n");
                    fprintf(output[i], "\n");
                    fprintf(output[i], "\n");
                }
                else
                {
                    modulo(s1, s2, s4, output[i]);
                    break;
                }
            default:
                if (help1[0] != '\0')
                {
                    fprintf(output[i], "Unknown operation ERROR");
                    fprintf(output[i], "\n");
                    fprintf(output[i], "\n");
                    fprintf(output[i], "\n");
                    fprintf(output[i], "\n");
                }
                break;

            }
            if (choice == 1)
            {
                i++;
                fclose(output[i - 1]);
            }

            printf("(finished)");
            printf("\n");
        }



        memset(s1, 0, T);
        memset(s2, 0, S);
        memset(s4, 0, T);
        memset(help1, 0, S);
        memset(help2, 0, S);

    }



    if (choice == 0)  fclose(output[i]);
    fclose(input);
    printf("\n %s", "All operations have been successfully completed: ");

    system("pause");

    return 0;
}
