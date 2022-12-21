#!/usr/bin/env python3

import argparse
from typing import Dict

parser = argparse.ArgumentParser()

parser.add_argument('--puzzle',
                    type=str,
                    action="store",
                    required=True,
                    help='Puzzle input')

args = parser.parse_args()

with open(args.puzzle) as fp:
    lines = fp.readlines()


def process(lines, freq, freqs):
    for line in lines:
        freq = freq + int(line)
        if freq in freqs:
            return freq, True
        freqs[freq] = True
    return freq, False


freq = 0
freqs: Dict[int, bool] = {}
freq, twice = process(lines, freq, freqs)
print(f"part_1: {freq}")

while twice is False:
    freq, twice = process(lines, freq, freqs)
print(f"part_2: {freq}")
