//
//  Truck.cpp
//  parkman
//
//  Created by fakewen on 6/22/17.
//  Copyright © 2017 Koshr. All rights reserved.
//

#include "Truck.hpp"
#include <iostream>
using namespace std;
Truck::Truck(){
    //cout<<"Truck @ .c"<<endl;
}

VehicleSize Truck::getSize(){
    //cout<<"[T]"<<endl;
    return VehicleSize::Large;
}
