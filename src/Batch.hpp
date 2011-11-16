//
//  Batch.hpp
//  gedparse-ul
//
//  Created by Christopher Miller on 11/16/11.
//  Copyright (c) 2011 FSDEV. All rights reserved.
//

// stl
#include <iostream>
#include <string>

#ifndef __BATCH_HPP_
#define __BATCH_HPP_

namespace FamilySearch { namespace GEDCOM {
   
    class Batch {
    private:
        std::string batch;
        bool _isSet;
        
    public:
        Batch();
        
        std::string& getBatch();
        void setBatch(std::string);
        bool isSet();
        
        friend std::ostream& operator<< (std::ostream&, Batch&);
        friend std::istream& operator>> (std::istream&, Batch&);
    };
    
    std::ostream& operator<< (std::ostream&, Batch&);
    std::istream& operator>> (std::istream&, Batch&);
    
} }

#endif
