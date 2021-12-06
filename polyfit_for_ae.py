#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Jun  4 09:22:43 2021

@author: geoff
"""

import numpy as np
import matplotlib.pyplot as plt
import os
file_dir = "C:/Users/zngweixy/Desktop/AE/code/csv_seeker07b"

def polyfit_exp(file_path):
    with open(file_path, "r") as f:
        lines = f.readlines()

    xx = []
    yy = []    
    for i, line in enumerate(lines):
        vec = line.strip().split(",")
        if(int(vec[1])==0):
            continue;
        xx.append(int(vec[0]))         
        yy.append(int(vec[1])) 

    x = np.array(yy)
    y = np.array(xx) 

    z = np.polyfit(x,y,2) 
    p = np.poly1d(z)
    # print("{:.0f},{:.0f},{:.0f},{:.0f}".format(p(400), p(500), p(1000), p(1500)))
    # print("{:.0f}".format(p(400)))
    print(p)
    


    yvals = p(x)
    plt.plot(x,y,'*',)
    plt.plot(x,yvals,'r')
    plt.xlabel('gray')
    plt.ylabel('exp')
    plt.legend(loc=4) 
    plt.title(' ')

if __name__ == "__main__":
    scene=['室内工位','窗边顺光','室外阴影','室外顺光','室外逆光','室外侧光']
    dist=[40,60,80,100]
    for j, s in enumerate(scene):
        print(s)
        for i, d in enumerate(dist):
            file_path = os.path.join(file_dir, s, "exp_gray_"+str(d)+".csv")
            polyfit_exp(file_path)
    


