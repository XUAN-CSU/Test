#include <stdio.h>

void test_hex_octal()
{
	int a  = 15;
	printf("in hex: %08x\n", a);

	int b = 255;
	printf("in octal: %o\n", b);

	int c = 333;
	printf("in hex: %08x\n", c);

}

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define CRC32_POLY 0xEDB88320

static uint32_t crc32_table[256];

void init_crc32_table() {
    uint32_t crc;
    for (int i = 0; i < 256; ++i) {
        crc = i;
        for (int j = 8; j > 0; --j) {
            if (crc & 1) {
                crc = (crc >> 1) ^ CRC32_POLY;
            } else {
                crc >>= 1;
            }
        }
        crc32_table[i] = crc;
    }
}

uint32_t crc32(const void *data, size_t length) {
    uint32_t crc = 0xFFFFFFFF;
    const uint8_t *byte = data;

    while (length--) {
        crc = (crc >> 8) ^ crc32_table[(crc ^ *byte++) & 0xFF];
    }

    return crc ^ 0xFFFFFFFF;
}

int main() {
    init_crc32_table();

    const char *data1 = "Hello, world!";
    const char *data2 = "Hello, World!"; // Notice the difference in capitalization

    uint32_t crc1 = crc32(data1, strlen(data1));
    uint32_t crc2 = crc32(data2, strlen(data2));

    printf("CRC-32 checksum for '%s': %08X\n", data1, crc1);
    printf("CRC-32 checksum for '%s': %08X\n", data2, crc2);

    if (crc1 == crc2) {
        printf("Checksums are identical.\n");
    } else {
        printf("Checksums differ.\n");
    }

    return 0;
}
