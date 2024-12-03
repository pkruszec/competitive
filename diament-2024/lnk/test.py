import random

N = 5
gen_out_todo = True
n = 500
t = (1, 1000)

in_prefix = "input/bgw{:02d}.in"
out_prefix = "output/bgw{:02d}.out"

for i in range(1, N+1):
    if gen_out_todo:
        with open(out_prefix.format(i), "w", encoding="utf-8") as f:
            f.write("todo\n")

    with open(in_prefix.format(i), "w", encoding="utf-8") as f:
        f.write(f"{n+2} {n+2}\n")

        l = [i for i in range(1, n+1)]

        f.write(f"1500 ")

        for x in l:
            f.write(f"{x} ")
            
        f.write(f"1600 \n")

        f.write(f"1600 ")

        for x in l:
            f.write(f"{x} ")

        f.write(f"1500 \n")
