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
    Link* hand;
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

        hand = body->link(prefix + "GAUGE_HAND");
        if(!hand) {
            os << "The hand is not found." << std::endl;
            return false;
        }
        hand->setActuationMode(Link::JointDisplacement);
        io->enableIO(hand);

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
        bool is_valve_opened = valve->q() < radian(0.0) ? true : false;
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

        double q1 = valve->q();
        double q1_upper = valve->q_upper();
        double q1_lower = valve->q_lower();
        double q1_range = fabs(q1_upper) + fabs(q1_lower);
        double q1_rate = (q1 - q1_lower) / q1_range;

        double q2 = hand->q();
        double q2_upper = hand->q_upper();
        double q2_lower = hand->q_lower();
        double q2_range = fabs(q2_upper) + fabs(q2_lower);
        double q2_target = q2_upper - q2_range * q1_rate;

        if(q2_target > q2_upper) {
            q2_target = q2_upper;
        } else if(q2_target < q2_lower) {
            q2_target = q2_lower;
        }

        hand->q_target() = q2_target;

        return true;
    }
};

CNOID_IMPLEMENT_SIMPLE_CONTROLLER_FACTORY(LeakedLineController)