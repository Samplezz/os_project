#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Function prototypes
void showMenu();
void listFiles();
void changePermissions();
void makeDeleteFiles();
void createSymbolicLink();
void copyFiles();
void moveFiles();
void redirection();
void aliases();
void viewFileContent();
void findFiles();

int main() {
    int choice;
    
    // Ensure the directory structure exists (Optional setup)
    system("mkdir -p /hotel/admin /hotel/staff /hotel/guests 2>/dev/null");

    do {
        showMenu();
        printf("Enter your choice (1-10, 0 to exit): ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); // Clear input buffer
            choice = -1;
        }

        switch (choice) {
            case 1: listFiles(); break;
            case 2: changePermissions(); break;
            case 3: makeDeleteFiles(); break;
            case 4: createSymbolicLink(); break;
            case 5: copyFiles(); break;
            case 6: moveFiles(); break;
            case 7: redirection(); break;
            case 8: aliases(); break;
            case 9: viewFileContent(); break;
            case 10: findFiles(); break;
            case 0: printf("Exiting...\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }
        
        if (choice != 0) {
            printf("\nPress Enter to continue...");
            while (getchar() != '\n');
            getchar();
        }

    } while (choice != 0);

    return 0;
}

void showMenu() {
    // system("clear"); // Optional: clear screen
    printf("\n========================================\n");
    printf("      Hotel Management System Menu      \n");
    printf("========================================\n");
    printf("1. List files/directories\n");
    printf("2. Change permissions of files/directories\n");
    printf("3. Make/delete files/directories\n");
    printf("4. Create symbolic link files\n");
    printf("5. Copy files/directories\n");
    printf("6. Move files/directories\n");
    printf("7. Use redirection to create or update files\n");
    printf("8. Set and use aliases for common tasks\n");
    printf("9. View file content (cat, head, tail)\n");
    printf("10. Find files or directories (find, grep)\n");
    printf("0. Exit\n");
    printf("========================================\n");
}

void listFiles() {
    printf("\n--- List Files ---\n");
    printf("Listing contents of /hotel:\n");
    system("ls -R /hotel");
}

void changePermissions() {
    char path[256];
    char mode[10];
    printf("\n--- Change Permissions ---\n");
    printf("Enter file/directory path: ");
    scanf("%s", path);
    printf("Enter mode (e.g., 755, +x): ");
    scanf("%s", mode);
    
    char command[512];
    snprintf(command, sizeof(command), "chmod %s %s", mode, path);
    system(command);
}

void makeDeleteFiles() {
    int choice;
    char path[256];
    printf("\n--- Make/Delete Files/Directories ---\n");
    printf("1. Create Directory\n");
    printf("2. Delete Directory\n");
    printf("3. Create File (touch)\n");
    printf("4. Delete File\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    
    printf("Enter path: ");
    scanf("%s", path);
    
    char command[512];
    switch (choice) {
        case 1: snprintf(command, sizeof(command), "mkdir -p %s", path); break;
        case 2: snprintf(command, sizeof(command), "rmdir %s", path); break;
        case 3: snprintf(command, sizeof(command), "touch %s", path); break;
        case 4: snprintf(command, sizeof(command), "rm %s", path); break;
        default: printf("Invalid choice.\n"); return;
    }
    system(command);
}

void createSymbolicLink() {
    char target[256], linkname[256];
    printf("\n--- Create Symbolic Link ---\n");
    printf("Enter target file/directory: ");
    scanf("%s", target);
    printf("Enter link name: ");
    scanf("%s", linkname);
    
    char command[512];
    snprintf(command, sizeof(command), "ln -s %s %s", target, linkname);
    system(command);
}

void copyFiles() {
    char source[256], dest[256];
    printf("\n--- Copy Files ---\n");
    printf("Enter source path: ");
    scanf("%s", source);
    printf("Enter destination path: ");
    scanf("%s", dest);
    
    char command[512];
    snprintf(command, sizeof(command), "cp -r %s %s", source, dest);
    system(command);
}

void moveFiles() {
    char source[256], dest[256];
    printf("\n--- Move Files ---\n");
    printf("Enter source path: ");
    scanf("%s", source);
    printf("Enter destination path: ");
    scanf("%s", dest);
    
    char command[512];
    snprintf(command, sizeof(command), "mv %s %s", source, dest);
    system(command);
}

void redirection() {
    char text[1024];
    char filename[256];
    int append;
    
    printf("\n--- Redirection ---\n");
    printf("Enter text to write: ");
    while (getchar() != '\n'); // Clear buffer
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0; // Remove newline
    
    printf("Enter filename: ");
    scanf("%s", filename);
    
    printf("1. Overwrite (>)\n2. Append (>>)\nEnter choice: ");
    scanf("%d", &append);
    
    char command[2048];
    if (append == 1) {
        snprintf(command, sizeof(command), "echo \"%s\" > %s", text, filename);
    } else {
        snprintf(command, sizeof(command), "echo \"%s\" >> %s", text, filename);
    }
    system(command);
}

void aliases() {
    char name[100], command[256];
    printf("\n--- Aliases ---\n");
    printf("Note: Aliases created here are temporary or shell-specific.\n");
    printf("Enter alias name: ");
    scanf("%s", name);
    printf("Enter command: ");
    while (getchar() != '\n');
    fgets(command, sizeof(command), stdin);
    command[strcspn(command, "\n")] = 0;
    
    char full_cmd[512];
    snprintf(full_cmd, sizeof(full_cmd), "alias %s='%s'; echo \"Alias created: %s='%s'\"", name, command, name, command);
    // Note: system() spawns a subshell, so alias is lost immediately. 
    // We can only demonstrate the command syntax or append to a file.
    printf("Executing: %s\n", full_cmd);
    system(full_cmd); 
    printf("(Note: In a real C program using system(), aliases don't persist to the parent shell.)\n");
}

void viewFileContent() {
    int choice;
    char path[256];
    printf("\n--- View File Content ---\n");
    printf("1. cat (Whole file)\n");
    printf("2. head (First 10 lines)\n");
    printf("3. tail (Last 10 lines)\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    
    printf("Enter file path: ");
    scanf("%s", path);
    
    char command[512];
    switch (choice) {
        case 1: snprintf(command, sizeof(command), "cat %s", path); break;
        case 2: snprintf(command, sizeof(command), "head %s", path); break;
        case 3: snprintf(command, sizeof(command), "tail %s", path); break;
        default: printf("Invalid choice.\n"); return;
    }
    system(command);
}

void findFiles() {
    int choice;
    char query[256];
    char path[256];
    
    printf("\n--- Find Files ---\n");
    printf("1. Find by name (find)\n");
    printf("2. Find by content (grep)\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    
    char command[512];
    if (choice == 1) {
        printf("Enter directory to search in: ");
        scanf("%s", path);
        printf("Enter filename pattern: ");
        scanf("%s", query);
        snprintf(command, sizeof(command), "find %s -name \"%s\"", path, query);
    } else if (choice == 2) {
        printf("Enter directory/file to search in: ");
        scanf("%s", path);
        printf("Enter search string: ");
        scanf("%s", query);
        snprintf(command, sizeof(command), "grep -r \"%s\" %s", query, path);
    } else {
        printf("Invalid choice.\n");
        return;
    }
    system(command);
}
