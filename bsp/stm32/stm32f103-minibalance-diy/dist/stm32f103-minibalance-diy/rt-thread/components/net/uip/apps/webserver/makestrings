#!/usr/bin/perl


sub stringify {
  my $name = shift(@_);
  open(OUTPUTC, "> $name.c");
  open(OUTPUTH, "> $name.h");
  
  open(FILE, "$name");
  
  while(<FILE>) {
    if(/(.+) "(.+)"/) {
      $var = $1;
      $data = $2;
      
      $datan = $data;
      $datan =~ s/\\r/\r/g;
      $datan =~ s/\\n/\n/g;
      $datan =~ s/\\01/\01/g;      
      $datan =~ s/\\0/\0/g;
      
      printf(OUTPUTC "const char $var\[%d] = \n", length($datan) + 1);
      printf(OUTPUTC "/* \"$data\" */\n");
      printf(OUTPUTC "{");
      for($j = 0; $j < length($datan); $j++) {
	printf(OUTPUTC "%#02x, ", unpack("C", substr($datan, $j, 1)));
      }
      printf(OUTPUTC "};\n");
      
      printf(OUTPUTH "extern const char $var\[%d];\n", length($datan) + 1);
      
    }
  }
  close(OUTPUTC);
  close(OUTPUTH);
}
stringify("http-strings");

exit 0;

