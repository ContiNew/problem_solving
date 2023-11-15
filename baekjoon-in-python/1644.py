import math

def isPrime(n : int)-> bool:  # 소수 판정
    border = round(math.sqrt(n))
    for i in range (2, border):
        if(n % i == 0):
            return False
    return True

def getPrimesUnder(n: int)-> list: # 에라토스테네스의 체 이용 n 이하의 소수를 모두 구함
    multiple_checklist = []
    prime_under_n = []
    border = round(math.sqrt(n))
    for i in range(2, border):
        if (isPrime(i) == True):
            multiple_checklist.append(i)
    for i in range(2, n+1):
        flag = True
        for j in multiple_checklist:
            if (i % j == 0 and i != j):
                flag = False
                break
        if(flag): 
            prime_under_n.append(i)
    return prime_under_n

def count_combination(n: int)-> int: # 콤비네이션을 카운트 한다. 
    prime_under_n = getPrimesUnder(n)
    tmp = n; i = 0; count = 0
    for pivot in prime_under_n: 
        flag = False
        tmp = n
        for p in prime_under_n[i:]:
            tmp -= p
            if(tmp == 0):
                flag = True
                break
            if(tmp <0): break
        i += 1
        if(flag): count += 1
    return count

N = int(input())
combinations = count_combination(N)
print(combinations)
            
        
            

    