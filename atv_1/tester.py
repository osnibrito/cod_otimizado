import subprocess
import os
import pandas as pd
import io

n = 10

# Dado um arquivo binario retorna informacoes de teste
# 'L1-dcache-load', 'L1-dcache-load-misses', 'branch-instructions', 'branch-misses' 'time'
# em um df de uma linha

def info_by_bin(file, command):
    process_perf = subprocess.Popen(command + file, shell=True, stderr=subprocess.PIPE)
    _, info_bytes = process_perf.communicate()
    info = str(info_bytes, 'UTF-8')
    df = pd.read_csv(io.StringIO(info), sep=';', usecols=[0, 3], header=None)
    timing = df.iat[0,1]
    df = df.drop(df.columns[1], axis=1).transpose()
    df.columns = metrics
    df['time'] = timing
    return df

metrics = ['L1-dcache-load', 'L1-dcache-load-misses', 'branch-instructions', 'branch-misses']
perf_command = f"perf stat --field-separator ';' -e {','.join(metrics)} ./bin/"

# gera binarios
process = subprocess.Popen('make all', shell=True)
process.wait()
files = os.listdir("./bin")

execs = []
# Rodando para todo arquivo binario
for file in files:

    # n testes para cada arquivo
    for i in range(n):
        line = info_by_bin(file, perf_command)
        line['run'] = i
        line['file'] = file
        execs.append(line)

# Une todas informacoes em um unico df
df = pd.concat(execs)
df.to_csv('data.csv', index=False)

subprocess.Popen('make clean', shell=True)

