import re
import os
import json
import sys


list_element_types = ["CENTRAL", "REGIONAL", "LOCAL", "SENSOR", "ACTUATOR", "LAN"]
list_directory_to_check = ["actuator/", "central/", "local/", "regional/", "sensor/", "lan/"]



string_path_topology = "tests_topology/"
string_path_catalog = string_path_topology + "catalog/"

for directory in list_directory_to_check:
    path = string_path_catalog + directory

    list_files_name = os.listdir(path)
    list_files_name.sort()
    print(list_files_name)


string_path1 = "tests_topology/state_machines/prova_rapida/src-gen/"
string_path2 = "tests_topology/state_machines/actuator-state-machine/src-gen/"



list_files_name1 = os.listdir(string_path1)
list_files_name2 = os.listdir(string_path2)

#print(list_files_name1)
#print(list_files_name2)

string_project1 = list_files_name1[0][:-2]
string_project2 = list_files_name2[0][:-2]

#print(string_project1)
#print(string_project2)


#string_project1 = "Nomemio"
#string_project2 = "Statechart"

file1 = open(string_path1 + string_project1 + ".h", "r")
file2 = open(string_path2 + string_project2 + ".h", "r")

full_file1 = file1.read()
full_file2 = file2.read()



#print(string_regex)

def build_regex(string_project):
    start_string = "typedef enum  {\n"
    end_string = "\n} " + string_project + "EventID;"
    
    string_regex = start_string + "((.|\n)*)" + end_string

    return string_regex

def clean_string(string, string_project):
    return string.strip().replace(string_project + "_", "")

def get_events_names(string, string_project):
    types_list = string.split(",\n")[1:]
    return [clean_string(x, string_project) for x in types_list]

def get_list_events(string_project, full_file2):
    string_regex = build_regex(string_project)
    
    #final = re.search(string_regex, full_file1)
    final = re.findall(string_regex, full_file2)
    events_names = get_events_names(final[0][0], string_project)
    return events_names

def build_function_names(events_names, string_project):
    return [string_project.lower() + "_raise_" + x for x in events_names]


def build_fill_functions(fout, list_element_types, num_types_for_element, num_raise_for_type, string_project):

    num_element_types = len(list_element_types)

    functions_to_implement = []

    final_string = ""


    ####################################
    #GENERATE FILL INIT PTR
    ###################################
    final_string += "void fill_init_ptr( void(*** ref_init_ptr)() ){\n\n"

    for i in range(0, num_element_types):
        final_string += "\tref_init_ptr[" + str(list_element_types[i]) + "] = malloc(sizeof( void (*)() ) * " + str(num_types_for_element[i]) + ");\n"
        for j in range(0, num_types_for_element[i]):
            function_name = "init_" + list_element_types[i] + "_" + str(j)
            functions_to_implement.append(function_name)
            final_string += "\tref_init_ptr[" + str(list_element_types[i]) + "]" + "[" + str(j) + "]" + " = " + function_name + ";\n"
        final_string += "\n"


    final_string += "}\n\n"

    ####################################
    #GENERATE INIT FUNCTIONS
    ###################################
    for function_name in functions_to_implement:
        final_string += "void " + function_name + "(" + "){\n"
        final_string += "}\n\n"


    ####################################
    #GENERATE FILL RAISE PTR
    ###################################
    final_string += "void fill_raise_ptr( void(**** ref_raise_ptr)() ){\n\n"

    for i in range(0, num_element_types):
        final_string += "\tref_raise_ptr[" + str(list_element_types[i]) + "] = malloc(sizeof( void (**)() ) * " + str(num_types_for_element[i]) + ");\n"

        for j in range(0, num_types_for_element[i]):
            final_string += "\tref_raise_ptr[" + str(list_element_types[i]) + "]" + "[" + str(j) + "]" + " = malloc(sizeof( void (*)() ) * " + str(len(num_raise_for_type[i][j])) + ");\n"

            for k in range(0, len(num_raise_for_type[i][j])):
                final_string += "\tref_raise_ptr[" + str(list_element_types[i]) + "]" + "[" + str(j) + "]" + "[" + str(k) + "]" + " = " + num_raise_for_type[i][j][k] + ";\n"

        final_string += "\n"


    final_string += "}\n\n"


    fout.write(final_string)


def build_file_c(fout, events_names, list_element_types, string_project):
    num_types_for_element = [1, 2, 1, 2, 3, 5]
    num_raise_for_type = [[["raise0", "raise1"]], [["raise0", "raise1"], ["raise0", "raise1"]], [["raise0"]], [["raise0", "raise1"], ["raise0"]], [["raise0", "raise1", "raise2"], ["raise0"], ["raise0"]], [["raise0", "raise1", "raise2", "raise3", "raise4"], ["raise0"], ["raise0"], ["raise0"], ["raise0"]]]
    build_fill_functions(fout, list_element_types, num_types_for_element, num_raise_for_type, string_project)





#string_regex = build_regex(string_project2)

#final = re.search(string_regex, full_file1)
#final = re.findall(string_regex, full_file2)


#print(full_file1)

#print(final)
#print(len(final[0]))

#print(final[0][0])

#print(get_events_names(final[0][0], string_project2))

events_names = get_list_events(string_project2, full_file2)

print(build_function_names(events_names, string_project2))

path_file_out = "linking.c"
fout = open(path_file_out, "w")

build_file_c(fout, events_names, list_element_types, string_project2)

#print(events_names)
