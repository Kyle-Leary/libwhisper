#include "tests.h"
#include <assert.h>
#include <stdio.h>

#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

// flush IO with the \n AFTER the ansi reset code.
#define TEST(name)                                                             \
  {                                                                            \
    printf(GREEN "---Start testing " #name "---" RESET "\n");                  \
    test_##name();                                                             \
    printf(GREEN "---End testing " #name "---" RESET "\n");                    \
  }

int main(int argc, char *argv[]) {
  printf("TESTING LIBWHISPER...\n");
  TEST(hm)
  TEST(cm)
  TEST(contig_array)
  TEST(array)
  TEST(queue)
  printf("SUCCESSFULLY TESTED LIBWHISPER.\n");
  return 0;
}
