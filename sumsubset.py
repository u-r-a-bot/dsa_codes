def subset_sum(nums, target):
    result = []
    backtrack(nums, target, [], result)
    return result

def backtrack(nums, target, path, result):
    if target == 0:
        result.append(path)
        return
    if target < 0 or not nums:
        return
    for i in range(len(nums)):
        backtrack(nums[i+1:], target-nums[i], path+[nums[i]], result)

nums = [int(input("Enter number ")) for x in range(int(input("Enter size of set ")))]
target = int(input("Enter your target "))

print(subset_sum(nums , target))