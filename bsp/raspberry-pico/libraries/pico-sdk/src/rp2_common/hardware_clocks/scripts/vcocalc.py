#!/usr/bin/env python3

import argparse

parser = argparse.ArgumentParser(description="PLL parameter calculator")
parser.add_argument("--input", "-i", default=12, help="Input (reference) frequency. Default 12 MHz", type=float)
parser.add_argument("--vco-max", default=1600, help="Override maximum VCO frequency. Default 1600 MHz", type=float)
parser.add_argument("--vco-min", default=400, help="Override minimum VCO frequency. Default 400 MHz", type=float)
parser.add_argument("--low-vco", "-l", action="store_true", help="Use a lower VCO frequency when possible. This reduces power consumption, at the cost of increased jitter")
parser.add_argument("output", help="Output frequency in MHz.", type=float)
args = parser.parse_args()

# Fixed hardware parameters
fbdiv_range = range(16, 320 + 1)
postdiv_range = range(1, 7 + 1)

best = (0, 0, 0, 0)
best_margin = args.output

for fbdiv in (fbdiv_range if args.low_vco else reversed(fbdiv_range)):
	vco = args.input * fbdiv
	if vco < args.vco_min or vco > args.vco_max:
		continue
	# pd1 is inner loop so that we prefer higher ratios of pd1:pd2
	for pd2 in postdiv_range:
		for pd1 in postdiv_range:
			out = vco / pd1 / pd2
			margin = abs(out - args.output)
			if margin < best_margin:
				best = (out, fbdiv, pd1, pd2)
				best_margin = margin

print("Requested: {} MHz".format(args.output))
print("Achieved: {} MHz".format(best[0]))
print("FBDIV: {} (VCO = {} MHz)".format(best[1], args.input * best[1]))
print("PD1: {}".format(best[2]))
print("PD2: {}".format(best[3]))
