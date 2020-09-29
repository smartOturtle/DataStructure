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
在二维数组周围添加一圈
``` python
def add_cycle(a):
    return [[0] * (len(a[0]) + 2)] + [[0] + row + [0] for row in a] + [[0] * (len(a[0]) + 2)]
```
