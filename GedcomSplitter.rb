#!/usr/env ruby

require 'FileUtils'
require 'choice'

Choice.options do

  header 'GEDCOM Splitter Options:'
  
  option :file, :required => true do
    short '-f'
    long '--file=FILE'
    desc 'The input GEDCOM to cut up'
  end
  
  option :cuts, :required => true do
    short '-c'
    long '--cuts=NUMBER'
    desc 'The number of GEDCOMs to split this into'
    cast Integer
  end
  
  option :output, :required => true do
    short '-o'
    long '--output=DIR'
    desc 'Put the output files here'
  end
  
end

FILE=File.absolute_path Choice.choices[:file]
CUTS=Choice.choices[:cuts]
OUTPUT_DIR=File.absolute_path Choice.choices[:output]
INCREMENT=File.size(FILE)/CUTS

File.open(FILE, File::RDONLY) do |f|
  CUTS.times do |t|
    buff=f.read INCREMENT
    unless f.eof?
      buff<<f.gets("\r\n0")
      f.ungetc "\r\n0"
      buff.chomp! "\r\n0"
    end
    
    fname=File.join(OUTPUT_DIR, "#{t}.GED")
    FileUtils.rm fname if File.exists? fname
    
    File.open(fname, File::WRONLY|File::CREAT) do |f|
      f.write buff
    end
  end
end

