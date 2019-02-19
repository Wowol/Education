# vim:ts=4:sts=4:sw=4:expandtab

import logging
import random
import queue

import api


class RandomRouter(api.Algorithm):
    """Routing algorithm that forwards packets in random directions"""

    def tick(self, packets):
        for src, packet in packets:
            self.router.store_packet(packet)
        packets = self.router.stored_packets
        random.shuffle(packets)
        links = self.router.links
        random.shuffle(links)
        for link in links:
            if len(packets) > 0:
                self.router.forward_packet(link, packets[-1])
                packets = packets[0:-1]


class DistanceVectorRouter(api.Algorithm):
    """Distance vector type routing algorithm"""

    def __init__(self, router):
        super().__init__(router)
        self.tick_count = 0
        self.distance = dict()

    @property
    def distance_vector(self):
        return [(dst, hops) for (dst, (hops, _)) in self.distance.items()]

    def tick(self, packets):
        self.distance[self.router.id] = (0, None)
        link_map = dict()
        for link in self.router.links:
            link_map[link.dst] = link
        for src, packet in packets:
            if isinstance(packet, api.MetaPacket):
                for dst in [dst for (dst, (hops, lnk)) in self.distance.items() if lnk is not None and lnk == packet.src]:
                    del self.distance[dst]
                for dst, hops in packet.payload:
                    if dst not in self.distance or hops+1 < self.distance[dst][0]:
                        self.distance[dst] = (hops+1, packet.src)
            else:
                self.router.store_packet(packet)
        if self.tick_count % 10 == 0:
            for link in self.router.links:
                self.router.forward_packet(link, api.MetaPacket(
                    self.router.id, link.dst, self.distance_vector))
        else:
            link_pkt = dict()
            for packet in self.router.stored_packets:
                dst = self.distance.get(packet.dst, (None, None))[1]
                if dst is None:
                    continue
                try:
                    lnk = link_map[dst]
                    if lnk is not None:
                        if lnk.dst not in link_pkt:
                            self.router.forward_packet(lnk, packet)
                            link_pkt[lnk.dst] = 1
                except:
                    pass
        self.tick_count += 1


class LinkStateRouter(api.Algorithm):

    def __init__(self, router):
        super().__init__(router)
        self.tick_count = 0
        self.last_info_from_router = {}
        self.graph = {}
        self.which_link = {}  # router -> link

    @property
    def link_state(self):
        p = []
        for i in self.router.links:
            p.append(i.dst)
        return (self.tick_count, p)

    def bfs(self):
        q = queue.Queue()
        visited = set()

        visited.add(self.router.id)
        for link in self.router.links:
            q.put(link.dst)
            self.which_link[link.dst] = link
            visited.add(link.dst)
            if link.dst not in self.graph:
                self.graph[link.dst] = []

        while not q.empty():
            t = q.get()
            for neighbour in self.graph[t]:
                if neighbour not in visited:
                    self.which_link[neighbour] = self.which_link[t]
                    visited.add(neighbour)
                    q.put(neighbour)

    # Return True if info is newer
    def got_meta_packet(self, packet):
        tick = packet.payload[0]
        neighbours = packet.payload[1]
        if packet.src != self.router.id and (packet.src not in self.last_info_from_router or self.last_info_from_router[packet.src] < tick):
            self.last_info_from_router[packet.src] = packet.payload[0]

            if packet.src not in self.graph:
                self.graph[packet.src] = []

            to_delete = []
            for old_neighbour in self.graph[packet.src]:
                if old_neighbour not in neighbours:
                    to_delete.append(old_neighbour)

            self.graph[packet.src] = neighbours

            for router in to_delete:
                self.graph[router].remove(packet.src)

            for n in neighbours:
                if n not in self.graph:
                    self.graph[n] = []
                if packet.src not in self.graph[n]:
                    self.graph[n].append(packet.src)

            self.bfs()
            return True
        return False

    def del_link(self, link):
        self.which_link = {key: val for key,
                           val in self.which_link.items() if val != link}

    def tick(self, packets):
        for src, packet in packets:
            if isinstance(packet, api.MetaPacket):
                if self.got_meta_packet(packet):
                    for link in self.router.links:
                        self.router.store_packet(api.MetaPacket(
                            packet.src, link.dst, packet.payload))
            else:
                self.router.store_packet(packet)

        if self.tick_count % 50 == 0:
            for link in self.router.links:
                self.router.forward_packet(link, api.MetaPacket(
                    self.router.id, link.dst, self.link_state))
        else:
            used_links = set()
            for packet in self.router.stored_packets:
                if packet.dst in self.which_link:
                    good_link = self.which_link[packet.dst]
                    if good_link not in used_links:
                        self.router.forward_packet(good_link, packet)
                        used_links.add(good_link)
                    else:
                        self.router.store_packet(packet)
        self.tick_count += 1
