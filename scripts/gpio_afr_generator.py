#! /bin/python

import xml.etree.ElementTree as ET
import sys
import argparse
import os
import re

class MCU:
    def __init__(self, name):
        if len(name) != 11:
            print("Cannot process MCU with not complete name including flash and pin number information.")
            sys.exit(1)

        self.pins = []
        self.name = name

    def add_pin(self, pin):
        self.pins.append(pin)

    def get_mcu_base_name(self):
        return self.name[:9]

    def get_mcu_full_name(self):
        return self.name[:11]

class Pin:
    def __init__(self, name):
        try:
            index = name.index("-")
            _name = name[:index]
        except ValueError:
            _name = name

        try:
            index = _name.index("/")
            __name = _name[:index]
        except ValueError:
            __name = _name

        self.name = __name
        self.af_list = []

    def add_af(self, af_s0, af_s1):
        af_s0 = af_s0.replace("-", "_")
        af_s1 = af_s1.replace("-", "_")
        af_s0 = af_s0.replace("/", "_")
        af_s1 = af_s1.replace("/", "_")
        self.af_list.append((af_s0, af_s1))

class Emitter():
    def __init__(self, mcu):
        self.mcu = mcu

    def print_macro_list(self, stream=sys.stdout, custom_include_protector=None):
        #print header
        if custom_include_protector == None:
            stream.write("#ifndef AFR_" + self.mcu.get_mcu_base_name() + "_H_included\n")
            stream.write("#define AFR_" + self.mcu.get_mcu_base_name() + "_H_included\n")
        else:
            stream.write("#ifndef " + custom_include_protector + "\n")
            stream.write("#define " + custom_include_protector + "\n")

        for pin in self.mcu.pins:
            #skip pins without AF
            if len(pin.af_list) == 0:
                continue

            #form list with macros
            macro_list = []
            for x in pin.af_list:
                start = x[1].find("AF")
                end = x[1].find("_", start)
                macro_val = x[1][start:end]
                macro_val = macro_val.replace("AF", "AFR_")
                macro_name = "AFR_" + pin.name + "_" + x[0]
                macro_list.append((macro_name, macro_val))

            #find longest macro name, to have nice formating ^w^
            longest_len = 0
            for x in macro_list:
                if len(x[0]) > longest_len:
                    longest_len = len(x[0])

            stream.write("\n//" + pin.name + "\n")

            for x in macro_list:
                macro_name = "{:<{}}".format(x[0], longest_len)
                macro_val = x[1]

                stream.write("#define " + macro_name + " " + macro_val + "\n")

        stream.write("\n#endif\n")

class Parser():
    def __init__(self, mcu):
        self.mcu = mcu

    def parse_gpio_config(self, filename):
        self.processRoot(filename)

    def process_PossibleValue_struct(self, pin, af_s0, possible_value):
        pin.add_af(af_s0, possible_value.text)

    def process_SpecificParameter_struct(self, pin, af_s0, specific_parameter):
        for child in list(specific_parameter):
            tag_last_13 = child.tag[-13:]
            if(tag_last_13 == "PossibleValue"):
                self.process_PossibleValue_struct(pin, af_s0, child)

    def process_PinSignal_struct(self, pin, pin_signal):
        af_s0 = pin_signal.attrib["Name"]
        for child in list(pin_signal):
            tag_last_17 = child.tag[-17:]
            if tag_last_17 == "SpecificParameter":
                self.process_SpecificParameter_struct(pin, af_s0, child)

    def process_GPIO_Pin_struct(self, gpio_pin):
        pin = Pin(gpio_pin.attrib["Name"])
        self.mcu.add_pin(pin)

        for child in list(gpio_pin):
            tag_last_9 = child.tag[-9:]
            if tag_last_9 == "PinSignal":
                self.process_PinSignal_struct(pin, child)

    def processRoot(self, filename):
        tree = ET.parse(filename)
        root = tree.getroot()

        for child in root:
            tag_last_8 = child.tag[-8:]
            if tag_last_8 == "GPIO_Pin":
                self.process_GPIO_Pin_struct(child)

    def parse_variant_file_for_gpio(self, variant_file):
        tree = ET.parse(variant_file)
        root = tree.getroot()

        for child in root:
            if child.tag[-2:] == "IP":
                if child.attrib["InstanceName"] == "GPIO" and child.attrib["Name"] == "GPIO":
                    return child.attrib["Version"]

class Finder():
    def __init__(self, mcu):
        self.mcu = mcu
        return

    def compare_name(self, name, name_list):
        for variant in name_list:
            if self._compare_name(name, variant[:11]) == True:
                return True
        return False

    def _compare_name(self, str1, str2):
        if len(str1) != len(str2):
            return False
        for i in range(len(str1)):
            if str1[i] == 'x' or str2[i] == 'x':
                continue
            elif str1[i] != str2[i]:
                return False
        return True

    def _unroll(self, output, name):
        if output == None:
            output = []

        if '(' not in name:
            output.append(name)

        for letter in re.findall(r'\((.*?)\)', name):
            for char in letter:
                if char == '-':
                    continue

                new_string = name.replace('('+letter+')', char)

                if '(' in new_string:
                    self._unroll(output, new_string)
                else:
                    output.append(new_string)

        return list(set(output))

    def find_mcu_defs(self, path_to_db):
        defs = []
        variants = []

        for root, dirs, files in os.walk(path_to_db):
            for file in files:
                if file.endswith(".xml") and file.startswith(self.mcu.get_mcu_base_name()) and root.endswith("mcu"):
                    variants.append((os.path.join(root, file), file))

        for variant in variants:
            _variants = self._unroll(None, variant[1])

            for i in range(len(_variants)):
                _variants[i] = _variants[i].replace(".xml", "")

            if self.compare_name(self.mcu.get_mcu_full_name(), _variants) == True:
                defs.append(variant)

        return defs

    def find_gpio_file(self, path_to_db, gpio_defs_name):
        for root, dirs, files in os.walk(path_to_db):
            for file in files:
                if file.endswith("Modes.xml") and file.startswith("GPIO-" + gpio_defs_name):
                    return os.path.join(root, file)
        return None

def main():
    parser = argparse.ArgumentParser(description='Generate header files for alternate function registers in STM32.')
    parser.add_argument("--mcu", help="Specify MCU name.", default="none", required=True)
    parser.add_argument('-i', "--input", help="File with GPIO definitions to parse.")
    parser.add_argument("-o", "--output", help="File to generate output into.")
    parser.add_argument("-d", "--db", help="Path to DB folder with STM32CubeMX data.")
    parser.add_argument("--include-protector", help="Specify custom include protector.")

    args = parser.parse_args()

    myMcu = MCU(args.mcu)
    myParser = Parser(myMcu)
    myEmitter = Emitter(myMcu)
    myFinder = Finder(myMcu)

    inputFile = ""

    if args.db == None:
        if args.input == None:
            print("Neither search path or manual input was given, please provide '--db' or '--input' argument.")
            sys.exit(2)
        else:
            inputFile = args.input
    else:
        if args.input == None:

            variant_files = myFinder.find_mcu_defs(args.db)

            if len(variant_files) > 0:
                print("Please select appropriate config file")
                for x in range(len(variant_files)):
                    print(str(x) + " : " + variant_files[x][0])

                choice = input("?")

                try:
                    integer = int(choice)
                except ValueError:
                    print("Given index is can't be converted into integer.")
                    sys.exit(1)

                if integer < 0 or integer > len(variant_files):
                    print("Given index is out of range.")
                    sys.exit(1)

                variant_file = variant_files[integer][0]
            else:
                variant_file = variant_files[0][0]

            inputFile = myFinder.find_gpio_file(args.db, myParser.parse_variant_file_for_gpio(variant_file))
        else:
            print("Manually specified input file and search path is set. Using '--input' instead of searching.")
            inputFile = args.input

    myParser.parse_gpio_config(inputFile)

    if args.output != None:
        f = open(args.output, "w+")
        myEmitter.print_macro_list(f, custom_include_protector=args.include_protector)
    else:
        myEmitter.print_macro_list(custom_include_protector=args.include_protector)

if __name__ == "__main__":
    main()
