/**
    Pressure Gauge Controller
    @author Kenta Suzuki
*/

#include <cnoid/Joystick>
#include <cnoid/SimpleController>

using namespace std;
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
        ostream& os = io->os();
        Body* body = io->body();

        useDebugMode = false;
        for(auto opt : io->options()) {
            if(opt == "debug") {
                useDebugMode = true;
                os << "Debug mode has started." << endl;
            }
        }

        hand = body->link("HAND");
        if(!hand) {
            os << "The hand is not found." << endl;
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