import subprocess
import sys

process_numbers =  [1, 2, 4, 8, 16, 32, 64, 128, 256]
interval_numbers = [10**6, 10**7, 10**8, 10**9, 10**10]

for intervals in interval_numbers:
    for processes in process_numbers:
        command = ['mpirun', '-np', str(processes+1), './hw3', f'-DINTERVALS={intervals}']
        subprocess.run(command, stdout = sys.stdout)
