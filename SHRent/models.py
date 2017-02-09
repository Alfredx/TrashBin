# -*- coding: utf-8 -*-
# author: ShenChao


class HouseModel(object):
    FLOOR_TYPE_CHOICES = ((0, '低区'),
                          (1, '中区'),
                          (2, '高区'))
    FACE_DIRECTION_CHOICES = ((1, '东'),(2, '南'),(3, '西'),(4, '北'))
    FITMENT_TYPE_CHOICES = ()
    RENT_TYPE_CHOICES = ((0,'整租'),(1,'合租'))
    def __init__(self, *kwargs):
        super(HouseModel, self).__init__()
        self.url = ''
        self.title = ''
        self.price = 0
        self.housing_estate = ''
        self.halls = 0
        self.rooms = 0
        self.area = 0
        self.address = ''
        self.price_per_area = 0
        self.district = ''
        self.block = ''
        self.floor_type = 0
        self.floor = 0
        self.face_direction = 1
        self.nearby_metro_line = 0
        self.nearby_metro_station = ''
        self.distance_to_metro = 0
        self.fitment_type = 0
        self.rent_type = 0
        self.has_own_washroom = False
        self.has_own_balcony = False
        self.is_on_sale = False
        self.update_time = None
        self.bringin_records = []
        self.bringin_7_days = 0
        self.bringin_count = 0
        self.images = []
        self.layout_image = ''


class AgentModel(object):
    def __init__(self):
        self.name = ''



class MetroLineModel(object):
    def __init__(self):
        self.lineno = 0
        self.neighbours = []