def pelindrome(s: str) -> bool:
    i, j = 0, len(s) - 1
    # i는 앞에서 부터 뒤 인덱스를 탐색, j는 뒤에서 부터 앞 인덱스를 탐색
    while i < j:
        if s[i] != s[j]:
            return False
        i += 1
        j -= 1

    return True


def pelindrome_recursion(s: str, front: int, rear: int) -> bool:
    if front >= rear:
        return True

    if s[front] == s[rear]:
        return pelindrome_recursion(s, front + 1, rear - 1)
    else:
        return False


s = input()
print(pelindrome(s))
print(pelindrome_recursion(s, 0, len(s) - 1))
