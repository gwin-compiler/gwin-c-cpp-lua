#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>

bool IsRunAsAdmin()
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
    printf("Installing gwin compiler 1.0...\n");
    if (IsRunAsAdmin())
    {
        if (system("git --version") == 1) { 
            printf("Git not found. Please install Git.\n");
            Sleep(4000);
            return 1;
        }
    }
    else
    {
        printf("The program is not running as administrator.\n");
        Sleep(4000);
        return 1;
    }
    system("cd C:/ && git clone --branch <tag_name> --single-branch <repository_url>");
    rename("C:/gwin-c-cpp-lua", "C:/gwin");

    // Create a batch file to set the PATH environment variable
    FILE *batchFile = fopen("set_path.bat", "w");
    if (batchFile != NULL) {
        fprintf(batchFile, "@echo off\n");
        fprintf(batchFile, "set NEW_PATH=%%PATH%%;C:\\gwin\\bin\n");
        fprintf(batchFile, "setx PATH \"%%NEW_PATH%%\"\n");
        fprintf(batchFile, "echo PATH updated successfully.\n");
        fclose(batchFile);

        // Execute the batch file
        system("set_path.bat");

        // Delete the batch file
        if (remove("set_path.bat") == 0) {
            printf("Batch file deleted successfully.\n");
        }
        else {
            printf("Error deleting batch file.\n");
        }
    }
    else {
        printf("Error creating batch file.\n");
        return 1;
    }

    printf("gwin compiler installed successfully.\n");

    // Wait for 4 seconds before closing
    Sleep(4000);

    return 0;
}