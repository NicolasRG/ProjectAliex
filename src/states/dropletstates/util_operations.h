#ifndef DROPLSET_STATE_UTIL_P_H
#define DROPLSET_STATE_UTIL_P_H

#include <string>
#include <map>
#include "dropletstate.h"
#include "idlestate.h"
#include "runstate.h"

using namespace godot;
//point of small clean up could be done here to have to instiate
DropletState* internal_map_state_idl(int state_id);


#endif