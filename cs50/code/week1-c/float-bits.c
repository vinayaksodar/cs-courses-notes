#include <stdio.h>
#include <stddef.h> // Required for size_t

// Function to print the bits of a single byte (remains the same)
void print_byte_bits(unsigned char byte)
{
    // Iterate from the most significant bit (MSB) to the least (LSB)
    for (int i = 7; i >= 0; i--)
    {
        // Shift the byte right by 'i' positions
        // Use bitwise AND with 1 to isolate the bit at the current position
        int bit = (byte >> i) & 1;
        printf("%d", bit);
    }
}

int main()
{
    // Use 'double' for standard 64-bit floating point
    double my_double = 0.1; // Example double value (e)

    // Use %.17g for printing doubles to see full precision generally
    printf("Double value: %.17g\n", my_double);
    printf("Size of double: %zu bytes (%zu bits)\n", sizeof(my_double), sizeof(my_double) * 8);

    // Get a pointer to the raw bytes of the double
    // unsigned char is used because it's typically 1 byte
    unsigned char *byte_ptr = (unsigned char *)&my_double;

    printf("Memory representation (bits, byte by byte in memory order):\n");

    // Iterate through each byte of the double (usually 8 bytes)
    // The order depends on the system's endianness
    for (size_t i = 0; i < sizeof(my_double); i++)
    {
        printf("Byte %zu: ", i);
        print_byte_bits(byte_ptr[i]);
        printf("  (Hex: 0x%02X)\n", byte_ptr[i]); // Also show hex value
    }
    printf("\n");

    printf("Combined bits (memory order): ");
    for (size_t i = 0; i < sizeof(my_double); i++)
    {
        print_byte_bits(byte_ptr[i]);
        printf(" "); // Space between bytes
    }
    printf("\n\n");

    printf("--- Endianness Note ---\n");
    printf("The order of the bytes shown above is the order they appear in memory.\n");
    printf(" - On Little-Endian systems (common, e.g., x86), the least significant byte is stored first (at the lowest memory address, Byte 0).\n");
    printf(" - On Big-Endian systems, the most significant byte is stored first.\n");
    printf("The IEEE 754 double-precision standard defines a logical order (1 Sign | 11 Exponent | 52 Mantissa), but the storage order in memory might differ.\n");

    return 0;
}