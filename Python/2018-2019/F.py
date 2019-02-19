from functools import partial


class Proxy:
    def __init__(self, obj):
        self.__dict__["obj"] = obj

    def __getattr__(self, atr):
        d = self.obj.__dict__
        for k, v in self.obj.__dict__.items():
            if k.lower() == atr.lower():
                # if callable(v):
                #     return partial(v, self.obj)
                return v

        for c in self.obj.__class__.mro():
            d = c.__dict__
            for k, v in d.items():
                if (k.lower() == atr.lower()):
                    if callable(v):
                        return partial(v, self.obj)
                    return v

        return 42

    def __setattr__(self, atr, value):
        d = self.obj.__dict__
        for k, v in d.items():
            if k.lower() == atr.lower():
                # if (callable(value)):
                #     setattr(self.obj, k, partial(value, self.obj))
                #     return
                setattr(self.obj, k, value)
                return

        for c in self.obj.__class__.mro():
            d = c.__dict__
            for k in d.keys():
                if (k.lower() == atr.lower()):
                    setattr(self.obj, k, value)
                    return

        self.obj.__dict__[atr.lower()] = value
