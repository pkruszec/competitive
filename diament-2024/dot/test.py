import random

N = 1
gen_out_todo = True
n1 = 500
n2 = 500
t = (-1000, 1000)

in_prefix = "input/thousand{:02d}.in"
out_prefix = "output/thousand{:02d}.out"

for i in range(1, N+1):
    if gen_out_todo:
        with open(out_prefix.format(i), "w", encoding="utf-8") as f:
            f.write("todo\n")

    with open(in_prefix.format(i), "w", encoding="utf-8") as f:
        f.write(f"{n1} {n2}\n")
        for j in range(n1):
            f.write(f"1000 ")
        f.write("\n")

        for j in range(n2):
            f.write(f"1000 ")
        f.write("\n")
