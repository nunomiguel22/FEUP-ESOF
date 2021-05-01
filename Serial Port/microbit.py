#!/usr/bin/env python3

import os
import requests
import sys
import serial
import serial.tools.list_ports
import time
import webbrowser


microbit_baud_rate = 115200
survey_base_url = "http://45.137.150.177/ESOF/voting.php?"


def get_microbit_port():
    serial_ports = list(serial.tools.list_ports.comports())

    for port in serial_ports:
        sep = str(port.description).find(' (')
        port_description = str(port.description)[:sep]
        if port_description == 'mbed Serial Port':
            return port.device
        if port_description.find(' - ') != -1:
            sep, port_description = str(port.description).split(' - ')
            if port_description == 'mbed Serial Port':
                return port.device
    return -1


def connect_to_port(port):
    mb_port = serial.Serial(port, microbit_baud_rate)
    return mb_port


def read_forever():
    microbit_port = get_microbit_port()
    if microbit_port != -1:
        mb_connect = connect_to_port(microbit_port)
        while True:
            bytes_waiting = mb_connect.inWaiting()
            if bytes_waiting > 0:
                print(mb_connect.readline().decode("utf-8"), end='')
    else:
        print("Port not found")


def generate_full_url(question, option1, option2, timeout):
    survey_url = survey_base_url + "question=" + \
        question + '&' + "timeout=" + str(timeout)
    if option1 != "" and option2 != "":
        survey_url = survey_url + '&' + "option1=" + \
            option1 + '&' + "option2=" + option2
    return survey_url


def voting(timeout, question, option1, option2):
    webbrowser.open(generate_full_url(question, option1, option2, timeout))
    print("Voting started")
    time_started = time.time()
    microbit_port = get_microbit_port()
    if microbit_port != -1:
        mb_connect = connect_to_port(microbit_port)
        # Store ids of microbits that already voted
        ids_voted = []
        # Store votes
        votes_no = 0
        votes_yes = 0

        while (time.time() - time_started) < timeout:
            if mb_connect.inWaiting() > 0:
                received = mb_connect.readline().decode("utf-8").rstrip()
                if received.find('_') != -1:
                    msg, mbid, vote = received.split('_')
                    if msg == 'V':
                        if mbid not in ids_voted:
                            ids_voted.append(mbid)
                            if vote == "Y":
                                votes_yes += 1
                                print("ID: " + mbid + " voted YES")
                            elif vote == "N":
                                votes_no += 1
                                print("ID: " + mbid + " voted NO")
                            requests.get(
                                f'http://45.137.150.177/ESOF/count_vote.php?question={question}&vote={vote}')
    else:
        print("Cannot connect to microbit")
        return

    print("Voting ended Yes: ", votes_yes, " No: ", votes_no)


def send_id(id):
    microbit_port = get_microbit_port()
    if microbit_port != -1:
        mb_connect = connect_to_port(microbit_port)
        mb_connect.write(str.encode(id + '\n'))
        mb_connect.close()


requests.get(f'http://45.137.150.177/ESOF/count_vote.php?question=cor?&vote=Y')

if len(sys.argv) >= 2:
    if sys.argv[1] == "read_forever":
        read_forever()
    if sys.argv[1] == "send_id" and len(sys.argv) >= 3:
        send_id(sys.argv[2])
    if sys.argv[1] == "voting":
        timeout = 10
        option1 = ""
        option2 = ""
        if len(sys.argv) >= 4:
            question = sys.argv[2]
            timeout = int(sys.argv[3])
            if len(sys.argv) >= 6:
                option1 = '\'' + sys.argv[4] + '\''
                option2 = '\'' + sys.argv[5] + '\''
            voting(timeout, question, option1, option2)
