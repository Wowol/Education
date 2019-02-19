#!/usr/bin/env python3

import argparse
import logging
import sys

import api
import simulator
import algorithm
import network

net_base = network.Network
nets = [(name, cls) for name, cls in network.__dict__.items() if
        isinstance(cls, type) and
        issubclass(cls, net_base) and
        cls != net_base
        ]

algo_base = api.Algorithm
algos = [(name, cls) for name, cls in algorithm.__dict__.items() if
         isinstance(cls, type) and
         issubclass(cls, algo_base) and
         cls != algo_base
         ]

parser = argparse.ArgumentParser(description='ROUTER Simulator.')
parser.add_argument('-v', '--verbose', action='store_true',
                    default=False, help='show more info')
parser.add_argument('-d', '--debug', action='store_true',
                    default=False, help='show debug info')
parser.add_argument('--ticks', type=int, default=1000, help='simulator ticks')
parser.add_argument('network', type=str, help='network to simulate (' +
                    ','.join([name for name, cls in nets]) + ')')
parser.add_argument('algorithm', type=str, help='algorithm to simulate (' +
                    ','.join([name for name, cls in algos]) + ')')
parser.add_argument('-s', '--silent', action='store_true', default=False, help='print only interesting values')
args = parser.parse_args()

log_level = logging.CRITICAL
if args.verbose:
    log_level = logging.INFO
if args.debug:
    log_level = logging.DEBUG
logging.basicConfig(level=log_level)

net = None
for name, cls in nets:
    if name.lower().startswith(args.network.lower()):
        net = cls
if net is None:
    parser.print_help()
    sys.exit(1)

algo = None
for name, cls in algos:
    if name.lower().startswith(args.algorithm.lower()):
        algo = cls
if algo is None:
    parser.print_help()
    sys.exit(1)

sim = simulator.Simulator()
n = net(sim, algo)
for i in range(args.ticks):
    n.tick(i)

if args.silent:
    print (sim.stats["delivery_rate"], sim.stats["avg_time"])
else:
    print(sim.stats)
