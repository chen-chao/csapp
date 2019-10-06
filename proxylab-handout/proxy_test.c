#include <stdio.h>
#include <string.h>

static int test_count = 0;
static int test_pass = 0;
static int main_ret = 0;

void parse_url(char *url, char *hostname, char *port, char *uri);

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

static void TEST_URL(char *url, char *expect_host,
		     char *expect_port, char *expect_uri)
{
  char hostname[2000], port[2000], uri[2000];
  parse_url(url, hostname, port, uri);
  EXPECT_EQ_STRING(expect_host, hostname);
  EXPECT_EQ_STRING(expect_port, port);
  EXPECT_EQ_STRING(expect_uri, uri);
}

static void test_parse_url() {
  TEST_URL("http://www.example.com", "www.example.com", "80", "/");
  TEST_URL("www.example.com", "www.example.com", "80", "/");
  TEST_URL("www.example.com/index.html", "www.example.com",
	   "80", "/index.html");
  TEST_URL("www.example.com:1234", "www.example.com", "1234", "/");
  TEST_URL("https://example.com/index.html", "example.com",
	   "443", "/index.html");
  TEST_URL("https://example.com:50037/somepage&args", "example.com",
	   "50037", "/somepage&args");
}


static void test_proxy() {
  test_parse_url();
}

int main() {
  test_proxy();
  printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
  return main_ret;
}
