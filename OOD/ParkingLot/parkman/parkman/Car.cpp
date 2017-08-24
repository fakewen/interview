//
//  Car.cpp
//  parkman
//
//  Created by fakewen on 6/22/17.
//  Copyright © 2017 Koshr. All rights reserved.
//

#include "Car.hpp"
Car::Car(){
    //cout<<"Car @ .h"<<endl;
}
VehicleSize Car::getSize(){
    //cout<<"[C]"<<endl;
    return VehicleSize::Compact;
}
