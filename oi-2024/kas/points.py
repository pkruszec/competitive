import sys
import math

_, *args = sys.argv

xs = None
if not args:
    xs = []
    lines = sys.stdin.readlines()
    for l in lines:
        parts = l.split()
        if not parts:
            continue
        xs.append(int(parts[-1]))
else:
    xs = args

s = 0.0
for a in xs:
    w = int(a)
    x = 100 * (math.log2(1 + min(2000, w)) / math.log2(1+2000))
    s += x
    # print(f"{x:.0f}")

print(f"sum {s:.0f} avg {s/len(xs):.0f}")
