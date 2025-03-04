#ifndef DROPLET_NODE_ATTR_P_H
#define DROPLET_NODE_ATTR_P_H

namespace godot {
    struct DropletAttrs{
        double time_passed;
        //TODD MOVE THIS TO SCENE BASED VAR/STATE 
        //MOVEMENT RELATED STATS
        double MAX_RUN_SPEED = 300.0;
        double RUN_ACCELERATION = 5;
        double BASE_RUN_SPEED = 100.0;  
    
        //JUMP RELATED STATS
        double GRAVITY = 100.0;
        double LOG_DRAG = 25.0;
    };
}

#endif