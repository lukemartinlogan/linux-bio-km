
import sys, os
import re
import json

def get_all_json(dir):
    paths = []
    all_fns = os.listdir(dir)
    for fn in all_fns:
        path = os.path.join(dir, fn)
        if os.path.isdir(path):
            paths += get_all_json(path)
        if re.search("\.json", path):
            paths.append(path)
    return paths

if len(sys.argv) < 2:
    print("USAGE: python3 pretty-format-json.py [/path/to/json/root/dir]")
    sys.exit(1)
root_dir = sys.argv[1]

corpus = get_all_json(root_dir)
for path in corpus:
    with open(path, "r+") as fp:
        print(path)
        data = json.load(fp)
        fp.seek(0)
        fp.truncate()
        json.dump(data, fp, indent=3)
