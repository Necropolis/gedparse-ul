#!/usr/bin/env ruby

require 'thor'
require 'paint'
require 'mongo'
require 'pp'

require './GedcomSplitter'
require './GedcomReader'
require './ChunkyArray'

class Gedcom < Thor
  
  desc "",""
  def foo(*ifiles)
    puts ifiles
  end
  
  
  desc "split INFILE OUTDIR CUTS", "Split the GEDCOM INFILE into CUTS pieces, placing them in the directory OUTDIR"
  def split(ifile, odir, cuts)
    ifile = File.expand_path ifile
    odir = File.expand_path odir
    cuts = cuts.to_i
    raise "Nonexistant GEDCOM #{ifile}!" unless File.exists? ifile
    raise "Not a directory #{odir}!" unless Dir.exists? odir
    # puts "cutting #{File.expand_path ifile} into #{cuts} pieces to be put in #{File.expand_path odir}"
    FamilySearch::GEDCOM::Splitter.cut!(ifile, odir, cuts) do |gedcom, outfile, size|
      puts "Cut #{File.basename(gedcom)} into #{Paint[File.basename(outfile), :green]} with size #{Paint[size, :green]} bytes"
    end
  end
  
  desc "write DBNAME COLNAME INFILE", "Write to the mongo database"
  def write(db_name, col_name, ifile)
    f=File.expand_path ifile
    raise "Nonexistant file #{ifile}" unless File.exists?(f)
    db = Mongo::Connection.new.db(db_name)
    col = db[col_name]
    FamilySearch::GEDCOM::Reader.parse f do |filename, record, records_read|
      col.insert record
      puts "#{Paint[records_read, :green]} records read from #{filename}" if records_read % 71 == 0
    end
  end
  
  desc "write_all DBNAME COLNAME INFILE0 INFILE1...", "Write the GEDCOM data to a Mongo database on localhost of db DBNAME and collection COLNAME"
  method_options :threads => 4
  def write_all(db_name, col_name, *ifiles)
    threads = options[:threads]
    
    ifiles.each{|ifile| raise "Nonexistant file #{ifile}" unless File.exists?(File.expand_path(ifile))}
    ifiles.each do |ifile|
      Process.spawn "thor gedcom:write #{db_name} #{col_name} #{ifile}"
    end
    Process.waitall
  end

  desc "read INFILE0 INFILE1...", "Read the GEDCOM, just to try parsing it."
  def read(*ifiles)
    ifiles.each{|ifile| raise "Nonexistant file #{ifile}" unless File.exists?(File.expand_path(ifile))}
    ifiles.each do |ifile|
      ifile = File.expand_path ifile
      raise "Nonexistant GEDCOM #{ifile}!" unless File.exists? ifile
    
      print "\n"
      FamilySearch::GEDCOM::Reader.parse ifile do |filename, record, records_read|
        print "\r#{Paint[records_read, :green]} records read from #{filename}"
      end
    end
  end
  
  
end
