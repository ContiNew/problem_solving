import sys

def star_pattern(n:int,index:list,matrix:list):
    if(n==3):
        #base case
        row = index[0]; col = index[1]
        for i in range(row, row+3):
            for j in range(col, col+3):
                if(i-row == 1 and j-col == 1): matrix[i][j] =" "
                else: matrix[i][j] ="*"
    else:
        #recursive case
        point = int(n/3)
        vacant_x = index[0]+point
        vacant_y = index[1]+point
        for i in range(vacant_x, vacant_x+point):
            for j in range(vacant_y,vacant_y+point):
                matrix[i][j] = " "
        #일단 주어진 매트릭스의 중앙을 뚫는다. 
        
        for i in range(0 , 3):
            for j in range(0 , 3):
                target_x = index[0]+i*point
                target_y = index[1]+j*point
                if(vacant_x == target_x and vacant_y == target_y): continue
                param_idx = [target_x, target_y]
                star_pattern(point, param_idx, matrix)
            
            
N=int(input())
matt = [[" " for col in range(N)]for row in range(N)]
star_pattern(N,[0,0],matt)

for row in matt:
    for col in row:
        print(col,end="")
    print()
