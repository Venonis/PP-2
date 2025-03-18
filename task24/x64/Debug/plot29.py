import pandas as pd
import subprocess
import time
import re
from matplotlib import pyplot as plt

# Конфигурация параметров тестирования
threads_counts = [1, 2, 4, 6, 8, 10, 12]
iterations = [100, 10_000_000, 4_000_000_000]
results = []

def run_mpi_program(threads, num_intervals):
    """Запускает MPI-программу и возвращает время выполнения и значение pi"""
    start_time = time.time()
    
    proc = subprocess.Popen(
        ['mpiexec', '-n', str(threads), 'task24.exe'],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True
    )
    
    # Передаем входные данные и получаем вывод
    stdout, _ = proc.communicate(str(num_intervals) + '\n')
    duration = time.time() - start_time
    
    # Парсим результат
    pi_match = re.search(r'Computed value of pi: ([\d.]+)', stdout)
    pi_value = float(pi_match.group(1)) if pi_match else None
    
    return duration, pi_value

if __name__ == '__main__':
    for threads in threads_counts:
        for n in iterations:
            print(f'Running: {threads} threads, {n} intervals...')
            
            try:
                time_taken, pi = run_mpi_program(threads, n)
                results.append({
                    'Threads': threads,
                    'Intervals': n,
                    'Time (s)': time_taken,
                    'Pi Value': pi
                })
            except Exception as e:
                print(f'Error: {e}')
                continue

    # Создаем и сохраняем таблицу
    df = pd.DataFrame(results)
    df.to_csv('pi_calculation_results.csv', index=False)
    print("\nResults saved to pi_calculation_results.csv")
    
    # Строим графики
    plt.figure(figsize=(12, 8))
    
    for n in iterations:
        subset = df[df['Intervals'] == n]
        plt.plot(subset['Threads'], subset['Time (s)'], 
                marker='o', label=f'{n:,} intervals')
    
    plt.xlabel('Number of MPI Processes')
    plt.ylabel('Execution Time (s)')
    plt.title('MPI Pi Calculation Performance')
    plt.legend()
    plt.grid(True)
    plt.savefig('mpi_pi_performance.png')
    print("Plot saved to mpi_pi_performance.png")