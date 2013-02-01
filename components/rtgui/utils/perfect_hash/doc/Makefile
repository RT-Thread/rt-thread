

all: doc.html doc.txt


doc.html: doc.in parameters.txt mktable.py
	./mktable.py >table.html
	markdown doc.in | \
            sed -e "s,<h6>table</h6>,m4_include(\`table.html')," | \
            m4 -P >doc.html
	rm table.html


doc.txt: doc.in parameters.txt
	sed <doc.in -e "s,###### table,m4_include(\`parameters.txt')," \
                    -e "s,\`\([^\`]*\)\`,'\1',g" | m4 -P >doc.txt


clean:
	rm doc.html doc.txt


