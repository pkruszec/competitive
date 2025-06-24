class _PorLib:
    def __init__(self):
        self._initialized = False
        self._n = None

    def _initialize(self):
        if not self._initialized:
            self._n = int(input())
            self._initialized = True

    def get_N(self):
        if not self._initialized:
            self._initialize()
        return self._n

    def swap_and_get_inversions(self, a: int, b: int) -> int:
        if not self._initialized:
            self._initialize()
        print(a, b, flush=True)  # Send the swap request to stdout
        result = int(input())   # Read the resulting inversion count from stdin
        return result


# Singleton instance of _PorLib
__some_class_object = _PorLib()

# Public API
def DajN() -> int:
    """Returns the value of n (the number of books)."""
    return __some_class_object.get_N()

def Zamiana(a: int, b: int) -> int:
    """Swaps books at positions `a` and `b` and returns the number of inversions."""
    return __some_class_object.swap_and_get_inversions(a, b)

# Expose the public functions for import
__all__ = ['DajN', 'Zamiana']
