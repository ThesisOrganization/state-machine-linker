import re
import os
import json
import sys

DECLARATION_FILL_INIT = "void fill_init_ptr( void(*** ref_init_ptr)() )"
DECLARATION_FILL_RAISE = "void fill_raise_ptr( void(**** ref_raise_ptr)() )"


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




def get_elements_state_machine(path_topology, list_directory_to_check):
    path_catalog = path_topology + "catalog/"
    
    #num_types_for_element = []
    num_raise_for_type = []

    files_c_to_compile = []
    files_h_to_compile = []

    list_state_machine_names = []
    
    num_directory_to_check = len(list_directory_to_check)
    
    for i in range(0, num_directory_to_check):
        path_files_types = path_catalog + list_directory_to_check[i]
    
        list_files_name = os.listdir(path_files_types)
        list_files_name.sort()
        #print(list_files_name)
    
        num_types_for_actual_element = len(list_files_name)
        
        #num_types_for_element.append(num_types_for_actual_element)
    
        num_raise_for_type.append([])

        list_state_machine_names.append([])
    
        for j in range(0, num_types_for_actual_element):
            path_file_type = path_files_types + list_files_name[j]
    
    
            fproject = open(path_file_type, "r")
    
    
            num_raise_for_type[i].append([])

            json_data = json.load(fproject)
            if "state_machine" in json_data and json_data["state_machine"] != "":
                project_name = json_data["state_machine"]
            else:
                list_state_machine_names[i].append("")
                continue
            
    
            path_project = path_topology + "state_machines/" + project_name + "/"
    
            fproject.close()
    
            generated_file_name = get_string_project(path_project)
            
            list_state_machine_names[i].append(generated_file_name)
            
            file_to_add = path_project + "src-gen/" + generated_file_name + ".c"
            if file_to_add not in files_c_to_compile:
                files_c_to_compile.append(file_to_add)

            file_to_add = path_project + "src-gen/" + generated_file_name + ".h"
            if file_to_add not in files_h_to_compile:
                files_h_to_compile.append(file_to_add)
            
            file_to_add = path_project + "src/sc_types.h"
            if file_to_add not in files_h_to_compile:
                files_h_to_compile.append(file_to_add)
    
            fin = open(path_project + "src-gen/" + generated_file_name + ".h", "r")
            
            full_file = fin.read()
    
            fin.close()
    
            list_events = get_list_events(generated_file_name, full_file)
            list_events = build_function_names(list_events, generated_file_name)
    
            num_of_events = len(list_events)
            
    
            for k in range(0, num_of_events):
                event = list_events[k]
                num_raise_for_type[i][j].append(event)

    return num_raise_for_type, files_c_to_compile, files_h_to_compile, list_state_machine_names

def merge_lists(list_of_lists):
    merge = []
    for l in list_of_lists:
        merge.extend(l)
    return merge



def build_fill_functions(fout, list_element_types, num_types_for_element, num_raise_for_type, path_file_out, list_state_machine_names):

    num_element_types = len(list_element_types)

    functions_to_implement = []
    state_machine_functions = []


    final_string = '#include "' + path_file_out + '.h"\n'

    final_string += "\n"


    ####################################
    #GENERATE FILL INIT PTR
    ###################################
    final_string += DECLARATION_FILL_INIT + "{\n\n"

    for i in range(0, num_element_types):
        merged_list = merge_lists(num_raise_for_type[i])
        if len(merged_list) == 0:
            final_string += "\tref_init_ptr[" + str(list_element_types[i]) + "] = NULL;\n"
            final_string += "\n"
            continue

        num_types = len(num_raise_for_type[i])

        final_string += "\tref_init_ptr[" + str(list_element_types[i]) + "] = malloc(sizeof( void (*)() ) * " + str(num_types) + ");\n"

        for j in range(0, num_types):
            num_raise = len(num_raise_for_type[i][j])
            if num_raise == 0:
                final_string += "\tref_init_ptr[" + str(list_element_types[i]) + "]" + "[" + str(j) + "]" + " = NULL;\n"
                continue

            function_name = "init_" + list_element_types[i] + "_" + str(j)
            functions_to_implement.append(function_name)
            state_machine_functions.append(list_state_machine_names[i][j])

            final_string += "\tref_init_ptr[" + str(list_element_types[i]) + "]" + "[" + str(j) + "]" + " = " + function_name + ";\n"

        final_string += "\n"


    final_string += "}\n\n"

    ####################################
    #GENERATE INIT FUNCTIONS
    ###################################
    if len(functions_to_implement) != len(state_machine_functions):
        print("ERROR: len(functions_to_implement) != len(state_machine_functions)")
        return

    num_functions_to_implement = len(functions_to_implement)
    for i in range(num_functions_to_implement):
        final_string += "void " + functions_to_implement[i] + "(" + "){\n"

        final_string += "\t" + state_machine_functions[i] + "* sc = malloc(sizeof(" + state_machine_functions[i] + "));\n"
        final_string += "\t" + state_machine_functions[i].lower() + "_init(sc);\n"
        final_string += "\t" + state_machine_functions[i].lower() + "_enter(sc);\n"

        final_string += "}\n\n"


    ####################################
    #GENERATE FILL RAISE PTR
    ###################################
    final_string += DECLARATION_FILL_RAISE + "{\n\n"

    for i in range(0, num_element_types):
        merged_list = merge_lists(num_raise_for_type[i])
        if len(merged_list) == 0:
            final_string += "\tref_raise_ptr[" + str(list_element_types[i]) + "] = NULL;\n"
            final_string += "\n"
            continue
        
        num_types = len(num_raise_for_type[i])

        final_string += "\tref_raise_ptr[" + str(list_element_types[i]) + "] = malloc(sizeof( void (**)() ) * " + str(num_types) + ");\n"

        for j in range(0, num_types):
            num_raise = len(num_raise_for_type[i][j])
            if num_raise == 0:
                final_string += "\tref_raise_ptr[" + str(list_element_types[i]) + "]" + "[" + str(j) + "]" + " = NULL;\n"
                continue

            final_string += "\tref_raise_ptr[" + str(list_element_types[i]) + "]" + "[" + str(j) + "]" + " = malloc(sizeof( void (*)() ) * " + str(num_raise) + ");\n"

            for k in range(0, num_raise):
                final_string += "\tref_raise_ptr[" + str(list_element_types[i]) + "]" + "[" + str(j) + "]" + "[" + str(k) + "]" + " = " + num_raise_for_type[i][j][k] + ";\n"

        final_string += "\n"


    final_string += "}\n\n"


    fout.write(final_string)

def build_header_file(fout, list_element_types, path_file_out, files_h_to_compile):
    final_string = ""

    final_string += "#ifndef " + path_file_out.upper() + "_H\n"
    final_string += "#define " + path_file_out.upper() + "_H\n"

    final_string += "\n"

    for file_h in files_h_to_compile:
        final_string += '#include "' + file_h + '"\n'

    final_string += "\n"

    final_string += "typedef enum _element_type{\n"
    final_string += "\t" + list_element_types[0] + " = 0,\n"
    for element in list_element_types[1:]:
        final_string += "\t" + element + ",\n"
    final_string += "} element_type;\n"

    final_string += "\n"

    final_string += DECLARATION_FILL_INIT + ";\n"

    final_string += DECLARATION_FILL_RAISE + ";\n"

    final_string += "\n"

    final_string += "#endif /* " + path_file_out.upper() + "_H */\n"

    fout.write(final_string)


def build_files(fout, fheader, list_element_types, path_topology, list_directory_to_check, path_file_out):

    num_raise_for_type, files_c_to_compile, files_h_to_compile, list_state_machine_names = get_elements_state_machine(path_topology, list_directory_to_check)
    num_types_for_element = get_num_types_for_element(num_raise_for_type)

    build_fill_functions(fout, list_element_types, num_types_for_element, num_raise_for_type, path_file_out, list_state_machine_names)

    build_header_file(fheader, list_element_types, path_file_out, files_h_to_compile)

    return files_c_to_compile, files_h_to_compile



if len(sys.argv) < 2:
    path_topology = "tests_topology/"
else:
    path_topology = sys.argv[1]

if len(sys.argv) < 3:
    path_file_out = "linking"
else:
    path_file_out = sys.argv[2]

list_element_types = ["CENTRAL", "REGIONAL", "LOCAL", "SENSOR", "ACTUATOR", "LAN"]
list_directory_to_check = ["central/", "regional/", "local/", "sensor/", "actuator/", "lan/"]



fout = open(path_file_out + ".c", "w")
fheader = open(path_file_out + ".h", "w")

list_files_c_to_compile, list_files_h_to_compile = build_files(fout, fheader, list_element_types, path_topology, list_directory_to_check, path_file_out)

fout.close()
fheader.close()


list_files_c_to_compile.append(path_file_out+".c")
list_files_h_to_compile.append(path_file_out+".h")



print('PASSING_C="',end='')
for file_c in list_files_c_to_compile:
    print(file_c + " ", end="")
print('" ', end="")

print('PASSING_H="',end="")
for file_h in list_files_h_to_compile:
    print(file_h + " ", end="")
print('" ')



