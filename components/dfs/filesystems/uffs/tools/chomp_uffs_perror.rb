#usage:
#	find . -name "*.c" | xargs /usr/bin/ruby path/to/chomp_uffs_perror.rb
#

ARGV.each do |file|
	lines = []
	count = 0
	File.open(file).each_line do |line|
		if line =~ /^(.*uffs_Perror.+)PFX(\s*".+)$/
			lines << ($1 + $2)
			count += 1
                        #puts ($1 + $2)
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
