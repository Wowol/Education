from collections import deque
from functools import partial

class MRO:
    def __init__(self, obj):
        self.obj = obj
    def __getattr__(self, atr):

        if (atr in self.obj.__dict__):
            return self.obj.__dict__[atr]

        q = deque()
        q.append(self.obj.__class__)
        while (len(q)>0):
            current = q.popleft()
            if atr in current.__dict__:
                if (callable(current.__dict__[atr])):
                    return partial(current.__dict__[atr], self.obj)
                return current.__dict__[atr]
            else:
                for parent in reversed(current.__bases__):
                    q.append(parent)
        return self.obj.__getattr__(atr)
        
