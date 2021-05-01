
# FEUP-ESOF

# Conference-Connect

![alt text][mbsimple]

## Links
* [Report](https://github.com/softeng-feup/open-cx-a-programmer-odissey/blob/master/docs/Development-Report.md)
* [Project Board](https://github.com/softeng-feup/open-cx-a-programmer-odissey/projects/1)

## Contents
* [Compiling and Flashing](#Compiling-and-flashing)
* [On First flash](#On-First-Flash)
* [Proximity Mode](#Proximity-Mode)
* [Voting Mode](#Voting-Mode)
* [Sharing Mode](#Sharing-Mode)
* [Changing Radio Channels](#Changing-Radio-Channels)
* [Button Combos](#Button-Combos)
* [Shutting Down](#Shutting-Down)

## Compiling and Flashing
The programs in the microbit folder can be compiled manually using the arm gcc compiler but this is not recommended. The recommended way to compile is using [the mbed compiler](https://ide.mbed.com/). To compile using the mbed compiler microbit must be the selected device and then you can simply create a zip of the program and drag it to the online IDE. Upon hitting compile, if the program is successfully compiled, a ".hex" file will be downloaded automatically. 

To flash the microbit with the program, the microbit must be connect to the computer by USB and then you can simply copy or drag the file to the microbit device. The microbit will do the rest.

## On First Flash

Upon flashing the microbit will display the following message "ID not found" and will wait to receive the users information over USB(serial port). The information is send using the python script available in the repository in the folder "Serial Port". After receiving user information the microbit will enter proximity mode.

## Proximity Mode

Proximity mode is the program's default mode. In this mode the microbit will continuously attempt to find other microbits that share similar interests to the user, if there are no users with interests in common, within range, the microbit will display an "X". If a user is found with an interest in common the microbit will display a symbol representing the interest.

![alt text][mbproximity]
![alt text][mbproxfound]

If a group of more than 2 people are in range of each other the interest that has the most people in common will be displayed, as to encourage group discussion of common topics.

## Voting Mode

The program has a voting mode available, this mode allows users to vote on surveys using button A(yes) and button B(no). To enter voting mode the user must hold button A for a few seconds and then release. At this point the message "Voting" will be displayed on screen and the user is free to cast votes using buttons A and B, the votes will be sent over radio. To return the microbit to proximity mode a user needs to simply click A and B simultaneously.

To make a survey a python script is used. The script, named microbit.py, can be found in the folder Serial Port. To run the script python 3 is needed, as well as modules pySerial and requests. In order to receive votes you will need a microbit connected to a computer with the server microbit program flashed. On windows the [arm mbed serial driver](http://os.mbed.com/media/downloads/drivers/mbedWinSerial_16466.exe) may be needed.

To generate a survey launch the script with arguments: voting "question" timeout "option1" "option2". Example on windows would be: 
> py -3 microbit.py "my question?" 40 "yes" "no"

To repeat the survey later while retaining the previous run the option arguments are not needed, in this example it would be:

> py -3 microbit.py "my question?" 60

After launching the script the following webpage should appear on screen:

![alt text][voting]

Votes from microbits on the same channel and within range of the server will appear automatically on the page.

## Sharing Mode

If the user wishes to share information, such as contacts or CV, the user needs to enter sharing mode by holding button B for a few seconds. To receive information the user must simply be in sharing mode. Information is sent be pressing button A while in sharing mode. Due to microbit limitations the information gathered will be provided to the user upon returning the microbit. To return the microbit to proximity mode a user needs to simply click A and B simultaneously.

## Changing Radio Channels

In order to ensure microbits communicate with the right users a mode to change radio channel is available. In proximity mode, a user can change radio channel by holding buttons A and B. The current radio channel, 0 by default, will the be displayed on screen. Button A will increment the radio channel and B will decrement. Radio channels are limited to 10 channels(0-9).  

![alt text][mbradio]

This mode is useful when there are multiple surveys happening at the same time as a way to ensure users vote on the correct survey, and as a way to ensure a user shares information with the correct person if more are in range. To return the microbit to proximity mode a user needs to simply click A and B simultaneously.

Note: Microbits will use channel 0 as default, upon changing channel proximity mode will no longer be able to communicate with other microbits on channel 0. It is recommended that the user switch channels when needed to vote or share information and then return to channel 0 in order to use proximity mode.

## Button Combos

On Proximity mode:
* Hold A to enter voting mode
* Hold B to enter sharing mode
* Hold A and B simultaneously to enter radio channel changing mode.

On Voting mode:
* Press A to vote yes
* Press B to vote no

On Sharing mode:
* Press A to send information

Changing radio channels:
* Press A to increment radio channel
* Press B to decrement radio channel

To return to proximity mode from other modes simply press A and B simultaneously.

## Shutting Down

After being flashed the microbit can lose power at any time and will retain all information. However if the microbit is flashed with another program, or even the same, all information on the microbit will be lost. 

The microbit can be reset at anytime by pressing the button located on the rear of the microbit, this will not cause the microbit to lose any information.


[voting]: docs/mbscreens/votingpage.jpg "voting page"
[mbradio]: docs/mbscreens/mbradiogroup.jpg "Radio Channel"
[mbproximity]: docs/mbscreens/mbproximity.jpg "No users with common interests found"
[mbproxfound]: docs/mbscreens/mbproxfound.jpg "Found users with common interests"
[mbsimple]: docs/mbscreens/mbsimple.jpg "microbit"
>>>>>>> open-cx-a-programmer-odissey/master
