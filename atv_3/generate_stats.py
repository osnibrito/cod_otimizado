import pandas as pd

def get_stats(df: pd.DataFrame) -> (dict):
    dict_stat = {}
    
    print("compile ", df["time_compile"].std())
    print("RUN ", df["time_run"].std())

    dict_stat["min_compile"] = df["time_compile"].min()
    dict_stat["max_compile"] = df["time_compile"].max()
    dict_stat["media_compile"] = df["time_compile"].mean()
    dict_stat["mediana_compile"] = df["time_compile"].median()
    dict_stat["desvio_compile"] = round(df["time_compile"].std())
    
    dict_stat["min_run"] = df["time_run"].min()
    dict_stat["max_run"] = df["time_run"].max()
    dict_stat["media_run"] = df["time_run"].mean()
    dict_stat["mediana_run"] = df["time_run"].median()
    dict_stat["desvio_run"] = round(df["time_run"].std())
    return dict_stat

f = open("stats.csv",'w')
f.write(f"program,flag,min_compile,max_compile,media_compile,mediana_compile,desvio_compile,min_run,max_run,media_run,mediana_run,desvio_run\n")

df = pd.read_csv("datatime.csv", sep=",")
print(df.head())
spectral = df[df["program"] == "spectral"]
n_body = df[df["program"] == "n_body"]

stat_run = {}
print(df[df["flag"] == pd.NA])
for flag in df["flag"].unique():
    spectral_filter = spectral[spectral["flag"] == flag]
    n_body_filter = n_body[n_body["flag"] == flag]
    
    if n_body_filter.empty:
        print(flag)
        continue
    
    stat_run["spectral_"+flag] = get_stats(spectral_filter)
    f.write(f"spectral,{flag}")
    for value in stat_run["spectral_"+flag].values():
        f.write(f",{value}")

    stat_run["n_body_"+flag] = get_stats(n_body_filter)
    f.write(f"\nn_body,{flag}")
    
    for value in stat_run["n_body_"+flag].values():
        f.write(f",{value}")
    f.write(f"\n")


for key in stat_run.keys():
    print(key)
    print(stat_run[key].values())

df = pd.DataFrame(stat_run).columns