#!/usr/bin/env python
 
import math
from RoboticArmClass import RoboticArm
import publish_joint_states_vel_acc as convert_tool

nameList = ['ang_joint_1','ang_joint_2','ang_joint_3','ang_joint_4','ang_joint_5','gripper']
gripperPose = '0'
curJointState = [0,0,0,0,0]



def ParseMsg(msg):
    try:
        coord_list = msg.split()
        print(coord_list)
        x = float(coord_list[0])
        y = float(coord_list[1])
        z = float(coord_list[2])
        pith = float(coord_list[3])
        roll = float(coord_list[4])
        return x,y,z,pith,roll
    except ValueError:
        pass


def MoveToPointCallback(msg):
    x,y,z,pitch,roll = ParseMsg(msg)
    roboticArm = RoboticArm()
    availJointState,goalJointState = roboticArm.InversProblem(x,y,z,pitch,roll)

    if (not availJointState):
        print('Point cannot be reached')
    else:
        goalJointState = [str(el) for el in goalJointState]
        strName = ' '.join(nameList)
        strJS = ' '.join(goalJointState) + ' ' + gripperPose
        strCmd = strName + ' ' + strJS

        print(strCmd)
        print('Well Done!!!')
        convert_tool.move_of_trapeze_principle(strCmd)
        



if __name__=='__main__':
    MoveToPointCallback("240 350 280 0 2")

