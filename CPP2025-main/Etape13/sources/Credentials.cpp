#include "Credentials.h"
#include <cstring>

void Credentials::crypt()
{
    for (int i = 0; login[i]; i++)
        login[i] = (login[i] + 9) % 255;

    for (int i = 0; password[i]; i++)
        password[i] = (password[i] + 5) % 255;
}

void Credentials::decrypt()
{
    for (int i = 0; login[i]; i++)
        login[i] = (login[i] - 9 + 255) % 255;

    for (int i = 0; password[i]; i++)
        password[i] = (password[i] - 5 + 255) % 255;
}
