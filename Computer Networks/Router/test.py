from subprocess import call, PIPE, Popen
import sys


networks =  ["HyperCube", "Geographic"]

n_tests = 50


for net in networks:
    sum_rate = 0
    sum_time = 0
    for current_test in range(n_tests):
        p = Popen(f'python simulate.py {net} Link -s', stdout=PIPE)
        output, err = p.communicate()
        splitted = output.split()
        rate = float(splitted[0])
        time = float(splitted[1])
        sum_rate += rate
        sum_time += time
    avg_rate = sum_rate / n_tests
    avg_time = sum_time / n_tests
    print(net, avg_rate, avg_time)

