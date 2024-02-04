

def swap(lis, pos1, pos2) -> list:
    lis[pos1], lis[pos2] = lis[pos2], lis[pos1]
    return lis


def partition(A: list, left: int, right: int):
    pivot, i, j = A[left], left + 1, right
    while i <=j:
        while  i<= right and A[i] < pivot :
            i += 1
        while j>=left and A[j] > pivot:
            j = j - 1
        if i <= j:
            A = swap(A, i, j)
            i, j = i + 1, j - 1

    A = swap(A, i - 1, left)
    return i - 1




def quicksort(lis: list) -> list:
    if len(lis) <= 1:
        return lis
    partition_index = partition(lis, 0, len(lis) - 1)
    left = quicksort(lis[:partition_index])
    right = quicksort(lis[partition_index + 1:])
    return left +[lis[partition_index]]+ right


test_case = [2, 6, 3, 5, 1, 3, 4, 7, 8, 9, 0]
sorted_lis = quicksort(test_case)
print(sorted_lis)
