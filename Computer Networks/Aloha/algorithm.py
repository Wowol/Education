# vim:ts=4:sts=4:sw=4:expandtab

import api
import logging
import random
import math


class SimpleAlgorithm(api.Algorithm):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

    def tick(self):
        logging.debug("Algorithm tick : %s" % (repr([
            self.tick_count,
            (self.frame and str(self.frame.id)),
            (self.frame and self.frame.first_tick),
            (self.frame and self.frame.length),
            self.part,
            self.channel.transmit_status,
            self.max_length,
        ]),))
        if self.frame is not None:
            self.transmit()

    def successed(self):
        pass

    def failed(self, *_):
        pass


class AlohaAlgorithm(api.Algorithm):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.sleep = 0
        self.number_of_fails = 0

    def successed(self):
        self.sleep = 0
        self.number_of_fails = 0

    def failed(self, *_):
        self.number_of_fails += 1
        self.sleep = random.randrange(2**self.number_of_fails)*self.max_length

    def tick(self):
        if self.sleep > 0:
            self.sleep -= 1
            return

        if self.frame is not None:
            self.transmit()

class SlottedAlohaAlgorithm(api.Algorithm):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.sleep = 0
        self.number_of_fails = 0

    def successed(self):
        self.sleep = 0
        self.number_of_fails = 0

    def failed(self, *_):
        self.number_of_fails += 1
        self.sleep = random.randrange(2**self.number_of_fails)*self.max_length

    def tick(self):
        if self.sleep > 0:
            self.sleep -= 1
            return

        if self.frame is not None:
            if self.part != 0 or self.tick_count % self.max_length == 0:
                self.transmit()


class CSMAAlgorithm(api.Algorithm):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.sleep = 0
        self.number_of_fails = 0

    def successed(self):
        self.number_of_fails = 0
        self.sleep = 0
    
    def failed(self, tick):
        self.number_of_fails += 1
        self.sleep = random.randrange(2**self.number_of_fails)*self.max_length

        #alignment to frame
        self.sleep += (self.max_length - (self.sleep + tick) % self.max_length) % self.max_length

    def tick(self):
        if self.sleep > 0:
            self.sleep -= 1
            return
        
        if self.frame is not None:
            if self.part == 0 and self.channel.carrier_sense:
                return
            self.transmit()