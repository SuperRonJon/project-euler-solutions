import sys

def factorial(value):
    product = 1
    for i in range(2, value+1):
        product *= i
    return product

def sum_digits(value):
    total = 0
    cur = value
    while cur > 0:
        total += cur % 10
        cur = int(cur // 10)
    return total

if __name__ == '__main__':
    n = 10
    if len(sys.argv) == 2:
        try:
            n = int(sys.argv[1])
        except ValueError:
            print(f"Error parsing {sys.argv[1]} to integer.")
            sys.exit(1)
    n_fact = factorial(n)
    fact_sum = sum_digits(n_fact)
    print(f"{n}! = {n_fact}\nSum: {fact_sum}")
