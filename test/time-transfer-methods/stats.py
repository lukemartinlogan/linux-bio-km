
import os, sys
import pandas as pd
import re
from functools import reduce

def get_all_txt(dir):
    paths = []
    all_fns = os.listdir(dir)
    for fn in all_fns:
        path = os.path.join(dir, fn)
        if os.path.isdir(path):
            paths += get_all_txt(path)
        if re.search("\.txt", path):
            paths.append(path)
    return paths

######MAIN
if len(sys.argv) != 2:
    print("Usage: python3 /path/to/time-transfer-stats.py [log-dir]")
    sys.exit(1)

log_dir = sys.argv[1]
print(sys.argv[2])
log_files = get_all_txt(log_dir)

dict_df = []
for log_file in log_files:
    size_re = re.search("(\d+)([kKmMgGbB])", log_file)
    size = int(size_re.group(1))
    size_unit = size_re.group(2)
    with open(log_file) as log:
        log_data = log.readlines()
        for line in log_data:
            dict_df.append({
                "test_id": log_file,
                "msec": float(line),
                "size": size,
                "size_unit": size_unit
            })

df = pd.DataFrame(dict_df)
df = df.groupby(by=["test_id", "size", "size_unit"])
mean_df = df.mean().reset_index().rename(columns={"msec": "mean_msec"})
std_df = df.std().reset_index().rename(columns={"msec": "std_msec"})
min_df = df.min().reset_index().rename(columns={"msec": "min_msec"})
max_df = df.max().reset_index().rename(columns={"msec": "max_msec"})
stats = [mean_df, std_df, min_df, max_df]
stats_df = reduce(lambda left,right: pd.merge(left, right, on=None, how="outer"), stats)

print(stats_df)
stats_df.to_csv(os.path.join(log_dir, "stats.csv"))
stats_df.to_json(os.path.join(log_dir, "stats.json"), orient="records", lines=True, indent=2)
