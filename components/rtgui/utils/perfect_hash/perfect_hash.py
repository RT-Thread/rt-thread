#!/usr/bin/env python
"""
Generate a minimal perfect hash function for the keys in a file,
desired hash values may be specified within this file as well.
A given code template is filled with parameters, such that the
output is code which implements the hash function.
Templates can easily be constructed for any programming language.

The code is based on an a program A.M. Kuchling wrote:
http://www.amk.ca/python/code/perfect-hash

The algorithm the program uses is described in the paper
'Optimal algorithms for minimal perfect hashing',
Z. J. Czech, G. Havas and B.S. Majewski.
http://citeseer.ist.psu.edu/122364.html

The algorithm works like this:

1.  You have K keys, that you want to perfectly hash against some
    desired hash values.

2.  Choose a number N larger than K.  This is the number of
    vertices in a graph G, and also the size of the resulting table G.

3.  Pick two random hash functions f1, f2, that return values from 0..N-1.

4.  Now, for all keys, you draw an edge between vertices f1(key) and f2(key)
    of the graph G, and associate the desired hash value with that edge.

5.  Check if G is acyclic, i.e. has no loops; if no, go back to step 2.

6.  Assign values to each vertex such that, for each edge, you can add
    the values for the two vertices and get the desired (hash) value 
    for that edge.  This task is easy, because the graph is acyclic.
    This is done by picking a vertex, and assigning it a value of 0.
    Then do a depth-first search, assigning values to new vertices so that
    they sum up properly.

7.  f1, f2, and vertex values of G now make up a perfect hash function.


For simplicity, the implementation of the algorithm combines steps 5 and 6.
That is, we check for loops in G and assign the vertex values in one procedure.
If this procedure succeeds, G is acyclic and the vertex values are assigned.
If the procedure fails, G is cyclic, and we go back to step 2, replacing G
with a new graph, and thereby discarding the vertex values from the failed
attempt.
"""
__author__  = 'Ilan Schnell <ilanschnell@gmail.com>, 2008 (and AMK 2000)'
__license__ = 'GNU GPL 2'
__version__ = '0.1'


import sys, random, string, cStringIO, StringIO

verbose = False
trails = 5


class Graph:
    """
    Implements a graph with 'N' vertices.  First, you connect the graph with
    edges, which have a desired value associated.  Then the vertex values
    are assigned, which will fail if the graph is cyclic.  The vertex values
    are assigned such that the two values corresponding to an edge add up to
    the desired edge value (mod N).
    
    Example:
    >>> G = Graph(3)
    >>> G.assign_vertex_values()
    True
    
    Now we make an edge between vertex 0 and 1 with desired edge value 2:
    >>> G.connect(0, 1, 2)
    
    Make another edge 1:2 with desired edge value 1:
    >>> G.connect(1, 2, 1)
    
    The graph is still acyclic, and assigning values works:
    >>> G.assign_vertex_values()
    True
    >>> G.vertex_values
    [0, 2, 2]
    
    What do these values mean?
    When you add the values for edge 0:1 you get 0 + 2 = 2, as desired.
    For edge 1:2 you add 2 + 2 = 4 = 1 (mod 3), as desired.
    
    Adding edge 0:2 produces a loop, so the graph is no longer acyclic.
    Assigning values fails.
    >>> G.connect(0, 2, 0)
    >>> G.assign_vertex_values()
    False
    """
    def __init__(self, N):
        self.N = N                     # number of vertices
        
        # maps a vertex number to the list of tuples (vertices, edge value)
        # to which it is connected by edges.
        self.adjacent = [[] for n in xrange(N)]
    
    def connect(self, vertex1, vertex2, edge_value):
        """
        Connect 'vertex1' and 'vertex2' with an edge, with associated
        value 'value'
        """
        # Add vertices to each other's adjacent list
        self.adjacent[vertex1].append( (vertex2, edge_value) )
        self.adjacent[vertex2].append( (vertex1, edge_value) )
        
    def assign_vertex_values(self):
        """
        Try to assign the vertex values, such that, for each edge, you can
        add the values for the two vertices involved and get the desired
        value for that edge, i.e. the desired hash key.
        This will fail when the graph is cyclic.

        This is done by a Depth-First Search of the graph.  If the search
        finds a vertex that was visited before, there's a loop and False is
        returned immediately, i.e. the assignment is terminated.
        On success (when the graph is acyclic) True is returned.
        """
        self.vertex_values = self.N * [-1]  # -1 means unassigned
        
        visited = self.N * [False]
        
        # Loop over all vertices, taking unvisited ones as roots.
        for root in xrange(self.N):
            if visited[root]:
                continue

            # explore tree starting at 'root'
            self.vertex_values[root] = 0    # set arbitrarily to zero

            # Stack of vertices to visit, a list of tuples (parent, vertex)
            tovisit = [ (None, root) ]
            while tovisit:
                parent, vertex = tovisit.pop()
                visited[vertex] = True
                
                # Loop over adjacent vertices, but skip the vertex we arrived
                # here from the first time it is encountered.
                skip = True
                for neighbor, edge_value in self.adjacent[vertex]:
                    if skip and neighbor == parent:
                        skip = False
                        continue
                    
                    if visited[neighbor]:
                        # We visited here before, so the graph is cyclic.
                        return False

                    tovisit.append( (vertex, neighbor) )
                    
                    # Set new vertex's value to the desired edge value,
                    # minus the value of the vertex we came here from.
                    self.vertex_values[neighbor] = \
                        ( edge_value - self.vertex_values[vertex] ) % self.N

        # check if all vertices have a valid value
        for vertex in xrange(self.N):
            assert self.vertex_values[vertex] >= 0

        # We got though, so the graph is acyclic,
        # and all values are now assigned.
        return True


def generate_hash(kdic, Hash):
    """
    Return hash functions f1 and f2, and G for a perfect minimal hash.
    Input is dictionary 'kdic' with the keys and desired hash values.
    'Hash' is a random hash function generator, that means Hash(N) returns a
    returns a random hash function which returns hash values from 0..N-1.
    """
    # N is the number of vertices in the graph G
    N = 1 if not kdic else (max(kdic.values()) + 1)
    if verbose >= 2:
        sys.stderr.write('N = %i\n' % N)
    
    trail = 0 # Number of trial graphs so far
    while True:
        if (trail % trails) == 0:   # trails failures, increase N slightly
            if trail > 0:
                N = max(N+1, int(1.05*N))
            if verbose:
                sys.stderr.write('\n')
                sys.stderr.write('Generating graphs N = %i ' % N)
        trail += 1
        
        if verbose:
            sys.stderr.write('.')
            sys.stderr.flush()
        
        G = Graph(N)   # Create graph with N vertices
        f1 = Hash(N)   # Create 2 random hash functions
        f2 = Hash(N)
        
        # Connect vertices given by the values of the two hash functions
        # for each key.  Associate the desired hash value with each edge.
        for key, hashval in kdic.iteritems():
            G.connect(f1(key), f2(key), hashval)
        
        # Try to assign the vertex values.  This will fail when the graph
        # is cyclic.  But when the graph is acyclic it will succeed and we
        # break out, because we're done.
        if G.assign_vertex_values():
            break
    
    if verbose:
        sys.stderr.write('\nAcyclic graph found after %i trails.\n' % trail)
        
    if verbose >= 2:
        sys.stderr.write('N = %i\n' % N)
    if verbose:
        sys.stderr.write('Checking generated hash function... ')

    # Sanity check the result by actually verifying that all the keys
    # hash to the right value.
    for key, hashval in kdic.iteritems():
        assert hashval == ( G.vertex_values[f1(key)] +
                            G.vertex_values[f2(key)] ) % N
    
    if verbose:
        sys.stderr.write('OK\n')
    
    return f1, f2, G.vertex_values


class Hash1:
    """
    Random hash function generator.
    For simplicity and speed, this doesn't implement any byte-level hashing
    scheme.  Instead, a random string is generated and prefixing to str(key),
    and then Python's hashing function is used.
    """
    def __init__(self, N):
        self.N = N
        self.salt = "".join(random.choice(string.letters + string.digits)
                            for i in xrange(8))
        
    def __call__(self, key):
        return hash(self.salt + str(key)) % self.N

    template = """
def perfect_hash(key):
    return (G[ hash('$S1' + str(key)) % $NG ] +
            G[ hash('$S2' + str(key)) % $NG ]) % $NG
"""

class Hash2:
    """
    Random hash function generator.
    Simple byte level hashing, each byte is multiplied in sequence to a table
    containing random numbers modulo N, and then these products are summed up.
    The table with random numbers is dynamically expanded whenever
    a key longer than the current table size is encountered.
    """
    def __init__(self, N):
        self.N = N
        self.salt = []
        
    def __call__(self, key):
        skey = key
        while len(self.salt) < len(skey): # add more salt if necessary
            self.salt.append(random.randint(0, self.N-1))
        
        return sum(self.salt[i] * ord(c)
                   for i, c in enumerate(skey)) % self.N
    
    template = """
S1 = [$S1]
S2 = [$S2]

def hash_f(key, T):
    return sum(T[i % $NS] * ord(c) for i, c in enumerate(str(key))) % $NG

def perfect_hash(key):
    return (G[hash_f(key, S1)] + G[hash_f(key, S2)]) % $NG
"""


class PerfHash:
    """
    This class is designed for creating perfect hash tables at run time,
    which should be avoided, in particulat inserting new keys is
    prohibitively expensive since a new perfect hash table needs to be
    constructed.  However, this class can be usefull for testing.
    
    >>> d = PerfHash({'foo':(429, 'bar'), 42:True, False:'baz'})
    >>> d['foo'], d[42], d[False]
    ((429, 'bar'), True, 'baz')
    >>> d[False] = (1, 2)
    >>> d[False]
    (1, 2)
    >>> d.has_key('foo')
    True
    >>> d.has_key(True)
    False
    """
    def __init__(self, dic):
        self.klst = []
        self.objs = []
        kdic = {}
        for hashval, (key, obj) in enumerate(dic.iteritems()):
            self.klst.append(key)
            self.objs.append(obj)
            kdic[key] = hashval
            
        self.N = len(dic)
        self.f1, self.f2, self.G = generate_hash(kdic, Hash1)

    def __setitem__(self, newkey, newobj):
        dic = {}
        for key in self.klst:
            dic[key] = self[key]
        dic[newkey] = newobj
        self.__init__(dic)

    def hashval(self, key):
        return ( self.G[self.f1(key)] + self.G[self.f2(key)] ) % len(self.G)
    
    def __getitem__(self, key):
        h = self.hashval(key)
        if h < self.N and key == self.klst[h]:
            return self.objs[h]
        else:
            raise IndexError

    def has_key(self, key):
        h = self.hashval(key)
        return h < self.N and key == self.klst[h]

    
class Format:
    """
    >>> class o:
    ...     pass
    >>> o.delimiter = ': '
    >>> o.width = 75
    >>> o.indent = 4
    >>> x = Format( o )
    >>> x( range(10) )
    '0: 1: 2: 3: 4: 5: 6: 7: 8: 9'
    >>> o.delimiter = '; '
    >>> x = Format( o )
    >>> x( range(5) )
    '0; 1; 2; 3; 4'
    >>> o.delimiter = ' '
    >>> x = Format( o )
    >>> x( range(5), quote = True )
    '"0" "1" "2" "3" "4"'
    >>> x(42)
    '42'
    >>> x('Hello')
    'Hello'
    """
    def __init__(self, options):
        names = ['width', 'indent', 'delimiter']
        
        for name in names:
            setattr(self, name, getattr(options, name))

        if verbose >=2:
            sys.stderr.write("Format options:\n")
            for name in names:
                sys.stderr.write('  %s: %r\n' % (name, getattr(self, name)))
    
    def __call__(self, data, quote = False):
        if type(data) != type([]):
            return str(data)
        
        lendel = len(self.delimiter)
        aux = StringIO.StringIO()
        pos = 20
        for i, elt in enumerate(data):
            last = bool(i == len(data)-1)
            
            s = ('"%s"' if quote else '%s') % elt
            
            if pos + len(s) + lendel > self.width:
                aux.write('\n' + (self.indent * ' '))
                pos = self.indent
            
            aux.write(s)
            pos += len(s)
            if not last:
                aux.write(self.delimiter)
                pos += lendel

        return aux.getvalue()


def keyDict(keys_hashes):
    """
    Checks a list with (key, hashvalue) tupels and returns dictionary.

    >>> d = keyDict([(1, 2), (3, 4), (5, 6)])
    >>> d[3]
    4
    """
    K = len(keys_hashes)     # number of keys
    if verbose >= 2:
        sys.stderr.write('K = %i\n' % K)
        
    kdic = dict(keys_hashes)
    if len(kdic) < K:
        sys.stderr.write('Warning: Input contains duplicate keys\n')
    
    if len(set(kdic.values())) < K:
        sys.stderr.write('Warning: Input contains duplicate hash values\n')
    
    return kdic



def generate_code(keys_hashes, template, Hash, options, extra_subs):
    """
    Takes a list of key value pairs and inserts the generated parameter
    lists into the 'template' strinng.  'Hash' is the random hash function
    generator, and the optional keywords are formating options.
    The return value is the substituted code template.
    """
    f1, f2, G = generate_hash(keyDict(keys_hashes), Hash)
    
    assert f1.N == f2.N == len(G)
    assert len(f1.salt) == len(f2.salt)
    
    fmt = Format(options)

    return string.Template(template).substitute(
        NS = len(f1.salt),
        S1 = fmt(f1.salt),
        S2 = fmt(f2.salt),
        NG = len(G),
        G  = fmt(G),
        NK = len(keys_hashes),
        K  = fmt([key for key, hashval in keys_hashes], quote = True),
        H  = fmt([hashval for key, hashval in keys_hashes]),
        **extra_subs)



def read_table(filename, options):
    """
    Reads keys and desired hash value pairs from a file.  If no column
    for the hash value is specified, a sequence of hash values is generated,
    from 0 to N-1, where N is the number of rows found in the file.
    """
    if verbose >= 2:
        sys.stderr.write("Reading table from file `%s' to extract keys.\n" %
                         filename)
    try:
        f = file(filename)
    except IOError :
        exit("Error: Could not open `%s' for reading." % filename)

    keys_hashes = []
    hashval = -1

    if verbose >= 2:
        sys.stderr.write("Reader options:\n")
        for name in ['comment', 'splitby', 'keycol', 'hashcol']:
            sys.stderr.write('  %s: %r\n' %
                             (name, getattr(options, name)))
        
    for n, line in enumerate(f):
        line = line.strip()
        if not line or line.startswith(options.comment):
            continue

        if line.count(options.comment): # strip content after comment
            line = line.split(options.comment)[0].strip()

        row = [col.strip() for col in line.split(options.splitby)]
        
        try:
            key = row[options.keycol-1]
        except IndexError :
            exit("%s:%i: Error: Cannot read key, not enough columns." %
                 (filename, n+1))
            
        if options.hashcol:
            try:
                val = row[options.hashcol-1]
            except IndexError :
                exit("%s:%i: Error: Cannot read hash value, not enough columns."
                     % (filename, n+1))
            try:
                hashval = int(val)
            except ValueError :
                exit("%s:%i: Error: Cannot convert `%s' to int." %
                     (filename, n+1, row[options.hashcol-1]))
        else:
            hashval += 1
        
        keys_hashes.append( (key, hashval) )

    f.close()
    
    if not keys_hashes:
        exit("Error: no keys found in file `%s'." % filename)

    return keys_hashes



def print_keys_hashes(keys_hashes):
    fmt = '%-20s %10s'
    head = fmt % ('Key', 'Hash value')
    sys.stderr.write('\n' + head + '\n')
    sys.stderr.write(len(head)*'-' + '\n')
    for tup in keys_hashes:
        sys.stderr.write(fmt % tup + '\n')
    sys.stderr.write('\n')

def read_template(filename):
    if verbose >= 2:
        sys.stderr.write("Reading template from file `%s'.\n" % filename)

    try:
        f = file(filename)
    except IOError :
        fatal_error("Error: Could not open `%s' for reading." % filename)

    return f.read()


def builtin_template(Hash):
    return """\
# =======================================================================
# ================= Python code for perfect hash function ===============
# =======================================================================

G = [$G]
""" + Hash.template + """
# ============================ Sanity check =============================

K = [$K]
H = [$H]

assert len(K) == len(H) == $NK

for k, h in zip(K, H):
    assert perfect_hash(k) == h
"""


def print_code(code, name, width = 78):
    def center(s):
        v = (width - len(s))/2
        return '='*v + s + '='*v
    sys.stderr.write(center(' BEGIN %s ' % name) + '\n')
    sys.stderr.write(code + '\n')
    sys.stderr.write(center(' END %s ' % name) + '\n')
    

def self_test(options):
    import doctest
    global verbose
    print 'Starting self tests ...'

    def random_word():
        return ''.join(random.choice(string.letters + string.digits)
                       for i in xrange(random.randint(1, 20)))

    def flush_dot():
        sys.stdout.write('.')
        sys.stdout.flush()
        
    def run(K, Hash):
        flush_dot()
        
        keys = [chr(65+i) for i in xrange(K)]
        hashes = range(K)
        
        random.shuffle(keys)
        random.shuffle(hashes)
        
        code = generate_code(zip(keys, hashes),
                             builtin_template(Hash),
                             Hash,
                             options)
        exec(code) in {}

    verbose = False
    for Hash in [Hash1, Hash2]:
        for K in xrange(0, 27):
            run(K, Hash)
    print
    
    verbose = options.verbose
    N = 250
    for Hash in [Hash1, Hash2]:
        if verbose:
            print 'Generating approximately %i key/hash pairs ...' % N
        kh = {}
        for i in xrange(N):
            kh[random_word()] = i

        if verbose:
            print 'Generating code for %i key/hash pairs ...' % len(kh)
        code = generate_code(kh.items(),
                             builtin_template(Hash),
                             Hash,
                             options)
        if verbose:
            print 'Executing code ...'
        flush_dot()
        exec(code) in {}

    flush_dot()
    d = PerfHash(dict([(100-i, i*i) for i in xrange(500)]))
    for i in xrange(500):
        assert d[100-i] == i*i
    flush_dot()
    d[None] = True
    assert d[None] == True
    
    if verbose:
        print 'Running doctest ...'
    
    verbose = False
    failure_count, test_count = doctest.testmod(report = True, verbose = False)
    print
    if failure_count:
        sys.stderr.write('FAILED\n')
        sys.exit(2)
    else:
        sys.stderr.write('%i tests passed.\n' % test_count)
        sys.stderr.write('OK\n')
        sys.exit(0)


if __name__ == '__main__':
    from optparse import OptionParser
    
    usage = "usage: %prog [options] KEYS_FILE [TMPL_FILE]"
    
    description = """\
Generates code for perfect hash functions from
a file with keywords and a code template.
If no template file is provided, a small built-in Python template
is processed and the output code is written to stdout.
"""
    
    parser = OptionParser(usage = usage,
                          description = description,
                          prog = sys.argv[0],
                          version = "%prog 0.1")
    
    parser.add_option("--delimiter",
                      action  = "store",
                      default = ", ",
                      help    = "Delimiter for list items used in output, "
                                "the default delimiter is '%default'",
                      metavar = "STR")

    parser.add_option("--indent",
                      action  = "store",
                      default = 2,
                      type    = "int",
                      help    = "Make INT spaces at the beginning of a "
                                "new line when generated list is wrapped. "
                                "Default is %default",
                      metavar = "INT")

    parser.add_option("--width",
                      action  = "store",
                      default = 76,
                      type    = "int",
                      help    = "Maximal width of generated list when "
                                "wrapped.  Default width is %default",
                      metavar = "INT")

    parser.add_option("--comment",
                      action  = "store",
                      default = "#",
                      help    = "STR is the character, or sequence of "
                                "characters, which marks the beginning "
                                "of a comment (which runs till "
                                "the end of the line), in the input "
                                "KEYS_FILE. "
                                "Default is '%default'",
                      metavar = "STR")

    parser.add_option("--splitby",
                      action  = "store",
                      default = ",",
                      help    = "STR is the character by which the columns "
                                "in the input KEYS_FILE are split. "
                                "Default is '%default'",
                      metavar = "STR")

    parser.add_option("--keycol",
                      action  = "store",
                      default = 1,
                      type    = "int",
                      help    = "Specifies the column INT in the input "
                                "KEYS_FILE which contains the keys. "
                                "Default is %default, i.e. the first column.",
                      metavar = "INT")
                      
    parser.add_option("--hashcol",
                      action  = "store",
                      default = 0,
                      type    = "int",
                      help    = "Specifies the column INT in the input "
                                "KEYS_FILE which contains the desired "
                                "hash values. "
                                "By default the hash values are given by the "
                                "sequence 0..N-1.",
                      metavar = "INT")
                      
    parser.add_option("--trails",
                      action  = "store",
                      default = 5,
                      type    = "int",
                      help    = "Specifies the number of trails before "
                                "N is increased.  A small INT will give "
                                "compute faster, but the array G will be "
                                "large.  A large INT will take longer to "
                                "compute but G will be smaller. "
                                "Default is %default",
                      metavar = "INT")
                      
    parser.add_option("--hft",
                      action  = "store",
                      default = 2,
                      type    = "int",
                      help    = "Hash function type INT (see documentation), "
                                "The default is %default",
                      metavar = "INT")

    parser.add_option("-e", "--execute",
                      action  = "store_true",
                      help    = "Execute the generated code within "
                                "the Python interpreter.")
    
    parser.add_option("-o", "--output",
                      action  = "store",
                      help    = "Specify output FILE explicitly. "
                                "`-o std' means standard output. "
                                "`-o no' means no output. "
                                "By default, the file name is obtained "
                                "from the name of the template file by "
                                "substituting `tmpl' to `code'.",
                      metavar = "FILE")
    
    parser.add_option("--test",
                      action  = "store_true",
                      help    = "Perform self test")
    
    parser.add_option("-v", "--verbose",
                      action  = "count",
                      help    = "Be verbose, "
                                "use -vv to be even more verbose")
    
    options, args = parser.parse_args()
    print type(options), '\n', repr(options)

    if options.trails > 0:
        trails = options.trails
    else:
        parser.error("trails before increasing N has to be larger than zero")

    verbose = options.verbose
    
    if options.test:
        self_test(options)
    
    if len(args) not in (1, 2):
        parser.error("incorrect number of arguments")

    if len(args) == 2 and not args[1].count('tmpl'):
        parser.error("template filename does not contain 'tmpl'")

    if options.hft == 1:
        Hash = Hash1
    elif options.hft == 2:
        Hash = Hash2
    else:
        parser.error("Hash function %i not implemented.")
    
    # --------------------- end parsing and checking --------------
    
    # ---------------- keys_file
    
    keys_file = args[0]
    
    if verbose:
        sys.stderr.write("keys_file = %r\n" % keys_file)
    
    # ---------------- keys_hashes
    
    keys_hashes = read_table(keys_file, options)
    
    if verbose >= 3:
        print_keys_hashes(keys_hashes)
        
    # ---------------- tmpl_file

    if len(args) == 2:
        tmpl_file = args[1]
    else:
        tmpl_file = None
    
    if verbose:
        sys.stderr.write("tmpl_file = %r\n" % tmpl_file)

    # ---------------- template

    if tmpl_file:
        template = read_template(tmpl_file)
    else:
        template = builtin_template(Hash)
    
    if verbose >= 3:
        print_code(template, 'TEMPLATE')
    
    # ---------------- outname
    
    if options.output:
        outname = options.output
        
    else:
        if tmpl_file:
            if tmpl_file.count('tmpl'):
                outname = tmpl_file.replace('tmpl', 'code')
            else:
                exit("Hmm, template filename does not contain 'tmpl'")
        else:
            outname = 'std'
    
    if verbose:
        sys.stderr.write("outname = %r\n" % outname)

    # ---------------- outstream
    
    if outname == 'std':
        outstream = sys.stdout

    elif outname == 'no':
        outstream = None
        
    else:
        try:
            outstream = open(outname, 'w')
        except IOError :
            exit("Error: Could not open `%s' for writing." % outname)

    # ---------------- generated code
    
    code = generate_code(keys_hashes, template, Hash, options)
    if verbose >= 3:
        print_code(code, 'GENERATED CODE')

    # ---------------- execute code
    
    if options.execute or template == builtin_template(Hash):
        if verbose:
            sys.stderr.write('Executing code...\n')
        exec(code)

    # ---------------- write code to output stream

    if outstream:
        outstream.write(code)
        if not outname == 'std':
            outstream.close()
