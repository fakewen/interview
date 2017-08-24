//
//  ParkingLot.cpp
//  parkman
//
//  Created by fakewen on 6/22/17.
//  Copyright © 2017 Koshr. All rights reserved.
//
//https://stackoverflow.com/questions/19657728/create-a-vector-of-instances-of-a-class-in-c
#include "ParkingLot.hpp"


ParkingLot::ParkingLot(int numsLevels, int numSpotsPerLevel){
    vector<Level*> tmp[numsLevels];
    cout<<"[ParkingLot, init end]"<<endl;
    for(int i=0;i<numsLevels;i++){
        tmp->push_back(new Level(numSpotsPerLevel));
    }
    levels=*tmp;
    //levels=vector<Level*>(numsLevels,new Level(numSpotsPerLevel));
    cout<<"[ParkingLot, init end]  "<<levels.size()<<"X"<<levels[0]->spots.size()<<endl<<"************"<<endl<<endl<<endl;
}
bool ParkingLot::hasSpot(Vehicle* v){
    for(auto lv:levels){//levels 10*10
        if(lv->hasSpot(v)){
            return true;
        }
    }
    return false;
}
bool ParkingLot::park(Vehicle* v){
    int ltmp=0;
    for(auto lv:levels){
        ltmp++;
        if(lv->park(v)){
            cout<<"[ParkingLot] Park a "<<((int(v->getSize())==1)?"Car":"Truck")<<" @ "<<ltmp<<"LVL"<<endl;
            return true;
        }
    }
    cout<<"[ParkingLot]Lot cann't Park!!!"<<endl;
    return false;
}
bool ParkingLot::leave(Vehicle* v){
    int ltmp=0;
    for(auto lv:levels){
        ltmp++;
        if(lv->leave(v)){
            string carStr="?";
            switch (v->getSize()) {
                case VehicleSize::Compact:
                    carStr="Car";
                    break;
                case VehicleSize::Large:
                    carStr="Truck";
                    break;
                default:
                    break;
            }
            cout<<"[ParkingLot]leave A "<<carStr<<" @ "<<ltmp<<"LVL"<<endl;
            return true;
        }
    }
    cout<<"[ParkingLot] can't leave"<<endl;
    return false;
}
