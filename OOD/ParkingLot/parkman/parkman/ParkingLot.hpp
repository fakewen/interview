//
//  ParkingLot.hpp
//  parkman
//
//  Created by fakewen on 6/22/17.
//  Copyright © 2017 Koshr. All rights reserved.
//

#ifndef ParkingLot_hpp
#define ParkingLot_hpp
#include "Level.hpp"
#include <stdio.h>

class ParkingLot{
private:
public:
    vector<Level*> levels;

    ParkingLot(int numsLevels, int numSpotsPerLevel);
    bool hasSpot(Vehicle* v);
    bool park(Vehicle* v);
    bool leave(Vehicle* v);
};


#endif /* ParkingLot_hpp */
