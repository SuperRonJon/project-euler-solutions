import sys
import time

def sum_lines(filename):
    total = 0
    file = sys.stdin if filename is None else open(filename, "r")
    for line in file:
        total += int(line.strip())
    if filename is not None:
        file.close()
    return total

if __name__ == "__main__":
    filename = None
    if len(sys.argv) == 2:
        filename = sys.argv[1]

    start_time = time.perf_counter_ns()

    total = sum_lines(filename)

    end_time = time.perf_counter_ns()

    time_diff = end_time - start_time
    elapsed_sec = int(time_diff / 1000000000)
    elapsed_nsec = time_diff % 1000000000
    elapsed_time_sec = time_diff / 1000000000.0

    print(f"Sum:               {total}")
    print(f"First 10 digits:   {str(total)[:10]}")
    print(f"Elapsed time:      {elapsed_time_sec:.8f}s")
    print(f"                   {elapsed_sec}s {elapsed_nsec}ns")

