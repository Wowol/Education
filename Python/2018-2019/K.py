class CallCounter(type):
    counter_array = []
    def __init__(*args, **kwargs):
        type.__init__(*args, **kwargs)
        cls = args[0]

        class Inside:
            def __init__(self, f):
                self.f = f
                self.cls = cls

                def captured_function(*args, **kwargs):
                    captured_function.calls += 1
                    return f(*args, **kwargs)

                self.captured_function = captured_function
                self.captured_function.calls = 0

        for k, v in cls.__dict__.items():
            if callable(v):
                w = Inside(v)
                setattr(cls, k, w.captured_function)
                CallCounter.counter_array.append(w)

    def ranking(n):
        if n > 0:
            e = []
            for c in CallCounter.counter_array:
                if c.captured_function.calls > 0:
                    e.append((c.cls.__name__, c.f.__name__, c.captured_function.calls))
            
            e.sort(key = lambda qq: (-qq[2], qq[0], qq[1]))
            if (len(e) < n):
                raise Exception("Too few methods have been called!")

            for x in e:
                print(f"{x[0]}.{x[1]}() --> {x[2]}")

    def clear(c):
        for x in CallCounter.counter_array:
            if x.cls == c:
                x.captured_function.calls = 0

    def ideal():
        e = []
        for w in CallCounter.counter_array:
            e.append((w, w.captured_function.calls))
        e.sort(key = lambda qq: (-qq[1], qq[0]))
        if (len(e) >= 4 and len(entries) >= 4) or len(e) < 3: 
            raise Exception ('Too few methods have been called!')

        class IdealClass:
            pass

        setattr(IdealClass, f"{e[0][0].cls.__name__}_{e[0][0].f.__name__}", e[0][0].captured_function)
        setattr(IdealClass, f"{e[1][0].cls.__name__}_{e[1][0].f.__name__}", e[1][0].captured_function)
        setattr(IdealClass, f"{e[2][0].cls.__name__}_{e[2][0].f.__name__}", e[2][0].captured_function)

        return IdealClass