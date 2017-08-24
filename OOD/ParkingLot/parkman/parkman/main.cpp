//
//  main.cpp
//  parkman
//
//  Created by fakewen on 6/22/17.
//  Copyright © 2017 Koshr. All rights reserved.
//

/*
#include "Truck.hpp"
#include "Vehicle.hpp"*/
#include "ParkingLot.hpp"
#include "Level.hpp"
#include "ParkingSpot.hpp"
#include "Truck.hpp"
#include "Car.hpp"
#include "Vehicle.hpp"
#include "VehicleSize.hpp"
#include <vector>
#include <iostream>
#include <assert.h>
using namespace std;

int main(int argc, const char * argv[]) {
    
    ParkingLot* lot = new ParkingLot(10,10);
    cout<<"========"<<endl;
    for(int i=0;i<10;i++){
        
        for(int j=0;j<10;j++){
            auto it=lot->levels[i]->spots[j];
            cout<<"&"<<((int(it->size)==1)?"Car":"Truck")<<","<<((it->currentVehicle==NULL)?"y":"n");
            if((it->currentVehicle!=NULL))return -1;
        }
        cout<<endl;
    }
    cout<<"====Checked! All init spot is available for park===="<<endl;
    vector<Vehicle*> vv;
    cout<<endl<<"***********"<<"[Main] new&Park Start"<<endl;
    for(int i =0;i<50;i++){
        //Vehicle* v=(i%2==0)?new Car():new Truck();
        Vehicle* v;
        if(i%2==0)v=new Car();
        else{v= new Truck();}
        
        vv.push_back(v);
        bool hasSpot=lot->hasSpot(v);
        cout<<i<<"[hasSpot]++"<<(hasSpot?"has":"has not!")<<"[V's style]"<<((int(v->getSize())==1)?"Car":"Truck")<<endl;
        lot->park(v);
        cout<<i<<"[hasSpot]--"<<hasSpot<<endl;
        //if(hasSpot==false)cout<<"?????"<<endl<<endl<<endl;
        /*
        if(i<40){
            assert(hasSpot);
            assert(lot->park(v));
        }else{
            assert(!hasSpot);
            assert(!lot->park(v));
        }*/
    }
    cout<<endl<<"***********"<<"[Main] new&Park End"<<endl;
    
    cout<<endl<<"***********"<<"[Main] Leave Start"<<endl;
    for(Vehicle* v:vv){
        lot->leave(v);
    }
    cout<<"***********"<<"[Main] Leave End"<<endl;
}
