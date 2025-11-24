#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void list_files();
void change_permissions();
void make_delete_files();
void create_symlink();
void copy_files();
void move_files();
void redirection();
void aliases();
void view_content();
void find_files();
void print_menu();

int main() {
    int choice;
    
    // Ensure the bank directory exists
    system("./setup_banking.sh");

    while (1) {
        print_menu();
        printf("Enter your choice (1-11): ");
        if (scanf("%d", &choice) != 1) {
            // Clear input buffer if invalid input
            while (getchar() != '\n');
            printf("Invalid input. Please enter a number.\n");
            continue;
        }
        getchar(); // Consume newline

        switch (choice) {
            case 1: list_files(); break;
            case 2: change_permissions(); break;
            case 3: make_delete_files(); break;
            case 4: create_symlink(); break;
            case 5: copy_files(); break;
            case 6: move_files(); break;
            case 7: redirection(); break;
            case 8: aliases(); break;
            case 9: view_content(); break;
            case 10: find_files(); break;
            case 11: 
                printf("Exiting system. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
        
        printf("\nPress Enter to continue...");
        getchar();
    }

    return 0;
}

void print_menu() {
    printf("\n========================================\n");
    printf("        BANKING SYSTEM MENU\n");
    printf("========================================\n");
    printf("1. List files/directories\n");
    printf("2. Change permissions of files/directories\n");
    printf("3. Make/delete files/directories\n");
    printf("4. Create symbolic link files\n");
    printf("5. Copy files/directories\n");
    printf("6. Move files/directories\n");
    printf("7. Use redirection to create/update files\n");
    printf("8. Set and use aliases\n");
    printf("9. View file content\n");
    printf("10. Find files or directories\n");
    printf("11. Exit\n");
    printf("========================================\n");
}

void list_files() {
    char dir[100];
    printf("Enter directory to list (e.g., ./bank/admin): ");
    fgets(dir, sizeof(dir), stdin);
    dir[strcspn(dir, "\n")] = 0; // Remove newline

    char command[200];
    sprintf(command, "ls -l %s", dir);
    system(command);
}

void change_permissions() {
    char file[100];
    char mode[10];
    printf("Enter file/directory path: ");
    fgets(file, sizeof(file), stdin);
    file[strcspn(file, "\n")] = 0;

    printf("Enter new mode (e.g., 755 or u+x): ");
    fgets(mode, sizeof(mode), stdin);
    mode[strcspn(mode, "\n")] = 0;

    char command[200];
    sprintf(command, "chmod %s %s", mode, file);
    system(command);
}

void make_delete_files() {
    int action;
    char path[100];
    printf("1. Create Directory\n2. Delete Directory/File\nChoose action: ");
    scanf("%d", &action);
    getchar(); // Consume newline

    printf("Enter path: ");
    fgets(path, sizeof(path), stdin);
    path[strcspn(path, "\n")] = 0;

    char command[200];
    if (action == 1) {
        sprintf(command, "mkdir -p %s", path);
    } else if (action == 2) {
        sprintf(command, "rm -rf %s", path);
    } else {
        printf("Invalid action.\n");
        return;
    }
    system(command);
}

void create_symlink() {
    char target[100], linkname[100];
    printf("Enter target file path: ");
    fgets(target, sizeof(target), stdin);
    target[strcspn(target, "\n")] = 0;

    printf("Enter link name: ");
    fgets(linkname, sizeof(linkname), stdin);
    linkname[strcspn(linkname, "\n")] = 0;

    char command[300];
    sprintf(command, "ln -s %s %s", target, linkname);
    system(command);
}

void copy_files() {
    char src[100], dest[100];
    printf("Enter source path: ");
    fgets(src, sizeof(src), stdin);
    src[strcspn(src, "\n")] = 0;

    printf("Enter destination path: ");
    fgets(dest, sizeof(dest), stdin);
    dest[strcspn(dest, "\n")] = 0;

    char command[300];
    sprintf(command, "cp -r %s %s", src, dest);
    system(command);
}

void move_files() {
    char src[100], dest[100];
    printf("Enter source path: ");
    fgets(src, sizeof(src), stdin);
    src[strcspn(src, "\n")] = 0;

    printf("Enter destination path: ");
    fgets(dest, sizeof(dest), stdin);
    dest[strcspn(dest, "\n")] = 0;

    char command[300];
    sprintf(command, "mv %s %s", src, dest);
    system(command);
}

void redirection() {
    char text[200], file[100];
    int mode;
    
    printf("Enter text to write: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0;

    printf("Enter file path: ");
    fgets(file, sizeof(file), stdin);
    file[strcspn(file, "\n")] = 0;

    printf("1. Overwrite (>)\n2. Append (>>)\nChoose mode: ");
    scanf("%d", &mode);
    getchar();

    char command[400];
    if (mode == 1) {
        sprintf(command, "echo \"%s\" > %s", text, file);
    } else if (mode == 2) {
        sprintf(command, "echo \"%s\" >> %s", text, file);
    } else {
        printf("Invalid mode.\n");
        return;
    }
    system(command);
}

void aliases() {
    // Aliases in system() are ephemeral and won't persist to the shell or other system() calls.
    // This is a simulation or would require appending to .bashrc which is risky/complex for this scope.
    // We will simulate it by defining a macro or just printing a message that it's set for the session concept.
    char name[50], command[100];
    printf("Enter alias name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    printf("Enter command: ");
    fgets(command, sizeof(command), stdin);
    command[strcspn(command, "\n")] = 0;

    printf("Alias '%s' set to '%s' (Note: Aliases in this C program are simulated and not persistent).\n", name, command);
    // In a real shell script we would do: echo "alias %s='%s'" >> ~/.bashrc
}

void view_content() {
    char file[100];
    int choice;
    printf("Enter file path: ");
    fgets(file, sizeof(file), stdin);
    file[strcspn(file, "\n")] = 0;

    printf("1. cat (All)\n2. head (First 10 lines)\n3. tail (Last 10 lines)\nChoose tool: ");
    scanf("%d", &choice);
    getchar();

    char command[200];
    if (choice == 1) sprintf(command, "cat %s", file);
    else if (choice == 2) sprintf(command, "head %s", file);
    else if (choice == 3) sprintf(command, "tail %s", file);
    else {
        printf("Invalid choice.\n");
        return;
    }
    system(command);
}

void find_files() {
    char dir[100], term[100];
    int choice;
    printf("1. Find by name\n2. Find by content (grep)\nChoose: ");
    scanf("%d", &choice);
    getchar();

    if (choice == 1) {
        printf("Enter directory to search: ");
        fgets(dir, sizeof(dir), stdin);
        dir[strcspn(dir, "\n")] = 0;
        printf("Enter filename pattern: ");
        fgets(term, sizeof(term), stdin);
        term[strcspn(term, "\n")] = 0;
        
        char command[300];
        sprintf(command, "find %s -name \"%s\"", dir, term);
        system(command);
    } else if (choice == 2) {
        printf("Enter file/directory to search in: ");
        fgets(dir, sizeof(dir), stdin);
        dir[strcspn(dir, "\n")] = 0;
        printf("Enter search string: ");
        fgets(term, sizeof(term), stdin);
        term[strcspn(term, "\n")] = 0;

        char command[300];
        sprintf(command, "grep -r \"%s\" %s", term, dir);
        system(command);
    } else {
        printf("Invalid choice.\n");
    }
}
