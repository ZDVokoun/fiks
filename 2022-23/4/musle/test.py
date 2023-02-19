def sums(arr, l, r, sum = 0, hist = []):
     if l > r:
             print(sum, hist)
             return
     sums(arr, l + 1, r, sum, hist)
     lst = hist.copy()
     lst.append(arr[l])
     sums(arr, l + 1, r, sum + arr[l], lst)

sums([1,2,3], 0, 2)
