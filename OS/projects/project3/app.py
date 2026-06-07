# ─────────────────────────────────────────────
# FCFS CPU Scheduling Algorithm
# Operating Systems Project
# Section: 2673
#        <<< Dr. Alwaleed Alharbi >>>
# ─────────────────────────────────────────────


def fcfs_scheduling(processes):
    """
    FCFS Scheduling Algorithm
    Input: list of processes (pid, at, bt)
    Output: processes with ct, tat, wt
    """

    # Sort processes by Arrival Time
    processes.sort(key=lambda p: p['at'])

    current_time = 0

    for process in processes:

        # If CPU is idle, jump to arrival time
        if current_time < process['at']:
            current_time = process['at']

        # Completion Time
        process['ct'] = current_time + process['bt']
        current_time = process['ct']

        # Turnaround Time
        process['tat'] = process['ct'] - process['at']

        # Waiting Time
        process['wt'] = process['tat'] - process['bt']

    return processes


def print_results(processes):
    """Display FCFS results in a table"""

    print("\n" + "=" * 50)
    print(" FCFS CPU Scheduling Results")
    print("=" * 50)

    print(f"{'PID':<10}{'AT':<6}{'BT':<6}{'CT':<6}{'TAT':<6}{'WT':<6}")
    print("-" * 50)

    for p in processes:
        print(f"{p['pid']:<10}{p['at']:<6}{p['bt']:<6}"
              f"{p['ct']:<6}{p['tat']:<6}{p['wt']:<6}")

    print("-" * 50)

    n = len(processes)

    avg_tat = sum(p['tat'] for p in processes) / n
    avg_wt = sum(p['wt'] for p in processes) / n

    print(f"\nAverage Turnaround Time = {avg_tat:.2f}")
    print(f"Average Waiting Time     = {avg_wt:.2f}")


def main():

    print("=== FCFS CPU Scheduling Simulator ===")

    n = int(input("Enter number of processes: "))
    processes = []

    for i in range(n):
        pid = input("Process ID: ")
        at = int(input("Arrival Time: "))
        bt = int(input("Burst Time: "))

        processes.append({
            'pid': pid,
            'at': at,
            'bt': bt
        })

    result = fcfs_scheduling(processes)
    print_results(result)


if __name__ == "__main__":
    main()
