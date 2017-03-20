 Project made at the University of Applied Sciences Potsdam; Course: 11EG-P - Lost in Navigation; WiSe 2016/17 


# Project Luna
## The rolling companion robot

[University of Applied Sciences Potsdam](http://www.fh-potsdam.de/)  
Semester: Winter 2016/17  
Course: [11EG-P: Lost in Navigation](https://incom.org/workspace/6888)  
Collaborators: [miduku](https://github.com/miduku), [flempke](https://github.com/flempke), [edgalindo](https://github.com/edgalindo)   
Supervisors: [Fabian Morón Zirfas](https://incom.org/profil/270), [Prof. Myriel Milicevic](https://incom.org/profil/6664)
 
This Project was realized with [Node.js](https://nodejs.org/en/), [Particle API JS](https://docs.particle.io/reference/javascript/), and the [Particle Desktop IDE](https://www.particle.io/products/development-tools/particle-desktop-ide) during the cource *Lost in Navigation* at the *University of Applied Sciences Potsdam*.

### About
This is the repository containing the necessary code and other assets to build a rolling robot. This robot is a prototype created during a course at the University of Applied Sciences Potsdam, which acts as a kind of companion to follow you around.

This prototype is far from being perfect and manual keyboard inputs are still needed to controll the robot.

![kugel_lauft.gif](https://raw.githubusercontent.com/miduku/project-luna/master/assets/images/kugel_lauft.gif)


### Content
Folders `/photon`and `/web` contain the necessary code to run the robot with the Particle Photon. The `/assets` folder contains other files such as circuit diagrams or .stl files.



### Software
It is necessary to run Node.js to run the code. I would recommend installing Node.js through [nvm](https://github.com/creationix/nvm).
Additionally you need to have a [particle.io account](https://www.particle.io/) and a registered Particle Photon.

To run the code you also need to have a local node server running. If you already have one installed skip the first step

#### 1. Install live-server: 
`npm install -g live-server`

#### 2. 'Upload' ino code
in `/photon/src` you can find the .ino file for the Particle Photon. You can easily flash this into your Photon by just copy&pasting the entire code by creating a new app in [https://build.particle.io/build/new](https://build.particle.io/build/new)

#### 3. Run the API
Open `index.js` in `/web/js` and enter your particle.io credentials:
```
	let config = {
      username: '###@###.##',
      password: '####',
      deviceName: '####',
      // don't edit below
      accessToken: '?',
      deviceId: '?'
    }
```

Open your terminal and go to the folder `/web`
Then enter `live-server`
Your browser should open now.

When connected with the Particle you should be able to control the robto with **w**, **a**, **s**, **d**, **q** and **e**.
**shift** is for full stop.


### Hardware
These hardware components were used to build the robot:
* 1x Particle Photon [link](https://store.particle.io/products/photon)
* 1x Particle Power Shield [link](https://store.particle.io/products/power-shield-with-headers)
* 1x 7,4V LiPo Battery
* 1x 8-Bit Shiftregister SN74HC595N
* 2x Adafruit 1,2A DC/Stepper Motor Driver [link](https://www.adafruit.com/products/2448)
* 4x Omni-wheels [link](http://www.exp-tech.de/en/dagu-48mm-omni-wheels-pair?___from_store=de)
* 4x 6V DCmotor/gearhead [link](http://www.exp-tech.de/en/dagu-48mm-omni-wheels-pair?___from_store=de)
* dot matrix board
* small weights

The acrylic ball has the diameter of 18cm.

![IMG_20170116_225731.jpg](https://raw.githubusercontent.com/miduku/project-luna/master/assets/images/IMG_20170116_225731.jpg)

![IMG_20170117_222056.jpg](https://raw.githubusercontent.com/miduku/project-luna/master/assets/images/IMG_20170117_222056.jpg)

![IMG_20170121_123740.jpg](https://raw.githubusercontent.com/miduku/project-luna/master/assets/images/IMG_20170121_123740.jpg)

![IMG_20170122_182610.jpg](https://raw.githubusercontent.com/miduku/project-luna/master/assets/images/IMG_20170122_182610.jpg)



#### 3D Print
The inner chasis was 3D printed and everything was build with modularity in mind.
You can find .stl files in `/assets/stl files`

![IMG_20170115_144418.jpg](https://raw.githubusercontent.com/miduku/project-luna/master/assets/images/IMG_20170115_144418.jpg)

![IMG_20170115_154105.jpg](https://raw.githubusercontent.com/miduku/project-luna/master/assets/images/IMG_20170115_154105.jpg)

![IMG_20170115_182901.jpg](https://raw.githubusercontent.com/miduku/project-luna/master/assets/images/IMG_20170115_182901.jpg)


#### Circuitry
[Fritzing](http://fritzing.org/) files can be found in`/assets/fritzing`

![project-luna_Steckplatine.png](https://raw.githubusercontent.com/miduku/project-luna/master/assets/fritzing/project-luna_Steckplatine.png)

![project-luna_Schaltplan.png](https://raw.githubusercontent.com/miduku/project-luna/master/assets/fritzing/project-luna_Schaltplan.png)

![IMG_20170116_225603.jpg](https://raw.githubusercontent.com/miduku/project-luna/master/assets/images/IMG_20170116_225603.jpg)
