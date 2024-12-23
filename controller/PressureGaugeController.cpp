/**
    Pressure Gauge Controller
    @author Kenta Suzuki
*/

#include <cnoid/SimpleController>

using namespace cnoid;

class PressureGaugeController : public SimpleController
{
    SimpleControllerIO* io;
    Link* valve;
    Link* hand;

public:

    virtual bool initialize(SimpleControllerIO* io) override
    {
        this->io = io;
        std::ostream& os = io->os();
        Body* body = io->body();

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
       
        return true;
    }

    virtual bool control() override
    {
        double q1 = valve->q();
        double q1_upper = valve->q_upper();
        double q1_lower = valve->q_lower();
        double q1_range = fabs(q1_upper) + fabs(q1_lower);
        double q1_rate = (q1 - q1_lower) / q1_range;

        double q2 = hand->q();
        double q2_upper = hand->q_upper();
        double q2_lower = hand->q_lower();
        double q2_range = fabs(q2_upper) + fabs(q2_lower);
        double q2_target = q2_range * q1_rate + q2_lower;

        if(q2_target > q2_upper) {
            q2_target = q2_upper;
        } else if(q2_target < q2_lower) {
            q2_target = q2_lower;
        }

        hand->q_target() = q2_target;

        return true;
    }
};

CNOID_IMPLEMENT_SIMPLE_CONTROLLER_FACTORY(PressureGaugeController)