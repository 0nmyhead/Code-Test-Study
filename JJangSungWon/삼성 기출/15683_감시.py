import sys
import copy


def dfs(idx):
    global min_area, arr
    if idx == len(position):
        temp = 0
        for i in range(N):
            for j in range(M):
                if arr[i][j] == 0:
                    temp += 1
        min_area = min(min_area, temp)
    else:
        value, row, col = position[idx]
        temp = copy.deepcopy(arr)
        if value == 1:
            # ��
            for i in range(row - 1, -1, -1):
                if arr[i][col] == 0:
                    arr[i][col] = '#'
                elif arr[i][col] == 6:
                    break
            dfs(idx + 1)

            # ��
            arr = copy.deepcopy(temp)
            for i in range(row + 1, N):
                if arr[i][col] == 0:
                    arr[i][col] = '#'
                elif arr[i][col] == 6:
                    break
            dfs(idx + 1)

            # ��
            arr = copy.deepcopy(temp)
            for i in range(col -1, -1, -1):
                if arr[row][i] == 0:
                    arr[row][i] = '#'
                elif arr[row][i] == 6:
                    break
            dfs(idx + 1)

            # ��
            arr = copy.deepcopy(temp)
            for i in range(col + 1, M):
                if arr[row][i] == 0:
                    arr[row][i] = '#'
                elif arr[row][i] == 6:
                    break
            dfs(idx + 1)
        elif value == 2:
            # ��, ��
            for i in range(row - 1, -1, -1):
                if arr[i][col] == 0:
                    arr[i][col] = '#'
                elif arr[i][col] == 6:
                    break
            for i in range(row + 1, N):
                if arr[i][col] == 0:
                    arr[i][col] = '#'
                elif arr[i][col] == 6:
                    break
            dfs(idx + 1)

            # ��, ��
            arr = copy.deepcopy(temp)
            for i in range(col -1, -1, -1):
                if arr[row][i] == 0:
                    arr[row][i] = '#'
                elif arr[row][i] == 6:
                    break
            for i in range(col + 1, M):
                if arr[row][i] == 0:
                    arr[row][i] = '#'
                elif arr[row][i] == 6:
                    break
            dfs(idx + 1)
        elif value == 3:
            # ��, ��
            for i in range(row - 1, -1, -1):
                if arr[i][col] == 0:
                    arr[i][col] = '#'
                elif arr[i][col] == 6:
                    break
            for i in range(col + 1, M):
                if arr[row][i] == 0:
                    arr[row][i] = '#'
                elif arr[row][i] == 6:
                    break
            dfs(idx + 1)

            # ��, ��
            arr = copy.deepcopy(temp)
            for i in range(col + 1, M):
                if arr[row][i] == 0:
                    arr[row][i] = '#'
                elif arr[row][i] == 6:
                    break
            for i in range(row + 1, N):
                if arr[i][col] == 0:
                    arr[i][col] = '#'
                elif arr[i][col] == 6:
                    break
            dfs(idx + 1)

            # ��, ��
            arr = copy.deepcopy(temp)
            for i in range(row + 1, N):
                if arr[i][col] == 0:
                    arr[i][col] = '#'
                elif arr[i][col] == 6:
                    break
            for i in range(col -1, -1, -1):
                if arr[row][i] == 0:
                    arr[row][i] = '#'
                elif arr[row][i] == 6:
                    break
            dfs(idx + 1)

            # ��, ��
            arr = copy.deepcopy(temp)
            for i in range(col -1, -1, -1):
                if arr[row][i] == 0:
                    arr[row][i] = '#'
                elif arr[row][i] == 6:
                    break
            for i in range(row - 1, -1, -1):
                if arr[i][col] == 0:
                    arr[i][col] = '#'
                elif arr[i][col] == 6:
                    break
            dfs(idx + 1)
        elif value == 4:
            # ��, ��, ��
            for i in range(col -1, -1, -1):
                if arr[row][i] == 0:
                    arr[row][i] = '#'
                elif arr[row][i] == 6:
                    break
            for i in range(row - 1, -1, -1):
                if arr[i][col] == 0:
                    arr[i][col] = '#'
                elif arr[i][col] == 6:
                    break
            for i in range(col + 1, M):
                if arr[row][i] == 0:
                    arr[row][i] = '#'
                elif arr[row][i] == 6:
                    break
            dfs(idx + 1)

            # ��, ��, ��
            arr = copy.deepcopy(temp)
            for i in range(row - 1, -1, -1):
                if arr[i][col] == 0:
                    arr[i][col] = '#'
                elif arr[i][col] == 6:
                    break
            for i in range(col + 1, M):
                if arr[row][i] == 0:
                    arr[row][i] = '#'
                elif arr[row][i] == 6:
                    break
            for i in range(row + 1, N):
                if arr[i][col] == 0:
                    arr[i][col] = '#'
                elif arr[i][col] == 6:
                    break
            dfs(idx + 1)

            # ��, ��, ��
            arr = copy.deepcopy(temp)
            for i in range(col + 1, M):
                if arr[row][i] == 0:
                    arr[row][i] = '#'
                elif arr[row][i] == 6:
                    break
            for i in range(row + 1, N):
                if arr[i][col] == 0:
                    arr[i][col] = '#'
                elif arr[i][col] == 6:
                    break
            for i in range(col -1, -1, -1):
                if arr[row][i] == 0:
                    arr[row][i] = '#'
                elif arr[row][i] == 6:
                    break
            dfs(idx + 1)

            # ��, ��, ��
            arr = copy.deepcopy(temp)
            for i in range(row + 1, N):
                if arr[i][col] == 0:
                    arr[i][col] = '#'
                elif arr[i][col] == 6:
                    break
            for i in range(col -1, -1, -1):
                if arr[row][i] == 0:
                    arr[row][i] = '#'
                elif arr[row][i] == 6:
                    break
            for i in range(row - 1, -1, -1):
                if arr[i][col] == 0:
                    arr[i][col] = '#'
                elif arr[i][col] == 6:
                    break
            dfs(idx + 1)
        else:
            # ��
            for i in range(row - 1, -1, -1):
                if arr[i][col] == 0:
                    arr[i][col] = '#'
                elif arr[i][col] == 6:
                    break
            # ��
            for i in range(row + 1, N):
                if arr[i][col] == 0:
                    arr[i][col] = '#'
                elif arr[i][col] == 6:
                    break
            # ��
            for i in range(col -1, -1, -1):
                if arr[row][i] == 0:
                    arr[row][i] = '#'
                elif arr[row][i] == 6:
                    break
            # ��
            for i in range(col + 1, M):
                if arr[row][i] == 0:
                    arr[row][i] = '#'
                elif arr[row][i] == 6:
                    break
            dfs(idx + 1)


if __name__ == "__main__":

    # input
    N, M = map(int, sys.stdin.readline().split())  # ����, ����
    arr = [list(map(int, sys.stdin.readline().split())) for _ in range(N)]

    # CCTY ��ġ ��������
    position = []
    for i in range(N):
        for j in range(M):
            if arr[i][j] != 0 and arr[i][j] != 6:
                position.append(([arr[i][j], i, j]))

    min_area = sys.maxsize
    dfs(0)
    print(min_area)