# openCX-a-programmer-odissey Development Report

Welcome to the documentation pages for Connection Connect a module of **openCX**!

You can find here detailed information about the module, from a high-level vision to low-level implementation decisions, a kind of Software Development Report (see [template](https://github.com/softeng-feup/open-cx/blob/master/docs/templates/Development-Report.md)), organized by discipline (as of RUP): 

* Business modeling 
  * [Product Vision](#Product-Vision)
  * [Elevator Pitch](#Elevator-Pitch)
* Requirements
  * [Use Case Diagram](#Use-case-diagram)
  * [User stories](#User-stories)
  * [UI Mockups](#UI-mockups)
  * [Domain model](#Domain-model)
* Architecture and Design
  * [Physical Architecture](#Physical-architecture)
  * [Logical architecture](#Logical-architecture)
  * [Prototype](#Prototype)
* Implementation
  * [Iteration 1](#Iteration-1)
  * [Iteration 2](#Iteration-2)
  * [Iteration 3](#Iteration-3)
  * [Iteration 4](#Iteration-4)
  * [Iteration 5](#Iteration-5)
* Test
  * [Acceptance tests](#Acceptance-tests)
* Change management
  * [Issues at Github](https://github.com/softeng-feup/open-cx-a-programmer-odissey/issues)
* Project management
  * [Board at Github Projects](https://github.com/softeng-feup/open-cx-a-programmer-odissey/projects/1) 

So far, contributions have been exclusively made by the initial team, but are now open to the community, in all areas and topics: requirements, technologies, development, experimentation, testing, etc.

Please contact us! 

Thank you!

Made by:
 * Álvaro Francisco Barbosa Miranda
 * Gonçalo Santos Oliveira
 * João Filipe Carvalho de Araújo
 * Nuno Miguel Fernandes Marques
 * Pedro Alexandre Vieites Mendes

## Product Vision
Interactions between people in a conference can get easily hampered: conferences are often hosted in an unknown place and the audience comes from all around the world. This means that, most times, it is hard to meet people who have similar interests and network with them without trying to talk to other people and then coming to the conclusion you have nothing in common with them. On the other hand, it is not uncommon to carry several copies of one's CV so as to deliver them to potential employees. Because of these problems, Conference Connect was born, a revolutionary smart badge that locates people with similar interests, connects people with businesses and allows you to easily participate in surveys!

## Elevator Pitch
We aim to improve interactions between conference goers using the power of technology by offering them a networking platform where they can find people with similar interests, exchange information and even participate in surveys using a [micro:bit](https://microbit.org) powered smart badge.

## Requirements

### Use case diagram
![Use cases](https://user-images.githubusercontent.com/2162852/67559084-2099d280-f710-11e9-9bbb-42d1b8b58b02.png)

Each of these use cases relies on the existence of a Micro:bit device previously configured with the attendee's, lecturer's or company's information.

### User stories
This is a listing of all user stories following the MoSCoW method. Each user story includes a link to the relevant issue (which contains a detailed description of what the user story is about, acceptance tests and who was assigned to it) as well as an estimate of the effort necessary to implement it.

#### Must haves
* As an attendee, I want to easily exchange contact information with other attendees. [View issue](https://github.com/softeng-feup/open-cx-a-programmer-odissey/issues/14) (Effort: M)
* As an attendee i want to be able to retrieve a microbit with my registration data. [View issue](https://github.com/softeng-feup/open-cx-a-programmer-odissey/issues/20) (Effort: S)
* As a attendee or lecturer i want to be able to make a registration with my personal information, interests and optionally a CV before getting a microbit. [View issue](https://github.com/softeng-feup/open-cx-a-programmer-odissey/issues/8) (Effort: S)
* As a attendee or lecturer i want to change my microbit radio channel so that i can do, or enter, surveys without interference from other microbit communications. [View issue](https://github.com/softeng-feup/open-cx-a-programmer-odissey/issues/19) (Effort: S)

#### Should haves
* As an attendee, I want my badge to notify me every time someone with similar interests to mine is near me so that I can have an easier time networking. [View issue](https://github.com/softeng-feup/open-cx-a-programmer-odissey/issues/17)
* As a lecturer, I want to survey my audience so that I can easily collect relevant information to my area or important to me. [View issue](https://github.com/softeng-feup/open-cx-a-programmer-odissey/issues/18)
* As a business, I want to know who is interested in my activities as well as information on who is looking for a job with me. [View issue](https://github.com/softeng-feup/open-cx-a-programmer-odissey/issues/11)

#### Could haves
* As an attendee, I want to easily send my CV to potential employers. [View issue](https://github.com/softeng-feup/open-cx-a-programmer-odissey/issues/12) (Effort: M)
* As an attendee, I want to easily send my CV to potential employers. As an employer i want to retrieve all CVs received on my microbit. [View issue](https://github.com/softeng-feup/open-cx-a-programmer-odissey/issues/12)
* As an attendee, I want to easily exchange contact information with other attendees. [View issue](https://github.com/softeng-feup/open-cx-a-programmer-odissey/issues/14)
* As a business, I want to know who is interested in my activities as well as information on who is looking for a job with me. [View issue](https://github.com/softeng-feup/open-cx-a-programmer-odissey/issues/11)
* As an attendee as i return my microbit i want to receive an e-mail for every person that shared their information with me. [View issue](https://github.com/softeng-feup/open-cx-a-programmer-odissey/issues/21)
* As an attendee, i want to use an optional app on my phone to retrieve the contact information, CVs and any other information in my microbit in realtime. [View issue](https://github.com/softeng-feup/open-cx-a-programmer-odissey/issues/10)

With these user stories, the map looks like this:

![Use cases](https://raw.githubusercontent.com/softeng-feup/open-cx-a-programmer-odissey/f2a3f3e654464fdc5de0e3122b9de8a96b0e25eb/docs/user_story_map.png)

### UI Mockups
UI Mockups and a usage guide can be found on the [project readme](https://github.com/softeng-feup/open-cx-a-programmer-odissey/blob/master/README.md).

### Domain model
![Domain Model](https://github.com/softeng-feup/open-cx-a-programmer-odissey/blob/master/docs/DomainModel.png)

## Architecture and Design
The main focus of our architecture is based on being able to use the micro:bit whithout requiring an application, this is achieved by comunicating with the PC using [serial port](https://github.com/softeng-feup/open-cx-a-programmer-odissey/tree/master/Serial%20Port) on a [server](https://github.com/softeng-feup/open-cx-a-programmer-odissey/tree/master/Microbit%20Programs/server) micro:bit, and by making the connection with [other](https://github.com/softeng-feup/open-cx-a-programmer-odissey/tree/master/Microbit%20Programs/client) micro:bits using the radio.

### Logical architecture
![Physical Layer](https://github.com/softeng-feup/open-cx-a-programmer-odissey/blob/master/docs/Uml.jpg)

### Physical architecture
#### Deployment Diagram
![Physical Layer Deployment](https://github.com/softeng-feup/open-cx-a-programmer-odissey/blob/master/docs/Physical%20Layer%20Deployment.PNG)

#### Component Diagram
![Physical Layer Component](https://github.com/softeng-feup/open-cx-a-programmer-odissey/blob/master/docs/Physical%20Layer%20Component.PNG)

We chose to use C++ while programming the microbit because it's a more lighweight language for the microbit in comparison to python and javascript and the microbit doesn't have much computing power. We also chose to use microbits using serial port with a PC for the servers because it made comunicating with the clients 

### Prototype
In the first iteration we focused on testing microbits capabilities, eventually choosing to program the microbit using C++ due to the heavy hardware limitations (16mhz single core CPU, 16kb of RAM), for example using python the microbit does not have enough memory to even use the bluetooth module, blink tests on microbit are also about 20 times faster on C++. 

After choosing languanges we focused testing the microbit's hardware (radio range and interference, computing performace, the possibility of toggling between bluetooth and radio. Progress was made but no user story was completed in this iteration. 

## Implementation

### Iteration 1
As we had to wait to have a second microbit available on our first iteration we mostly continued our efforts from the prototype, testing the microbits capabilities.

### Iteration 2
On the second interation with two microbits available we coded serveral microbit programs to display images on the LEDs, read and write to the persistent file system, measure radio intensity and a first working proximity program that would display an image on screen when a microbit with a hardcoded interest was in range.

### Iteration 3
On the third iteration we continued working on our proximity program and also started working the voting feature, starting with a microbit program to act as a server and another as a client

### Iteration 4
On the fourth iteration we reassembled all microbit individual programs into a single client program. Programs were separated to improve compile times and general workflow with the microbit. At this point the programs were mature enough to be integrated together. This single program at this point could read an unique user ID into persistent memory, use proximity mode by default and change to voting mode or radio channel changing mode using key combinations. Aditionally a python script to receive votes was coded and work on a web interface for the votes was nearly completed.

### Iteration 5
On the fith iteration the voting interface was completed, work started on open-cx integration.

## Tests
Due to the nature of microbit programing automated unit tests are not viable for the microbit programs themselves.

We intend to test the following features:
* Similar interests - by getting various microbits with different interests together and verifying that only the ones with the most similar interests get paired
* Sending CVs - by verifying that the company has received all the CVsthat were sent using the microbits.
* Voting - by using several microbits in a room to respond to the quiz and verifying that the results to the poll displayed are the same has the answers inputed.

 All of the above tests will be repeated using different number of microbits and different values for the microbits

### Acceptance tests
Acceptance tests can be found in the users stories on our [project board](https://github.com/softeng-feup/open-cx-a-programmer-odissey/projects/1)

## Configuration and change management
Configuration and change management are key activities to control change to, and maintain the integrity of, a project’s artifacts (code, models, documents).

For the purpose of ESOF, we will use a very simple approach, just to manage feature requests, bug fixes, and improvements, using GitHub issues and following the [GitHub flow](https://guides.github.com/introduction/flow/).

## Project management
[Board at Github Projects](https://github.com/softeng-feup/open-cx-a-programmer-odissey/projects/1)

## Evolution - contributions to open-cx

There is no app so there is no possible integration
