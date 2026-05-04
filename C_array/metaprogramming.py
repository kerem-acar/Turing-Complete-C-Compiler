def generate_new_array(result_file_path, type, name, prefix):
    with open("template_array.c", 'r') as f:
        source_code = f.read()
    
    
    source_code = source_code.replace("%TYPE%", type)
    source_code = source_code.replace("%NAME%", name)
    source_code = source_code.replace("%PREFIX%", prefix)
    

    with open(result_file_path, 'w') as f:
        f.write(source_code)

generate_new_array("statement_array.c", "AST_Statement", "stat", "Stat")