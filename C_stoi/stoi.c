int exponentation(int base, int exponent) {
    int result = 1;

    for (int i = 0; i < exponent; i++) {
        result *= base;
    }

    return result;
}

int stoi(char *str) {
    int str_length = 0;

    while (str[str_length]) {
        str_length++;
    }



    int result = 0;
    int i = 0;

    while (str_length > 0 && str[i] != '\0') {
        result += exponentation(10, str_length - 1) * (str[i] - '0');
        i++;
        str_length--;
    }

    return result;
}

