#!/usr/bin/env python3

import re
from functools import reduce

def part_1(line: str) -> int:
    def x(acc, match):
        x, y = match.group(1, 2)
        return acc + (int(x) * int(y))
    return reduce(x, re.finditer(r'mul\((\d+),(\d+)\)', line), 0)

if __name__ == '__main__':
    with open('input.txt', 'r') as file:
        corrupted = file.read()
    print(part_1(corrupted))
