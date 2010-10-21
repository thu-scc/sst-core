// Copyright 2009-2010 Sandia Corporation. Under the terms
// of Contract DE-AC04-94AL85000 with Sandia Corporation, the U.S.
// Government retains certain rights in this software.
// 
// Copyright (c) 2009-2010, Sandia Corporation
// All rights reserved.
// 
// This file is part of the SST software package. For license
// information, see the LICENSE file in the top level directory of the
// distribution.


#include "sst_config.h"
#include "sst/core/serialization/core.h"

#include <sst/core/timeVortex.h>

namespace SST {

    TimeVortex::TimeVortex() : ActivityQueue() {}

    TimeVortex::~TimeVortex() {}
    
    bool TimeVortex::empty()
    {
	return data.empty();
    }
    
    int TimeVortex::size()
    {
	return data.size();
    }
    
    void TimeVortex::insert(Activity* activity)
    {
	data.insert(activity);
    }
    
    Activity* TimeVortex::pop()
    {
	if ( data.size() == 0 ) return NULL;
	std::multiset<Activity*,Activity::less_time_priority>::iterator it = data.begin();
	Activity* ret_val = (*it);
	data.erase(it);
	return ret_val;

    }

    Activity* TimeVortex::front()
    {
	return *data.begin();
    }

    void TimeVortex::print() const {
	std::multiset<Activity*,Activity::less_time_priority>::iterator it;

	printf("TimeVortex state:\n");
	for ( it = data.begin(); it != data.end(); it++ ) {
	    (*it)->print("  ");
	}
    }

    

} // namespace SST

BOOST_CLASS_EXPORT_IMPLEMENT(SST::ActivityQueue)
BOOST_CLASS_EXPORT_IMPLEMENT(SST::TimeVortex)
