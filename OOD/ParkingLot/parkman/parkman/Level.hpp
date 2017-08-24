//
//  Level.hpp
//  parkman
//
//  Created by fakewen on 6/22/17.
//  Copyright © 2017 Koshr. All rights reserved.
//

#ifndef Level_hpp
#define Level_hpp
#include "ParkingSpot.hpp"
#include <stdio.h>
#include "Car.hpp"
#include "Truck.hpp"
#include <iostream>
#include <vector>
using namespace std;
class Level{
private:
public:
    vector<ParkingSpot*> spots;

    Level(int numOfSpots);
    bool hasSpot(Vehicle* v);
    bool park(Vehicle* v);
    bool leave(Vehicle* v);
};

#endif /* Level_hpp */
