import subprocess
SIZES = [10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000, 20000, 50000, 100000]

output_file = open("timings.csv", "w")
output_file.write("n, Avg, error\n")

for size in SIZES:
    args = ("build/zotti_asd_project_timings", str(size))
    popen = subprocess.Popen(args, stdout=subprocess.PIPE)
    popen.wait()
    output = popen.stdout.read()
    output_file.write(output)

output_file.close()