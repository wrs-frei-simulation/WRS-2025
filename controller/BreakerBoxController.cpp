/**
    Light Controller
    @author Kenta Suzuki
*/

#include <cnoid/EigenUtil>
#include <cnoid/SimpleController>
#include <cnoid/SpotLight>

using namespace cnoid;

class BreakerBoxController : public SimpleController
{
    Link* breaker;
    DeviceList<SpotLight> lights;
    std::ostream* os;

public:
    virtual bool initialize(SimpleControllerIO* io) override
    {
        auto ioBody = io->body();

        std::string prefix;

        for(auto& option : io->options()) {
            prefix = option;
            io->os() << "prefix: " << prefix << std::endl;
        }

        breaker = ioBody->link(prefix + "LEVER_L");
        lights = ioBody->devices();

        if(!breaker) {
            (*os) << prefix << "LEVER_L is not found." << std::endl;
        }
        io->enableInput(breaker, Link::JointAngle);

        os = &io->os();
        for(auto& light : lights) {
            // (*os) << light->name() << " is fouond." << std::endl;
            light->on(false);
            light->notifyStateChange();
        }
        return true;
    }

    virtual bool control() override
    {
        bool is_breaker_up = breaker->q() > radian(0.0) ? true : false;
        for(auto& light : lights) {
            if(is_breaker_up && !light->on()) {
                light->on(true);
            } else if(!is_breaker_up && light->on()) {
                light->on(false);
            }
            light->notifyStateChange();
        }
        return true;
    }
};

CNOID_IMPLEMENT_SIMPLE_CONTROLLER_FACTORY(BreakerBoxController)
