import numpy as np


def part_1(list_a, list_b):
    print(np.sum(np.abs(list_a - list_b), dtype=np.int64))


def part_2(list_a, list_b):
    result = 0
    for num in list_a:
        result += int(np.sum(num == list_b) * num)
    print(result)


if __name__ == "__main__":
    # read file into two lists
    lists = np.loadtxt("./input.txt")
    list_a = np.sort(lists[:, 0])
    list_b = np.sort(lists[:, 1])

    part_1(list_a, list_b)
    part_2(list_a, list_b)
