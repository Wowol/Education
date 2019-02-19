# vim:ts=4:sts=4:sw=4:expandtab

import api
import random
import math


class Network:
    def __init__(self, simulator, algorithm):
        self.simulator = simulator

    def tick(self, tick_count):
        self.simulator.tick()


class SimpleNetwork(Network):
    def __init__(self, simulator, algorithm):
        super().__init__(simulator, algorithm)

        self.r1 = self.simulator.add_router(algorithm, 'a')
        self.r2 = self.simulator.add_router(algorithm, 'b')
        self.r3 = self.simulator.add_router(algorithm, 'c')
        self.r4 = self.simulator.add_router(algorithm, 'd')
        self.simulator.add_link(self.r1, self.r2)
        self.simulator.add_link(self.r2, self.r3)
        self.simulator.add_link(self.r3, self.r4)

    def tick(self, tick_count):
        if tick_count % 2 == 0:
            self.simulator.add_packet(self.r1, self.r4)
        super().tick(tick_count)


class HyperCube(Network):
    def change_bit(self, n, p):
        bit = 1 - ((n >> p) & 1)
        mask = 1 << p
        return (n & ~mask) | ((bit << p) & mask)

    def __init__(self, simulator, algorithm):
        super().__init__(simulator, algorithm)

        self.dimension = 4
        self.routers = []
        for x in range(2**self.dimension):
            self.routers.append(self.simulator.add_router(algorithm, str(x)))

        for x in range(2**self.dimension):
            for b in range(self.dimension):
                self.simulator.add_link(
                    self.routers[x], self.routers[self.change_bit(x, b)])

    def tick(self, tick_count):
        if random.random() < 0.05:
            first = random.randrange(2**self.dimension)
            second = random.randrange(2**self.dimension)
            while first == second:
                second = random.randrange(2**self.dimension)
            self.simulator.add_packet(
                self.routers[first], self.routers[second])
        super().tick(tick_count)


class BrokenEdge(Network):
    def __init__(self, simulator, algorithm):
        super().__init__(simulator, algorithm)

        self.number = 100
        self.routers = []

        for x in range(self.number):
            self.routers.append(self.simulator.add_router(algorithm, str(x)))

        for x in range(self.number):
            self.simulator.add_link(
                self.routers[x], self.routers[(x+1) % self.number])

    def tick(self, tick_count):
        if tick_count % 5 == 0:
            self.simulator.del_line(
                self.routers[0], self.routers[self.number - 1])

        if tick_count % 10 == 0:
            self.simulator.add_link(
                self.routers[0], self.routers[self.number - 1])

        if random.random() < 0.05:
            self.simulator.add_packet(self.routers[90], self.routers[10])

        super().tick(tick_count)


class Geographic(Network):
    def __init__(self, simulator, algorithm):
        super().__init__(simulator, algorithm)

        self.size = 100

        self.vec = 5
        self.number = 10

        self.routers = []
        self.vectors = []
        self.positions = []

        for x in range(self.number):
            self.routers.append(self.simulator.add_router(algorithm, str(x)))
            self.vectors.append(
                (random.randrange(-self.vec, self.vec), random.randrange(-self.vec, self.vec)))
            self.positions.append(
                (random.randrange(self.size), random.randrange(self.size)))

    def tick(self, tick_count):
        if tick_count % 20 == 0:
            for x in range(self.number):
                self.positions[x] = (
                    self.positions[x][0] + self.vectors[x][0], self.positions[x][1] + self.vectors[x][1])

            max_dist = 0
            number = 0
            for x in range(self.number):
                for y in range(x+1, self.number):
                    max_dist = max(max_dist, (self.positions[x][0] - self.positions[y][0])**2 + (
                        self.positions[x][1]-self.positions[y][1])**2)

            for x in range(self.number):
                for y in range(x+1, self.number):
                    self.simulator.del_line(self.routers[x], self.routers[y])
                    squared_dist = (self.positions[x][0] - self.positions[y][0])**2 + (
                        self.positions[x][1]-self.positions[y][1])**2
                    if squared_dist < max_dist/8:
                        number += 1
                        self.simulator.add_link(
                            self.routers[x], self.routers[y])

    #    if tick_count % 100 == 0:
        if random.random() < 0.5:
            first = random.randrange(self.number)
            second = random.randrange(self.number)
            while first == second:
                second = random.randrange(self.number)

            self.simulator.add_packet(
                self.routers[first], self.routers[second])

        super().tick(tick_count)
