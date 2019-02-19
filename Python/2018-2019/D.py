class Matrix:
    def __init__(self, size, values=None):
        self.size = size
        if values == None:
            self.a = []
            for y in range(size):
                self.a.append([])
                for x in range(size):
                    self.a[y].append(0)
        else:
            self.a = [list(line) for line in values]


    def __iter__(self):
        currentIndex = 0
        while (currentIndex < self.size ** 2):
            currentIndex += 1
            yield self[(currentIndex-1)//self.size][(currentIndex-1)%self.size]

    def __getitem__(self, index):
        return self.a[index]

    def __add__(self, other):
        new = Matrix(self.size)
        for y in range(self.size):
            for x in range(self.size):
                new[y][x] = self[y][x] + other[y][x]
        return new

    def __mod__(self, const):
        new = Matrix(self.size)
        for y in range(self.size):
            for x in range(self.size):
                new[y][x] = self[y][x] % const
        return new

    def __mul__(self, other):
        new = Matrix(self.size)
        if isinstance(other, int):
            for y in range(self.size):
                for x in range(self.size):
                    new[y][x] = self[y][x] * other
        else:
            for y in range(self.size):
                for x in range(self.size):
                    for z in range(self.size):
                        new[y][x] += (self[y][z] * other[z][x])
        return new

    def __pow__(self, pow):
        new = Matrix(self.size)
        for i in range(self.size):
            new[i][i] = 1
        else:
            for i in range(pow):
                new *= self
        return new

    def __repr__(self):
        out = str(self.size)+"\n"
        for y in range(self.size):
            for x in range(self.size):
                out += str(self.a[y][x]) + " "
            out += "\n"
        return out