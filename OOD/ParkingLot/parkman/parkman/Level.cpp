//
//  Level.cpp
//  parkman
//
//  Created by fakewen on 6/22/17.
//  Copyright © 2017 Koshr. All rights reserved.
//

#include "Level.hpp"

vector<ParkingSpot*> spots;

Level::Level(int numOfSpots){
    vector< ParkingSpot*> spotsTmp;//CONST??!!
    int i=0;
    for(;i<numOfSpots/2;i++){
        //cout<<"[Level]new a Car"<<endl;
        spots.push_back(new ParkingSpot(VehicleSize::Compact));
    }
    for(;i<numOfSpots;i++){
        //cout<<"[Level]new a Truck"<<endl;
        spots.push_back(new ParkingSpot(VehicleSize::Large));
    }
    //spots=spotsTmp;
    cout<<"[Level]THis LVL has"<<spots.size()<<endl;
}
bool Level::hasSpot(Vehicle* v){
    for(auto it:spots){
        if(it->fit(v)){
            return true;
        }
    }
    return false;
}
bool Level::park(Vehicle* v){
    for(auto it:spots){
        if(it->fit(v)){
            cout<<"[Level]a "<< ((int(v->getSize())==1)?"Car":"Truck") <<" parked"<<endl;
            it->park(v);
            return true;
        }
    }
    return false;
}
bool Level::leave(Vehicle* v){
    for(auto it:spots){
        if(it->getVehicle()==v){
            cout<<"[Level]a "<< ((int(v->getSize())==1)?"Car":"Truck") <<" leave"<<endl;
            it->leave();
            return true;
        }
    }
    return false;
}
