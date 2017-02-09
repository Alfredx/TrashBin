# -*- coding: utf-8 -*-
# author: ShenChao


import spider

if __name__ == '__main__':
    print('main')
    lianjia = spider.LianjiaSpider()
    lianjia.create_processes(pnum=8)