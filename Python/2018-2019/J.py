class Singleton(type):
    _d = {}

    def __call__(cls, *args, **kwargs):
        if cls not in cls._d:
            cls._d[cls] = type.__call__(cls, *args, **kwargs)
        return cls._d[cls]


class Final(type):
    def __prepare__(clsname, bases):
        return {'_isMeta': True}

    def __new__(meta, clsname, bases, dic):
        for a in bases:
            if "_isMeta" in a.__dict__:
                raise TypeError

        ret = type.__new__(meta, clsname, bases, dic)
        return ret
