___used___ = []
___depth___ = 0

def monit(level):
    def decorator(function):
        def wrapper(*args):
            global ___used___, ___depth___
            t = (level, ___depth___, wrapper, function.__name__)
            ___used___.append((t, (0, args)))
            ___depth___ += 1
            value = function(*args)
            ___depth___ -= 1
            ___used___.append((t, (1, value)))
            return value
        return wrapper
    return decorator

def ___print___(depth, isReturn, indent, add, name):
    for i in range(depth):
        print(indent, end='')
    if isReturn:
        print('return', add)
    else:                        
        argsStr = ','.join(map(str, add))
        print(f"{name}({argsStr})")

def report(level, indent= "->", limits=None):
    good = []
    for k in ___used___:
        (lev, d, wr, name) = k[0]
        isReturn = k[1][0]
        add = k[1][1]
        if lev <= level:
            if limits != None and wr in limits:
                first, second = limits[wr]
                if d+1 >= first and second >= d+1: 
                    ___print___(d, isReturn, indent, add, name)
            else:
                ___print___(d, isReturn, indent, add, name)
                        

def clear():
    global ___used___
    ___used___ = []



# @monit(1)
# def fib(a):
# 	if a == 0: return 1
# 	if a == 1: return 1
# 	return fib(a-1) + fib(a-2)

# fib(6)
# report(1, limits = {fib:(1,2)})
# report(1,limits = {fib:(6,6)})
# clear()


# @monit(2)
# def f(a):
# 	if a == 0:
# 		return 1
# 	return f(a-1)*a

# #f = monit(2)(f) -- monit(2) = convert, wiec monit(2)(f) = convert(f)

# @monit(1)
# def g(a, b):
# 	if b == 0:
# 		return 1
# 	return g(a, b-1) * f(a)

# g(2, 2)

# report(2)
# report(1)
# report(2, limits = {f:(1,2), g:(1,2)})
# clear()