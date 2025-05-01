import random

class T:
    def __repr__(self):
        return "t"

class BinOp:
    def __init__(self, lhs, rhs):
        self.lhs = lhs
        self.rhs = rhs

    def __repr__(self):
        return f"{self.lhs}{self.__class__.OP}{self.rhs}"

class Add(BinOp):
    OP = "+"

class Mul(BinOp):
    OP = "*"

def gen_term(d=0):
    v = random.randint(0, 2)
    if v == 0:
        return random.randint(1, 50)
    elif v == 1:
        return T()
    else:
        return gen_expr(d+1)

def gen_binop(d=0):
    ops = [Add, Mul]
    cls = ops[random.randint(0, len(ops)-1)]
    return cls(gen_expr(d+1), gen_expr(d+1))

def gen_expr(d=0):
    if d >= 10:
        return gen_term(d+1)

    v = random.randint(0, 4)
    if v == 0:
        return gen_term(d+1)
    else:
        return gen_binop(d+1)

def main():
    # random.seed(13214432)
    print(gen_expr())

if __name__ == "__main__":
    main()
