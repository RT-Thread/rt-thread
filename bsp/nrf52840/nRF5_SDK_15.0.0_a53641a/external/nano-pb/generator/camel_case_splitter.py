def split_camel_case(input):
    def remove_camel_case(camel_case_input):
        no_camel_case = ""
        if len(camel_case_input) <= 0:
            return ""
        no_camel_case += camel_case_input[0].lower()
        for c in camel_case_input[1:]:
            if c.isupper():
                no_camel_case += "_" + c.lower()
            else:
                no_camel_case += c
        return no_camel_case

    underscore_split = input.split("_")
    retval = ""
    for i in underscore_split:
        if is_camel_case_name(i):
            retval += remove_camel_case(i) + "_"
        else:
            retval += i + "_"

    return retval[:-1].replace("__", "_")


def is_camel_case_name(input):
    if '_' in input:
        return False

    if input.islower():
        return False

    if input.isupper():
        return False

    return True