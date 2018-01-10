typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, int len);
void show_int(int x);
void show_float(float x);
void show_pointer(void *x);
void show_val(int x);
void get_bit(byte_pointer bp, char *s);
void get_bits(byte_pointer start, int len, char *s);
