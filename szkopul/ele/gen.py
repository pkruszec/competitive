import viz
import random

N = 10
E = 6

chance_f = 0.2
chance_e = chance_f + 0.2

entries = []

for i in range(1, N+1):
    path = f"test/test{i:02d}.txt"

    with open(path, "w", encoding="utf-8") as f:
        m = random.randint(5, 20)
        f.write(f"{m}\n")
        for x in range(m):
            r = random.random()
            v = random.randint(1, E)
            if r < chance_f:
                f.write(f"{-v} ")
            elif r < chance_e:
                f.write(f"{v} ")
            else:
                f.write("0 ")
        f.write("\n")

    rx, ox = viz.main([None, path])
    entries.append((path, rx, ox))

with open("tests.adoc", "w", encoding="utf-8") as f:
    f.write(
        """= Tests
:author: Paweł Kruszec
:email: pakruszec@gmail.com

        """
    )

    for p, res, out in entries:
        f.write(
            f"""
----
Input:
include::{p}[]

Result:
{res}
----

image:{out}[]

            """
        )
