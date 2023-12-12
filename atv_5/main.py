from timeit import timeit
import functools

NUM_TESTS_FIB = 100
NUM_TESTS_CONCAT = 100

#Teste de otimização de memoização com sequência de fibonacci recursiva
def fib(n):
    if (n <= 1):
        return 1
    else:
        return fib(n-1) + fib (n-2)
    
@functools.lru_cache()
def fib_optimized(n):
    if (n <= 1):
        return 1
    else:
        return fib_optimized(n-1) + fib_optimized(n-2)

#Teste de otimização de concatenação de strings
def read_words_from_file(file_path):
    with open(file_path, 'r') as file:
        file_content = file.read()
        words = file_content.split()
        return words
    
def string_from_array(arr):
    result = ""
    for item in arr:
        result += str(item)
    return result

def string_from_array_optimized(arr):
    result_parts = []
    for item in arr:
        result_parts.append(str(item))
    result = "".join(result_parts)

if __name__ == '__main__':
    # fib(30)
    time_taken = timeit("fib(30)", setup="from __main__ import fib", number=NUM_TESTS_FIB)
    average_time_per_call = time_taken / NUM_TESTS_FIB
    print(f"Tempo médio de fib(30), sem otimizações, com {NUM_TESTS_FIB} testes: {average_time_per_call} segundos")
    
    # fib_optimized(30)
    time_taken = timeit("fib_optimized(30)", setup="from __main__ import fib_optimized", number=NUM_TESTS_FIB)
    average_time_per_call = time_taken / NUM_TESTS_FIB
    print(f"Tempo médio de fib_optimized(30), com memoização, com {NUM_TESTS_FIB} testes: {average_time_per_call} segundos")
    
    # Concatenação de strings
    script = read_words_from_file("shrek_script.txt")
    
    # string_from_array(script)
    time_taken = timeit("string_from_array(script)", setup="from __main__ import string_from_array, script", number=NUM_TESTS_CONCAT)
    average_time_per_call = time_taken / NUM_TESTS_CONCAT
    print(f"Tempo médio de string_from_array, sem otimizações, com {NUM_TESTS_CONCAT} testes: {average_time_per_call} segundos")

    # string_from_array_optimized(script)
    time_taken = timeit("string_from_array_optimized(script)", setup="from __main__ import string_from_array_optimized, script", number=NUM_TESTS_CONCAT)
    average_time_per_call = time_taken / NUM_TESTS_CONCAT
    print(f"Tempo médio de string_from_array_optimized, com otimização, com {NUM_TESTS_CONCAT} testes: {average_time_per_call} segundos")
