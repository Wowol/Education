class inst:
    def __init__(self, cls):
        self.cls = cls
        self.__num_of_inst__ = 0

    def __call__(self, *args, **kwargs):
        self.__num_of_inst__ += 1
        return self.cls(*args, **kwargs)

    def __getattr__(self, att):
        return getattr(self.cls, att)

    def num_of_inst(self):
        print(f"Liczba instancji klasy {self.cls.__name__}: {self.__num_of_inst__}")
