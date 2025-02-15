class DropletState
{
public:
    DropletState(){}
    virtual ~DropletState(){}
    virtual double calculate_run_veloicty(double delta, bool left, double velocity) = 0;    // "= 0" part makes this method pure virtual, and
                                   // also makes this class abstract.
    virtual void method2() = 0;
};