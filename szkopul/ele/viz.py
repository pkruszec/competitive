import matplotlib.pyplot as plt
import sys
import pathlib

def main(args):
    MAX = (10**9)
    MIN = -MAX

    try:
        path = pathlib.Path(args[1])
    except IndexError:
        path = pathlib.Path("input01.txt")

    with open(path, "r", encoding="utf-8") as f:
        f.readline()
        xs = [int(x) for x in f.read().split()]

    n = len(xs)
    xs.append(MIN)
    xs.insert(0, MIN)

    conn = []

    def f(i):
        k = MAX
        c = []
        val = -xs[i]

        # right
        cc = []
        cs = 1
        cv = 0
        j = i+1
        cc.append((j-1, j))
        while xs[j] >= 0:
            cv += xs[j]
            if cv >= val and cs < k:
                k = cs
                c = cc
                break
            cc.append((j, j+1))
            cs += 1
            j += 1

        # left
        cc = []
        cs = 1
        cv = 0
        j = i-1
        cc.append((j, j+1))
        while xs[j] >= 0:
            cv += xs[j]
            if cv >= val and cs < k:
                k = cs
                c = cc
                break
            cc.append((j-1, j))
            cs += 1
            j -= 1

        if k == MAX:
            return -1
        
        conn.extend(c)
        return k

    s = 0
    bad = False
    for i in range(1, n+1):
        if xs[i] < 0:
            r = f(i)
            if r < 0:
                bad = True

            if not bad:
                s += r

    res = -1
    if not bad:
        res = s

    plt.plot([1, n], [0, 0], zorder=-2)

    for c in conn:
        plt.plot([c[0], c[1]], [0, 0], linewidth=6, zorder=-1, color="gray")

    for i in range(1, n+1):
        v = xs[i]

        s = 60
        fc = "b"
        ec = "b"

        if v != 0:
            s = 200
        
        if v < 0:
            fc = "white"

        plt.scatter(i, 0, s=s, facecolors=fc, edgecolors=ec)

    base = pathlib.Path("./output")
    out = base.joinpath(pathlib.Path(path.stem + ".svg"))

    plt.ylim((-0.2, 0.2))
    plt.gca().set_aspect(5)
    plt.savefig(out, dpi=1)

    print(f"saved {out}")
    return res, out

if __name__ == "__main__":
    print(main(sys.argv)[0])
