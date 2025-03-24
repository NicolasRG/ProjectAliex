#include "util_operations.h"
#include "dropletstate.h"

using namespace godot;


    DropletState* internal_map_state_idl(int state_id){
        switch (state_id)
        {
        case(1):
            /* code */
            return new IdleState();
            break;
        case(2):
            return new RunState();
        default:
            return new IdleState();
            break;
        }
    }