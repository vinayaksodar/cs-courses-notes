# Floating-Point Inaccuracy

## Foundational Concepts

Let's get some first principles solidified first:

1.  Computers only store 0s and 1s, so anything else (like hexadecimal) is just a representation of the underlying binary information.
2.  This is true for every programming language, meaning floating-point inaccuracy is a common issue across languages.
3.  Hexadecimal representation is often used because every binary pattern can be represented _exactly_ in hexadecimal, and it's usually shorter and easier for humans to read than long binary strings.

Just like you cannot represent certain fractions exactly in one number system (e.g., 1/3 in decimal is 0.3333..., repeating infinitely), the same applies to representing decimal fractions in binary.

### The Problem with 0.1 in Binary

No matter how many base-2 (binary) digits you use, the decimal value `0.1` cannot be represented exactly as a finite binary fraction. In base 2, 1/10 is the infinitely repeating fraction:

```
0.0001100110011001100110011001100110011001100110011...
```

## The IEEE 754 Standard

Since at least the year 2000, most machines use the IEEE 754 standard for binary floating-point arithmetic. Almost all platforms map Python floats to the IEEE 754 `binary64` ("double precision") format. These `binary64` values use 64 bits in total, providing 53 bits of precision for the number itself. When you try to store `0.1`, the computer strives to convert it to the closest possible fraction of the form _J_ / 2<sup>_N_</sup>, where _J_ is an integer that can be represented using exactly 53 bits.

## Representing 0.1 in IEEE 754 Binary64

Let's understand how `0.1` (decimal) is actually stored using the IEEE 754 standard.

### Method 1: Conceptual Conversion (Fractional Binary)

#### Step 1: Decimal to Binary (Fractional)

**0.1 (decimal)** in binary is **infinitely repeating**:

```
0.0001100110011001100110011001100110011001100110011...
```

#### Step 2: Normalize the Binary Number

Express this in **scientific notation (base 2)** by shifting the binary point:

```
1.10011001100110011001100110011001100110011001100110011... × 2⁻⁴
```

We shift the point 4 places to the right, resulting in an exponent of **-4**.

#### Step 3: Truncate or Round to 53 Bits Precision

IEEE 754 **binary64** uses:

- **1 bit** for the sign.
- **11 bits** for the exponent (stored with a bias of 1023).
- **52 bits** for the **fraction (mantissa)**. We achieve **53 bits of precision** because the leading `1.` in the normalized form is **implicit** and not explicitly stored.

We take the normalized form and keep the first 52 bits _after_ the binary point:

```
1.10011001100110011001100110011001100110011001100110011...
```

The 52 bits for the mantissa are:

```
1001100110011001100110011001100110011001100110011001
```

_(Note: Careful comparison with the Integer Math method below shows rounding occurs, and the last bit is actually rounded up)_

#### Step 4: Assemble the Final IEEE 754 Representation

Let's assemble the components:

- **Sign bit**: `0` (since 0.1 is positive)
- **Exponent**:
  - Actual exponent = -4
  - Stored exponent = -4 + 1023 (bias) = **1019**
  - Binary representation (11 bits): `01111111011`
- **Mantissa (52 bits)**:
  - Derived from the normalized form (removing the implicit leading `1.`) and considering rounding (see next method):
    ```
    1001100110011001100110011001100110011001100110011010
    ```

Putting it all together (Sign | Exponent | Mantissa):

```
0 | 01111111011 | 1001100110011001100110011001100110011001100110011010
```

This 64-bit pattern is what's actually stored. If you convert this exact binary representation back to decimal, you get:

```
0.1000000000000000055511151231257827021181583404541015625
```

### Method 2: Integer Math (Finding the Closest Fraction)

To avoid potential precision issues with infinitely repeating binary fractions during the conversion, systems often use integer arithmetic to find the closest representable value.

We want to find the closest fraction of the form `J / 2**N` to `0.1`, where `J` is an integer representable with exactly 53 bits.
Rewrite `1 / 10 ~= J / (2**N)` as `J ~= 2**N / 10`.

Recalling that `J` must have exactly 53 bits (meaning `2**52 <= J < 2**53`), we find the best value for `N` is 56:

```python
>>> 2**52 <= 2**56 // 10 < 2**53
True
```

56 is the unique integer value for `N` that satisfies this condition for `J`. Now, calculate `J` by performing the division and rounding:

```python
>>> q, r = divmod(2**56, 10)
>>> q
7205759403792793
>>> r
6
```

Since the remainder (`6`) is more than half of the divisor (`10`), we round the quotient (`q`) up:

```python
>>> J = q + 1
>>> J
7205759403792794
```

Therefore, the best possible approximation to `1/10` in IEEE 754 double precision is `7205759403792794 / 2**56`.

Let's look at the numerator `J` in binary:

```
7205759403792794₁₀ = 11001100110011001100110011001100110011001100110011010₂
```

This binary representation has 53 bits. The most significant bit (the implicit `1.`) corresponds to `2**52`, and the following 52 bits form the stored mantissa:

```
1001100110011001100110011001100110011001100110011010
```

This matches the mantissa derived (with rounding considered) in the first method.

## Practical Demonstration in Python

Let's use Python to inspect the actual bits stored for the float `0.1`.

### Python Code

```python
import struct
import sys

# The Python float you want to inspect
my_float = 0.1

# Pack the Python float into bytes using the C double format ('d')
# This uses the system's native byte order (endianness).
try:
    packed_bytes = struct.pack("d", my_float)
except struct.error as e:
    print(f"Error packing float: {e}")
    print("This might happen on unusual platforms where 'float' isn't a standard double.")
    exit()

print(f"Python float value: {my_float}")
print(f"Underlying C Type Size: {struct.calcsize('d')} bytes ({struct.calcsize('d') * 8} bits)")
print(f"System Endianness: {sys.byteorder}")
print("-" * 30)

print("Memory Representation (Bytes in native storage order):")
bit_representations_memory_order = []
for i, byte_val in enumerate(packed_bytes):
    bits = format(byte_val, "08b")
    hex_val = format(byte_val, "02X")
    print(f"Byte {i}: {bits}  (Hex: 0x{hex_val})")
    bit_representations_memory_order.append(bits)

print("\nCombined bits (native memory storage order):")
print(" ".join(bit_representations_memory_order))
print("-" * 30)

# --- Deconstruct based on IEEE 754 ---
print("Deconstructing the bits according to IEEE 754 (Double Precision):")

# Reconstruct the logical bit pattern (Sign | Exponent | Mantissa)
# based on system endianness
if sys.byteorder == "little":
    # On little-endian, bytes are stored LSB first, so reverse the byte list
    logical_bit_string = "".join(reversed(bit_representations_memory_order))
    print("(System is Little-Endian, bytes reversed for logical view)")
elif sys.byteorder == "big":
    # On big-endian, bytes are stored MSB first, matching logical view
    logical_bit_string = "".join(bit_representations_memory_order)
    print("(System is Big-Endian, bytes already in logical view)")
else:
    logical_bit_string = None
    print("Could not determine logical order for unknown endianness.")

if logical_bit_string:
    # Extract Sign (1 bit), Exponent (11 bits), Fraction/Mantissa (52 bits)
    sign_bit = logical_bit_string[0]
    exponent_bits = logical_bit_string[1:12]
    fraction_bits = logical_bit_string[12:]

    # Calculate the actual exponent value
    exponent_value = int(exponent_bits, 2)
    actual_exponent = exponent_value - 1023 # Bias for double precision

    print(f"  Sign Bit     : {sign_bit} ({'Positive' if sign_bit == '0' else 'Negative'})")
    print(f"  Exponent Bits: {exponent_bits} (Stored: {exponent_value}, Actual: {actual_exponent})")
    print(f"  Fraction Bits: {fraction_bits}")

```

### Code Output and Analysis

```
Python float value: 0.1
Underlying C Type Size: 8 bytes (64 bits)
System Endianness: little
------------------------------
Memory Representation (Bytes in native storage order):
Byte 0: 10011010  (Hex: 0x9A)
Byte 1: 10011001  (Hex: 0x99)
Byte 2: 10011001  (Hex: 0x99)
Byte 3: 10011001  (Hex: 0x99)
Byte 4: 10011001  (Hex: 0x99)
Byte 5: 10011001  (Hex: 0x99)
Byte 6: 10111001  (Hex: 0xB9)
Byte 7: 00111111  (Hex: 0x3F)

Combined bits (native memory storage order):
10011010 10011001 10011001 10011001 10011001 10011001 10111001 00111111
------------------------------
Deconstructing the bits according to IEEE 754 (Double Precision):
(System is Little-Endian, bytes reversed for logical view)
  Sign Bit     : 0 (Positive)
  Exponent Bits: 01111111011 (Stored: 1019, Actual: -4)
  Fraction Bits: 1001100110011001100110011001100110011001100110011010
```

**Analysis:** The output confirms the IEEE 754 representation derived earlier:

- **Sign:** 0 (Positive)
- **Exponent:** `01111111011` (Decimal 1019, representing the actual exponent -4 after adjusting for the bias of 1023).
- **Fraction (Mantissa):** `100110011001...1010` (The 52 stored bits, matching the result from the integer math method which included rounding).

This practical example demonstrates how the theoretical concepts of binary representation and the IEEE 754 standard manifest in the actual bits stored in computer memory for a common decimal fraction like 0.1.
