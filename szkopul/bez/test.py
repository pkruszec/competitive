import os
import subprocess

with open("result_new.txt", "w") as out:
    for e in os.listdir("./tests"):
        with open(os.path.join("./tests", e), "rb") as f:
            inp = f.read()

        p = subprocess.run(["bez"], input=inp, capture_output=True)
        out.write(p.stdout.decode("utf-8"))
