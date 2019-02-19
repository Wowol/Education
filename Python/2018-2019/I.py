def private(*private_names):
    def class_rebuilder(cls):
        class NewClass:
            def __init__(self, *args):
                self.__dict__["wrapped"] = cls(*args)

            def __getattr__(self, attr_name):
                if attr_name not in private_names:
                    return getattr(self.wrapped, attr_name)
                else:
                    raise TypeError(f"Pobranie atrybutu prywatnego: {attr_name}")

            def __setattr__(self, attr_name, value):
                if attr_name not in private_names:
                    setattr(self.wrapped, attr_name, value)
                else:
                    raise TypeError(f"Modyfikacja atrybutu prywatnego: {attr_name}")
        return NewClass
    return class_rebuilder