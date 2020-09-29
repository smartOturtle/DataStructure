# DataStructure

二分法模板
``` python
def lower_bound(array, target):
    lo, hi = 0, len(array)
    while lo < hi:
        mid = (lo + hi) // 2
        if array[mid] <= target:
            hi = mid
        else:
            lo = mid + 1
    return lo


def upper_bound(array, target):
    lo, hi = 0, len(array)
    while lo < hi:
        mid = (lo + hi) // 2
        if array[mid] < target:#唯一差别少个等号
            hi = mid
        else:
            lo = mid + 1
    return lo
```
滑动窗口模板
``` python
def sliding_window(array, size):
    array = iter(array)
    return accumulate(array, lambda t, elm: t[1:] + (elm,), initial=tuple(islice(array, size)))
```
