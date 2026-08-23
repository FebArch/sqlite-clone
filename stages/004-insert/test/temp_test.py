# import pytest
# import subprocess

# res = subprocess.Popen(
#     ["python"],
#     stdin=subprocess.PIPE,
#     stdout=subprocess.PIPE,
#     text=True
# )

# output1, _ = res.communicate("print('Hello World')\nprint('Joker is your fav movie')")
# print(output1)

# output2, _ = res.communicate("print('Joker is your fav movie')")
# print(output2)

# import subprocess

# result = subprocess.run(
#     ["git", "log", "--oneline", "-5"],
#     capture_output=True,
#     text=True
# )

# print(result.stdout)       # stdout string
# print(result.returncode)

'''
import subprocess

cmd = ["printf", "line1\nline2\nline3\n"]

# Default: output is returned as bytes
result_bytes = subprocess.run(cmd, capture_output=True)
print("Bytes mode:")
print(" type:", type(result_bytes.stdout))
print(" value:", result_bytes.stdout)

# Text mode: output is decoded into a Python string
result_text = subprocess.run(cmd, capture_output=True, text=True)
print("\nText mode:")
print(" type:", type(result_text.stdout))
print(" value:", result_text.stdout)



db > Executed
db > Unrecognized keyword at start of
db > (1, shufaan, shufaan@gmail.com)
Executed
db >


~ ./db
db > Executed
db > Unrecognized keyword at start of
db > (1, shufaan, shufaan@gmail.com)
Executed
db >
'''

from argparse import ArgumentParser
from time import sleep

parser = ArgumentParser()
parser.add_argument("time", type=int)

args = parser.parse_args()

print(f"Start timer of {args.time} seconds")

for _ in range(args.time):
    print(".", end="", flush=True)
    sleep(1)

print("Done")
