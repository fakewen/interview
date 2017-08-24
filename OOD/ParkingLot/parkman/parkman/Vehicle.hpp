//
//  Vehicle.hpp
//  parkman
//
//  Created by fakewen on 6/22/17.
//  Copyright © 2017 Koshr. All rights reserved.
//

#ifndef Vehicle_hpp
#define Vehicle_hpp
#include "VehicleSize.hpp"
#include <stdio.h>
#include <iostream>
using namespace std;

class Vehicle{
    
public:
    
    virtual VehicleSize getSize()=0;
    //Vehicle(){}

};

#endif /* Vehicle_hpp */
