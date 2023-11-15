def longest_pelindrome(s: str) -> str:
    base_pelindrome = []
    candidates = []
    # 길이가 2인 펠린드롬 부분 문자열을 찾는다.
    for i in range(len(s) - 1):
        if s[i] == s[i + 1]:
            base_pelindrome.append((i, i + 1))

    # 길이가 3인 펠린드롬 부분 문자열을 찾는다.
    for i in range(len(s) - 2):
        if s[i] == s[i + 2]:
            base_pelindrome.append((i, i + 2))

    # 베이스 펠린드롬에서 확장해가면서 찾는다.
    for base in base_pelindrome:
        front, rear = base[0], base[1]
        while front >= 0 and rear < len(s):
            if s[front] == s[rear]:
                candidates.append((front, rear))
                front -= 1
                rear += 1
            else:
                break

    nowmax = (0, 0)

    for candidate in candidates:
        if nowmax[1] - nowmax[0] < candidate[1] - candidate[0]:
            nowmax = candidate

    return s[nowmax[0] : nowmax[1] + 1]


s = input()
print(longest_pelindrome(s))
