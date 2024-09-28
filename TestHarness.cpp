#include "UserClass.h"

int main(int argc, char* argv[])
{
    UserClass* user = new UserClass("Presentation/");

    user->KeystrokeHandling();

    delete user;

    return 0;
}