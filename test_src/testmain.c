#include "tests.h"
#include <assert.h>
#include <stdio.h>

#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

#define TEST(name)                                                             \
  {                                                                            \
    printf(GREEN "---Start testing " #name "---\n" RESET);                     \
    test_##name();                                                             \
    printf(GREEN "---End testing " #name "---\n" RESET);                       \
  }

int main(int argc, char *argv[]) {
  printf("TESTING LIBWHISPER...\n");
  TEST(hm)
  TEST(contig_array)
  printf("SUCCESSFULLY TESTED LIBWHISPER.\n");
  return 0;
}
