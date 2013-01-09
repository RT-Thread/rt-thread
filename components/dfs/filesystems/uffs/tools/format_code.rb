#usage:
#	find . -name "*.c" | xargs /usr/bin/ruby path/to/format_code.rb
#

ARGV.each do |file|
	lines = []
	count = 0
	File.open(file).each_line do |line|
		if line =~ /^(.*)\s$/
			lines << $1.dup
			count += 1
		else
			lines << line
		end
	end
	if count > 0
		f = File.open(file, "w")
		lines.each do |s|
			f.puts s
		end
		f.close
		puts "Fix file #{file}, modified lines: #{count}"
	end
end
