import sys
import math

_, *args = sys.argv
s = 0.0
for a in args:
    w = int(a)
    x = 100 * (math.log2(1 + min(2000, w)) / math.log2(1+2000))
    s += x
    # print(f"{x:.0f}")

print(f"sum {s:.0f} avg {s/len(args):.0f}")
