import subprocess

try:
    res = subprocess.run(["python", "temp_test.py"], check=True, timeout=6)
    print(res.returncode)


except FileNotFoundError as err:
    print("File not found\n")

except subprocess.TimeoutExpired as err:
    print("Process does not executed in time")

except subprocess.CalledProcessError as err:
    print("Proccess was not called properly")

