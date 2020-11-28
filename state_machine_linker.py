import re
import os
import json
import sys




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


def get_string_project(path_to_state_machine):
    string_path = path_to_state_machine + "src-gen/"
    #print(string_path)
    list_files_name = os.listdir(string_path)
    
    string_project = list_files_name[0][:-2]

    return string_project


def get_num_types_for_element(num_raise_for_type):
    num_types_for_element = []
    for list_type in num_raise_for_type:
        num_types_for_element.append(len(list_type))

    return num_types_for_element




def get_elements_state_machine(path_topology):
    path_catalog = path_topology + "catalog/"
    
    num_types_for_element = []
    num_raise_for_type = []
    
    num_directory_to_check = len(list_directory_to_check)
    
    for i in range(0, num_directory_to_check):
        path_files_types = path_catalog + list_directory_to_check[i]
    
        list_files_name = os.listdir(path_files_types)
        list_files_name.sort()
        #print(list_files_name)
    
        num_types_for_actual_element = len(list_files_name)
        
        num_types_for_element.append(num_types_for_actual_element)
    
        num_raise_for_type.append([])
    
        for j in range(0, num_types_for_actual_element):
            path_file_type = path_files_types + list_files_name[j]
    
    
            fproject = open(path_file_type, "r")
    
    
            json_data = json.load(fproject)
            if "path" in json_data and json_data["path"] != "":
                project_name = json_data["path"]
            else:
                break
            
    
            path_project = path_topology + "state_machines/" + project_name + "/"
    
            fproject.close()
    
            generated_file_name = get_string_project(path_project)
    
            fin = open(path_project + "src-gen/" + generated_file_name + ".h", "r")
            
            full_file = fin.read()
    
            fin.close()
    
            list_events = get_list_events(generated_file_name, full_file)
            list_events = build_function_names(list_events, generated_file_name)
    
            num_of_events = len(list_events)
            
            num_raise_for_type[i].append([])
    
            for k in range(0, num_of_events):
                event = list_events[k]
                num_raise_for_type[i][j].append(event)

    return num_raise_for_type

#num_raise_for_type = get_elements_state_machine(path_topology)
#num_types_for_element = get_num_types_for_element(num_raise_for_type)
#
#print(num_types_for_element)
#print(num_raise_for_type)



#[[["raise0", "raise1"]], [["raise0", "raise1"], ["raise0", "raise1"]], [["raise0"]], [["raise0", "raise1"], ["raise0"]], [["raise0", "raise1", "raise2"], ["raise0"], ["raise0"]], [["raise0", "raise1", "raise2", "raise3", "raise4"], ["raise0"], ["raise0"], ["raise0"], ["raise0"]]]
'''
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
'''


#print(string_regex)



def build_fill_functions(fout, list_element_types, num_types_for_element, num_raise_for_type):

    num_element_types = len(list_element_types)

    functions_to_implement = []

    final_string = ""


    ####################################
    #GENERATE FILL INIT PTR
    ###################################
    final_string += "void fill_init_ptr( void(*** ref_init_ptr)() ){\n\n"

    for i in range(0, num_element_types):
        if num_types_for_element[i] == 0:
            final_string += "\tref_init_ptr[" + str(list_element_types[i]) + "] = NULL;\n"
            final_string += "\n"
            continue

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
        if num_types_for_element[i] == 0:
            final_string += "\tref_raise_ptr[" + str(list_element_types[i]) + "] = NULL;\n"
            final_string += "\n"
            continue

        final_string += "\tref_raise_ptr[" + str(list_element_types[i]) + "] = malloc(sizeof( void (**)() ) * " + str(num_types_for_element[i]) + ");\n"

        for j in range(0, num_types_for_element[i]):
            final_string += "\tref_raise_ptr[" + str(list_element_types[i]) + "]" + "[" + str(j) + "]" + " = malloc(sizeof( void (*)() ) * " + str(len(num_raise_for_type[i][j])) + ");\n"

            for k in range(0, len(num_raise_for_type[i][j])):
                final_string += "\tref_raise_ptr[" + str(list_element_types[i]) + "]" + "[" + str(j) + "]" + "[" + str(k) + "]" + " = " + num_raise_for_type[i][j][k] + ";\n"

        final_string += "\n"


    final_string += "}\n\n"


    fout.write(final_string)


def build_file_c(fout, list_element_types, path_topology):

    #num_types_for_element = [1, 2, 1, 2, 3, 5]
    #num_raise_for_type = [[["raise0", "raise1"]], [["raise0", "raise1"], ["raise0", "raise1"]], [["raise0"]], [["raise0", "raise1"], ["raise0"]], [["raise0", "raise1", "raise2"], ["raise0"], ["raise0"]], [["raise0", "raise1", "raise2", "raise3", "raise4"], ["raise0"], ["raise0"], ["raise0"], ["raise0"]]]
    #num_raise_for_type = build_function_names(num_raise_for_type, string_project)
    num_raise_for_type = get_elements_state_machine(path_topology)
    num_types_for_element = get_num_types_for_element(num_raise_for_type)

    build_fill_functions(fout, list_element_types, num_types_for_element, num_raise_for_type)





#string_regex = build_regex(string_project2)

#final = re.search(string_regex, full_file1)
#final = re.findall(string_regex, full_file2)


#print(full_file1)

#print(final)
#print(len(final[0]))

#print(final[0][0])

#print(get_events_names(final[0][0], string_project2))

#events_names = get_list_events(string_project2, full_file2)

#print(build_function_names(events_names, string_project2))

list_element_types = ["CENTRAL", "REGIONAL", "LOCAL", "SENSOR", "ACTUATOR", "LAN"]
list_directory_to_check = ["central/", "regional/", "local/", "sensor/", "actuator/", "lan/"]

path_topology = "tests_topology/"

path_file_out = "linking.c"
fout = open(path_file_out, "w")

build_file_c(fout, list_element_types, path_topology)

#print(events_names)
