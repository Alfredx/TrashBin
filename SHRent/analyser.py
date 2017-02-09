# -*- coding: utf-8 -*-
# author: ShenChao


from models import HouseModel, AgentModel, MetroLineModel

class Analyser(object):
    """docstring for Analyser"""
    def __init__(self, houses, agents, metros):
        super(Analyser, self).__init__()
        self.houses = houses
        self.agents = agents
        self.metros = metros

    

