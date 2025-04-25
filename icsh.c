/* ICCS227: Project 1: icsh
 * Name: Thanadet Udomsit
 * StudentID: 6580138
 */

#include "stdio.h"
#include "string.h"

#define MAX_CMD_BUFFER 255

int execute_command(char* buffer, char* last_command);

int main() {

  char buffer[MAX_CMD_BUFFER];
  char last_command[MAX_CMD_BUFFER];
  int run = 1;
  int exit_code = 0;

  printf("\nWelcome to \n");
  printf(" ___  ________  ________  ___  ___     \n");
  printf("|\\  \\|\\   ____\\|\\   ____\\|\\  \\|\\  \\    \n");
  printf("\\ \\  \\ \\  \\___|\\ \\  \\___|\\ \\  \\\\\\  \\   \n");
  printf(" \\ \\  \\ \\  \\    \\ \\_____  \\ \\   __  \\  \n");
  printf("  \\ \\  \\ \\  \\____\\|____|\\  \\ \\  \\ \\  \\ \n");
  printf("   \\ \\__\\ \\_______\\____\\_\\  \\ \\__\\ \\__\\ \n");
  printf("    \\|__|\\|_______|\\_________\\|__|\\|__| \n");
  printf("                  \\|_________|         \n");
  printf("                                       \n");

  while (run) {
      printf("icsh$ ");
      fgets(buffer, MAX_CMD_BUFFER, stdin);

    // remove the \n otherwise it will be passed into the execute_command and wont be read properly
    // ie when we input "echo" it will read as "echo\n" and so the text_after_command wont be null or 
    // when we don't input any command it will actually input "\n"
    // so then the execute_command will  return 1 and ggs stop running (should return 0)

      buffer[strcspn(buffer, "\n")] = 0;
      if (strlen(buffer) == 0) {
        continue;
      }

    exit_code = execute_command(buffer, last_command);

    if (exit_code != 0) {
      run = 0;
      printf("\n---------\n");
      printf("exit code: %d\n", exit_code);
      printf("---------\n");
    }
    else {
      strcpy(last_command, buffer);
    }
  }

  return 0;
}

int execute_command(char* buffer, char* last_command) {

  // Make a copy because strtok modify the string
  char buffer_copy[MAX_CMD_BUFFER];
  strcpy(buffer_copy, buffer);

  // Get command
  char* command = strtok(buffer_copy, " ");
  // printf("command: %s:\n", command);

  if (command == NULL) {
    return 0;
  }

  // echo command
  if (strcmp(command, "echo") == 0) {

    char* text_after_command = strchr(buffer, ' ');
    if (text_after_command != NULL) {
      printf("%s\n", text_after_command + 1);
    }
    else {
      printf("\n");
    }

    return 0;
  }

  if (strcmp(command, "!!") == 0) {
    if (strlen(last_command) != 0) {
      printf("%s\n", last_command);
    }

    // printf("In !!\n");

    return 0;
  }

  return 0;
}
