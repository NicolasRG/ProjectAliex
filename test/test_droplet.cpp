#include "../src/droplet.h" // Include your Droplet class header
#include <iostream>

int main() {
    // Initialize a Droplet object
    godot::Droplet droplet;

    // Test setters and getters
    droplet.set_max_run_speed(10.0);
    droplet.set_run_acceleration(2.0);
    droplet.set_base_run_speed(5.0);
    droplet.set_gravity(9.8);
    droplet.set_log_drag(0.5);

    // Print values to verify
    std::cout << "Max Run Speed: " << droplet.get_max_run_speed() << std::endl;
    std::cout << "Run Acceleration: " << droplet.get_run_acceleration() << std::endl;
    std::cout << "Base Run Speed: " << droplet.get_base_run_speed() << std::endl;
    std::cout << "Gravity: " << droplet.get_gravity() << std::endl;
    std::cout << "Log Drag: " << droplet.get_log_drag() << std::endl;

    // Test other functionality
    // droplet._ready(); // Uncomment if you want to test _ready()
    // droplet._process(0.016); // Uncomment if you want to test _process()

    std::cout << "Droplet test completed!" << std::endl;
    return 0;
}