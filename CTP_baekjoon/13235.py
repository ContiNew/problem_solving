def check_p(word: str, front: int, rear: int) -> bool:
    if front > rear:
        return True
    elif word[front] == word[rear]:
        return check_p(word, front + 1, rear - 1)
    elif word[front] != word[rear]:
        return False


word = input()
if check_p(word, 0, len(word) - 1):
    print("true")
else:
    print("false")
