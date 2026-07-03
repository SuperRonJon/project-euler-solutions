#include <stdbool.h>
#include <stdio.h>
#include <string.h>

enum weekday
{
	SUNDAY = 0,
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY
};

enum month
{
	JANUARY = 0,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER
};

void weekday_string(char *buff, const enum weekday day)
{
	static const char* const weekday_lookup[] = {
		"Sunday",
		"Monday",
		"Tuesday",
		"Wednesday",
		"Thursday",
		"Friday",
		"Saturday"
	};
	int index = (int)day;
	strcpy(buff, weekday_lookup[index]);
	return;
}

void month_string(char *buff, const enum month m)
{
	static const char* const month_lookup[] = {
		"January",
		"February",
		"March",
		"April",
		"May",
		"June",
		"July",
		"August",
		"September",
		"October",
		"November",
		"December",
	};
	int index = (int)m;
	strcpy(buff, month_lookup[index]);
	return;
}

int days_in_month(const enum month m, const bool is_leapyear)
{
	switch (m)
	{
		case SEPTEMBER:
		case APRIL:
		case JUNE:
		case NOVEMBER:
			return 30;
		case FEBRUARY:
			return is_leapyear ? 29: 28;
		default:
			return 31;
	}
}

bool is_leap_year(const int year)
{
	if (year % 4 == 0)
	{
		if (year % 100 == 0)
		{
			return year % 400 == 0;
		}
		return true;
	}
	return false;
}

struct date
{
	int date;
	enum month month;
	int year;
	enum weekday day;
};

void increment_date(struct date *d)
{
	const int max_days = days_in_month(d->month, is_leap_year(d->year));
	d->date++;
	if (d->date > max_days)
	{
		d->date = 1;
		d->month = (d->month + 1) % 12;
		if (d->month == JANUARY)
			d->year++;
	}
	d->day = (d->day + 1) % 7;
}

void increment_n(struct date *d, const int n)
{
	for (int i = 0; i < n; i++)
	{
		increment_date(d);
	}
}

void print_date(const struct date *d)
{
	char weekday_str[10];
	char month_str[10];
	weekday_string(weekday_str, d->day);
	month_string(month_str, d->month);

	printf("%s %s %d, %d\n", weekday_str, month_str, d->date, d->year);
}

int main(int argc, char **argv)
{
	struct date curr_date = {7, JANUARY, 1900, SUNDAY};
	int sunday_count = 0;
	while (curr_date.year < 2001)
	{
		if (curr_date.year >= 1901 && curr_date.day == SUNDAY && curr_date.date == 1)
		{
			sunday_count++;
		}
		increment_date(&curr_date);
	}
	printf("Sundays: %d\n", sunday_count);
 }
