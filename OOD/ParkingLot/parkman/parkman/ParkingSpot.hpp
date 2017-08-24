//
//  ParkingSpot.hpp
//  parkman
//
//  Created by fakewen on 6/22/17.
//  Copyright © 2017 Koshr. All rights reserved.
//

#ifndef ParkingSpot_hpp
#define ParkingSpot_hpp

#include <stdio.h>
#include "Car.hpp"
#include "Truck.hpp"
#include <iostream>
using namespace std;

class ParkingSpot{
private:
public:
    VehicleSize size;
    Vehicle* currentVehicle;

    ParkingSpot(VehicleSize _size);
    bool fit(Vehicle* v);
    
    void park(Vehicle* v);
    void leave();
    Vehicle* getVehicle();
};


#endif /* ParkingSpot_hpp */
