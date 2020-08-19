from collections import defaultdict
from functools import cmp_to_key
import sys


class Trip:
    def __init__(self):
        self.ordered_at = None
        self.arrived_at = None
        self.started_at = None
        self.finished_at = None
        self.user_id = None
        self.X = None
        self.Y = None

    def is_broken(self) -> bool:
        return (self.ordered_at is None) or (self.arrived_at is None) or (self.started_at is None) or (self.finished_at is None)


def my_cmp(a, b):
    print(a, b, sep=" ")
    if a[0] == b[0]:
        return a[1] < b[1]
    else:
        return a[0] > b[0]


t = int(sys.stdin.readline().strip())

for _ in range(t):
    events_count, users_count, K = [int(i) for i in sys.stdin.readline().strip().split(' ')]

    trips = defaultdict(Trip)
    total_waiting_time = defaultdict(int)

    for i in range(events_count):
        data = sys.stdin.readline().strip().split(' ')
        query_type, order_id, other = data[0], data[1], data[2:]
        if query_type == "ordered":
            trips[order_id].user_id = other[0]
            trips[order_id].ordered_at = int(other[1])
            trips[order_id].X = int(other[2])
            trips[order_id].Y = int(other[3])
        elif query_type == "arrived":
            trips[order_id].arrived_at = int(other[0])
        elif query_type == "started":
            trips[order_id].started_at = int(other[0])
        elif query_type == "finished":
            trips[order_id].finished_at = int(other[0])

    for trip in trips.values():
        if (trip.is_broken()):
            continue
        if (trip.started_at - trip.arrived_at) > (K * 60):
            continue

        total_waiting_time[trip.user_id] += max(trip.finished_at - (trip.ordered_at + (trip.X + trip.Y + K) * 60), 0)

    new_total_waiting_time = dict()
    for i, j in total_waiting_time.items():
        if j > 0:
            new_total_waiting_time[i] = j
    total_waiting_time = new_total_waiting_time

    if (len(total_waiting_time) == 0) or (users_count == 0):
        print('-')
    else:
        ans = [(-item[1], item[0]) for item in total_waiting_time.items()]
        ans.sort()
        print(' '.join([i[1] for i in ans[:users_count]]))
