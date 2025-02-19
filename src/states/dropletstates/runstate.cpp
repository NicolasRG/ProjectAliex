#include "dropletstate.h"

using namespace godot;


//if i make this class house the actual base movementmethods
//what states do i need how much code will the reuse
//run
//idle
//jumping
//slowed or is that part of the others??

class RunState: public DropletState
{
public:
    const std::string stateName = "DROPLET_RUN_STATE";
    //TODO MAKE SURE THAT ALL OLD STATES ARE EXPLICITLY DELETED WHEN VARIABLE ARE SETUP!!!!!!
    RunState(DropletState* oldstate){
        UtilityFunctions::print("Going into run state");
    };

    ~RunState(){};
    

    double calculate_run_veloicty(double delta, bool left, godot::Input* input_handler, AnimatedSprite2D* animatedsprite , double velocity, 
        double RUN_ACCELERATION, double BASE_RUN_SPEED, double MAX_RUN_SPEED);  
    double calculate_jump_velocity(double delta, bool left, Input* input_handler, AnimatedSprite2D* animatedsprite , double velocity);
};

double RunState::calculate_run_veloicty(double delta, bool left, godot::Input* input_handler, AnimatedSprite2D* animatedsprite , double velocity, 
    double RUN_ACCELERATION, double BASE_RUN_SPEED, double MAX_RUN_SPEED){
    UtilityFunctions::print(velocity);
    const double DELTA_DILUTANT = .1;

    double direction;

    if(left){
        direction  = -1;
        animatedsprite->set_flip_h(false);
        UtilityFunctions::print("move left");
        animatedsprite->play();
    }else{
        direction = 1;
        UtilityFunctions::print("move right");
        //move this to state
        animatedsprite->set_flip_h(true);
        animatedsprite->play();
    }

    double calcualted_accelartion = (delta * DELTA_DILUTANT * RUN_ACCELERATION);
    double calculated_velocity = (BASE_RUN_SPEED  + calcualted_accelartion )* direction + velocity;
    //this should be some abs
    if(calculated_velocity > 0){
        calculated_velocity = fmin(calculated_velocity, MAX_RUN_SPEED);
    }else if(calculated_velocity < 0){
        calculated_velocity = fmax(calculated_velocity, (-1*MAX_RUN_SPEED));
    }
        //if the velocity is zerio we dont care

    std::string message = std::to_string(calculated_velocity);
    UtilityFunctions::print(message.data()); 
    return calculated_velocity;
}

double RunState::calculate_jump_velocity(double delta, bool left, Input* input_handler, AnimatedSprite2D* animatedsprite , double velocity){
    return 0.00;
}