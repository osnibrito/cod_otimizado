import subprocess
import os
import pandas as pd
import io
import re

N_COMPILE = 100

def write_csv(d: dict, filename: str):
    f = open(filename,'w')
    f.write(f"program,flag,time_compile,time_run\n")

    for program in d:
        for flag in d[program]:
            nameflag = flag
            if flag == "":
                nameflag = "no-flag"
            for i in range(N_COMPILE):
                f.write(f"{program},{nameflag},{d[program][flag]['time_compile'][i]},{d[program][flag]['time_run'][i]}\n")

    f.close()
    return

def get_time_run(command: str) -> list:
    timing = []

    for _ in range(N_COMPILE):
        process = subprocess.Popen(
            command, 
            shell=True, 
            stderr=subprocess.PIPE, 
            executable='/bin/bash'
        )
        process.wait()
        _, info_bytes = process.communicate()
        info = str(info_bytes, 'UTF-8')
        real_time = info.split("\n")[1]

        real_time = real_time.split("\t")[1]
        m, s, ms = re.findall('(\d+)[m](\d+)\,(\d+)', real_time)[0]
        final_ms = float(m) * 60000 + float(s) * 1000 + float(ms)

        timing.append(final_ms)
    return timing

if __name__ == "__main__":
    programs = ["spectral", "n_body"]
    flags = ["", "O1", "O2", "O3", "Os"]
    data = {}
    for program in programs:
        data[program] = {}
        for flag in flags:
            data[program][flag] = {}
            command_compile = f"time make {program}"
            command_run = f"time make run_{program}"

            if flag:
                args = f" ARGS=\"-{flag}\""
                command_compile += args
                command_run += args
                
            print(command_compile)
            data[program][flag]["time_compile"] = get_time_run(command_compile)
            print(command_run)
            data[program][flag]["time_run"] = get_time_run(command_run)
    print(data)
    write_csv(data, "datatime.csv")
    
