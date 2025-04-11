import struct
import sys

# The Python float you want to inspect
my_float = 0.1

# Pack the Python float into bytes.
# 'd' is the format code for a C double (which Python floats usually are).
# By default, struct.pack uses the machine's native byte order (endianness).
try:
    # Use 'd' for native C double format and endianness
    packed_bytes = struct.pack("d", my_float)
    # Alternatively, force endianness if needed:
    # packed_bytes = struct.pack('<d', my_float) # Little-endian
    # packed_bytes = struct.pack('>d', my_float) # Big-endian
except struct.error as e:
    print(f"Error packing float: {e}")
    print(
        "This might happen on unusual platforms where 'float' isn't a standard double."
    )
    exit()

print(f"Python float value: {my_float}")
print(
    f"Underlying C Type Size: {struct.calcsize('d')} bytes ({struct.calcsize('d') * 8} bits)"
)
print(f"System Endianness: {sys.byteorder}")
print("-" * 30)

print("Memory Representation (Bytes in native storage order):")

bit_representations_memory_order = []

# Iterate through the bytes object returned by struct.pack
for i, byte_val in enumerate(packed_bytes):
    # byte_val is an integer representing the byte's value (0-255)
    # Format the integer as an 8-digit binary string, padded with leading zeros
    bits = format(byte_val, "08b")
    hex_val = format(byte_val, "02X")  # Also show Hex
    print(f"Byte {i}: {bits}  (Hex: 0x{hex_val})")
    bit_representations_memory_order.append(bits)

print("\nCombined bits (native memory storage order):")
print(" ".join(bit_representations_memory_order))
print("-" * 30)

# --- Deconstruct based on IEEE 754 (assuming standard double) ---

# Reconstruct the logical bit pattern (Sign | Exponent | Mantissa)
# This depends on the system's endianness used during packing

if sys.byteorder == "little":
    # On little-endian, struct.pack puts LSB first, so reverse bytes for logical view
    logical_bit_string = "".join(reversed(bit_representations_memory_order))
    print("Reconstructed logical IEEE 754 order (Little-Endian System):")
elif sys.byteorder == "big":
    # On big-endian, struct.pack puts MSB first, matching logical view
    logical_bit_string = "".join(bit_representations_memory_order)
    print("Logical IEEE 754 order (Big-Endian System):")
else:
    logical_bit_string = None
    print("Could not determine logical order for unknown endianness.")

if logical_bit_string:
    # Extract S, E, F from the 64-bit string
    sign_bit = logical_bit_string[0]
    exponent_bits = logical_bit_string[1:12]  # 11 bits
    fraction_bits = logical_bit_string[12:]  # 52 bits

    # Calculate exponent value
    exponent_value = int(exponent_bits, 2)
    actual_exponent = exponent_value - 1023  # Bias for double precision

    print(f"  Sign Bit: {sign_bit} ({'Positive' if sign_bit == '0' else 'Negative'})")
    print(
        f"  Exponent Bits: {exponent_bits} (Stored Value: {exponent_value}, Actual Exponent: {actual_exponent})"
    )
    print(f"  Fraction Bits: {fraction_bits}")
