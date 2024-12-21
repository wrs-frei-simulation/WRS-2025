/**
    Pressure Gauge Controller
    @author Kenta Suzuki
*/

#include <cnoid/Joystick>
#include <cnoid/SimpleController>

using namespace cnoid;

class PressureGaugeController : public SimpleController
{
    SimpleControllerIO* io;
    bool useDebugMode;
    Link* hand;

    Joystick joystick;

public:

    virtual bool initialize(SimpleControllerIO* io) override
    {
        this->io = io;
        std::ostream& os = io->os();
        Body* body = io->body();

        std::string prefix;

        useDebugMode = false;
        for(auto& option : io->options()) {
            if(option == "debug") {
                useDebugMode = true;
                os << "Debug mode has started." << std::endl;
            } else if(!option.empty()) {
                prefix = option;
                io->os() << "prefix: " << prefix << std::endl;
            }
        }

        hand = body->link(prefix + "HAND");
        if(!hand) {
            os << "The hand is not found." << std::endl;
            return false;
        }
        hand->setActuationMode(Link::JointVelocity);
        io->enableIO(hand);

        joystick.makeReady();
       
        return true;
    }

    virtual bool control() override
    {
        joystick.readCurrentState();

        for(int i = 0; i < 1; ++i) {
            double pos = joystick.getPosition(Joystick::L_STICK_H_AXIS);
            if(fabs(pos) < 0.15) {
                pos = 0.0;
            }

            if(useDebugMode) {
                double q = hand->q();
                double q_upper = hand->q_upper();
                double q_lower = hand->q_lower();

                if((q > q_upper && pos > 0.0) || (q < q_lower && pos < 0.0)) {
                    pos = 0.0;
                }

                hand->dq_target() = pos;
            } else {
                hand->dq_target() = 0.0;
            }
        }

        return true;
    }
};

CNOID_IMPLEMENT_SIMPLE_CONTROLLER_FACTORY(PressureGaugeController)