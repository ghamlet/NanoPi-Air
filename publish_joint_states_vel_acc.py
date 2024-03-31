#!/usr/bin/env python

import math

fromEncToRadFor1066428 = 4096/(2*math.pi)
fromRncToRadFor12 = (1024*180)/(300*math.pi)
minEncPoseForGripper = 390
fromEncToLinGripper = 7.75
zeroPose = [2048, 2048, 2048, 2048, 512, 680]

currentState = {
        'name': [],
        'position':[]
    }
currentState['position'] = [0,0,0,0,0,0]
maxVelocity = 1
kVelRadSToMotorVel = 0.11/30*math.pi
kAccRadToMotorAcc = 8.58/180*math.pi
kAcc = 0.6
countOfJoint = 6
stop_move = False


def parse_msg(msg):
    jointState = {
        "name": [],
        "position":[]
    }

    msgList = msg.split()
    jointState['name'] = msgList[0:countOfJoint]
    jointState['position'] = msgList[countOfJoint:]
    jointState['position'] = [float(el) for el in jointState['position']] 
    print(jointState)
    return jointState


def convert_pose_vel_acc(name,poseList):
    jointcmd = {
        'position': []
    }

    jointcmd['name'] = name
    poseListPub = []
   

    for i in range(len(name)):
        if(name[i] == 'ang_joint_5'): 
            poseListPub.append(round((poseList[i]*fromRncToRadFor12)+zeroPose[i]))

        elif(name[i] == 'gripper'):
            poseListPub.append(round(poseList[i]*fromEncToLinGripper + minEncPoseForGripper))
            
        else:
            poseListPub.append(round((poseList[i]*fromEncToRadFor1066428)+zeroPose[i]))
           

    jointcmd['position'] = poseListPub
    return jointcmd    


def move_of_trapeze_principle(msg):
    msg = parse_msg(msg)
   
    jointCmd = convert_pose_vel_acc(msg['name'], msg['position'])
    print(jointCmd)
    return jointCmd
   

# move_of_trapeze_principle("ang_joint_1 ang_joint_2 ang_joint_3 ang_joint_4 ang_joint_5 gripper 0.56 0.19 -0.92 0.73 0.0 0")