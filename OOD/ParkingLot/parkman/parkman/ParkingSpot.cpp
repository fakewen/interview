//
//  ParkingSpot.cpp
//  parkman
//
//  Created by fakewen on 6/22/17.
//  Copyright © 2017 Koshr. All rights reserved.
//

#include "ParkingSpot.hpp"
VehicleSize size;
Vehicle* currentVehicle;
ParkingSpot::ParkingSpot(VehicleSize _size){
    size=_size;
    currentVehicle=NULL;
}
bool ParkingSpot::fit(Vehicle* v){//size是VehicleSize    v.getSize>VehicleSize
    return currentVehicle==NULL && int(v->getSize())<=int(size);
}

void ParkingSpot::park(Vehicle* v){
    //if(fit(v)){
    currentVehicle=v;
    cout<<"[ParkingSpot]Park a "<< ((int(v->getSize())==1)?"Car":"Truck") <<" in Spot"<<endl;
    //}else{
    //  cout<<"unavailable@ Spot"<<endl;
    //}
}
void ParkingSpot::leave(){
    cout<<"[ParkingSpot]Leave a Vehicle from a ["<< ((int(size)==1)?"Compact":"Large")<<"] size spot"<<endl;
    currentVehicle=NULL;
}
Vehicle* ParkingSpot::getVehicle(){
    return currentVehicle;
}

