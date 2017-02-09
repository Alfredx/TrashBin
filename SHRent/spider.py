# -*- coding: utf-8 -*-
# author: ShenChao

from models import HouseModel, AgentModel
from multiprocessing import Process
import os
import re
import requests
import time
import urllib
import urllib2
from selenium import webdriver

DEFAULT_MAX_PAGE = 500


class DataFetcher(object):
    def __init__(self):
        super(DataFetcher, self).__init__()
        cap = webdriver.DesiredCapabilities.PHANTOMJS
        cap["phantomjs.page.settings.resourceTimeout"] = 1000
        cap["phantomjs.page.settings.loadImages"] = False
        #cap["phantomjs.page.settings.localToRemoteUrlAccessEnabled"] = True
        self.driver = webdriver.PhantomJS(desired_capabilities=cap)
    
    def get_house_list(self, page_id):
        # 租房数据不需要设定header各项参数
        url = 'http://sh.lianjia.com/zufang/d%d'
        self.driver.get('%s%d'%(url,page_id))
        lis = self.driver.find_elements_by_css_selector('#house-lst li')
        result = []
        for li in lis:
            href = li.find_element_by_css_selector('a[name="selectDetail"][class="rent"]')
            data = {
                'url': href.get_attribute('href'),
                'metro': 0,
                'station': '',
                'distance': 0,
                'rent_type': u'整租',
                'balcony': False,
                'washroom': False,
                'on_sale': False,
            }
            innerHTML = li.get_attribute('innerHTML').encode('utf-8')
            metro = re.search('距离([0-9]+)号线(.+)站([0-9]+)米', innerHTML)
            if metro:
                data['metro'] = metro.group(1)
                data['station'] = metro.group(2).decode('utf-8')
                data['distance'] = metro.group(3)
            ziru_label = re.search('自如(合租|整租)', innerHTML)
            if ziru_label:
                data['rent_type'] = ziru_label.group(1).decode('utf-8')
            balcony = re.search('独立阳台', innerHTML)
            if balcony:
                data['balcony'] = True
            washroom = re.search('独卫', innerHTML)
            if washroom:
                data['washroom'] = True
            if re.search('http://cdn7.dooioo.com/static/img/animatedec.gif', innerHTML):
                data['on_sale'] = True
            result.append(data)
        return result

    def get_house_data(self, house_data):
        #无需header，同get_house_list
        self.driver.get(house_data['url'])
        
        house = HouseModel()
        # 这里更好的做法是把所有数据的html特征提取出来，写入特定的特征文件，然后依靠该文件读取数据
        # 这样做的好处是当目标html被修改时只更新特征文件就行，而不需要修改代码，有利于热更新
        # 现在为了快速编码所以hardcode了
        house.url = house_data['url']
        house.nearby_metro_line = house_data['metro']
        house.nearby_metro_station = house_data['station']
        house.distance_to_metro = house_data['distance']
        house.rent_type = house_data['rent_type']
        house.has_own_balcony = house_data['balcony']
        house.has_own_washroom = house_data['washroom']
        house.is_on_sale = house_data['on_sale']
        house.title = self.driver.find_element_by_class_name('main').text
        house.price = float(self.driver.find_element_by_class_name('price').text.replace(u'\u5143/\u6708', ''))
        addrs = self.driver.find_elements_by_class_name('addrEllipsis')
        house.housing_estate = addrs[0].get_attribute('title')
        house.address = addrs[1].get_attribute('title')
        td_data = self.driver.find_elements_by_css_selector('td[width="50%"]')
        floor_data = td_data[0].text.split('/')
        house.floor_type = floor_data[0]
        house.floor = int(floor_data[1][:-1])
        house.face_direction = td_data[1].text
        district_data = td_data[2].text.split(' ')
        house.district = district_data[0]
        house.block = district_data[1]
        house.update_time = td_data[3].text
        room_info = self.driver.find_element_by_css_selector('.room .mainInfo').text.split(' ')
        house.rooms = int(room_info[0][:-1])
        house.halls = int(room_info[1][:-1])
        house.area = int(self.driver.find_element_by_css_selector('.area .mainInfo').text[:-1])
        house.price_per_area = house.price/house.area
        house.layout_image = self.driver.find_element_by_id('img_huxing').get_attribute('src')
        images = self.driver.find_elements_by_css_selector('.album-view-wrap img')
        for img in images:
            house.images.append(img.get_attribute('data-large'))
        try:
            house.bringin_7_days = int(self.driver.find_element_by_class_name('count').text)
            house.bringin_count = int(re.search('([0-9]+)',self.driver.find_element_by_class_name('totalCount').text).group(1))
            bringin_list = self.driver.execute_script('return init.kanfangList')
            if bringin_list:
                house.bringin_records = bringin_list
        except Exception as e:
            house.bringin_count = 0
            house.bringin_7_days = 0
            house.bringin_records = []
        return house



    @staticmethod
    def clean_html(html):
        return html.replace('\n', '').replace('\t', '')


class Worker(Process):
    STATE_STOP = 0
    STATE_RUN = 1
    def __init__(self, page, max_page=DEFAULT_MAX_PAGE):
        super(Worker, self).__init__()
        self.page = page
        self.max_page = max_page
        self.state = self.STATE_STOP
        self.fetcher = DataFetcher()

    def stop(self):
        self.state = self.STATE_STOP

    def run(self):
        self.state = self.STATE_RUN
        # print(os.getpid(), self.page, self.max_page)
        while self.state and self.page <= self.max_page:
            break
            house_list = self.fetcher.get_house_list(self.page)
            if house_list == []:
                break
            for house in house_list:
                house_data = self.fetcher.get_house_data(house)
            self.page += 1


class LianjiaSpider(object):
    def __init__(self):
        super(LianjiaSpider, self).__init__()

    def create_processes(self, pnum=4):
        url = 'http://sh.lianjia.com/zufang'
        response = requests.get(url)
        plainHTML = DataFetcher.clean_html(response.content)
        total = int(re.search('<h2>为您找到<span>(?P<total>[0-9]+)</span>套上海在租房源</h2>', plainHTML).group(1))
        print('total houses: %d'%total)
        max_page = (total/20+pnum)/pnum

        fetcher = DataFetcher()
        # print(fetcher.get_house_list(1))
        print(fetcher.get_house_data(fetcher.get_house_list(1)[0]))

        for i in range(pnum):
            worker = Worker(i*max_page, max_page=max_page)
            worker.start()

