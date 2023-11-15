def solve():
    d_day = int(input())
    counsel_list = list()

    for d in range(d_day):
        counsel = list(map(int, input().split(" ")))
        counsel.append(d)
        counsel_list.append(counsel)

    for item in counsel_list[:]:
        if item[0] + item[2] > d_day:
            counsel_list.remove(item)
    # 1. 처음부터 답안에 포함될 수 있는지를 상담 리스트를 순회하면서 확인함.

    result_list = list()
    result_list.append(counsel_list.pop())

    for i in range(len(counsel_list) - 1, -1, -1):
        victims = list()
        for item in result_list[:]:
            if item[2] <= counsel_list[i][0] - 1 + counsel_list[i][2]:
                # item.d < c.d + c.t 인지 확인
                victims.append(item)
                result_list.remove(item)

        if len(victims) == 0:
            result_list.append(counsel_list[i])
        else:
            victims_cost = 0
            for v in victims:
                victims_cost += v[1]
            if victims_cost < counsel_list[i][1]:
                result_list.append(counsel_list[i])
            else:
                while len(victims) != 0:
                    result_list.append(victims.pop())

    sum = 0
    for r in result_list:
        sum += r[1]
    print(sum)


solve()
