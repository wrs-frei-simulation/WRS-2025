/**
    Switch Button Controller
    @author Kenta Suzuki
*/

#include <cnoid/MathUtil>
#include <cnoid/SimpleController>
#include <cnoid/SpotLight>

using namespace cnoid;

class SwitchButtonController : public SimpleController
{
    SimpleControllerIO* io;
    Link* buttonJoint[2];
    DeviceList<SpotLight> lights;
    double qref[2];
    double qprev[2];
    double dt;
    bool prevButtonState[2];

public:

    virtual bool initialize(SimpleControllerIO* io) override
    {
        this->io = io;
        std::ostream& os = io->os();
        Body* body = io->body();
        lights = body->devices();
        prevButtonState[0] = prevButtonState[1] = false;

        std::string prefix;

        for(auto& option : io->options()) {
            prefix = option;
            io->os() << "prefix: " << prefix << std::endl;
        }

        buttonJoint[0] = body->link(prefix + "BUTTON_G");
        buttonJoint[1] = body->link(prefix + "BUTTON_R");
        for(int i = 0; i < 2; ++i) {
            Link* joint = buttonJoint[i];
            if(!joint) {
                os << "Button joint " << i << " is not found." << std::endl;
                return false;
            }
            qref[i] = qprev[i] = joint->q();
            joint->setActuationMode(Link::JointEffort);
            io->enableIO(joint);
        }

        dt = io->timeStep();

        for(auto& light : lights) {
            // (*os) << light->name() << " is fouond." << std::endl;
            light->on(false);
            light->notifyStateChange();
        }

        return true;
    }

    virtual bool control() override
    {
        static const double P = 10.0;
        static const double D = 5.0;

        for(int i = 0; i < 2; ++i) {
            Link* joint = buttonJoint[i];
            double q = joint->q();
            double q_upper = joint->q_upper();
            double q_lower = joint->q_lower();
            double dq = (q - qprev[i]) / dt;
            double dqref = 0.0;
            qref[i] = 0.005;
            joint->u() = P * (qref[i] - q) + D * (dqref - dq);
            qprev[i] = q;

            bool currentState = q < 0.001 ? true : false;
            if(currentState && !prevButtonState[i]) {
                for(auto& light : lights) {
                    light->on(!light->on());
                    light->notifyStateChange();
                }
                // std::string button_name = i == 0 ? "green" : "red";
                // io->os() << "The " + button_name + " button has been pushed." << std::endl;
            }
            prevButtonState[i] = currentState;
        }

        return true;
    }
};

CNOID_IMPLEMENT_SIMPLE_CONTROLLER_FACTORY(SwitchButtonController)