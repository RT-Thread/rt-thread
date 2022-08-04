import re
import pprint
import os
from subprocess import check_output
from optparse import OptionParser

# Constants
rtl_ext_end = ".dfinish"
rtl_ext = None # e.g. '.c.270r.dfinish'. The number '270' will change with gcc version and is auto-detected by the
               # function find_rtl_ext
dir = r'.' # Working directory
su_ext = '.su'
obj_ext = '.o'
manual_ext = '.msu'
read_elf_path = "arm-none-eabi-readelf.exe" # You may need to enter the full path here
stdout_encoding = "utf-8"  # System dependant


class Printable:
    def __repr__(self):
        return "<" + type(self).__name__ + "> " + pprint.pformat(vars(self), indent=4, width=1)


class Symbol(Printable):
    pass


def read_symbols(file):
    from subprocess import check_output

    def to_symbol(read_elf_line):
        v = read_elf_line.split()

        s2 = Symbol()
        s2.value = int(v[1], 16)
        s2.size = int(v[2])
        s2.type = v[3]
        s2.binding = v[4]
        if len(v) >= 8:
            s2.name = v[7]
        else:
            s2.name = ""

        return s2

    output = check_output([read_elf_path, "-s", "-W", file]).decode(stdout_encoding)
    lines = output.splitlines()[3:]
    return [to_symbol(line) for line in lines]


def read_obj(tu, call_graph):
    """
    Reads the file tu.o and gets the binding (global or local) for each function
    :param tu: name of the translation unit (e.g. for main.c, this would be 'main')
    :param call_graph: a object used to store information about each function, results go here
    """
    symbols = read_symbols(tu[0:tu.rindex(".")] + obj_ext)

    for s in symbols:

        if s.type == 'FUNC':
            if s.binding == 'GLOBAL':
                # Check for multiple declarations
                if s.name in call_graph['globals'] or s.name in call_graph['locals']:
                    raise Exception('Multiple declarations of {}'.format(s.name))
                call_graph['globals'][s.name] = {'tu': tu, 'name': s.name, 'binding': s.binding}
            elif s.binding == 'LOCAL':
                # Check for multiple declarations
                if s.name in call_graph['locals'] and tu in call_graph['locals'][s.name]:
                    raise Exception('Multiple declarations of {}'.format(s.name))

                if s.name not in call_graph['locals']:
                    call_graph['locals'][s.name] = {}

                call_graph['locals'][s.name][tu] = {'tu': tu, 'name': s.name, 'binding': s.binding}
            elif s.binding == 'WEAK':
                if s.name in call_graph['weak']:
                    raise Exception('Multiple declarations of {}'.format(s.name))
                call_graph['weak'][s.name] = {'tu': tu, 'name': s.name, 'binding': s.binding}
            else:
                raise Exception('Error Unknown Binding "{}" for symbol: {}'.format(s.binding, s.name))


def find_fxn(tu, fxn, call_graph):
    """
    Looks up the dictionary associated with the function.
    :param tu: The translation unit in which to look for locals functions
    :param fxn: The function name
    :param call_graph: a object used to store information about each function
    :return: the dictionary for the given function or None
    """

    if fxn in call_graph['globals']:
        return call_graph['globals'][fxn]
    else:
        try:
            return call_graph['locals'][fxn][tu]
        except KeyError:
            return None


def find_demangled_fxn(tu, fxn, call_graph):
    """
    Looks up the dictionary associated with the function.
    :param tu: The translation unit in which to look for locals functions
    :param fxn: The function name
    :param call_graph: a object used to store information about each function
    :return: the dictionary for the given function or None
    """
    for f in call_graph['globals'].values():
        if 'demangledName' in f:
            if f['demangledName'] == fxn:
                return f
    for f in call_graph['locals'].values():
        if tu in f:
            if 'demangledName' in f[tu]:
                if f[tu]['demangledName'] == fxn:
                    return f[tu]
    return None


def read_rtl(tu, call_graph):
    """
    Read an RTL file and finds callees for each function and if there are calls via function pointer.
    :param tu: the translation unit
    :param call_graph: a object used to store information about each function, results go here
    """

    # Construct A Call Graph
    function = re.compile(r'^;; Function (.*) \((\S+), funcdef_no=\d+(, [a-z_]+=\d+)*\)( \([a-z ]+\))?$')
    static_call = re.compile(r'^.*\(call.*"(.*)".*$')
    other_call = re.compile(r'^.*call .*$')

    for line_ in open(tu + rtl_ext).readlines():
        m = function.match(line_)
        if m:
            fxn_name = m.group(2)
            fxn_dict2 = find_fxn(tu, fxn_name, call_graph)
            if not fxn_dict2:
                pprint.pprint(call_graph)
                raise Exception("Error locating function {} in {}".format(fxn_name, tu))

            fxn_dict2['demangledName'] = m.group(1)
            fxn_dict2['calls'] = set()
            fxn_dict2['has_ptr_call'] = False
            continue

        m = static_call.match(line_)
        if m:
            fxn_dict2['calls'].add(m.group(1))
            # print("Call:  {0} -> {1}".format(current_fxn, m.group(1)))
            continue

        m = other_call.match(line_)
        if m:
            fxn_dict2['has_ptr_call'] = True
            continue


def read_su(tu, call_graph):
    """
    Reads the 'local_stack' for each function.  Local stack ignores stack used by callees.
    :param tu: the translation unit
    :param call_graph: a object used to store information about each function, results go here
    :return:
    """

    su_line = re.compile(r'^([^ :]+):([\d]+):([\d]+):(.+)\t(\d+)\t(\S+)$')
    i = 1

    for line in open(tu[0:tu.rindex(".")] + su_ext).readlines():
        m = su_line.match(line)
        if m:
            fxn = m.group(4)
            fxn_dict2 = find_demangled_fxn(tu, fxn, call_graph)
            fxn_dict2['local_stack'] = int(m.group(5))
        else:
            print("error parsing line {} in file {}".format(i, tu))
        i += 1


def read_manual(file, call_graph):
    """
    reads the manual stack useage files.
    :param file: the file name
    :param call_graph: a object used to store information about each function, results go here
    """

    for line in open(file).readlines():
        fxn, stack_sz = line.split()
        if fxn in call_graph:
            raise Exception("Redeclared Function {}".format(fxn))
        call_graph['globals'][fxn] = {'wcs': int(stack_sz),
                                      'calls': set(),
                                      'has_ptr_call': False,
                                      'local_stack': int(stack_sz),
                                      'is_manual': True,
                                      'name': fxn,
                                      'tu': '#MANUAL',
                                      'binding': 'GLOBAL'}


def validate_all_data(call_graph):
    """
    Check that every entry in the call graph has the following fields:
    .calls, .has_ptr_call, .local_stack, .scope, .src_line
    """

    def validate_dict(d):
        if not ('calls' in d and 'has_ptr_call' in d and 'local_stack' in d
                and 'name' in d and 'tu' in d):
            print("Error data is missing in fxn dictionary {}".format(d))

    # Loop through every global and local function
    # and resolve each call, save results in r_calls
    for fxn_dict2 in call_graph['globals'].values():
        validate_dict(fxn_dict2)

    for l_dict in call_graph['locals'].values():
        for fxn_dict2 in l_dict.values():
            validate_dict(fxn_dict2)

def resolve_all_calls(call_graph):
    def resolve_calls(fxn_dict2):
        fxn_dict2['r_calls'] = []
        fxn_dict2['unresolved_calls'] = set()

        for call in fxn_dict2['calls']:
            call_dict = find_fxn(fxn_dict2['tu'], call, call_graph)
            if call_dict:
                fxn_dict2['r_calls'].append(call_dict)
            else:
                fxn_dict2['unresolved_calls'].add(call)

    # Loop through every global and local function
    # and resolve each call, save results in r_calls
    for fxn_dict in call_graph['globals'].values():
        resolve_calls(fxn_dict)

    for l_dict in call_graph['locals'].values():
        for fxn_dict in l_dict.values():
            resolve_calls(fxn_dict)


def calc_all_wcs(call_graph):
    def calc_wcs(fxn_dict2, call_graph1, parents):
        """
        Calculates the worst case stack for a fxn that is declared (or called from) in a given file.
        :param parents: This function gets called recursively through the call graph.  If a function has recursion the
        tuple file, fxn will be in the parents stack and everything between the top of the stack and the matching entry
        has recursion.
        :return:
        """

        # If the wcs is already known, then nothing to do
        if 'wcs' in fxn_dict2:
            return

        # Check for pointer calls
        if fxn_dict2['has_ptr_call']:
            fxn_dict2['wcs'] = 'unbounded'
            return

        # Check for recursion
        if fxn_dict2 in parents:
            fxn_dict2['wcs'] = 'unbounded'
            return

        # Calculate WCS
        call_max = 0
        for call_dict in fxn_dict2['r_calls']:

            # Calculate the WCS for the called function
            parents.append(fxn_dict2)
            calc_wcs(call_dict, call_graph1, parents)
            parents.pop()

            # If the called function is unbounded, so is this function
            if call_dict['wcs'] == 'unbounded':
                fxn_dict2['wcs'] = 'unbounded'
                return

            # Keep track of the call with the largest stack use
            call_max = max(call_max, call_dict['wcs'])

            # Propagate Unresolved Calls
            for unresolved_call in call_dict['unresolved_calls']:
                fxn_dict2['unresolved_calls'].add(unresolved_call)

        fxn_dict2['wcs'] = call_max + fxn_dict2['local_stack']

    # Loop through every global and local function
    # and resolve each call, save results in r_calls
    for fxn_dict in call_graph['globals'].values():
        calc_wcs(fxn_dict, call_graph, [])

    for l_dict in call_graph['locals'].values():
        for fxn_dict in l_dict.values():
            calc_wcs(fxn_dict, call_graph, [])


def print_all_fxns(call_graph):

    def print_fxn(row_format, fxn_dict2):
        unresolved = fxn_dict2['unresolved_calls']
        stack = str(fxn_dict2['wcs'])
        if unresolved:
            unresolved_str = '({})'.format(' ,'.join(unresolved))
            if stack != 'unbounded':
                stack = "unbounded:" + stack
        else:
            unresolved_str = ''

        print(row_format.format(fxn_dict2['tu'], fxn_dict2['demangledName'], stack, unresolved_str))

    def get_order(val):
        if val == 'unbounded':
            return 1
        else:
            return -val

    # Loop through every global and local function
    # and resolve each call, save results in r_calls
    d_list = []
    for fxn_dict in call_graph['globals'].values():
        d_list.append(fxn_dict)

    for l_dict in call_graph['locals'].values():
        for fxn_dict in l_dict.values():
            d_list.append(fxn_dict)

    d_list.sort(key=lambda item: get_order(item['wcs']))

    # Calculate table width
    tu_width = max(max([len(d['tu']) for d in d_list]), 16)
    name_width = max(max([len(d['name']) for d in d_list]), 13)
    row_format = "{:<" + str(tu_width + 2) + "}  {:<" + str(name_width + 2) + "}  {:>14}  {:<17}"

    # Print out the table
    print("")
    print(row_format.format('Translation Unit', 'Function Name', 'Stack', 'Unresolved Dependencies'))
    for d in d_list:
        print_fxn(row_format, d)


def find_rtl_ext():
    # Find the rtl_extension
    global rtl_ext

    for root, directories, filenames in os.walk('.'):
        for f in filenames:
            if (f.endswith(rtl_ext_end)):
                rtl_ext = f[f[:-len(rtl_ext_end)].rindex("."):]
                print("rtl_ext = " + rtl_ext)
                return

    print("Could not find any files ending with '.dfinish'.  Check that the script is being run from the correct "
          "directory.  Check that the code was compiled with the correct flags")
    exit(-1)


def find_files():
    tu = []
    manual = []
    all_files = []
    for root, directories, filenames in os.walk(dir):
        for filename in filenames:
            all_files.append(os.path.join(root,filename))

    files = [f for f in all_files if os.path.isfile(f) and f.endswith(rtl_ext)]
    for f in files:
        base = f[0:-len(rtl_ext)]
        short_base = base[0:base.rindex(".")]
        if short_base + su_ext in all_files and short_base + obj_ext in all_files:
            tu.append(base)
            print('Reading: {}{}, {}{}, {}{}'.format(base, rtl_ext, short_base, su_ext, short_base, obj_ext))

    files = [f for f in all_files if os.path.isfile(f) and f.endswith(manual_ext)]
    for f in files:
        manual.append(f)
        print('Reading: {}'.format(f))

    # Print some diagnostic messages
    if not tu:
        print("Could not find any translation units to analyse")
        exit(-1)

    return tu, manual


def main():

    # Find the appropriate RTL extension
    find_rtl_ext()

    # Find all input files
    call_graph = {'locals': {}, 'globals': {}, 'weak': {}}
    tu_list, manual_list = find_files()

    # Read the input files
    for tu in tu_list:
        read_obj(tu, call_graph)  # This must be first

    for fxn in call_graph['weak'].values():
        if fxn['name'] not in call_graph['globals'].keys():
            call_graph['globals'][fxn['name']] = fxn

    for tu in tu_list:
        read_rtl(tu, call_graph)
    for tu in tu_list:
        read_su(tu, call_graph)

    # Read manual files
    for m in manual_list:
        read_manual(m, call_graph)

    # Validate Data
    validate_all_data(call_graph)

    # Resolve All Function Calls
    resolve_all_calls(call_graph)

    # Calculate Worst Case Stack For Each Function
    calc_all_wcs(call_graph)

    # Print A Nice Message With Each Function and the WCS
    print_all_fxns(call_graph)




def ThreadStackStaticAnalysis(env):
    print('Start thread stack static analysis...')

    import rtconfig
    read_elf_path = rtconfig.EXEC_PATH + r'\readelf.exe'
    main()

    print('\nThread stack static analysis done!')
    return
