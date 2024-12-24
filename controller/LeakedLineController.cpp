/**
    Leaked Line Controller
    @author Kenta Suzuki
*/

#include <cnoid/FireDevice>
#include <cnoid/FountainDevice>
#include <cnoid/MathUtil>
#include <cnoid/SimpleController>
#include <cnoid/SmokeDevice>

using namespace cnoid;

class LeakedLineController : public SimpleController
{
    SimpleControllerIO* io;
    Link* valve;
    DeviceList<FireDevice> fires;
    DeviceList<FountainDevice> fountains;
    DeviceList<SmokeDevice> smokes;

public:

    virtual bool initialize(SimpleControllerIO* io) override
    {
        this->io = io;
        std::ostream& os = io->os();
        Body* body = io->body();
        fires = body->devices();
        fountains = body->devices();
        smokes = body->devices();

        std::string prefix;

        for(auto& option : io->options()) {
            prefix = option;
            io->os() << "prefix: " << prefix << std::endl;
        }

        valve = body->link(prefix + "VALVE_HANDLE");
        if(!valve) {
            os << "The valve is not found." << std::endl;
            return false;
        }
        io->enableInput(valve, Link::JointAngle);

        for(auto& fire : fires) {
            fire->on(true);
            fire->notifyStateChange();
        }
        for(auto& fountain : fountains) {
            fountain->on(true);
            fountain->notifyStateChange();
        }
        for(auto& smoke : smokes) {
            smoke->on(true);
            smoke->notifyStateChange();
        }

        return true;
    }

    virtual bool control() override
    {
        bool is_valve_opened = valve->q() > radian(180.0) ? true : false;
        for(auto& fire : fires) {
            if(is_valve_opened && !fire->on()) {
                fire->on(true);
            } else if(!is_valve_opened && fire->on()) {
                fire->on(false);
            }
            fire->notifyStateChange();
        }
        for(auto& fountain : fountains) {
            if(is_valve_opened && !fountain->on()) {
                fountain->on(true);
            } else if(!is_valve_opened && fountain->on()) {
                fountain->on(false);
            }
            fountain->notifyStateChange();
        }
        for(auto& smoke : smokes) {
            if(is_valve_opened && !smoke->on()) {
                smoke->on(true);
            } else if(!is_valve_opened && smoke->on()) {
                smoke->on(false);
            }
            smoke->notifyStateChange();
        }

        return true;
    }
};

CNOID_IMPLEMENT_SIMPLE_CONTROLLER_FACTORY(LeakedLineController)