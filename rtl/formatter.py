import sys

with open(sys.argv[1], "r") as file_in:
    with open(f"{sys.argv[1]}t", "w") as file_out:
        line = file_in.readline()
        while len(line) > 0:
            file_out.write(f'"{line.rstrip().replace('"', '\\"')}\\n"\n')
            line = file_in.readline()
