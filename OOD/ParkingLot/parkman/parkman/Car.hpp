//
//  Car.hpp
//  parkman
//
//  Created by fakewen on 6/22/17.
//  Copyright © 2017 Koshr. All rights reserved.
//

#ifndef Car_hpp
#define Car_hpp
#include "Vehicle.hpp"
#include <stdio.h>


class Car :public Vehicle{//public inhibit!!!!!
public:
    Car();
    VehicleSize getSize() override;   
};

#endif /* Car_hpp */
