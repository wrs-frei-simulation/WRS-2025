/**
    MonoCrawler Controller
    @author Kenta Suzuki
*/

#include <cnoid/SharedJoystick>
#include <cnoid/SimpleController>
#include <cnoid/SpotLight>
#include <cnoid/RangeCamera>
#include <cnoid/RangeSensor>

 using namespace std;
 using namespace cnoid;

class MonoCrawlerJoystickController : public SimpleController
{
    SimpleControllerIO* io;
    bool usePseudoContinousTrackMode;
    bool useRearFlipper;
    int spacerActuationMode;
    Link* trackL[3];
    Link* trackR[3];
    Link* spacerJoint[4];
    double qref[4];
    double qprev[4];
    double dt;
    int num_joints;
    int num_tracks;

    struct DeviceInfo {
        DevicePtr device;
        int buttonId;
        bool prevButtonState;
        bool stateChanged;
        DeviceInfo(Device* device, int buttonId)
            : device(device),
              buttonId(buttonId),
              prevButtonState(false),
              stateChanged(false)
        { }
    };
    vector<DeviceInfo> devices;

    SharedJoystickPtr joystick;
    int targetMode;

public:

    virtual bool initialize(SimpleControllerIO* io) override
    {
        this->io = io;
        ostream& os = io->os();
        Body* body = io->body();

        usePseudoContinousTrackMode = true;
        useRearFlipper = true;
        // spacerActuationMode = Link::JointEffort;
        spacerActuationMode = Link::JointVelocity;
        num_joints = 4;
        num_tracks = 6;
        for(auto opt : io->options()) {
            if(opt == "wheel") {
                usePseudoContinousTrackMode = false;
            }
            if(opt == "position") {
                spacerActuationMode = Link::JointDisplacement;
                os << "The joint-position command mode is used." << endl;
            }
            if(opt == "velocity") {
                spacerActuationMode = Link::JointVelocity;
                os << "The joint-velocity command mode is used." << endl;
            }
            if(opt == "mono1") {
                useRearFlipper = false;
                num_joints = 2;
                num_tracks = 4;
            }
        }

        if(usePseudoContinousTrackMode) {
            trackL[0] = body->link("TRACK_L");
            trackL[1] = body->link("TRACK_LF");
            trackR[0] = body->link("TRACK_R");
            trackR[1] = body->link("TRACK_RF");
        } else {
            trackL[0] = body->link("SPROCKET_L");
            trackL[1] = body->link("SPROCKET_LF");
            trackR[0] = body->link("SPROCKET_R");
            trackR[1] = body->link("SPROCKET_RF");
        }

        if(!trackL[0] || !trackL[1] || !trackR[0] || !trackR[1]) {
            os << "The tracks are not found." << endl;
            return false;
        }

        io->enableOutput(trackL[0], Link::JointVelocity);
        io->enableOutput(trackL[1], Link::JointVelocity);
        io->enableOutput(trackR[0], Link::JointVelocity);
        io->enableOutput(trackR[1], Link::JointVelocity);

        spacerJoint[0] = body->link("SPACER_LF");
        spacerJoint[1] = body->link("SPACER_RF");

        if(useRearFlipper) {
            if(usePseudoContinousTrackMode) {
                trackL[2] = body->link("TRACK_LR");
                trackR[2] = body->link("TRACK_RR");
            } else {
                trackL[2] = body->link("SPROCKET_LR");
                trackR[2] = body->link("SPROCKET_RR");
            }

            if(!trackL[2] || !trackR[2]) {
                os << "The rear tracks are not found." << endl;
                return false;
            }

            io->enableOutput(trackL[2], Link::JointVelocity);
            io->enableOutput(trackR[2], Link::JointVelocity);

            spacerJoint[2] = body->link("SPACER_LR");
            spacerJoint[3] = body->link("SPACER_RR");
        }

        for(int i = 0; i < num_joints; ++i) {
            Link* joint = spacerJoint[i];
            if(!joint) {
                os << "Spacer joint " << i << " is not found." << endl;
                return false;
            }
            qref[i] = qprev[i] = joint->q();
            joint->setActuationMode(spacerActuationMode);
            io->enableIO(joint);
        }

        dt = io->timeStep();

        devices = {
            {     body->findDevice<SpotLight>("LIGHT"), Joystick::A_BUTTON },
            {  body->findDevice<RangeCamera>("KINECT"), Joystick::B_BUTTON },
            {       body->findDevice<RangeSensor>("VLP-16"), Joystick::Y_BUTTON }
        };

        // Turn on all the devices
        for(auto& device : devices) {
            device.device->on(true);
            device.device->notifyStateChange();
        }

        joystick = io->getOrCreateSharedObject<SharedJoystick>("joystick");
        targetMode = joystick->addMode();

        return true;
    }

    virtual bool control() override
    {
        joystick->updateState(targetMode);

        double pos[2];
        for(int i = 0; i < 2; ++i) {
            pos[i] = joystick->getPosition(targetMode,
                i == 0 ? Joystick::L_STICK_H_AXIS : Joystick::L_STICK_V_AXIS);
            if(fabs(pos[i]) < 0.2) {
                pos[i] = 0.0;
            }
        }

        if(usePseudoContinousTrackMode) {
            double k = 1.0;
            for(int i = 0; i < num_tracks / 2; ++i) {
                trackL[i]->dq_target() = k * (-2.0 * pos[1] + pos[0]);
                trackR[i]->dq_target() = k * (-2.0 * pos[1] - pos[0]);
            }
        } else {
            double k = 4.0;
            for(int i = 0; i < num_tracks / 2; ++i) {
                trackL[i]->dq_target() = k * (-pos[1] + pos[0]);
                trackR[i]->dq_target() = k * (-pos[1] - pos[0]);
            }
        }

        double pos2[4];
        for(int i = 0; i < 4; ++i) {
            pos2[i] = joystick->getPosition(targetMode,
                i < 2 ? Joystick::L_TRIGGER_AXIS : Joystick::R_TRIGGER_AXIS);
            pos2[i] = joystick->getButtonState(targetMode, 
                i < 2 ? Joystick::L_BUTTON : Joystick::R_BUTTON) ? -1.0 : pos2[i];
            pos2[i] = i < 2 ? -pos2[i] : pos2[i];
            if(fabs(pos2[i]) < 0.2) {
                pos2[i] = 0.0;
            }
        }

        static const double P = 200.0;
        static const double D = 50.0;

        for(int i = 0; i < num_joints; ++i) {
            Link* joint = spacerJoint[i];
            double pos = pos2[i];

            if(spacerActuationMode == Link::JointDisplacement) {
                joint->q_target() = joint->q() + pos * dt;
            } else if(spacerActuationMode == Link::JointVelocity) {
                joint->dq_target() = pos;
            } else if(spacerActuationMode == Link::JointEffort) {
                double q = joint->q();
                double q_upper = joint->q_upper();
                double q_lower = joint->q_lower();
                double dq = (q - qprev[i]) / dt;
                double dqref = 0.0;
                double deltaq = 0.002 * pos;
                qref[i] += deltaq;
                dqref = deltaq / dt;
                joint->u() = P * (qref[i] - q) + D * (dqref - dq);
                qprev[i] = q;
            }
        }

        for(auto& info : devices) {
            if(info.device) {
                bool stateChanged = false;
                bool buttonState = joystick->getButtonState(targetMode, info.buttonId);
                if(buttonState && !info.prevButtonState) {
                    info.device->on(!info.device->on());
                    stateChanged = true;
                }
                auto spotLight = dynamic_pointer_cast<SpotLight>(info.device);
                if(spotLight) {
                    if(joystick->getPosition(targetMode, Joystick::R_TRIGGER_AXIS) > 0.1) {
                        spotLight->setBeamWidth(
                            std::max(0.1f, spotLight->beamWidth() - 0.001f));
                        stateChanged = true;
                    } else if(joystick->getButtonState(targetMode, Joystick::R_BUTTON)) {
                        spotLight->setBeamWidth(
                            std::min(0.7854f, spotLight->beamWidth() + 0.001f));
                        stateChanged = true;
                    }
                }
                info.prevButtonState = buttonState;
                if(stateChanged) {
                    info.device->notifyStateChange();
                }
            }
        }

        return true;
    }
};

CNOID_IMPLEMENT_SIMPLE_CONTROLLER_FACTORY(MonoCrawlerJoystickController)