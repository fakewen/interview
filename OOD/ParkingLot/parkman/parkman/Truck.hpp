//
//  Truck.hpp
//  parkman
//
//  Created by fakewen on 6/22/17.
//  Copyright © 2017 Koshr. All rights reserved.
//

#ifndef Truck_hpp
#define Truck_hpp
#include "Vehicle.hpp"
#include <stdio.h>

class Truck:public Vehicle{
public:
    Truck();
    VehicleSize getSize() override;
    
};


#endif /* Truck_hpp */
