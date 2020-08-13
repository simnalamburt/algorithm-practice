from datetime import date, timedelta
startdate, days = input().split()
days = int(days) - 1

print((date.fromisoformat(startdate) + timedelta(days=days)).isoformat())
