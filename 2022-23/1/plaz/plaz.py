from typing import List, Tuple, NamedTuple, Deque

# from dataclasses import dataclass
from collections import deque

# class QueueItem:
#     __slots__ = ["x", "y", "prkno", "trace"]
#     def __init__(self, x, y, prkno, trace):
#         self.x = x
#         self.y = y
#         self.prkno = prkno
#         self.trace = trace


class QueueItem(NamedTuple):
    x: int
    y: int
    has_board: bool
    trace: List[Tuple[int, int]]


def task(
    m: List[List[bool]],
    n: int,
    start: Tuple[int, int],
    finish: Tuple[int, int],
    has_board: bool,
) -> List[Tuple[int, int]] | None:
    visited = [[False for _ in range(n)] for _ in range(n)]
    visited[start[1]][start[0]] = True
    queue: Deque[QueueItem] = deque([])
    if has_board:
        visited_without_board = [[False for _ in range(n)] for _ in range(n)]
        # visited_without_board[start[1]][start[0]] = True
    if not m[start[1]][start[0]]:
        queue.append(QueueItem(start[0], start[1], has_board, []))
    while len(queue) > 0:
        current = queue.popleft()
        if (current.x, current.y) == finish:
            return [*current.trace, (current.x, current.y)]
        for x, y in [
            (current.x, current.y - 1),
            (current.x, current.y + 1),
            (current.x - 1, current.y),
            (current.x + 1, current.y),
        ]:
            if 0 <= x < n and 0 <= y < n:
                if has_board:
                    if (
                        current.has_board
                        and m[y][x]
                        and not visited_without_board[y][x]
                    ):
                        visited_without_board[y][x] = True
                        queue.append(
                            QueueItem(
                                x,
                                y,
                                False,
                                [*current.trace, (current.x, current.y)]
                            )
                        )
                    elif (
                        not current.has_board
                        and not visited_without_board[y][x]
                        and not m[y][x]
                    ):
                        visited_without_board[y][x] = True
                        queue.append(
                            QueueItem(
                                x,
                                y,
                                current.has_board,
                                [*current.trace, (current.x, current.y)],
                            )
                        )
                    elif (
                        current.has_board
                        and not visited[y][x]
                        and not m[y][x]
                    ):
                        visited[y][x] = True
                        queue.append(
                            QueueItem(
                                x,
                                y,
                                current.has_board,
                                [*current.trace, (current.x, current.y)],
                            )
                        )
                elif not m[y][x] and not visited[y][x]:
                    visited[y][x] = True
                    queue.append(
                        QueueItem(
                            x,
                            y,
                            current.has_board,
                            [*current.trace, (current.x, current.y)],
                        )
                    )
    return None


def main():
    # Input parsing
    n = int(input())
    start = tuple([int(x) for x in input().split()])
    finish = tuple([int(x) for x in input().split()])
    has_board = bool(int(input()))
    k = int(input())
    m = [[False for _ in range(n)] for _ in range(n)]
    for _ in range(k):
        [x, y] = [int(x) for x in input().split()]
        m[y][x] = True

    # Run the algorithm
    result = task(m, n, start, finish, has_board)

    # Printing result
    if result is None:
        print("Nema reseni.")
        return
    print(len(result) - 1)
    for item in result:
        print(item[0], item[1])


if __name__ == "__main__":
    main()
