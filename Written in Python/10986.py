# 수 N개 A1, A2, ..., AN이 주어진다. 
#이때, 연속된 부분 구간의 합이 M으로 나누어 떨어지는 구간의 개수를 구하는 프로그램을 작성하시오.
# 즉, Ai + ... + Aj (i ≤ j) 의 합이 M으로 나누어 떨어지는 (i, j) 쌍의 개수를 구해야 한다.

# 입력
# 첫째 줄에 N과 M이 주어진다. (1 ≤ N ≤ 106, 2 ≤ M ≤ 103)
# 둘째 줄에 N개의 수 A1, A2, ..., AN이 주어진다. (0 ≤ Ai ≤ 109)

# 출력
# 첫째 줄에 연속된 부분 구간의 합이 M으로 나누어 떨어지는 구간의 개수를 출력한다.


def get_combinations(seq:list, M:int) -> int:
    # 모듈러 연산 성질 이용 
    # (a - b) % n = ((a % n) - (b % n)) % n
    # (a + b) % n = ((a % n) + (b % n)) % n
    # 누적합 리스트를 구하면 [0, a1 , a1+a2, ..., a1+...+an]
    # 이를 누적합[m] - 누적합[k (k는 m보다 작음)] 꼴이면 모든 연속된 구간합을 구할 수 있음 
    # (Sum1 - Sum2) % n = 0 이려면 ((sum1 % n) - (sum2 % n)) % n = 0 이어야 함 
    # 따라서 sum1 % n = sum2 % n 이어야 됨. 둘다 같은 remainder 이어야 함.
    count_list = [0 for i in range(M)] # 나머지

    for i in range(1, len(seq)):
        seq[i] = ((seq[i] % M) + (seq[i-1] % M)) % M
        count_list[seq[i]] += 1
    
    # 나머지가 0인 부분합을 만드는 조합은
    # 나머지가 같은 부분합에 대해 고를 수 있는 경우의 수는 
    # 구간 (0, 나머지가 같은 누적합들 -1) 까지의 합이다. 
    combination = 0
    for count in count_list:
    # Case 1. 부분합을 만드는 조합을 짰을 때 나머지가 같은 두 누적합을 고르는 경우의 수
        if(count >= 2):
            combination += sum(range(0,count))
    
    combination += count_list[0] 
    # Case 2. 누적합 그 자체가 이미 나머지가 0인 경우
    
    return combination


M = int(input().split(" ")[1])
second_line = input().split(" ")
seq = [] # 수열
seq.append(0)
for char in second_line:
    seq.append(int(char))
remainder_sum = get_combinations(seq, M)
print(remainder_sum)

    