#include <stdio.h>
#include <string.h>
#include "proxy.h"

static int test_count = 0;
static int test_pass = 0;
static int main_ret = 0;

#define EXPECT_EQ_BASE(equality, expect, actual, format) \
    do {\
        test_count++;\
        if (equality)\
            test_pass++;\
        else {\
            fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", __FILE__, __LINE__, expect, actual);\
            main_ret = 1;\
        }\
    } while(0)


#define EXPECT_EQ_STRING(expect, actual) EXPECT_EQ_BASE(strcmp((expect), (actual)) == 0, expect, actual, "%s")

static void TEST_URL(char *url, char *expect_host, char *expect_port)
{
  char hostname[2000], port[2000];
  parse_url(url, hostname, port);
  EXPECT_EQ_STRING(expect_host, hostname);
  EXPECT_EQ_STRING(expect_port, port);
}

static void test_parse_url() {
  TEST_URL("http://www.example.com", "http://www.example.com", "80");
  TEST_URL("www.example.com", "www.example.com", "80");
  TEST_URL("www.example.com:1234", "www.example.com", "1234");
  TEST_URL("example.com:8000/index.html", "example.com", "8000");
  TEST_URL("https://example.com:50037/somepage&args", "https://example.com", "50037");
}

static void test_read_header() {

}

static void test_proxy() {
  test_parse_url();
  test_read_header();
}

int main() {
  test_proxy();
  printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
  return main_ret;
}
