a = 1
b = 2


def swap(a, b):
    tmp = a
    a = b
    b = tmp


print(
    a, b
)  # prints 1,2 not 2,1 as a and b are passed by value not reference unlike mutable objects
