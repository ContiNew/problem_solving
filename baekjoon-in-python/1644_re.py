import math

def primes_under_n(n : int) -> list: # 에라토스테네스의 체 이용
    prime_list = [True for i in range(n+1)]
    root_of_n = round(math.sqrt(n))
    prime_list[0:2] = [False,False] # 0, 1은 해당 안됨
    for i in range (2,root_of_n+1):
        if prime_list[i] == True:
            for j in range(2, math.ceil(n/i)+1):
                if(i*j>n): continue
                prime_list[i*j] = False
    return prime_list

def check_combination(n :int) -> int:
    prime_list = primes_under_n(n)
    prime_numbers = []
    for i in range(2, n+1):
        if prime_list[i] == True:
            prime_numbers.append(i)
    count = 0
    left = 0; right = 1
    while(left < right and right <= len(prime_numbers) ):  #  투 포인터 이용
        if(sum(prime_numbers[left:right]) < n):
            right += 1
        elif(sum(prime_numbers[left:right]) > n):
            left += 1
        else:
            count += 1
            left += 1
    return count

N = int(input())
result = check_combination(N)
print(result)