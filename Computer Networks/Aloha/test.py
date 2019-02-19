from subprocess import call, PIPE, Popen
import sys


clients = [5, 10, 15, 20]
length = [1, 2, 5]
frames = [0.1]


algorithm = ["Aloha", "SlottedAloha", "CSMA"]


output_file = open("test_result", "w")
for c in clients:
    for l in length:
        for f in frames:
            print("\\begin{center}")
            print(f'Clients = {c}, Length = {l}, Frames = {f} \\\\')
            print('\\begin{tabular}{l*{6}{c}r}')
            print('Algorithm & total & success & effectivness \\\\')
            print('\\hline')
            for a in algorithm:
                total = 0
                success = 0
                for n_tests in range(0, 10):
                    p = Popen(f'python simulate.py {a} --clients {c} --length {l} --frames {f} -s', stdout=PIPE)
                    output, err = p.communicate()
                    splitted = output.split()
                    current_total = int(splitted[0])
                    current_success = int(splitted[1])
                    total += current_total
                    success += current_success
                print(f'{a} & {total} & {success} & {"%.2f"%(success / total * 100)}\\% \\\\')
                # print(c, l, f, a, total, success, "%.2f"%(success / total * 100))
            print('\\end{tabular} \\\\ \n')
            print("\\end{center}")


