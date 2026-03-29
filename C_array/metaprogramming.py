def generate_new_array(source_file_path, result_file_path, desired_type, prefix):
    with open(source_file_path, 'r') as f:
        lines = f.readlines()
    
    source_code = "".join(lines[1:])
    source_code = source_code.replace("TokenArray", f"{prefix}Array")
    source_code = source_code.replace("Token", desired_type)
    source_code = source_code.replace("token", desired_type)

    with open(result_file_path, 'w') as f:
        f.write(source_code)


generate_new_array("token_array.c", "char_array.c", "char", "Char")