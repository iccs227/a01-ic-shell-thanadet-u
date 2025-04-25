/* ICCS227: Project 1: icsh
 * Name:
 * StudentID:
 */

#include "stdio.h"

#define MAX_CMD_BUFFER 255

int main() {
  
  printf("Welcome to \n");
  printf(" ___  ________  ________  ___  ___     \n");
  printf("|\\  \\|\\   ____\\|\\   ____\\|\\  \\|\\  \\    \n");
  printf("\\ \\  \\ \\  \\___|\\ \\  \\___|\\ \\  \\\\\\  \\   \n");
  printf(" \\ \\  \\ \\  \\    \\ \\_____  \\ \\   __  \\  \n");
  printf("  \\ \\  \\ \\  \\____\\|____|\\  \\ \\  \\ \\  \\ \n");
  printf("   \\ \\__\\ \\_______\\____\\_\\  \\ \\__\\ \\__\\ \n");
  printf("    \\|__|\\|_______|\\_________\\|__|\\|__| \n");
  printf("                  \\|_________|         \n");
  printf("                                       \n");

  char buffer[MAX_CMD_BUFFER];
  while (1) {
      printf("icsh $ ");
      fgets(buffer, 255, stdin);
      printf("you said: %s\n", buffer);
  }
  
}
