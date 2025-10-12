# World Robot Summit 2025 Harsh Environment F-REI Challenge, Simulation Disaster Challenge Official GitHub

## Overview
The competition at the tournament is set up with the scenario of “Information gathering and emergency response in a harsh environment, assuming a plant disaster".

## Task（Regularly update）
- We currently have built a simulation environment that takes into account the tasks required for disaster response.
- We have uploaded a simplified course that will allow you to perform each task in the future.

## New information（Update: October 5th, 2025）
- About simulation perfomance
	- In WRS2025, there are no specific regulations for custom robots other than simulation performance. A simulation is considered real-time when the ratio of computation time to simulation time (output by Choreonoid) is close to 1.0.

- The simulation environment consisted of four areas, Area 1 to Area 4, as shown below. The competition was divided into each area.
<img width="50%" src="./fig/wrs2025-plant.png"> 
<img width="50%" src="./fig/wrs2025-plant2.png">

#### Area 1: Lever control, Turning on the light, Opening the door
<img width="50%" src="./fig/area1.png"> 

- The area around the start (Click on the image to view simulation on youtube)

[![](https://img.youtube.com/vi/-OKpuWwvyP4/0.jpg)](https://youtu.be/-OKpuWwvyP4) 

##### Scenario
You use a remote-controlled robot to explore an area where objects are scattered after a plant accident. Since the area is dark, the robot can turn on lights by operating switches to illuminate the area. It will open doors and explore small rooms. To explore the area, the robot must read as many QR codes scattered throughout the area as possible and return to the starting point within the time limit. This area is designed to measure the robot's mobility, operability, and exploration capabilities. Additionally, it is necessary to consider the possibility of limited visibility due to communication issues caused by remote operation, as well as the possibility of sudden power outages.

##### Considering component
- Switch, Door, Stick, Truss field, QR code, and ･･･

<img width="25%" src="./fig/switch.png"><img width="25%" src="./fig/switch1.png"><img width="25%" src="./fig/door2.png">

<img width="25%" src="./fig/door3.png"><img width="25%" src="./fig/stick.png"><img width="25%" src="./fig/truss.png"><img width="25%" src="./fig/qr.png">

#### Area 2: Firefighting
<img width="50%" src="./fig/area2.png"> 

- The area around the start (Click on the image to view simulation on youtube)

[![](https://img.youtube.com/vi/RqlraRtlhWA/0.jpg)](https://youtu.be/RqlraRtlhWA) 

##### Scenario
You must explore this area where objects are scattered after a plant disaster. Since there is a fire in this area, the robots take out a fire hose from the fire extinguisher box and put out the fire. Gases (smoke) and liquids (water) leak from pipes in the area, so the robot can stop the leaking fluids by operating the valves. It is also necessary to read the values of the analog meters installed in the plant. To explore this area, the robot must read as many QR codes scattered throughout the area as possible and return to the starting point within the time limit. This area is constructed to measure the movement, manipulation, and search abilities of the robots. In addition, it is necessary to assume that the field of vision will be reduced due to the effects of communication in remote control and that there may be sudden power outages.

##### Considering component
- Switch, Fire extinguisher box, Valve, Meter, Broken robot, QR code, and ･･･

<img width="25%" src="./fig/switch1.png"><img width="25%" src="./fig/fire1.png"><img width="25%" src="./fig/valve1.png">

<img width="25%" src="./fig/meter1.png"><img width="25%" src="./fig/obstacle-robot.png"><img width="25%" src="./fig/qr.png">


#### Area 3: Running up/down stairs and ramp 
<img width="50%" src="./fig/area3.png"> 

- The area around the start (Click on the image to view simulation on youtube)

[![](https://img.youtube.com/vi/EvLPmafm8BM/0.jpg)](https://youtu.be/EvLPmafm8BM) 

##### Scenario
You must explore this area where objects are scattered after a plant disaster.
Gases (smoke) and liquids (water) leak from pipes in the area, so the robot can stop the leaking fluids by operating the valves. 
The robots must climb the stairs or ramp, turn the valve on the second floor, and stop the leak.
It is also necessary to read the values of the analog meters installed in the plant. To explore this area, the robot must read as many QR codes scattered throughout the area as possible and return to the starting point within the time limit. This area is constructed to measure the movement, manipulation, and search abilities of the robots. In addition, it is necessary to assume that the field of vision will be reduced due to the effects of communication in remote control and that there may be sudden power outages.

##### Considering component
- Switch, Stair, Ramp, Catwalk, Valve, Meter, QR code, and ･･･

<img width="25%" src="./fig/switch1.png"><img width="25%" src="./fig/stairs1.png"><img width="25%" src="./fig/ramp1.png">

<img width="25%" src="./fig/valve1.png"><img width="25%" src="./fig/meter1.png"><img width="25%" src="./fig/qr.png">

#### Area 4: Entering ducts, tank inspections
<img width="50%" src="./fig/area4.png"> 

- The area around the start (Click on the image to view simulation on youtube)

[![](https://img.youtube.com/vi/f4MrvI26BAk/0.jpg)](https://youtu.be/f4MrvI26BAk) 

##### Scenario
You use the robot, which is UAV, to enter the duct and investigate the tank connected to the duct. The passage connected to the duct is narrow and maze-like, requiring careful exploration to avoid getting lost. On the other hand, Gases (smoke) and liquids (water) leak from pipes in the area, so the UGV can stop the leaking fluids by operating the valves. In order to explore the area, you must read as many QR codes as possible, which are scattered around the area, and move the robot from the start area to the goal area within the time limit. This area is constructed to measure the movement, manipulation and search abilities of the robots. In addition, it is necessary to assume that the field of vision will be reduced due to the effects of communication in remote control, and that there may be sudden power outages.

##### Considering component
- Switch, Duct, Valve, Meter, QR code, and ･･･

<img width="25%" src="./fig/switch1.png"><img width="25%" src="./fig/duct1.png"><img width="25%" src="./fig/valve1.png"><img width="25%" src="./fig/meter1.png"><img width="25%" src="./fig/qr.png">

#### About video noise

- As part of the harsh environment challenge, the following video communication noise occasionally occurs. Please operate the robot so that it functions properly, even in the presence of noise.
	- White Noise
	<img width="50%" src="./fig/noise1.png">
 
	- Block Noise
	<img width="50%" src="./fig/noise2.png">

## Plant component
Each component is described at the following URL: https://github.com/wrs-frei-simulation/WRS-2025/blob/main/component.md

## Simulation Environment

Choreonoid is used as the robot simulator in the World Robot Summit 2025 Simulation Disaster Challenge. Moreover, AGX Dynamics is used as a physics engine.

#### AGX Dynamics installation reference
Before constructing the WRS2025 environmental specifications for Choreonoid, please install this software.
- https://choreonoid.org/en/documents/latest/agxdynamics/install/install-agx-ubuntu.html
- Movie for installation (Click on the image to view simulation on youtube)

[![](https://img.youtube.com/vi/SxmwYl_gPEY/0.jpg)](https://youtu.be/SxmwYl_gPEY) 

#### HAIROWorldPlugin installation reference
Please obtain this software before building Choreonoid's WRS2025 environment specification.
Competitors are requested to contact the competition secretariat.
Others should contact JAEA Suzuki at "suzuki.kenta38※jaea.go.jp" .
（Change the ※ to @ when you send us an email. ）

#### How to install Choreonoid
- Requirements
	- OS: Ubuntu22.04，CPU: amd64 (Intel CPU, Ryzen CPU)
	- ROS2: Humble Hawksbill 
	- Cannot be installed on a virtual environment on an Apple Silicon Mac (because the CPU is arm-based)
- Building Choreonoid for the competitor's computer 
	1. Building Choreonoid Without ROS2 for the first time
	2. Rebuilding Choreonoid Without ROS2 For Pre-competition (Already Choreonoid built)
	3. Building Choreonoid for pre-tournament (with ROS2 integration)


#### 1. Building Choreonoid Without ROS2 for the first time
```bash
$ cd
$ git clone https://github.com/choreonoid/choreonoid.git
$ git clone https://github.com/wrs-frei-simulation/WRS-Pre-2024.git choreonoid/ext/WRS2024PRE
$ git clone https://github.com/wrs-frei-simulation/WRS-2025.git choreonoid/ext/WRS2025
```
- **Move ``hairo-world-plugin`` to ``choreonoid/ext/``.**
```bash
$ choreonoid/misc/script/install-requisites-ubuntu-22.04.sh
$ cd ~/choreonoid && mkdir build && cd build
$ cmake .. -DBUILD_AGX_DYNAMICS_PLUGIN=ON -DBUILD_AGX_BODYEXTENSION_PLUGIN=ON -DBUILD_WRS2018=ON -DBUILD_SCENE_EFFECTS_PLUGIN=ON -DBUILD_HAIRO_WORLD_PLUGIN=ON -DENABLE_INSTALL_RPATH_USE_LINK_PATH=ON
$ make -j8 # -j8 for 8-core CPU, -jN for N-core CPU

# Run Choreonoid Without ROS2
$ ./bin/choreonoid
```

#### 2. Rebuilding Choreonoid Without ROS2 For WRS2025 (Already Choreonoid built)
```bash
$ cd ~
$ git clone https://github.com/wrs-frei-simulation/WRS-Pre-2024.git choreonoid/ext/WRS2024PRE
$ git clone https://github.com/wrs-frei-simulation/WRS-2025.git choreonoid/ext/WRS2025
```
- **Move ``hairo-world-plugin`` to ``choreonoid/ext/``.**
```bash
$ cd ~/choreonoid/build
$ cmake .. -DBUILD_AGX_DYNAMICS_PLUGIN=ON -DBUILD_AGX_BODYEXTENSION_PLUGIN=ON -DBUILD_WRS2018=ON -DBUILD_SCENE_EFFECTS_PLUGIN=ON -DBUILD_HAIRO_WORLD_PLUGIN=ON -DENABLE_INSTALL_RPATH_USE_LINK_PATH=ON
$ make -j8 # -j8 for 8-core CPU, -jN for N-core CPU

# Run Choreonoid Without ROS2
$ ./bin/choreonoid
```

#### 3. Building Choreonoid for WRS2025 (with ROS2 integration)
1. Install ROS2 (Humble Hawksbill) first.
```bash
# Add the ROS 2 apt repository
$ sudo apt install software-properties-common
$ sudo add-apt-repository universe
$ sudo apt update && sudo apt install curl -y
$ sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg
$ echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null

# Install ROS 2 packages
$ sudo apt update
$ sudo apt upgrade
$ sudo apt install ros-humble-desktop
$ sudo apt install ros-humble-compressed-image-transport
$ sudo apt install python3-colcon-common-extensions

# Sourcing the setup script (for bash)
$ echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc
$ source ~/.bashrc
```

- Movie for installation (Click on the image to view simulation on youtube)

[![](https://img.youtube.com/vi/pLnRYuRHtV0/0.jpg)](https://youtu.be/pLnRYuRHtV0) 


2. Install Choreonoid
```bash
# Clean-Build Choreonoid With ROS2
$ mkdir -p ~/ws/src
$ cd ~/ros2_ws/src
$ git clone https://github.com/choreonoid/choreonoid.git
$ git clone https://github.com/choreonoid/choreonoid_ros.git
$ git clone https://github.com/wrs-frei-simulation/WRS-Pre-2024.git choreonoid/ext/WRS2024PRE
$ git clone https://github.com/wrs-frei-simulation/WRS-2025.git choreonoid/ext/WRS2025
```
- **Move ``hairo-world-plugin`` to ``choreonoid/ext/``.**
```bash
$ git clone https://github.com/wrs-sim/choreonoid_joy2.git
$ choreonoid/misc/script/install-requisites-ubuntu-22.04.sh
$ cd ~/ros2_ws
$ colcon build --symlink-install --cmake-args -DBUILD_AGX_DYNAMICS_PLUGIN=ON -DBUILD_AGX_BODYEXTENSION_PLUGIN=ON -DBUILD_WRS2018=ON -DBUILD_SCENE_EFFECTS_PLUGIN=ON -DBUILD_HAIRO_WORLD_PLUGIN=ON -DENABLE_INSTALL_RPATH_USE_LINK_PATH=ON

# Run Choreonoid With ROS2
$ source install/setup.bash
$ ros2 run choreonoid_ros choreonoid
```

- Movie for installation (Click on the image to view simulation on youtube)

[![](https://img.youtube.com/vi/2oGcO8FwFng/0.jpg)](https://youtu.be/2oGcO8FwFng) 


## Practice Environment
Once the above installation is successful, you will be able to set up a practice environment for WRS2025.
<img width="100%" src="./fig/practice.png">
<img width="20%" src="./fig/obstacle-robot.png">

#### In the case of Choreonoid Without ROS2
- 1: Building Choreonoid Without ROS2 for the first time
- 2: Rebuilding Choreonoid Without ROS2 For WRS2025 (Already Choreonoid built)
```bash
$ cd ~
$ cd ~/choreonoid/build
$ ./bin/choreonoid ../ext/WRS2025/registration/registration_m3.yaml --wrs-util M3
```

#### In the case of Choreonoid With ROS2
- 3: Building Choreonoid for WRS2025 (with ROS2 integration)
```bash
$ cd ~
$ cd ~/ros2_ws
$ source install/setup.bash
$ ros2 run choreonoid_ros choreonoid ~/ros2_ws/src/choreonoid/ext/WRS2025/registration/registration_m3.yaml --wrs-util M3
```

## Important Notice（Update: August 29th, 2025）
- Robot simulation will be performed on computers provided by the organizers
	- The specs of the organizer's computer: https://www.amazon.co.jp/dp/B0BTM9SYSX?language=en_US

- Please obtain the simulation results via network communication and operate the robots on your own computers. The computers provided by the organizers will serve as servers, and the computers provided by the competitors will serve as clients.
	- The mobile robot is in a simulation on the organizer's computers and connected to the competitor's computers via the network. This relationship is similar to a real mobile robot connected to a host computers via a network. If a team wishes to use its unique robot or functions in the match, it will submit the robot model and program to the organizers, who will implement it on the competition simulation computers.

- Example movie for configuration (Click on the image to view simulation on youtube)
	- Connection and IP setting
	
 	[![](https://img.youtube.com/vi/xuybtku4VAU/0.jpg)](https://youtu.be/xuybtku4VAU) 

	- Remote Robot Control via ROS2 Communication

	[![](https://img.youtube.com/vi/8PlOL2M9Hno/0.jpg)](https://youtu.be/8PlOL2M9Hno) 

- Note: **Do not use Wi-Fi communication while using this connection method. Choreonoid simulation will slow down while Wi-Fi communication is in use.**
  
### To process Choreonoid on a Nvidia GPU（Update: August 28th, 2025）
1. Select Prime Profiles in "NVIDIA settings".
2. For "Select the GPU you would like to use", select "NVIDIA (Performance Mode)"
<img width="66%" src="./fig/gpu-setting.png">

3. When you launch Choreonoid, if it displays “Driver Profile: NVIDIA Corporation ○○” as shown below, Choreonoid will use the NVIDIA GPU. 
<img width="66%" src="./fig/gpu-choreonoid.png">

- However, when running on a laptop, please perform Choreonoid simulations while connected to a power source (simulations will run slowly if not connected).

## Pre-check list for competitors

1. Obtaining the AGX license and HAIROWorldPlugin
	- Obtain the AGX license from the competition secretariat
	- Apply for use HAIROWorldPlugin and receive the HAIROWorldPlugin.zip file

2. Installing ROS2
	- Install ROS2 appropriate for the OS you are using.

3. Building Choreonoid
	- Build a practice/competition environment by referring to the following page
	- https://github.com/wrs-frei-simulation/WRS-2025?tab=readme-ov-file#simulation-environment

4. Loading practice/competition environment
	- Load the practice/competition environment by referring to the following page
	- https://github.com/wrs-frei-simulation/WRS-2025?tab=readme-ov-file#practice-environment 

5. Introducing your robots to the environment
	- Introduce your own robot into a environment by referring to the following page
	- https://github.com/wrs-frei-simulation/WRS-2025/blob/main/place_robot.md


## Competition Environment
Please start Choreonoid with the following command.

#### In the case of Choreonoid Without ROS2
```bash
$ cd ~
$ cd ~/choreonoid/build
$ ./bin/choreonoid ../ext/WRS2025/registration/registration/registration_20251010.yaml --wrs-util PS-1
```

#### In the case of Choreonoid With ROS2
```bash
$ cd ~
$ cd ~/ros2_ws
$ source install/setup.bash
$ ros2 run choreonoid_ros choreonoid ~/ros2_ws/src/choreonoid/ext/WRS2025/registration/registration_20251010.yaml --wrs-util PS-1
```

| YAML file | Arguments | Explanation |
| ---- | ---- | ---- |
| registration_20251010.yaml | ``PS-1`` | Loading preliminary environment |
| registration_20251010.yaml | ``PS-2`` | Loading preliminary environment |
| registration_20251010.yaml | ``PS-3`` | Loading preliminary environment |
| registration_20251010.yaml | ``PS-4`` | Loading preliminary environment |
| registration_20251011.yaml | ``PS-1`` | Loading semifinal environment |
| registration_20251011.yaml | ``PS-2`` | Loading semifinal environment |
| registration_20251011.yaml | ``PS-3`` | Loading semifinal environment |
| registration_20251011.yaml | ``PS-4`` | Loading semifinal environment |
| registration_20251012.yaml | ``PS-12`` | Loading final environment |
| registration_20251012.yaml | ``PS-34`` | Loading final environment |


## 2024 Pre-tournament
- 2024 Pre-tournament Official GitHub page: https://github.com/wrs-frei-simulation/WRS-Pre-2024

- Sample movie (Click on the image to view simulation on youtube)
  - Overview of the entire area
    
    [![](https://img.youtube.com/vi/Oi1t4SQqD-A/0.jpg)](https://www.youtube.com/watch?v=Oi1t4SQqD-A) 
	
  - Robot simulation

    [![](https://img.youtube.com/vi/b9BqyA2T81Y/0.jpg)](https://www.youtube.com/watch?v=b9BqyA2T81Y)
     
  - Simulation of air duct intrusion affected by air flow

    [![](https://img.youtube.com/vi/iCsacqRvRAQ/0.jpg)](https://www.youtube.com/watch?v=iCsacqRvRAQ)

- Live Broadcast
  - Preliminary contest: https://www.youtube.com/watch?v=bKAUXahBdgg
  - Final: https://www.youtube.com/watch?v=ruW7kajVFAw
