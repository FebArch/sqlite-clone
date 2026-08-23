import pytest
import subprocess

queries = [
    "INSERT INTO users VALUES 1 shufaan shufaan@gmail.com\n",
    "SELECT\n",
    ".exit\n"
]

expected_output = [
    "~ ./db\ndb > Executed \ndb > Error reading input\n",
    "(1, shufaan, shufaan@gmail.com)\nExecuted \ndb >",
    ""
]

output = []

res = subprocess.Popen(
    [".\\repl_v0.exe"],
    shell=True,
    # stages\004-insert\src\repl_v0.exe
    # ["python", "--version"],
    stdin= subprocess.PIPE,
    stdout= subprocess.PIPE,
    text = True,
    cwd="../src/"
)

# for query in queries:
    # o, _ = res.communicate(queries[0])
    # output.append(o)    
o, _ = res.communicate(queries[0])
output.append(o)

print(o)
# print(output)

def test_queries():
    # for i in range(len(expected_output)):
    assert output[0] == expected_output[0]
