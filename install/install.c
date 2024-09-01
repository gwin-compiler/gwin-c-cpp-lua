#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>

BOOL IsRunAsAdmin()
{
    BOOL isAdmin = FALSE;
    PSID adminGroup = NULL;
    SID_IDENTIFIER_AUTHORITY ntAuthority = SECURITY_NT_AUTHORITY;

    if (AllocateAndInitializeSid(&ntAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID,
                                 DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &adminGroup))
    {
        CheckTokenMembership(NULL, adminGroup, &isAdmin);
        FreeSid(adminGroup);
    }

    return isAdmin;
}

int main() {
    printf("Installing gwin compiler...\n")
    if (IsRunAsAdmin())
    {
        if (system("git --version") == 1) { 
        printf("Git not found. Please install Git.\n");
        return 1;
    }
    }
    else
    {
        printf("The program is not running as administrator.\n");
        return 1;
    }
    system("cd C:/ && git clone https://github.com/gwin-compiler/gwin-c-cpp-lua.git");
    system("cd C:/ && mv gwin-c-cpp-lua gwin")
    system('setx PATH "%PATH%;C:/gwin/bin"');
    printf("gwin compiler installed successfully.\n");

    return 0;
}