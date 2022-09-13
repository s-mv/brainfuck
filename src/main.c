#include "brainf.h"
#include "common.h"
#include "transpiler.h"

extern u32 id;

int main(int argc, char *argv[]) {
  Init();

  // go through arguments
  for (int i = 0; i < argc; i++) {
    if (!strcmp(argv[i], "-h")) {
      printf("%s", help_message);
      return 0;
    }
    if (!strcmp(argv[i], "-f")) {
      if (i + 1 >= argc)
        printf("File name not provided.\n");
      else
        Execute(argv[i + 1]);
      return 0;
    }
    if (!strcmp(argv[i], "-c")) {
      if (i + 1 >= argc)
        printf("File name not provided.\n");
      else
        Compile(argv[i + 1]);
      return 0;
    }
  }

  // REPL
  printf(
      "Brainfuck interpreter: version s.m.v.\n"
      "Please keep input under %d characters!\n"
      "Press ctrl-C to exit.\n"
      "Use -h for help.\n",
      REPL_MAX_CHARS);
  loop {
    printf(": ");

    // TODO: change this to have a flexible length
    char c[REPL_MAX_CHARS];
    fgets(c, REPL_MAX_CHARS, stdin);

    id = 0;
    Run(c);

    printf("\n");
  }
  return 0;
}
// I DON "TKNOW WHAT"I AM DOING WITH MY LI FE HEKPE HELP
// kidding, take care dear programmers