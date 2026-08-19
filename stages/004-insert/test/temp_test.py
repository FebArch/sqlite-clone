import pytest
import subprocess

res = subprocess.Popen(
    ["python"],
    stdin=subprocess.PIPE,
    stdout=subprocess.PIPE,
    text=True
)

output1, _ = res.communicate("print('Hello World')\nprint('Joker is your fav movie')")
print(output1)

# output2, _ = res.communicate("print('Joker is your fav movie')")
# print(output2)