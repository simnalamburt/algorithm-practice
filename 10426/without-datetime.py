def is_leap_year(year: int) -> bool:
    '''
    윤년은 연도가 4의 배수이면서, 100의 배수가 아닐 때 또는 400의 배수일 때이다.

    Example:
        is_leap_year(1899) # False
        is_leap_year(1900) # False
        is_leap_year(2000) # True
        is_leap_year(2004) # True
        is_leap_year(2100) # False
    '''
    return (year % 4 == 0 and not (year % 100 == 0)) or year % 400 == 0

def dates_in_month(year: int, month: int) -> int:
    if month == 1:
        return 31
    elif month == 2:
        return 29 if is_leap_year(year) else 28
    elif month == 3:
        return 31
    elif month == 4:
        return 30
    elif month == 5:
        return 31
    elif month == 6:
        return 30
    elif month == 7:
        return 31
    elif month == 8:
        return 31
    elif month == 9:
        return 30
    elif month == 10:
        return 31
    elif month == 11:
        return 30
    elif month == 12:
        return 31


def is_date_overflow(year: int, month: int, date: int) -> bool:
    return date > dates_in_month(year, month)

startdate, delta_in_days = input().split()
year, month, date = map(int, startdate.split('-'))
date += int(delta_in_days) - 1

while is_date_overflow(year, month, date):
    date -= dates_in_month(year, month)
    month += 1
    if month > 12:
        month -= 12
        year += 1

print(f'{year}-{month:02}-{date:02}')
