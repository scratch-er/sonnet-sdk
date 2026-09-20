#!/usr/bin/env python3
"""Convert a binary file to MI (Memory Initialization) format.

Usage: bin2mi.py <input> <output>

Assumptions: little endian, 32-bit words, hex format.
Address depth (number of words) is calculated on the fly.
"""

import sys

WORD_BYTES = 4  # 32-bit words
WORD_BITS = WORD_BYTES * 8


def main():
    if len(sys.argv) != 3:
        sys.exit("Usage: bin2mi.py <input> <output>")

    input_path, output_path = sys.argv[1], sys.argv[2]

    with open(input_path, "rb") as f:
        data = f.read()

    words = [
        int.from_bytes(data[i : i + WORD_BYTES], "little")
        for i in range(0, len(data), WORD_BYTES)
    ]

    with open(output_path, "w") as f:
        f.write("#File_format=Hex\n")
        f.write(f"#Address_depth={len(words)}\n")
        f.write(f"#Data_width={WORD_BITS}\n")
        for word in words:
            f.write(f"{word:0{WORD_BITS // 4}X}\n")


if __name__ == "__main__":
    main()
